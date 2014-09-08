#ifndef CaloSimPrimaryGeneratorAction_h
#define CaloSimPrimaryGeneratorAction_h 1
#include <stdio.h>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4String.hh"
#include <G4ios.hh>
#include <assert.h>
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

class CaloSimDetectorConstruction;
class G4ParticleGun;
class G4Event;
class CaloSimPrimaryGeneratorMessenger;

class CaloSimPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
	CaloSimPrimaryGeneratorAction(CaloSimDetectorConstruction*);
	~CaloSimPrimaryGeneratorAction();

public:
	void GeneratePrimaries(G4Event* anEvent);
	CaloSimPrimaryGeneratorMessenger* generatorMessenger; //pointer to the Messenger

	bool DefineBeamParticle(G4String particleName = "e-");
	inline void SetUseFile(G4bool usefile)
	{
		if (usefile) G4cout << "Set to use Gun Input file " << G4endl;
		fUseFile = usefile;
	}
	inline void SetEnergy(G4double energy)
	{
		fEnergy = energy;
	}
	inline void SetEnergySpread(G4double energy)
	{
		assert(energy>=0);
		if (energy<1e-6) energy = 1e-6;
		fEnergySpread = energy;
	}
	inline void SetAngle(G4double angle)
	{
		fAngle = angle;
	}
	inline void SetAngleRand(G4double anglerand)
	{
		fAngleRand = anglerand;
	}
	inline void SetXInit(G4double xinit)
	{
		fXInit = xinit;
	}
	inline void SetXInitRand(G4double xinitrand)
	{
		fXInitRand = xinitrand;
	}
	inline void SetYInit(G4double yinit)
	{
		fYInit = yinit;
	}
	inline void SetYInitRand(G4double yinitrand)
	{
		fYInitRand = yinitrand;
	}

	void SetInputFile(G4String fname);
//	{
//		G4cout << "Use Gun Input file " << fname << G4endl;
//		fFilename = fname;
//	}

private:
	G4ParticleGun* particleGun;
	CaloSimDetectorConstruction* myDetector;

	G4double fEnergy, fEnergySpread, fAngle, fAngleRand, fXInit, fXInitRand, fYInit,
	        fYInitRand;
	G4String fFilename;

	G4bool fUseFile;

	FILE *elecfile;

	G4int evcnt;

};

#endif

