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
my $target_length = 40;

#Carbon target
my $target_length_C = 0.01*2.54;

# carbon optics target run
# my @y    = (0,0,(1.125/2-0.688/2)*2.54,(1.125/2-0.688/2)*2.54);  #beam pass through pos1 foil center, and pos4 and pos6

# carbon hole target run
my @y    = (0,-(0.906-0.688/2)*2.54,-(0.906-1.125/2)*2.54,-(0.906-1.125/2)*2.54);  #beam pass through pos4 and pos6 holes

# carbon foil target run
# my @y    = ???  #beam pass through pos4 and pos6 top

sub beamline
{
make_beam_entrance();
make_beam_exit();
make_beam_exit_long();
# make_beam_coolgas_NOtarget();
# make_beam_coolgas_He3();
make_beam_coolgas_carbon();
make_beam_coolgas_carbon_hole();
}

sub make_beam_entrance
{
# upstream Be window .01thk, 12.80 inch from target center at pivot,and 0.0002" thk Al cover, inner diameter 2.067" outter diameter 2.375", length 200cm
 my @z    = (-12.80*2.54-100,0,-100+0.01*2.54/2,100-0.0002*2.54-0.01*2.54/2,100-0.0002*2.54/2);
 my @Rin  = (0.,0.,0.,0.,0);
 my @Rout = (2.375/2*2.54,2.067/2*2.54,2.067/2*2.54,2.067/2*2.54,2.067/2*2.54);
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
}

sub make_beam_exit
{
# downstream Be window .02thk, 17.25 inch from target center at pivot,and 0.001" thk Al cover, inner diameter 2.067" outter diameter 2.375"
 my @z    = (17.25*2.54+100,0,-100+0.001*2.54/2,-100+0.001*2.54+0.02*2.54/2,100-0.02*2.54/2,);
 my @Rin  = (0.,0.,0.,0.,0);
 my @Rout = (2.375/2*2.54,2.067/2*2.54,2.067/2*2.54,2.067/2*2.54,2.067/2*2.54);
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
}

sub make_beam_exit_long
{
 my @z    = (17.25*2.54+100*2+800,0);
 my @Rin  = (0.,0.);
 my @Rout1 = (2.375/2*2.54,2.067/2*2.54);
 my @Rout2 = (10.375/2*2.54,10.067/2*2.54); 
 my @Dz   = (800,800);

 my $NUM  = 2; 
 my @name = ("exit_long_outer","exit_long_inner"); 
 my @mother=("$DetectorMother","$DetectorName\_exit_long_outer");
 my @mat  = ("G4_Al","G4_Galactic");
 my @color = ("ff00ff","808080");

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
    $detector{"type"}       = "Cons";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout1[$n-1]*cm $Rin[$n-1]*cm $Rout2[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
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
}

sub make_beam_coolgas_NOtarget
{
# upstream Be window .01thk, 12.80 from TC, downstream Be window .02thk, 17.25 from TC
# filled with N2 gas
 my $NUM  = 1;
 my @z    = ((-12.80+17.25)*2.54/2);
 my @Rin  = (0.);
 my @Rout = (75);
 my @Dz   = ((12.80+17.25)*2.54/2);
 my @name = ("coolgas_everywhere"); 
 my @mother = ("$DetectorMother");
 my @mat  = ("G4_N");
 my @color = ("808088");
 
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
    $detector{"ncopy"}      = 1;
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

sub make_beam_coolgas_He3
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
 my @mat  = ("G4_N","G4_N","G4_N");
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
    $detector{"ncopy"}      = 1;
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
# filled with N2 gas and Carbon foils 0.01" thk at z=-200,0,133.35mm https://logbooks.jlab.org/entry/3750828 https://logbooks.jlab.org/entry/3820241
# assume pos 1 has "carbon target", pos 4 and 6 has "carbon target with hole short"
# carbon foil https://hallcweb.jlab.org/wiki/images/9/9e/67507-00087-1.pdf
# more details: From the model I (Silviu) got from Bert the distance between Optics 1 and Optics 4 is 200 mm, between Optics 4 and Optics 6 is 133.35 mm and all foils have the same thickness, 0.254 mm, made of graphite. Optics 1 is supposed to be at the z of the upstream glass cell beam window, Optics 4 is supposed to be at the mid point of glass cell along the beam line. The original 7 Optics foils were supposed to be equidistant along the beam line from the z of the US glass cell beam window to the DS beam window, spanning 40 cm, for a distance between adjacent foils of 400/6 = 66.67 mm. I guess the spokespeople decided that they only need foils 1, 4 and 6

 my $coolgas_z=(-12.80*2.54+17.25*2.54)/2;
 my $NUM  = 4;
 my @z    = ($coolgas_z,-20-$coolgas_z,0-$coolgas_z,13.335-$coolgas_z);
 my @Dx = (75,0.625/2*2.54,0.625/2*2.54,0.625/2*2.54);
 my @Dy = (75,0.688/2*2.54,1.125/2*2.54,1.125/2*2.54);
 my @Dz   = ((12.80*2.54+17.25*2.54)/2-0.1,$target_length_C/2,$target_length_C/2,$target_length_C/2);
 my @name = ("coolgas","target_carbon1","target_carbon2","target_carbon3"); 
 my @mother = ("$DetectorMother","$DetectorName\_coolgas","$DetectorName\_coolgas","$DetectorName\_coolgas");
 my @mat  = ("G4_N","G4_GRAPHITE","G4_GRAPHITE","G4_GRAPHITE");
 my @color = ("808088","101011","101011","101011");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm $y[$n-1]*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = "$Dx[$n-1]*cm $Dy[$n-1]*cm $Dz[$n-1]*cm";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
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

sub make_beam_coolgas_carbon_hole
{
 my @y_hole   = ((0.906-1.125/2)*2.54,(0.906-1.125/2)*2.54);

 my $NUM  = 2;
 my @Rin  = (0,0);
 my @Rout = (0.039/2*2.54,0.039/2*2.54);
 my @Dz   = ($target_length_C/2,$target_length_C/2);
 my @name = ("target_carbon2_hole","target_carbon3_hole"); 
 my @mother = ("$DetectorName\_target_carbon2","$DetectorName\_target_carbon3");
 my @mat  = ("G4_N","G4_N");
 my @color = ("808088","808088");
 
 for(my $n=1; $n<=$NUM; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    $detector{"mother"}      = "$mother[$n-1]" ;
    $detector{"description"} = "$DetectorName\_$name[$n-1]";
    $detector{"pos"}        = "0*cm $y_hole[$n-1]*cm 0*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = $color[$n-1];
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
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