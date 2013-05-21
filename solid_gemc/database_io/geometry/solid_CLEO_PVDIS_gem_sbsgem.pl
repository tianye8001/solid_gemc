#!/usr/bin/perl -w

#  * Describe the single GEM Chamber module (similar to COMPASS)
#  * see: "Construction Of GEM Detectors for the COMPASS experiment", CERN Tech Note TA1/00-03
#
#  This version allows one to specify how many sectors (default is 30,
#  and some SOLiD software assumes this), and variant materials
#  (including no material).

#  Usage: solid_gem.pl -nsectors=n -activeangle=a -material=m


use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $rmin      = 1;
my $rmax      = 1000000;

my %detector = ();    # hash (map) that defines the gemc detector
$detector{"rmin"} = $rmin;
$detector{"rmax"} = $rmax;

use Getopt::Long;
use Math::Trig;

my $DetectorMother="root";

sub make_gem
{
    my $argj = join " ", @ARGV;

    my $Nplate  = 4;
    my $NSECTORS = $argj =~ /-nsectors=([0-9]*)/ ? $1 : 30;   # how many sectors
    my $ACTIVEANGLE = $argj =~ /-activeangle=([0-9.]*)/ ? $1 : 360/$NSECTORS;   # active area degrees per sector
    my $HACTIVEANGLE = $ACTIVEANGLE * 0.5;
    my $MATERIAL = $argj =~ /-material=([0-9]*)/ ? $1 : 1;   # 0 for no material

    my $DetectorName = 'CLEO_PVDIS_gem_sbsgem';
    my $file     = "solid_$DetectorName";
    $file .= '_onesector' if $NSECTORS == 1;
    $file .= '_nomat' if $MATERIAL == 0;
    $file .= ".txt";

#    my @PlateZ  = (157,185,295,310);
#    my @Rin  = (55,65,105,115);
#    my @Rout = (115,140,200,215);
    my @PlateZ = (157.5,185.5,306,315);
    my @Rin = (48,59,105,109);
    my @Rout = (122,143,230,237);

#  * Consist of 23 layers of different size, material and position
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
#  * (19a   G10 120 um + 60 um (assume 60 um glue as G10)    # not implemented yet)
#  * Honeycomb
#  * 20   NEMA G10 120 um
#  * 21   NOMEX    3 mm       #should be 3um?
#  * 22   NEMA G10 120 um

    my $Nlayer = 23;
  # unit in mm
    my @layer_thickness = 
	(0.12,  #  HoneyComb NEMA G10 120 um
	 0.003,  #  HoneyComb NOMEX    3um
	 0.12,  #  HoneyComb NEMA G10 120 um
	 0.05,  #  Drift Cathode Kapton 50 um
	 0.005,  #  Drift Cathode Copper 5 um
	 3,  #  Drift Cathode Gas 3 mm
	 0.005,  #  GEM0 Copper 5 um
	 0.05,  #  GEM0 Kapton 50 um
	 0.005,  #  GEM0 Copper 5 um
	 2,  #  GEM0 Gas 2 mm
	 0.005,  #  GEM1 Copper 5 um
	 0.05,  #  GEM1 Kapton 50 um
	 0.005,  #  GEM1 Copper 5 um
	 2,  #  GEM1 Gas 2 mm
	 0.005,  #  GEM2 Copper 5 um
	 0.05,  #  GEM2 Kapton 50 um
	 0.005,  #  GEM2 Copper 5 um
	 2,  #  GEM2 Gas 2 mm 
	 0.01,  #  Readout Board Copper 10 um
	 0.05,  #  Readout Board Kapton 50 um
	 0.12,  #  Honeycomb NEMA G10 120 um
	 0.003,  #  Honeycomb NOMEX   3um
	 0.12);  #  Honeycomb NEMA G10 120 um

    # compute half total thickness of chamber
    my $Dz = 0;
    $Dz += $_/2 foreach (@layer_thickness);

    my @material = $MATERIAL == 0 ? 
	("Vacuum",  #  HoneyComb NEMA G10 120 um
	 "Vacuum",  #  HoneyComb NOMEX    3um
	 "Vacuum",  #  HoneyComb NEMA G10 120 um
	 "Vacuum",  #  Drift Cathode Kapton 50 um
	 "Vacuum",  #  Drift Cathode Copper 5 um
	 "Vacuum",  #  Drift Cathode Gas 3 mm
	 "Vacuum",  #  GEM0 Copper 5 um
	 "Vacuum",  #  GEM0 Kapton 50 um
	 "Vacuum",  #  GEM0 Copper 5 um
	 "Vacuum",  #  GEM0 Gas 2 mm
	 "Vacuum",  #  GEM1 Copper 5 um
	 "Vacuum",  #  GEM1 Kapton 50 um
	 "Vacuum",  #  GEM1 Copper 5 um
	 "Vacuum",  #  GEM1 Gas 2 mm
	 "Vacuum",  #  GEM2 Copper 5 um
	 "Vacuum",  #  GEM2 Kapton 50 um
	 "Vacuum",  #  GEM2 Copper 5 um
	 "Vacuum",  #  GEM2 Gas 2 mm 
	 "Vacuum",  #  Readout Board Copper 10 um
	 "Vacuum",  #  Readout Board Kapton 50 um
	 "Vacuum",  #  Honeycomb NEMA G10 120 um
	 "Vacuum",  #  Honeycomb NOMEX   3um
	 "Vacuum")  #  Honeycomb NEMA G10 120 um
	:
	("NEMAG10",  #  HoneyComb NEMA G10 120 um
	 "NOMEX",  #  HoneyComb NOMEX    3um
	 "NEMAG10",  #  HoneyComb NEMA G10 120 um
	 "Kapton",  #  Drift Cathode Kapton 50 um
	 "Copper",  #  Drift Cathode Copper 5 um
	 "GEMgas",  #  Drift Cathode Gas 3 mm
	 "Copper",  #  GEM0 Copper 5 um
	 "Kapton",  #  GEM0 Kapton 50 um
	 "Copper",  #  GEM0 Copper 5 um
	 "GEMgas",  #  GEM0 Gas 2 mm
	 "Copper",  #  GEM1 Copper 5 um
	 "Kapton",  #  GEM1 Kapton 50 um
	 "Copper",  #  GEM1 Copper 5 um
	 "GEMgas",  #  GEM1 Gas 2 mm
	 "Copper",  #  GEM2 Copper 5 um
	 "Kapton",  #  GEM2 Kapton 50 um
	 "Copper",  #  GEM2 Copper 5 um
	 "GEMgas",  #  GEM2 Gas 2 mm 
	 "Copper",  #  Readout Board Copper 10 um
	 "Kapton",  #  Readout Board Kapton 50 um
	 "NEMAG10",  #  Honeycomb NEMA G10 120 um
	 "NOMEX",  #  Honeycomb NOMEX   3um
	 "NEMAG10");  #  Honeycomb NEMA G10 120 um
    my @sens = 
	("no",  #  HoneyComb NEMA G10 120 um
	 "no",  #  HoneyComb NOMEX    3um
	 "no",  #  HoneyComb NEMA G10 120 um
	 "no",  #  Drift Cathode Kapton 50 um
	 "SBSGEM",  #  Drift Cathode Copper 5 um
	 "SBSGEM",  #  Drift Cathode Gas 3 mm
	 "SBSGEM",  #  GEM0 Copper 5 um
	 "no",  #  GEM0 Kapton 50 um
	 "no",  #  GEM0 Copper 5 um
	 "no",  #  GEM0 Gas 2 mm
	 "no",  #  GEM1 Copper 5 um
	 "no",  #  GEM1 Kapton 50 um
	 "no",  #  GEM1 Copper 5 um
	 "no",  #  GEM1 Gas 2 mm
	 "no",  #  GEM2 Copper 5 um
	 "no",  #  GEM2 Kapton 50 um
	 "no",  #  GEM2 Copper 5 um
	 "no",  #  GEM2 Gas 2 mm 
	 "SBSGEM",  #  Readout Board Copper 10 um
	 "no",  #  Readout Board Kapton 50 um
	 "no",  #  Honeycomb NEMA G10 120 um
	 "no",  #  Honeycomb NOMEX   3um
	 "no");  #  Honeycomb NEMA G10 120 um
    my @hitt = 
	("",  #  HoneyComb NEMA G10 120 um
	 "",  #  HoneyComb NOMEX    3um
	 "",  #  HoneyComb NEMA G10 120 um
	 "",  #  Drift Cathode Kapton 50 um
	 "SBSGEM",  #  Drift Cathode Copper 5 um
	 "SBSGEM",  #  Drift Cathode Gas 3 mm
	 "SBSGEM",  #  GEM0 Copper 5 um
	 "",  #  GEM0 Kapton 50 um
	 "",  #  GEM0 Copper 5 um
	 "",  #  GEM0 Gas 2 mm
	 "",  #  GEM1 Copper 5 um
	 "",  #  GEM1 Kapton 50 um
	 "",  #  GEM1 Copper 5 um
	 "",  #  GEM1 Gas 2 mm
	 "",  #  GEM2 Copper 5 um
	 "",  #  GEM2 Kapton 50 um
	 "",  #  GEM2 Copper 5 um
	 "",  #  GEM2 Gas 2 mm 
	 "SBSGEM",  #  Readout Board Copper 10 um
	 "",  #  Readout Board Kapton 50 um
	 "",  #  Honeycomb NEMA G10 120 um
	 "",  #  Honeycomb NOMEX   3um
	 "");  #  Honeycomb NEMA G10 120 um
    my $color_NEMAG10 = "00ff00";
    my $color_NOMEX = "ffse14";
    my $color_Copper = "ffe731";
    my $color_Kapton = "1a4fff";
    my $color_Air = "ff33fc";
    my @color = 
	($color_NEMAG10,  #  HoneyComb NEMA G10 120 um
	 $color_NOMEX,  #  HoneyComb NOMEX    3um
	 $color_NEMAG10,  #  HoneyComb NEMA G10 120 um
	 $color_Kapton,  #  Drift Cathode Kapton 50 um
	 $color_Copper,  #  Drift Cathode Copper 5 um
	 $color_Air,  #  Drift Cathode Gas 3 mm
	 $color_Copper,  #  GEM0 Copper 5 um
	 $color_Kapton,  #  GEM0 Kapton 50 um
	 $color_Copper,  #  GEM0 Copper 5 um
	 $color_Air,  #  GEM0 Gas 2 mm
	 $color_Copper,  #  GEM1 Copper 5 um
	 $color_Kapton,  #  GEM1 Kapton 50 um
	 $color_Copper,  #  GEM1 Copper 5 um
	 $color_Air,  #  GEM1 Gas 2 mm
	 $color_Copper,  #  GEM2 Copper 5 um
	 $color_Kapton,  #  GEM2 Kapton 50 um
	 $color_Copper,  #  GEM2 Copper 5 um
	 $color_Air,  #  GEM2 Gas 2 mm 
	 $color_Copper,  #  Readout Board Copper 10 um
	 $color_Kapton,  #  Readout Board Kapton 50 um
	 $color_NEMAG10,  #  Honeycomb NEMA G10 120 um
	 $color_NOMEX,  #  Honeycomb NOMEX   3um
	 $color_NEMAG10);  #  Honeycomb NEMA G10 120 um

    for(my $n=1; $n<=$Nplate; $n++)
    {
	$detector{"name"}        = "$DetectorName\_$n";
	$detector{"mother"}      = "$DetectorMother" ;
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
	$detector{"rotation"}   = "0*deg 0*deg 0*deg";
	$detector{"color"}      = "111111";
	$detector{"type"}       = "Tube";
	$detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*mm 0*deg 360*deg";
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
	    
	    for( my $sec = 0; $sec < $NSECTORS; $sec++ ){
		my $thisrot = -$sec*360.0/$NSECTORS;
		
		$detector{"name"}        = "$DetectorName\_$n\_$i\_$sec";
		$detector{"mother"}      = "$DetectorName\_$n";
		$detector{"description"} = $detector{"name"};
		$detector{"pos"}        = "0*cm 0*cm $layerZ*mm";
		$detector{"rotation"}   = "0*deg 0*deg $thisrot*deg";
		$detector{"color"}      = "$color[$i-1]";
		$detector{"type"}       = "Tube";
		$detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $DlayerZ*mm -$HACTIVEANGLE*deg $ACTIVEANGLE*deg";
		$detector{"material"}   = "$material[$i-1]";
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "$sens[$i-1]";
		$detector{"hit_type"}    = "$hitt[$i-1]";
		my $id=(($n-1)*$NSECTORS + $sec + 1 )*100+$i;
		$detector{"identifiers"} = "id manual $id";
		print_det(\%detector, $file);
	    }
	}
    }
}
make_gem();
