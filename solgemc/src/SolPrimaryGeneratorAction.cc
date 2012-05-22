// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "SolPrimaryGeneratorAction.h"
#include "detector.h"

// %%%%%%%%%%%
// C++ headers
// %%%%%%%%%%%
#include <iostream>
using namespace std;

/*
  These allow us to get at the instance of this class anywhere
*/

int SolPrimaryGeneratorAction::__SolPrimaryGeneratorActionInit = 0;
SolPrimaryGeneratorAction 
   *SolPrimaryGeneratorAction::__SolPrimaryGeneratorActionPtr = NULL;

SolPrimaryGeneratorAction::SolPrimaryGeneratorAction(gemc_opts *opts) {
    gemcOpt = opts;
    hd_msg        = gemcOpt->args["LOG_MSG"].args + " Beam Settings >> " ;
    input_gen     = gemcOpt->args["INPUT_GEN_FILE"].args;
    GEN_VERBOSITY = gemcOpt->args["GEN_VERBOSITY"].arg;

    particleTable = G4ParticleTable::GetParticleTable();

    setBeam();

    particleGun = new G4ParticleGun(1);


    if(NP>0){
	cout << endl << hd_msg << " Luminosity Particle Type: "      << L_Particle->GetParticleName() << endl;
	cout << hd_msg << " Luminosity Particle Momentum: "    << G4BestUnit(L_Mom, "Energy") ;
	cout << endl;
	cout << hd_msg << " Luminosity Particle Direction: (theta, phi) = (" << L_Theta/deg << ", " << L_Phi/deg << ")" ;
	cout << " deg " << endl;
	cout << hd_msg << " Luminosity Particle Vertex: (" << L_vx/cm << ", " << L_vy/cm << ", " << L_vz/cm << ")" ;
	if(L_dvr + L_dvz > 0) cout << " (radius, z-spread) = (" << L_dvr/cm << ", " << L_dvz/cm << ")" ;
	cout << " cm " << endl;
	cout << hd_msg << " Number of Luminosity Particles: " << NP << endl;
	cout << hd_msg << " Luminosity Time Window: " << TWINDOW/ns << " nanoseconds." << endl ;
	cout << hd_msg << " Luminosity Time Between Bunches: " << TBUNCH/ns << " nanoseconds." << endl;
    }

    if(NP2>0){
	cout << endl << hd_msg << " Luminosity Particle 2 Type: "      << L_Particle2->GetParticleName() << endl;
	cout << hd_msg << " Luminosity Particle 2 Momentum: "    << G4BestUnit(L_Mom2, "Energy") ;
	cout << endl;
	cout << hd_msg << " Luminosity Particle 2 Direction: (theta, phi) = (" << L_Theta2/deg << ", " << L_Phi2/deg << ")" ;
	cout << " deg " << endl;
	cout << hd_msg << " Luminosity Particle Vertex: (" << L_vx2/cm << ", " << L_vy2/cm << ", " << L_vz2/cm << ")" ;
	if(L_dvr2 + L_dvz2 > 0) cout << " (radius, z-spread) = (" << L_dvr2/cm << ", " << L_dvz2/cm << ")" ;
	cout << " cm " << endl;
	cout << hd_msg << " Number of Luminosity Particles 2: " << NP2 << endl;
	cout << hd_msg << " Luminosity Time Between Bunches: " << TBUNCH2/ns << " nanoseconds." << endl;
    }

    if(__SolPrimaryGeneratorActionInit){
	fprintf(stderr, "WARNING:  SolPrimaryGeneratorAction already initialzied\n");
    } else {
	__SolPrimaryGeneratorActionPtr  = this;
	__SolPrimaryGeneratorActionInit = 1;
    }

}

void SolPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    // external generator: input file
    // SOLLUND format:
    // Header (Event Info):
    // 1               2                     3                    4               5                 6  7  8   9   10  11
    // # of Particles, weight, # of Target Nucleons, # of Target Protons, Pol. of Target, Pol. of Electron, x, y, W2, Q2, nu
    //
    // Body (Particle Info):
    // 1       2      3     4            5       6         7    8    9    10   11    12        13        14
    // index, charge, type, particle id, parent, daughter, p_x, p_y, p_z, p_t, mass, x vertex, y vertex, z vertex
    // type is 1 for particles in the detector
    if(gformat == "SOLLUND" && !gif.eof()) {
	double tmp, px, py, pz;
	int NPART, pdef, type, parent, daughter;
	gif >> NPART >> weight >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
	for(int p=0; p<NPART; p++) {
	    gif >> tmp >> tmp >> type >> pdef >> parent >> daughter >> px >> py >> pz >> tmp >> tmp >> Vx >> Vy >> Vz;
	    if(type == 1) {
		// Primary Particle
		Particle = particleTable->FindParticle(pdef);
		if(!Particle) {
		    cout << hd_msg << " Particle id " << pdef << " not found in G4 table." << endl << endl;

		    return;
		}
		particleGun->SetParticleDefinition(Particle);

		// 4-momenta
		G4ThreeVector pmom(px*GeV, py*GeV, pz*GeV);
		Mom = pmom.mag();
		Phi   = pmom.getPhi();
		Theta = pmom.getTheta();
		double mass = Particle->GetPDGMass();
		double akine = sqrt(Mom*Mom + mass*mass) - mass ;

		beam_dir = G4ThreeVector(cos(Phi/rad)*sin(Theta/rad), sin(Phi/rad)*sin(Theta/rad), cos(Theta/rad));
		particleGun->SetParticleEnergy(akine);
		particleGun->SetParticleMomentumDirection(beam_dir);

		// vertex
		beam_vrt = G4ThreeVector(Vx*cm, Vy*cm, Vz*cm);
		particleGun->SetParticlePosition(beam_vrt);

		// polarization
		beam_pol = G4ThreeVector( 0.0, 0.0, 0.0 );
		particleGun->SetParticlePolarization(beam_pol);
		
		// Primary particle generated int the middle of Time window
		particleGun->SetParticleTime(TWINDOW/2);
		particleGun->GeneratePrimaryVertex(anEvent);
		if(GEN_VERBOSITY > 3)
		    cout << hd_msg << " Particle Number:  " << p << ", id=" << pdef << "(" << Particle->GetParticleName() << ")" 
			<< "  Vertex=" << beam_vrt/cm << "cm,  momentum=" << pmom/GeV << " GeV" << endl;
	    }
	}
    }



    // Luminosity Particles
    int NBUNCHES   = (int) floor(TWINDOW/TBUNCH);
    int PBUNCH     = (int) floor((double)NP/NBUNCHES);

    particleGun->SetParticleDefinition(L_Particle);
    particleGun->SetParticlePosition(L_beam_vrt);
    double L_mass = L_Particle->GetPDGMass();
    double L_akine = sqrt(L_Mom*L_Mom + L_mass*L_mass) - L_mass ;



    particleGun->SetParticleEnergy(L_akine);
    particleGun->SetParticleMomentumDirection(L_beam_dir);
    for(int b=0; b<NBUNCHES; b++)
    {
	for(int p=0; p<PBUNCH; p++)
	{
	    // luminosity vertex
	    double L_VR  = G4UniformRand()*L_dvr/mm;
	    double L_PHI = 2.0*pi*G4UniformRand();
	    L_vx = L_beam_vrt.x()/mm + L_VR*cos(L_PHI);
	    L_vy = L_beam_vrt.y()/mm + L_VR*sin(L_PHI);
	    L_vz = L_beam_vrt.z()/mm + (2.0*G4UniformRand()-1.0)*L_dvz/mm;
	    G4ThreeVector LUMI_V(L_vx, L_vy, L_vz);
	    particleGun->SetParticlePosition(LUMI_V);

	    particleGun->  SetParticleTime(TBUNCH*b);
	    particleGun->GeneratePrimaryVertex(anEvent);
	}
    }


    // Luminosity Particles2
    int NBUNCHES2   = (int) floor(TWINDOW/TBUNCH2);
    int PBUNCH2     = (int) floor((double)NP2/NBUNCHES2);

    particleGun->SetParticleDefinition(L_Particle2);
    particleGun->SetParticlePosition(L_beam_vrt2);
    double L_mass2 = L_Particle2->GetPDGMass();
    double L_akine2 = sqrt(L_Mom2*L_Mom2 + L_mass2*L_mass2) - L_mass2 ;



    particleGun->SetParticleEnergy(L_akine2);
    particleGun->SetParticleMomentumDirection(L_beam_dir2);
    for(int b=0; b<NBUNCHES2; b++)
	for(int p=0; p<PBUNCH2; p++)
	{
	    // luminosity vertex 2
	    double L_VR  = G4UniformRand()*L_dvr2/mm;
	    double L_PHI = 2.0*pi*G4UniformRand();
	    L_vx2 = L_beam_vrt2.x()/mm + L_VR*cos(L_PHI);
	    L_vy2 = L_beam_vrt2.y()/mm + L_VR*sin(L_PHI);
	    L_vz2 = L_beam_vrt2.z()/mm + (2.0*G4UniformRand()-1.0)*L_dvz2/mm;
	    G4ThreeVector LUMI_V(L_vx2, L_vy2, L_vz2);
	    particleGun->SetParticlePosition(LUMI_V);

	    particleGun->  SetParticleTime(TBUNCH2*b);
	    particleGun->GeneratePrimaryVertex(anEvent);
	}
}








void SolPrimaryGeneratorAction::setBeam() {
    string hd_msg    = gemcOpt->args["LOG_MSG"].args + " Beam Settings >> " ;

    gformat.assign(  input_gen, 0, input_gen.find(",")) ;
    gfilename.assign(input_gen,    input_gen.find(",") + 1, input_gen.size()) ;
    cout << hd_msg << " Opening  " << gformat << " file: " << TrimSpaces(gfilename).c_str() << endl;
    gif.open(TrimSpaces(gfilename).c_str());
    if(!gif)
    {
	cerr << hd_msg << " Can't open input file " << TrimSpaces(gfilename).c_str() << ". Exiting. " << endl;
	exit(1);
    }


    // %%%%%%%%%%%%%%%
    // Luminosity Beam
    // %%%%%%%%%%%%%%%
    string L_beam     = gemcOpt->args["LUMI_P"].args;
    string L_vert     = gemcOpt->args["LUMI_V"].args;
    string L_vert_s   = gemcOpt->args["LUMI_SPREAD_V"].args;

    string L_blockstr;
    int L_ppos = L_beam.find(",");
    L_blockstr.assign(L_beam, 0, L_ppos);

    L_Particle = particleTable->FindParticle(L_blockstr);

    if(!L_Particle)
    {
	if(L_blockstr == "show_all")
	{
	    for(int i=0; i<particleTable->entries(); i++) 
		cout << hd_msg << " g4 particle: " << particleTable->GetParticleName(i) << endl;
	}
	else
	    cout << hd_msg << " Particle " << L_blockstr << " not found in G4 table. Exiting" << endl << endl;

	exit(0);
    }

    // %%%%%%%%%%%%%%%%%%%
    // Luminosity Momentum
    // %%%%%%%%%%%%%%%%%%%
    // energy
    L_beam.assign(L_beam, L_ppos+1, L_beam.size());
    L_ppos = L_beam.find(",");
    L_blockstr.assign(L_beam, 0, L_ppos);
    L_Mom = get_number(L_blockstr);
    // theta angle
    L_beam.assign(L_beam, L_ppos+1, L_beam.size());
    L_ppos = L_beam.find(",");
    L_blockstr.assign(L_beam, 0, L_ppos);
    L_Theta =  get_number(L_blockstr);
    // phi angle
    L_beam.assign(L_beam, L_ppos+1, L_beam.size());
    L_ppos = L_beam.find("\"");
    L_blockstr.assign(L_beam, 0, L_ppos);
    L_Phi =  get_number(L_blockstr);

    L_beam_dir = G4ThreeVector(cos(L_Phi/rad)*sin(L_Theta/rad), sin(L_Phi/rad)*sin(L_Theta/rad), cos(L_Theta/rad));

    // %%%%%%%%%%%%%%%%%
    // Luminosity Vertex
    // %%%%%%%%%%%%%%%%%
    // units
    L_ppos = L_vert.find(")");
    string L_units;
    L_units.assign(L_vert, L_ppos+1, L_vert.size() - L_ppos);
    // vx
    L_ppos = L_vert.find("(");
    L_vert.assign(L_vert, L_ppos+1, L_vert.size()); 
    L_ppos = L_vert.find(",");
    L_blockstr.assign(L_vert, 0, L_ppos);
    L_vx = get_number(L_blockstr + "*" + L_units); 
    // vy
    L_ppos = L_vert.find(",");
    L_vert.assign(L_vert, L_ppos+1, L_vert.size());
    L_ppos = L_vert.find(",");
    L_blockstr.assign(L_vert, 0, L_ppos);
    L_vy = get_number(L_blockstr + "*" + L_units);
    // vz
    L_ppos = L_vert.find(",");
    L_vert.assign(L_vert, L_ppos+1, L_vert.size());
    L_ppos = L_vert.find(",");
    L_blockstr.assign(L_vert, 0, L_ppos);
    L_vz = get_number(L_blockstr + "*" + L_units);
    L_beam_vrt = G4ThreeVector(L_vx, L_vy, L_vz);

    // %%%%%%%%%%%%%%%%%%%%%%%%
    // Luminosity Vertex Spread
    // %%%%%%%%%%%%%%%%%%%%%%%%
    L_ppos = L_vert_s.find(")");
    L_units.assign(L_vert_s, L_ppos+1, L_vert_s.size() - L_ppos);
    // dvr
    L_ppos = L_vert_s.find("(");
    L_vert_s.assign(L_vert_s, L_ppos+1, L_vert_s.size());
    L_ppos = L_vert_s.find(",");
    L_blockstr.assign(L_vert_s, 0, L_ppos);
    L_dvr = get_number(L_blockstr + "*" + L_units);
    // dvz
    L_ppos = L_vert_s.find(",");
    L_vert_s.assign(L_vert_s, L_ppos+1, L_vert_s.size());
    L_ppos = L_vert_s.find(",");
    L_blockstr.assign(L_vert_s, 0, L_ppos);
    L_dvz = get_number(L_blockstr + "*" + L_units);


    // %%%%%%%%%%%%%%%%%%%%%
    // Luminosity Parameters
    // %%%%%%%%%%%%%%%%%%%%%
    string L_pars = gemcOpt->args["LUMI_EVENT"].args;
    // NP
    L_ppos = L_pars.find(",");
    L_blockstr.assign(L_pars, 0, L_ppos);
    NP = atoi(L_blockstr.c_str());
    // TWINDOW
    L_ppos = L_pars.find(",");
    L_pars.assign(L_pars, L_ppos+1, L_pars.size());
    L_ppos = L_pars.find(",");
    L_blockstr.assign(L_pars, 0, L_ppos);
    TWINDOW = get_number(L_blockstr);
    // TBUNCH
    L_ppos = L_pars.find(",");
    L_pars.assign(L_pars, L_ppos+1, L_pars.size());
    L_ppos = L_pars.find(",");
    L_blockstr.assign(L_pars, 0, L_ppos-1);
    TBUNCH = get_number(L_blockstr);





    // %%%%%%%%%%%%%%%%%
    // Luminosity Beam 2
    // %%%%%%%%%%%%%%%%%
    string L_beam2     = gemcOpt->args["LUMI2_P"].args;
    string L_vert2     = gemcOpt->args["LUMI2_V"].args;
    string L_vert_s2   = gemcOpt->args["LUMI2_SPREAD_V"].args;

    L_ppos = L_beam2.find(",");
    L_blockstr.assign(L_beam2, 0, L_ppos);

    L_Particle2 = particleTable->FindParticle(L_blockstr);

    if(!L_Particle2)
    {
	if(L_blockstr == "show_all")
	{
	    for(int i=0; i<particleTable->entries(); i++)
		cout << hd_msg << " g4 particle: " << particleTable->GetParticleName(i) << endl;
	}
	else
	    cout << hd_msg << " Particle " << L_blockstr << " not found in G4 table. Exiting" << endl << endl;

	exit(0);
    }

    // %%%%%%%%%%%%%%%%%%%%%
    // Luminosity Momentum 2
    // %%%%%%%%%%%%%%%%%%%%%
    // energy
    L_beam2.assign(L_beam2, L_ppos+1, L_beam2.size());
    L_ppos = L_beam2.find(",");
    L_blockstr.assign(L_beam2, 0, L_ppos);
    L_Mom2 = get_number(L_blockstr);
    // theta angle
    L_beam2.assign(L_beam2, L_ppos+1, L_beam2.size());
    L_ppos = L_beam2.find(",");
    L_blockstr.assign(L_beam2, 0, L_ppos);
    L_Theta2 =  get_number(L_blockstr);
    // phi angle
    L_beam2.assign(L_beam2, L_ppos+1, L_beam2.size());
    L_ppos = L_beam2.find("\"");
    L_blockstr.assign(L_beam2, 0, L_ppos);
    L_Phi2 =  get_number(L_blockstr);

    L_beam_dir2 = G4ThreeVector(cos(L_Phi2/rad)*sin(L_Theta2/rad), sin(L_Phi2/rad)*sin(L_Theta2/rad), cos(L_Theta2/rad));

    // %%%%%%%%%%%%%%%%%%%
    // Luminosity Vertex 2
    // %%%%%%%%%%%%%%%%%%%
    // units
    L_ppos = L_vert2.find(")");
    L_units.assign(L_vert2, L_ppos+1, L_vert2.size() - L_ppos);
    // vx
    L_ppos = L_vert2.find("(");
    L_vert2.assign(L_vert2, L_ppos+1, L_vert2.size());
    L_ppos = L_vert2.find(",");
    L_blockstr.assign(L_vert2, 0, L_ppos);
    L_vx2 = get_number(L_blockstr + "*" + L_units);
    // vy
    L_ppos = L_vert2.find(",");
    L_vert2.assign(L_vert2, L_ppos+1, L_vert2.size());
    L_ppos = L_vert2.find(",");
    L_blockstr.assign(L_vert2, 0, L_ppos);
    L_vy2 = get_number(L_blockstr + "*" + L_units);
    // vz
    L_ppos = L_vert2.find(",");
    L_vert2.assign(L_vert2, L_ppos+1, L_vert2.size());
    L_ppos = L_vert2.find(",");
    L_blockstr.assign(L_vert2, 0, L_ppos);
    L_vz2 = get_number(L_blockstr + "*" + L_units);
    L_beam_vrt2 = G4ThreeVector(L_vx2, L_vy2, L_vz2);

    // %%%%%%%%%%%%%%%%%%%%%%%%%%
    // Luminosity Vertex Spread 2
    // %%%%%%%%%%%%%%%%%%%%%%%%%%
    L_ppos = L_vert_s2.find(")");
    L_units.assign(L_vert_s2, L_ppos+1, L_vert_s2.size() - L_ppos);
    // dvr
    L_ppos = L_vert_s2.find("(");
    L_vert_s2.assign(L_vert_s2, L_ppos+1, L_vert_s2.size());
    L_ppos = L_vert_s2.find(",");
    L_blockstr.assign(L_vert_s2, 0, L_ppos);
    L_dvr2 = get_number(L_blockstr + "*" + L_units);
    // dvz
    L_ppos = L_vert_s2.find(",");
    L_vert_s2.assign(L_vert_s2, L_ppos+1, L_vert_s2.size());
    L_ppos = L_vert_s2.find(",");
    L_blockstr.assign(L_vert_s2, 0, L_ppos);
    L_dvz2 = get_number(L_blockstr + "*" + L_units);


    // %%%%%%%%%%%%%%%%%%%%%
    // Luminosity Parameters
    // %%%%%%%%%%%%%%%%%%%%%
    string L_pars2 = gemcOpt->args["LUMI2_EVENT"].args;
    // NP
    L_ppos = L_pars2.find(",");
    L_blockstr.assign(L_pars2, 0, L_ppos);
    NP2 = atoi(L_blockstr.c_str());
    // TBUNCH
    L_ppos = L_pars2.find(",");
    L_pars2.assign(L_pars2, L_ppos+1, L_pars2.size());
    L_ppos = L_pars2.find(",");
    L_blockstr.assign(L_pars2, 0, L_ppos-1);
    TBUNCH2 = get_number(L_blockstr);







}

SolPrimaryGeneratorAction *SolPrimaryGeneratorAction::GetInstance(){
    if( __SolPrimaryGeneratorActionInit ){
	return __SolPrimaryGeneratorActionPtr;
    } 
    return NULL;
}

SolPrimaryGeneratorAction::~SolPrimaryGeneratorAction()
{
    delete particleGun;
    gif.close();
}
