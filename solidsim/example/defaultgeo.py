# example for geometry construction in SolidSim
#
# Seamus Riordan
# sriordan@physics.umass.edu
# December 22, 2010
#
###########################################################3

# Import our Geant4 Python bindings
from SolidGeant4 import *
# Import Solid specific class bindings
from pysolid import *
import math

# Construction method is called Construct()
def Construct():
    #  Everything we need to keep in terms of the
    #  geometry must be declared as global.
    #  This includes all solids, logical volumes,
    #  physical volumes, and sensitive detectors.

    global world, lworld, pworld
    global defaultMaterial, pbmat
    global rot
    rot = []

    # Create the materials we would like to use
    defaultMaterial = gNistManager.FindOrBuildMaterial("G4_AIR")
    pbmat =  G4Material("Lead", 82., 207.19*g/mole, 11.35*g/cm3)

    # World solid and logical volume
    world = G4Box("World", 8*m, 8*m, 8*m)
    lworld = G4LogicalVolume(world, defaultMaterial, "World")

    wv = G4ThreeVector(0.0, 0.0, 0.0)
    pworld = G4PVPlacement(None, wv, lworld, "World", None, False, 0)

    global leadbox, llead, plead

    #make a detector
    global pbdet
    pbdet = SolidGenericDet("/det/pbdet")
    # We don't need to register this with SDmanager.  
    # It's done automatically.  The detector shows up as
    # the name in the manager

    leadbox = G4Box("leadbox", 80*cm, 20*cm, 20*cm )
    # We associate the logical volume with a sensitive detector
    # in the constructor.  SetSensitiveDetector has no bindings
    # included with Geant4
    llead = G4LogicalVolume(leadbox, pbmat, "leadbox", None, pbdet)

    ptiny = G4PVPlacement(None, G4ThreeVector(6.0*m, 0.0*m, 0.0), "plead", llead, pworld, False, 0)

    # Create some more boxes with rotations

    global newbox, logbox, pbox
    pbox = []
    newbox = G4Box("newbox!", 20*cm, 20*cm, 20*cm )
    logbox = G4LogicalVolume(newbox, pbmat, "lnewbox!")

    # change the colors of these boxes
    global va_red, va_blue
    va_red = G4VisAttributes(G4Color(1.0, 0.0, 0.0))
    llead.SetVisAttributes(va_red)

    va_blue = G4VisAttributes(G4Color(0.3, 0.3, 1.0))
    logbox.SetVisAttributes(va_blue)

    # make a bunch of rotations and store them in a list
    for i in range(10):
	ang = i*36.0*deg
	rot.append(G4RotationMatrix())
        rot[i].rotateX(ang)
	tv = G4ThreeVector(0.0, 3.0*m*math.sin(ang), 3.0*m*math.cos(ang))
	pbox.append(G4PVPlacement(rot[i], tv, "pbox_"+str(i), logbox, pworld, False, 0))

    # Make uniform magnetic field
    fieldMgr = gTransportationManager.GetFieldManager();
    global magfield;
    magfield = G4UniformMagField(G4ThreeVector(0.01*tesla,0.01*tesla,0.01*tesla));

    fieldMgr.SetDetectorField(magfield);
    fieldMgr.CreateChordFinder(magfield);

    # Return the physical world volume.
    return pworld

###############################################################
