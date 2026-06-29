use strict;
use warnings;

use lib ("$ENV{GEMC}/io");
use lib ("$ENV{GEMC}/api/perl");

use geometry;

our %configuration;

# Four 16-channel MRPC modules in GEMC Perl geometry.
# Updated to use an overall detector mother size of 38.4 x 30.9 x 3.5 cm.
# Internal layer lengths/widths are adjusted to fit this envelope.
# Gas gaps are passive by default for safe geometry testing.

my $DetectorBaseName = "solid_mrpc16";
my $DetectorMother   = "cc_pro_tcd";

my $MAKE_GAPS_SENSITIVE = 1;
my $HIT_TYPE = "solid_mrpc";  # use "mrpc" only after registering a C++ MRPC hit process

# Local positions inside cc_pro_tcd. Adjust as needed.
my @detector_pos = (
    [0.0,  0.0, -128.51],
    [0.0,  0.0, -122.79],
    [0.0,  0.0, 131.53],
    [0.0,  0.0, 137.24],
);

# Layer thicknesses from eTOF macro, cm.
my $thickness_gap          = 0.025;
my $thickness_readoutstrip = 0.0035;
my $thickness_glass        = 0.07;
my $thickness_innerglass   = 0.05;
my $thickness_PCB          = 0.08;
my $thickness_mylar        = 0.025;
my $thickness_electrode    = 0.0005;
# Choose honeycomb thickness so the full physical MRPC stack is 3.5 cm thick.
my $thickness_honeycomb    = 1.02875;

my $thickness_MRPC =
      $thickness_gap*10
    + $thickness_readoutstrip*3
    + $thickness_glass*8
    + $thickness_innerglass*4
    + $thickness_PCB*4
    + $thickness_mylar*4
    + $thickness_electrode*4
    + $thickness_honeycomb*2;

# Lengths in x direction, cm. Overall detector/mother x size is 38.4 cm.
my $length_gap          = 38.4;
my $length_glass1       = 38.4;
my $length_glass2       = 38.4;
my $length_readoutstrip = 38.4;
my $length_PCB          = 38.4;
my $length_mylar        = 38.4;
my $length_electrode    = 38.4;
my $length_honeycomb    = 38.4;

# 16-channel MRPC dimensions in y direction, cm. Overall detector/mother y size is 30.9 cm.
my $width_readoutstrip  = 1.5;
my $width_stripgap      = 0.2;
my $width_gap       = 28.5;
my $width_glass1    = 28.5;
my $width_glass2    = 30.9;
my $width_PCB       = 30.9;
my $width_mylar     = 30.9;
my $width_electrode = 28.5;
my $width_honeycomb = 30.9;
my $n_channel       = 16;

my %color = (
    "RPCgas"    => "ffffff",
    "RPCglass"  => "6699ff",
    "copper"    => "ff9900",
    "carbon"    => "222222",
    "mylar"     => "ff66cc",
    "pcbmvd"    => "00aa44",
    "honeycomb" => "ffaa00",
    "G4_AIR"    => "aaaaaa",
);

sub set_common
{
    my ($d) = @_;
    $d->{"rotation"} = "0*deg 0*deg 0*deg" unless defined $d->{"rotation"};
    $d->{"mfield"}   = "no";
    $d->{"ncopy"}    = 1;
    $d->{"pMany"}    = 0;
    $d->{"exist"}    = 1;
    $d->{"visible"}  = 1 unless defined $d->{"visible"};
    $d->{"style"}    = 1 unless defined $d->{"style"};
    $d->{"sensitivity"} = "no" unless defined $d->{"sensitivity"};
    $d->{"hit_type"}    = "no" unless defined $d->{"hit_type"};
    $d->{"identifiers"} = "no" unless defined $d->{"identifiers"};
}

sub print_checked_det
{
    my ($d) = @_;
    foreach my $k (qw(name mother description pos rotation color type dimensions material mfield ncopy pMany exist visible style sensitivity hit_type identifiers)) {
        if (!defined $d->{$k}) { print "MISSING: $k in $d->{name}\n"; }
        elsif ($d->{$k} eq "") { print "EMPTY: $k in $d->{name}\n"; }
    }
    print_det(\%configuration, $d);
}

sub add_box
{
    my ($name, $mother, $description, $x, $y, $z, $hx, $hy, $hz, $mat, $col, $sensitive, $sector, $layer, $component) = @_;
    my %detector = init_det();
    $detector{"name"}        = $name;
    $detector{"mother"}      = $mother;
    $detector{"description"} = $description;
    $detector{"pos"}         = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}    = "0*deg 0*deg 0*deg";
    $detector{"color"}       = $col;
    $detector{"type"}        = "Box";
    $detector{"dimensions"}  = "$hx*cm $hy*cm $hz*cm";
    $detector{"material"}    = $mat;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    if ($sensitive) {
        $detector{"sensitivity"} = $HIT_TYPE;
        $detector{"hit_type"}    = $HIT_TYPE;
        $detector{"identifiers"} = "sector manual $sector layer manual $layer component manual $component";
    }
    set_common(\%detector);
    print_checked_det(\%detector);
}

sub make_one_mrpc16
{
    my ($module_index, $x0, $y0, $z0) = @_;
    my $sector = $module_index + 1;
    my $DetectorName = "${DetectorBaseName}_${sector}";

    # Overall detector/mother size: 38.4 x 30.9 x 3.5 cm.
    # Do not add the previous 0.10 cm air margin here, so the mother volume matches the requested size.
    my $mother_hx = 38.4/2.0;
    my $mother_hy = 30.9/2.0;
    my $mother_hz = 3.5/2.0;

    add_box($DetectorName, $DetectorMother, "16-channel MRPC module $sector mother volume",
        $x0, $y0, $z0, $mother_hx, $mother_hy, $mother_hz, "G4_AIR", "aaaaaa", 0, $sector, 0, 0);

    my $position_PCB1 = 4*$thickness_innerglass + 2*$thickness_glass + 5*$thickness_gap
        + 2*($thickness_mylar+$thickness_electrode) + 3*$thickness_PCB/2.0 + 3*$thickness_readoutstrip/2.0;
    my $position_PCB2 = $thickness_PCB/2.0 + $thickness_readoutstrip/2.0;
    my $position_mylar1 = $thickness_PCB + 0.5*$thickness_readoutstrip + 0.5*$thickness_mylar;
    my $position_mylar2 = 0.5*$thickness_PCB + $thickness_readoutstrip + 0.5*$thickness_mylar;
    my $position_electrode1 = $position_mylar1 + 0.5*$thickness_mylar + 0.5*$thickness_electrode;
    my $position_electrode2 = $position_mylar2 + 0.5*$thickness_mylar + 0.5*$thickness_electrode;
    my $position_readout = 0.5*($thickness_PCB+$thickness_readoutstrip);
    my $position_honeycomb = $position_PCB1 + 0.5*($thickness_PCB+$thickness_honeycomb);
    my $position_gap = $position_electrode1 + 0.5*($thickness_electrode+$thickness_gap) + $thickness_glass;
    my $position_glass2  = 0.5*($thickness_glass+$thickness_electrode);
    my $position_glass2o = $position_mylar2 + $thickness_mylar/2.0 + $thickness_glass/2.0;

    my @pcb_z = ($position_PCB1, $position_PCB2, -$position_PCB2, -$position_PCB1);
    for (my $i=0; $i<@pcb_z; $i++) {
        add_box("${DetectorName}_PCB_" . ($i+1), $DetectorName, "MRPC16 PCB layer", 0, 0, $pcb_z[$i],
            $length_PCB/2, $width_PCB/2, $thickness_PCB/2, "pcbmvd", $color{"pcbmvd"}, 0, $sector, 0, $i+1);
    }

    my @mylar_z = ($position_mylar1, -$position_mylar1, $position_PCB1-$position_mylar2, $position_mylar2-$position_PCB1);
    for (my $i=0; $i<@mylar_z; $i++) {
        add_box("${DetectorName}_mylar_" . ($i+1), $DetectorName, "MRPC16 mylar layer", 0, 0, $mylar_z[$i],
            $length_mylar/2, $width_mylar/2, $thickness_mylar/2, "mylar", $color{"mylar"}, 0, $sector, 0, $i+1);
    }

    my @electrode_z = ($position_electrode1, -$position_electrode1, $position_PCB1-$position_electrode2, $position_electrode2-$position_PCB1);
    for (my $i=0; $i<@electrode_z; $i++) {
        add_box("${DetectorName}_electrode_" . ($i+1), $DetectorName, "MRPC16 carbon electrode", 0, 0, $electrode_z[$i],
            $length_electrode/2, $width_electrode/2, $thickness_electrode/2, "carbon", $color{"carbon"}, 0, $sector, 0, $i+1);
    }

    my $start_readout = -$width_gap/2.0 + ($width_gap - $n_channel*($width_readoutstrip+$width_stripgap))/2.0 + $width_readoutstrip/2.0;
    my $readout_copy = 0;
    for (my $j=1; $j<=2; $j++) {
        my $zsign = ($j == 1) ? -1.0 : 1.0;
        my $zstrip = ($position_PCB1 - $position_readout) * $zsign;
        for (my $i=1; $i<=$n_channel; $i++) {
            $readout_copy++;
            my $ystrip = $start_readout + ($width_readoutstrip+$width_stripgap)*($i-1);
            add_box("${DetectorName}_readout_${readout_copy}", $DetectorName, "MRPC16 readout strip", 0, $ystrip, $zstrip,
                $length_readoutstrip/2, $width_readoutstrip/2, $thickness_readoutstrip/2, "copper", $color{"copper"}, 0, $sector, $j, $i);
        }
    }
    for (my $i=1; $i<=$n_channel; $i++) {
        $readout_copy++;
        my $ystrip = $start_readout + ($width_readoutstrip+$width_stripgap)*($i-1);
        add_box("${DetectorName}_readout_${readout_copy}", $DetectorName, "MRPC16 central readout strip", 0, $ystrip, 0,
            $length_readoutstrip/2, $width_readoutstrip/2, $thickness_readoutstrip/2, "copper", $color{"copper"}, 0, $sector, 3, $i);
    }

    my @honeycomb_z = ($position_honeycomb, -$position_honeycomb);
    for (my $i=0; $i<@honeycomb_z; $i++) {
        add_box("${DetectorName}_honeycomb_" . ($i+1), $DetectorName, "MRPC16 honeycomb support", 0, 0, $honeycomb_z[$i],
            $length_honeycomb/2, $width_honeycomb/2, $thickness_honeycomb/2, "honeycomb", $color{"honeycomb"}, 0, $sector, 0, $i+1);
    }

    my $gap_copy = 0;
    for (my $j=1; $j<=2; $j++) {
        my $zsign = ($j == 1) ? -1.0 : 1.0;
        for (my $i=1; $i<=5; $i++) {
            $gap_copy++;
            my $zgap = ($position_gap + ($thickness_gap+$thickness_innerglass)*($i-1)) * $zsign;
            add_box("${DetectorName}_gap_${gap_copy}", $DetectorName, "MRPC16 RPC gas gap", 0, 0, $zgap,
                $length_gap/2, $width_gap/2, $thickness_gap/2, "RPCgas", $color{"RPCgas"}, $MAKE_GAPS_SENSITIVE, $sector, $gap_copy, 1);
        }
    }

    my @glass2_z = ($position_electrode1 + $position_glass2, -($position_electrode1 + $position_glass2), $position_PCB1 - $position_glass2o, $position_glass2o - $position_PCB1);
    for (my $i=0; $i<@glass2_z; $i++) {
        add_box("${DetectorName}_glass2_" . ($i+1), $DetectorName, "MRPC16 outer glass layer", 0, 0, $glass2_z[$i],
            $length_glass2/2, $width_glass2/2, $thickness_glass/2, "RPCglass", $color{"RPCglass"}, 0, $sector, 0, $i+1);
    }

    my $glass1_copy = 0;
    for (my $j=1; $j<=2; $j++) {
        my $zsign = ($j == 1) ? -1.0 : 1.0;
        for (my $i=1; $i<=4; $i++) {
            $glass1_copy++;
            my $zglass = ($position_glass2 + $position_electrode1 - $thickness_innerglass/2.0 + $thickness_glass/2.0 + $i*($thickness_innerglass+$thickness_gap)) * $zsign;
            add_box("${DetectorName}_glass1_${glass1_copy}", $DetectorName, "MRPC16 inner glass layer", 0, 0, $zglass,
                $length_glass1/2, $width_glass1/2, $thickness_innerglass/2, "RPCglass", $color{"RPCglass"}, 0, $sector, 0, $glass1_copy);
        }
    }
}

sub make_mrpc16_4modules
{
    for (my $imod = 0; $imod < @detector_pos; $imod++) {
        make_one_mrpc16($imod, $detector_pos[$imod][0], $detector_pos[$imod][1], $detector_pos[$imod][2]);
    }
}

make_mrpc16_4modules();

1;
