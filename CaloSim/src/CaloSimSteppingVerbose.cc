// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimSteppingVerbose.cc,v 1.2 2004/01/30 17:21:26 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "CaloSimSteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimSteppingVerbose::CaloSimSteppingVerbose()
{G4cout<<"CaloSimSteppingVerbose instantiating... done"<<G4endl;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimSteppingVerbose::~CaloSimSteppingVerbose()
{}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimSteppingVerbose::StepInfo()
{
  
}   //end of StepInfo()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimSteppingVerbose::TrackingStarted()
{

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
