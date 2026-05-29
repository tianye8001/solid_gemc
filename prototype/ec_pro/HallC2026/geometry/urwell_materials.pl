use strict;
use warnings;
use materials;
our %configuration;

sub materials
{
    my %mat = init_mat();

    $mat{"name"} = "kapton";
    $mat{"density"} = "1.42";
    $mat{"ncomponents"} = "4";
    $mat{"components"} = "G4_H 0.026362 G4_C 0.691133 G4_N 0.073270 G4_O 0.209235";
    print_mat(\%configuration, \%mat);
 
    %mat = init_mat();
    $mat{"name"} = "Al";
    $mat{"density"} = "2.699";
    $mat{"ncomponents"} = "1";
    $mat{"components"} = "G4_Al 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"} = "gas";
    $mat{"density"} = "0.00184";
    $mat{"ncomponents"} = "3";
    $mat{"components"} = "G4_Ar 0.93 G4_CARBON_DIOXIDE 0.05 isobutane 0.02";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"} = "Cu";
    $mat{"density"} = "8.96";
    $mat{"ncomponents"} = "1";
    $mat{"components"} = "G4_Cu 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"} = "dlc";
    $mat{"density"} = "1.8";
    $mat{"ncomponents"} = "1";
    $mat{"components"} = "G4_C 1";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"} = "glue";
    $mat{"density"} = "1.16";
    $mat{"ncomponents"} = "4";
    $mat{"components"} = "G4_C 0.5918 G4_H 0.106 G4_N 0.092 G4_O 0.2102";
    print_mat(\%configuration, \%mat);

    %mat = init_mat();
    $mat{"name"} = "g10";
    $mat{"density"} = "1.7";
    $mat{"ncomponents"} = "4";
    $mat{"components"} = "G4_Si 0.1 G4_O 0.2 G4_C 0.35 G4_H 0.35";
    print_mat(\%configuration, \%mat);
}
