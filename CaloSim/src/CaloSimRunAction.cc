// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimRunAction.cc,v 1.5 2004/03/03 22:09:14 asharp Exp $
// GEANT4 tag $Name:  $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "CaloSimRunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include <time.h>

using CLHEP::HepRandom;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimRunAction::CaloSimRunAction()
{G4cout<<"CaloSimRunManager instantiating... done"<<G4endl;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimRunAction::~CaloSimRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

//void CaloSimRunAction::BeginOfRunAction(const G4Run* aRun, const G4int parameter=0)
void CaloSimRunAction::BeginOfRunAction(const G4Run* aRun)
{
  //  G4cout<<"CaloSimRunAction::BeginOfRunAction"<<G4endl;

  // Can this function be modified to add a "card reader" function?!?!?
  //  if(parameter){
  //    G4cout<<"The value of \'parameter\' is "<<parameter<<G4endl;}
  //  else G4cout<<"\'parameter\' not found."<<G4endl;

  runID = aRun->GetRunID();
  G4cout << "### Run " << runID << " start." << G4endl;

  //  HepRandom::setTheEngine(new RanecuEngine); //selection of a random
  G4long seed=time(0); //returns time in seconds as an integer
  HepRandom::setTheSeed(seed);//changes the seed of the random engine
  HepRandom::showEngineStatus();//shows the actual seed
 


  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      // UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 
  //  G4cout<<"CaloSimRunAction::BeginOfRunAction ended."<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimRunAction::EndOfRunAction(const G4Run*)
{
  //  G4cout<<"CaloSimRunAction::EndOfRunAction"<<G4endl;
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  
  if(G4VVisManager::GetConcreteInstance())
  {
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }
  G4cout << "### Run has ended." << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....





