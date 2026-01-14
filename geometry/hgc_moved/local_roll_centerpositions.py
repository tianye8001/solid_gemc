# -*- coding: utf-8 -*-
"""
Created on Wed Aug  6 01:54:31 2025

@author: diego
"""

import numpy as np

def rotate_about_axis(point, axis_point, axis_dir, angle_deg):
    angle = np.deg2rad(angle_deg)
    p = point - axis_point
    u = axis_dir / np.linalg.norm(axis_dir)
    c = np.cos(angle)
    s = np.sin(angle)
    C = 1 - c
    ux, uy, uz = u
    R = np.array([
        [c + ux*ux*C,     ux*uy*C - uz*s, ux*uz*C + uy*s],
        [uy*ux*C + uz*s,  c + uy*uy*C,    uy*uz*C - ux*s],
        [uz*ux*C - uy*s,  uz*uy*C + ux*s, c + uz*uz*C   ]
    ])
    p_rot = R @ p
    return axis_point + p_rot

# --- USER INPUT ---
local_roll = -15  # What you want physically (e.g., -15 for left roll)
global_roll_deg = -local_roll  # Use this for Euler angle code! (positive value for left roll)

num_wedges = 30
z_increment_deg = 12
orig_center = np.array([0, 0, 376])

# Geometry order: -168 to 180 in 12 deg steps
# outer edge mid point x,y,z for 30 mirrors
theta_zs_geom = np.arange(-168, 181, 12)
bottom_points = np.array([
    [-215.661983,  -45.84037,   418.92],
    [-201.418503,  -89.6773,    418.92],
    [-178.372067, -129.5949,    418.92],
    [-147.529916, -163.8486,    418.92],
    [-110.240000, -190.9413,    418.92],
    [ -68.132067, -209.6889,    418.92],
    [ -23.046436, -219.2722,    418.92],
    [  23.046436, -219.2722,    418.92],
    [  68.132067, -209.6889,    418.92],
    [ 110.240000, -190.9413,    418.92],
    [ 147.529916, -163.8486,    418.92],
    [ 178.372067, -129.5949,    418.92],
    [ 201.418503,  -89.6773,    418.92],
    [ 215.661983,  -45.84037,   418.92],
    [ 220.480000,    0.0,       418.92], # 1st mirror in perl script
    [ 215.661983,   45.84037,   418.92],
    [ 201.418503,   89.6773,    418.92],
    [ 178.372067,  129.5949,    418.92],
    [ 147.529916,  163.8486,    418.92],
    [ 110.240000,  190.9413,    418.92],
    [  68.132067,  209.6889,    418.92],
    [  23.046436,  219.2722,    418.92],
    [ -23.046436,  219.2722,    418.92],
    [ -68.132067,  209.6889,    418.92],
    [-110.240000,  190.9413,    418.92],
    [-147.529916,  163.8486,    418.92],
    [-178.372067,  129.5949,    418.92],
    [-201.418503,   89.6773,    418.92],
    [-215.661983,   45.84037,   418.92],
    [-220.480000,   0.0,        418.92], # 15th mirror in perl script
])

# --- Position Calculation (geometry order) for the mirror position in perl script ---
positions = []
for i in range(num_wedges):
    bottom = bottom_points[i]
    theta = np.deg2rad(theta_zs_geom[i])
    # Local X axis after wedge's Z rotation
    axis = np.array([np.cos(theta), np.sin(theta), 0])
    center = orig_center
    rot_center = rotate_about_axis(center, bottom, axis, local_roll)
    positions.append(rot_center)

# --- Euler Angle Calculation (rotation order, to be shifted) for the mirror rotation in perl script  ---
euler_angles = []
for i in range(num_wedges):
    theta_z_deg = (i+1) * z_increment_deg
    theta_z_rad = np.deg2rad(theta_z_deg)
    Rx_roll = np.array([
        [1, 0, 0],
        [0, np.cos(np.deg2rad(global_roll_deg)), -np.sin(np.deg2rad(global_roll_deg))],
        [0, np.sin(np.deg2rad(global_roll_deg)), np.cos(np.deg2rad(global_roll_deg))]
    ])
    Rz = np.array([
        [np.cos(theta_z_rad), -np.sin(theta_z_rad), 0],
        [np.sin(theta_z_rad),  np.cos(theta_z_rad), 0],
        [0, 0, 1]
    ])
    R_combined = Rx_roll @ Rz
    sy = np.sqrt(R_combined[0,0]**2 + R_combined[1,0]**2)
    if sy > 1e-6:
        x_rad = np.arctan2(R_combined[2,1], R_combined[2,2])
        y_rad = np.arctan2(-R_combined[2,0], sy)
        z_rad = np.arctan2(R_combined[1,0], R_combined[0,0])
    else:
        x_rad = np.arctan2(-R_combined[1,2], R_combined[1,1])
        y_rad = np.arctan2(-R_combined[2,0], sy)
        z_rad = 0
    x_deg = np.rad2deg(x_rad)
    y_deg = np.rad2deg(y_rad)
    z_deg = np.rad2deg(z_rad)
    euler_angles.append((x_deg, y_deg, z_deg))

# -- Shift euler_angles to match geometry order --
euler_angles_shifted = np.roll(euler_angles, -15, axis=0)  # Now wedge 1 matches -168°, etc

# -- For local roll: Do NOT flip X; only flip Z if needed for convention (here we'll keep Z as calculated) --
euler_angles_perl = [(x, y, z) for (x, y, z) in euler_angles_shifted]

# --- Output Perl lines ---
print("\n# === Perl code for all 30 wedges (position and rotation matched for local roll) ===\n")
for i in range(num_wedges):
    x, y, z = positions[i]
    xang, yang, zang = euler_angles_perl[i]
    print(f'elsif ($i=={i+1}) {{ $detector{{"pos"}} = "{x:.4f}*cm {y:.4f}*cm {z:.4f}*cm"; $detector{{"rotation"}} = "{xang:.4f}*deg {yang:.4f}*deg {zang:.4f}*deg"; }}  # wedge {i+1}, theta_z={theta_zs_geom[i]}')
