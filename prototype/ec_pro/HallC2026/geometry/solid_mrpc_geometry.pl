# use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;

# Define detector name and parent mother volume
my $DetectorName = 'solid_mrpc';
my $DetectorMother="cc_pro_tcd";

# Define standard materials mapping to G4 database
# (Using G4 equivalents for standard materials where custom ones aren't defined)
my %material_map = (
    "honeycomb" => "G4_POLYSTYRENE",  # Approximate honeycomb structural material
    "pcbmvd"    => "G4_G10",          # G10 composite for PCB
    "copper"    => "G4_Cu",           # Copper for readout strips
    "mylar"     => "G4_MYLAR",        # Mylar insulating film
    "carbon"    => "G4_C",            # Graphite/Carbon for resistive electrodes
    "RPCglass"  => "G4_GLASS",        # Bounding and floating glass plates
    "RPCgas"    => "G4_argon",        # Argon (as placeholder for RPC gas mixture)
);

# MRPC Layer specifications (sequentially from bottom to top)
my @layers = (
    # Each element: [name, thickness_in_cm, material, color_hex]
    { name => "honeycomb_bottom",  thick => 0.5000, mat => "honeycomb", col => "ff9933" },
    { name => "pcb_bottom_outer",  thick => 0.0800, mat => "pcbmvd",    col => "00aa00" },
    { name => "readout_bottom",     thick => 0.0035, mat => "copper",    col => "ff66b2" },
    { name => "mylar_bottom_outer", thick => 0.0250, mat => "mylar",     col => "cc00cc" },
    { name => "elec_bottom_outer",  thick => 0.0005, mat => "carbon",    col => "000000" },
    { name => "glass_bottom_outer", thick => 0.0700, mat => "RPCglass",  col => "66b2ff" },
    
    # Bottom gas gaps and floating inner glass plates
    { name => "gap_bottom_1",       thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_bottom_i1",    thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_bottom_2",       thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_bottom_i2",    thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_bottom_3",       thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_bottom_i3",    thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_bottom_4",       thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_bottom_i4",    thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_bottom_5",       thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    
    { name => "glass_bottom_inner", thick => 0.0700, mat => "RPCglass",  col => "66b2ff" },
    { name => "elec_bottom_inner",  thick => 0.0005, mat => "carbon",    col => "000000" },
    { name => "mylar_bottom_inner", thick => 0.0250, mat => "mylar",     col => "cc00cc" },
    { name => "pcb_bottom_inner",   thick => 0.0800, mat => "pcbmvd",    col => "00aa00" },
    
    # Shared center readout
    { name => "readout_center",     thick => 0.0035, mat => "copper",    col => "ff1493" },
    
    { name => "pcb_top_inner",      thick => 0.0800, mat => "pcbmvd",    col => "00aa00" },
    { name => "mylar_top_inner",    thick => 0.0250, mat => "mylar",     col => "cc00cc" },
    { name => "elec_top_inner",     thick => 0.0005, mat => "carbon",    col => "000000" },
    { name => "glass_top_inner",    thick => 0.0700, mat => "RPCglass",  col => "66b2ff" },
    
    # Top gas gaps and floating inner glass plates
    { name => "gap_top_1",          thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_top_i1",       thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_top_2",          thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_top_i2",       thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_top_3",          thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_top_i3",       thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_top_4",          thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    { name => "glass_top_i4",       thick => 0.0500, mat => "RPCglass",  col => "99ccff" },
    { name => "gap_top_5",          thick => 0.0250, mat => "RPCgas",    col => "ffffff" },
    
    { name => "glass_top_outer",    thick => 0.0700, mat => "RPCglass",  col => "66b2ff" },
    { name => "elec_top_outer",     thick => 0.0005, mat => "carbon",    col => "000000" },
    { name => "mylar_top_outer",    thick => 0.0250, mat => "mylar",     col => "cc00cc" },
    { name => "readout_top",        thick => 0.0035, mat => "copper",    col => "ff66b2" },
    { name => "pcb_top_outer",      thick => 0.0800, mat => "pcbmvd",    col => "00aa00" },
    { name => "honeycomb_top",      thick => 0.5000, mat => "honeycomb", col => "ff9933" },
);

# Calculate total thickness
my $total_thickness = 0;
foreach my $layer (@layers) {
    $total_thickness += $layer->{thick};
}

# The main subroutine loaded by GEMC configuration scripts
sub mrpc_geometry
{
    make_mrpc_mother();
    make_mrpc_layers();
}

# 1. Create the Mother Box containing all MRPC components
sub make_mrpc_mother
{
    my %detector = init_det();
    
    $detector{"name"}        = "mrpc_module";
    $detector{"mother"}      = $DetectorMother;
    $detector{"description"} = "MRPC Module Mother Volume (10x10 cm)";
    
    # Placed at z = 100 cm as requested
    $detector{"pos"}         = "0*cm 0*cm 100*cm";
    $detector{"rotation"}    = "0*deg 0*deg 0*deg";
    $detector{"color"}       = "888888"; # Medium Gray
    $detector{"type"}        = "Box";
    
    # Dimensions of the mother box (dx, dy, dz half-lengths)
    # x length = 10 cm => dx = 5 cm
    # y length = 10 cm => dy = 5 cm
    # z length = total_thickness => dz = total_thickness / 2
    my $half_z = $total_thickness / 2.0;
    $detector{"dimensions"}  = "5*cm 5*cm $half_z*cm";
    
    $detector{"material"}    = "G4_AIR";
    $detector{"mfield"}      = "no";
    $detector{"ncopy"}       = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 0; # Wireframe to see the internal components
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "";
    $detector{"identifiers"} = "";
    
    print_det(\%main::configuration, \%detector);
}

# 2. Build each layer inside the mother box
sub make_mrpc_layers
{
    my $current_z = -$total_thickness / 2.0;
    
    foreach my $layer (@layers) {
        my $thick = $layer->{thick};
        my $z_center = $current_z + $thick / 2.0;
        $current_z += $thick;
        
        my %detector = init_det();
        
        $detector{"name"}        = "mrpc_module_$layer->{name}";
        $detector{"mother"}      = "mrpc_module"; # Placed inside the mother volume
        $detector{"description"} = "MRPC component: $layer->{name}";
        
        # Local position inside the mother volume
        $detector{"pos"}         = "0*cm 0*cm $z_center*cm";
        $detector{"rotation"}    = "0*deg 0*deg 0*deg";
        $detector{"color"}       = $layer->{col};
        $detector{"type"}        = "Box";
        
        # Layer dimensions (half-lengths): dx = 5 cm, dy = 5 cm, dz = thick / 2
        my $half_thick = $thick / 2.0;
        $detector{"dimensions"}  = "5*cm 5*cm $half_thick*cm";
        
        # Assign material from standard map
        my $g4_material = $material_map{$layer->{mat}} || "G4_AIR";
        $detector{"material"}    = $g4_material;
        
        $detector{"mfield"}      = "no";
        $detector{"ncopy"}       = 1;
        $detector{"pMany"}       = 1;
        $detector{"exist"}       = 1;
        $detector{"visible"}     = 1;
        $detector{"style"}       = 1; # Solid rendering
        
        # Configure gas gaps to be sensitive to track hits
        if ($layer->{name} =~ /^gap_/) {
            $detector{"sensitivity"} = "flux";
            $detector{"hit_type"}    = "flux";
            $detector{"identifiers"} = "id manual $layer->{name}";
        } else {
            $detector{"sensitivity"} = "no";
            $detector{"hit_type"}    = "";
            $detector{"identifiers"} = "";
        }
        
        print_det(\%main::configuration, \%detector);
    }
}

# Main script entry point (only executes if run directly, not if required)
if (!caller) {
    # Initialize the main configuration
    our %configuration = init_configuration();
    $configuration{"detector_name"} = $DetectorName;
    
    # Generate the geometry
    mrpc_geometry();
}

1;
