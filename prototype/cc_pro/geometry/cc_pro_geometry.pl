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
make_chamber();
make_gas();
make_window_front();
make_window_back();
make_mirror();
make_pmt();
make_scplane_front();
make_scplane_back();
}

# N.B.
## 1. All the lengths are in centimeters

# Constants
my $DEG=180/3.1415926;  # conversion factor between degrees and radians

# Parameters
## Chamber
my $Ang_chamber=4;
# my $Ang_chamber=0.0;
my $Rmin1_chamber=0;  # inner radius of the chamber at the upstream side
my $Rmax1_chamber=14/2*2.54;  # outer radius of the chamber at the upstream side, 14 inch diameter
my $Rmin2_chamber=0;  # inner radius of the chamber at the downstream side
my $Rmax2_chamber=14/2*2.54;  # outer radius of the chamber at the downstream side, 14 inch diameter
# my $Zmin_chamber=1000;  # z position of the chamber at the upstream side
# my $Zmax_chamber=1254;  # z position of the chamber at the downstream side
my $Zmin_chamber=1000;  # z position of the chamber at the upstream side
my $Zmax_chamber=$Zmin_chamber+60*2.54;  # z position of the chamber at the downstream side
# my $Zmin_chamber=-300;  # z position of the chamber at the upstream side
# my $Zmax_chamber=300;  # z position of the chamber at the downstream side

## Gas
my $Rmin1_gas=$Rmin1_chamber;  # inner radius of the gas at the upstream side
my $Rmax1_gas=$Rmax1_chamber-0.75*2.54;  # outer radius of the gas at the upstream side, 12.5 inch diameter
my $Rmin2_gas=$Rmin2_chamber;  # inner radius of the gas at the downstream side
my $Rmax2_gas=$Rmax2_chamber-0.75*2.54;  # outer radius of the gas at the downstream side, 12.5 inch diameter

## Windows
my $halfthickness_window_front=0.005/2*2.54;  # half thickness of the front window, 0.005 inch 
my $halfthickness_window_back=0.75/2*2.54;  #PVC thickness is 3/4 inch


my $Z_window_front=$Zmin_chamber+$halfthickness_window_front;  # z position of the 1st front window
my $Z_window_back=$Zmax_chamber-$halfthickness_window_back;   # z position of the back window
my $Rmin_window_front=$Rmin1_gas;  # inner radius of the front windows
my $Rmax_window_front=$Rmax1_gas;  # outer radius of the front windows
my $Rmin_window_back=$Rmin2_gas;  # inner radius of the back windows
my $Rmax_window_back=$Rmax2_gas;  # outer radius of the back windows

## Gas Cont.
my $Zmin_gas=$Zmin_chamber+$halfthickness_window_front*2;  # z position of the gas at the upstream side
my $Zmax_gas=$Zmax_chamber-$halfthickness_window_back*2;  # z position of the gas at the downstream side

## Mirror
my $mirror_Rmin=0;
# my $mirror_Rmax=17/2*2.54;
my $mirror_Rmax=12.25/2*2.54;
# my $mirror_Rmax=13/2*2.54;
my $mirror_halfthickness=1;
# my $mirror_Z=$Zmin_chamber+203.2;
my $mirror_Z=$Zmin_chamber+40*2.54;

## PMT
my $half_width = 10.65;  # half width of the PMT
my $windowhalf_z = 1;  # half thickness of the front side of PMT
my $backendhalf_z = 1;   # half thickness of the back side of PMT
my $half_z = $windowhalf_z + $backendhalf_z;  # total half length of the PMT

## Scintillators:
my $sc1_x_hlfln = 7.0*2.54;  #for now, we assume the same size as the outer radius of the tube
my $sc1_y_hlfln = 7.0*2.54;  
my $sc2_x_hlfln = 7.0*2.54;
my $sc2_y_hlfln = 7.0*2.54;
my $sc_z_hlfln = 2.54/8.0;  #need exact measurement, but we assume they are 1/4" thick

my $sc1_zpos_loc = $Z_window_front - 10.; #10cm in front of front window
my $sc2_zpos_loc = $Z_window_back + 10.; #10cm behind of front window

my $sc1x = sin(-$Ang_chamber/$DEG)*$sc1_zpos_loc;
my $sc1y = 0.0;
my $sc1z = cos($Ang_chamber/$DEG)*$sc1_zpos_loc;

my $sc2x = sin(-$Ang_chamber/$DEG)*$sc2_zpos_loc;
my $sc2y = 0.0;
my $sc2z = cos($Ang_chamber/$DEG)*$sc2_zpos_loc;


# Hittype and materials
my $hitype="solid_hgc";  # alternative: "flux"
my $material_chamber="G4_POLYVINYL_CHLORIDE";
my $material_window_front = "G4_Al";  
my $material_window_back = "G4_POLYVINYL_CHLORIDE";  #actually, the back will be PVC
# my $material_gas="SL_HGC_C4F8_oneatm";  
# my $material_pmt_surface = "SL_HGC_C4F8_oneatm";
# my $material_gas="SL_LGCCgas";
# my $material_pmt_surface = "SL_LGCCgas";
my $material_gas="SL_N2gas";
my $material_pmt_surface = "SL_N2gas";
my $material_pmt_backend= "Kryptonite";
my $material_mirror= "SL_HGC_CFRP";
my $material_scint = "G4_PLASTIC_SC_VINYLTOLUENE";

sub make_chamber
{
#  my %detector=init_det();
#  $detector{"name"}        = "$DetectorName\_chamber";
#  $detector{"mother"}      = "$DetectorMother";
#  $detector{"description"} = $detector{"name"};
#  $detector{"pos"}         = "0*cm 0*cm 0*cm";
#  $detector{"rotation"}    = "0*deg $Ang_chamber*deg 0*deg";
#  $detector{"color"}       = "CCCC33";
#  $detector{"type"}        = "Polycone";
#  $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_chamber*cm $Rmin2_chamber*cm $Rmax1_chamber*cm $Rmax2_chamber*cm $Zmin_chamber*cm $Zmax_chamber*cm";
#  $detector{"material"}    = "$material_chamber";
#  $detector{"mfield"}      = "no";
#  $detector{"ncopy"}       = 1;
#  $detector{"pMany"}       = 1;
#  $detector{"exist"}       = 1;
#  $detector{"visible"}     = 1;
#  $detector{"style"}       = 0;
#  $detector{"sensitivity"} = "no";
#  $detector{"hit_type"}    = "no";
#  $detector{"identifiers"} = "no";
#  print_det(\%configuration, \%detector);

 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_chamber_l";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Polycone";
 $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_chamber*cm $Rmin2_chamber*cm $Rmax1_chamber*cm $Rmax2_chamber*cm $Zmin_chamber*cm $Zmax_chamber*cm";
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector);
 
 my $Zmin_chamber_t = $mirror_Z - (18.5-14/2)*2.54;
 my $Zmax_chamber_t = $mirror_Z + (18.5-14/2)*2.54;
 my $halfthickness_chamber_t = (18.5-14/2)*2.54;
 
#   %detector=init_det(); 
#  $detector{"name"}        = "$DetectorName\_chamber_t";
#  $detector{"mother"}      = "$DetectorMother";
#  $detector{"description"} = $detector{"name"};
#  $detector{"pos"}         = "0*cm 0*cm $mirror_Z*cm";
#  $detector{"rotation"}    = "0*deg 90*deg 0*deg";
#  $detector{"color"}       = "CCCC33";
#  $detector{"type"}        = "Polycone";
#  $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_chamber*cm $Rmin2_chamber*cm $Rmax1_chamber*cm $Rmax2_chamber*cm $Zmin_chamber_t*cm $Zmax_chamber_t*cm";
#  $detector{"material"}    = "Component";
#  print_det(\%configuration, \%detector); 

  %detector=init_det(); 
 $detector{"name"}        = "$DetectorName\_chamber_t";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm $halfthickness_chamber_t*cm $mirror_Z*cm";
 $detector{"rotation"}    = "90*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin1_chamber*cm $Rmax1_chamber*cm $halfthickness_chamber_t*cm 0*deg 360*deg"; 
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector); 

  %detector=init_det();
 $detector{"name"}        = "$DetectorName\_chamber";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg $Ang_chamber*deg 0*deg";
 $detector{"color"}       = "CCCC33";
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
#  my %detector=init_det();
#  $detector{"name"}        = "$DetectorName\_gas";
#  $detector{"mother"}      = "$DetectorName\_chamber";
#  $detector{"description"} = $detector{"name"};
#  $detector{"pos"}         = "0*cm 0*cm 0*cm";
#  $detector{"rotation"}    = "0*deg 0*deg 0*deg";
#  $detector{"color"}       = "AACC33";
#  $detector{"type"}        = "Polycone";
#  $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_gas*cm $Rmin2_gas*cm $Rmax1_gas*cm $Rmax2_gas*cm $Zmin_gas*cm $Zmax_gas*cm";
#  $detector{"material"}    = "$material_gas";
#  $detector{"mfield"}      = "no";
#  $detector{"ncopy"}       = 1;
#  $detector{"pMany"}       = 1;
#  $detector{"exist"}       = 1;
#  $detector{"visible"}     = 1;
#  $detector{"style"}       = 0;
#  print_det(\%configuration, \%detector);
 
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_gas_l";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "AACC33";
 $detector{"type"}        = "Polycone";
 $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_gas*cm $Rmin2_gas*cm $Rmax1_gas*cm $Rmax2_gas*cm $Zmin_gas*cm $Zmax_gas*cm";
 $detector{"material"}    = "Component";
 print_det(\%configuration, \%detector);
 
 my $Zmin_gas_t = $mirror_Z - (18.5-14/2)*2.54;
 my $Zmax_gas_t = $mirror_Z + (18.5-14/2)*2.54;
 my $halfthickness_gas_t = (18.5-14/2)*2.54;

 %detector=init_det(); 
 $detector{"name"}        = "$DetectorName\_gas_t";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm $halfthickness_gas_t*cm $mirror_Z*cm";
 $detector{"rotation"}    = "90*deg 0*deg 0*deg";
 $detector{"color"}       = "AACC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin1_gas*cm $Rmax1_gas*cm $halfthickness_gas_t*cm 0*deg 360*deg"; 
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
 $detector{"mother"}      = "$DetectorName\_chamber";
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
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "no";
 $detector{"identifiers"} = "no";
 print_det(\%configuration, \%detector);
}

sub make_window_back
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_window_back";
 $detector{"mother"}      = "$DetectorName\_chamber";
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
 $detector{"pos"}         = "0*cm 0*cm $mirror_Z*cm";
 $detector{"color"}       = "aaaaff"; 
#  $detector{"rotation"}    = "-45*deg 0*deg 0*deg";
#  $detector{"type"}        = "Tube";
#  $detector{"dimensions"}  = "$mirror_Rmin*cm $mirror_Rmax*cm $mirror_halfthickness*cm 0*deg 360*deg";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"type"}        = "CTube";
 $detector{"dimensions"}  = "$mirror_Rmin*cm $mirror_Rmax*cm $mirror_halfthickness*cm 0*deg 360*deg 0 0.7 -0.71 0 -0.7 0.71 "; 
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
      $detector{"pos"}         = "0*cm 47*cm $mirror_Z*cm";
      $detector{"rotation"}    =  "ordered: zxy 0*deg 0*deg 0*deg";
      $detector{"color"}       = "000000";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $half_z*cm $half_width*cm";
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
      $detector{"pos"}         = "0*cm $windowhalf_z*cm 0*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "009999";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $windowhalf_z*cm $half_width*cm";
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
      $detector{"pos"}         = "0*cm -$backendhalf_z*cm 0*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "000000";  #cyan
      $detector{"type"}        = "Box";
      $detector{"dimensions"}  = "$half_width*cm $backendhalf_z*cm $half_width*cm";
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
	$detector{"mother"}      = "$DetectorMother";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "$sc1x*cm $sc1y*cm $sc1z*cm"; 
	$detector{"rotation"}    = "0*deg $Ang_chamber*deg 0*deg";
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
	$detector{"mother"}      = "$DetectorMother";
	$detector{"description"} = $detector{"name"};
	$detector{"pos"}         = "$sc2x*cm $sc2y*cm $sc2z*cm"; 
	$detector{"rotation"}    = "0*deg $Ang_chamber*deg 0*deg";
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
