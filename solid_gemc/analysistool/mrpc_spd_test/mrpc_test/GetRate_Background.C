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

void GetHit(string input_filename)
{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	const double DEG=180./3.1415926;

	TString input_png = input_filename;
	input_png.ReplaceAll(".root","_zhit_gas.png");

	/*Set Histogram{{{*/
	char the_filename[200];
	sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());

	TString outfile_name = input_png;
	outfile_name.ReplaceAll(".png",".root");
	
	TFile *outputfile=new TFile(outfile_name.Data(), "recreate");

	TH2F *h3 = new TH2F("h3","Hit Counts in MRPC", 52, 0, 51, 52, 0, 1e5); //
	h3->SetXTitle("X (cm)");
	h3->SetYTitle("Y (cm)");
	h3->GetXaxis()->CenterTitle(1);
	h3->GetYaxis()->CenterTitle(1);
	/*End Set Histo}}}*/

	/*Set Branch{{{*/
	TFile *file=new TFile(input_filename.c_str());
	if (file->IsZombie()) {
		cout << "Error opening file" << input_filename << endl;
		exit(-1);
	}
	else cout << "open file " << input_filename << endl;

	TTree *Tgen = (TTree*) file->Get("genT");
	Int_t gen_evn,gen_ngen;
	Int_t gen_id_array[1000];
	Int_t *gen_id=gen_id_array;
	Float_t gen_px_array[1000],gen_py_array[1000],gen_pz_array[1000],gen_p_array[1000],
			gen_phi_array[1000],gen_theta_array[1000],gen_vx_array[1000],gen_vy_array[1000],gen_vz_array[1000];
	Float_t *gen_px=gen_px_array,*gen_py=gen_py_array,*gen_pz=gen_pz_array,*gen_p=gen_p_array,
			*gen_phi=gen_phi_array,*gen_theta=gen_theta_array,*gen_vx=gen_vx_array,
			*gen_vy=gen_vy_array,*gen_vz=gen_vz_array;
	Tgen->SetBranchAddress("evn",&gen_evn);
	Tgen->SetBranchAddress("ngen",&gen_ngen);
	Tgen->SetBranchAddress("id",gen_id);
	Tgen->SetBranchAddress("px",gen_px);
	Tgen->SetBranchAddress("py",gen_py);
	Tgen->SetBranchAddress("pz",gen_pz);
	Tgen->SetBranchAddress("p",gen_p);
	Tgen->SetBranchAddress("phi",gen_phi);
	Tgen->SetBranchAddress("theta",gen_theta);
	Tgen->SetBranchAddress("vx",gen_vx);
	Tgen->SetBranchAddress("vy",gen_vy);
	Tgen->SetBranchAddress("vz",gen_vz);

	TTree *Tflux = (TTree*) file->Get("fluxT");
	Int_t flux_evn,flux_nfluxhit;
	Int_t flux_ID_array[1000],flux_pid_array[1000],flux_mpid_array[1000];
	Int_t *flux_ID=flux_ID_array,*flux_pid=flux_pid_array,*flux_mpid=flux_mpid_array;
	Float_t flux_Edep_array[1000],flux_E_array[1000],flux_x_array[1000],flux_y_array[1000],flux_z_array[1000],
			flux_lx_array[1000],flux_ly_array[1000],flux_lz_array[1000],flux_t_array[1000],flux_px_array[1000],
			flux_py_array[1000],flux_pz_array[1000],flux_vx_array[1000],flux_vy_array[1000],flux_vz_array[1000],
			flux_mvx_array[1000],flux_mvy_array[1000],flux_mvz_array[1000];
	Float_t *flux_Edep=flux_Edep_array,*flux_E=flux_E_array,*flux_x=flux_x_array,*flux_y=flux_y_array,
			*flux_z=flux_z_array,*flux_lx=flux_lx_array,*flux_ly=flux_ly_array,*flux_lz=flux_lz_array,
			*flux_t=flux_t_array,*flux_px=flux_px_array,*flux_py=flux_py_array,*flux_pz=flux_pz_array,
			*flux_vx=flux_vx_array,*flux_vy=flux_vy_array,*flux_vz=flux_vz_array,*flux_mvx=flux_mvx_array,
			*flux_mvy=flux_mvy_array,*flux_mvz=flux_mvz_array;
	Tflux->SetBranchAddress("evn",&flux_evn);
	Tflux->SetBranchAddress("nfluxhit",&flux_nfluxhit);
	Tflux->SetBranchAddress("ID",flux_ID);
	Tflux->SetBranchAddress("Edep",flux_Edep);
	Tflux->SetBranchAddress("E",flux_E);
	Tflux->SetBranchAddress("x",flux_x);
	Tflux->SetBranchAddress("y",flux_y);
	Tflux->SetBranchAddress("z",flux_z);
	Tflux->SetBranchAddress("lx",flux_lx);
	Tflux->SetBranchAddress("ly",flux_ly);
	Tflux->SetBranchAddress("lz",flux_lz);
	Tflux->SetBranchAddress("t",flux_t);
	Tflux->SetBranchAddress("pid",flux_pid);
	Tflux->SetBranchAddress("mpid",flux_mpid);
	Tflux->SetBranchAddress("px",flux_px);
	Tflux->SetBranchAddress("py",flux_py);
	Tflux->SetBranchAddress("pz",flux_pz);
	Tflux->SetBranchAddress("vx",flux_vx);
	Tflux->SetBranchAddress("vy",flux_vy);
	Tflux->SetBranchAddress("vz",flux_vz);
	Tflux->SetBranchAddress("mvx",flux_mvx);
	Tflux->SetBranchAddress("mvy",flux_mvy);
	Tflux->SetBranchAddress("mvz",flux_mvz);

	// Int_t nevent = (Int_t)Tgen->GetEntries();
	Int_t nevent = (Int_t)Tflux->GetEntries();
	cout << nevent << endl;
	/*End Set Branch}}}*/

	/*Define MRPC & Others{{{*/
    //In each segmentation, 40 slides, each slides has 2.5cm width, 0.3cm between two slides.
	const double R_Min = 96.0;
	const double R_Max = 205.0;//Originally 210 but consider the size and the gap of each slide
    const int MRPC_Threshold = 4; //The Threshold to deterime how many hits means the slide has been fired
	const int MRPC_Module = 50; //50 module around the circle
	const int MRPC_Slide = 40;// 40 slides in each module, 
	const double MRPC_Width = 2.5; //cm
	const double MRPC_Gap = 0.3; //cm
	double MRPC_R[MRPC_Slide];//Center location of each slide
	int MRPC_Fire[MRPC_Slide];// I sum all 50 modules together, and devide the counts in each slides by 50
	int MRPC_Hit[MRPC_Slide];//each slide has 10 layers, count how many hits in these 10 layers for each event 
	for(int i=0;i<MRPC_Slide;i++){//I just want to initialize everything
		MRPC_R[i] = MRPC_Width/2.0 + i*(MRPC_Width+MRPC_Gap); //Notethat the edge of the first slide is at R=96
        MRPC_Fire[i] =0;
		MRPC_Hit[i] =0;
	}

	//In each player
	const double MRPC_Z = 410; //cm, MRPC Center
	const double MRPC_Gas_Thick =0.025; //cm
	const int MRPC_Gas_Layer =10; //cm
	const double MRPC_Glass_Thick =0.07; //cm const double Hit_Min = -0.5;
	const double Gas[MRPC_Gas_Layer] = {-(2.175+0.95*4)/10., -(2.175+0.95*3)/10., -(2.175+0.95*2)/10., -(2.175+0.95)/10., -2.175/10.,
		2.175/10., (2.175+0.95)/10., (2.175+0.95*2)/10., (2.175+0.95*3)/10., (2.175+0.95*4)/10.};//cm

	//Other Definition	
	const int Electron = 11;
	const int Gamma = 22;
	const int Beam = 0;
	double r = -1000.0, z = -1000.0;//cm
	int Slide_ID = 0;
    /*}}}*/

	/*Read in each event{{{*/
	//Int_t nselected = 1e5;
	Int_t nselected = nevent;
	for(Int_t i=0;i<nselected;i++){
		cout<<i<<"\r";
		Tflux->GetEntry(i);

		for(int k=0;k<MRPC_Slide;k++){
			MRPC_Hit[k] = 0;
		}

		for (Int_t j=0;j<flux_nfluxhit;j++) {
			if(*(flux_ID+j)>=4000000&&*(flux_ID+j)<4120000) { //ID of 10 gas layers: 4100000 - 41000009
				if(*(flux_pid+j)==Electron){//MRPC doesn't sense photon
					r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2))/10.;//cm
					if(r > R_Max||r<R_Min) continue;//The radius of a mrpc sector is 210cm;

					z =*(flux_z+j)/10. - MRPC_Z; //cm

					Slide_ID = (int)((r-96)/(MRPC_Width+MRPC_Gap));

					if(abs(r-(R_Min+MRPC_R[Slide_ID]))>MRPC_Width/2.0) continue; //Double Check whether it is still in the Gap
					cerr<<Form("=== R = %f, Slide_ID = %d, E= %e", r, Slide_ID, *(flux_E+j)/1e3)<<endl;

					for(int k=0;k<MRPC_Gas_Layer;k++){//Check 10layers
						if(abs(z-Gas[k])<=MRPC_Gas_Thick/2.0){ //Charge particle in the gas only
							MRPC_Hit[Slide_ID]++;
						}//Gas Only
					}//Check 10layers
				}// Electron & r>96,r<210, no in the gap
			}//Gass Layers
		}//Flux particles in one event
		for(int k=0;k<MRPC_Slide;k++){
			if(MRPC_Hit[k]>MRPC_Threshold){//If the hits are above the threshold, then I treat this slide has been fired
				MRPC_Fire[k]++; 
				cerr<<"--- Slide#"<<k<<" has been fired! Count = "<<MRPC_Fire[k]<<endl;
			}
		}

	}
	/*End Read in each event}}}*/

	ofstream outfile(Form("MRPC_T%d_Background.out",MRPC_Threshold));
	int Count_All = 0;
	for(int k=0;k<MRPC_Slide;k++){
		//MRPC_Fire[k] = 15.*1e-6/(1.6*1e-19) * (MRPC_Fire[k]/nselected); 
		MRPC_Fire[k] = (MRPC_Fire[k]);
		cerr<<"--- Slide#"<<k<<" has total count = "<<MRPC_Fire[k]<<endl;
		outfile<<"--- Slide#"<<k<<" has total count = "<<MRPC_Fire[k]<<endl;

	    Count_All +=MRPC_Fire[k];
		h3->Fill(MRPC_R[k], MRPC_Fire[k]);
	}
    cerr<<" ====== For Threshold ="<<MRPC_Threshold<<", Total Count for 1e8 beam = "<<Count_All<<endl;
    outfile<<" ====== For Threshold ="<<MRPC_Threshold<<", Total Count for 1e8 beam = "<<Count_All<<endl;

	/*Plot{{{*/
	TCanvas *c1 = new TCanvas("c1","c1", 800,600);
	gStyle->SetOptStat(0);
	gPad->SetLogy(0);
    h3->Draw();
	/*}}}*/

	outputfile->Write();
	outputfile->Flush();
	//	outputfile->Close();
}
