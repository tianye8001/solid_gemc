// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
//#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4BaryonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4IonConstructor.hh"

// %%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%
#include "SolidNoPhysics.h"


SolidNoPhysics::SolidNoPhysics() : G4VPhysicsConstructor("Solid No Physics")
{ }

SolidNoPhysics::~SolidNoPhysics(){}

void SolidNoPhysics::ConstructParticle()
{
    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor ionConstruct;
    ionConstruct.ConstructParticle();
}

void SolidNoPhysics::ConstructProcess()
{
    // string hd_msg = gemcOpt.args["LOG_MSG"].args + "Solid No Physics List: <<< ";
    // double   VERB = gemcOpt.args["PHY_VERBOSITY"].arg ;

}
