#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_PVDIS_baffle_kill';

my $envelope = "solid_$DetectorName";
my $file     = "solid_$DetectorName.txt";

my $rmin      = 1;
my $rmax      = 1000000;

my %detector = ();    # hash (map) that defines the gemc detector
$detector{"rmin"} = $rmin;
$detector{"rmax"} = $rmax;

use Getopt::Long;
use Math::Trig;


#6 plates, 9cm thick,every 30cm, 30 slits per plate, 20 blocks per slit

my $color_baffle="00C0C0";
my $material_baffle="Kryptonite";
#my $material_baffle="Vacuum";
my $sensitivity_baffle="no";
my $hit_baffle="";
# Kryptonite
# FLUX
sub make_baffle_plate_inner
{
 my $Nplate  = 6;
 my @PlateZ  = (40, 70, 100, 130, 160, 190); #(30,60,90,120,150,180)+10 in absolute coordinate
 my @Rin  = (0.20,  12.,  19.,    23.9,  28.9, 33.8);
 my @Rout = ( 0.40, 12.52, 24.65, 36.77, 48.89, 61.01,);
my $Dz   = 9.0/2.;

 for(my $n=1; $n<=$Nplate; $n++)
 {
    $detector{"name"}        = "cleopvdis_plate_inner_$n";
    $detector{"mother"}      = "root" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color_baffle";
    $detector{"type"}       = "Tube";
#    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"dimensions"} = "0.0*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "$material_baffle";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "$sensitivity_baffle";
    $detector{"hit_type"}    = "$hit_baffle";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_baffle_plate_inner();

sub make_baffle_plate_outer
{
 my $Nplate  = 6;

 my @PlateZ  = (42, 70, 100, 130, 160, 190); #(30,60,90,120,150,180)+10 in absolute coordinate
 my @Rin  = (41.31, 62.32, 83.32, 104.33, 125.34, 142.00);
 my $Rout = 145; #coil edge is at 142cm
 my $Dz   = 9.0/2.;

 for(my $n=1; $n<=$Nplate; $n++)
 {
    $detector{"name"}        = "cleopvdis_plate_outer_$n";
    $detector{"mother"}      = "root" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color_baffle";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "$material_baffle";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "$sensitivity_baffle";
    $detector{"hit_type"}    = "$hit_baffle";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_baffle_plate_outer();



#making buffle blocks, palte by plate, slit by slit,block by block
sub make_baffle_blocks
{
    my @x =(
	[   0.404026, 2.449437, 0.000000, 3.648214,
	2.449437, 4.494848, 0.000000, 4.516071,
	4.494848, 6.540259, 0.000000, 5.062500,
	6.540259, 8.585670, 0.000000, 5.158929,
	8.585670, 10.631081, 0.000000, 5.142857,
	10.631081, 12.676492, 0.000000, 5.175000,
	12.676492, 14.721903, 0.000000, 5.464286,
	14.721903, 16.767314, 0.000000, 5.914286,
	16.767314, 18.812725, 0.000000, 6.171429,
	18.812725, 20.858136, 0.000000, 6.332143,
	20.858136, 22.903547, 0.000000, 6.428571,
	22.903547, 24.948958, 0.000000, 6.750000,
	24.948958, 26.994369, 0.000000, 7.135714,
	26.994369, 29.039780, 0.000000, 7.392857,
	29.039780, 31.085191, 0.000000, 7.457143,
	31.085191, 33.130602, 0.000000, 7.810714,
	33.130602, 35.176013, 0.000000, 7.842857,
	35.176013, 37.221424, 0.000000, 8.260714,
	37.221424, 39.266835, 0.000000, 8.100000,
	39.266835, 41.312246, 0.000000, 7.650000,
	],
	[   12.524813, 15.014496, 0.729643, 4.111071,
	15.014496, 17.504179, 0.903214, 4.766786,
	17.504179, 19.993862, 1.012500, 5.306786,
	19.993862, 22.483545, 1.031786, 5.563929,
	22.483545, 24.973228, 1.028571, 5.535000,
	24.973228, 27.462911, 1.035000, 5.682857,
	27.462911, 29.952594, 1.092857, 6.017143,
	29.952594, 32.442277, 1.182857, 6.570000,
	32.442277, 34.931960, 1.234286, 6.859286,
	34.931960, 37.421643, 1.266429, 7.097143,
	37.421643, 39.911326, 1.285714, 7.206429,
	39.911326, 42.401009, 1.350000, 7.530000,
	42.401009, 44.890691, 1.427143, 7.785000,
	44.890691, 47.380374, 1.478571, 8.003571,
	47.380374, 49.870057, 1.491429, 8.067429,
	49.870057, 52.359740, 1.562143, 8.336143,
	52.359740, 54.849423, 1.568571, 8.360571,
	54.849423, 57.339106, 1.652143, 8.678143,
	57.339106, 59.828789, 1.620000, 8.550000,
	59.828789, 62.318472, 1.530000, 8.212500,
	],
	[   24.645600, 27.579555, 1.459286, 4.573929,
	27.579555, 30.513510, 1.806429, 5.017500,
	30.513510, 33.447465, 2.025000, 5.551071,
	33.447465, 36.381420, 2.063571, 5.968929,
	36.381420, 39.315375, 2.057143, 5.927143,
	39.315375, 42.249330, 2.070000, 6.190714,
	42.249330, 45.183285, 2.185714, 6.570000,
	45.183285, 48.117240, 2.365714, 7.225714,
	48.117240, 51.051194, 2.468571, 7.547143,
	51.051194, 53.985149, 2.532857, 7.862143,
	53.985149, 56.919104, 2.571429, 7.984286,
	56.919104, 59.853059, 2.700000, 8.310000,
	59.853059, 62.787014, 2.854286, 8.434286,
	62.787014, 65.720969, 2.957143, 8.614286,
	65.720969, 68.654924, 2.982857, 8.677714,
	68.654924, 71.588879, 3.124286, 8.861571,
	71.588879, 74.522834, 3.137143, 8.878286,
	74.522834, 77.456789, 3.304286, 9.095571,
	77.456789, 80.390744, 3.240000, 9.000000,
	80.390744, 83.324699, 3.060000, 8.775000,
	],
	[   36.766387, 40.144614, 2.188929, 5.036786,
	40.144614, 43.522841, 2.709643, 5.268214,
	43.522841, 46.901068, 3.037500, 5.795357,
	46.901068, 50.279295, 3.095357, 6.373929,
	50.279295, 53.657522, 3.085714, 6.319286,
	53.657522, 57.035749, 3.105000, 6.698571,
	57.035749, 60.413975, 3.278571, 7.122857,
	60.413975, 63.792202, 3.548571, 7.881429,
	63.792202, 67.170429, 3.702857, 8.235000,
	67.170429, 70.548656, 3.799286, 8.627143,
	70.548656, 73.926883, 3.857143, 8.762143,
	73.926883, 77.305110, 4.050000, 9.090000,
	77.305110, 80.683337, 4.281429, 9.083571,
	80.683337, 84.061564, 4.435714, 9.225000,
	84.061564, 87.439791, 4.474286, 9.288000,
	87.439791, 90.818018, 4.686429, 9.387000,
	90.818018, 94.196244, 4.705714, 9.396000,
	94.196244, 97.574471, 4.956429, 9.513000,
	97.574471, 100.952698, 4.860000, 9.450000,
	100.952698, 104.330925, 4.590000, 9.337500,
	],
	[   48.887174, 52.709673, 2.918571, 5.499643,
	52.709673, 56.532172, 3.612857, 5.518929,
	56.532172, 60.354671, 4.050000, 6.039643,
	60.354671, 64.177170, 4.127143, 6.778929,
	64.177170, 67.999669, 4.114286, 6.711429,
	67.999669, 71.822167, 4.140000, 7.206429,
	71.822167, 75.644666, 4.371429, 7.675714,
	75.644666, 79.467165, 4.731429, 8.537143,
	79.467165, 83.289664, 4.937143, 8.922857,
	83.289664, 87.112163, 5.065714, 9.392143,
	87.112163, 90.934662, 5.142857, 9.540000,
	90.934662, 94.757161, 5.400000, 9.870000,
	94.757161, 98.579660, 5.708571, 9.732857,
	98.579660, 102.402158, 5.914286, 9.835714,
	102.402158, 106.224657, 5.965714, 9.898286,
	106.224657, 110.047156, 6.248571, 9.912429,
	110.047156, 113.869655, 6.274286, 9.913714,
	113.869655, 117.692154, 6.608571, 9.930429,
	117.692154, 121.514653, 6.480000, 9.900000,
	121.514653, 125.337152, 6.120000, 9.900000,
	],
	[   61.007961, 65.057563, 3.648214, 5.962500,
	65.057563, 69.107165, 4.516071, 5.769643,
	69.107165, 73.156767, 5.062500, 6.283929,
	73.156767, 77.206369, 5.158929, 7.183929,
	77.206369, 81.255971, 5.142857, 7.103571,
	81.255971, 85.305573, 5.175000, 7.714286,
	85.305573, 89.355175, 5.464286, 8.228571,
	89.355175, 93.404777, 5.914286, 9.192857,
	93.404777, 97.454379, 6.171429, 9.610714,
	97.454379, 101.503981, 6.332143, 10.157143,
	101.503981, 105.553582, 6.428571, 10.317857,
	105.553582, 109.603184, 6.750000, 10.650000,
	109.603184, 113.652786, 7.135714, 10.382143,
	113.652786, 117.702388, 7.392857, 10.446429,
	117.702388, 121.751990, 7.457143, 10.508571,
	121.751990, 125.801592, 7.810714, 10.437857,
	125.801592, 129.851194, 7.842857, 10.431429,
	129.851194, 133.900796, 8.260714, 10.347857,
	133.900796, 137.950398, 8.100000, 10.350000,
	137.950398, 142.000000, 7.650000, 10.462500,
	],
    );

    my $Nplate  = 6;
    my $Nslit  = 30;

    my $Nblock  = 20;
 my @PlateZ  = (40, 70, 100, 130, 160, 190); #(30,60,90,120,150,180)+10 in absolute coordinate
    my $PlateDz   = 9.0/2;

    for(my $n=0; $n<$Nplate; $n++){
	for(my $j=0; $j<$Nblock; $j++){
	    my $j_c     = cnumber($j, 10);
	    my $n_c     = cnumber($n, 1);
	    my $i_c     = cnumber(0, 10);

	    $detector{"name"}        = "cleopvdis_plate$n_c.block$j_c";
	    $detector{"mother"}      = "root";
	    $detector{"description"} = $detector{"name"};
	    $detector{"pos"}         = "0*cm 0*cm $PlateZ[$n]*cm";
	    $detector{"rotation"}    = "0*deg 0*deg 0*deg";
	    $detector{"color"}       = "ff8800";
	    $detector{"type"}        = "Tube";
	    my $Rin  = $x[$n][0+$j*4];
	    my $Rout = $x[$n][1+$j*4];
	    my $Sphi = 0.0;
	    my $Dphi = 360.0;

	    $detector{"dimensions"}  = "$Rin*cm $Rout*cm $PlateDz*cm $Sphi*deg $Dphi*deg";
	    $detector{"material"}    = "Vacuum";
	    $detector{"mfield"}      = "no";
	    $detector{"ncopy"}       = 1;
	    $detector{"pMany"}       = 1;
	    $detector{"exist"}       = 1;
	    $detector{"visible"}     = 0;
	    $detector{"style"}       = 0;
	    $detector{"sensitivity"} = "no";
	    $detector{"hit_type"}    = "";
	    $detector{"identifiers"} = $detector{"name"};
	    print_det(\%detector, $file);

	    ################################################3

	    $detector{"name"}        = "cleopvdis_plate$n_c.slit$i_c.block$j_c";
	    $detector{"mother"}      = "cleopvdis_plate$n_c.block$j_c";
	    $detector{"description"} = $detector{"name"};
	    $detector{"pos"}         = "0*cm 0*cm 0*cm";
	    $detector{"rotation"}    = "0*deg 0*deg 0*deg";
	    $detector{"color"}       = "$color_baffle";
	    $detector{"type"}        = "Tube";

	    $Sphi = $x[$n][$j*4+2];
	    $Dphi = $x[$n][$j*4+3];

	    my $startphi = $Sphi + $Dphi;
	    my $stopphi  = $Sphi + 360.0/$Nslit;
	    my $phidiff  = $stopphi-$startphi;

	    $detector{"dimensions"}  = "$Rin*cm $Rout*cm $PlateDz*cm $startphi*deg $phidiff*deg";
	    $detector{"material"}    = "$material_baffle";
	    $detector{"mfield"}      = "no";
	    $detector{"ncopy"}       = 0;
	    $detector{"pMany"}       = 1;
	    $detector{"exist"}       = 1;
	    $detector{"visible"}     = 1;
	    $detector{"style"}       = 1;
	    $detector{"sensitivity"} = "$sensitivity_baffle";
	    $detector{"hit_type"}    = "$hit_baffle";
	    $detector{"identifiers"} = $detector{"name"};
	    print_det(\%detector, $file);


	    for(my $i=1; $i<$Nslit; $i++){
		my $slit_rotation = 360.0*$i/$Nslit;
		my $i_c     = cnumber($i, 10);
		$detector{"name"}        = "cleopvdis_plate$n_c.slit$i_c.block$j_c";
		$detector{"mother"}        = "cleopvdis_plate$n_c.block$j_c";
		$detector{"description"} = $detector{"name"};
		$detector{"pos"}         = "0*cm 0*cm 0*cm";
		$detector{"rotation"}    = "0*deg 0*deg $slit_rotation*deg";
		$detector{"color"}       = "$color_baffle";
		$detector{"type"}        = "CopyOf cleopvdis_plate$n_c.slit01.block$j_c";
		$detector{"dimensions"}  = "0*mm";
		$detector{"material"}    = "Vacuum";
		$detector{"mfield"}      = "no";
		$detector{"ncopy"}       = $i;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "no";
		$detector{"hit_type"}    = "";
		$detector{"identifiers"} = $detector{"name"};
		print_det(\%detector, $file);
	    }
	}
    }
}


make_baffle_blocks();
