/*
*/

#include "SolidEventAction.hh"

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
  fHitsCollectionID = -1;
}

SolidEventAction::~SolidEventAction() {
}

void SolidEventAction::BeginOfEventAction(const G4Event*) {
}

void SolidEventAction::EndOfEventAction(const G4Event* ) {  
}

