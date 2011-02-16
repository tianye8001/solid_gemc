#ifndef SolidNoPhysicsList_H
#define SolidNoPhysicsList_H 1

// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4VModularPhysicsList.hh"

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "usage.h"

class SolidNoPhysicsList: public G4VModularPhysicsList
{
 public:
   SolidNoPhysicsList(gemc_opts);
   virtual ~SolidNoPhysicsList();
   gemc_opts gemcOpt;  
  
 public:
   virtual void SetCuts();

};


#endif

