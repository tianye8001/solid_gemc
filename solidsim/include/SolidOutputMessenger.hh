#ifndef SolidOutputMessenger_h
#define SolidOutputMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SolidOutput;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

/**
*/

class SolidOutputMessenger: public G4UImessenger
{
  public:
  SolidOutputMessenger(SolidOutput* );
  ~SolidOutputMessenger();
  void SetNewValue(G4UIcommand*, G4String );
    
  private:
  
  SolidOutput *fOutput;
  G4UIdirectory *fOutDir;

  G4UIcmdWithAString *fOutputFileCmd;
  G4UIcmdWithAString *fOutputListCmd;
};
#endif
