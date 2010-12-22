/*
*/

#include "SolidEventAction.hh"
#include "SolidOutput.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4VVisManager.hh"

SolidEventAction::SolidEventAction(){ 
    const char *fname = "SolidEventAction()";
    fOutput = SolidOutput::GetInstance();
    if( !fOutput ){
	fprintf(stderr, "%s::%s  Warning: Could not get SolidOutput\n",
		GetClassName(), fname);
    }

  fHitsCollectionID = -1;
}

SolidEventAction::~SolidEventAction() {
}

void SolidEventAction::BeginOfEventAction(const G4Event*) {
}

void SolidEventAction::EndOfEventAction(const G4Event* ) {  
    // Fill tree with results
    if( fOutput ){ fOutput->FillTree(); }
}

