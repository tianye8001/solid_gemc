/*
*/

#include "globals.hh"
#include "G4ProcessManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"

#include "SolidPhysicsList.hh"
#include "SolidPhysicsListMessenger.hh"


SolidPhysicsList::SolidPhysicsList(){
  fMessenger = new SolidPhysicsListMessenger(this);
  SetVerboseLevel(1);
}

SolidPhysicsList::~SolidPhysicsList(){ 
  delete fMessenger;
}

void SolidPhysicsList::SetCuts(){
}
