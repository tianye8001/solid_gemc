// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4UnitsTable.hh"


// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "sbsgem_HitProcess.h"
#include "SolPrimaryGeneratorAction.h"

sbsgem_HitProcess :: sbsgem_HitProcess() {
    // PrimaryGeneratorAction can contain more information
    // that we want to pull out, such as info on the primary
    // track, any weighting that we want
    fPMG = NULL;
}

SolPrimaryGeneratorAction *sbsgem_HitProcess::GetPMG(){
    fPMG = SolPrimaryGeneratorAction::GetInstance();
    return fPMG;
}

PH_output sbsgem_HitProcess :: ProcessHit(MHit* aHit, gemc_opts Opt){
	PH_output out;
	out.identity = aHit->GetId();
	HCname = "SBS Gem Hit Process";

	if( !fPMG ){GetPMG();}

	double weight;
	if( fPMG ){ 
	    weight = fPMG->GetWeight(); 
	} else {
	    weight = 1.0;
	}

	// %%%%%%%%%%%%%%%%%%%
	// Raw hit information
	// %%%%%%%%%%%%%%%%%%%
	int nsteps = aHit->GetPos().size();

	// Get Total Energy deposited
	double Etot = 0;
	vector<G4double> Edep = aHit->GetEdep();
	for(int s=0; s<nsteps; s++) Etot = Etot + Edep[s];
	
	// average global positions of the hit
	
	// Want the first and last local positions
	
	double x, y, z;
	double lx_in, ly_in, lz_in;
	double lx_out, ly_out, lz_out;

	x = y = z = lx_in = ly_in = lz_in = 0;
	lx_out = ly_out = lz_out = 0;
	vector<G4ThreeVector> pos  = aHit->GetPos();
	vector<G4ThreeVector> Lpos = aHit->GetLPos();
	G4ThreeVector p = aHit->GetMom();
	
	for(int s=0; s<nsteps; s++) {
	    x  = x  +  pos[s].x()/((double) nsteps);
	    y  = y  +  pos[s].y()/((double) nsteps);
	    z  = z  +  pos[s].z()/((double) nsteps);
	}

	/*
	lx_in = Lpos[0].x();
	ly_in = Lpos[0].y();
	lz_in = Lpos[0].z();

	lx_out = Lpos[nsteps-1].x();
	ly_out = Lpos[nsteps-1].y();
	lz_out = Lpos[nsteps-1].z();
	*/

	//  I guess these should be in lab coords
	//  for the digitization software
	lx_in = pos[0].x();
	ly_in = pos[0].y();
	lz_in = pos[0].z();

	lx_out = pos[nsteps-1].x();
	ly_out = pos[nsteps-1].y();
	lz_out = pos[nsteps-1].z();

	// entrance and exit time
	double time_in = 0;
	double time_out = 0;
	vector<G4double> times = aHit->GetTime();

	time_in = times[0];
	time_out = times[nsteps-1];

	// Energy of the track
	double Ene = aHit->GetE();

	out.raws.push_back(Etot);
	out.raws.push_back(x);
	out.raws.push_back(y);
	out.raws.push_back(z);
	out.raws.push_back(lx_in);
	out.raws.push_back(ly_in);
	out.raws.push_back(lz_in);
	out.raws.push_back(time_in);
	out.raws.push_back(lx_out);
	out.raws.push_back(ly_out);
	out.raws.push_back(lz_out);
	out.raws.push_back(time_out);

	out.raws.push_back((double) aHit->GetPID());
	out.raws.push_back(aHit->GetVert().getX());
	out.raws.push_back(aHit->GetVert().getY());
	out.raws.push_back(aHit->GetVert().getZ());
	out.raws.push_back(Ene);

	out.raws.push_back(aHit->GetTId());
	out.raws.push_back(weight);
	out.raws.push_back(p.x());
	out.raws.push_back(p.y());
	out.raws.push_back(p.z());

	int id  = out.identity[0].id;
	out.dgtz.push_back(id);
	 
	return out;
}

vector<identifier>  sbsgem_HitProcess :: ProcessID(vector<identifier> id, G4Step* aStep, detector Detector, gemc_opts Opt)
{
    return id;
}











