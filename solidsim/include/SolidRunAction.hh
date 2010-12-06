#ifndef SolidRunAction_h
#define SolidRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4RunManager.hh"
#include "globals.hh"

class G4Run;
class SolidRunMessenger;

/**
 * SolidRunAction
 *
 * Call things to initialize
 */

class SolidRunAction : public G4UserRunAction {
    public:
	SolidRunAction();
	~SolidRunAction();

    public:
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run* );

    private:  
};
#endif



