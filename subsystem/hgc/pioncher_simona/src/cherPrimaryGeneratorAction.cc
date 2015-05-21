//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: cherPrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:54:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "cherPrimaryGeneratorAction.hh"
#include "cherPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherPrimaryGeneratorAction::cherPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  
  //create a messenger for this class
  gunMessenger = new cherPrimaryGeneratorMessenger(this);
  
  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("pi+");
  //  G4ParticleDefinition* particle = particleTable->FindParticle("pi-");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);

  // this is for CDF: position of the target w.r.t. the center of coil
  particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-350.0*cm));
  //  particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-330.0*cm));
  //  particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-370.0*cm));

  particleGun->SetParticleEnergy(3.*GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherPrimaryGeneratorAction::~cherPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //  particleGun->GeneratePrimaryVertex(anEvent);
  G4double angle_in = 12.*degree;
  //  G4double angle_in = 11.5*degree;
  G4double angle_out = 12.*degree;
  //  G4double angle_out = 9.3*degree;
  G4double angle_left = 0.*degree;
  G4double angle_right = 360.*degree;
  //  G4double angle_mean = (angle_in+angle_out)/2.;
  //  G4double angle_v = angle_in;
  //  G4int nphotonj = 30;
  //  G4int nphotoni = 4;
  //  G4int nphotonj = 22;
  //  G4int nphotonj = 42;
  //  G4int nphotonj = 35;
  G4int nphotonj = 100;
  G4int nphotoni = 1;
  for(G4int i=0; i<nphotoni; i++){
  //  for(G4int i=0; i<1; i++){
    for(G4int j=0; j<nphotonj; j++){
      //      G4double angle_v = angle_in + (angle_out-angle_in)*i/(nphotoni-1);
      G4double angle_v = angle_in + (angle_out-angle_in)*i/nphotoni;
      //      G4double angle_v = angle_in;
      G4double angle_h = angle_left + (angle_right-angle_left)*j/nphotonj;
      particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(angle_v)*cos(angle_h), 
							      sin(angle_v)*sin(angle_h), 
							      cos(angle_v))); 

      G4cout << "angle theta and phi from PrimaryGen: " << angle_v/degree << " " 
	     << angle_h/degree << G4endl; 
      particleGun->GeneratePrimaryVertex(anEvent);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }
     	       
 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton); 
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 particleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
