use strict;
use warnings;

use lib ("$ENV{GEMC}/io");
use lib ("$ENV{GEMC}/api/perl");

use geometry;

our %configuration;

# --------------------------------------------------------------------------
# SoLID beam-test uRWell geometry using LMU-style Box volumes.
#
# This version keeps the SoLID placement inside cc_pro_tcd and the existing
# urwell hit/bank/material files, but changes the geometry to match the
# uploaded LMU volume style:
#   - transverse half-size:    5.1 cm x 5.1 cm
#   - compact mother half-Z:   0.50 cm
#   - compact region half-Z:   0.48 cm
#   - all internal layers are Box volumes with LMU half-thicknesses
#   - layer z positions are calculated by thickness accumulation, centered at z = 0
#
# It uses the LMU uRWell stack, i.e. the region2/region3/region4/region5 style
# with muRwell, dlc, capacitive sharing layers, and readout layers.
# --------------------------------------------------------------------------

my $DetectorBaseName = "solid_urwell";
my $DetectorMother   = "cc_pro_tcd";

# Positions of the three uRWell modules inside cc_pro_tcd.
# These are local coordinates relative to cc_pro_tcd.
my $x0 = 0;
my $y0 = 0;

my @module_z = (
    71.12 + 17.34,
    71.12 + 45.76,
    71.12 + 52.82,
);

# Keep the beam-test orientation choice from the previous SoLID file:
# only the second physical module is flipped.
#
# For LMU Box geometry, flipping is implemented by changing z -> -z for the
# internal layer positions, so the layer stack faces the opposite direction.
my @module_flipped = (
    0,
    1,
    0,
);

# LMU transverse dimensions, all are half-dimensions in cm.
my $lmu_hx = 5.1;
my $lmu_hy = 5.1;

# Compact SoLID mother/region Z sizes.
# These remove the large empty LMU container space but keep the real LMU layer
# thicknesses and transverse size.
my $lmu_mother_hz = 0.50;
my $lmu_region_hz = 0.48;

my %color = (
    "kapton" => "bf0000",
    "Al"     => "2a3158",
    "gas"    => "afb0ba",
    "Cu"     => "fd7f00",
    "dlc"    => "14b6ce",
    "glue"   => "14ce3d",
    "g10"    => "aa44d8",
    "G4_AIR" => "aaaaaa"
);

# LMU uRWell internal layer table from lmu__volumes_default.txt.
# The third value is the full layer thickness in cm.
# This version does not use the original LMU absolute z positions; instead,
# it centers the full stack by accumulating thickness from -total_thickness/2.
my @lmu_urwell_layers = (
    ["window",               "kapton", 0.00250],
    ["window",               "Al",     0.00050],
    ["window",               "gas",    0.30000],

    ["cathode",              "kapton", 0.00500],
    ["cathode",              "Cu",     0.00050],
    ["cathode",              "gas",    0.30000],

    ["muRwell",              "Cu",     0.00010],
    ["muRwell",              "kapton", 0.00500],

    ["dlc",                  "dlc",    0.00050],
    ["dlc",                  "glue",   0.00280],

    ["capa_sharing_layer1",  "Cu",     0.00090],
    ["capa_sharing_layer1",  "glue",   0.00280],

    ["capa_sharing_layer2",  "Cu",     0.00290],
    ["capa_sharing_layer2",  "glue",   0.00750],

    ["readout1",             "Cu",     0.00370],
    ["readout1",             "g10",    0.10000],
    ["readout1",             "Cu",     0.00370],

    ["readout2",             "glue",   0.01250],
    ["readout2",             "g10",    0.10000],
    ["readout2",             "Cu",     0.00370],
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
        if (!defined $d->{$k}) {
            print "MISSING: $k in $d->{name}\n";
        }
        elsif ($d->{$k} eq "") {
            print "EMPTY: $k in $d->{name}\n";
        }
    }

    print_det(\%configuration, $d);
}

sub add_box
{
    my ($name, $mother, $desc, $x, $y, $z, $hx, $hy, $hz, $mat, $sector, $layer, $component, $sensitive) = @_;

    my %detector = init_det();

    $detector{"name"}        = $name;
    $detector{"mother"}      = $mother;
    $detector{"description"} = $desc;
    $detector{"pos"}         = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}    = "0*deg 0*deg 0*deg";
    $detector{"color"}       = exists $color{$mat} ? $color{$mat} : "aaaaaa";
    $detector{"type"}        = "Box";
    $detector{"dimensions"}  = "$hx*cm $hy*cm $hz*cm";
    $detector{"material"}    = $mat;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;

    if ($sensitive) {
        $detector{"sensitivity"} = "urwell";
        $detector{"hit_type"}    = "urwell";
        $detector{"identifiers"} =
            "region manual 1 sector manual $sector chamber manual 1 layer manual $layer component manual $component";
    }

    set_common(\%detector);
    print_checked_det(\%detector);
}

sub make_urwell
{
    for (my $imod = 0; $imod < @module_z; $imod++)
    {
        my $sector = $imod + 1;
        my $DetectorName = "${DetectorBaseName}_${imod}";
        my $RegionName   = "${DetectorName}_region";
        my $z0 = $module_z[$imod];
        my $is_flipped = $module_flipped[$imod];

        # Whole uRWell module inside cc_pro_tcd, using LMU mother half-size.
        add_box(
            $DetectorName,
            $DetectorMother,
            "SoLID uRWell module $imod LMU-style compact mother volume",
            $x0, $y0, $z0,
            $lmu_hx, $lmu_hy, $lmu_mother_hz,
            "G4_AIR",
            $sector, 0, 0, 0
        );

        # Inner region volume, matching LMU regionN.
        add_box(
            $RegionName,
            $DetectorName,
            "SoLID uRWell module $imod LMU-style compact inner region",
            0, 0, 0,
            $lmu_hx, $lmu_hy, $lmu_region_hz,
            "G4_AIR",
            $sector, 0, 0, 0
        );

        # Internal LMU uRWell layers.
        # Calculate z positions by thickness accumulation, centered at z = 0.
        my @layers_this_module = $is_flipped ? reverse(@lmu_urwell_layers) : @lmu_urwell_layers;

        my $total_thickness = 0.0;
        foreach my $L (@layers_this_module) {
            my ($group, $mat, $thick) = @$L;
            $total_thickness += $thick;
        }

        my $z = -$total_thickness/2.0;

        for (my $i = 0; $i < @layers_this_module; $i++)
        {
            my ($group, $mat, $thick) = @{$layers_this_module[$i]};
            my $zhalf = $thick/2.0;
            my $zpos  = $z + $zhalf;
            $z += $thick;

            my $is_sensitive = 0;
            my $layer_id = 0;
            my $component_id = 0;

            # Keep the same sensitive layer as the previous SoLID uRWell file.
            if ($group eq "cathode" && $mat eq "gas") {
                $is_sensitive = 1;
                $layer_id = 1;
                $component_id = 1;
            }

            add_box(
                "${DetectorName}_${group}_${mat}_${i}",
                $RegionName,
                "uRWell module $imod LMU Box $group $mat layer",
                0, 0, $zpos,
                $lmu_hx, $lmu_hy, $zhalf,
                $mat,
                $sector, $layer_id, $component_id, $is_sensitive
            );
        }
    }
}

make_urwell();

1;
