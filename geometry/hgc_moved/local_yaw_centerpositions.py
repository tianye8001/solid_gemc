# -*- coding: utf-8 -*-
"""
Created on Fri Aug  1 13:35:34 2025

@author: diego
"""

import numpy as np

# ========== CONFIGURATION ==========
desired_local_yaw_deg = -15
# Neutral wedge points (wedge 15 at 180°)
top_neutral = np.array([88.02, 0.0, 388.13])
bottom_neutral = np.array([220.48, 0.0, 418.92])

num_wedges = 30
z_increment_deg = 12

# Original bottom points for all 30 wedges (in order)
bottom_points_orig = np.array([
    [-215.661983, -45.84037, 418.92],
    [-201.418503, -89.67730, 418.92],
    [-178.372067, -129.5949, 418.92],
    [-147.529916, -163.8486, 418.92],
    [-110.240000, -190.9413, 418.92],
    [ -68.132067, -209.6889, 418.92],
    [ -23.046436, -219.2722, 418.92],
    [  23.046436, -219.2722, 418.92],
    [  68.132067, -209.6889, 418.92],
    [ 110.240000, -190.9413, 418.92],
    [ 147.529916, -163.8486, 418.92],
    [ 178.372067, -129.5949, 418.92],
    [ 201.418503,  -89.6773, 418.92],
    [ 215.661983,  -45.84037, 418.92],
    [ 220.480000,   0.0,      418.92],
    [ 215.661983,   45.84037, 418.92],
    [ 201.418503,   89.6773,  418.92],
    [ 178.372067,  129.5949,  418.92],
    [ 147.529916,  163.8486,  418.92],
    [ 110.240000,  190.9413,  418.92],
    [  68.132067,  209.6889,  418.92],
    [  23.046436,  219.2722,  418.92],
    [ -23.046436,  219.2722,  418.92],
    [ -68.132067,  209.6889,  418.92],
    [-110.240000,  190.9413,  418.92],
    [-147.529916,  163.8486,  418.92],
    [-178.372067,  129.5949,  418.92],
    [-201.418503,   89.6773,  418.92],
    [-215.661983,   45.84037, 418.92],
    [-220.480000,   0.0,      418.92]
])

# Global pivot point (original center)
global_pivot = np.array([0.0, 0.0, 376.0])

# Storage for outputs
wedge_rows = []
point_rows = []
new_position_centers = []

for i in range(1, num_wedges + 1):
    # Compute azimuth for wedge i, neutral at wedge 15
    theta_deg = (i - 15) * z_increment_deg
    total_z_deg = theta_deg + desired_local_yaw_deg  # Apply local yaw

    # Perl expects negative of physical rotation
    perl_angle = -(total_z_deg)

    # Rotation matrix around Z axis
    total_z_rad = np.deg2rad(total_z_deg)
    Rz = np.array([
        [np.cos(total_z_rad), -np.sin(total_z_rad), 0],
        [np.sin(total_z_rad),  np.cos(total_z_rad), 0],
        [0, 0, 1]
    ])

    # Rotate the neutral wedge points
    top_rot = Rz @ top_neutral
    bottom_rot = Rz @ bottom_neutral

    wedge_rows.append({
        "Wedge": i,
        "Euler_X*deg": 0.0,
        "Euler_Y*deg": 0.0,
        "Euler_Z*deg": perl_angle,
        "Perl_Rotation": f"0.0*deg 0.0*deg {perl_angle:.4f}*deg"
    })

    point_rows.append({
        "Wedge": i,
        "Top_X": top_rot[0], "Top_Y": top_rot[1], "Top_Z": top_rot[2],
        "Bottom_X": bottom_rot[0], "Bottom_Y": bottom_rot[1], "Bottom_Z": bottom_rot[2]
    })

    # Calculate translation to shift pivot so rotated bottom aligns with original bottom
    translation_vector = bottom_points_orig[i-1] - bottom_rot
    new_pos_center = global_pivot + translation_vector
    new_position_centers.append(new_pos_center)

# Convert to numpy array for easier handling
new_position_centers = np.array(new_position_centers)

# ====== OUTPUT ======

print("\n# === Perl code for all 30 wedges (position and rotation matched for local yaw) ===\n")
for i, pos in enumerate(new_position_centers, start=1):
    perl_rotation = wedge_rows[i-1]["Perl_Rotation"].replace(";", "")
    print(f'elsif ($i=={i}) {{ $detector{{"pos"}} = "{pos[0]:.6f}*cm {pos[1]:.6f}*cm {pos[2]:.6f}*cm"; $detector{{"rotation"}} = "{perl_rotation}"; }}  # wedge {i}, local yaw {desired_local_yaw_deg} deg')
