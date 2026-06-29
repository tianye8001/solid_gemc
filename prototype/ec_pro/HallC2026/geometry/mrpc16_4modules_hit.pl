use strict;
use warnings;

use hit;
our %configuration;

# Optional hit definition for MRPC gas gaps.
# Geometry is passive by default in mrpc16_4modules_geometry.pl.

sub define_hit
{
    my %hit = init_hit();

    $hit{"name"}        = "solid_mrpc";
    $hit{"description"} = "MRPC hit definitions";
    $hit{"identifiers"} = "sector layer component";

    $hit{"signalThreshold"} = "0.1*KeV";
    $hit{"timeWindow"}      = "50*ns";
    $hit{"prodThreshold"}   = "1*mm";
    $hit{"maxStep"}         = "100*um";
    $hit{"delay"}           = "50*ns";
    $hit{"riseTime"}        = "1*ns";
    $hit{"fallTime"}        = "2*ns";
    $hit{"mvToMeV"}         = 100;
    $hit{"pedestal"}        = -20;

    print_hit(\%configuration, \%hit);
}

1;
