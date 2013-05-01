#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_PVDIS_absorber_kill';

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

 my $material="Kryptonite";
 my $color="000000";

sub make_absorber_forwarangle
{
 my $z=96;

    $detector{"name"}        = "$DetectorName\_forwarangle";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color";
    $detector{"type"}       = "Cons";
    my $Rmin1 = 7;
    my $Rmax1 = 20;
    my $Rmin2 = 7;
    my $Rmax2 = 20;
    my $Dz    = 5;
    my $Sphi  = 0;
    my $Dphi  = 360;
    $detector{"dimensions"}  = "$Rmin1*cm $Rmax1*cm $Rmin2*cm $Rmax2*cm $Dz*cm $Sphi*deg $Dphi*deg";
    $detector{"material"}   = "$material";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "";
    $detector{"identifiers"} = "";
    print_det(\%detector, $file);
}
make_absorber_forwarangle();

# sub make_absorber_largeangle
# {
#  my $z=40;
# 
#     $detector{"name"}        = "$DetectorName\_largeangle";
#     $detector{"mother"}      = "$DetectorMother" ;
#     $detector{"description"} = $detector{"name"};
#     $detector{"pos"}        = "0*cm 0*cm $z*cm";
#     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
#     $detector{"color"}      = "$color";
#     $detector{"type"}       = "Cons";
#     my $Rmin1 = 43;
#     my $Rmax1 = 100;
#     my $Rmin2 = 43;
#     my $Rmax2 = 100;
#     my $Dz    = 1;
#     my $Sphi  = 0;
#     my $Dphi  = 360;
#     $detector{"dimensions"}  = "$Rmin1*cm $Rmax1*cm $Rmin2*cm $Rmax2*cm $Dz*cm $Sphi*deg $Dphi*deg";
#     $detector{"material"}   = "$material";
#     $detector{"mfield"}     = "no";
#     $detector{"ncopy"}      = 1;
#     $detector{"pMany"}       = 1;
#     $detector{"exist"}       = 1;
#     $detector{"visible"}     = 1;
#     $detector{"style"}       = 1;
#     $detector{"sensitivity"} = "no";
#     $detector{"hit_type"}    = "";
#     $detector{"identifiers"} = "";
#     print_det(\%detector, $file);
# }
# make_absorber_largeangle();
