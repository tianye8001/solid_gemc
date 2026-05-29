use strict;
use warnings;

use hit;
our %configuration;

sub define_hit
{
    my %hit = init_hit();

    $hit{"name"}        = "urwell";
    $hit{"description"} = "uRWell hit definitions";

    $hit{"identifiers"} = "region sector chamber layer component";

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
