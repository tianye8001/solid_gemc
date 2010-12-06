#ifndef SolidEventMessenger_h
#define SolidEventMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SolidEventAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

/*
*/

class SolidEventMessenger: public G4UImessenger
{
  public:
  SolidEventMessenger(SolidEventAction* );
  ~SolidEventMessenger();
  void SetNewValue(G4UIcommand*, G4String );
    
private:

};
#endif
