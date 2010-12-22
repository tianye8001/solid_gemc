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
    G4String particleName;
  // Define the messenger
  fGunMessenger = new SolidPrimaryGeneratorMessenger(this);
  fParticleGun  = new G4ParticleGun();

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(particleName="e-"));

}  

SolidPrimaryGeneratorAction::~SolidPrimaryGeneratorAction() {
  delete fParticleGun;
  delete fGunMessenger;
}


void SolidPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
     fParticleGun->SetParticleMomentum(1.0*GeV);
     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0, 0.0, 0.0));
     fParticleGun->GeneratePrimaryVertex(anEvent);
} 

