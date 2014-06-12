use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_PVDIS_ec_forwardangle_real';

my $DetectorMother="root";

sub solid_PVDIS_ec_forwardangle_real
{
make_ec_forwardangle_shower();
make_ec_forwardangle_shield();
make_ec_forwardangle_preshower();
}

my $ec_sen="flux";

 my $color="0000ff";
 my $material_abs="Lead";

# Sampling ratio = 0.253017(EM) 0.285811(MIP) 0.34+-0.04(H)
my $Nlayer=193;
# my $Nlayer=193;
my $LeadThick = 0.05; #cm
my $ScintThick = 0.15; #cm
my $GapThick = 0.024; #cm
my $LayerThick=$LeadThick+$ScintThick+$GapThick; #0.224cm
my $ShowerThick=$LayerThick*$Nlayer;  #43.425cm
my $leading_Pb = 0.5137*2; #cm, it should be 0.5612cm for X0
my $leading_Scint = 2; #cm 
my $PSThick=$leading_Pb+$leading_Scint; #3.0274mm

my $Dzlayer = $LayerThick/2;
my $Dzlead = $LeadThick/2;
my $Dzscint = $ScintThick/2;

  my $Rmin = 110;
  my $Rmax = 265;
  my $Sphi  = 0;
  my $Dphi  = 360;

sub make_ec_forwardangle_shower
{
    my $z=350;
    my $Dz = $ShowerThick/2;

    my %detector=init_det();
    $detector{"name"}        = "$DetectorName";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color;
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "Vacuum";
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

   for(my $i=1; $i<=$Nlayer; $i++)
    {
        my $layerZ = -$Dz+$LayerThick*($i-0.5);

        my %detector=init_det();
        $detector{"name"}        = "$DetectorName\_layer_$i";
        $detector{"mother"}      = "$DetectorName";
        $detector{"description"} = $detector{"name"};
        $detector{"pos"}        = "0*cm 0*cm $layerZ*cm";
        $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "000000";
        $detector{"type"}       = "Tube";
        $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dzlayer*cm 0*deg 360*deg";
        $detector{"material"}   = "Air";
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

   for(my $i=1; $i<=$Nlayer; $i++)
    {
	my $leadZ = -$Dzlayer+$LeadThick/2;

        my %detector=init_det();
        $detector{"name"}        = "$DetectorName\_lead_$i";
        $detector{"mother"}      = "$DetectorName\_layer_$i";
        $detector{"description"} = $detector{"name"};
        $detector{"pos"}        = "0*cm 0*cm $leadZ*cm";
        $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "ff00ff";
        $detector{"type"}       = "Tube";
        $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dzlead*cm 0*deg 360*deg";
        $detector{"material"}   = $material_abs;
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

   for(my $i=1; $i<=$Nlayer; $i++)
    {
	my $scintZ = -$Dzlayer+$LeadThick+$ScintThick/2;

        my %detector=init_det();
        $detector{"name"}        = "$DetectorName\_scint_$i";
        $detector{"mother"}      = "$DetectorName\_layer_$i";
        $detector{"description"} = $detector{"name"};
        $detector{"pos"}        = "0*cm 0*cm $scintZ*cm";
        $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "ff0000";
        $detector{"type"}       = "Tube";
        $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dzscint*cm 0*deg 360*deg";
        $detector{"material"}   = "ScintillatorB";
        $detector{"mfield"}     = "no";
        $detector{"ncopy"}      = 1;
        $detector{"pMany"}       = 1;
        $detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = $ec_sen;
	$detector{"hit_type"}    = $ec_sen;
	my $ID = 3100000+$i;
# 	my $ID = 3100001;
	$detector{"identifiers"} = "id manual $ID";
	print_det(\%configuration, \%detector);
    }

}

sub make_ec_forwardangle_shield
{
 my $z = 324.4; #cm
 my $Dz    = $leading_Pb/2;

 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_shield";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "ff00ff";
 $detector{"type"}       = "Tube";
 $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dz*cm 0*deg 360*deg";
 $detector{"material"}    = $material_abs;
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 1;
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "no";
 $detector{"identifiers"} = "no";
 print_det(\%configuration, \%detector);
}

sub make_ec_forwardangle_preshower
{
 my $z = 326; #cm
 my $Dz    = $leading_Scint/2;

 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_scint_0";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "ff0000"; 
 $detector{"type"}       = "Tube";
 $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dz*cm 0*deg 360*deg";
 $detector{"material"}    = "ScintillatorB";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 1;
 $detector{"sensitivity"} = $ec_sen;
 $detector{"hit_type"}    = $ec_sen;
 my $ID = 3100000;
 $detector{"identifiers"} = "id manual $ID";
 print_det(\%configuration, \%detector);
}

