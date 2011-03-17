// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimSteppingVerbose.hh,v 1.1.1.1 2003/10/24 19:10:20 asharp Exp $
// GEANT4 tag $Name:  $
//
//   This class manages the verbose outputs in G4SteppingManager. 
//   It inherits from G4SteppingVerbose.
//   It shows how to extract informations during the tracking of a particle.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimSteppingVerbose;

#ifndef CaloSimSteppingVerbose_h
#define CaloSimSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimSteppingVerbose : public G4SteppingVerbose {

public:
   
  CaloSimSteppingVerbose();
 ~CaloSimSteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

#endif
