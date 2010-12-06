/*
*/

#ifndef SolidRunMessenger_h
#define SolidRunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SolidRunAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

class SolidRunMessenger: public G4UImessenger
{
    public:
	SolidRunMessenger(SolidRunAction* );
	~SolidRunMessenger();
	void SetNewValue(G4UIcommand*, G4String );

    private:

};
#endif
