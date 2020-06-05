use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'beamline';

my $DetectorMother="root";

# my $z_target			= $parameters{"z_target"};

#He3 target
# my $target_length = 40;
# my $target_center = 0;

#Carbon target
my $target_length = 0.01*2.54;
my $target_center = -2.625*2.54;

sub beamline
{
make_beam_entrance();
make_beam_exit();
# make_beam_coolgas();
make_beam_coolgas_carbon();
}

sub make_beam_entrance
{
# upstream Be window .01thk, 12.80 inch from target center at pivot,and 0.0002" thk Al cover
 my @z    = (-12.80*2.54-100,0,-100+0.01*2.54/2,100-0.0002*2.54-0.01*2.54/2,100-0.0002*2.54/2);
 my @Rin  = (0.,0.,0.,0.,0);
 my @Rout = (2.375*2.54,2.067*2.54,2.067*2.54,2.067*2.54,2.067*2.54);
 my @Dz   = (100,100,0.01*2.54/2,0.01*2.54/2,0.0002*2.54/2);
 
 my $NUM  = 5;
 my @name = ("BMP1","BMV1","BMD1","BMW1","BMC1"); 
 my @mother = ("$DetectorMother","$DetectorName\_BMP1","$DetectorName\_BMV1","$DetectorName\_BMV1","$DetectorName\_BMV1"); 
 my @mat  = ("G4_Al","G4_Galactic","G4_Galactic","G4_Be","G4_Al");
 my @color = ("0000ff","808080","808080","00FFFF","FF00FF");

 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
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

sub make_beam_exit
{
# downstream Be window .02thk, 17.25 inch from target center at pivot,and 0.001" thk Al cover
 my @z    = (17.25*2.54+100,0,-100+0.001*2.54/2,-100+0.001*2.54+0.02*2.54/2,100-0.02*2.54/2,);
 my @Rin  = (0.,0.,0.,0.,0);
 my @Rout = (2.375*2.54,2.067*2.54,2.067*2.54,2.067*2.54,2.067*2.54);
 my @Dz   = (100,100,0.001*2.54/2,0.02*2.54/2,0.02*2.54/2,);

 my $NUM  = 5; 
 my @name = ("B3PP","B3PV","B3C1","B3W1","B3DM"); 
 my @mother=("$DetectorMother","$DetectorName\_B3PP","$DetectorName\_B3PV","$DetectorName\_B3PV","$DetectorName\_B3PV");
 my @mat  = ("G4_Al","G4_Galactic","G4_Al","G4_Be","G4_Galactic");
 my @color = ("0000ff","808080","FF00FF","00FFFF","808080");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
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


sub make_beam_coolgas
{
# upstream Be window .01thk, 12.80 from TC, downstream Be window .02thk, 17.25 from TC
# filled with N2 gas
 my $NUM  = 3;
 my @z    = ((-12.80*2.54-$target_length/2)/2,(17.25*2.54+$target_length/2)/2,0);
 my @Rin  = (0.,0.,1.1);
 my @Rout = (75,75,75);
 my @Dz   = ((12.80*2.54-$target_length/2)/2-0.1,(17.25*2.54-$target_length/2)/2-0.1,$target_length/2);
 my @name = ("coolgas_upstream","coolgas_downstream","coolgas_around"); 
 my @mother = ("$DetectorMother","$DetectorMother","$DetectorMother");
 my @mat  = ("SL_beamline_N2_1atm","SL_beamline_N2_1atm","SL_beamline_N2_1atm");
 my @color = ("808088","808088","808088");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
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
 }
}

sub make_beam_coolgas_carbon
{
# upstream Be window .01thk, 12.80 from TC, downstream Be window .02thk, 17.25 from TC
# filled with N2 gas and cabon coil at z=-2.635"
 my $NUM  = 3;
 my @z    = ((-12.80*2.54+$target_center-$target_length/2)/2,(17.25*2.54+$target_center+$target_length/2)/2,$target_center);
 my @Rin  = (0.,0.,0);
 my @Rout = (75,75,0.3*2.54);
 my @Dz   = ((12.80*2.54-$target_center+$target_length/2)/2-0.1,(17.25*2.54-$target_center-$target_length/2)/2-0.1,$target_length/2);
 my @name = ("coolgas_upstream","coolgas_downstream","target_carbon"); 
 my @mother = ("$DetectorMother","$DetectorMother","$DetectorMother");
 my @mat  = ("G4_N","G4_N","G4_C");
 my @color = ("808088","808088","101011");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
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
 }
}
