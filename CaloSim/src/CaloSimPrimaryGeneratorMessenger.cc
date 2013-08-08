// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimGeneratorMessenger.cc,v 1.3 2004/02/03 21:05:58 asharp Exp $
// GEANT4 tag $Name:  $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "CaloSimPrimaryGeneratorMessenger.hh"

#include "CaloSimPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"
#include "CaloSimMagneticField.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimPrimaryGeneratorMessenger::CaloSimPrimaryGeneratorMessenger(
        CaloSimPrimaryGeneratorAction* myGun) :
	myAction(myGun)
{
	G4cout << "CaloSimGeneratorMessenger instantiating... ";
	myGunDir = new G4UIdirectory("/Gun/");
	myGunDir->SetGuidance("CaloSim Gun control.");

	UseFileCmd = new G4UIcmdWithABool("/Gun/UseFile", this);
	UseFileCmd->SetGuidance(
	        "Set boolean flag for using input file (zero = no, 1 = yes)");
	UseFileCmd->SetParameterName("UseFile", false);
	UseFileCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	InputFileCmd = new G4UIcmdWithAString("/Gun/inputFile", this);
	InputFileCmd->SetGuidance("Name of the muon input file");
	InputFileCmd->SetParameterName("inputFile", false);
	InputFileCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	EnergyCmd = new G4UIcmdWithADouble("/Gun/Energy", this);
	EnergyCmd->SetGuidance("Energy of electron beam.");
	EnergyCmd->SetParameterName("Energy", false);
	EnergyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	EnergySpreadCmd = new G4UIcmdWithADouble("/Gun/EnergySpread", this);
	EnergySpreadCmd->SetGuidance("Energy Spread of electron beam, sampled in log scale.");
	EnergySpreadCmd->SetParameterName("EnergySpread", false);
	EnergySpreadCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	AngleCmd = new G4UIcmdWithADouble("/Gun/Angle", this);
	AngleCmd->SetGuidance("Starting Angle of electron beam. 0 = perp to face");
	AngleCmd->SetParameterName("Angle", false);
	AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	AngleRandCmd = new G4UIcmdWithADouble("/Gun/AngleRand", this);
	AngleRandCmd->SetGuidance("random inward offset of Angle of electron beam.");
	AngleRandCmd->SetParameterName("AngleRand", false);
	AngleRandCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	XInitCmd = new G4UIcmdWithADouble("/Gun/XInit", this);
	XInitCmd->SetGuidance("Minimum XInit of electron beam.");
	XInitCmd->SetParameterName("XInit", false);
	XInitCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	XInitRandCmd = new G4UIcmdWithADouble("/Gun/XInitRand", this);
	XInitRandCmd->SetGuidance("random +X offset of XInit of electron beam.");
	XInitRandCmd->SetParameterName("XInitRand", false);
	XInitRandCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	YInitCmd = new G4UIcmdWithADouble("/Gun/YInit", this);
	YInitCmd->SetGuidance("Minimum YInit of electron beam.");
	YInitCmd->SetParameterName("YInit", false);
	YInitCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	YInitRandCmd = new G4UIcmdWithADouble("/Gun/YInitRand", this);
	YInitRandCmd->SetGuidance("random +Y offset of YInit of electron beam.");
	YInitRandCmd->SetParameterName("YInitRand", false);
	YInitRandCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	UseMagneticField = new G4UIcmdWith3Vector("/Gun/UseMagneticField", this);
	UseMagneticField->SetGuidance("3D magnetic field stenth in Tesla");
	UseMagneticField->SetParameterName("Bx", "By", "Bz", false);
	UseMagneticField->AvailableForStates(G4State_PreInit, G4State_Idle);

	InputBeamParticle = new G4UIcmdWithAString("/Gun/InputBeamParticle", this);
	InputBeamParticle->SetGuidance("Name of initial particle type, ex. e-");
	InputBeamParticle->SetParameterName("InputBeamParticle", false);
	InputBeamParticle->AvailableForStates(G4State_PreInit, G4State_Idle);

	G4cout << "done" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimPrimaryGeneratorMessenger::~CaloSimPrimaryGeneratorMessenger()
{
	delete UseFileCmd;
	delete InputFileCmd;
	delete EnergyCmd;
	delete EnergySpreadCmd;
	delete AngleCmd;
	delete AngleRandCmd;
	delete XInitCmd;
	delete XInitRandCmd;
	delete YInitCmd;
	delete YInitRandCmd;

	delete UseMagneticField;
	delete InputBeamParticle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,
        G4String newValues)
{

	if (command == InputFileCmd)
	{
		myAction->SetInputFile(newValues);
	}
	else if (command == UseFileCmd)
	{
		myAction->SetUseFile(UseFileCmd->GetNewBoolValue(newValues));
	}
	else if (command == EnergyCmd)
	{
		myAction->SetEnergy(EnergyCmd->GetNewDoubleValue(newValues));
		printf("\n Energy: %f GeV\n", EnergyCmd->GetNewDoubleValue(newValues));
	}
	else if (command == EnergySpreadCmd)
	{
		myAction->SetEnergySpread(EnergySpreadCmd->GetNewDoubleValue(newValues));
		printf("\n Energy Spread: Energy -> Energy + %f GeV\n", EnergySpreadCmd->GetNewDoubleValue(newValues));
	}
	else if (command == AngleCmd)
	{
		myAction->SetAngle(AngleCmd->GetNewDoubleValue(newValues));
		printf("\n SetAngle:  %f Deg\n", AngleCmd->GetNewDoubleValue(newValues));
	}
	else if (command == AngleRandCmd)
	{
		myAction->SetAngleRand(AngleRandCmd->GetNewDoubleValue(newValues));
	}
	else if (command == XInitCmd)
	{
		myAction->SetXInit(XInitCmd->GetNewDoubleValue(newValues));
	}
	else if (command == XInitRandCmd)
	{
		myAction->SetXInitRand(XInitRandCmd->GetNewDoubleValue(newValues));
	}
	else if (command == YInitCmd)
	{
		myAction->SetYInit(YInitCmd->GetNewDoubleValue(newValues));
	}
	else if (command == YInitRandCmd)
	{
		myAction->SetYInitRand(YInitRandCmd->GetNewDoubleValue(newValues));
	}

	else if (command == UseMagneticField)
	{
		G4ThreeVector field = (UseMagneticField->GetNew3VectorValue(newValues))
		        * tesla;
		CaloSimMagneticField *fpMagField = new CaloSimMagneticField();
		fpMagField->SetMagFieldValue(field);
	}

	if (command == InputBeamParticle)
	{
		myAction->DefineBeamParticle(newValues);
	}

	else
		G4cout << "That command not found." << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
