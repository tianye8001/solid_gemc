#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_PVDIS_virtualhodoscope_gem';

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
sub make_virtualhodoscope_gem
{
#  my $Nplate  = 4;
# my @PlateZ  = (155,185,295,310);  # as on p56 of pac34 proposal
# my @PlateZ  = (157.5,185.5,297,306); # as in Eugen's code
#  my @PlateZ  = (157.5,185.5,306,321);  # change for last two planes further back as Cherenkov needs 10cm more
#  my @Rin  = (55,65,105,115);
#  my @Rout = (115,140,200,215);
#  my @PlateZ = (157.5,185.5,306,315);
 my $Nplate  = 5;
 my @PlateZ = (156.8,184.8,188.8,305,314);

#cover target center at 10cm from 21 to 36 degree
#  my @Rin = (56,67,113,117);
#  my @Rout = (108,129,215,222);
#  my $Dz   = 0.5;
#cover 40cm long full target with center at 10cm from 21 to 36 degree
#  my @Rin = (48,59,105,109);
#  my @Rout = (122,143,230,237);
 my @Rin = (45,55,63,90,90);
 my @Rout = (144,144,144,270,270);
 my $Dz   = 0.001/2; 
 my $color="44ee11";

 for(my $n=1; $n<=$Nplate; $n++)
 {
    $detector{"name"}        = "$DetectorName\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "111111";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "Vacuum";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0;
    $detector{"sensitivity"} = "FLUX";
    $detector{"hit_type"}    = "FLUX";
    my $id=1000000+$n*100000+10000;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%detector, $file);
 }
}
make_virtualhodoscope_gem();