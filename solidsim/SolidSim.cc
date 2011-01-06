/*
 */

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#include "SolidEventAction.hh"
#include "SolidDetectorConstruction.hh"
#include "SolidDetectorMessenger.hh"
#include "SolidPhysicsList.hh"
#include "SolidPrimaryGeneratorAction.hh"
#include "SolidRunAction.hh"
#include "SolidOutput.hh"
#include "SolidOutputMessenger.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UImessenger.hh"

int main(int argc ,char ** argv) {
  // Set the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());

  G4RunManager* runManager = new G4RunManager;

  // Output manager needs to be created before
  // SolidDetectorConstruction so detector classes 
  // can register their output when they are created
  SolidOutput *soutput = new SolidOutput();
  new SolidOutputMessenger(soutput);

  // Initialize the geometry
  SolidDetectorConstruction *sdc = new SolidDetectorConstruction();
  new SolidDetectorMessenger(sdc);
  runManager->SetUserInitialization(sdc);
  
  // Initialize the physics 
  runManager->SetUserInitialization(new SolidPhysicsList());
  
  // Initialize the primary particles  
  runManager->SetUserAction(new SolidPrimaryGeneratorAction());

  // Run Action
  SolidRunAction* pRunAction = new SolidRunAction();
  runManager->SetUserAction(pRunAction);

  SolidEventAction* pEventAction = new SolidEventAction();
  runManager->SetUserAction(pEventAction);

  
#ifdef G4VIS_USE
  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();
#endif
  
  
  G4UIsession* session = 0;
  if (argc == 1)   // Define UI session for interactive mode.
    {
      session = new G4UIterminal();
    } 

  // Get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  if (session)   // Define UI session for interactive mode.
    { 
      G4cout<<" UI session starts ..."<< G4endl;
      UI -> ApplyCommand("/control/execute defaultMacro.mac");    
      session -> SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI -> ApplyCommand(command + fileName);
    }  

  // Job termination
#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;

  delete soutput; soutput = NULL;

  return 0;
}
