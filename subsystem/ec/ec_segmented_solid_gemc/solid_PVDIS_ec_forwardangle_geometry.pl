use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_PVDIS_ec_forwardangle';

my $DetectorMother="root";

my $ec_sen="solid_ec";

my $color_abs="0000ff";
my $color_scint="f1ffe1";
my $color_gap="80ff77";
my $color_support="123456";
my $color_wrap_sectorodd="00ffff";
my $color_wrap_sectoreven="0000ff";

my $material_abs="G4_Pb";
my $material_scint="SL_ec_ScintillatorB";
my $material_gap="G4_MYLAR";
my $material_support="G4_Al";
my $material_wrap="G4_MYLAR";

# config mostly from CaloSim/include/Config.h
# Sampling ratio = 0.253017(EM) 0.285811(MIP) 0.34+-0.04(H)
# my $Nlayer=194;
# my $Thickness_lead = 0.05; #cm
# my $Thickness_scint = 0.15; #cm
# my $Thickness_gap = 0.024; #cm
# my $Thickness_shield = 0.5137*2; #cm, it should be 0.5612cm for X0
# my $Thickness_prescint = 2; #cm 
# my $Thickness_support = 2; #cm
# my $Thickness_preshower=$Thickness_shield+$Thickness_prescint; #3.0274mm
# my $z_shower=350;

#   my $Rmin = 110;
#   my $Rmax = 265;
#   my $Sphi  = 0;
#   my $Dphi  = 360;
  
my $Nlayer		= $parameters{"Nlayer"};
my $Thickness_lead	= $parameters{"Thickness_lead"};
my $Thickness_scint 	= $parameters{"Thickness_scint"};
my $Thickness_gap 	= $parameters{"Thickness_gap"};
my $Thickness_shield 	= $parameters{"Thickness_shield"};
my $Thickness_prescint 	= $parameters{"Thickness_prescint"};
my $Thickness_support 	= $parameters{"Thickness_support"};
my $Sidelength_shower 	= $parameters{"Sidelength_shower"};
my $z_shower 		= $parameters{"z_shower"};
my $Rmin 		= $parameters{"Rmin"};
my $Rmax 		= $parameters{"Rmax"};
my $Sphi 		= $parameters{"Sphi"};
my $Dphi 		= $parameters{"Dphi"};
my $total_module 	= $parameters{"total_module"};
my $total_module_active	= $parameters{"total_module_active"};

my @status;
my @idy;
my @idx;
my @y;
my @x;
my @sector;
for(my $i=1; $i<=$total_module; $i++)
{
  $status[$i-1] = $parameters{"id$i\_status"};
  $idy[$i-1] = $parameters{"id$i\_idy"};
  $idx[$i-1] = $parameters{"id$i\_idx"};
  $x[$i-1] = $parameters{"id$i\_y"};
  $y[$i-1] = $parameters{"id$i\_x"};  
  $sector[$i-1] = $parameters{"id$i\_sector"};
#   print "$idx[$i-1] \n";
}

my $Thickness_layer=$Thickness_lead+$Thickness_scint+$Thickness_gap; #0.224cm
my $Thickness_shower=$Thickness_layer*$Nlayer;  #43.456cm

my $z_support = $z_shower-$Thickness_shower/2-$Thickness_support/2;  #cm
my $z_prescint = $z_support-$Thickness_support/2-$Thickness_prescint/2; #cm 
my $z_shield = $z_prescint-$Thickness_prescint/2-$Thickness_shield/2;  #about 323.4cm


sub solid_PVDIS_ec_forwardangle
{
make_ec_shield();
make_ec_module();
}

sub make_ec_shield
{
 my $Dz    = $Thickness_shield/2;

 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_shield";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $z_shield*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "$color_abs";
 $detector{"type"}       = "Tube";
 $detector{"dimensions"} = "$Rmin*cm $Rmax*cm $Dz*cm $Sphi*deg $Dphi*deg";
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

sub make_ec_module
{   
#    for(my $i=1; $i<=30; $i++)   
   for(my $i=1; $i<=$total_module; $i++)   
    {    
      if($status[$i-1] eq 1) {
	  make_ec_module_shower($i);
	  make_ec_module_prescint($i);
	  make_ec_module_support($i);
      }
    }
}

sub make_ec_module_shower()
{   
    my $id = $_[0];
 
    my $Dr = $Sidelength_shower;
    my $Dr_wrap = $Sidelength_shower+0.2;        
    my $Dz_shower = $Thickness_shower/2;
    
    my %detector=init_det();
            
    $detector{"name"}        = "$DetectorName\_shower$id";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x[$id-1]*cm $y[$id-1]*cm $z_shower*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    if ($sector[$id-1]%2 eq 0) {$detector{"color"}      = $color_wrap_sectoreven;}
    else {$detector{"color"}      = $color_wrap_sectorodd;}
    $detector{"type"}       = "Pgon";
    $detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr_wrap*cm $Dr_wrap*cm -$Dz_shower*cm $Dz_shower*cm";
    $detector{"material"}   = "$material_wrap";
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
      
    my $Dz_layer = $Thickness_layer/2;        

        $detector{"name"}        = "$DetectorName\_shower$id\_layer";
        $detector{"mother"}      = "$DetectorName\_shower$id";
#         $detector{"description"} = $detector{"name"};
        $detector{"description"} = "Replica: 3*counts $Nlayer*counts $Thickness_layer*cm 0*mm";
#         $detector{"pos"}        = "0*cm 0*cm $layerZ*cm";
#         $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "$color_gap";
	$detector{"type"}       = "Pgon";
	$detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr*cm $Dr*cm -$Dz_layer*cm $Dz_layer*cm";
        $detector{"material"}   = "$material_gap";
#         $detector{"mfield"}     = "no";
#         $detector{"ncopy"}      = 1;
#         $detector{"pMany"}       = 1;
#         $detector{"exist"}       = 1;
# 	$detector{"visible"}     = 1;
# 	$detector{"style"}       = 1;
# 	$detector{"sensitivity"} = "no";
# 	$detector{"hit_type"}    = "no";
# 	$detector{"identifiers"} = "no";
	print_det(\%configuration, \%detector);
	
	my $leadZ = -$Dz_layer+$Thickness_lead/2;
	my $Dz_lead = $Thickness_lead/2;

        $detector{"name"}        = "$DetectorName\_shower$id\_lead";
        $detector{"mother"}      = "$DetectorName\_shower$id\_layer";
        $detector{"description"} = $detector{"name"};
        $detector{"pos"}        = "0*cm 0*cm $leadZ*cm";
        $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "$color_abs";
	$detector{"type"}       = "Pgon";
	$detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr*cm $Dr*cm -$Dz_lead*cm $Dz_lead*cm";
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

	my $scintZ = -$Dz_layer+$Thickness_lead+$Thickness_scint/2+$Thickness_gap/2;
	my $Dz_scint = $Thickness_scint/2;	

        $detector{"name"}        = "$DetectorName\_shower$id\_scint";
        $detector{"mother"}      = "$DetectorName\_shower$id\_layer";
        $detector{"description"} = $detector{"name"};
        $detector{"pos"}        = "0*cm 0*cm $scintZ*cm";
        $detector{"rotation"}   = "0*deg 0*deg 0*deg";
        $detector{"color"}      = "$color_scint";
	$detector{"type"}       = "Pgon";
	$detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr*cm $Dr*cm -$Dz_scint*cm $Dz_scint*cm";
        $detector{"material"}   = $material_scint;
        $detector{"mfield"}     = "no";
        $detector{"ncopy"}      = 1;
        $detector{"pMany"}       = 1;
        $detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = $ec_sen;
	$detector{"hit_type"}    = $ec_sen;
	my $ID = 3100000+$id;
	$detector{"identifiers"} = "id manual $ID";
	print_det(\%configuration, \%detector);  
}

sub make_ec_module_prescint()
{   
    my $id = $_[0];
 
    my $Dr = $Sidelength_shower;
    my $Dz_prescint = $Thickness_prescint/2;
    
    my %detector=init_det();
            
    $detector{"name"}        = "$DetectorName\_prescint$id";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x[$id-1]*cm $y[$id-1]*cm $z_prescint*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color_scint;
    $detector{"type"}       = "Pgon";
    $detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr*cm $Dr*cm -$Dz_prescint*cm $Dz_prescint*cm";
    $detector{"material"}   = "$material_scint";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
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

sub make_ec_module_support()
{   
    my $id = $_[0];
 
    my $Dr = $Sidelength_shower;
    my $Dz_support = $Thickness_support/2;
    
    my %detector=init_det();
            
    $detector{"name"}        = "$DetectorName\_support$id";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x[$id-1]*cm $y[$id-1]*cm $z_support*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color_support;
    $detector{"type"}       = "Pgon";
    $detector{"dimensions"} = "$Sphi*deg $Dphi*deg 6*counts 2*counts 0*cm 0*cm $Dr*cm $Dr*cm -$Dz_support*cm $Dz_support*cm";
    $detector{"material"}   = "$material_support";
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
