use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;
use Math::VectorReal;
  
my $DetectorName = 'solid_ccprototype';

my $DetectorMother="root";

sub solid_ccprototype_geometry
{
make_chamber();
make_gas();
make_block();
make_window_front();
make_window_back();
#make_cone();
# make_cone_front();
make_pmt();
make_mirror();
#make_shield();
}

#BaBar
# Z(306,396)
# Rin(96,104)
# Rout(265,265)

# CLEOv8
# Z(306,396)
# Rin(86,98)
# Rout(265,265)

my $ang_tilt = 39; #degree  #  this is tilt angle of cone and PMTs around the focus axis
my $rmin_w_end = 21.5; 
my $z_w_half = 10;
my $dis_P_PMT = 20;
my $z_angle_min = 390;
my $sphere_r_inner = 210;

my $shield_front_half_length = 15;
my $shield_back_half_length = 7;
my $shield_inner_radius = 20;

my $shield_total_half_length = $shield_front_half_length+$shield_back_half_length;
my $shield_outer_radius = $shield_inner_radius+0.3;


my $image_x = 0.;
my $rmin_w_front_cone = 10.16; 
my $rmax_w_front_cone = $rmin_w_front_cone+0.57;
my $rmax_w_end = $rmin_w_end+0.57;
my $z_angle_max = 423;
my $thickness_sphere = 0.3;
my $sphere_r_outer = $sphere_r_inner+$thickness_sphere;
my $Angle_in = 7;
my $Angle_out = 15;
my $Angle_opt = 11;
my $Z_target=350;
my $DEG=180/3.1415926;

my $y_angle_min = ($z_angle_min+$Z_target)*tan($Angle_in/$DEG);
my $y_angle_max = ($z_angle_max+$Z_target)*tan($Angle_out/$DEG);
my $pos_A = vector(0, $y_angle_max, $z_angle_max);
my $pos_B = vector(0, $y_angle_min, $z_angle_min);
my $vec_BA = $pos_A - $pos_B;
my $dir_BA = $vec_BA->norm();
my $dir_BA_ortho = vector(0, $dir_BA->z(),-$dir_BA->y());
my $dis_BA = sqrt($vec_BA->x()*$vec_BA->x()+$vec_BA->y()*$vec_BA->y()+$vec_BA->z()*$vec_BA->z());
my $dis_C_BA = sqrt($sphere_r_inner*$sphere_r_inner-$dis_BA*$dis_BA/4);
my $pos_sphere_center = $pos_B+$vec_BA/2+$dir_BA_ortho*$dis_C_BA;
#print "sphere center $pos_sphere_center->x() $pos_sphere_center->y() $pos_sphere_center->z()\n";

my $dis_C_PT = ($pos_sphere_center->y()-tan($Angle_opt/$DEG)*$pos_sphere_center->z()-tan($Angle_opt/$DEG)*350)/sqrt(1+tan($Angle_opt/$DEG)*tan($Angle_opt/$DEG));
my $ang_CPT = asin($dis_C_PT/$sphere_r_inner);
my $dir_P_PMT = vector(0,sin(2*$ang_CPT-$Angle_opt/$DEG),-cos(2*$ang_CPT-$Angle_opt/$DEG));
my $pos_P = vector(0,$pos_sphere_center->y()-$sphere_r_inner*sin($ang_CPT-$Angle_opt/$DEG),$pos_sphere_center->z()+$sphere_r_inner*cos($ang_CPT-$Angle_opt/$DEG));             
my $pos_PMT = $pos_P+$dis_P_PMT*$dir_P_PMT;
my $image_y = $pos_PMT->y();#239.7
my $image_z = $pos_PMT->z();#345
print "PMT position $image_y $image_z\n";
my $pos_x_sphere=sprintf('%f',$pos_sphere_center->y());
my $pos_y_sphere=sprintf('%f',$pos_sphere_center->x());
my $pos_z_sphere=sprintf('%f',$pos_sphere_center->z());





my $hitype="solid_hgc";
# my $hitype="flux";

my $material_chamber="G4_Al";
# my $material_gas="G4_Al";
my $material_gas="SL_HGC_C4F8O";
my $material_block="SL_HGC_C4F8O";
# my $material_block="G4_Al";
my $material_window_front_1 = "SL_HGC_kevlar";
my $material_window_front_2 = "SL_HGC_mylar";
my $material_window_back = "G4_Al";
# my $material_window_front_1 = "G4_Al";
# my $material_window_front_2 = "G4_Al";
my $material_cone= "G4_GLASS_PLATE";
# my $material_pmt_surface = "SL_HGC_pmt_surface";
# my $material_pmt_surface = "G4_GLASS_PLATE";
my $material_pmt_surface = "SL_HGC_C4F8O";
my $material_pmt_backend= "Kryptonite";
my $material_mirror= "SL_HGC_CFRP";

my $N=30; # number of sectors
my $ang_width=360/$N;  #in degree
# my $ang_tilt = 44.; #degree  #  this is tilt angle of cone and PMTs around the focus axis


my $sec_start = 96; #degree where the 1st sector starts


my $halfthickness_window_front_1=0.0215;
my $halfthickness_window_front_2=0.0065;
my $halfthickness_window_back=0.05;

# my $Rmin1_chamber=86;
my $Rmin1_chamber=130;
my $Rmax1_chamber=175;
# my $Rmin2_chamber=98;
# my $Rmin2_chamber=94;
my $Rmin2_chamber=130;
my $Rmax2_chamber=175;
my $Rmin1_gas=$Rmin1_chamber+0.5;
my $Rmax1_gas=$Rmax1_chamber-0.5;
my $Rmin2_gas=$Rmin2_chamber+0.5;
my $Rmax2_gas=$Rmax2_chamber-0.5;



# my $Zmin_chamber=306;
# my $Zmax_chamber=406;
my $Zmin_chamber=326;
my $Zmax_chamber=426;

my $Zmin_gas=$Zmin_chamber+($halfthickness_window_front_1*2+$halfthickness_window_front_2*2);
my $Zmax_gas=$Zmax_chamber-$halfthickness_window_back*2;

my $Z_window_front_1=$Zmin_chamber+$halfthickness_window_front_1;
my $Z_window_front_2=$Zmin_chamber+$halfthickness_window_front_1*2+$halfthickness_window_front_2;
my $Rmin_window_front=$Rmin1_gas;
my $Rmax_window_front=187;

my $Z_window_back=$Zmax_chamber-$halfthickness_window_back;
my $Rmin_window_back=$Rmin2_gas;
my $Rmax_window_back=$Rmax2_gas;

sub make_chamber
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_chamber";
 $detector{"mother"}      = "$DetectorMother";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Polycone";
#  $detector{"dimensions"}  = "0*deg 360*deg 2*counts 83*cm 96*cm 265*cm 265*cm 306*cm 406*cm";
 $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_chamber*cm $Rmin2_chamber*cm $Rmax1_chamber*cm $Rmax2_chamber*cm $Zmin_chamber*cm $Zmax_chamber*cm";
 $detector{"material"}    = "$material_chamber";
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

sub make_gas
{
 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_gas";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 0*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Polycone";
#  $detector{"dimensions"}  = "0*deg 360*deg 2*counts 83*cm 96*cm 265*cm 265*cm 306*cm 406*cm";
 $detector{"dimensions"}  = "0*deg 360*deg 2*counts $Rmin1_gas*cm $Rmin2_gas*cm $Rmax1_gas*cm $Rmax2_gas*cm $Zmin_gas*cm $Zmax_gas*cm";
 $detector{"material"}    = "$material_gas";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 1;
 $detector{"style"}       = 0;
#       $detector{"sensitivity"} = "flux";
#       $detector{"hit_type"}    = "flux";
#       $detector{"identifiers"} = "id manual 1";
 print_det(\%configuration, \%detector);
}


sub make_window_front
{
    my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_window_front_1";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $Z_window_front_1*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_window_front*cm $Rmax_window_front*cm $halfthickness_window_front_1*cm 0*deg 360*deg";
 $detector{"material"}    = $material_window_front_1;
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
 
 $detector{"name"}        = "$DetectorName\_window_front_2";
 $detector{"mother"}      = "$DetectorName\_chamber";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm $Z_window_front_2*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "CC33CC";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_window_front*cm $Rmax_window_front*cm $halfthickness_window_front_2*cm 0*deg 360*deg";
 $detector{"material"}    = $material_window_front_2;
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
 $detector{"color"}       = "CCCC33";
 $detector{"type"}        = "Tube";
 $detector{"dimensions"}  = "$Rmin_window_back*cm $Rmax_window_back*cm $halfthickness_window_back*cm 0*deg 360*deg";
 $detector{"material"}    = $material_window_back;
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

sub make_block
{
     for(my $i=1; $i<=$N; $i++){
      my $sector_start=$sec_start+0.5*$ang_width+$ang_width*($i-1);
      
      my %detector=init_det();
      $detector{"name"}        = "$DetectorName\_block_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "0*cm 0*cm 0*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "22CC33";  
      $detector{"type"}        = "Polycone";
      $detector{"dimensions"}  = "$sector_start*deg 0.000005*deg 2*counts $Rmin1_gas*cm $Rmin2_gas*cm $Rmax1_gas*cm $Rmax2_gas*cm $Zmin_gas*cm $Zmax_gas*cm";      
      $detector{"material"}    = $material_block;
      $detector{"mfield"}      = "no";
      $detector{"ncopy"}       = 1;
      $detector{"pMany"}       = 1;
      $detector{"exist"}       = 1;
      $detector{"visible"}     = 0;
      $detector{"style"}       = 0;
      print_det(\%configuration, \%detector);
    }
}

sub make_cone
{  

#   my $Dz = 18.;
  
  my $pos_r = $image_y-sin($ang_tilt/$DEG)*$z_w_half;  
  my $pos_z = $image_z+cos($ang_tilt/$DEG)*$z_w_half;
#print "cone $pos_r $pos_z\n";
     for(my $i=1; $i<=$N; $i++){
      my $pos_x = $pos_r*cos(($i-1)*$ang_width/$DEG+$sec_start/$DEG);
      my $pos_y = $pos_r*sin(($i-1)*$ang_width/$DEG+$sec_start/$DEG);    
#       my $ang_xrot=-($ang_tilt*sin(($i-1)*$ang_width/$DEG));
#       my $ang_yrot=($ang_tilt*cos(($i-1)*$ang_width/$DEG));
      my $ang_zrot=-(($i+-1)*$ang_width+$sec_start);
      my $ang_xrot=0;
      my $ang_yrot=$ang_tilt; 

#       my $z1=$pos_z-$z_w_half-0.002;
#       my $z2=$pos_z-$z_w_half-0.001;
#       my $z3=$pos_z-$z_w_half;
#       my $z4=$pos_z+$z_w_half;      
      
      %detector=init_det();
      $detector{"name"}        = "$DetectorName\_cone_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";  
      $detector{"rotation"}    =  "ordered: zxy $ang_zrot*deg $ang_xrot*deg $ang_yrot*deg";
      $detector{"color"}       = "3dff84";  
      $detector{"type"}        = "Cons";
      $detector{"dimensions"}  = "$rmin_w_front_cone*cm $rmax_w_front_cone*cm $rmin_w_end*cm $rmax_w_end*cm $z_w_half*cm 0*deg 360*deg";   
#       $detector{"type"}        = "Polycone";
#       $detector{"dimensions"}  = "0*deg 360*deg 4*counts 0*cm 0*cm $rmin_w_front_cone*cm $rmin_w_end*cm $rmin_w_front_cone*cm $rmin_w_front_cone*cm $rmax_w_front_cone*cm $rmin_w_end*cm $z1*cm $z2*cm $z3*cm $z4*cm";
      $detector{"material"}    = $material_cone;
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
}

sub make_cone_front
{

#   my $Dz = 18.;
  
#   my $pos_r = $image_y-sin($ang_tilt/$DEG)*$z_w_half+10;  
#   my $pos_z = $image_z+cos($ang_tilt/$DEG)*$z_w_half+10;
  my $pos_r = $image_y-sin($ang_tilt/$DEG)*$z_w_half-sin($ang_tilt/$DEG);  
  my $pos_z = $image_z+cos($ang_tilt/$DEG)*$z_w_half+cos($ang_tilt/$DEG);
#print "cone $pos_r $pos_z\n";
     for(my $i=1; $i<=$N; $i++){
      my $pos_x = $pos_r*cos(($i-1)*$ang_width/$DEG+$sec_start/$DEG);
      my $pos_y = $pos_r*sin(($i-1)*$ang_width/$DEG+$sec_start/$DEG);    
#       my $ang_xrot=-($ang_tilt*sin(($i-1)*$ang_width/$DEG));
#       my $ang_yrot=($ang_tilt*cos(($i-1)*$ang_width/$DEG));
      my $ang_zrot=-(($i+-1)*$ang_width+$sec_start);
      my $ang_xrot=0;
      my $ang_yrot=$ang_tilt; 

#       my $z1=$pos_z-$z_w_half-0.002;
#       my $z2=$pos_z-$z_w_half-0.001;
#       my $z3=$pos_z-$z_w_half;
#       my $z4=$pos_z+$z_w_half;      
      
      
      my %detector=init_det();
      $detector{"name"}        = "$DetectorName\_cone_front_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";  
      $detector{"rotation"}    =  "ordered: zxy $ang_zrot*deg $ang_xrot*deg $ang_yrot*deg";
#       $detector{"color"}       = "3dff84";  
      $detector{"color"}       = "111111";  
      $detector{"type"}        = "Cons";
      $detector{"dimensions"}  = "$rmin_w_front_cone*cm $rmax_w_front_cone*cm $rmin_w_end*cm $rmax_w_end*cm $z_w_half*cm 0*deg 360*deg";   
#       $detector{"type"}        = "Polycone";
#       $detector{"dimensions"}  = "0*deg 360*deg 4*counts 0*cm 0*cm $rmin_w_front_cone*cm $rmin_w_end*cm $rmin_w_front_cone*cm $rmin_w_front_cone*cm $rmax_w_front_cone*cm $rmin_w_end*cm $z1*cm $z2*cm $z3*cm $z4*cm";
#       $detector{"material"}    = $material_cone;
      $detector{"material"}    = $material_gas;
      $detector{"mfield"}      = "no";
      $detector{"ncopy"}       = 1;
      $detector{"pMany"}       = 1;
      $detector{"exist"}       = 1;
      $detector{"visible"}     = 1;
      $detector{"style"}       = 1;
      $detector{"sensitivity"} = "flux";
      $detector{"hit_type"}    = "flux";      
      my $id=2212000+$i;
      $detector{"identifiers"} = "id manual $id";         
      print_det(\%configuration, \%detector);           
    }
}

sub make_shield
{
  my $pos_r = $image_y+sin($ang_tilt/$DEG)*($shield_back_half_length-$shield_front_half_length);  
  my $pos_z = $image_z-cos($ang_tilt/$DEG)*($shield_back_half_length-$shield_front_half_length);
     for(my $i=1; $i<=$N; $i++){
      my $pos_x = $pos_r*cos(($i-1)*$ang_width/$DEG+$sec_start/$DEG);
      my $pos_y = $pos_r*sin(($i-1)*$ang_width/$DEG+$sec_start/$DEG);    
      my $ang_zrot=-(($i+-1)*$ang_width+$sec_start);
      my $ang_xrot=0;
      my $ang_yrot=$ang_tilt; 


      my %detector=init_det();
      $detector{"name"}        = "$DetectorName\_shield_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";  
      $detector{"rotation"}    =  "ordered: zxy $ang_zrot*deg $ang_xrot*deg $ang_yrot*deg";
      $detector{"color"}       = "808080";  
      $detector{"type"}        = "Tube";
      $detector{"dimensions"}  = "$shield_inner_radius*cm $shield_outer_radius*cm $shield_total_half_length*cm 0*deg 360*deg";   
      $detector{"material"}    = $material_cone;
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
}




sub make_pmt
{ 
#  my $z_w_half = 18.5;
#  my $pos_z = -($z_w_half-0.5);
 
 my $half_width = 10.16; 
#  my $windowhalf_z = 0.254;
 my $windowhalf_z = 0.001;
 my $backendhalf_z = 0.001; 
 my $half_z = $windowhalf_z + $backendhalf_z; 
 
  my $pos_r = $image_y+sin($ang_tilt/$DEG)*$half_z;  
  my $pos_z = $image_z-cos($ang_tilt/$DEG)*$half_z;
  #print "pmt $pos_r $pos_z\n";
     for(my $i=1; $i<=$N; $i++){
      my $pos_x = $pos_r*cos(($i-1)*$ang_width/$DEG+$sec_start/$DEG);
      my $pos_y = $pos_r*sin(($i-1)*$ang_width/$DEG+$sec_start/$DEG);    
#       my $ang_xrot=-($ang_tilt*sin(($i-1)*$ang_width/$DEG));
#       my $ang_yrot=($ang_tilt*cos(($i-1)*$ang_width/$DEG));
#       my $ang_zrot=-($i-1)*$ang_width;
      my $ang_zrot=-(($i-1)*$ang_width+$sec_start);
      my $ang_xrot=0;
      my $ang_yrot=$ang_tilt; 

#       my $posz=-(18.5-$half_z);

      my %detector;      
      %detector=init_det();      
      $detector{"name"}        = "$DetectorName\_pmt_$i";
#       $detector{"mother"}      = "$DetectorName\_cone_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
      $detector{"rotation"}    =  "ordered: zxy $ang_zrot*deg $ang_xrot*deg $ang_yrot*deg";
#       $detector{"pos"}         = "0*cm 0*cm $posz*cm";
#       $detector{"rotation"}    = "0*deg 0*deg 0*deg";
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
      $detector{"name"}        = "$DetectorName\_pmt_surface_$i";
#       $detector{"mother"}      = "$DetectorName\_gas";      
      $detector{"mother"}      = "$DetectorName\_pmt_$i";
      $detector{"description"} = $detector{"name"};
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
#       $detector{"rotation"}    = "$ang_xrot*deg $ang_yrot*deg 0*deg";
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
      my $id=2200000+$i*10000;      
      $detector{"identifiers"} = "id manual $id";      
      print_det(\%configuration, \%detector);
   
#       %detector=init_det();      
#       $detector{"name"}        = "$DetectorName\_pmt_backend_$i";
# #       $detector{"mother"}      = "$DetectorName\_gas";
#       $detector{"mother"}      = "$DetectorName\_pmt_$i";      
#       $detector{"description"} = $detector{"name"};
# #       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
# #       $detector{"rotation"}    = "$ang_xrot*deg $ang_yrot*deg 0*deg";
#       $detector{"pos"}         = "0*cm 0*cm -$windowhalf_z*cm";
#       $detector{"rotation"}    = "0*deg 0*deg 0*deg";
#       $detector{"color"}       = "000000";  #cyan
#       $detector{"type"}        = "Box";
#       $detector{"dimensions"}  = "$half_width*cm $half_width*cm $backendhalf_z*cm";
#       $detector{"material"}    = "Air_Opt";
#       $detector{"mfield"}      = "no";
#       $detector{"ncopy"}       = 1;
#       $detector{"pMany"}       = 1;
#       $detector{"exist"}       = 1;
#       $detector{"visible"}     = 1;
#       $detector{"style"}       = 1;
#       $detector{"sensitivity"} = "flux";
#       $detector{"hit_type"}    = "flux";
#       my $id=2200000+$i*10000;      
#       $detector{"identifiers"} = "id manual $id";
#       print_det(\%configuration, \%detector);
   
      %detector=init_det();      
      $detector{"name"}        = "$DetectorName\_pmt_backend_$i";
#       $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"mother"}      = "$DetectorName\_pmt_$i";      
      $detector{"description"} = $detector{"name"};
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
#       $detector{"rotation"}    = "$ang_xrot*deg $ang_yrot*deg 0*deg";
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
}

sub make_mirror
{
#=== cons of mirror ========================================  
#   // max and min polar angles in SIDIS in degree
#   my $Angle_in = 7.5;
#   my $Angle_in = 7.3;
#   my $Angle_out = 15.5; 
#   my $Angle_avg = ($Angle_in+$Angle_out)/2;   # 11.5

 
#   // z dist. between the target and front/back walls of the tank: 350 + 306 & 350 + 396
#   // add 15*cm to R_in because the mirror is sticking out
  my $Z_front = $Z_target+$Zmin_chamber;
  my $Z_end = $Z_target+$Zmax_chamber;
  my $Z_half_w = ($Z_end-$Z_front)/2.;  
  
#   // this is where the center of the cone should stay w.r.t. (0,0,0)
#   // i.e. in the middle of the tank: (306+406)/2=356*cm
#   my $cons_z=356;
  my $cons_z=($Zmin_chamber+$Zmax_chamber)/2;  

  my $R_front_in = $Z_front*tan(10/$DEG);
  my $R_front_out = $Z_front*tan(12/$DEG);
  my $R_end_in = $Z_end*tan(10/$DEG);
  my $R_end_out = $Z_end*tan(12/$DEG);
#print "$R_front_in $R_front_out $R_end_in $R_end_out\n";  
#   86.3640091200709 181.92483680982 99.5292544127646 209.657281445463

  my $ang_start=-0.5*$ang_width;  
#   my $ang_start=0;  

#===============================================================  
  
#===============================================================
  
#       // make a cone to intersect a sphere      
     for(my $i=1; $i<=$N; $i++){      
      my %detector=init_det();
      $detector{"name"}        = "$DetectorName\_mirror_cons_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $cons_z*cm";
#       $detector{"rotation"}    = "$ang_xrot*deg $ang_yrot*deg 0*deg";
      $detector{"pos"}         = "0*cm 0*cm $cons_z*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "808080";  #gray
      $detector{"type"}        = "Cons";
      $detector{"dimensions"}  = "$R_front_in*cm $R_front_out*cm $R_end_in*cm $R_end_out*cm $Z_half_w*cm $ang_start*deg $ang_width*deg";
      $detector{"material"}    = "Component";
#       $detector{"material"}    = "$material_pmt_backend";
#       $detector{"mfield"}      = "no";
#       $detector{"ncopy"}       = 1;
#       $detector{"pMany"}       = 1;
#       $detector{"exist"}       = 1;
#       $detector{"visible"}     = 1;
#       $detector{"style"}       = 1;      
      print_det(\%configuration, \%detector);
      
      %detector=init_det();
      $detector{"name"}        = "$DetectorName\_mirror_sphere_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $pos_z*cm";
#       $detector{"pos"}         = "0*cm 0*cm $Z_mirror*cm";
#       $detector{"pos"}         = "$pos_x*cm $pos_y*cm $cons_z*cm";
#       $detector{"rotation"}    = "$ang_xrot*deg $ang_yrot*deg 0*deg";
      $detector{"pos"}         = "$pos_x_sphere*cm $pos_y_sphere*cm $pos_z_sphere*cm";
      $detector{"rotation"}    = "0*deg 0*deg 0*deg";
      $detector{"color"}       = "808080";  #gray
      $detector{"type"}        = "Sphere";
      $detector{"dimensions"}  = "$sphere_r_inner*cm $sphere_r_outer*cm 0*deg 360*deg 0*deg 90*deg";
      $detector{"material"}    = "Component";
#       $detector{"material"}    = "$material_pmt_backend";      
#       $detector{"ncopy"}       = 1;
#       $detector{"pMany"}       = 1;
#       $detector{"exist"}       = 1;
#       $detector{"visible"}     = 1;
#       $detector{"style"}       = 1;            
      print_det(\%configuration, \%detector);      
      
      my $ang_zrot = -($sec_start+($i-1)*$ang_width);      
      
# Make the subtraction of the inner ellipsoid from the outer barrel:
# the "Operation:@" indicates that gemc should assume the coordinates
# and rotations of the mirror ellipsoid are given in its mother coordinate system,
# not relative to the outer barrel coordinate system:      
      %detector=init_det();
      $detector{"name"}        = "$DetectorName\_mirror_$i";
      $detector{"mother"}      = "$DetectorName\_gas";
      $detector{"description"} = $detector{"name"};
      $detector{"pos"}         = "0*cm 0*cm $cons_z*cm";      
      $detector{"rotation"}    = "0*deg 0*deg $ang_zrot*deg";
      $detector{"color"}       = "808080";  #gray				
      $detector{"type"}        = "Operation:@ $DetectorName\_mirror_cons_$i * $DetectorName\_mirror_sphere_$i";
      $detector{"dimensions"}  = "0";
#       $detector{"material"}    = "Component";      
      $detector{"material"}    = "$material_mirror";      
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
}