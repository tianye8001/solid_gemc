#ifndef SolidDetectorMessenger_h
#define SolidDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SolidDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

/**
*/

class SolidDetectorMessenger: public G4UImessenger
{
  public:
  SolidDetectorMessenger(SolidDetectorConstruction* );
  ~SolidDetectorMessenger();
  void SetNewValue(G4UIcommand*, G4String );
    
private:

};
#endif
