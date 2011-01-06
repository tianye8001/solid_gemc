#ifndef __SOLIDGENERICDETMESSENGER
#define __SOLIDGENERICDETMESSENGER

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"

class SolidGenericDet;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class SolidGenericDetMessenger: public G4UImessenger {
    public:
	SolidGenericDetMessenger(SolidGenericDet *);
	~SolidGenericDetMessenger();
	void SetNewValue(G4UIcommand *, G4String );

    private:
	SolidGenericDet *fDet;

	G4UIdirectory *fDetDir;

	G4UIcmdWithADoubleAndUnit *fGateStartCmd;
	G4UIcmdWithADoubleAndUnit *fGateStopCmd;
	G4UIcmdWithADoubleAndUnit *fFADCSizeCmd;
	G4UIcmdWithADoubleAndUnit *fTDCThreshCmd;
	G4UIcmdWithADoubleAndUnit *fTDCDeadCmd;
};

#endif//__SOLIDGENERICDETMESSENGER
