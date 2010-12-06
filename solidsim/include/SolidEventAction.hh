#ifndef SolidEventAction_h
#define SolidEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/*!
  SolidEventAction
*/

class SolidEventAction : public G4UserEventAction
{
public:
  SolidEventAction();
  ~SolidEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
    
private: 
  G4int fHitsCollectionID;
};

#endif



