/*
*/

#include "SolidDetectorMessenger.hh"
#include "SolidDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

SolidDetectorMessenger::SolidDetectorMessenger( SolidDetectorConstruction*sdc )
: fDC(sdc) { 
    fDCdir = new G4UIdirectory("/det/");
    fDCdir->SetGuidance("Detector construction control");

    fGeoFileCmd = new G4UIcmdWithAString("/det/geofile", this);
    
}

SolidDetectorMessenger::~SolidDetectorMessenger() { 
    delete fGeoFileCmd;
}

void SolidDetectorMessenger::SetNewValue(G4UIcommand *cmd, G4String val){
	if( cmd->GetCommandName() == "geofile" ){
	    fDC->SetGeoFile(val);
	}
}
