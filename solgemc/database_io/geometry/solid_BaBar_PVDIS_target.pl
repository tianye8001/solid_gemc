#!/usr/bin/perl -w

use strict;

use lib ("$ENV{GEMC}/database_io");
use geo;
use geo qw($pi);

my $DetectorName = 'BaBar_PVDIS_target';

my $envelope = "solid_$DetectorName";
my $file     = "solid_$DetectorName.txt";

my $rmin      = 1;
my $rmax      = 1000000;

my %detector = ();    # hash (map) that defines the gemc detector
$detector{"rmin"} = $rmin;
$detector{"rmax"} = $rmax;

use Getopt::Long;
use Math::Trig;

# C -- Auxil: target center
# C
# GPARVOL02  'TARC'    0  'SOLE'    0.    0.   10.    0  'TUBE'  3   1.    1.    1.
# C

#virtual volume
sub make_detector
{
 $detector{"name"}        = "$DetectorName";
 $detector{"mother"}      = "root";
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}         = "0*cm 0*cm 10*cm";
 $detector{"rotation"}    = "0*deg 0*deg 0*deg";
 $detector{"color"}       = "ff0000";
# $detector{"type"}        = "Tube";
# my $Rin        = 0;
# my $Rout       = 30;
# my $Dz         = 400;
# $detector{"dimensions"}  = "$Rin*cm $Rout*cm $Dz*cm 0*deg 360*deg";

$detector{"type"}        = "Polycone";

$detector{"dimensions"}  = "0*deg 360*deg 8 0*cm 0*cm 0*cm 0*cm 0*cm 0*cm 0*cm 0*cm 1.25*cm 1.25*cm 5*cm 5*cm 1.5*cm 1.5*cm 29*cm 29*cm -325*cm -25*cm -25*cm  25*cm  25*cm 35*cm  275*cm  399*cm" ;

#$detector{"dimensions"}  = "0*deg 360*deg 7 0*cm 1.25*cm 0*cm 0*cm 5*cm 300*cm  0*cm 5*cm 349*cm 0*cm 1.5*cm 350*cm 0*cm 1.5*cm 360*cm 0*cm 29*cm 600*cm 0*cm 29*cm 724*cm" ;

# $detector{"type"}        = "Box";
# $detector{"dimensions"}  = "1.0*cm 1.0*cm 400*cm";

 $detector{"material"}    = "Vacuum";
 $detector{"mfield"}      = "no";
 $detector{"ncopy"}       = 1;
 $detector{"pMany"}       = 1;
 $detector{"exist"}       = 1;
 $detector{"visible"}     = 0;
 $detector{"style"}       = 1;
 $detector{"sensitivity"} = "no";
 $detector{"hit_type"}    = "";
 $detector{"identifiers"} = $detector{"name"};

 print_det(\%detector, $file);
}
make_detector();

# C --     Beam pipe: entrance
# C
# GPARVOL03  'BMP1'  209  'TARC'    0.    0. -175.    0  'TUBE'  3   0.    1.25    150.   
# GPARVOL04  'BMV1'  221  'BMP1'    0.    0.    0.    0  'TUBE'  3   0.    1.22    150.   
# GPARVOL05  'BMD1'   99  'BMV1'    0.    0. -149.9   0  'TUBE'  3   0.    1.22      0.1  
# C
sub make_target_PVDIS_beampipe1_entrance
{
 my $NUM  = 2;
 my @z    = (-175.0,-175.0);
 my @Rin  = (1.22,0.);
 my @Rout = (1.25,1.22);
 my @Dz   = (150.,150.);
 my @name = ("BMP1","BMV1"); 
 my @mat  = ("Aluminum","Vacuum");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
#    $detector{"mother"}      = "root" ;
    $detector{"mother"}      = "$DetectorName" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "00ff00";
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
    $detector{"hit_type"}    = "";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_target_PVDIS_beampipe1_entrance();

# C --     Beam pipe: exit
# C
# GPARVOL06  'BMP2'  209  'TARC'    0.    0.   30.    0  'TUBE'  3   0.    1.50      5.   
# GPARVOL07  'BMV2'  221  'BMP2'    0.    0.    0.    0  'TUBE'  3   0.    1.45      5.   
# GPARVOL08  'BMP3'  209  'TARC'    0.    0.  155.    0  'CONE'  5  120.  0.   1.50   0.  29.00  
# GPARVOL09  'BMV3'  221  'BMP3'    0.    0.    0.    0  'CONE'  5  120.  0.   1.45   0.  28.00  
# GPARVOL10  'BMP4'  209  'TARC'    0.    0.  335.    0  'TUBE'  3   0.   29.0      60.   
# GPARVOL11  'BMV4'  221  'BMP4'    0.    0.    0.    0  'TUBE'  3   0.   28.0      60.   
# GPARVOL12  'BMD4'   99  'BMV4'    0.    0.   59.5   0  'TUBE'  3   0.   28.    0.5
# C
sub make_target_PVDIS_beampipe2_exit
{
 my $NUM  = 2;
 my @z    = (30.,30.0);
 my @Rin  = (1.45,0.);
 my @Rout = (1.50,1.45);
 my @Dz   = (5.,5.);
 my @name = ("BMP2","BMV2"); 
 my @mat  = ("Aluminum","Vacuum");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    #$detector{"mother"}      = "root" ;
    $detector{"mother"}      = "$DetectorName" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "00ff00";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    if( $n == 1 ){
	$detector{"visible"}     = 1;
    } else {
	$detector{"visible"}     = 0;
    }
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_target_PVDIS_beampipe2_exit();

sub make_target_PVDIS_beampipe3_exit
{
 my $NUM  = 2;
 my @z    = (155.,155.0);
 my @Rmin1  = (1.45,0.);
 my @Rmax1 = (1.50,1.45);
 my @Rmin2  = (28.,0.);
 my @Rmax2 = (29.,28.);
 my @Dz   = (120.,120.);
 my @name = ("BMP3","BMV3"); 
 my @mat  = ("Aluminum","Vacuum");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
#    $detector{"mother"}      = "root" ;
    $detector{"mother"}      = "$DetectorName" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "00ff00";
    $detector{"type"}       = "Cons";
    $detector{"dimensions"} = "$Rmin1[$n-1]*cm $Rmax1[$n-1]*cm $Rmin2[$n-1]*cm $Rmax2[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    if( $n == 1 ){
	$detector{"visible"}     = 1;
    } else {
	$detector{"visible"}     = 0;
    }
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "none";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_target_PVDIS_beampipe3_exit();

sub make_target_PVDIS_beampipe4_exit
{
 my $NUM  = 3;
 my @z    = (335.,335.,335+60.5);
 my @Rin  = (28.,0.,0.);
 my @Rout = (29.,28.,28.);
 my @Dz   = (60.,60.,0.5);
 my @name = ("BMP4","BMV4","BMD4"); 
 my @mat  = ("Aluminum","Vacuum","Kryptonite");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
    #$detector{"mother"}      = "root" ;
    $detector{"mother"}      = "$DetectorName" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    if( $n != 3 ){
	$detector{"color"}      = "00ff00";
    } else {
	$detector{"color"}      = "ff0000";
    }
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = $n;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    if( $n != 2 ){
	$detector{"visible"}     = 1;
    } else {
	$detector{"visible"}     = 0;
    }
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "none";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_target_PVDIS_beampipe4_exit();

# C --     Target  ==================================
# C
# GPARVOL21  'TACH'  209  'TARC'    0.    0.    0.    0  'TUBE'  3   0.    5.00   25.00    
# GPARVOL22  'TACV'  221  'TACH'    0.    0.    0.    0  'TUBE'  3   0.    4.95   24.95    
# GPARVOL23  'TAW1'  221  'TACH'    0.    0.  -24.975 0  'TUBE'  3   0.    1.22    0.025   
# GPARVOL24  'TAW2'  221  'TACH'    0.    0.   24.975 0  'TUBE'  3   0.    1.50    0.025   
# GPARVOL25  'TALU'  209  'TACV'    0.    0.    0.    0  'TUBE'  3   0.    1.918  20.0     
# GPARVOL26  'TLH2'  201  'TALU'    0.    0.    0.    0  'TUBE'  3   0.    1.900  19.982   

sub make_target_PVDIS_target
{
 my $NUM  = 7;
 my @z    = (0.,  -24.975, 24.975,  0.,    19.991, -19.991,    0.);
 my @Rin  = (4.95,1.22,  1.5,     1.9,    0.0,      0.0,       0.);
 my @Rout = (5.,  5.0,   5.0,     1.918,  1.918, 1.918,      1.9);
 my @Dz   = (25., 0.025,0.025    ,19.982, 0.009, 0.009     ,19.982);

 my @name = ("TACH","TACW1","TACW2","TAW","TAW1", "TAW2","TAH2"); 
 my @mat  = ("Aluminum","Aluminum","Aluminum","Aluminum","Aluminum","Aluminum","LH2");

 for(my $n=1; $n<=$NUM; $n++)
 {
#     my $pnumber     = cnumber($n-1, 10);
    $detector{"name"}        = "$DetectorName\_$name[$n-1]";
#    $detector{"mother"}      = "root" ;
    $detector{"mother"}      = "$DetectorName" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm $z[$n-1]*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "ff0000";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin[$n-1]*cm $Rout[$n-1]*cm $Dz[$n-1]*cm 0*deg 360*deg";
    $detector{"material"}   = $mat[$n-1];
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      =  0;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "none";
    $detector{"identifiers"} = $detector{"name"};

    print_det(\%detector, $file);
 }
}
make_target_PVDIS_target();


