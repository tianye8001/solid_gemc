#!/usr/bin/perl -w
use strict;

use lib ("$ENV{GEMC}/io");
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
    print "   urgroove.pl <configuration filename>\n\n";
    print " Example:\n";
    print "   ./urgroove.pl config.dat\n\n";
    print " This creates the SoLID uRGroove materials, geometry, hit, and bank definitions.\n\n";
    exit;
}

if(scalar @ARGV != 1)
{
    help();
}

our %configuration = load_configuration($ARGV[0]);

# Force output txt files to start with solid_urgroove.
$configuration{"detector_name"} = "solid_urgroove";

require "./urgroove_materials.pl";
require "./urgroove_geometry.pl";
require "./urgroove_hit.pl";
require "./urgroove_bank.pl";

materials();
define_hit();
define_bank();

1;
