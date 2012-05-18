#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_solenoid';

my $envelope = "solid_$DetectorName";
my $file     = "solid_$DetectorName.txt";

my $rmin      = 1;
my $rmax      = 1000000;

my %detector = ();    # hash (map) that defines the gemc detector
$detector{"rmin"} = $rmin;
$detector{"rmax"} = $rmax;

use Getopt::Long;
use Math::Trig;

sub make_detector
{
 my $NUM  = 16;
 my @pos_Z = (-131.25,0,131.25,0,0,-224.26,321.51,437.76,0,0,0,0,0,0,0,0);
 my @name = ("UpstreamCoil","CentralCoil","DownstreamCoil","ReturnYoke1","ReturnYoke2","YokeEndPiecesDownstream","DownstreamTop","CalorimeterAreaLayers","UpstreamPoletip1","UpstreamPoletip2","NoseCone","DownstreamFrontMagneticPole","TopTriangle","UpstreamTop","CherenkovShield","UpstreamTargetShield");
 my @Rin = (154,154,154,225,180,95,286,110.5);
 my @Rout = (156,156,156,261,216,261,321,286);
 my @Dz   = (43.75,87.5,43.75,175.26,175.26,20,133.75,17.5);
 my $material_coil = "Aluminum";
 my $material_yoke = "Iron";
 my @color= ("ffffff","ffffff","ffffff","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF","F63BFF");
#  my @color= ("ffffff","ffffff","ffffff","F63B11","123456","324564","234556","765356","890876","654444","098578","857493","394865","4335fe","ba4356","acffee");
 my @type= ("Tube","Tube","Tube","Tube","Tube","Tube","Tube","Tube","Polycone","Polycone","Polycone","Polycone","Polycone","Polycone","Polycone","Polycone");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "root";
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $pos_Z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = $type[$n-1];
    if ($n<=8) {$detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";}
    if ($n==9) {$detector{"dimensions"} = "0*deg 360*deg 8 164.50*cm 149.00*cm 149.00*cm 149.00*cm 149.00*cm 149.00*cm 164.50*cm 180.00*cm 231.00*cm 240.996*cm 240.996*cm 246.00*cm 261.00*cm 261.00*cm 261.00*cm 261.00*cm -200.26*cm -191.93*cm -191.93*cm -187.76*cm -187.76*cm -183.59*cm -183.59*cm -175.26*cm";}
    if ($n==10) {$detector{"dimensions"} = "0*deg 360*deg 2 52.08*cm 69.89*cm 95.00*cm 95*cm -244.26*cm -204.26*cm";}
    if ($n==11) {$detector{"dimensions"} = "0*deg 360*deg 3 26.01*cm 26.01*cm 26.01*cm 43.09*cm 110.50*cm 110.50*cm 150.26*cm 420.26*cm 455.26*cm";}
    if ($n==12) {$detector{"dimensions"} = "0*deg 360*deg 8 164.50*cm 149.00*cm 149.00*cm 149.00*cm 149.00*cm 149.00*cm 164.50*cm 180.00*cm 231.00*cm 240.996*cm 240.996*cm 246.00*cm 261.00*cm 261.00*cm 261.00*cm 261.00*cm 200.26*cm 191.93*cm 191.93*cm 187.76*cm 187.76*cm 183.59*cm 183.59*cm 175.26*cm";}
    if ($n==13) {$detector{"dimensions"} = "0*deg 360*deg 2 261.00*cm 261.00*cm 261.00*cm 321.00*cm 87.76*cm 187.76*cm";}
    if ($n==14) {$detector{"dimensions"} = "0*deg 360*deg 4 261.00*cm 261.00*cm 261.00*cm 261.00*cm 261.00*cm 281.00*cm 281.00*cm 261.00*cm -244.26*cm -214.26*cm -154.26*cm -124.26*cm";}
    if ($n==15) {$detector{"dimensions"} = "0*deg 360*deg 4 286.00*cm 223.00*cm 223.00*cm 286.00*cm 286.00*cm 286.00*cm 286.00*cm 286.00*cm 250.00*cm 280.00*cm 283.00*cm 305.00*cm";}
    if ($n==16) {$detector{"dimensions"} = "0*deg 360*deg 3 27.59*cm 27.59*cm 52.08*cm 27.59*cm 45.20*cm 142.08*cm -309.26*cm -299.26*cm -244.26*cm";}
    if ($n<=3) {$detector{"material"} = $material_coil;}
    if ($n>3)  {$detector{"material"} = $material_yoke;}
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
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
make_detector();
	


