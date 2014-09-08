#define GEMC2CaloSim_cxx
// The class definition in GEMC2CaloSim.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("GEMC2CaloSim.C")
// Root > T->Process("GEMC2CaloSim.C","some options")
// Root > T->Process("GEMC2CaloSim.C+")
//

#include "GEMC2CaloSim.h"
#include <TH2.h>
#include <TStyle.h>
#include <assert.h>

#include <iostream>
#include <TStyle.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>
#include <fstream>

#include <TMath.h>
#include <TVector.h>
#include <TRotation.h>

using namespace std;

GEMC2CaloSim::GEMC2CaloSim(TString outfilename) :
	foutfilename(outfilename)
{

}

void GEMC2CaloSim::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();

	foutfile.open(foutfilename.Data(), ios_base::out);
	assert(foutfile.is_open());

	sumXP = sumYP = sumN =0;

}

void GEMC2CaloSim::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();

}

Bool_t GEMC2CaloSim::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// It can be passed to either GEMC2CaloSim::GetEntry() or TBranch::GetEntry()
	// to read either all or the required parts of the data. When processing
	// keyed objects with PROOF, the object is already loaded and is available
	// via the fObject pointer.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.
	if (entry % 1000 == 0)
		cout << entry << endl;

	GetEntry(entry);

	//cut - large angle calo
	if (!(nfluxhit==1 && ID[0]==1)) return kTRUE;

	TVector3 hitpos(x[0], y[0], z[0]);
	TVector3 hitp(px[0], py[0], pz[0]);

	// remove simple phi symmetric
	TRotation rot;
	rot.RotateZ(-TMath::ATan2(y[0],x[0]));

	TVector3 hitpos_nophi = rot * hitpos;
	TVector3 hitp_nophi = rot * hitp;

//	cout << "----------------"<<endl;
//	hitpos . Print();
//	rot.Print();
//	hitpos_nophi . Print();
//	cout << "----------------"<<endl;


	TRotation rot_Calo;
	// For Calo plane in the azimuthal direction
	rot_Calo.RotateZ(0);
	// For Calo plane in the radical direction
	//	rot_Calo.RotateZ(TMath::Pi()/2);


//	TVector3 hitpos_Calo = rot_Calo* hitpos_nophi;
	TVector3 hitp_Calo = rot_Calo* hitp_nophi;
	assert(TMath::Abs(hitpos_nophi.Y())<1e-10);

//	// WARNING: aribitary scaling
//	hitp_Calo = hitp_Calo* (1./3.);
//	E[0] /= 3;

	// output
	assert(foutfile.is_open());
	foutfile << 0 << "\t" << 0 << "\t" << -21 << "\t" // x, y, z
			<<hitp_Calo.X()/1000 << "\t"<<hitp_Calo.Y()/1000 << "\t"<<hitp_Calo.Z()/1000 << "\t"//\vec{p} in GeV
	        << E[0]/1000  << "\t"<< endl; // Energy in GeV

	assert(TMath::Abs(hitp_Calo.Mag() -E[0] )<1e-1);

	//for summary
	sumN ++ ;
	sumXP += hitp_Calo.X()/hitp_Calo.Z();
	sumYP += hitp_Calo.Y()/hitp_Calo.Z();

	return kTRUE;
}

void GEMC2CaloSim::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.

}

void GEMC2CaloSim::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

	foutfile.close();
	cout << "Saved to "<<foutfilename<<endl;

	cout <<"Average Momentum on Calo: <dX/dZ> = "<<sumXP/sumN<<"<dY/dZ> = " <<sumYP/sumN<<endl;
}
