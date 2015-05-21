
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
// $Id: CalorimeterSD.cc,2012-08-01 $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "RunAction.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "CalorimeterHit.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh" 
#include "G4EventManager.hh"

//#include "PrimaryGeneratorAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::CalorimeterSD(G4String name)
:G4VSensitiveDetector(name)
// CalorimeterSD::CalorimeterSD()
// :G4VSensitiveDetector()
{
//  os.open("output.dat");
//  os2.open("output2.dat");    
   std::stringstream ss;
//    G4String name="pioncher";
   ss << name <<".dat";   
   G4String filename = ss.str();
   ss.clear();
  os3.open(filename);

  G4String HCname;
//  collectionName.insert(HCname="HitsCollection");
  collectionName.insert(name);
  etotal = 0.;
  vertexcheck = G4ThreeVector(0., 0., 0.);
  energycheck = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::~CalorimeterSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::Initialize(G4HCofThisEvent* HCE)
{
//  HitsCollection = new CalorimeterHitsCollection (SensitiveDetectorName,collectionName[0]); 
HitsCollection = new CalorimeterHitsCollection (GetName(),collectionName[0]);
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
    HCE->AddHitsCollection( HCID, HitsCollection ); 
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4bool CalorimeterSD::ProcessHits(const G4Step* aStep,G4TouchableHistory*)
{
 

 const G4Track* aTrack = aStep->GetTrack();
//  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPostStepPoint()->GetTouchable());
  G4VPhysicalVolume* PhysVol = theTouchable->GetVolume();
  CalorimeterHit* newHit = new CalorimeterHit();   

  G4int evid = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();


  G4double evtID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  G4String Name = PhysVol->GetName();
//  G4cout<<"THE NAME IS::::::::::::::::::::::::::::::;"<<Name<<G4endl;
  G4int ModuleID = PhysVol->GetCopyNo();
   HitsCollection->insert( newHit );
   G4ThreeVector vdir = aTrack->GetMomentumDirection();

  G4int PMTid=0;
   for(int i = 0; i < 30; ++i) {
    std::stringstream ss;
//   ss << "PMTArray_" << i;
   ss << "av_2_impr_1_PMT_pv_" << i;
   G4String arrayid = ss.str();
   ss.clear();
   if(Name==arrayid)
   {
    PMTid=i;
   }

  }

  if(ModuleID<60){
// const G4Event* currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
//  G4int EvtID = currentEvent->GetEventID();


  G4double edep = aStep->GetTotalEnergyDeposit();
  G4ThreeVector apos = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector vpos = aTrack->GetVertexPosition();
//  etotal += edep;
 
  G4double KinEne = aTrack->GetKineticEnergy();
//  G4ParticleDefinition* aParticle = aTrack->GetDefinition();
//  G4String par = aParticle->GetParticleName();
//  G4double evntID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
//  G4String Name = PhysVol->GetName();
//  G4int ModuleID = PhysVol->GetCopyNo();


//   newHit->SetDirection  (aStep->GetPreStepPoint()->GetMomentumDirection());
 //  if(vdir.z()<0.0){
//    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());

/*
    newHit->SetTrackID  (evntID);
    newHit->SetStepE    (KinEne);
    newHit->SetEdep     (edep);
    newHit->SetPos        (aStep->GetPreStepPoint()->GetPosition());
    newHit->SetDirection  (aStep->GetPreStepPoint()->GetMomentumDirection());
    newHit->SetVertex (vpos);
    HitsCollection->insert( newHit );
*/

  //print
 
/*
   if (energycheck != KinEne || vertexcheck != vpos) {   
      energycheck = KinEne;
      vertexcheck = vpos;
      if(par == "e-") {newHit->Printf(os);}
      else {
        G4cout<< par << G4endl;
        newHit->Printf(os2);
      }
    }
*/


   os3 <<evid<<"    "<<evtID <<"    ";
   os3 << apos.x() <<"    "<<apos.y() <<"    "<<apos.z() <<"    ";
   os3 << vpos.x() <<"    "<<vpos.y() <<"    "<<vpos.z() <<"    ";
   os3 << ModuleID <<"    "<<PMTid<<"    "<<KinEne<<"    "<<edep;
   os3 << G4endl;
}
//}
//   G4cout<<evntID<< G4endl;

//     newHit->Draw();
  return true;
} 


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::EndOfEvent(G4HCofThisEvent*)
{


// if (verboseLevel>0) { 
//     EvtID++;
     G4int NbHits = HitsCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits in the Calorimeter: " << G4endl;
     for (G4int i=0;i<NbHits;i++) (*HitsCollection)[i]->Print();
//    } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

