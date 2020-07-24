#!/usr/bin/perl -w
use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_SIDIS_ec_forwardangle_virtualplane';

my $DetectorMother="root";

my $z_shower 		= $parameters{"z_shower"};
my $Rmin 		= $parameters{"Rmin"}-5;
my $Rmax 		= $parameters{"Rmax"}+5;

sub solid_SIDIS_ec_forwardangle_virtualplane
{
make_front();
# make_middle();
# make_inner();
make_rear();
}

sub make_front
{
 my $z_vp = $z_shower-25;
 
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_front";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z_vp*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CC6633";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin*cm $Rmax*cm 0.001*cm 0*deg 360*deg";
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 $detector{"identifiers"} = "id manual 3110000";
 print_det(\%configuration, \%detector);
}

sub make_middle
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_middle";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 324.6*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CC6633";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin*cm $Rmax*cm 0.001*cm 0*deg 360*deg"; 
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 $detector{"identifiers"} = "id manual 3120000";
 print_det(\%configuration, \%detector);
}


sub make_inner
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_inner";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 350*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CC6633";
 $detector{"type"}        = "Cons";
  my $Rmin1 = 97;
  my $Rmax1 = 97.1;
  my $Rmin2 = 97;
  my $Rmax2 = 97.1;
  my $Dz    = 25;
  my $Sphi  = 0;
  my $Dphi  = 360;
 $detector{"dimensions"}  = "$Rmin1*cm $Rmax1*cm $Rmin2*cm $Rmax2*cm $Dz*cm $Sphi*deg $Dphi*deg";
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 $detector{"identifiers"} = "id manual 3130000";
 print_det(\%configuration, \%detector);
}

sub make_rear
{
 my $z_vp = $z_shower+25;
 
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_rear";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z_vp*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CC6633";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin*cm $Rmax*cm 0.001*cm 0*deg 360*deg";
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 $detector{"identifiers"} = "id manual 3140000";
 print_det(\%configuration, \%detector);
}
