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
#include "TTree.h"
#include "TFile.h"
#include <fstream>
#include "TObject.h"           // from ROOT libraries
#include "TRandom3.h"
#include "Config.h"

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

  static void SetInitTheta(double theta) {Theta=theta; }
private:

  TRandom3  RndGen;

  static double Theta;
  double myTheta;

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
//  TH2D* EvsFiber;
  TH2F *hHit_XY,*hHit_XZ,*hHit_YZ;
  TH1F *hStep_Layer;
  TH1F *hStep_Fiber;

public:

  TTree* T;

  G4int NBlockHit;

  G4int blockID[nblock];
  G4double blockX[nblock];
  G4double blockY[nblock];


  G4int NHitLayer;
  G4int layerID[nScintlayer];

  // Energy Depostition
  G4double blockWEdep[nblock];
  G4double blockglueEdep[nblock];
  G4double blockfiberEdep[nblock];
  G4double blockfiberEdep_PS[nblock];

  G4double glueEdepLayer[nScintlayer];
  G4double fiberEdepLayer[nScintlayer];
  G4double fiberEdepIonizingLayer[nScintlayer];
  G4double WEdepLayer[nScintlayer];


  G4int NBlockHitLayer;
  G4double blockglueEdepLayer[nblock*nScintlayer];
  G4double blockfiberEdepLayer[nblock*nScintlayer];


  G4double blockfiberPhotons[nblock]; // photons per block
  G4double fiberPhotonsLayer[nScintlayer]; // photons per layer
  G4double blockfiberPhotonsLayer[nblock*nScintlayer];

};

#endif





