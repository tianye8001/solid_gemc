/*
 */

#include "SolidPhysicsListMessenger.hh"
#include "SolidPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

SolidPhysicsListMessenger::SolidPhysicsListMessenger(SolidPhysicsList * physList)
:fPhysicsList(physList)
{  
}

SolidPhysicsListMessenger::~SolidPhysicsListMessenger()
{
}

void SolidPhysicsListMessenger::SetNewValue(G4UIcommand* ,G4String ) {
}






