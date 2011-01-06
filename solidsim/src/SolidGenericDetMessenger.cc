#include "SolidGenericDetMessenger.hh"
#include "SolidGenericDet.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

SolidGenericDetMessenger::SolidGenericDetMessenger(SolidGenericDet *d):
fDet(d)
{
    const char *dname = d->GetDataName();
    char cmdname[255];

    sprintf(cmdname, "%s/", dname);
    fDetDir = new G4UIdirectory(cmdname);
    fDetDir->SetGuidance("Generic detector control");

    sprintf(cmdname, "%s/gatestart", dname);
    fGateStartCmd = new G4UIcmdWithADoubleAndUnit(cmdname, this);
    fGateStartCmd->SetGuidance("(F)ADC gate start");
    fGateStartCmd->SetParameterName("start", true);
    fGateStartCmd->SetUnitCategory("Time");
    fGateStartCmd->SetDefaultValue(0.0);
    fGateStartCmd->SetDefaultUnit("ns");

    sprintf(cmdname, "%s/gatestop", dname);
    fGateStopCmd = new G4UIcmdWithADoubleAndUnit(cmdname, this);
    fGateStopCmd->SetGuidance("(F)ADC gate stop");
    fGateStopCmd->SetParameterName("stop", true);
    fGateStopCmd->SetUnitCategory("Time");
    fGateStopCmd->SetDefaultValue(0.0);
    fGateStopCmd->SetDefaultUnit("ns");

    sprintf(cmdname, "%s/fadcres", dname);
    fFADCSizeCmd = new G4UIcmdWithADoubleAndUnit(cmdname, this);
    fFADCSizeCmd->SetGuidance("FADC Time Resolution");
    fFADCSizeCmd->SetParameterName("fadcres", true);
    fFADCSizeCmd->SetUnitCategory("Time");
    fFADCSizeCmd->SetDefaultValue(0.5);
    fFADCSizeCmd->SetDefaultUnit("ns");

    sprintf(cmdname, "%s/tdcthresh", dname);
    fTDCThreshCmd = new G4UIcmdWithADoubleAndUnit(cmdname, this);
    fTDCThreshCmd->SetGuidance("TDC Threshold");
    fTDCThreshCmd->SetParameterName("tdcthresh", true);
    fTDCThreshCmd->SetUnitCategory("Energy");
    fTDCThreshCmd->SetDefaultValue(0.0);
    fTDCThreshCmd->SetDefaultUnit("MeV");

    sprintf(cmdname, "%s/tdcdead", dname);
    fTDCDeadCmd = new G4UIcmdWithADoubleAndUnit(cmdname, this);
    fTDCDeadCmd->SetGuidance("TDC Deadtime");
    fTDCDeadCmd->SetParameterName("tdcdead", true);
    fTDCDeadCmd->SetUnitCategory("Time");
    fTDCDeadCmd->SetDefaultValue(0.0);
    fTDCDeadCmd->SetDefaultUnit("ns");

    return;
}

SolidGenericDetMessenger::~SolidGenericDetMessenger(){
    delete fGateStartCmd;
    delete fGateStopCmd;
    delete fFADCSizeCmd;
    delete fTDCThreshCmd;
    delete fTDCDeadCmd;
}

void SolidGenericDetMessenger::SetNewValue(G4UIcommand *cmd, G4String val){
    if( cmd == fGateStartCmd ){
	G4double gatestart = fGateStartCmd->GetNewDoubleValue(val);
	fDet->SetGateStart(gatestart);
    }
    if( cmd == fGateStopCmd ){
	G4double gatestop = fGateStopCmd->GetNewDoubleValue(val);
	fDet->SetGateStop(gatestop);
    }
    if( cmd == fFADCSizeCmd ){
	G4double size = fFADCSizeCmd->GetNewDoubleValue(val);
	fDet->SetFADCtRes(size);
    }
    if( cmd == fTDCThreshCmd ){
	G4double thresh = fTDCThreshCmd->GetNewDoubleValue(val);
	fDet->SetTDCThresh(thresh);
    }
    if( cmd == fTDCDeadCmd ){
	G4double dt = fTDCDeadCmd->GetNewDoubleValue(val);
	fDet->SetTDCDeadtime(dt);
    }
}
