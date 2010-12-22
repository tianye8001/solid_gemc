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

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"


SolidPhysicsList::SolidPhysicsList(){
  fMessenger = new SolidPhysicsListMessenger(this);
  SetVerboseLevel(1);
  particleList = new G4DecayPhysics("decays");
  emPhysicsList = new G4EmStandardPhysics();
}

void SolidPhysicsList::ConstructParticle(){
  particleList->ConstructParticle();
//  emPhysicsList->ConstructParticle();
}

void SolidPhysicsList::ConstructProcess(){
  // FIXME:  Temporary list for now

  AddTransportation();
  particleList->ConstructProcess();
  emPhysicsList->ConstructProcess();

}

SolidPhysicsList::~SolidPhysicsList(){ 
  delete fMessenger;
}

void SolidPhysicsList::SetCuts(){
}
