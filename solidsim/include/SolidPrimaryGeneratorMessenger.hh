/*
*/

#ifndef SolidPrimaryGeneratorMessenger_h
#define SolidPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class SolidPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class SolidPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    SolidPrimaryGeneratorMessenger(SolidPrimaryGeneratorAction*);
   ~SolidPrimaryGeneratorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);

 private:
    SolidPrimaryGeneratorAction* SolidAction; 
};

#endif

