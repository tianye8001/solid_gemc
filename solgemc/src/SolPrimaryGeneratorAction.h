#ifndef SolPrimaryGeneratorAction_h
#define SolPrimaryGeneratorAction_h 1

// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "usage.h"

// %%%%%%%%%%%
// C++ headers
// %%%%%%%%%%%
#include <fstream>


// %%%%%%%%%%%%%%%%
// Class definition
// %%%%%%%%%%%%%%%%
class SolPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
	SolPrimaryGeneratorAction(gemc_opts*);
	~SolPrimaryGeneratorAction();

    public:
	void GeneratePrimaries(G4Event* anEvent);
	gemc_opts *gemcOpt;
	double GEN_VERBOSITY;

	double GetWeight(){ return weight; }
    private:
	string input_gen;                 ///< Input Option
	string hd_msg;                    ///< Head Message Log
	G4ParticleTable* particleTable;   ///< Geant4 Particle Table

	// Primary Beam
	G4ParticleDefinition *Particle;   ///< Particle type
	double mom,   dmom,    Mom;       ///< beam momentum, delta momentum, randomized momentum
	double theta, dtheta,  Theta;     ///< theta, delta theta, randomized theta
	double phi,   dphi,    Phi;       ///< phi, delta phi, randomized phi
	double vx, vy, vz;                ///< Beam Vertex coordinates
	double dvr, dvz;                  ///< Deltas Beam Vertex: Radius and z-vertex
	double Vx, Vy, Vz;                ///< Randomized Beam Vertex coordinates
	double weight;
	double polDeg, polTheta, polPhi;  ///< Polarization degree and  direction
	G4ThreeVector beam_dir;           ///< beam direction
	G4ThreeVector beam_vrt;           ///< beam vertex
	G4ThreeVector beam_pol;           ///< beam polarization vector

	// Generators Input Files
	ifstream  gif;                    ///< Generator Input File
	string    gformat;                ///< Generator Format. Supported: LUND.
	string    gfilename;              ///< Input Filename


	// Luminosity Beam
	G4ParticleDefinition *L_Particle; ///< Luminosity Particle type
	double L_Mom;                     ///< Luminosity beam momentum
	double L_Theta;                   ///< theta
	double L_Phi;                     ///< phi
	double L_vx, L_vy, L_vz;          ///< Luminosity Beam Vertex coordinates
	double L_dvr,  L_dvz;             ///< Luminosity Deltas Beam Vertex: Radius and z-vertex
	int NP;                           ///< Number of Luminosity Particles per event
	double TWINDOW;                   ///< Time Window
	double TBUNCH;                    ///< Time Between Bunches
	G4ThreeVector L_beam_dir;         ///< Luminosity beam direction
	G4ThreeVector L_beam_vrt;         ///< Luminosity beam vertex

	// Luminosity Beam2
	G4ParticleDefinition *L_Particle2; ///< Luminosity Particle type
	double L_Mom2;                     ///< Luminosity beam momentum
	double L_Theta2;                   ///< theta
	double L_Phi2;                     ///< phi
	double L_vx2, L_vy2, L_vz2;        ///< Luminosity Beam Vertex coordinates
	double L_dvr2,  L_dvz2;            ///< Luminosity Deltas Beam Vertex: Radius and z-vertex
	int NP2;                           ///< Number of Luminosity Particles per event
	double TBUNCH2;                    ///< Time Between Bunches
	G4ThreeVector L_beam_dir2;         ///< Luminosity beam direction
	G4ThreeVector L_beam_vrt2;         ///< Luminosity beam vertex


	G4ParticleGun* particleGun;
	void setBeam();

	// These functions allow us to get at the instance
	// of this class anywhere
    public:
	static SolPrimaryGeneratorAction *GetInstance();
    private:
	static int __SolPrimaryGeneratorActionInit;
	static SolPrimaryGeneratorAction *__SolPrimaryGeneratorActionPtr;
};

#endif


