#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'gem';

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

#  * Describe the single GEM Chamber module (similar to COMPASS)
#  * see: "Construction Of GEM Detectors for the COMPASS experiment", CERN Tech Note TA1/00-03
#  *
#  * Consist of 15 layers of different size, material and position
#  *
#  *
#  * HoneyComb
#  *  0   NEMA G10 120 um
#  *  1   NOMEX    3 mm  #should be 3um?
#  *  2   NEMA G10 120 um
#  * Drift Cathode
#  *  3   Copper 5 um    #should exchange with 4?
#  *  4   Kapton 50 um   #should exchange with 3?
#  *  5   Air 3 mm
#  * GEM0
#  *  6   Copper 5 um
#  *  7   Kapton 50 um
#  *  8   Copper 5 um
#  *  9   Air 2 mm
#  * GEM1
#  * 10   Copper 5 um
#  * 11   Kapton 50 um
#  * 12   Copper 5 um
#  * 13   Air 2 mm
#  * GEM2
#  * 14   Copper 5 um
#  * 15   Kapton 50 um
#  * 16   Copper 5 um
#  * 17   Air 2 mm 
#  * Readout Board
#  * 18   Copper 10 um
#  * 19   Kapton 50 um
#  * 20   G10 120 um + 60 um (assume 60 um glue as G10)    # not implmented yet
#  * Honeycomb
#  * 21   NEMA G10 120 um
#  * 22   NOMEX    3 mm       #should be 3um?
#  * 23   NEMA G10 120 um

sub make_gem
{

 my $Nplate  = 4;
#  my @PlateZ  = (155,185,295,310);
 my @PlateZ  = (155,185,306,321);
 my @Rin  = (55,65,105,115);
 my @Rout = (115,140,200,215);
#  my $Dz   = 0.48;
#  my $material="DCgas";
#  my $color="44ee11";

# total thickness
#  my $Dz   = 15.955/2;
my $Dz   = 9.781/2; 
#  my $material="DCgas";
#  my $color="44ee11";

 my $Nlayer = 23;
  # unit in mm
 my @layer_thickness = (0.12,0.003,0.12,0.05,0.005,3,0.005,0.05,0.005,2,0.005,0.05,0.005,2,0.005,0.05,0.005,2,0.01,0.05,0.12,0.003,0.12);
#  my @material = ("Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum","Vacuum");
 my @material = ("NEMAG10","NOMEX","NEMAG10","Kapton","Copper","GEMgas","Copper","Kapton","Copper","GEMgas","Copper","Kapton","Copper","GEMgas","Copper","Kapton","Copper","GEMgas","Copper","Kapton","NEMAG10","NOMEX","NEMAG10");
 my @sens = ("no","no","no","no","no","SBSGEM","no","no","no","no","no","no","no","no","no","no","no","no","SBSGEM","no","no","no","no");
 my @hitt = ("","","","","","SBSGEM","","","","","","","","","","","","","SBSGEM","","","","");
 my $color_NEMAG10 = "00ff00";
 my $color_NOMEX = "ffse14";
 my $color_Copper = "ffe731";
 my $color_Kapton = "1a4fff";
 my $color_Air = "ff33fc";
 my @color = ($color_NEMAG10,$color_NOMEX,$color_NEMAG10,$color_Kapton,$color_Copper,$color_Air,$color_Copper,$color_Kapton,$color_Copper,$color_Air,$color_Copper,$color_Kapton,$color_Copper,$color_Air,$color_Copper,$color_Kapton,$color_Copper,$color_Air,$color_Copper,$color_Kapton,$color_NEMAG10,$color_NOMEX,$color_NEMAG10);
#  my @color =  ("44ee11","44ee23","45ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11","44ee11");

 for(my $n=1; $n<=$Nplate; $n++)
 {
    $detector{"name"}        = "$DetectorName\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "111111";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*mm -6*deg 12*deg";
    $detector{"material"}   = "Vacuum";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "";
    my $id=1000000+$n*100000;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%detector, $file);

    for(my $i=1; $i<=$Nlayer; $i++)
    {
	my $layerZ = -$Dz;
	for(my $k=1; $k<=$i-1; $k++)
	{	
	   $layerZ = $layerZ+$layer_thickness[$k-1];
	}
	$layerZ = $layerZ+$layer_thickness[$i-1]/2;
	
	my $DlayerZ=$layer_thickness[$i-1]/2;

	$detector{"name"}        = "$DetectorName\_$n\_$i";
	$detector{"mother"}      = "$DetectorName\_$n";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}        = "0*cm 0*cm $layerZ*mm";
	$detector{"rotation"}   = "0*deg 0*deg 0*deg";
	$detector{"color"}      = "$color[$i-1]";
	$detector{"type"}       = "Tube";
	$detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $DlayerZ*mm -6*deg 12*deg";
	$detector{"material"}   = "$material[$i-1]";
	$detector{"mfield"}     = "no";
	$detector{"ncopy"}      = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
#	$detector{"sensitivity"} = "FLUX";
#	$detector{"hit_type"}    = "FLUX";

	$detector{"sensitivity"} = "$sens[$i-1]";
	$detector{"hit_type"}    = "$hitt[$i-1]";
	my $id=$n*100+$i;
	$detector{"identifiers"} = "id manual $id";
	print_det(\%detector, $file);
    }
 }
}
make_gem();