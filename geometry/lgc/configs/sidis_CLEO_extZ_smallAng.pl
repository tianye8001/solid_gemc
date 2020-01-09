#hybrid configuration for PVDIS and SIDIS, with SIDIS mirror rotated.

$use_pvdis = 0;
$use_CLEO = 1;
#$ang_xrot = 63.0;
$ang_xrot = 63.0;
$ang_zrot = 1.8;
$pmtN = 3;
$rmin_w_end = 21.0;
$rmax_w_end = 21.5;

$buildM2 = 1;

#tank
$backPlaneZ = 311.0;
$image_z = 250.0;
$image_y = 245.0;
$Pos_im_Obs_V = vector($image_x, $image_y, $image_z);

$Z_M1 = 255.0;
#$Z_M1 = 255.0;
$T_M1 = 3.0;
#$cr_ang1 = 11.3;
$cr_ang1 = 9.0;
$ztarg_cent1 = -350.0;
$Angle_in1 = 7.6;
$Angle_out1 = 15.0;
$mirrAng1 = 0.0;
$zmirrRotPoint1 = $Z_M1 -39.0;

$Z_M2 = 303.0;
$T_M2 = 3.0;
$cr_ang2 = 33.5;
$ztarg_cent2 = 10.0;
$Angle_in2 = 32.5;
$Angle_out2 = 38.0;
