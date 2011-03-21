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

#ifndef CaloSimPrimaryGeneratorMessenger_h
#define CaloSimPrimaryGeneratorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"

class CaloSimPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimPrimaryGeneratorMessenger: public G4UImessenger
{
public:
	CaloSimPrimaryGeneratorMessenger(CaloSimPrimaryGeneratorAction* myGun);
	~CaloSimPrimaryGeneratorMessenger();

	void SetNewValue(G4UIcommand*, G4String);

private:
	CaloSimPrimaryGeneratorAction* myAction;

	G4UIdirectory* myGunDir;

	/*  G4UIcmdWithoutParameter*   PolarizationEchoCmd;
	 G4UIcmdWithADouble* PolarizationXCmd;
	 G4UIcmdWithADouble* PolarizationYCmd;
	 G4UIcmdWithADouble* PolarizationZCmd;
	 */
	G4UIcmdWithABool* UseFileCmd;
	G4UIcmdWithADouble* EnergyCmd;
	G4UIcmdWithADouble* AngleCmd;
	G4UIcmdWithADouble* AngleRandCmd;
	G4UIcmdWithADouble* XInitCmd;
	G4UIcmdWithADouble* XInitRandCmd;
	G4UIcmdWithADouble* YInitCmd;
	G4UIcmdWithADouble* YInitRandCmd;
	G4UIcmdWithAString* InputFileCmd;

	//Additional command by Jin Huang
	G4UIcmdWith3Vector* UseMagneticField;
	G4UIcmdWithAString* InputBeamParticle;

	/*
	 G4UIcmdWithABool* StartAtRestCmd;
	 G4UIcmdWithABool* FormatWithZCmd;
	 G4UIcmdWithADoubleAndUnit* StartZCmd;
	 */

};

#endif

