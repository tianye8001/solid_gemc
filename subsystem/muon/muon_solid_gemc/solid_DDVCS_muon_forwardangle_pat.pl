#!/usr/bin/perl -w
use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

my $DetectorName = 'solid_DDVCS_muon_forwardangle_pat';
my $DetectorMother="root";

sub solid_DDVCS_muon_forwardangle_pat()
{
make_mu_detector();
make_PVC();
make_foam();
make_copper();
make_iron();
}

my $layers = 4; #number of iron layers which is 1 layer more than iron layers
my $z=5250; #z position (in mm) of the front face of first iron layer
my $iron_thickness = 360; #in mm

my $y = 0; #vertical position in mm of center of detector
my $foam_thickness = 5.3; #in mm
my $copper_thickness = 0.13; #width of copper strips in mm
my $gas_width = 9; #width of wire chamber in mm
my $comb_thickness = 1; #width of PVC comb in mm
my $units_per_layer = 14; #number of muon detectors units in one layer (in x-direction)
my $chambers_per_counter = 8; #number of wire chambers in one proportional counter
my $counter_width = ($chambers_per_counter * $gas_width) + (($chambers_per_counter + 1) * $comb_thickness); #length of proportional counter in mm
my $detector_length = 4870; #length of muon detector in mm 
my $distance_btwn_chambers = $gas_width + 2*$comb_thickness + 2*$copper_thickness + $foam_thickness;

#make wire chambers
sub make_mu_detector
{
 for(my $i=0; $i<$layers; $i++) {
 for(my $k=0; $k<$units_per_layer; $k++){
 for(my $n=0; $n < 3*$chambers_per_counter; $n++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_$i\_$k\_$n";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "aa0000";
    $detector{"type"}       = "Box";
    if ($n < $chambers_per_counter) 
          {$detector{"dimensions"} = ($gas_width/2)."*mm ".($detector_length/2)."*mm ".($gas_width/2)."*mm";
	   $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($comb_thickness+$gas_width/2)+($gas_width+$comb_thickness)*$n)."*mm $y*mm ".($z+$iron_thickness+$foam_thickness+$copper_thickness+$comb_thickness+($gas_width/2)+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";}
    if (($n >= $chambers_per_counter) && ($n < 2*$chambers_per_counter)) 
          {$detector{"dimensions"} = ($gas_width/2)."*mm ".($detector_length/2)."*mm ".($gas_width/2)."*mm";
	   $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($comb_thickness+$gas_width/2)+($gas_width+$comb_thickness)*($n-$chambers_per_counter))."*mm $y*mm ".($z+$iron_thickness+$foam_thickness+$copper_thickness+$comb_thickness+($gas_width/2)+$distance_btwn_chambers+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";}
    if (($n >= 2*$chambers_per_counter) && ($n < 3*$chambers_per_counter))     
          {$detector{"dimensions"} = ($gas_width/2)."*mm ".($detector_length/2)."*mm ".($gas_width/2)."*mm";
	   $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($comb_thickness+$gas_width/2)+($gas_width+$comb_thickness)*($n-2*$chambers_per_counter))."*mm $y*mm ".($z+$iron_thickness+$foam_thickness+$copper_thickness+$comb_thickness+($gas_width/2)+2*$distance_btwn_chambers+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";}


    $detector{"material"} = "G4_Ar";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "flux";
    $detector{"hit_type"}    = "flux";
    my $id=6100000+$k*100+$n;
    $detector{"identifiers"} = "id manual $id";
    print_det(\%configuration, \%detector);
 }}
}
}

sub make_foam
{
for(my $i=0; $i<$layers; $i++) {
 for(my $k=0; $k<$units_per_layer; $k++){
 for(my $n=0;$n<=3; $n++) {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_Foam_$i\_$k\_$n";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "ffa500";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = ($counter_width/2)."*mm ".($detector_length/2)."*mm ".($foam_thickness/2)."*mm";
    $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($counter_width/2))."*mm $y*mm ".(($z+$iron_thickness+$foam_thickness/2) + $n * ($distance_btwn_chambers)+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";
    $detector{"material"} = "G4_POLYSTYRENE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }}
}
}

sub make_PVC
{ 
for(my $i=0; $i<$layers; $i++) {
for(my $k=0; $k<$units_per_layer; $k++){

for(my $m=0;$m<3; $m++) {
 for(my $n=0; $n<=$chambers_per_counter; $n++)
 {

    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_PVC_vert_$i\_$k\_$m\_$n";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "123456";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = ($comb_thickness/2)."*mm ".($detector_length/2)."*mm ".($gas_width/2)."*mm";
    $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width) + ($comb_thickness/2) + $n*($gas_width+$comb_thickness))."*mm $y*mm ".($z+$iron_thickness+$foam_thickness+$copper_thickness+($comb_thickness/2) + $distance_btwn_chambers*$m+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";
   # print "layer =  $m   z = "$z+$s "  $x = $r \n";
    $detector{"material"} = "G4_POLYVINYL_CHLORIDE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }
 for(my $l=0; $l<2; $l++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_PVC_horiz_$i\_$k\_$m\_$l";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "123456";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = ($counter_width/2)."*mm ".($detector_length/2)."*mm ".($comb_thickness/2)."*mm";
    $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($counter_width/2))."*mm $y*mm ".($z+$iron_thickness+$foam_thickness+$copper_thickness+($comb_thickness/2)+($l*($gas_width+$comb_thickness) + ($m * $distance_btwn_chambers) + ($iron_thickness + 3*$distance_btwn_chambers + $foam_thickness)*$i))."*mm";
    $detector{"material"} = "G4_POLYVINYL_CHLORIDE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }
}}
}}

sub make_copper
{ 
for(my $i=0; $i<$layers; $i++) {
for(my $k=0; $k<$units_per_layer; $k++){

for(my $m=0;$m<3; $m++) {
 for(my $l=0; $l<2; $l++)
 {
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_copper_$i\_$k\_$m\_$l";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "ffdf00";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = ($counter_width/2)."*mm ".($detector_length/2)."*mm ".($copper_thickness/2)."*mm";
    $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($counter_width/2))."*mm $y*mm ".((($z+$iron_thickness+$foam_thickness+($copper_thickness/2))+$l*($copper_thickness + $gas_width + 2*$comb_thickness)) + ($distance_btwn_chambers*$m)+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";
    $detector{"material"} = "G4_Cu";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
 }
}}
}}

sub make_iron
{ 
  for(my $i=0; $i<$layers-1; $i++) {
    for(my $k=0; $k<$units_per_layer; $k++){
	
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_iron_$i\_$k";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = $detector{"name"};
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"} = "a9a9a9";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = ($counter_width/2)."*mm ".($detector_length/2)."*mm ".($iron_thickness/2)."*mm";
    $detector{"pos"}        = ((($k-$units_per_layer/2)*$counter_width)+($counter_width/2))."*mm $y*mm ".($z+($iron_thickness/2)+($iron_thickness+3*$distance_btwn_chambers+$foam_thickness)*$i)."*mm";
    $detector{"material"} = "G4_Fe";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}	     = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
    print_det(\%configuration, \%detector);
}}
}
