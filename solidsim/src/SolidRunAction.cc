/*
 */

#include "SolidRunAction.hh"
#include "SolidEventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "SolidDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Timer.hh"
#include "SolidRunAction.hh"
#include "SolidOutput.hh"

SolidRunAction::SolidRunAction(){
    const char *fname = "SolidRunAction()";
    fOutput = SolidOutput::GetInstance();
    if( !fOutput ){
	fprintf(stderr, "%s::%s  Warning: Could not get SolidOutput\n",
		GetClassName(), fname);
    }
}

SolidRunAction::~SolidRunAction(){ 
}

void SolidRunAction::BeginOfRunAction(const G4Run*) { 	
    if( fOutput ){
	fOutput->CreateOutputFile();
    }
}

void SolidRunAction::EndOfRunAction(const G4Run*) {
    if( fOutput ){
	fOutput->CloseOutputFile();
    }
}
