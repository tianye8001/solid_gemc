#!/usr/bin/env python3
"""
General RK4 propagator for charged particles in SoLID-style mapped magnetic fields.

Library API
-----------
    load_map(fname, n_outer, n_inner)          -> (axis1, axis2, B1, B2)
    momentum_from_angles(p, theta_deg, phi_deg)-> (px, py, pz) GeV/c
    field_at(pos, solenoid=, oxford=, ...)     -> B vector (Gauss)
    propagate(charge, momentum, vertex, z_stop, solenoid=, oxford=, ...)
        returns (final_pos_cm, final_phat)

Field models
------------
    - solenoid (cylindrical-z, axis along lab z, centered at origin)
    - oxford   (cylindrical-x, axis along lab x, centered at `oxford_origin`)

When BOTH fields are passed, the oxford field overrides the solenoid inside a cube
of half-size `oxford_box_half` centered at `oxford_origin` — this matches GEMC's
G4FieldManager local-override behaviour for the SoLID NH3 target volume.
Pass only one of solenoid / oxford to use that field everywhere.

Conventions
-----------
    - All positions in cm, momenta in GeV/c, fields in Gauss.
    - charge is in units of |e|; pi- is -1, chargedgeantino / pi+ / proton is +1.
    - Equation: dp̂/ds = charge * k * (p̂ × B), with k = 2.998e-7 / |p_GeV| (cm^-1 G^-1).

Validation: see `test_geantino_field.py` (Δr ≤ 6 mm vs Geant4 chargedgeantino).
"""
import numpy as np
import argparse

FIELD_DIR = "../../field"
K_FACTOR = 2.998e-7  # |e|*c in cm^-1 * G^-1 * GeV (so k = K_FACTOR / p_GeV)


# -------- field map loading & interpolation --------

def load_map(fname, n_outer, n_inner):
    """Load a GEMC ASCII field map. The file's outer loop has n_outer points and the
    inner loop has n_inner points. Returns (axis1_vals, axis2_vals, B1, B2) where
    Bn are 2D arrays shaped [n_outer, n_inner] = [transverse, longitudinal] for both
    cylindrical-z (solenoid) and cylindrical-x (oxford) maps."""
    rows = []
    with open(fname) as f:
        for line in f:
            parts = line.split()
            if len(parts) == 4:
                try:
                    rows.append([float(p) for p in parts])
                except ValueError:
                    pass  # XML attribute lines that happen to have 4 tokens
    data = np.array(rows)
    assert data.shape[0] == n_outer * n_inner, \
        f"Expected {n_outer*n_inner} rows, got {data.shape[0]}"
    axis1 = data[::n_inner, 0]
    axis2 = data[:n_inner, 1]
    B1 = data[:, 2].reshape(n_outer, n_inner)
    B2 = data[:, 3].reshape(n_outer, n_inner)
    return axis1, axis2, B1, B2


def bilinear(x_grid, y_grid, Z, x, y):
    """Bilinear interpolation on a regular grid Z[ix, iy]."""
    i = int(np.clip(np.searchsorted(x_grid, x) - 1, 0, len(x_grid) - 2))
    j = int(np.clip(np.searchsorted(y_grid, y) - 1, 0, len(y_grid) - 2))
    fx = (x - x_grid[i]) / (x_grid[i+1] - x_grid[i])
    fy = (y - y_grid[j]) / (y_grid[j+1] - y_grid[j])
    return (Z[i,   j  ] * (1-fx) * (1-fy) +
            Z[i+1, j  ] *    fx  * (1-fy) +
            Z[i,   j+1] * (1-fx) *    fy  +
            Z[i+1, j+1] *    fx  *    fy)


# -------- per-field evaluators --------

def solenoid_field_at(pos, solenoid):
    """Cylindrical-z field at lab position `pos` (cm). Symmetry axis = lab z."""
    x, y, z = pos
    r_grid, z_grid, Br_map, Bz_map = solenoid
    r_cyl = np.sqrt(x*x + y*y)
    r_c = min(r_cyl, r_grid[-1])
    z_c = float(np.clip(z, z_grid[0], z_grid[-1]))
    Bz = bilinear(r_grid, z_grid, Bz_map, r_c, z_c)
    if r_cyl > 1e-10:
        Br = bilinear(r_grid, z_grid, Br_map, r_c, z_c)
        return np.array([Br * x / r_cyl, Br * y / r_cyl, Bz])
    return np.array([0.0, 0.0, Bz])


def oxford_field_at(pos, oxford, origin=(0.0, 0.0, -350.0)):
    """Cylindrical-x field at lab position `pos` (cm). Symmetry axis = lab x.
    `origin` is the field map center (matches DISPLACE_FIELDMAP in the gcard)."""
    x, y, z = pos
    ox, oy, oz = origin
    rp_grid, x_grid, Br_map, Bx_map = oxford
    dx = x - ox
    dy = y - oy
    dz = z - oz
    r_perp = np.sqrt(dy*dy + dz*dz)
    rp_c = min(r_perp, rp_grid[-1])
    x_c = float(np.clip(dx, x_grid[0], x_grid[-1]))
    Bx = bilinear(rp_grid, x_grid, Bx_map, rp_c, x_c)
    if r_perp > 1e-10:
        Br = bilinear(rp_grid, x_grid, Br_map, rp_c, x_c)
        return np.array([Bx, Br * dy / r_perp, Br * dz / r_perp])
    return np.array([Bx, 0.0, 0.0])


def field_at(pos, solenoid=None, oxford=None,
             oxford_origin=(0.0, 0.0, -350.0), oxford_box_half=65.0):
    """Return B (Gauss) at lab `pos` (cm). Implements GEMC's local-override:
    inside a cube centered at `oxford_origin` with half-side `oxford_box_half`,
    the oxford field replaces the solenoid; outside, only solenoid is used."""
    if oxford is not None:
        x, y, z = pos
        ox, oy, oz = oxford_origin
        if (abs(x - ox) <= oxford_box_half and
            abs(y - oy) <= oxford_box_half and
            abs(z - oz) <= oxford_box_half):
            return oxford_field_at(pos, oxford, oxford_origin)
    if solenoid is not None:
        return solenoid_field_at(pos, solenoid)
    if oxford is not None:
        return oxford_field_at(pos, oxford, oxford_origin)
    return np.zeros(3)


# -------- RK4 step & main propagator --------

def _rk4_step(pos, phat, ds, charge, k, field_kwargs):
    def deriv(p, ph):
        B = field_at(p, **field_kwargs)
        return ph, charge * k * np.cross(ph, B)
    dx1, dp1 = deriv(pos,                  phat)
    dx2, dp2 = deriv(pos + 0.5*ds*dx1,     phat + 0.5*ds*dp1)
    dx3, dp3 = deriv(pos + 0.5*ds*dx2,     phat + 0.5*ds*dp2)
    dx4, dp4 = deriv(pos +     ds*dx3,     phat +     ds*dp3)
    new_pos  = pos  + (ds/6.0) * (dx1 + 2*dx2 + 2*dx3 + dx4)
    new_phat = phat + (ds/6.0) * (dp1 + 2*dp2 + 2*dp3 + dp4)
    new_phat /= np.linalg.norm(new_phat)
    return new_pos, new_phat


def momentum_from_angles(p_GeV, theta_deg, phi_deg):
    """Convert (|p|, theta, phi) to (px, py, pz) in GeV/c."""
    theta = np.radians(theta_deg)
    phi   = np.radians(phi_deg)
    return np.array([p_GeV * np.sin(theta) * np.cos(phi),
                     p_GeV * np.sin(theta) * np.sin(phi),
                     p_GeV * np.cos(theta)])


def propagate(charge, momentum, vertex, z_stop,
              solenoid=None, oxford=None,
              oxford_origin=(0.0, 0.0, -350.0), oxford_box_half=65.0,
              ds_cm=0.05, ds_fine_cm=0.01,
              return_path=False, checkpoints=None):
    """Propagate a charged particle from `vertex` until it reaches z = `z_stop`.

    Args:
        charge:        particle charge in units of |e| (e.g. +1, -1).
        momentum:      (px, py, pz) in GeV/c — 3-vector.
        vertex:        (vx, vy, vz) in cm — starting position.
        z_stop:        cm — propagation stops when pos[2] >= z_stop.
        solenoid:      tuple from load_map(...) for cylindrical-z field, or None.
        oxford:        tuple from load_map(...) for cylindrical-x field, or None.
        oxford_origin: (x,y,z) cm — center of the oxford field box (DISPLACE_FIELDMAP).
        oxford_box_half: cm — half-side of cube where oxford overrides solenoid.
        ds_cm:         step size outside the oxford box (default 0.05 cm).
        ds_fine_cm:    step size inside the oxford box (default 0.01 cm).
        return_path:   if True, returns list of (pos, phat) tuples along path.
        checkpoints:   optional list of z values (cm) to print track state at.

    Returns:
        (final_pos, final_phat)  — both numpy arrays of shape (3,).
        If return_path: also returns list of (pos, phat) at each step.
    """
    momentum = np.asarray(momentum, dtype=float)
    p_mag = np.linalg.norm(momentum)
    if p_mag <= 0:
        raise ValueError("momentum must be nonzero")
    pos  = np.asarray(vertex, dtype=float).copy()
    phat = momentum / p_mag
    k = K_FACTOR / p_mag

    field_kwargs = dict(solenoid=solenoid, oxford=oxford,
                        oxford_origin=oxford_origin, oxford_box_half=oxford_box_half)

    next_ckpt = iter(sorted(checkpoints or []))
    ckpt = next(next_ckpt, None)

    path = [(pos.copy(), phat.copy())] if return_path else None

    if phat[2] <= 0:
        raise ValueError(f"Initial pz must be positive (got phat={phat}); cannot reach z_stop={z_stop}")

    while pos[2] < z_stop:
        ox, oy, oz = oxford_origin
        in_box = (oxford is not None and
                  abs(pos[0] - ox) <= oxford_box_half and
                  abs(pos[1] - oy) <= oxford_box_half and
                  abs(pos[2] - oz) <= oxford_box_half)
        ds = ds_fine_cm if in_box else ds_cm

        # cap step to land exactly at z_stop
        z_remaining = z_stop - pos[2]
        if phat[2] * ds > z_remaining:
            ds = z_remaining / phat[2]

        if ckpt is not None and pos[2] >= ckpt:
            B = field_at(pos, **field_kwargs)
            print(f"    z={pos[2]*10:7.0f}mm  pos=({pos[0]*10:7.1f},{pos[1]*10:7.1f}) mm  "
                  f"B=({B[0]:7.0f},{B[1]:7.0f},{B[2]:7.0f}) G")
            ckpt = next(next_ckpt, None)

        pos, phat = _rk4_step(pos, phat, ds, charge, k, field_kwargs)
        if return_path:
            path.append((pos.copy(), phat.copy()))

    if return_path:
        return pos, phat, path
    return pos, phat


# -------- CLI --------

_CLI_EPILOG = """\
Examples
--------
  # pi- (q=-1), p=7.5 GeV at theta=8 deg, phi=0, vertex (0,0,-350cm), to HGC at z=313cm:
  rk4_propagate.py --charge -1 --p 7.5 --theta 8 --phi 0 --vz -350 --z 313 --solenoid --oxford

  # chargedgeantino with cartesian momentum, no oxford (solenoid only):
  rk4_propagate.py --charge +1 --px 1.044 --py 0 --pz 7.427 --vz -350 --z 313 --solenoid

  # JSON output (for piping into other tools):
  rk4_propagate.py --charge -1 --p 5 --theta 12 --phi 45 --vz -350 --z 200 --solenoid --oxford --json

  # Print track state at intermediate z planes (use --checkpoints=... for negative values):
  rk4_propagate.py --charge -1 --p 7.5 --theta 8 --phi 90 --vz -350 --z 313 \\
                   --solenoid --oxford --checkpoints=-300,-200,-100,0,100,200

Specify momentum either with --p/--theta/--phi (spherical) or --px/--py/--pz (cartesian).
All positions are cm, momenta GeV/c, fields Gauss. Charge in units of |e|.
"""


def _build_argparser():
    p = argparse.ArgumentParser(
        prog="rk4_propagate",
        description="RK4 propagator for charged particles in SoLID mapped magnetic fields.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=_CLI_EPILOG)
    p.add_argument("--charge", type=float, required=True, help="charge in |e| (e.g. -1, +1)")
    # momentum: angle form
    p.add_argument("--p",     type=float, help="|p| in GeV/c (use with --theta/--phi)")
    p.add_argument("--theta", type=float, help="polar angle in degrees")
    p.add_argument("--phi",   type=float, help="azimuthal angle in degrees")
    # momentum: cartesian form
    p.add_argument("--px", type=float, help="px in GeV/c (use with --py/--pz)")
    p.add_argument("--py", type=float, help="py in GeV/c")
    p.add_argument("--pz", type=float, help="pz in GeV/c")
    # vertex
    p.add_argument("--vx", type=float, default=0.0, help="vertex x in cm (default: 0)")
    p.add_argument("--vy", type=float, default=0.0, help="vertex y in cm (default: 0)")
    p.add_argument("--vz", type=float, default=-350.0, help="vertex z in cm (default: -350)")
    # output plane
    p.add_argument("--z", type=float, required=True, help="target z plane in cm")
    # field selection
    p.add_argument("--solenoid", action="store_true", help="enable solenoid_CLEOv9")
    p.add_argument("--oxford",   action="store_true", help="enable oxford_ptarget at z=-350 cm")
    p.add_argument("--solenoid-file", default=f"{FIELD_DIR}/solenoid_CLEOv9.dat",
                   help="solenoid map path (default: %(default)s)")
    p.add_argument("--oxford-file",   default=f"{FIELD_DIR}/oxford_ptarget.dat",
                   help="oxford map path (default: %(default)s)")
    p.add_argument("--oxford-origin", type=str, default="0,0,-350",
                   help="oxford map center, cm, comma-separated (default: 0,0,-350)")
    p.add_argument("--oxford-box-half", type=float, default=65.0,
                   help="oxford-override cube half-size, cm (default: 65)")
    # integration
    p.add_argument("--ds",      type=float, default=0.05, help="step outside oxford box, cm (default: 0.05)")
    p.add_argument("--ds-fine", type=float, default=0.01, help="step inside oxford box, cm (default: 0.01)")
    p.add_argument("--checkpoints", type=str, default="",
                   help="comma-separated z values (cm) to print track state at")
    # output formatting
    p.add_argument("--json",  action="store_true", help="emit result as one JSON line")
    p.add_argument("--quiet", "-q", action="store_true", help="suppress map-loading messages")
    return p


def _parse_momentum(args):
    px, py, pz = args.px, args.py, args.pz
    p, theta, phi = args.p, args.theta, args.phi
    cart_given = sum(v is not None for v in (px, py, pz))
    sph_given  = sum(v is not None for v in (p, theta, phi))
    if cart_given == 3 and sph_given == 0:
        return np.array([px, py, pz])
    if sph_given == 3 and cart_given == 0:
        return momentum_from_angles(p, theta, phi)
    raise SystemExit(
        "ERROR: specify momentum exactly one way — either --px/--py/--pz "
        "(all three) OR --p/--theta/--phi (all three).")


def main():
    import json
    args = _build_argparser().parse_args()
    p_vec = _parse_momentum(args)

    sol = oxf = None
    if args.solenoid:
        if not args.quiet: print(f"Loading solenoid map: {args.solenoid_file}")
        sol = load_map(args.solenoid_file, 501, 1201)
    if args.oxford:
        if not args.quiet: print(f"Loading oxford map:   {args.oxford_file}")
        oxf = load_map(args.oxford_file, 200, 401)
    if sol is None and oxf is None and not args.quiet:
        print("WARNING: no field selected — track will be a straight line.")

    oxford_origin = tuple(float(v) for v in args.oxford_origin.split(","))
    if len(oxford_origin) != 3:
        raise SystemExit("--oxford-origin must be 'x,y,z' (3 values)")

    ckpts = [float(x) for x in args.checkpoints.split(",") if x.strip()] or None

    final_pos, final_phat = propagate(
        charge=args.charge,
        momentum=p_vec,
        vertex=(args.vx, args.vy, args.vz),
        z_stop=args.z,
        solenoid=sol, oxford=oxf,
        oxford_origin=oxford_origin,
        oxford_box_half=args.oxford_box_half,
        ds_cm=args.ds, ds_fine_cm=args.ds_fine,
        checkpoints=ckpts)

    x_mm, y_mm, z_mm = final_pos[0]*10, final_pos[1]*10, final_pos[2]*10
    r_mm = float(np.sqrt(x_mm*x_mm + y_mm*y_mm))

    if args.json:
        out = {
            "x_mm": float(x_mm), "y_mm": float(y_mm), "z_mm": float(z_mm),
            "r_mm": r_mm,
            "phat": [float(v) for v in final_phat],
            "input": {
                "charge": args.charge,
                "momentum_GeV": [float(v) for v in p_vec],
                "vertex_cm": [args.vx, args.vy, args.vz],
                "z_stop_cm": args.z,
                "solenoid": args.solenoid, "oxford": args.oxford,
            },
        }
        print(json.dumps(out))
    else:
        print(f"Final position at z = {z_mm:.1f} mm:")
        print(f"  x = {x_mm:.3f} mm")
        print(f"  y = {y_mm:.3f} mm")
        print(f"  r = {r_mm:.3f} mm")
        print(f"Final unit momentum: ({final_phat[0]:.6f}, {final_phat[1]:.6f}, {final_phat[2]:.6f})")


if __name__ == "__main__":
    main()
