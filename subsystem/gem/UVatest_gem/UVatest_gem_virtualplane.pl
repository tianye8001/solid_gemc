use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'UVatest_gem_virtualplane';

my $DetectorMother="root";

sub UVatest_gem_virtualplane
{
make_gem_virtualplane();
}

my $Nplate	= 2;
my @PlateX = (0,0);  #position in X, unit cm
my @PlateY = (0,0);  #position in Y, unit cm
my @PlateZ = (99,101);  #position in Z, unit cm
my @Dx = (100/2,100/2);    #half length in X, unit cm
my @Dy = (100/2,100/2);     #half length in Y, unit cm
 
sub make_gem_virtualplane
{

 my $Dz   = 0.001/2; 
#  my $color="44ee11";

 for(my $n=1; $n<=$Nplate; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $PlateZ[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "CC6633";
#     $detector{"type"}       = "Tube";
#     $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz*cm 0*deg 360*deg";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = "$Dx[$n-1]*cm $Dy[$n-1]*cm $Dz*mm";
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
