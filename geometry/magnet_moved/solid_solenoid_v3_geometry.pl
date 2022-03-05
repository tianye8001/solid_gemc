#!/usr/bin/perl -w
use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_solenoid';

my $DetectorMother="root";

sub solid_solenoid
{
make_yoke();
make_coilcorr();
}

sub make_yoke
{
# modeled after info in appendix of Jay Benesch's magnet model with "SoLID_2020vs2022.pdf" in 2022/03

 my $NUM  = 14;
 my @name =
 ("InnerOctagon","OuterOctagon","SpacerBarUpstream","SpacerBarDownstream","UpstreamCoilCollar","UpstreamPlug","DownstreamCoilCollar","EndcapInterface","EndcapNoseCone","EndcapCylinder","Endplate1","Endplate2","ConePlate","CorretorRing");
 my $material_yoke = "G4_Fe";
 my $color_yoke = "F63BFF";
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 0*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    
    if ($n<=8) {$detector{"rotation"}   = "0*deg 0*deg 22.5*deg";}
    else  {$detector{"rotation"}   = "0*deg 0*deg 0*deg";}
    
    $detector{"color"} = $color_yoke;
    
    if ($n<=8) {$detector{"type"}       = "Pgon";}
    else  {$detector{"type"}       = "Polycone";}
    
    if ($n==1) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 3*counts 191.075*cm 191.075*cm 191.075*cm 230.142*cm 230.142*cm 217.692*cm -266.7*cm 209.23*cm 224.79*cm";} # Inner Octagon
    if ($n==2) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 239.763*cm 239.763*cm 278.832*cm 278.832*cm -266.7*cm 209.23*cm";} # Outer Octagon      
    if ($n==3) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 230.142*cm 230.142*cm 239.763*cm 239.763*cm -266.7*cm -241.2*cm";} # spacer bar upstream   
    if ($n==4) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 230.142*cm 230.142*cm 239.763*cm 239.763*cm 182.73*cm 209.23*cm";} # spacer bar downstream
    if ($n==5) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 144.145*cm 144.145*cm 191.075*cm 191.075*cm -266.7*cm -189.23*cm";} # Upstream coil collar
#     if ($n==6) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 38.94*cm 66.19*cm 144.145*cm 144.145*cm -266.7*cm -208.28*cm";} # Upstream plug
    if ($n==6) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 38.94*cm 66.19*cm 144.145*cm 144.145*cm -266.7*cm -214.276*cm";} # Upstream plug
    if ($n==7) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 3*counts 144*cm 144*cm 164.447*cm 191.075*cm 191.075*cm 191.075*cm 189.23*cm 199.23*cm 224.79*cm";} # Downstream coil collar
    if ($n==8) {$detector{"dimensions"} = "0*deg 360*deg 8*counts 2*counts 278.832*cm 278.832*cm 286.51*cm 286.51*cm 183.83*cm 209.23*cm";} # endcap interface

#     if ($n==9) {$detector{"dimensions"} = "0*deg 360*deg 4*counts 19*cm 19.85*cm 25.28*cm 35*cm 61*cm 68.759*cm 85*cm 85*cm 189.23*cm 210*cm 342.27*cm 579.12*cm";} # Endcap nose cone (including cone,zhiwen_taper,cylinderA)
    if ($n==9) {$detector{"dimensions"} = "0*deg 360*deg 3*counts 19*cm 28.31*cm 35*cm 59.16*cm 85*cm 85*cm 189.23*cm 416.04*cm 579.12*cm";} # Endcap nose cone (including cone,cylinderA)
    if ($n==10) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 270*cm 270*cm 286.51*cm 286.51*cm 209.23*cm 529.59*cm";} # endcap cylinder    
    if ($n==11) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 286.51*cm 286.51*cm 529.59*cm 546.1*cm";} # end plate1
    if ($n==12) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 286.51*cm 286.51*cm 546.1*cm 562.61*cm";} # end plate2
    if ($n==13) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 213.36*cm 196.85*cm 562.61*cm 579.12*cm";} # cone plate
    if ($n==14) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 50.8*cm 50.8*cm 51.435*cm 51.435*cm -278*cm -266.7*cm";} # corrector ring steel
    
    $detector{"material"} = $material_yoke;
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
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

sub make_coilcorr
{
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_coilcorr";
    $detector{"mother"}      = "$DetectorMother";
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 0*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "ff8011";
    $detector{"type"}       = "Polycone";
    $detector{"dimensions"} = "0*deg 360*deg 2*counts 40*cm 40*cm 49*cm 49*cm -277*cm -268*cm";
    $detector{"material"}   = "G4_Cu";
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
