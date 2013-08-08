// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimDetectorHit.cc,v 1.8 2004/04/09 19:03:10 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "CaloSimDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"
#include "stdio.h"
#include <fstream>
using namespace std;

G4Allocator<CaloSimDetectorHit> CaloSimDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimDetectorHit::CaloSimDetectorHit()
{
  TrackNumber = -1;
  ParticleType = -1;
  Edep = 0.0;
  ParticleMomentum = G4ThreeVector(-999, -999, -999);
  ParticleEnergy = 0.0;
  LocalTime = 0.0;
  GlobalTime = 0.0;
  HitPosition = G4ThreeVector(-999, -999, -999);
  VertexMomentum = G4ThreeVector(-999, -999, -999);
  VertexEnergy = 0.0;
  DecayVolID = 999;
  StepProcessName = "None";
  CreatorProcessName = "None";
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimDetectorHit::~CaloSimDetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimDetectorHit::SetDecayVolID(G4Step */*thisStep*/)
{
  
  return;


}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
void CaloSimDetectorHit::SetDecayVolID(G4String thisVolumeName)
{
  G4cout<<"SetDecayVolID has been called with argument "
	<<thisVolumeName<<G4endl;

  return;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimDetectorHit::CaloSimDetectorHit(const CaloSimDetectorHit& right)
{
  TrackNumber  = right.TrackNumber;
  Edep         = right.Edep;
  HitPosition  = right.HitPosition;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

const CaloSimDetectorHit& CaloSimDetectorHit::operator=(const CaloSimDetectorHit& right)
{
  TrackNumber  = right.TrackNumber;
  Edep         = right.Edep;
  HitPosition  = right.HitPosition;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

int CaloSimDetectorHit::operator==(const CaloSimDetectorHit& /*right*/) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimDetectorHit::Draw()
{
  /*  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(HitPosition);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimDetectorHit::Print() // this goes to the screen for user to watch
{
  //  if(true) return; // primitive verbosity setting
  // don't print out hits with small energy deposition,
  // unless the particle is a primary muon
  if(Edep < 0.125 && TrackNumber!= 1) return;

  // else, print out information to screen formatted as below
  else {

    // 1 0 4 0 3.6692 1.80247 1.9 2.8 -1000 0 0 1 3.6692 
    // example of output

    G4cerr << TrackNumber          << " " // 1
	   << ParticleType         << " " // 3
	   << Edep                 << " " // 4
	   << ParticleEnergy       << " " // 5
	   << LocalTime            << " " // 6
	   << GlobalTime           << " " // 6
	   << HitPosition.x()      << " " // 7
	   << HitPosition.y()      << " " // 8
	   << HitPosition.z()      << " "; // 9
    if(ParticleType == 1 || ParticleType == 4) {
      G4cerr << VertexPosition.x()   << " " // 10
	     << VertexPosition.y()   << " " // 11
	     << VertexPosition.z()   << " " // 12
	     << VertexTime           << " "; // 13
      G4cerr << VertexMomentum.x()   << " " // 14
	     << VertexMomentum.y()   << " " // 15
	     << VertexMomentum.z()   << " " // 16
	     << VertexEnergy         << " "; // 17
    }
    else {
      G4cerr << -999   << " " // 10
	     << -999   << " " // 11
	     << -999   << " " // 12
	     << 0.0    << " "; // 13
    }
    G4cerr <<G4endl;
  }
}

void CaloSimDetectorHit::PrintToFile(ofstream *file)
{ // to the output file specified by CaloSimDetectorSD

  if(Edep < 0.125 && TrackNumber!= 1) return; // to shorten the file length

  *file << TrackNumber          << " " // 1
	<< ParticleType         << " " // 3
	<< Edep                 << " " // 4
    //	<< ParticleMomentum.x() << " " //
    //	<< ParticleMomentum.y() << " " //
    //	<< ParticleMomentum.z() << " " //
	<< ParticleEnergy       << " " // 5
	<< LocalTime            << " " // 6
	<< GlobalTime           << " " // 6
        << HitPosition.x()      << " " // 7
        << HitPosition.y()      << " " // 8
        << HitPosition.z()      << " "; // 9
  if(ParticleType == 1 || ParticleType == 4) {
    *file << VertexMomentum.x()   << " " // 10
	  << VertexMomentum.y()   << " " // 11
	  << VertexMomentum.z()   << " " // 12
	  << VertexEnergy         << " "; // 13
      }
  else {
    *file << -999   << " " // 10
	  << -999   << " " // 11
	  << -999   << " " // 12
	  << 0.0    << " "; // 13
      }
  *file << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....





