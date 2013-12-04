/// \file SolEventAction.h
/// Derived from MEventAction.\n
/// Adds provisions for saving and restoring random number state
/// \author \n Rich Holmes
/// \author mail: rsholmes@phy.syr.edu\n\n\n
#ifndef SolEventAction_H
#define SolEventAction_H 1

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "MEventAction.h"

/// \class SolEventAction
/// <b> SolEventAction </b>\n\n
/// Derived from MEventAction.\n
/// The two functions:
/// - BeginOfEventAction
/// - EndOfEventAction
/// define the routines at the begin
/// and at the end of each event.\n
/// In EndOfEventAction the output is written out
/// (if the output option is selected)
class SolEventAction : public MEventAction
{
 public:
  SolEventAction(gemc_opts, map<string, double>);       ///< Constructor copies gemc options
  ~SolEventAction();                                    ///< Destructor
    
 private:
  stringstream fSaveRand;
  stringstream fSaveInput;
  bool fSaveMe;
  std::ofstream* fSaveRandFile;
  std::ofstream* fSaveInputFile;
  std::ifstream* fRestoreRandFile;

 public:
  void BeginOfEventAction(const G4Event*);            ///< Routine at the start of each event
  void EndOfEventAction(const G4Event*);              ///< Routine at the end of each event
  void SaveMe() {fSaveMe = true;}
  stringstream& SaveInput() {return fSaveInput;}
};

#endif




