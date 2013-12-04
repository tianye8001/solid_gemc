#include <iostream>
using namespace std;

#include "Randomize.hh"

#include "SolEventAction.h"

SolEventAction::SolEventAction(gemc_opts opts, map<string, double> gpars)
  : MEventAction (opts, gpars),
    fSaveMe (false),
    fSaveRandFile (NULL),
    fSaveInputFile (NULL),
    fRestoreRandFile (NULL)
{
  string saverandfilename = gemcOpt.args["SAVE_RAND_FILE"].args;
  if (saverandfilename != "")
    {
      fSaveRandFile = new ofstream (saverandfilename.c_str());
    }
  string saveinputfilename = gemcOpt.args["SAVE_INPUT_FILE"].args;
  if (saveinputfilename != "")
    {
      fSaveInputFile = new ofstream (saveinputfilename.c_str());
    }
  string restorerandfilename = gemcOpt.args["RESTORE_RAND_FILE"].args;
  if (restorerandfilename != "")
    {
      fRestoreRandFile = new ifstream (restorerandfilename.c_str());
    }
}

SolEventAction::~SolEventAction()
{
  if (fSaveRandFile != NULL)
    {
      fSaveRandFile->close();
      delete fSaveRandFile;
    }
  if (fSaveInputFile != NULL)
    {
      fSaveInputFile->close();
      delete fSaveInputFile;
    }
  if (fRestoreRandFile != NULL)
    {
      fRestoreRandFile->close();
      delete fRestoreRandFile;
    }
}

void SolEventAction::BeginOfEventAction(const G4Event* evt)
{
  MEventAction::BeginOfEventAction (evt);

  // If requested, get saved RNG state from file
  if (fRestoreRandFile != NULL && !fRestoreRandFile->eof())
    {
      CLHEP::HepRandom::restoreFullState (*fRestoreRandFile);
      if (fRestoreRandFile->eof())
	cerr << "End of saved RNG file" << endl;
    }
  
  if (fSaveRandFile != NULL)
    {
      fSaveMe = false;
      fSaveRand.str ("");
      fSaveRand.clear();
      CLHEP::HepRandom::saveFullState (fSaveRand);
    }
  if (fSaveInputFile != NULL)
    {
      fSaveMe = false;
    }

}

void SolEventAction::EndOfEventAction(const G4Event* evt)
{
  MEventAction::EndOfEventAction (evt);
  if (fSaveRandFile != NULL && fSaveMe)
    {
      *fSaveRandFile << fSaveRand.str();
    }
  if (fSaveInputFile != NULL && fSaveMe)
    {
      *fSaveInputFile << fSaveInput.str();
    }
}
