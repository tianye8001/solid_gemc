#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_PVDIS_baffle_observer';

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

#baffle observer at PVDIS forward angle EC entrance

my $targetoff=10;

sub make_baffle_observer
{
#  my $Nplate  = 6;
#  my @PlateZ  = (40,68,96,124,152,180);
#  my @PlateZ  = (35.5,63.5,91.5,119.5,147.5,175.5);
#  my @PlateZ  = (35.48,63.48,91.48,119.48,147.48,175.48);
#  my @PlateZ  = (44.52,72.52,100.52,128.52,156.52,184.52);
my $Nplate  = 22;
my @PlateZ  = (30+$targetoff-4.5-0.1,44+$targetoff-4.5-0.1,58+$targetoff-4.5-0.1,72+$targetoff-4.5-0.1,86+$targetoff-4.5-0.1,100+$targetoff-4.5-0.1,114+$targetoff-4.5-0.1,128+$targetoff-4.5-0.1,142+$targetoff-4.5-0.1,156+$targetoff-4.5-0.1,170+$targetoff-4.5-0.1,
30+$targetoff+4.5+0.1,44+$targetoff+4.5+0.1,58+$targetoff+4.5+0.1,72+$targetoff+4.5+0.1,86+$targetoff+4.5+0.1,100+$targetoff+4.5+0.1,114+$targetoff+4.5+0.1,128+$targetoff+4.5+0.1,142+$targetoff+4.5+0.1,156+$targetoff+4.5+0.1,170+$targetoff+4.5+0.1
);
#  my @Rin = (0);
#  my @Rout = (145);
 my $Dz   = 0.001;

 for(my $n=1; $n<=$Nplate; $n++)
 {
    $detector{"name"}        = "$DetectorName\_plate_observer_$n";
    $detector{"mother"}      = "$DetectorMother";
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "ff0000";
    $detector{"type"}       = "Tube";
#     $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"dimensions"} = "0*cm 145*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "Vacuum";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0;
    $detector{"sensitivity"} = "FLUX";
    $detector{"hit_type"}    = "FLUX";
#     my $id=0+$n*100000+10000;
    my $id=$n;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%detector, $file);
 }
}
make_baffle_observer();
