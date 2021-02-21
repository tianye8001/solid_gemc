use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;


my $DetectorName = 'solid_PVDIS_gem';

my $DetectorMother="root";

my $Nplate	= $parameters{"Nplate"};

my @Nsect = ($parameters{"Nsect1"},$parameters{"Nsect2"},$parameters{"Nsect3"},$parameters{"Nsect4"},$parameters{"Nsect5"});

#in cm 
my @PlateZ = ($parameters{"PlateZ1"},$parameters{"PlateZ2"},$parameters{"PlateZ3"},$parameters{"PlateZ4"},$parameters{"PlateZ5"});
my @Rin    = ($parameters{"Rin1"},$parameters{"Rin2"},$parameters{"Rin3"},$parameters{"Rin4"},$parameters{"Rin5"});

# in deg
my @angle_width = (360./$parameters{"Nsect1"},360./$parameters{"Nsect2"},360./$parameters{"Nsect3"},360./$parameters{"Nsect4"},360./$parameters{"Nsect5"});
my @offrot = ($parameters{"offrot1"},$parameters{"offrot2"},$parameters{"offrot3"},$parameters{"offrot4"},$parameters{"offrot5"});

#plane 1 using gem1, plane 2 and 3 using gem2, plane 4 and 4 using gem3
# in mm
my @gem_inner_half=($parameters{"gem1_inner"}/2,$parameters{"gem2_inner"}/2,$parameters{"gem2_inner"}/2,$parameters{"gem3_inner"}/2,$parameters{"gem3_inner"}/2);
my @gem_outer_half=($parameters{"gem1_outer"}/2,$parameters{"gem2_outer"}/2,$parameters{"gem2_outer"}/2,$parameters{"gem3_outer"}/2,$parameters{"gem3_outer"}/2);
my @gem_height_half=($parameters{"gem1_height"}/2,$parameters{"gem2_height"}/2,$parameters{"gem2_height"}/2,$parameters{"gem3_height"}/2,$parameters{"gem3_height"}/2);

my @frame_inner_half=($parameters{"frame1_inner"}/2,$parameters{"frame2_inner"}/2,$parameters{"frame2_inner"}/2,$parameters{"frame3_inner"}/2,$parameters{"frame3_inner"}/2);
my @frame_outer_half=($parameters{"frame1_outer"}/2,$parameters{"frame2_outer"}/2,$parameters{"frame2_outer"}/2,$parameters{"frame3_outer"}/2,$parameters{"frame3_outer"}/2);
my @frame_height_half=($parameters{"frame1_height"}/2,$parameters{"frame2_height"}/2,$parameters{"frame2_height"}/2,$parameters{"frame3_height"}/2,$parameters{"frame3_height"}/2);

sub solid_PVDIS_gem_geometry
{
make_gem();
}

sub make_gem
{
# refer  to https://hallaweb.jlab.org/wiki/index.php/Solid_Tracking#GEM_module.27s_geometry_and_material

my $Nlayer = 24;
my @layer_thickness =
(0.005,0.02,3,0.05,0.005,3,0.005,0.05,0.005,2,0.005,0.05,0.005,2,0.005,0.05,0.005,2,0.01,0.05,0.18,3,0.02,0.005);  # in mm

my $Dz   = 0;
$Dz += $_ for @layer_thickness;
$Dz = int($Dz*5000)/10000.0;  # half thickness in mm
# 0.005+0.02+3+0.05+0.005+3+0.005+0.05+0.005+2+0.005+0.05+0.005+2+0.005+0.05+0.005+2+0.01+0.05+0.18+3+0.02+0.005=15.525

my @material =
("G4_Al","SL_gem_mylar","SL_gem_GEMgas","SL_gem_Kapton","G4_Cu","SL_gem_GEMgas","G4_Cu","SL_gem_Kapton","G4_Cu","SL_gem_GEMgas","G4_Cu","SL_gem_Kapton","G4_Cu","SL_gem_GEMgas","G4_Cu","SL_gem_Kapton","G4_Cu","SL_gem_GEMgas","G4_Cu","SL_gem_Kapton","SL_gem_NEMAG10","SL_gem_GEMgas","SL_gem_mylar","G4_Al");
my $color_NEMAG10 = "00ffdd";
my $color_Al_front = "00ff00";
my $color_Al_back = "ddse00";
my $color_mylar = "ffse14";
my $color_Copper = "ffe731";
my $color_Kapton = "1a4fff";
my $color_gas = "ff33fc"; 
my @color = ($color_Al_front,$color_mylar,$color_gas,$color_Kapton,$color_Copper,$color_gas,$color_Copper,$color_Kapton,$color_Copper,$color_gas,$color_Copper,$color_Kapton,$color_Copper,$color_gas,$color_Copper,$color_Kapton,$color_Copper,$color_gas,$color_Copper,$color_Kapton,$color_NEMAG10,$color_gas,$color_mylar,$color_Al_back);
my @hittype = ("no","no","no","no","solid_gem","solid_gem","solid_gem","no","solid_gem","solid_gem","solid_gem","no","no","no","no","no","no","no","solid_gem","no","no","no","no","no");

 for(my $n=1; $n<=$Nplate; $n++)
 {
    my $Rin_tube=$Rin[$n-1]-5; #Rin match 
    my $Rout_tube=$Rin[$n-1]+$frame_height_half[$n-1]/10*2+5;
       
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "111111";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin_tube*cm $Rout_tube*cm $Dz*mm 0*deg 360*deg";
    $detector{"material"}   = "G4_AIR";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);

    for( my $sec = 1; $sec <= $Nsect[$n-1]; $sec++ ){
    
      # sec1 start from 90 deg in phi
      my $sec_pos_rot = (90 + ($sec+0.5-1) * $angle_width[$n-1] + $offrot[$n-1]);    

      my $sec_center = $Rin[$n-1]*10+$gem_height_half[$n-1];	#assume Rin matches gem inner, not frame inner
      my $sec_pos_x = $sec_center * cos($sec_pos_rot/180*3.1416);
      my $sec_pos_y = $sec_center * sin($sec_pos_rot/180*3.1416);      
      
      my $sec_rot = - (180 + ($sec+0.5-1) * $angle_width[$n-1] + $offrot[$n-1]);
      
	    my %detector=init_det();
	    $detector{"name"}        = "$DetectorName\_$n\_$sec";
	    $detector{"mother"}      = "$DetectorName\_$n";
	    $detector{"description"} = $detector{"name"};
	    $detector{"pos"}        = "$sec_pos_x*mm $sec_pos_y*mm 0*mm ";
	    $detector{"rotation"}   = "-90*deg $sec_rot*deg 0*deg";	    
# 	    $detector{"rotation"}   = "-90*deg 0*deg 0*deg";
# 	    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
	    $detector{"color"}      = "$color_Kapton";
	    $detector{"type"}        = "Trd";
	    $detector{"dimensions"}  = "$frame_inner_half[$n-1]*mm $frame_outer_half[$n-1]*mm $Dz*mm $Dz*mm  $frame_height_half[$n-1]*mm";   
	    $detector{"material"}   = "SL_gem_NEMAG10";
	    $detector{"mfield"}     = "no";
	    $detector{"ncopy"}      = 1;
	    $detector{"pMany"}       = 1;
	    $detector{"exist"}       = 1;
	    $detector{"style"}       = 0;
	    $detector{"sensitivity"} = "no";
	    $detector{"hit_type"}    = "no";
	    $detector{"identifiers"} = "no";
	    print_det(\%configuration, \%detector);    

    
      for(my $i=1; $i<=$Nlayer; $i++)
      {
	my $layer_pos = -$Dz;
	for(my $k=1; $k<=$i-1; $k++)
	{	
	   $layer_pos = $layer_pos+$layer_thickness[$k-1];
	}
	$layer_pos = $layer_pos+$layer_thickness[$i-1]/2;
		
	my $Dlayer=$layer_thickness[$i-1]/2;

	    my %detector=init_det();
	    $detector{"name"}        = "$DetectorName\_$n\_$sec\_$i";
	    $detector{"mother"}      = "$DetectorName\_$n\_$sec";
	    $detector{"description"} = $detector{"name"};
	    $detector{"pos"}        = "0*mm $layer_pos*mm 0*mm ";
	    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
	    $detector{"color"}      = "$color[$i-1]";
	    $detector{"type"}        = "Trd";
	    $detector{"dimensions"}  = "$gem_inner_half[$n-1]*mm $gem_outer_half[$n-1]*mm $Dlayer*mm $Dlayer*mm  $gem_height_half[$n-1]*mm";   
	    $detector{"material"}   = "$material[$i-1]";
	    $detector{"mfield"}     = "no";
	    $detector{"ncopy"}      = 1;
	    $detector{"pMany"}       = 1;
	    $detector{"exist"}       = 1;
	    $detector{"style"}       = 1;
	    $detector{"sensitivity"} = "$hittype[$i-1]";
	    $detector{"hit_type"}    = "$hittype[$i-1]";
	    my $id=1000000+$n*100000+$sec*1000+$i;
	    $detector{"identifiers"} = "id manual $id";
	    print_det(\%configuration, \%detector);
	}
    }
 }
}
1;
