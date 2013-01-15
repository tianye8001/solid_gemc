// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimDetectorMessenger.hh,v 1.2 2004/02/03 21:09:28 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#ifndef CaloSimGeneratorMessenger_h
#define CaloSimGeneratorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CaloSimPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimGeneratorMessenger: public G4UImessenger
{
public:
  CaloSimGeneratorMessenger(CaloSimPrimaryGeneratorAction*);
  ~CaloSimGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  CaloSimPrimaryGeneratorAction* myGenerator;
  
  G4UIdirectory*             mygenDir;

  /*  G4UIcmdWithoutParameter*   PolarizationEchoCmd;
  G4UIcmdWithADouble* PolarizationXCmd;
  G4UIcmdWithADouble* PolarizationYCmd;
  G4UIcmdWithADouble* PolarizationZCmd;
  */

  G4UIcmdWithADouble* EnergyCmd;
  G4UIcmdWithADouble* AngleCmd;
  G4UIcmdWithAString* InputFileCmd;
  G4UIcmdWithoutParameter*   UpdateCmd;  
  /*
  G4UIcmdWithABool* StartAtRestCmd;
  G4UIcmdWithABool* FormatWithZCmd;
  G4UIcmdWithADoubleAndUnit* StartZCmd;
  */


};

#endif

