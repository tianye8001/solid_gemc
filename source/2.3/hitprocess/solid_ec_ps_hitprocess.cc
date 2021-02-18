// G4 headers
#include "G4UnitsTable.hh"
#include "G4Poisson.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// gemc headers
#include "solid_ec_ps_hitprocess.h"

map<string, double> solid_ec_ps_HitProcess :: integrateDgt(MHit* aHit, int hitn)
{
	map<string, double> dgtz;	
	vector<identifier> identity = aHit->GetId();

	trueInfos tInfos(aHit);

	int id = identity[0].id;
	
	dgtz["hitn"] = hitn;
	dgtz["id"]  =  id;
	
	dgtz["pid"]     = (double) aHit->GetPID();
	dgtz["mpid"]    = (double) aHit->GetmPID();
	dgtz["tid"]     = (double) aHit->GetTId();
	dgtz["mtid"]    = (double) aHit->GetmTrackId();
	dgtz["otid"]    = (double) aHit->GetoTrackId();
	dgtz["trackE"]  = aHit->GetE();
	dgtz["totEdep"] = tInfos.eTot;
	dgtz["avg_x"]   = tInfos.x;
	dgtz["avg_y"]   = tInfos.y;
	dgtz["avg_z"]   = tInfos.z;
	dgtz["avg_lx"]  = tInfos.lx;
	dgtz["avg_ly"]  = tInfos.ly;
	dgtz["avg_lz"]  = tInfos.lz;
	dgtz["px"]      = aHit->GetMom().getX();
	dgtz["py"]      = aHit->GetMom().getY();
	dgtz["pz"]      = aHit->GetMom().getZ();
	dgtz["vx"]      = aHit->GetVert().getX();
	dgtz["vy"]      = aHit->GetVert().getY();
	dgtz["vz"]      = aHit->GetVert().getZ();
	dgtz["mvx"]     = aHit->GetmVert().getX();
	dgtz["mvy"]     = aHit->GetmVert().getY();
	dgtz["mvz"]     = aHit->GetmVert().getZ();		
	dgtz["avg_t"]   = tInfos.time;	
	dgtz["nsteps"] 	= aHit->GetPIDs().size();	
	dgtz["procID"]  = aHit->GetProcID();	
	
// 	cout<<"==============================================================================" <<endl;		  	
// 	cout<<"id "<<id << " procID " <<aHit->GetProcID() <<endl;		  
		  
	// Get the shower half_length along z
// 	double length_half = aHit->GetDetector().dimensions[0]; // Units: mm
// 	cout <<"length_half "<< aHit->GetDetector().dimensions[0] <<" "<< aHit->GetDetector().dimensions[1] <<" "<< aHit->GetDetector().dimensions[2] << endl;
	double length_half = 220; // Units: mm
	
	// Get info about detector material to eveluate Birks effect
// 	double birks_constant=aHit->GetDetector().GetLogical()->GetMaterial()->GetIonisation()->GetBirksConstant();
	//	cout << " Birks constant is: " << birks_constant << endl;
	//	cout << aHit->GetDetector().GetLogical()->GetMaterial()->GetName() << endl;	
	double birks_constant=0.126; // 0.126 mm/MeV for polystyrene-based scintillators https://en.wikipedia.org/wiki/Birks%27_law	
	
	vector<G4ThreeVector> Lpos = aHit->GetLPos();   // local position wrt centre of the detector piece in mm
	vector<double>      Edep = aHit->GetEdep();     // deposited energy in the hit, in MeV
	vector<int> charge = aHit->GetCharges();        // charge for each step
	vector<double> times = aHit->GetTime();
	vector<double> dx = aHit->GetDx();              // step length
	
	unsigned nsteps = times.size();                 // total number of steps in the hit
	
	
	// variables for each step:
	double dz1 = 0,dz2 = 0.;       // distance travelled by the light to end of module
	double EdepB = 0.;    // Energy deposit, scaled in accordance with Birk's effect	
	double Eend = 0.;      // attenuated energy as it arrives at end of module
	
	// variables for hit:
	double totEdepB = 0.;      // total Energy deposit,scaled in accordance with Birk's effect
	double totEend = 0.;      // total attenuated energy as it arrives at end of module	
	double Edep_seg[10]={0,0,0,0,0,0,0,0,0,0};	
	double EdepB_seg[10]={0,0,0,0,0,0,0,0,0,0};	
	double Eend_seg[10]={0,0,0,0,0,0,0,0,0,0};	
		
	if(tInfos.eTot>0){
	  for(unsigned int s=0; s<nsteps; s++)
	  {
	    // apply Birks effect:
	    EdepB = BirksAttenuation(Edep[s],dx[s],charge[s],birks_constant);
// 	    cout<< "step " << s << "\t"  << "dx "<<dx[s]<< "\t" <<"charge  "<<charge[s] << "\t" << "Edep " << Edep[s] << "\t" <<  "EdepB " << EdepB << "\t";

	    // Integrate energy over entire hit.
 	    totEdepB = totEdepB + EdepB;		  
	    
	    // Distances travelled one end of WLS fiber in preshower
	    dz1   = 100; //assume 100mm, can change to hit dependance later
	    // Distances travelled the other end of WLS fiber in preshower
	    dz2   = 100; //assume 100mm, can change to hit dependance later
// 	    cout<<"Lpos "<<Lpos[s].z()<< "\t" <<"dz1 "<<dz1 << "\t";
	    
	    // Calculate attenuated energy which reach module end
	    double attlength_D=3600; //Unit mm, WLS Y11(200)  http://kuraraypsf.jp/psf/ws.html
	    Eend  = 0.5 * EdepB * exp(-dz1/attlength_D) + 0.5 * EdepB * exp(-dz2/attlength_D);
	    
	    // Integrate energy over entire hit.
	    totEend = totEend + Eend;		  
// 	    cout << "Eend " << Eend << "\t" << "totEend " << totEend << endl;	
	    
// 	    int i_dz=int((length_half - Lpos[s].z())/(length_half/5.)); //shower depth in 10 blocks
// 	    if (0<=i_dz && i_dz<=9){
// 	      Edep_seg[i_dz]=Edep_seg[i_dz]+Edep[s];
// 	      EdepB_seg[i_dz]=EdepB_seg[i_dz]+EdepB;
// 	      Eend_seg[i_dz]=Eend_seg[i_dz]+Eend;
// 	    }
	    
	  }   // close loop over steps s		
	}  // closes tInfos.eTot>0
	
// 	cout << "totEdep " << tInfos.eTot << "\t"  << "totEdepB " << totEdepB << "\t" << "totEend " << totEend  << endl; 
// 	cout << "Edep_seg " << Edep_seg[0] << "\t" << Edep_seg[1] << "\t" << Edep_seg[2] << "\t" << Edep_seg[3] << "\t" << Edep_seg[4] << "\t" << Edep_seg[5] << "\t" << Edep_seg[6] << "\t" << Edep_seg[7] << "\t" << Edep_seg[7] << "\t" << Edep_seg[9] << endl;
// // // // 	cout << "EdepB_seg " << EdepB_seg[0] << "\t" << EdepB_seg[1] << "\t" << EdepB_seg[2] << "\t" << EdepB_seg[3] << "\t" << EdepB_seg[4] << "\t" << EdepB_seg[5] << "\t" << EdepB_seg[6] << "\t" << EdepB_seg[7] << "\t" << EdepB_seg[7] << "\t" << EdepB_seg[9] << endl;
// 	cout << "Eend_seg " << Eend_seg[0] << "\t" << Eend_seg[1] << "\t" << Eend_seg[2] << "\t" << Eend_seg[3] << "\t" << Eend_seg[4] << "\t" << Eend_seg[5] << "\t" << Eend_seg[6] << "\t" << Eend_seg[7] << "\t" << Eend_seg[7] << "\t" << Eend_seg[9] << endl;

	dgtz["totEdepB"] = totEdepB;		
	dgtz["totEend"] = totEend;		
// 	dgtz["Edep_seg0"] = Edep_seg[0];dgtz["Edep_seg1"] = Edep_seg[1];dgtz["Edep_seg2"] = Edep_seg[2];dgtz["Edep_seg3"] = Edep_seg[3];dgtz["Edep_seg4"] = Edep_seg[4];dgtz["Edep_seg5"] = Edep_seg[6];dgtz["Edep_seg6"] = Edep_seg[7];dgtz["Edep_seg7"] = Edep_seg[7];dgtz["Edep_seg8"] = Edep_seg[8];dgtz["Edep_seg9"] = Edep_seg[9];
// 	dgtz["EdepB_seg0"] = EdepB_seg[0];dgtz["EdepB_seg1"] = EdepB_seg[1];dgtz["EdepB_seg2"] = EdepB_seg[2];dgtz["EdepB_seg3"] = EdepB_seg[3];dgtz["EdepB_seg4"] = EdepB_seg[4];dgtz["EdepB_seg5"] = EdepB_seg[6];dgtz["EdepB_seg6"] = EdepB_seg[7];dgtz["EdepB_seg7"] = EdepB_seg[7];dgtz["EdepB_seg8"] = EdepB_seg[8];dgtz["EdepB_seg9"] = EdepB_seg[9];
// 	dgtz["Eend_seg0"] = Eend_seg[0];dgtz["Eend_seg1"] = Eend_seg[1];dgtz["Eend_seg2"] = Eend_seg[2];dgtz["Eend_seg3"] = Eend_seg[3];dgtz["Eend_seg4"] = Eend_seg[4];dgtz["Eend_seg5"] = Eend_seg[6];dgtz["Eend_seg6"] = Eend_seg[7];dgtz["Eend_seg7"] = Eend_seg[7];dgtz["Eend_seg8"] = Eend_seg[8];dgtz["Eend_seg9"] = Eend_seg[9];
		
	return dgtz;
}

vector<identifier>  solid_ec_ps_HitProcess :: processID(vector<identifier> id, G4Step* aStep, detector Detector)
{
	id[id.size()-1].id_sharing = 1;
	return id;
}


map< string, vector <int> >  solid_ec_ps_HitProcess :: multiDgt(MHit* aHit, int hitn)
{
	map< string, vector <int> > MH;
	
	return MH;
}

double solid_ec_ps_HitProcess::BirksAttenuation(double destep, double stepl, int charge, double birks)
{
	//Example of Birk attenuation law in organic scintillators.
	//adapted from Geant3 PHYS337. See MIN 80 (1970) 239-244
	//
	// Taken from GEANT4 examples advanced/amsEcal and extended/electromagnetic/TestEm3
	//
	double response = destep;
	if (birks*destep*stepl*charge != 0.)
	{
		response = destep/(1. + birks*destep/stepl);
	}
	return response;
}


double solid_ec_ps_HitProcess::BirksAttenuation2(double destep,double stepl,int charge,double birks)
{
	//Extension of Birk attenuation law proposed by Chou
	// see G.V. O'Rielly et al. Nucl. Instr and Meth A368(1996)745
	// 
	//
	double C=9.59*1E-4*mm*mm/MeV/MeV;
	double response = destep;
	if (birks*destep*stepl*charge != 0.)
	{
		response = destep/(1. + birks*destep/stepl + C*pow(destep/stepl,2.));
	}
	return response;
}
