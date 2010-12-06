#ifndef SolidPhysicsListMessenger_h
#define SolidPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SolidPhysicsList;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

/**
*/

class SolidPhysicsListMessenger: public G4UImessenger {

public:
  
  SolidPhysicsListMessenger(SolidPhysicsList* physList);
  ~SolidPhysicsListMessenger();
  void SetNewValue(G4UIcommand*,G4String );
  
private:
  SolidPhysicsList* fPhysicsList;   
};

#endif








