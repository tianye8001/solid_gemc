#ifndef CaloSimPhysicsList_h
#define CaloSimPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class CaloSimPhysicsList: public G4VUserPhysicsList
{
  public:
    CaloSimPhysicsList();
    ~CaloSimPhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();


  protected:
    // these methods Construct particles 
    void ConstructBosons();
    void ConstructLeptons();
      void ConstructMesons();
  //    void ConstructBaryons();

  protected:
  // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();
    void ConstructHadron();


};

#endif







