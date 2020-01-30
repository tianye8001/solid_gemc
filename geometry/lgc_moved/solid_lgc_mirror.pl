#!/usr/bin/perl -w
use strict;
use warnings;
use mirrors;

our %configuration;

print "\n\n   -== Writing mirror properties ==- \n\n";

#use strict;
#use lib ("$ENV{GEMC}/io");
#use utils;
#use mirrors;

# Help Message
#sub help()
#{
#	print "\n Usage: \n";
#	print "   mirror.pl <configuration filename>\n";
# 	print "   Will create mirrors\n";
# 	print "   Note: The passport and .visa files must be present to connect to MYSQL. \n\n";
#	exit;
#}

# Make sure the argument list is correct
# If not pring the help
#if( scalar @ARGV != 1)
#{
#	help();
#	exit;
#}


# Loading configuration file and paramters
#our %configuration = load_configuration($ARGV[0]);

# One can change the "variation" here if one is desired different from the config.dat
# $configuration{"variation"} = "myvar";

# Table of optical photon energies (wavelengths)                                     

sub print_lgc_mirror
{


    my @PhotonEnergy = (
	"2.04358*eV","2.0664*eV","2.09046*eV","2.14023*eV",
	"2.16601*eV","2.20587*eV","2.23327*eV","2.26137*eV",
	"2.31972*eV","2.35005*eV","2.38116*eV","2.41313*eV",
	"2.44598*eV","2.47968*eV","2.53081*eV","2.58354*eV",
	"2.6194*eV","2.69589*eV","2.73515*eV","2.79685*eV",
	"2.86139*eV","2.95271*eV","3.04884*eV","3.12665*eV",
	"3.2393*eV","3.39218*eV","3.52508*eV","3.66893*eV",
	"3.82396*eV","3.99949*eV","4.13281*eV","4.27679*eV",
	"4.48244*eV","4.65057*eV","4.89476*eV","5.02774*eV",
	"5.16816*eV","5.31437*eV","5.63821*eV","5.90401*eV",
	"6.19921*eV"
	);           

    my @reflectivity_mirror = (
	"0.8678125","0.8651562","0.8639063","0.8637500",
	"0.8640625","0.8645313","0.8643750","0.8656250",
	"0.8653125","0.8650000","0.8648437","0.8638281",
	"0.8635156","0.8631250","0.8621875","0.8617188",
	"0.8613281","0.8610156","0.8610938","0.8616016",
	"0.8623047","0.8637500","0.8655859","0.8673828",
	"0.8700586","0.8741992","0.8781055","0.8825195",
	"0.8876172","0.8937207","0.8981836","0.9027441",
	"0.9078369","0.9102002","0.9093164","0.9061743",
	"0.9004223","0.8915210","0.8599536","0.8208313",
	"0.7625024"
	);         

    my @efficiency_mirror = (
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0."
	);  

    my @reflectivity_pmt = (
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0.","0.","0.","0.",
	"0."
	); 
    
    my @efficiency_pmt = (
	"0.008","0.0124","0.0157","0.02125",
	"0.0275","0.034","0.04","0.048",
	"0.062","0.0753","0.09","0.1071",
	"0.12144","0.1428","0.15","0.16429",
	"0.17857","0.1928","0.2","0.2125",
	"0.225","0.2375","0.25","0.2625",
	"0.275","0.275","0.275","0.275",
	"0.275","0.275","0.2625","0.25",
	"0.2375","0.2125","0.192859","0.185716",
	"0.178573","0.15714","0.13572","0.1143",
	"0.09"
	);


	my %mat;
	
	%mat= init_mir();
	$mat{"name"}         = "LGC_WinstonCone";
	$mat{"description"}  = "LGC_WinstonCone";
	$mat{"type"}         = "dielectric_metal";
	$mat{"finish"}       = "polished";
	$mat{"model"}        = "unified";
	$mat{"border"}       = "SkinSurface";
	$mat{"photonEnergy"} = arrayToString(@PhotonEnergy);
	$mat{"reflectivity"} = arrayToString(@reflectivity_mirror);
	$mat{"efficiency"}   = arrayToString(@efficiency_mirror);	
	print_mir(\%configuration, \%mat);

	%mat= init_mir();
	$mat{"name"}         = "LGC_PMT_LightStop";
	$mat{"description"}  = "Stops the optical photons behind pmts";
	$mat{"type"}         = "dielectric_metal";
	$mat{"finish"}       = "polished";
	$mat{"model"}        = "unified";
	$mat{"border"}       = "SkinSurface";
	$mat{"photonEnergy"} = arrayToString(@PhotonEnergy);
	$mat{"reflectivity"} = arrayToString(@reflectivity_pmt);
	$mat{"efficiency"}   = arrayToString(@efficiency_mirror);	
	print_mir(\%configuration, \%mat);

	%mat= init_mir();
	$mat{"name"}         = "LGC_Mirror";
	$mat{"description"}  = "LGC_Mirror";
	$mat{"type"}         = "dielectric_metal";
	$mat{"finish"}       = "polished";
	$mat{"model"}        = "unified";
	$mat{"border"}       = "SkinSurface";
	$mat{"photonEnergy"} = arrayToString(@PhotonEnergy);
	$mat{"reflectivity"} = arrayToString(@reflectivity_mirror);
	$mat{"efficiency"}   = arrayToString(@efficiency_mirror);	
	print_mir(\%configuration, \%mat);
	
}
print_lgc_mirror();
1;
