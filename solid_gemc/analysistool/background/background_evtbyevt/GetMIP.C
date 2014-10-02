#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TLine.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TH3F.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>

using namespace std;

void GetMIP(TString input_filename)
{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	const double DEG=180./3.1415926;
	
	/*Set Histogram{{{*/
	TString outfile_name = input_filename;
	outfile_name.ReplaceAll(".root","_mip.root");
	
	TFile *outputfile=new TFile(outfile_name.Data(), "recreate");

const double R_Min = 90.0;//cm
	const double R_Max = 220.0;//cm
	const double Z_Min = -0.68;//cm
	const double Z_Max = 0.68;//cm
//	const double SPD_Z = 407.5; //cm, SPD Before 
//	const double SPD_Z = 412.5; //cm, SPD After 
//	const double SPD_Thick =0.1; //cm
//	const double SPD_Thick =0.5; //cm
	//const double EDep_Min = 1e-5;//MeV
	const double EDep_Min = -0.005;//MeV
	const double EDep_Max = 50.0; //MeV

	TH1F *h1 = new TH1F("h1","Energy Deposit in SPD", 1000, EDep_Min, EDep_Max); 
	h1->SetXTitle("EDep (MeV)");
	h1->GetXaxis()->SetTitleOffset(1.1);
	h1->GetXaxis()->SetTitleFont(32);
	h1->GetXaxis()->SetTitleSize(0.05);
	h1->GetXaxis()->CenterTitle(1);
	/*End Set Histo}}}*/

	TFile *file=new TFile(input_filename.Data());
	if (file->IsZombie()) {
		cout << "Error opening file" << input_filename << endl;
		//continue;
		exit(-1);
	}
	else cout << "open file " << input_filename << endl;

	/*Set Branch{{{*/
	//Header Tree:
	// Var#1~#8 are free slots for propogating important info from the "INPUT generator seed"
	// For example, they can be used to store the cross section and other physics quantities
	// In eicRate, we store the following quantities:
	// var1->Wprate, var2->Wmrate, var3->targetPol, var4->x,var5->y, var6->W, var7->Q2, var8->rate 
	//
	TTree *header = (TTree*) file->Get("header");
	vector <double> *head_evn=0,*head_evn_type=0; //Note: Vectors have to be initialized at first!!!
	vector <double> *head_beamPol=0;
	vector<double> *head_Wmrate=0, *head_Wprate=0, *head_targetPol=0, *head_x=0, *head_Q2=0, *head_W=0, *head_rate=0, *head_y=0;
	header->SetBranchAddress("evn",&head_evn);
	header->SetBranchAddress("evn_type",&head_evn_type);
	header->SetBranchAddress("beamPol",&head_beamPol);
	header->SetBranchAddress("var1",    &head_Wprate);
	header->SetBranchAddress("var2",    &head_Wmrate);
	header->SetBranchAddress("var3",    &head_targetPol);
	header->SetBranchAddress("var4",    &head_x);
	header->SetBranchAddress("var5",    &head_y);
	header->SetBranchAddress("var6",    &head_W);
	header->SetBranchAddress("var7",    &head_Q2);
	header->SetBranchAddress("var8",    &head_rate);

	TTree *generated = (TTree*) file->Get("generated");
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	generated->SetBranchAddress("pid",&gen_pid);
	generated->SetBranchAddress("px",&gen_px);
	generated->SetBranchAddress("py",&gen_py);
	generated->SetBranchAddress("pz",&gen_pz);
	generated->SetBranchAddress("vx",&gen_vx);
	generated->SetBranchAddress("vy",&gen_vy);
	generated->SetBranchAddress("vz",&gen_vz);

	TTree *flux = (TTree*) file->Get("flux");
	vector<double> *flux_id=0,*flux_hitn=0,*flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0;
	vector<double> *flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0;
	vector<double> *flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	flux->SetBranchAddress("hitn",&flux_hitn);
	flux->SetBranchAddress("id",&flux_id);
	flux->SetBranchAddress("pid",&flux_pid);
	flux->SetBranchAddress("mpid",&flux_mpid);
	flux->SetBranchAddress("tid",&flux_tid);
	flux->SetBranchAddress("mtid",&flux_mtid);
	flux->SetBranchAddress("otid",&flux_otid);
	flux->SetBranchAddress("trackE",&flux_trackE);
	flux->SetBranchAddress("totEdep",&flux_totEdep);
	flux->SetBranchAddress("avg_x",&flux_avg_x);
	flux->SetBranchAddress("avg_y",&flux_avg_y);
	flux->SetBranchAddress("avg_z",&flux_avg_z);
	flux->SetBranchAddress("avg_lx",&flux_avg_lx);
	flux->SetBranchAddress("avg_ly",&flux_avg_ly);
	flux->SetBranchAddress("avg_lz",&flux_avg_lz);
	flux->SetBranchAddress("px",&flux_px);
	flux->SetBranchAddress("py",&flux_py);
	flux->SetBranchAddress("pz",&flux_pz);
	flux->SetBranchAddress("vx",&flux_vx);
	flux->SetBranchAddress("vy",&flux_vy);
	flux->SetBranchAddress("vz",&flux_vz);
	flux->SetBranchAddress("mvx",&flux_mvx);
	flux->SetBranchAddress("mvy",&flux_mvy);
	flux->SetBranchAddress("mvz",&flux_mvz);
	flux->SetBranchAddress("avg_t",&flux_avg_t);
	/*End Set Branch}}}*/
	int nevent = (int)generated->GetEntries();
	cout << "nevent = " << nevent << endl;


	/*Read in each event{{{*/
	const double SPD_Z = 407.5; //cm, SPD Before 
	//	const double SPD_Z = 412.5; //cm, SPD After 
	const double SPD_Thick =0.1; //cm
	//	const double SPD_Thick =0.5; //cm
	const int Electron = 11;
	const int Gamma = 22;
	const int Beam = 0;
	double fmom = -1000.1, r = -1000.1, z = -1000.0;//cm
	double EDep_Total = 0.0;
	for(Int_t i=0;i<nevent;i++){
		cout<<i<<"\r";
		flux->GetEntry(i);

		EDep_Total = 0.0;
		for (Int_t j=0;j<flux_hitn->size();j++) {
	        int ID_flux = (int) (flux_id->at(j));
			if (ID_flux==5100000){  //SPD
				fmom=sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2)+pow(flux_pz->at(j),2))/1e3;//cm
				r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/10.;//cm
				z =flux_avg_z->at(j)/10. - SPD_Z; //cm

				if(r > 210.0||r<96.0) continue;//The radius of a mrpc sector is 210cm;

				EDep_Total += flux_totEdep->at(j); //MeV

			} //Gas & Electron & r>96,r<210
			}//Flux particles in one event
            h1->Fill(EDep_Total);
		}
		/*End Read in each event}}}*/

		TCanvas *c1 = new TCanvas("c1","c1", 800,600);
        gPad->SetLogx(1);
        gPad->SetLogy(1);
		h1->Draw();

		outputfile->Write();
		outputfile->Flush();

//		file->Close();
}
