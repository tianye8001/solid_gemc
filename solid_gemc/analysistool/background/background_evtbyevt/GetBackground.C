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

void GetBackground(TString input_filename)
{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	const double DEG=180./3.1415926;

	TString input_png = input_filename;
	input_png.ReplaceAll(".root","_zhit.png");

	/*Set Histogram{{{*/
	TString outfile_name = input_png;
	outfile_name.ReplaceAll(".png",".root");

	TFile *outputfile=new TFile(outfile_name.Data(), "recreate");

	/*End Set Histo}}}*/

	/*Set Branch{{{*/
	TFile *file=new TFile(input_filename.Data());
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

	/*Define SPD & Others{{{*/
	//In each segmentation, 40 slides, each slides has 2.5cm width, 0.3cm between two slides.
	const double R_Min = 98.0;
	const double R_Max = 230.0;//Originally 210 but consider the size and the gap of each slide
	const int SPD_Module = 60; //60 module around the circle
	const int SPD_Slide = 4;// 4 slides in each module, 
	const double SPD_Width = 8.0; //cm
	
	double SPD_R[SPD_Slide];//Center location of each slide
	int SPD_In[SPD_Slide];// Number of particles going into the device
	int SPD_Fire[SPD_Module][SPD_Slide];// I sum all 50 modules together, and devide the counts in each slides by 50
	double SPD_EDep[SPD_Module][SPD_Slide];
	int SPD_Hit[SPD_Module][SPD_Slide];

	for(int i=0;i<SPD_Slide;i++){//I just want to initialize everything
		SPD_R[i] = SPD_Width/2.0 + i*SPD_Width; //Notethat the edge of the first slide is at R=96
		SPD_In[i] =0;
		for(int j=0;j<SPD_Module;j++){
			SPD_Fire[j][i] =0;
			SPD_EDep[j][i] =0;
			SPD_Hit[j][i] =0;
		}
	}
	const double SPD_Z = 412.5; //cm, SPD Center
	double SPD_Threshold = 0.12; //MeV for 1mm SPD
	double SPD_Thick =0.1; //cm
	if(input_filename.Contains("5mm")){
		SPD_Threshold = 0.60; //MeV for 5mm SPD
		SPD_Thick =0.5; //cm
	}
    cerr<<" --- Using Cut = "<< SPD_Threshold<<endl;
	//Other Definition	
	const int Electron = 11;
	const int Gamma = 22;
	const int Beam = 0;
	const int Neutron = 2112;
	const int Neutrino1 = 12;//Nu_e
	const int Neutrino2 = 14;//Nu_Mu
	const int Neutrino3 = 16;//Nu_Tao
	double r = -1000.0, z = -1000.0;//cm
	int Slide_ID = 0;
	int Module_ID = 0;
	/*}}}*/
	int VP_After =0; //Virtual plane after SPD
	if(input_filename.Contains("SPDbefore"))
		VP_After = 4110000;
	else if(input_filename.Contains("SPDafter"))
		VP_After = 3110000;
	else{
		cerr<<"*** ERROR ***"<<endl;
	   return;
	}

	/*Read in each event{{{*/
	//Int_t nselected = 1e5;
	Int_t nselected = nevent;
	for(Int_t i=0;i<nselected;i++){
		cout<<i<<"\r";
		Tflux->GetEntry(i);

		for(int k=0;k<SPD_Slide;k++){
			for(int l=0;l<SPD_Module;l++){
				SPD_EDep[l][k] = 0.0; //Different events have different numbers of hits, so need to reset
				SPD_Hit[l][k] = 0; //Different events have different numbers of hits, so need to reset
			}
		}

		for (Int_t j=0;j<flux_nfluxhit;j++) {
			r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2))/10.;//cm
			if(r > R_Max||r<R_Min) continue;//The radius of a mrpc sector is 210cm;
			Slide_ID = (int)((r-R_Min)/SPD_Width);
			if(fabs(r-(R_Min+SPD_R[Slide_ID]))>SPD_Width/2.0) continue; //Double Check

			if(*(flux_ID+j)==5110000 && *(flux_pz+j)>1e-19)//Forward events 
				SPD_In[Slide_ID]++;
			if(*(flux_ID+j)==VP_After && *(flux_pz+j)<-1e-19)//Backward events from EC or MRPC
				SPD_In[Slide_ID]++;

			if(*(flux_ID+j)==5100000) { //ID for SPD 
				if(*(flux_pid+j)>10000||*(flux_pid+j)==Gamma||*(flux_pid+j)==Neutron||*(flux_pid+j)==Neutrino1) continue; //SPD doesn't sense neutral 
				double hit_y = *(flux_y+j), hit_x = *(flux_x+j);	
				double hit_phi = fabs(atan(hit_y/hit_x)*DEG);
				Module_ID = (int) hit_phi/(360./SPD_Module);
				if(Module_ID>=SPD_Module)
					cerr<<"**** ERROR, wrong Phi calculation!!!"<<endl;

				cerr<<Form("=== MPD = %3d, PID = %3d, Slide_ID = %3d, Module_ID =%3d E= %8.3f, E_Dep = %5.4f",
					   	*(flux_mpid+j), *(flux_pid+j), Slide_ID,Module_ID, *(flux_E+j), *(flux_Edep+j))<<endl;
				SPD_EDep[Module_ID][Slide_ID]+= (*(flux_Edep+j));//MeV
				SPD_Hit[Module_ID][Slide_ID]++;
			}//  r>96,r<210, no in the gap

		}//Flux particles in one event
		for(int k=0;k<SPD_Slide;k++){
			for(int l=0;l<SPD_Module;l++){
				//if(SPD_EDep[l][k]>=SPD_Threshold){//If the EDep is above the threshold, then I treat this slide has been fired
				if(SPD_Hit[l][k]>=1){//If the EDep is above the threshold, then I treat this slide has been fired
					cerr<<Form(" +++ E_Dep for [%3d][%3d] = %f, for T =%4.2f, Hit=%3d",l,k,SPD_EDep[l][k], SPD_Threshold,SPD_Hit[l][k])<<endl;
					SPD_Fire[l][k]++; 
					cerr<<"--- Slide#"<<k<<" has been fired! Count = "<<SPD_Fire[l][k]<<endl;
				}
			}
		}

	}
	/*End Read in each event}}}*/

	double Count_To_Rate = 0.0;
	if(input_filename.Contains("pi0")){
		Count_To_Rate = 241.0/1e6; //Count to MHz
		if(input_filename.Contains("up")||input_filename.Contains("down")){
			Count_To_Rate = 136.0/1e6;//Count to MHz
		}
	}
	else
		Count_To_Rate = 1.5/1.6; //Count to MHz for 15uA electron events;

	cerr<<" --- Using Converting Factor = "<<Count_To_Rate<<endl;

	TString input_out = input_filename;
	input_out.ReplaceAll("8.root","8");
	ofstream outfile(Form("SPDi_%s_1mm.out",input_out.Data()));
	int Count_All = 0, In_All = 0;
	for(int k=0;k<SPD_Slide;k++){
		for(int l=0;l<SPD_Module;l++){
			//SPD_Fire[k] = 15.*1e-6/(1.6*1e-19) * (SPD_Fire[k]/nselected); 
			SPD_Fire[l][k] = (SPD_Fire[l][k]);
			cerr<<Form("--- Slide#%d--%d has total count = ",l,k,SPD_Fire[l][k])<<endl;
			outfile<<l<<" "<<k<<"  "<<SPD_In[k]<<"  "<<SPD_Fire[l][k]<<endl;

			Count_All +=SPD_Fire[l][k];
		}
		In_All +=SPD_In[k];
	}
	cerr<<" ====== For Total incoming particle = "<< In_All*Count_To_Rate/SPD_Module<<endl;
	cerr<<" ====== For Threshold ="<<SPD_Threshold<<", Total Count for 1e8 beam = "<<Count_All*Count_To_Rate/SPD_Module<<endl;
	outfile<<" ====== For Total incoming particle = "<< In_All*Count_To_Rate/SPD_Module<<endl;
	outfile<<" ====== For Threshold ="<<SPD_Threshold<<", Total Count for 1e8 beam = "<<Count_All*Count_To_Rate/SPD_Module<<endl;

	outputfile->Write();
	outputfile->Flush();
	//	outputfile->Close();
}
