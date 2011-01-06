/*
*/

#include "SolidOutputMessenger.hh"
#include "SolidOutput.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

SolidOutputMessenger::SolidOutputMessenger( SolidOutput*sout)
: fOutput(sout) { 
    fOutDir = new G4UIdirectory("/output/");
    fOutDir->SetGuidance("Detector construction control");

    fOutputFileCmd = new G4UIcmdWithAString("/output/outfile", this);
    fOutputListCmd = new G4UIcmdWithAString("/output/outlist", this);
    
}

SolidOutputMessenger::~SolidOutputMessenger() { 
    delete fOutputFileCmd;
    delete fOutputListCmd;
}

void SolidOutputMessenger::SetNewValue(G4UIcommand *cmd, G4String val){
	if( cmd->GetCommandName() == "outfile" ){
	    fOutput->SetOutputFile(val);
	}
	if(  cmd->GetCommandName() == "outlist"){
	    fOutput->SetOutputList(val);
	}
}
