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
    print "   ./mrpc16_4modules.pl config.dat\n\n";
    print " This generates four standalone 16-channel MRPC modules in GEMC Perl geometry.\n\n";
    exit;
}

if(scalar @ARGV != 1)
{
    help();
}

our %configuration = load_configuration($ARGV[0]);

$configuration{"detector_name"} = "solid_mrpc16";

require "./mrpc16_4modules_materials.pl";
require "./mrpc16_4modules_geometry.pl";
require "./mrpc16_4modules_hit.pl";
require "./mrpc16_4modules_bank.pl";

materials();
define_hit();
define_bank();

1;
