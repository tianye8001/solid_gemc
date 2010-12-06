/*
*/
#ifndef SolidPhysicsList_h 
#define SolidPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class SolidPhysicsListMessenger;

class SolidPhysicsList: public G4VModularPhysicsList
{
public:
  SolidPhysicsList();
  virtual ~SolidPhysicsList();

   void SetCuts();

private:
  SolidPhysicsListMessenger* fMessenger;
};

#endif



