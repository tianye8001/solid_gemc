/*
 */
#include "SolidPrimaryGeneratorMessenger.hh"
#include "SolidPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"

SolidPrimaryGeneratorMessenger::SolidPrimaryGeneratorMessenger(
                                             SolidPrimaryGeneratorAction* SolidGun)
:SolidAction(SolidGun)
{ 
}

SolidPrimaryGeneratorMessenger::~SolidPrimaryGeneratorMessenger()
{
}  

void SolidPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* ,G4String )                
{
}                 
