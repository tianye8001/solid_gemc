#!/usr/bin/perl -w
use strict;

use lib ("$ENV{GEMC}/io");
use lib ("$ENV{GEMC}/api/perl");

use utils;

our %configuration = load_configuration($ARGV[0]);

$configuration{"detector_name"} = "solid_urwell";

require "./urwell_materials.pl";
require "./urwell_geometry.pl";
require "./urwell_hit.pl";
require "./urwell_bank.pl";

materials();
define_hit();
define_bank();
