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

  void ConstructParticle();
  void ConstructProcess();

   void SetCuts();

private:
  SolidPhysicsListMessenger* fMessenger;
  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  particleList;

};

#endif



