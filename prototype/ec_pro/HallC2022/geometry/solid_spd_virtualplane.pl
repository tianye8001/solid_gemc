#!/usr/bin/perl -w
# use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_spd';

# my $DetectorMother="root";
my $DetectorMother="cc_pro_tcd";
my $sc1_x_hlfln = 14./2;  
my $sc1_y_hlfln = 40./2;  
my $sc2_x_hlfln = 14./2;
my $sc2_y_hlfln = 40./2;
my $sc_z_hlfln = 5./2;
my $z1 = -56*2.54/2-6.5-5./2-3;
my $z2 =  56*2.54/2+4.5+1.5+14.7+5./2-3;  

my $spd1_x_hlfln = 10./2;  
my $spd1_y_hlfln = 25./2;  
my $spd2_x_hlfln = 14./2;
my $spd2_y_hlfln = 40./2;
my $spd1_z_hlfln = 0.6/2;
my $spd2_z_hlfln = 2./2;

my $z3 = 56*2.54/2+4.5+1.5+14.7+5.+2+0.6/2-1;
my $z4 = 56*2.54/2+4.5+1.5+14.7+5.+2+0.6+1.5+2./2-1.5;  


sub solid_spd_virtualplane
{
make_1();
make_2();
make_3();
make_4();
}

sub make_1
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_virtualplane_1";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z1*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "00ffff";
 $detector{"type"}       = "Box";
 $detector{"dimensions"} = "$sc1_x_hlfln*cm $sc1_y_hlfln*cm 0.0001*cm";	    
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 my $ID = 1;
 $detector{"identifiers"} = "id manual $ID";
 print_det(\%configuration, \%detector);
}

sub make_2
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_virtualplane_2";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z2*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "00ffff";
 $detector{"type"}       = "Box";
 $detector{"dimensions"} = "$sc2_x_hlfln*cm $sc2_y_hlfln*cm 0.0001*cm";	    
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 my $ID = 2;
 $detector{"identifiers"} = "id manual $ID";
 print_det(\%configuration, \%detector);
}

sub make_3
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_virtualplane_3";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z3*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "00ffff";
 $detector{"type"}       = "Box";
 $detector{"dimensions"} = "$spd1_x_hlfln*cm $spd1_y_hlfln*cm 0.0001*cm";	    
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 my $ID = 7;
 $detector{"identifiers"} = "id manual $ID";
 print_det(\%configuration, \%detector);
}
sub make_4
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_virtualplane_4";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z4*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "00ffff";
 $detector{"type"}       = "Box";
 $detector{"dimensions"} = "$spd2_x_hlfln*cm $spd2_y_hlfln*cm 0.0001*cm";	    
 $detector{"material"}    = "G4_Galactic";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "flux";
 $detector{"hit_type"}    = "flux";
 my $ID = 8;
 $detector{"identifiers"} = "id manual $ID";
 print_det(\%configuration, \%detector);
}
solid_spd_virtualplane();
1;
