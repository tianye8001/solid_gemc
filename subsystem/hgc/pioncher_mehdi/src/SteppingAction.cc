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
// $Id: SteppingAction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "CalorimeterSD.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"
#include "G4ios.hh"
//#include "UserManager.hh"
////#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//SteppingAction::SteppingAction(DetectorConstruction* det,EventAction* evt):detector(det), eventaction(evt){ }
SteppingAction::SteppingAction(){ }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingAction::UserSteppingAction(const  G4Step* aStep)
{            
//G4cout<<"*********************************************======VOLUME====="<<G4endl;


//	UserManager* userManager = UserManager::GetUserManager();
	G4Track* theTrack = aStep->GetTrack();
	G4int theTrackID = theTrack->GetTrackID();	
         if(theTrack->GetMaterial()->GetName() == "Kryptonite")        
         {
            theTrack->SetTrackStatus(fStopAndKill);
         }

        if( theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && theTrack->GetParentID() > 0 )
        {
	 G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
	 G4OpBoundaryProcessStatus boundaryStatus = Undefined;
	 G4OpBoundaryProcess* boundary = NULL;

         if( !boundary )
	  {
           G4ProcessManager* pm = theTrack->GetDefinition()->GetProcessManager();
	   G4int nprocesses = pm->GetProcessListLength();
	   G4ProcessVector* pv = pm->GetProcessList();
	   boundary=(G4OpBoundaryProcess*)(*pv)[0];
	   for ( G4int i=0; i<nprocesses; i++ )
	    {
	     if( (*pv)[i]->GetProcessName()=="OpBoundary" ) 
	      {
	       boundary=(G4OpBoundaryProcess*)(*pv)[i];
	       break;
	      }
	    }
	  }
          if( thePostPoint->GetStepStatus() == fGeomBoundary )
          {
           if( boundary )
            {
	     boundaryStatus = boundary->GetStatus();
            }
 
          switch( boundaryStatus )
            {
             case Detection:
              {
               G4SDManager* SDman = G4SDManager::GetSDMpointer();
 
               G4String sdName="PMTARRAY";
               CalorimeterSD* pmtSD = (CalorimeterSD*)SDman->FindSensitiveDetector(sdName);
               if(pmtSD)pmtSD->ProcessHits(aStep,NULL);
//              G4cout<<"**************************FOUND SD!*************************************"<<G4endl;

/*
                 for(int i = 0; i < 30; ++i) 
                 {
                 std::stringstream ss;
                 ss << "PMTArray_" << i;
                 G4String sdName = ss.str();
                 ss.clear();
                 G4cout<<"======VOLUME====="<<sdName<<G4endl;
                 CalorimeterSD* pmtSD = (CalorimeterSD*)SDman->FindSensitiveDetector(sdName);
                 if(pmtSD)pmtSD->ProcessHits(aStep,NULL);
                 G4cout<<"**************************FOUND SD!*************************************"<<G4endl;
                 }
*/
                 break;
               
              }
               case SpikeReflection: {break;}//mirror or cone
               case FresnelRefraction: {break;}
            }
          }
        }
        
}
//
//For further improvement
//
/*
void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step

  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;


  
   if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
      stepl = aStep->GetStepLength();
      
   if (volume == detector->GetAbsorber()) eventaction->AddAbs(edep,stepl);
   if (volume == detector->GetGap())      eventaction->AddGap(edep,stepl);
 
  //example of saving random number seed of this event, under condition
  //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent(); 
}
*/

 

