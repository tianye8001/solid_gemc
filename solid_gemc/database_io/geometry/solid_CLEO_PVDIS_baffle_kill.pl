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

my $DetectorMother="root";

my $color_baffle="00C0C0";

my $material_baffle="Kryptonite";
my $sensitivity_baffle="no";
my $hit_baffle="";

# In PVDIS PAC34 proposal, page 35 (http://hallaweb.jlab.org/collab/PAC/PAC34/PR-09-012-pvdis.pdf). It's mentioned that the baffle position is 30,60,90,120,150,180cm relative to BaBar solenoid coil center at 0. But it's actually relative to the target center which is at 10cm as seen on the Fig 3.3 on page 31.
# Later on, it seems Eugene has further tweaked them to 30,58,86,114,142,170. refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/geant3/solid_comgeant_pvdis/pvdis_02_01_p_14_01/fort.22

#6 plates, 9cm thick,every 28cm, 30 slits per plate, 20 blocks per slit

my $targetoff=10; # target offset in cm

 my $Nplate  = 6;
 my @PlateZ  = (30+$targetoff,58+$targetoff,86+$targetoff,114+$targetoff,142+$targetoff,170+$targetoff);
 my $Dz   = 9.0/2.;

sub make_baffle_plate_inner
{
#  my @Rin  = (2.00, 10.86, 21.61, 32.36, 43.10, 53.85);
#  my @Rout = (2.11, 12.86, 23.61, 34.36, 45.10, 55.85);
 my @Rin = (3.80, 10.86, 21.61, 32.36, 43.10, 53.85);
 my @Rout = (4.00, 12.86, 23.61, 34.36, 45.10, 55.85);


 for(my $n=1; $n<=$Nplate; $n++)
 {
    my $n_c     = cnumber($n-1, 1);
    $detector{"name"}        = "$DetectorName\_plateinner$n_c";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color_baffle";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "$material_baffle";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "$sensitivity_baffle";
    $detector{"hit_type"}    = "$hit_baffle";
    my $id=0+$n*100000;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%detector, $file);
 }
}
make_baffle_plate_inner();

sub make_baffle_plate_outer
{
 my @Rin  = (39.60, 59.94, 80.28, 100.63, 120.97, 141.31);
 my @Rout = (41.60, 61.94, 82.28, 102.63, 122.97, 143.31);

 for(my $n=1; $n<=$Nplate; $n++)
 {
    my $n_c     = cnumber($n-1, 1);
    $detector{"name"}        = "$DetectorName\_plateouter$n_c";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color_baffle";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "$material_baffle";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "$sensitivity_baffle";
    $detector{"hit_type"}    = "$hit_baffle";
    my $id=0+$n*100000;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%detector, $file);
 }
}
make_baffle_plate_outer();

#making buffle blocks, palte by plate, slit by slit,block by block
sub make_baffle_blocks
{
my @x =( 
[
 4.00,  5.78,  7.37,  5.62,
 5.78,  7.56,  6.67,  6.06,
 7.56,  9.34,  6.36,  6.42,
 9.34, 11.12,  5.76,  6.70,
11.12, 12.90,  4.97,  7.12,
12.90, 14.68,  4.71,  6.82,
14.68, 16.46,  4.05,  7.04,
16.46, 18.24,  3.32,  7.43,
18.24, 20.02,  2.99,  7.79,
20.02, 21.80,  2.68,  8.14,
21.80, 23.58,  2.36,  8.49,
23.58, 25.36,  2.02,  8.87,
25.36, 27.14,  1.61,  9.32,
27.14, 28.92,  1.66,  9.27,
28.92, 30.70,  1.67,  9.25,
30.70, 32.48,  1.82,  9.09,
32.48, 34.26,  1.93,  8.96,
34.26, 36.04,  1.91,  8.99,
36.04, 37.82,  2.00,  8.89,
37.82, 39.60,  1.96,  8.93
],
[
12.86, 15.21,  8.49,  5.70,
15.21, 17.57,  7.88,  6.16,
17.57, 19.92,  7.64,  6.42,
19.92, 22.28,  7.10,  6.78,
22.28, 24.63,  6.40,  7.26,
24.63, 26.98,  6.08,  7.24,
26.98, 29.34,  5.46,  7.59,
29.34, 31.69,  4.80,  8.04,
31.69, 34.05,  4.55,  8.32,
34.05, 36.40,  4.30,  8.58,
36.40, 38.75,  4.06,  8.85,
38.75, 41.11,  3.79,  9.14,
41.11, 43.46,  3.47,  9.49,
43.46, 45.82,  3.51,  9.45,
45.82, 48.17,  3.52,  9.43,
48.17, 50.52,  3.64,  9.31,
50.52, 52.88,  3.73,  9.21,
52.88, 55.23,  3.71,  9.23,
55.23, 57.59,  3.78,  9.16,
57.59, 59.94,  3.75,  9.19
],
[
23.61, 26.44,  9.62,  5.78,
26.44, 29.28,  9.09,  6.26,
29.28, 32.11,  8.92,  6.43,
32.11, 34.94,  8.44,  6.85,
34.94, 37.78,  7.82,  7.40,
37.78, 40.61,  7.44,  7.66,
40.61, 43.44,  6.87,  8.15,
43.44, 46.28,  6.29,  8.66,
46.28, 49.11,  6.11,  8.85,
49.11, 51.95,  5.93,  9.03,
51.95, 54.78,  5.76,  9.21,
54.78, 57.61,  5.57,  9.41,
57.61, 60.45,  5.34,  9.65,
60.45, 63.28,  5.36,  9.62,
63.28, 66.11,  5.37,  9.61,
66.11, 68.95,  5.45,  9.53,
68.95, 71.78,  5.52,  9.46,
71.78, 74.62,  5.50,  9.48,
74.62, 77.45,  5.55,  9.42,
77.45, 80.28,  5.54,  9.44
],
[
34.36, 37.67, 10.74,  5.86,
37.67, 40.98, 10.30,  6.35,
40.98, 44.30, 10.21,  6.44,
44.30, 47.61,  9.78,  6.93,
47.61, 50.92,  9.25,  7.53,
50.92, 54.24,  8.81,  8.09,
54.24, 57.55,  8.28,  8.71,
57.55, 60.86,  7.77,  9.28,
60.86, 64.18,  7.66,  9.38,
64.18, 67.49,  7.56,  9.48,
67.49, 70.80,  7.45,  9.58,
70.80, 74.12,  7.34,  9.68,
74.12, 77.43,  7.20,  9.81,
77.43, 80.75,  7.22,  9.80,
80.75, 84.06,  7.22,  9.79,
84.06, 87.37,  7.27,  9.75,
87.37, 90.69,  7.31,  9.71,
90.69, 94.00,  7.30,  9.72,
94.00, 97.31,  7.33,  9.69,
97.31, 100.63,  7.32,  9.70
],
[
45.10, 48.90, 11.86,  5.95,
48.90, 52.69, 11.51,  6.45,
52.69, 56.48, 11.49,  6.45,
56.48, 60.28, 11.11,  7.01,
60.28, 64.07, 10.67,  7.67,
64.07, 67.86, 10.17,  8.51,
67.86, 71.66,  9.68,  9.26,
71.66, 75.45,  9.26,  9.90,
75.45, 79.24,  9.22,  9.91,
79.24, 83.04,  9.19,  9.93,
83.04, 86.83,  9.15,  9.94,
86.83, 90.62,  9.11,  9.95,
90.62, 94.42,  9.07,  9.97,
94.42, 98.21,  9.07,  9.97,
98.21, 102.00,  9.07,  9.97,
102.00, 105.80,  9.09,  9.96,
105.80, 109.59,  9.10,  9.96,
109.59, 113.38,  9.10,  9.96,
113.38, 117.18,  9.11,  9.96,
117.18, 120.97,  9.11,  9.96
],
[
55.85, 60.13, 12.98,  6.03,
60.13, 64.40, 12.72,  6.55,
64.40, 68.67, 12.77,  6.45,
68.67, 72.94, 12.45,  7.09,
72.94, 77.22, 12.09,  7.81,
77.22, 81.49, 11.54,  8.93,
81.49, 85.76, 11.09,  9.82,
85.76, 90.04, 10.74, 10.51,
90.04, 94.31, 10.78, 10.44,
94.31, 98.58, 10.81, 10.37,
98.58, 102.86, 10.85, 10.30,
102.86, 107.13, 10.89, 10.23,
107.13, 111.40, 10.93, 10.14,
111.40, 115.67, 10.93, 10.15,
115.67, 119.95, 10.93, 10.15,
119.95, 124.22, 10.91, 10.18,
124.22, 128.49, 10.90, 10.21,
128.49, 132.77, 10.90, 10.20,
132.77, 137.04, 10.89, 10.22,
137.04, 141.31, 10.89, 10.21
]
);

 my $Nslit  = 30;
 my $Nblock  = 20;

 for(my $n=1; $n<=$Nplate; $n++){
  for(my $i=1; $i<=$Nslit; $i++){
    for(my $j=1; $j<=$Nblock; $j++){ 
	my $n_c     = cnumber($n-1, 1);
	my $i_c     = cnumber($i-1, 10);
	my $j_c     = cnumber($j-1, 10);

	$detector{"name"}        = "$DetectorName\_plate$n_c.slit$i_c.block$j_c";
	$detector{"mother"}      = "$DetectorMother";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "0*cm 0*cm $PlateZ[$n-1]*cm";
	$detector{"rotation"}    = "0*deg 0*deg 0*deg";
	$detector{"color"}       = "$color_baffle";
	$detector{"type"}        = "Tube";
	my $Rin  = $x[$n-1][($j-1)*4+0];
	my $Rout = $x[$n-1][($j-1)*4+1];
	my $Sphi = $x[$n-1][($j-1)*4+2]+($i-1)*12;
 	my $Dphi = $x[$n-1][($j-1)*4+3];
	    my $startphi = $Sphi + $Dphi;
	    my $stopphi  = $Sphi + 12;
	    my $phidiff  = $stopphi-$startphi;
	    $detector{"dimensions"}  = "$Rin*cm $Rout*cm $Dz*cm $startphi*deg $phidiff*deg";
# 	$detector{"dimensions"}  = "$Rin*cm $Rout*cm $Dz*cm $Sphi*deg $Dphi*deg";
	$detector{"material"}    = "$material_baffle";
	$detector{"mfield"}      = "no";
	$detector{"ncopy"}       = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "$sensitivity_baffle";
	$detector{"hit_type"}    = "$hit_baffle";
	my $id=0+$n*100000;
	$detector{"identifiers"} = "id manual $id";
	print_det(\%detector, $file);
     }
   }
 }
}
make_baffle_blocks();
