use strict;
use warnings;

use lib ("$ENV{GEMC}/io");
use lib ("$ENV{GEMC}/api/perl");

use geometry;

our %configuration;

my $DetectorBaseName = "solid_urgroove";
my $DetectorMother   = "cc_pro_tcd";

# Keep manual SoLID-style geometry now.
# Later, if a uRGroove/uRWell volume table is available, set this to 1
# and fill get_volume_info() near the bottom.
my $USE_VOLUME_TABLE = 0;

# If you have a dedicated C++ hit process named "urgroove", keep this as urgroove.
# If you want to temporarily reuse the already-compiled uRWell hit process,
# you may set it to "urwell" for testing.
my $HIT_TYPE = "urgroove";
#my $HIT_TYPE = "no";

my $NMODULES = 2;

my $x0 = 0;
my $y0 = 0;

# Positions of the two uRGroove modules.
# These use the first two positions from the current uRWell geometry style.
# Adjust as needed.
my @module_z = (
      -71.12-38.66,
      -71.12-22.15,
);

# No flip by default.
my @module_flipped = (
    0,
    0,
);

# Match the LMU-style SoLID uRWell transverse size.
# Full transverse size = 10.2 cm x 10.2 cm.
my $manual_hx = 5.1;  # cm
my $manual_hy = 5.1;  # cm

# Compact SoLID uRGroove mother half-thickness.
# Similar to the compact SoLID uRWell geometry: keep a small container around
# the real material stack instead of the large LMU 2.8241 cm half-Z box.
my $urwell_mother_z_half = 0.50;  # cm

# uRGroove detail configuration.
my $drift_gap_cm        = 0.300;  # 3 mm
my $groove_depth_cm     = 0.005;  # 50 um
my $groove_top_width_cm = 0.007;  # 70 um
my $readout_pitch_cm    = 0.020;  # 200 um

# For 10.24 cm full width, this is about 512 strips.
my $approx_nstrips = int((2.0*$manual_hx)/$readout_pitch_cm + 0.5);

my %color = (
    "kapton"       => "bf0000",
    "Al"           => "2a3158",
    "urgroove_gas" => "afb0ba",
    "gas"          => "afb0ba",
    "Cu"           => "fd7f00",
    "dlc"          => "14b6ce",
    "glue"         => "14ce3d",
    "g10"          => "aa44d8"
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

sub make_urgroove
{
    my %detector;

    # Simplified uRGroove layer stack.
    #
    # Main difference from uRWell:
    #   - 3 mm drift gas layer is the sensitive ionization volume.
    #   - amplification zone is represented by a 50 um groove gas layer.
    #
    # The microscopic 70 um groove top width and 200 um readout pitch are stored
    # above as parameters for a future dedicated C++ uRGroove hit process. This
    # simplified Perl geometry does not instantiate hundreds of individual grooves.
    my @layers = (
        ["window",        "kapton",       0.005],
        ["window",        "Al",           0.002],

        ["drift",         "urgroove_gas", $drift_gap_cm],

        ["groove",        "urgroove_gas", $groove_depth_cm],
        ["groove_edge",   "kapton",       0.005],
        ["resistive",     "dlc",          0.001],

        ["readout1",      "Cu",           0.002],
        ["readout1",      "g10",          0.050],
        ["readout1",      "Cu",           0.002],

        ["readout2",      "glue",         0.005],
        ["readout2",      "g10",          0.050],
        ["readout2",      "Cu",           0.002],
    );

    my $total_thickness = 0.0;
    foreach my $L (@layers) {
        $total_thickness += $L->[2];
    }

    # Use compact uRWell-like mother half-thickness.
    # The uRGroove layers are already centered because z starts at -total_thickness/2.
    my $mother_z_half = $urwell_mother_z_half;

    for (my $imod = 0; $imod < $NMODULES; $imod++)
    {
        my $DetectorName = "${DetectorBaseName}_${imod}";
        my $z0 = $module_z[$imod];

        %detector = init_det();

        $detector{"name"}        = $DetectorName;
        $detector{"mother"}      = $DetectorMother;
        $detector{"description"} =
            "SoLID uRGroove module $imod mother; groove top ${groove_top_width_cm} cm; pitch ${readout_pitch_cm} cm; approx strips $approx_nstrips";
        $detector{"pos"}         = "$x0*cm $y0*cm $z0*cm";
        $detector{"rotation"}    = "0*deg 0*deg 0*deg";
        $detector{"color"}       = "00aaaa";
        $detector{"type"}        = "Box";
        $detector{"dimensions"}  = "$manual_hx*cm $manual_hy*cm $mother_z_half*cm";

        if ($USE_VOLUME_TABLE) {
            my ($type_from_table, $dim_from_table) =
                get_volume_info("mother", $imod, "mother", "air", 0, $module_flipped[$imod]);

            if (defined $type_from_table && defined $dim_from_table) {
                $detector{"type"}       = $type_from_table;
                $detector{"dimensions"} = $dim_from_table;
            }
        }

        $detector{"material"}    = "G4_AIR";
        $detector{"visible"}     = 1;
        $detector{"style"}       = 0;

        set_common(\%detector);
        print_checked_det(\%detector);

        my $is_flipped = $module_flipped[$imod];
        my @layers_this_module = $is_flipped ? reverse(@layers) : @layers;

        my $z = -$total_thickness/2.0;
        my $i = 0;

        foreach my $L (@layers_this_module)
        {
            my ($group, $mat, $thick) = @$L;
            my $zhalf = $thick/2.0;
            my $zpos = $z + $thick/2.0;
            $z += $thick;

            %detector = init_det();

            $detector{"name"}        = "${DetectorName}_${group}_${mat}_${i}";
            $detector{"mother"}      = $DetectorName;
            $detector{"description"} = "uRGroove module $imod $group $mat layer";
            $detector{"pos"}         = "0*cm 0*cm $zpos*cm";
            $detector{"rotation"}    = "0*deg 0*deg 0*deg";
            $detector{"color"}       = exists $color{$mat} ? $color{$mat} : "aaaaaa";

            # Match the LMU-style SoLID uRWell size/shape: Box layers.
            $detector{"type"}        = "Box";
            $detector{"dimensions"}  = "$manual_hx*cm $manual_hy*cm $zhalf*cm";

            if ($USE_VOLUME_TABLE) {
                my ($type_from_table, $dim_from_table) =
                    get_volume_info("layer", $imod, $group, $mat, $i, $is_flipped);

                if (defined $type_from_table && defined $dim_from_table) {
                    $detector{"type"}       = $type_from_table;
                    $detector{"dimensions"} = $dim_from_table;
                }
            }

            $detector{"material"}    = $mat;
            $detector{"visible"}     = 1;
            $detector{"style"}       = 1;

            # Sensitive ionization volume: the 3 mm drift gas.
	    if ($group eq "drift" && $mat eq "urgroove_gas") {
	    # if (0 && $group eq "drift" && $mat eq "urgroove_gas") {
                $detector{"sensitivity"} = $HIT_TYPE;
                $detector{"hit_type"}    = $HIT_TYPE;

                $detector{"identifiers"} =
                    "region manual 1 sector manual " . ($imod + 1) .
                    " chamber manual 1 layer manual 1 component manual 1";
            }

            set_common(\%detector);
            print_checked_det(\%detector);

            $i++;
        }
    }
}

sub get_volume_info
{
    my ($kind, $imod, $group, $mat, $layer_index, $is_flipped) = @_;

    # Future hook for a volume table.
    return (undef, undef);
}

make_urgroove();

1;
