#!/usr/bin/perl -w

use strict;

# Driver for LMU-style GEM geometry adapted to the SoLID HallC2026 beam-test setup.
#
# Usage:
#   ./solid_lmu_gem.pl config.dat
#
# It expects these files in the same directory:
#   solid_lmu_gem_materials.pl
#   solid_lmu_gem_bank.pl
#   solid_lmu_gem_hit.pl
#   solid_lmu_gem_geometry_4modules_flipped.pl
#
# It generates files with detector_name from config.dat, for example:
#   solid_lmu_gem__materials_Original.txt
#   solid_lmu_gem__bank_Original.txt
#   solid_lmu_gem__hit_Original.txt
#   solid_lmu_gem__geometry_Original.txt
#
# If your config.dat has:
#   detector_name: solid_lmu_gem
#   variation: Original
#   factory: TEXT
#
# the output names will naturally match the solid_lmu_gem prefix.

use lib ("$ENV{GEMC}/api/perl");

use utils;
use parameters;
use geometry;
use hit;
use bank;
use math;
use materials;

sub help
{
    print "\n Usage:\n";
    print "   solid_lmu_gem.pl <configuration filename>\n\n";
    print " Example:\n";
    print "   ./solid_lmu_gem.pl config.dat\n\n";
    print " This creates the SoLID LMU-style GEM materials, bank, hit, and geometry definitions.\n\n";
    exit;
}

if(scalar @ARGV != 1)
{
    help();
}

our %configuration = load_configuration($ARGV[0]);
$configuration{"detector_name"} = "solid_lmu_gem";
$configuration{"variation"} = "Original";

print "\n";
print "Generating SoLID LMU-style GEM geometry\n";
print "  detector_name = $configuration{detector_name}\n";
print "  variation     = $configuration{variation}\n";
print "  factory       = $configuration{factory}\n" if defined $configuration{"factory"};
print "\n";

# Load support files.
require "./solid_lmu_gem_materials.pl";
require "./solid_lmu_gem_bank.pl";
require "./solid_lmu_gem_hit.pl";
require "./solid_lmu_gem_geometry.pl";

# Generate TEXT definitions.
solid_lmu_gem_materials();
solid_lmu_gem_bank();
solid_lmu_gem_hit();
solid_lmu_gem_geometry();

print "\nDone generating SoLID LMU-style GEM files.\n\n";

1;
