/*
*/

#include "SolidDetectorMessenger.hh"
#include "SolidDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

SolidDetectorMessenger::SolidDetectorMessenger( SolidDetectorConstruction* ) { 
}

SolidDetectorMessenger::~SolidDetectorMessenger() { 
}

void SolidDetectorMessenger::SetNewValue(G4UIcommand*, G4String ){
}
