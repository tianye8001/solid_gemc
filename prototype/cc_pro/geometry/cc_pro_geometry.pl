use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;
use Getopt::Long;
use Math::Trig;
use Math::VectorReal;  

my $DetectorName = 'cc_pro';
my $DetectorMother="root";

sub cc_pro_geometry
{
make_tcd();
make_chamber();
make_gas();
make_window_front();
make_window_back();
make_mirror();
make_pmt();
make_scplane_front();
make_scplane_back();
make_ec();
}

# N.B.
## 1. All the lengths are in centimeters

# Constants
my $DEG=180/3.1415926;  # conversion factor between degrees and radians

# Parameters
## Chamber
my $AngY_tcd=-74.55;  #angle from the upstream beamline to the Cherenkov is about 105.45 with a hard to estimate error, only left side of beam direction
# my $AngY_tcd=3.5; #angle from downstream beamline, only right side of beam direction
# my $AngY_tcd=0.0;

my $AngX_chamber=0; # local angle of chamber
# my $AngX_chamber=-0.5; # local angle of chamber
my $AngY_chamber=-74.55;
# my $AngY_chamber=3.5; #local angle of chamber

# measurement done at front scintilator plane ($sc1_r) which is 5" before chamber front window
# 17 feet 10 inch (543.6cm) to pivot at large angle, 39 feet (1189cm) to pivot at small angle, by Jack Seagal
my $rmin_chamber=543.6+5*2.54;  # z position of the chamber entrance at large angle
# my $rmin_chamber=1189+5*2.54;  # z position of the chamber entrance at small angle

my $halflength_chamber_l = 60*2.54/2;
my $rmax_chamber=$rmin_chamber+$halflength_chamber_l*2;  # z position of the chamber exit
my $r_chamber=$rmin_chamber+$halflength_chamber_l;

my $x_chamber = sin(-$AngY_tcd/$DEG)*$r_chamber;
my $y_chamber = 0.0;
my $z_chamber = cos($AngY_tcd/$DEG)*$r_chamber;

my $Rmin_chamber=0;  # inner radius of the chamber
my $Rmax_chamber=14/2*2.54;  # outer radius of the chamber, 14 inch diameter

## Gas
my $Rmin_gas=0;  # inner radius of the gas
my $Rmax_gas=12.25/2*2.54;  # outer radius of the gas, 12.25 inch diameter

## Windows
my $halfthickness_window_front=0.005/2*2.54;  # half thickness of the front window, 0.005 inch 
my $halfthickness_window_back=0.75/2*2.54;  #PVC thickness is 3/4 inch

my $Z_window_front=-$halflength_chamber_l+$halfthickness_window_front;
my $Z_window_back=$halflength_chamber_l-$halfthickness_window_back;
my $Rmin_window_front=$Rmin_gas;  # inner radius of the front windows
my $Rmax_window_front=$Rmax_gas;  # outer radius of the front windows
my $Rmin_window_back=$Rmin_gas;  # inner radius of the back windows
my $Rmax_window_back=$Rmax_gas;  # outer radius of the back windows

# my $r_window_front=$rmin_chamber+$halfthickness_window_front;  # r position of the front window
# my $r_window_back=$rmax_chamber-$halfthickness_window_back;   # r position of the back window

## Gas Cont.
my $rmin_gas=$rmin_chamber+$halfthickness_window_front*2;  # z position of the gas at the upstream side
my $rmax_gas=$rmax_chamber-$halfthickness_window_back*2;  # z position of the gas at the downstream side

## Mirror
my $mirror_Rmin=0;
my $mirror_Rmax=$Rmax_gas;
my $mirror_halfthickness=0.005;
my $mirror_d=40*2.54-$halflength_chamber_l;  # mirror at 40" front the chamber front window
# my $mirror_R=$Rmin_chamber+$mirror_d;

## PMT
# my $PMT_y = 15/2*2.54;
# my $PMT_y = 47;
my $PMT_y = 22.75*2.54;  # 22.75" according to Ed Kaczanowicz from Temple
my $half_width = 10.65;  # half width of the PMT
my $windowhalf_z = 0.1;  # half thickness of the front side of PMT
my $backendhalf_z = 0.1;   # half thickness of the back side of PMT
my $half_z = $windowhalf_z + $backendhalf_z;  # total half length of the PMT

# my $halflength_chamber_t = ($PMT_y-14/2)*2.54;
# my $halflength_chamber_t = $PMT_y-$Rmax1_chamber;
my $halflength_chamber_t = $PMT_y;

 
## Scintillators:
my $sc1_x_hlfln = 8/2*2.54;  
my $sc1_y_hlfln = 22/2*2.54;  
my $sc2_x_hlfln = 8/2*2.54;
my $sc2_y_hlfln = 22/2*2.54;
my $sc_z_hlfln = 0.25/2*2.54;

# my $sc1_r = $r_window_front - 5*2.54; #5inch before front window
# my $sc2_r = $r_window_back + 5*2.54; #5inch behind back window
# my $sc1x = sin(-$AngY_tcd/$DEG)*$sc1_r;
# my $sc1y = 0.0;
# my $sc1z = cos($AngY_tcd/$DEG)*$sc1_r;
# my $sc2x = sin(-$AngY_tcd/$DEG)*$sc2_r;
# my $sc2y = 0.0;
# my $sc2z = cos($AngY_tcd/$DEG)*$sc2_r;

my $Z_sc1 = $Z_window_front - 5*2.54; #5inch before front window
my $Z_sc2 = $Z_window_back + 5*2.54;  #5inch behind back window

## EC: 4.25in square modules with length 18in in 3x3 array
my $ec_x_hlfln = 4.25*3/2*2.54;  
my $ec_y_hlfln = 4.25*3/2*2.54;  
# my $ec_z_hlfln = 18/2*2.54;
my $ec_z_hlfln = 0.01/2*2.54;

## EC 17in behind back window
# my $ec_r = $r_window_back + 17*2.54 + $ec_z_hlfln;

# my $ec_xpos = sin(-$AngY_tcd/$DEG)*$ec_r;
# my $ec_ypos = 0.0;
# my $ec_zpos = cos($AngY_tcd/$DEG)*$ec_r;

my $Z_ec = $Z_window_back + 17*2.54 + $ec_z_hlfln;

# Hittype and materials
my $hitype="solid_hgc";  # alternative: "flux"
my $material_chamber="G4_POLYVINYL_CHLORIDE";
my $material_window_front = "G4_Al";  
my $material_window_back = "G4_POLYVINYL_CHLORIDE";  #actually, the back will be PVC
my $material_gas="SL_HGC_C4F8_oneatm";  
my $material_pmt_surface = "SL_HGC_C4F8_oneatm";
# my $material_gas="SL_LGCCgas";
# my $material_pmt_surface = "SL_LGCCgas";
# my $material_gas="SL_N2gas";
# my $material_pmt_surface = "SL_N2gas";
my $material_pmt_backend= "Kryptonite";
my $material_mirror= "SL_HGC_CFRP";
my $material_scint = "G4_PLASTIC_SC_VINYLTOLUENE";
# my $material_ec = "G4_SODIUM_IODIDE";
my $material_ec = "Kryptonite";

sub make_tcd
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_tcd";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "$x_chamber*cm $y_chamber*cm $z_chamber*cm";
 $detector{"rotation"}    = "$AngX_chamber*deg $AngY_chamber*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Box";
 $detector{"dimensions"}  = "30*cm 150*cm 150*cm";
 $detector{"material"}    = "G4_AIR";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 0;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "no";
 $detector{"identifiers"} = "no";
 print_det(\%configuration, \%detector);
}

sub make_chamber
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_chamber_l";
 $detector{"mother"}      = "$DetectorName\_tcd";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC00";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_chamber*cm $Rmax_chamber*cm $halflength_chamber_l*cm 0*deg 360*deg"; 
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector);
 
  %detector=init_det(); 
 $detector{"name"}        = "$DetectorName\_chamber_t";
 $detector{"mother"}      = "$DetectorName\_tcd";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm $PMT_y*cm $mirror_d*cm";
 $detector{"rotation"}    = "90*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC00";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_chamber*cm $Rmax_chamber*cm $halflength_chamber_t*cm 0*deg 360*deg"; 
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector); 

  %detector=init_det();
 $detector{"name"}        = "$DetectorName\_chamber";
 $detector{"mother"}      = "$DetectorName\_tcd";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "ff0000";
 $detector{"type"}        = "Operation:@ $DetectorName\_chamber_l + $DetectorName\_chamber_t";
 $detector{"dimensions"}  = "0";      
 $detector{"material"}    = "$material_chamber";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "no";
 $detector{"identifiers"} = "no";
 print_det(\%configuration, \%detector); 
 
}

sub make_gas
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_gas_l";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "AACC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_gas*cm $Rmax_gas*cm $halflength_chamber_l*cm 0*deg 360*deg"; 
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector);
 
 %detector=init_det(); 
 $detector{"name"}        = "$DetectorName\_gas_t";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm $PMT_y*cm $mirror_d*cm";
 $detector{"rotation"}    = "90*deg 0*deg 0*deg";
 $detector{"color"}       = "AACC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_gas*cm $Rmax_gas*cm $halflength_chamber_t*cm 0*deg 360*deg"; 
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector); 

  %detector=init_det();
 $detector{"name"}        = "$DetectorName\_gas";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "AACC33";
 $detector{"type"}        = "Operation:@ $DetectorName\_gas_l + $DetectorName\_gas_t";
 $detector{"dimensions"}  = "0";      
 $detector{"material"}    = "$material_gas";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "no";
 $detector{"identifiers"} = "no";
 print_det(\%configuration, \%detector);  
}


sub make_window_front
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_window_front";
 $detector{"mother"}      = "$DetectorName\_gas";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $Z_window_front*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCAA33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_window_front*cm $Rmax_window_front*cm $halfthickness_window_front*cm 0*deg 360*deg";
 $detector{"material"}    = $material_window_front;
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 1;
  $detector{"sensitivity"} = "flux";
  $detector{"hit_type"}    = "flux";
  $detector{"identifiers"} = "id manual 10";
  print_det(\%configuration, \%detector);
}

sub make_window_back
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_window_back";
 $detector{"mother"}      = "$DetectorName\_gas";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $Z_window_back*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCAA33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_window_back*cm $Rmax_window_back*cm $halfthickness_window_back*cm 0*deg 360*deg";
 $detector{"material"}    = $material_window_back;
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

sub make_mirror
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_mirror";
 $detector{"mother"}      = "$DetectorName\_gas";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $mirror_d*cm";
 $detector{"color"}       = "aaaaff";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"type"}        = "CTube";
 $detector{"dimensions"}  = "$mirror_Rmin*cm $mirror_Rmax*cm $mirror_halfthickness*cm 0*deg 360*deg 0*cm 0.7*cm -0.7*cm 0*cm -0.7*cm 0.7*cm"; 
 $detector{"material"}    = $material_window_back;
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 1;
  $detector{"sensitivity"} = "mirror: SL_HGC_mirror";
  $detector{"hit_type"}    = "mirror";
  $detector{"identifiers"} = "no";      
 print_det(\%configuration, \%detector);
}

sub make_pmt
{ 
      my %detector;      
      %detector=init_det();      
      $detector{"name"}        = "$DetectorName\_pmt";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "0*cm $PMT_y*cm $mirror_d*cm";
      $detector{"rotation"}    = "-90*deg 0*deg 0*deg";
      $detector{"color"}       = "000000";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $half_width*cm $half_z*cm";
      $detector{"material"}    = $material_pmt_surface;
      $detector{"mfield"}      = "no";
      $detector{"ncopy"}       = 1;
      $detector{"pMany"}       = 1;
      $detector{"exist"}       = 1;
      $detector{"visible"}     = 1;
      $detector{"style"}       = 0; 
      print_det(\%configuration, \%detector); 
      
      %detector=init_det();
      $detector{"name"}        = "$DetectorName\_pmt_surface";     
      $detector{"mother"}      = "$DetectorName\_pmt";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "0*cm 0*cm $windowhalf_z*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "009999";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $half_width*cm $windowhalf_z*cm";
      $detector{"material"}    = $material_pmt_surface;
      $detector{"mfield"}      = "no";
      $detector{"ncopy"}       = 1;
      $detector{"pMany"}       = 1;
      $detector{"exist"}       = 1;
      $detector{"visible"}     = 1;
      $detector{"style"}       = 1;
      $detector{"sensitivity"} = $hitype;
      $detector{"hit_type"}    = $hitype;
      my $id=2200000+10000;      
      $detector{"identifiers"} = "id manual $id";      
      print_det(\%configuration, \%detector);
   
   
      %detector=init_det();      
      $detector{"name"}        = "$DetectorName\_pmt_backend";
      $detector{"mother"}      = "$DetectorName\_pmt";      
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "0*cm 0*cm -$backendhalf_z*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "000000";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $half_width*cm $backendhalf_z*cm";
      $detector{"material"}    = $material_pmt_backend;
      $detector{"mfield"}      = "no";
      $detector{"ncopy"}       = 1;
      $detector{"pMany"}       = 1;
      $detector{"exist"}       = 1;
      $detector{"visible"}     = 1;
      $detector{"style"}       = 1;
      print_det(\%configuration, \%detector);
}

sub make_scplane_front
{
	my %detector=init_det();
	$detector{"name"}        = "$DetectorName\_scfront";
	$detector{"mother"}      = "$DetectorName\_tcd";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "0*cm 0*cm $Z_sc1*cm";
	$detector{"rotation"}    = "0*deg 0*deg 0*deg";
	$detector{"color"}       = "CC6633";
	$detector{"type"}        = "Box";
	$detector{"dimensions"}  = "$sc1_x_hlfln*cm $sc1_y_hlfln*cm $sc_z_hlfln*cm";
	$detector{"material"}    = $material_scint;
	$detector{"mfield"}      = "no";
	$detector{"ncopy"}       = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "flux";
	$detector{"hit_type"}    = "flux";
	$detector{"identifiers"} = "id manual 1";
	print_det(\%configuration, \%detector);
 
}

sub make_scplane_back
{
	my %detector=init_det();
	$detector{"name"}        = "$DetectorName\_scback";
	$detector{"mother"}      = "$DetectorName\_tcd";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "0*cm 0*cm $Z_sc2*cm"; 
	$detector{"rotation"}    = "0*deg 0*deg 0*deg";
	$detector{"color"}       = "CC6633";
	$detector{"type"}        = "Box";
	$detector{"dimensions"}  = "$sc2_x_hlfln*cm $sc2_y_hlfln*cm $sc_z_hlfln*cm";
	$detector{"material"}    = $material_scint;
	$detector{"mfield"}      = "no";
	$detector{"ncopy"}       = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "flux";
	$detector{"hit_type"}    = "flux";
	$detector{"identifiers"} = "id manual 2";
	print_det(\%configuration, \%detector);
 
}

sub make_ec
{
	my %detector=init_det();
	$detector{"name"}        = "$DetectorName\_ec";
	$detector{"mother"}      = "$DetectorName\_tcd";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "0*cm 0*cm $Z_ec*cm"; 
	$detector{"rotation"}    = "0*deg 0*deg 0*deg";
	$detector{"color"}       = "aa4422";
	$detector{"type"}        = "Box";
	$detector{"dimensions"}  = "$ec_x_hlfln*cm $ec_y_hlfln*cm $ec_z_hlfln*cm";
	$detector{"material"}    = $material_ec;
	$detector{"mfield"}      = "no";
	$detector{"ncopy"}       = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "flux";
	$detector{"hit_type"}    = "flux";
	$detector{"identifiers"} = "id manual 3";
	print_det(\%configuration, \%detector);
 
}

