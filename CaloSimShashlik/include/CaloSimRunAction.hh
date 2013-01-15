// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimRunAction.hh,v 1.4 2004/02/03 21:10:48 asharp Exp $
// GEANT4 tag $Name:  $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#ifndef CaloSimRunAction_h
#define CaloSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class G4Run;

class CaloSimRunAction: public G4UserRunAction
{
public:
	CaloSimRunAction();
	~CaloSimRunAction();

	G4int GetRunID() const
	{
		return runID;
	};

public:
	void BeginOfRunAction(const G4Run*);
	//  void BeginOfRunAction(const G4Run*, const G4int);
	void EndOfRunAction(const G4Run*);

private:
	G4int runID;
};

#endif

