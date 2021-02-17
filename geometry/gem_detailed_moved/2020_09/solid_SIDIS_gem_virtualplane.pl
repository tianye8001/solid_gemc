use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_SIDIS_gem_virtualplane';

my $DetectorMother="root";

sub solid_SIDIS_gem_virtualplane
{
make_gem_virtualplane();
}

my $Nplate	= $parameters{"Nplate"};
 
# in cm
my @PlateZ = ($parameters{"PlateZ1"}-0.9,$parameters{"PlateZ2"}-0.9,$parameters{"PlateZ3"}-0.9,$parameters{"PlateZ4"}-0.9,$parameters{"PlateZ5"}-0.9,$parameters{"PlateZ6"}-0.9);
my @Rin    = ($parameters{"Rin1"},$parameters{"Rin2"},$parameters{"Rin3"},$parameters{"Rin4"},$parameters{"Rin5"},$parameters{"Rin6"});

#plane 1 and plane 2 using gem1, plane3 and plane4 use gem2, plane5 use gem1, plane6 use gem2
# in mm
my @frame_height_half=($parameters{"frame1_height"}/2,$parameters{"frame1_height"}/2,$parameters{"frame2_height"}/2,$parameters{"frame2_height"}/2,$parameters{"frame1_height"}/2,$parameters{"frame2_height"}/2);

sub make_gem_virtualplane
{
 my $Dz   = 0.001/2; 
#  my $color="44ee11";

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
    $detector{"color"}      = "CC6633";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin_tube*cm $Rout_tube*cm $Dz*cm 0*deg 360*deg";
    $detector{"material"}   = "G4_Galactic";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0;
    $detector{"sensitivity"} = "flux";
    $detector{"hit_type"}    = "flux";
    my $id=1000000+$n*100000+10000;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%configuration, \%detector);
 }
}
