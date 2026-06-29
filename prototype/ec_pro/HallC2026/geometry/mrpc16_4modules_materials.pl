use strict;
use warnings;

use materials;
our %configuration;

# Materials for four 16-channel MRPC modules.
# These are self-contained placeholder material definitions based on the
# eTOF ROOT geometry media names: RPCgas, RPCglass, copper, carbon,
# mylar, pcbmvd, honeycomb.

sub materials
{
    my %mat = init_mat();
    $mat{"name"}        = "RPCgas";
    $mat{"description"} = "MRPC gas mixture R134A/SF6/isobutane = 90/5/5 by mass";
    $mat{"density"}     = "0.00425";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.2354 G4_H 0.0227 G4_F 0.7262 G4_S 0.0157";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "RPCglass";
    $mat{"description"} = "MRPC glass approximation";
    $mat{"density"}     = "2.5";
    $mat{"ncomponents"} = "2";
    $mat{"components"}  = "G4_Si 0.467 G4_O 0.533";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "copper";
    $mat{"description"} = "copper readout";
    $mat{"density"}     = "8.96";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Cu 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "carbon";
    $mat{"description"} = "carbon electrode";
    $mat{"density"}     = "2.0";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_C 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "mylar";
    $mat{"description"} = "mylar";
    $mat{"density"}     = "1.39";
    $mat{"ncomponents"} = "3";
    $mat{"components"}  = "G4_C 0.625 G4_H 0.042 G4_O 0.333";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "pcbmvd";
    $mat{"description"} = "PCB FR4 approximation";
    $mat{"density"}     = "1.85";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_Si 0.180 G4_O 0.405 G4_C 0.278 G4_H 0.137";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "honeycomb";
    $mat{"description"} = "honeycomb support approximation";
    $mat{"density"}     = "0.05";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.50 G4_H 0.06 G4_O 0.35 G4_N 0.09";
    print_mat(\%configuration, \%mat);


}

1;
