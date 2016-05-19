#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'CLEO_PVDIS_ec_forwardangle_block_0p55x5deg_kill';

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

my $material="Kryptonite";

sub make_ec_forwardangle_block
{
 for(my $n=1; $n<=30; $n++)
 {
  for(my $m=1; $m<=10; $m++)
  {
    $detector{"name"}        = "$DetectorName\_$n\_$m";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 315*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color_baffle";
    $detector{"type"}       = "Tube";
#     my $phi_s=($n-1)*12+2.2;
#     $detector{"dimensions"} = "110*cm 200*cm 2.5*cm $phi_s*deg 2.5*deg";
    my $phi_s=($n-1)*12+2.8+($m-1)*(6.5-2.8)/9.;
    my $phi_e=($n-1)*12+7.2+($m-1)*(8.0-7.2)/9.;
    my $phi = $phi_e - $phi_s;
    my $rin  =105+($m-1)*10;
    my $rout =$rin+10;
    $detector{"dimensions"} = "$rin*cm $rout*cm 2.5*cm $phi_s*deg $phi*deg";
#     $detector{"dimensions"} = "105*cm 200*cm 2.5*cm $phi_s*deg 6*deg";
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
 }
}
make_ec_forwardangle_block();
