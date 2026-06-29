use strict;
use warnings;

use materials;
our %configuration;

# Materials for the SoLID uRGroove geometry.
#
# Notes:
#   - The drift gas is defined as an Ar/CO2/isobutane mixture.
#   - Please adjust the three mass fractions below if the exact gas recipe is different.
#   - They must add up to 1.0.
#
# Current default:
#   Ar         70%
#   CO2        28%
#   isobutane   2%
#
# GEMC/Geant4 note:
#   The G4PAI model is a physics-list/physics-process setting, not a geometry
#   material setting. This material file only defines the gas composition.

sub materials
{
    my %mat = init_mat();

    my $frac_Ar     = 0.93;
    my $frac_CO2    = 0.05;
    my $frac_iC4H10 = 0.02;

    %mat = init_mat();
    $mat{"name"}        = "isobutane";
    $mat{"description"} = "isobutane C4H10";
    $mat{"density"}     = "0.00251";
    $mat{"ncomponents"} = "2";
    $mat{"components"}  = "G4_C 0.8266 G4_H 0.1734";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "urgroove_gas";
    $mat{"description"} = "uRGroove Ar CO2 isobutane gas mixture";
    $mat{"density"}     = "0.00184";
    $mat{"ncomponents"} = "3";
    $mat{"components"}  = "G4_Ar $frac_Ar G4_CARBON_DIOXIDE $frac_CO2 isobutane $frac_iC4H10";
    print_mat(\%configuration, \%mat);

    # Alias for compatibility if other scripts still refer to material name "gas".
    %mat = init_mat();
    $mat{"name"}        = "gas";
    $mat{"description"} = "alias gas for uRGroove Ar CO2 isobutane mixture";
    $mat{"density"}     = "0.00184";
    $mat{"ncomponents"} = "3";
    $mat{"components"}  = "G4_Ar $frac_Ar G4_CARBON_DIOXIDE $frac_CO2 isobutane $frac_iC4H10";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "kapton";
    $mat{"description"} = "kapton";
    $mat{"density"}     = "1.42";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_H 0.026362 G4_C 0.691133 G4_N 0.073270 G4_O 0.209235";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "Al";
    $mat{"description"} = "aluminum";
    $mat{"density"}     = "2.699";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Al 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "Cu";
    $mat{"description"} = "copper";
    $mat{"density"}     = "8.96";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Cu 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "dlc";
    $mat{"description"} = "DLC carbon";
    $mat{"density"}     = "1.8";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_C 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "glue";
    $mat{"description"} = "epoxy glue";
    $mat{"density"}     = "1.16";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.5918 G4_H 0.1060 G4_N 0.0920 G4_O 0.2102";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "g10";
    $mat{"description"} = "G10";
    $mat{"density"}     = "1.7";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_Si 0.1 G4_O 0.2 G4_C 0.35 G4_H 0.35";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"}        = "EM528";
    $mat{"description"} = "EM528 adhesive";
    $mat{"density"}     = "1.16";  # replace if known
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.5918 G4_H 0.1060 G4_N 0.0920 G4_O 0.2102";
    print_mat(\%configuration, \%mat);
}

1;
