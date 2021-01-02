#!/usr/bin/perl -w
use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_solenoid_cryo';

my $DetectorMother="root";

sub solid_solenoid_cryo
{
make_cryostat();
}

# from CLEO-II NIM paper "The cryostat consists of a 12 mm thick outer cylinder, a 10 mm inner cylinder and two 20 mm thick end flanges which are bolted and sealed with O-rings."

sub make_cryostat
{
 my $Nplate  = 4;
 my @PlateZ  = (0, 0, -(189.00-1),189.00-1);
 my @Rin  = (144.00,176.60-0.12,144.00,144.00);
 my @Rout = (144.00+0.10,176.60-0.01,176.60-0.01,176.60-0.01);
 my @Dz   = ((189*2-2-2)/2,(189*2-2-2)/2,2/2-0.005,2/2-0.005);
 my @name = ("CryostatInner","CryostatOuter","CryostatFlangeUpstream","CryostatFlangeDownstream");
 my $material="SL_StainlessSteel";
 my $color="ffffff";

 for(my $n=1; $n<=$Nplate; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "$color";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = "$material";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }
}
