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

SolidRunAction::SolidRunAction(){
}

SolidRunAction::~SolidRunAction(){ 
}

void SolidRunAction::BeginOfRunAction(const G4Run*) { 	
}

void SolidRunAction::EndOfRunAction(const G4Run*) {
}
