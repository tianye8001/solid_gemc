#ifndef SolidPrimaryGeneratorAction_h
#define SolidPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class SolidPrimaryGeneratorMessenger;


class SolidPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
	SolidPrimaryGeneratorAction();    
	~SolidPrimaryGeneratorAction();

	void GeneratePrimaries(G4Event*);

    private:
	G4ParticleGun*                fParticleGun;
	SolidPrimaryGeneratorMessenger* fGunMessenger; 
};

#endif


