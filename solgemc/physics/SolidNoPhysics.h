#ifndef SolidNoPhysics_H
#define SolidNoPhysics_H 1

// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4VPhysicsConstructor.hh"

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "usage.h"

class SolidNoPhysics : public G4VPhysicsConstructor
{
 public: 
   SolidNoPhysics();
   virtual ~SolidNoPhysics();

 public: 
   virtual void ConstructParticle();
   virtual void ConstructProcess();

};


#endif

