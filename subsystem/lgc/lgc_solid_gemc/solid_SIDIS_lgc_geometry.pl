# use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;
use Math::VectorReal;
  

# Perl Dependencies:  Math::VectorReal and Math::MatrixReal to build the Mirrors and do the neceissary rotations.  See www.cpan.org to obtain these modules.


# This file loads a configuration file and builds all the necessary components for the PVDIS or SIDIS Cherenkov detector.  Each component is run under a seperate perl script.  Note that the necissary variables are loaded from an external perl vile declared in the command line.  This is done to allow scripting and optimization of the geometry database.

#use strict;

# print "starting new update\n";

# use lib ("$ENV{GEMC}/database_io");
# use geo;
# use geo qw($pi);
# use Math::MatrixReal;
# use Math::VectorReal qw(:all);
# use Getopt::Long;
# use Math::Trig;

require 'my_vars.pl';  #sets the neccissary variable names
require 'common_functions.pl';  #rotations and mirror building functions.

my $lowEM = $use_lowEM;
my $detPlane = $use_detPlane;

#use 'configs/'.$ARGV[0];  #sets variable values for geometry;
# if($#ARGV < 0){
#     do 'configs/pvdis_CLEO_nominal.pl';
# }else{
#     do $ARGV[0];
# }

require 'build_world_and_tank.pl';
require 'build_pmts.pl';
# require 'build_cones.pl';
# require 'build_mirror1.pl';
# #require 'build_mirror1_alt.pl';
# require 'build_mirror2.pl';
# require 'build_mirror3.pl';
# require 'build_support.pl';
# # require 'lowEM/solid_CLEO_PVDIS_baffle_babarbafflemore1.pl';
# #require 'lowEM/solid_CLEO_PVDIS_baffle_inspection.pl';
# #require 'build_baffle_pvdis.pl';

#start building the pieces:

# make_mother();

# if($lowEM){
#     if($use_pvdis){
# 	make_baffle_plate_inner();
# 	make_baffle_plate_outer();
# 	make_baffle_plate();
# 	make_baffle_blocks();
# 	require 'lowEM/solid_CLEO_PVDIS_beamline.pl';
# 	make_beam_entrance();
# #    make_beam_exit();
# 	require 'lowEM/solid_CLEO_solenoid.pl';
# 	make_coil_yoke();
# 	make_cryostat();
# 	require 'lowEM/solid_CLEO_PVDIS_target.pl'; 
# 	make_target_PVDIS_target();
# #    require 'lowEM/solid_CLEO_PVDIS_absorber.pl';
# #    make_absorber_forwarangle_1();
# #    make_absorber_forwarangle_2();
# 	require 'lowEM/solid_CLEO_PVDIS_gem.pl';
# 	make_gem();
# 	require 'lowEM/solid_CLEO_PVDIS_ec_forwardangle.pl';
# 	make_ec_forwardangle();
# 	make_ec_forwardangle_shield();
# 	require 'lowEM/solid_CLEO_PVDIS_ec_forwardangle_block.pl';
# 	make_ec_forwardangle_block();
#     }else{
# 	require 'lowEM/solid_CLEO_SIDIS_beamline.pl';
# 	make_beam_entrance();
# 	make_beam_exit();
# 	make_beam_coolgas();
# 	require 'lowEM/solid_CLEO_SIDIS_target.pl';
# 	make_target();
# 	require 'lowEM/solid_CLEO_SIDIS_target_collimator.pl';
# 	make_upstream_collimator();
# 	make_downstream_collimator();
# 	require 'lowEM/solid_CLEO_SIDIS_absorber.pl';
# 	make_absorber_forwarangle_1();
# 	make_absorber_forwarangle_2();
# 	make_absorber_largeangle();
# 	require 'lowEM/solid_CLEO_SIDIS_ec_forwardangle.pl';
# 	make_ec_forwardangle();
# 	make_ec_forwardangle_shield();
# 	require 'lowEM/solid_CLEO_SIDIS_ec_largeangle.pl';
# 	make_ec_largeangle();
# 	make_ec_largeangle_shield();
# 	require 'lowEM/solid_CLEO_SIDIS_gem.pl';
# 	make_gem();
#     }
# }
# if($makeEmpty){
#      make_tank_empty();
# }
# 
# if($detPlane){
#     require 'build_detPlane.pl';
#     makeDetPlanes();
# }
# 
if($buildTank){
    if($use_CLEO){
	make_tank_CLEO_pvdis();
	if(!$use_pvdis){
	    make_tank_CLEO_sidis();
	    if(!$detPlane){
		make_tank_CLEO_sidis_front_window();
	    }
	}else{
	    if(!$detPlane){
		make_tank_CLEO_frontwindow();
	    }
	}
    }else{
	make_tank_BaBar_pvdis();
    }
}
if($buildPMTs){
    makePMTs();
}
# if($buildCones){
#     makeCones();
# }
# if($buildM1){
#     make_mirror1();
# }
# if($buildM2){
#     make_mirror2();
# }
# if($buildM3){
#     make_mirror3();
# }
# if($buildSupport){
#     makeSupport();
# }
# 
# if($use_pvdis && $buildBaffle && !$lowEM){
#     make_baffle_plate_inner();
#     make_baffle_plate_outer();
#     make_baffle_plate();
#     make_baffle_blocks();
# }
