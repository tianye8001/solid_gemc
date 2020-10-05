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
make_coil_yoke();
make_cryostat();
}

#build from Poisson input file CLEOv8.am, add/substract 0.01cm at various interface to avoid overlap 

sub make_coil_yoke
{
 my $NUM  = 15;
 my @name =
 ("InnerOctagon","OuterOctagon","SpacerBarUpstream","SpacerBarDownstream","Coil","UpstreamCoilCollar","UpstreamPlug","DownstreamCoilCollar","EndcapNoseCone","EndcapCylinder","Endplate1","Endplate2","ConePlate","EndcapInterface","CorretorRing");
 my $material_coil = "G4_Al";
 my $material_yoke = "G4_Fe";# "Iron";
 my $color_coil = "ff8000";
 my $color_yoke = "F63BFF";
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 0*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    if ($n==5) {$detector{"color"} = $color_coil;}
    else {$detector{"color"} = $color_yoke;}
    
# modeled after info in appendix of Jay Benesch's magnet model with "SoLID_2020.pdf" in 2020/03
# use cylinder to replace inner and outer octagon for simplicity
# geometry polycone defines number of counts with inner radius,outer radius,z position
# refer to http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomSolids.html#tessellated-solids

    $detector{"type"}       = "Polycone";
    if ($n==1) {$detector{"dimensions"} = "0*deg 360*deg 3*counts 191.075*cm 191.075*cm 191.075*cm 230.142*cm 230.142*cm 217.692*cm -266.7*cm 209.23*cm 224.79*cm";} # Inner Octagon 
    if ($n==2) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 239.763*cm 239.763*cm 278.832*cm 278.832*cm -266.7*cm 209.23*cm";} # Outer Octagon  
    if ($n==3) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 230.142*cm 230.142*cm 239.763*cm 239.763*cm -266.7*cm -241.2*cm";} # spacer bar upstream   
    if ($n==4) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 230.142*cm 230.142*cm 239.763*cm 239.763*cm 182.73*cm 209.23*cm";} # spacer bar downstream
    if ($n==5) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 151.7*cm 151.7*cm 154.9*cm 154.9*cm -173.75*cm 173.75*cm";} # Coil    
    if ($n==6) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 144.145*cm 144.145*cm 191.075*cm 191.075*cm -266.7*cm -189.23*cm";} # Upstream coil collar
    if ($n==7) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 38.94*cm 66.19*cm 144.145*cm 144.145*cm -266.7*cm -208.28*cm";} # Upstream plug
    if ($n==8) {$detector{"dimensions"} = "0*deg 360*deg 3*counts 144*cm 144*cm 164.447*cm 191.075*cm 191.075*cm 191.075*cm 189.23*cm 199.23*cm 224.79*cm";} # Downstream coil collar
    if ($n==9) {$detector{"dimensions"} = "0*deg 360*deg 4*counts 19*cm 19.85*cm 25.28*cm 35*cm 61*cm 68.759*cm 85*cm 85*cm 189.23*cm 210*cm 342.27*cm 579.12*cm";} # Endcap nose cone (including cone,zhiwen_taper,cylinderA)
    if ($n==10) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 270*cm 270*cm 286.51*cm 286.51*cm 209.23*cm 529.59*cm";} # endcap cylinder    
    if ($n==11) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 286.51*cm 286.51*cm 529.59*cm 546.1*cm";} # end plate1
    if ($n==12) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 286.51*cm 286.51*cm 546.1*cm 562.61*cm";} # end plate2
    if ($n==13) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 85*cm 85*cm 213.36*cm 196.85*cm 562.61*cm 579.12*cm";} # cone plate
    if ($n==14) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 278.832*cm 278.832*cm 286.51*cm 286.51*cm 183.83*cm 209.23*cm";} # endcap interface    
    if ($n==15) {$detector{"dimensions"} = "0*deg 360*deg 2*counts 50.8*cm 50.8*cm 51.435*cm 51.435*cm -278*cm -266.7*cm";} # corrector ring

    if ($n==5) {$detector{"material"} = $material_coil;}
    else {$detector{"material"} = $material_yoke;}
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
