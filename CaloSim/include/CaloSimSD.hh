// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimSD.hh,v 1.21 2004/04/09 19:07:48 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#ifndef CaloSimSD_h
#define CaloSimSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4DecayTable.hh"
#include <fstream>
#include "CaloSimDetectorHit.hh"

#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TFile.h"
#include <fstream>
#include "TObject.h"           // from ROOT libraries

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimSD : public G4VSensitiveDetector
{

public:
  //  CaloSimSD(G4String);
  CaloSimSD(G4String, G4String);
  ~CaloSimSD();

  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  void ProcessEventHC(G4HCofThisEvent*);

private:
  //////////////////////////////////
  // GEANT4 objects and variables //
  //////////////////////////////////
  ofstream newInfo;
  CaloSimHitsCollection* detectorCollection;
  G4bool EventPreparedToPrint;

  G4int badFirstStep, parentID;

  G4String particleName;
  G4VPhysicalVolume* currentVolume;
  G4String volumeName;
  G4VPhysicalVolume* nextVolume;
  G4int ParticleType;
  G4double totalEdep;

  G4int evtIndex;
  G4bool Prim4VecSet;
  G4bool fEnteredCalo, fStartOut;

  G4int GetParticleType(G4String particleName, G4int parentID);

  G4ThreeVector vtxPos, vtxMom, diffPos, caloPos;
  G4ThreeVector pos;
  G4double vtxE;

  //  FILE *outfile;

  TFile* rootFile;
  TH1D*  TotalEdepPerEvent;
  TH1D*  NumTilesHit;
  TH1D*  NumTilesHitEdepCut;
  TH2D*  EdepPerTilePair;
  TNtuple* ntuple;
  TH2D* EvsFiber;
  TH2F *hHit_XY,*hHit_XZ,*hHit_YZ;

};

#endif





