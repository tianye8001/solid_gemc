use strict;
use warnings;

our %configuration;

sub solid_lmu_gem_materials
{
    # LMU-style materials for the SoLID beam-test GEM/uRWell geometry.
    #
    # Extracted from the LMU materials.pl convention:
    #   kapton, Al, gas, dlc, Cr, Cu, glue, nomex_pure, nomex, g10
    #
    # Note:
    #   The original LMU glue definition used "C 15 H 32 N 2 O 4".
    #   For this SoLID/GEMC version, glue is written with normalized mass
    #   fractions, which is safer in the current GEMC setup.

    my %mat = init_mat();

    # Kapton
    %mat = init_mat();
    $mat{"name"}        = "kapton";
    $mat{"description"} = "lmu kapton";
    $mat{"density"}     = "1.42";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_H 0.026362 G4_C 0.691133 G4_N 0.073270 G4_O 0.209235";
    print_mat(\%configuration, \%mat);

    # Aluminum
    %mat = init_mat();
    $mat{"name"}        = "Al";
    $mat{"description"} = "lmu Al";
    $mat{"density"}     = "2.699";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Al 1";
    print_mat(\%configuration, \%mat);

    # Ar/CO2 gas
    %mat = init_mat();
    $mat{"name"}        = "gas";
    $mat{"description"} = "lmu gas ArCO2 70/30";
    $mat{"density"}     = "0.00184";
    $mat{"ncomponents"} = "3";
    $mat{"components"}  = "G4_Ar 0.93 G4_CARBON_DIOXIDE 0.05 isobutane 0.02";
    print_mat(\%configuration, \%mat);

    # DLC
    %mat = init_mat();
    $mat{"name"}        = "dlc";
    $mat{"description"} = "lmu dlc";
    $mat{"density"}     = "1.8";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_C 1";
    print_mat(\%configuration, \%mat);

    # Chromium
    %mat = init_mat();
    $mat{"name"}        = "Cr";
    $mat{"description"} = "lmu Cr";
    $mat{"density"}     = "7.8";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Cr 1";
    print_mat(\%configuration, \%mat);

    # Copper
    %mat = init_mat();
    $mat{"name"}        = "Cu";
    $mat{"description"} = "lmu Cu";
    $mat{"density"}     = "8.96";
    $mat{"ncomponents"} = "1";
    $mat{"components"}  = "G4_Cu 1";
    print_mat(\%configuration, \%mat);

    # Epoxy glue, C15H32N2O4 written as normalized mass fractions
    %mat = init_mat();
    $mat{"name"}        = "glue";
    $mat{"description"} = "epoxy glue";
    $mat{"density"}     = "1.16";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.5918 G4_H 0.1060 G4_N 0.0920 G4_O 0.2102";
    print_mat(\%configuration, \%mat);

    # Nomex pure, C14H10N2O2 written as normalized mass fractions
    %mat = init_mat();
    $mat{"name"}        = "nomex_pure";
    $mat{"description"} = "nomex pure";
    $mat{"density"}     = "1.38";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_C 0.6344 G4_H 0.0381 G4_N 0.1057 G4_O 0.2218";
    print_mat(\%configuration, \%mat);

    # Nomex honeycomb
    %mat = init_mat();
    $mat{"name"}        = "nomex";
    $mat{"description"} = "nomex honeycomb";
    $mat{"density"}     = "0.04";
    $mat{"ncomponents"} = "2";
    $mat{"components"}  = "nomex_pure 0.5 G4_AIR 0.5";
    print_mat(\%configuration, \%mat);

    # G10
    %mat = init_mat();
    $mat{"name"}        = "g10";
    $mat{"description"} = "g10 material";
    $mat{"density"}     = "1.700";
    $mat{"ncomponents"} = "4";
    $mat{"components"}  = "G4_Si 0.1 G4_O 0.2 G4_C 0.35 G4_H 0.35";
    print_mat(\%configuration, \%mat);
}

# Optional alias if your main driver expects materials()
sub materials
{
    solid_lmu_gem_materials();
}

1;
