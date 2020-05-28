use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_SIDIS_target_NH3_block';

my $DetectorMother="root";

sub solid_SIDIS_target_NH3_block
{
 my $NUM  = 2;
#  my @z    = (30,30);
 my @z    = (35,35);
 my @y    = (15+2,-15-2); 
 my @rot    = (90,-90); 
#  my @Rin  = (1.5,1.5);
#  my @Rout = (30,30);
 my @Dz   = (15,15);
 my @name = ("1","2"); 
 my @mother = ("solid_SIDIS_target_NH3_field","solid_SIDIS_target_NH3_field");
 my @mat  = ("SL_target_NH3_TungstenPowder","SL_target_NH3_TungstenPowder");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
     my %detector=init_det(); 
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm $y[$n-1]*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "$rot[$n-1]*deg 0*deg 0*deg";
#     $detector{"type"}       = "Tube";
#     $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"type"}        = "Trd";
#     $detector{"dimensions"}  = "4.7*cm 2*cm 4.7*cm 2*cm $Dz[$n-1]*cm";   #regular
#     $detector{"dimensions"}  = "2.35*cm 1*cm 2.35*cm 1*cm $Dz[$n-1]*cm";  #small
#     $detector{"dimensions"}  = "4.7*cm 2*cm 2.35*cm 1*cm $Dz[$n-1]*cm";   #small z
#     $detector{"dimensions"}  = "9.4*cm 4*cm 9.4*cm 4*cm $Dz[$n-1]*cm";   #large
    $detector{"dimensions"}  = "4.7*cm 2*cm 9.4*cm 4*cm $Dz[$n-1]*cm";   #large z
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;  # style 0 shows only borders
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }
}

# sub solid_SIDIS_target_NH3_block
# {
#  my $NUM  = 2;
#  my @z    = (30,50);
#  my @Rin  = (1.5,2.5);
#  my @Rout = (60,60);
#  my @Dz   = (0.05,0.05);
#  my @name = ("1","2"); 
#  my @mother = ("solid_SIDIS_target_NH3_field","solid_SIDIS_target_NH3_field");
#  my @mat  = ("G4_Galactic","G4_Galactic");
#  
#  for(my $n=1; $n<=$NUM; $n++)
#  {
# #     my $pnumber     = cnumber($n-1, 10);
#      my %detector=init_det(); 
#     $detector{"name"}        = "$DetectorName\_$name[$n-1]";
#     $detector{"mother"}      = "$mother[$n-1]" ;
#     $detector{"description"} = "$DetectorName\_$name[$n-1]";
#     $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
#     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
#     $detector{"type"}       = "Tube";
#     $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
#     $detector{"material"}   = $mat[$n-1];
#     $detector{"mfield"}     = "no";
#     $detector{"ncopy"}      = 1;
#     $detector{"pMany"}       = 1;
#     $detector{"exist"}       = 1;
#     $detector{"visible"}     = 1;
#     $detector{"style"}       = 1;  # style 0 shows only borders
#     $detector{"sensitivity"} = "flux";
#     $detector{"hit_type"}    = "flux";
#     $detector{"identifiers"} = "id manual $n";
#     print_det(\%configuration, \%detector);
#  }
# }

