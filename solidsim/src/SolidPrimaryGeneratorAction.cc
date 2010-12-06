/*
 */
#include "SolidPrimaryGeneratorAction.hh"
#include "SolidPrimaryGeneratorMessenger.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

SolidPrimaryGeneratorAction::SolidPrimaryGeneratorAction() {
  // Define the messenger
  fGunMessenger = new SolidPrimaryGeneratorMessenger(this);
  fParticleGun  = new G4ParticleGun();

}  

SolidPrimaryGeneratorAction::~SolidPrimaryGeneratorAction() {
  delete fParticleGun;
  delete fGunMessenger;
}


void SolidPrimaryGeneratorAction::GeneratePrimaries(G4Event* ) {
} 

