# -*- coding: utf-8 -*-
"""
Created on Tue Aug 12 19:14:32 2025

@author: diego
"""

import numpy as np

# ====== CONFIGURE YOUR PHYSICAL LOCAL ROTATIONS HERE ======
roll_deg  = 0   # local roll  (about local x)
pitch_deg = -1  # local pitch (about local y)
yaw_deg   = -5   # local yaw   (about local z)

# ====== NEUTRAL WEDGE GEOMETRY (theta = 0 deg) ======
# neutral wedge = wedge 15 in your table
center_orig    = np.array([0.0, 0.0, 376.0])
Inner_mid_neutral    = np.array([88.02, 0.0, 388.13])
Outer_mid_neutral = np.array([220.48, 0.0, 418.92])  # pivot (must remain fixed)

# Local basis at theta = 0:
# radial (x_loc), tangential (y_loc), beam (z_loc)
x_loc = np.array([1.0, 0.0, 0.0])
y_loc = np.array([0.0, 1.0, 0.0])
z_loc = np.array([0.0, 0.0, 1.0])

def rodrigues(axis, angle_deg):
    a = np.asarray(axis, float)
    a /= np.linalg.norm(a)
    th = np.deg2rad(angle_deg)
    c, s = np.cos(th), np.sin(th)
    K = np.array([[    0, -a[2],  a[1]],
                  [ a[2],     0, -a[0]],
                  [-a[1],  a[0],     0]])
    return np.eye(3)*c + (1-c)*np.outer(a,a) + s*K

def rotate_about_pivot(p, pivot, R):
    return pivot + R @ (p - pivot)

def euler_zyx_from_R(R):
    # intrinsic ZYX (R = Rz * Ry * Rx)
    sy = np.sqrt(R[0,0]**2 + R[1,0]**2)
    if sy > 1e-12:
        x = np.arctan2(R[2,1], R[2,2])
        y = np.arctan2(-R[2,0], sy)
        z = np.arctan2(R[1,0], R[0,0])
    else:
        x = np.arctan2(-R[1,2], R[1,1])
        y = np.arctan2(-R[2,0], sy)
        z = 0.0
    return np.rad2deg([x, y, z])  # returns (X, Y, Z) in degrees

# === Build the physical rotation about LOCAL axes (intrinsic x then y then z) ===
R_phys = rodrigues(x_loc, roll_deg) @ rodrigues(y_loc, pitch_deg) @ rodrigues(z_loc, yaw_deg)

# === Rotate center/Inner_mid about the Outer_mid pivot -> Outer_mid stays fixed by construction ===
center_new = rotate_about_pivot(center_orig, Outer_mid_neutral, R_phys)
Inner_mid_new    = rotate_about_pivot(Inner_mid_neutral,   Outer_mid_neutral, R_phys)

# === Sanity check: rotating the Outer_mid about itself yields itself ===
Outer_mid_check = rotate_about_pivot(Outer_mid_neutral, Outer_mid_neutral, R_phys)

# === Extract global ZYX Euler angles and apply Perl sign convention (Perl = -Physical) ===
xE, yE, zE = euler_zyx_from_R(R_phys)
x_perl, y_perl, z_perl = -xE, -yE, -zE

# === Print results for wedge 15 (neutral) ===
print("Neutral wedge (phi=0) results:\n")
print("Outer_mid (pivot) original:", Outer_mid_neutral)
print("Outer_mid after rotation  :", Outer_mid_check, "(should match original)\n")

print("New center position:  ({:.4f}, {:.4f}, {:.4f}) cm".format(*center_new))
print("New Inner_mid position:     ({:.4f}, {:.4f}, {:.4f}) cm".format(*Inner_mid_new))
print("Global ZYX (physical): X={:.4f} deg, Y={:.4f} deg, Z={:.4f} deg".format(xE, yE, zE))
print("Perl angles (sign flip): X={:.4f} deg, Y={:.4f} deg, Z={:.4f} deg".format(x_perl, y_perl, z_perl))

# Copy-paste line for your Perl (explicit order to avoid mismatches):
print("\n# --- Perl line (neutral wedge = i==15) ---")
print(f'$detector{{"pos"}} = "{center_new[0]:.4f}*cm {center_new[1]:.4f}*cm {center_new[2]:.4f}*cm";'
      f'$detector{{"rotation"}} = "ordered: zyx {z_perl:.4f}*deg {y_perl:.4f}*deg {x_perl:.4f}*deg";'
)
