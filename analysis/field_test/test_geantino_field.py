#!/usr/bin/env python3
"""
Validation test for rk4_propagate.py against Geant4 chargedgeantino reference.

Test setup
----------
chargedgeantino (q=+1, no material interactions), p=7.5 GeV/c, theta=8 deg,
vertex=(0,0,-350cm), propagated to z=313 cm (HGC plane). 4 phi values.

Reference data was produced by `run_NH3_geantino_test.sh` which runs
`solid_SIDIS_NH3_moved_hgc_batch.gcard` for chargedgeantino with N=1.
Extracted from the flux bank at id=2210000 (HGC), pid=0 (chargedgeantino).

Why chargedgeantino, not pi-
----------------------------
Pi- at large transverse deflection is contaminated by material interactions
(only ~466/1000 phi=90 events even reach the HGC, distribution dominated
by secondaries with 5-95 percentile spanning 1.3 m). Chargedgeantino has
charge but no interactions, so reproduces clean field propagation.

Expected agreement
------------------
Δr ≤ 0.05 mm where the track travels mostly along the oxford symmetry axis
(phi=0, 180), Δr ≤ 6 mm at phi=90/270 where the track crosses the oxford
Bx sign-flip region at r_perp ~ 30 cm. Lower ds_fine to 0.002 for sub-mm
at phi=90. phi=270 is not in the HGC active area (track lands at y<0).
"""
import numpy as np
from rk4_propagate import (FIELD_DIR, load_map, momentum_from_angles, propagate)


# Reference data from run_NH3_geantino_test.sh, 2026-05-01
GEANT4_REF = {
    0:   (949.08,   74.57),    # mm
    90:  (147.85, 1140.83),
    180: (-892.31,  331.88),
    270: None,                 # track misses HGC active area in Geant4
}

# Track parameters (chargedgeantino)
CHARGE   = +1
P_GEV    = 7.5
THETA    = 8.0
VERTEX   = (0.0, 0.0, -350.0)  # cm
Z_HGC    = 313.0               # cm = 3130 mm


def main():
    print("Loading field maps...")
    sol = load_map(f"{FIELD_DIR}/solenoid_CLEOv9.dat", 501, 1201)
    oxf = load_map(f"{FIELD_DIR}/oxford_ptarget.dat", 200, 401)

    print(f"\nchargedgeantino  q=+1  p={P_GEV} GeV/c  theta={THETA} deg")
    print(f"vertex={VERTEX} cm  →  z_stop={Z_HGC} cm")
    print("=" * 75)

    max_dr = 0.0
    for phi in (0, 90, 180, 270):
        p_vec = momentum_from_angles(P_GEV, THETA, phi)
        final_pos, _ = propagate(
            charge=CHARGE, momentum=p_vec, vertex=VERTEX, z_stop=Z_HGC,
            solenoid=sol, oxford=oxf)
        x_mm, y_mm = final_pos[0]*10, final_pos[1]*10

        ref = GEANT4_REF[phi]
        print(f"\nphi = {phi:3d} deg")
        print(f"  RK4:    x = {x_mm:9.2f}  y = {y_mm:9.2f}  mm")
        if ref is None:
            print(f"  Geant4: track missed HGC active area — RK4 prediction not validated")
        else:
            gx, gy = ref
            dx, dy = x_mm - gx, y_mm - gy
            dr = np.sqrt(dx*dx + dy*dy)
            max_dr = max(max_dr, dr)
            print(f"  Geant4: x = {gx:9.2f}  y = {gy:9.2f}  mm")
            print(f"  Δx = {dx:+7.2f}  Δy = {dy:+7.2f}  mm    Δr = {dr:.2f} mm")

    print("\n" + "=" * 75)
    print(f"Max Δr (validated phi values): {max_dr:.2f} mm")
    print("PASS" if max_dr < 10.0 else "FAIL — investigate")


if __name__ == "__main__":
    main()
