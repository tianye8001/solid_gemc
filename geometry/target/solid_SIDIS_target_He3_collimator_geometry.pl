use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_SIDIS_target_He3_collimator';

my $DetectorMother="root";

my $z_collimator_upstream	= -355;
my $z_collimator_downstream	= -315;

my $material_collimator = "SL_target_He3_TungstenPowder";

sub solid_SIDIS_target_He3_collimator
{
make_collimator_upstream();
make_collimator_downstream();
}


sub make_collimator_upstream
{
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_upstream";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z_collimator_upstream*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "003300";
    $detector{"type"}       = "Cons";
#     my $Rmin1 = 1.3;
#     my $Rmax1 = 2.7;
#     my $Rmin2 = 2.6;
#     my $Rmax2 = 5.4;
    my $Rmin1 = 1.85;
    my $Rmax1 = 4.00;
    my $Rmin2 = 3.05;
    my $Rmax2 = 6.70;
    my $Dz    = 5;
    my $Sphi  = 0;
    my $Dphi  = 360;
    $detector{"dimensions"}  = "$Rmin1*cm $Rmax1*cm $Rmin2*cm $Rmax2*cm $Dz*cm $Sphi*deg $Dphi*deg";
    $detector{"material"}   = "$material_collimator";
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

sub make_collimator_downstream
{
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_downstream";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z_collimator_downstream*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "003300";
    $detector{"type"}       = "Cons";
#     my $Rmin1 = 1.3;
#     my $Rmax1 = 2.7;
#     my $Rmin2 = 2.6;
#     my $Rmax2 = 5.4;
    my $Rmin1 = 1.85;
    my $Rmax1 = 4.00;
    my $Rmin2 = 3.05;
    my $Rmax2 = 6.70;
    my $Dz    = 5;
    my $Sphi  = 0;
    my $Dphi  = 360;
    $detector{"dimensions"}  = "$Rmin1*cm $Rmax1*cm $Rmin2*cm $Rmax2*cm $Dz*cm $Sphi*deg $Dphi*deg";
    $detector{"material"}   = "$material_collimator";
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
