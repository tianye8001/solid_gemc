/*
*/

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "SolidDetectorMessenger.hh"
#include "SolidDetectorConstruction.hh"

#include "SolidFieldMap.hh"
#include "SolidFieldManager.hh"

/////////////////////////////////////////////////////////////////////////////
SolidDetectorConstruction::SolidDetectorConstruction() {
  fDetectorMessenger = new SolidDetectorMessenger(this);
  fFieldMan = new SolidFieldManager();
}

/////////////////////////////////////////////////////////////////////////////
SolidDetectorConstruction::~SolidDetectorConstruction() { 
  delete fDetectorMessenger;
}

G4VPhysicalVolume* SolidDetectorConstruction::Construct() {  
    const char *thisfunc = "Construct";

  int ret = fFieldMan->ProcessFieldMaps();

  if( ret == -1 ){
      fprintf(stderr, "%s::%s Adding fields has failed\n",
	      GetClassName(), thisfunc );
      // Something is wrong.  Let's die here before running
      // further
      exit(1);
      return NULL;
  }

  return NULL;
}
