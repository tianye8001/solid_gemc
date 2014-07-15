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
#include <TString.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>

using namespace std;

void GetRate(TString input_filename)
{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	const double DEG=180./3.1415926;

	ifstream infile(input_filename.Data());
	TString output_filename = input_filename;
	output_filename.ReplaceAll(".list",".out");
	ofstream outfile(output_filename.Data());

	TString root_filename;
	double SPD_Thick = 0.0;
	double EDep_Cut = 0.0;
	while(infile>>root_filename){

		if(root_filename.Contains("5mm")){
			SPD_Thick = 5.0;//mm
			EDep_Cut = 0.6;	//MeV
		}
		else if(root_filename.Contains("1mm")){
			SPD_Thick = 1.0;//mm
			EDep_Cut = 0.12;//MeV	
		}

		/*Set Branch{{{*/
		TFile *file=new TFile(root_filename.Data());
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

		/*Read in each event{{{*/
		const double SPD_Z = 407.5; //cm, SPD Before 
		//	const double SPD_Z = 412.5; //cm, SPD After 
		//const double SPD_Thick =0.1; //cm
		//	const double SPD_Thick =0.5; //cm
		const int Electron = 11;
		const int Gamma = 22;
		const int Neutron = 2112;
		const int Neutrino1 = 12;//Nu_e
		const int Neutrino2 = 14;//Nu_Mu
		const int Neutrino3 = 16;//Nu_Tao
		const int Beam = 0;
		double fmom = -1000.1, r = -1000.1, z = -1000.0;//cm
		int Counter_All = 0;
		int G_2_E = 0;
		int G_All = 0;
		double E0, R, RErr;
		double EDep_Total = 0.0;
		for(Int_t i=0;i<nevent;i++){
			cout<<i<<"\r";
			Tgen->GetEntry(i);         
			E0 = (*(gen_p))/1e3;
			Tflux->GetEntry(i);
		
			Counter_All = 0;
			EDep_Total = 0.0;
			for (Int_t j=0;j<flux_nfluxhit;j++) {
				fmom=sqrt(pow(*(flux_px+j),2)+pow(*(flux_py+j),2)+pow(*(flux_pz+j),2))/1e3;//GeV
				r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2))/10.;//cm
				z =*(flux_z+j)/10. - SPD_Z; //cm

				if(r > 210.0||r<96.0) continue;//The radius of a mrpc sector is 210cm;
			
				//cerr<<Form("=== MPD = %3d, PID = %3d", *(flux_mpid+j), *(flux_pid+j))<<endl;

				if (*(flux_ID+j)==5110000&&(*(flux_pid+j)==Gamma&&*(flux_mpid+j)==Beam)){  //SPD
					G_All++;
				}
				if (*(flux_ID+j)==5100000){  //SPD
					//if(*(flux_pid+j)==Gamma||*(flux_pid+j)==Neutron||*(flux_pid+j)==Neutrino1) continue; //SPD doesn't sense neutral 
					if(*(flux_pid+j)==Electron||*(flux_pid+j)==-Electron){
						Counter_All++;
						EDep_Total += *(flux_Edep+j); //MeV
					}
				} //Gas & Electron & r>96,r<210
				}//Flux particles in one event

			if(Counter_All>=1)
			//if(EDep_Total >=EDep_Cut)//MIP Cut at 0.1MeV for 1mm, 0.8MeV for 5mm	
			//if(EDep_Total >1e-7)//MIP Cut at 0.1MeV for 1mm, 0.8MeV for 5mm	
					G_2_E ++;
			}
			/*End Read in each event}}}*/

		    G_All +=G_2_E;
			cerr<<"E = "<<E0<<" : Gamma = "<<G_All<<", Gamma_2_E = "<< G_2_E  <<" %= "<< G_2_E*1.0/(G_All*1.0)*100.0<<"%"<<endl;

			R =G_2_E*1.0/(G_All*1.0)*100.0; 
			RErr = R*sqrt(1./G_2_E + 1./G_All);
			Tgen->Delete();
			Tflux->Delete();
			file->Close();
			//		outfile <<E0<<"  " << root_filename.Data() << "  "<<R<<"  "<<RErr <<endl;
			outfile<<Form("%8.2e %8.4f  %8.4f %20s", E0, R, RErr, root_filename.Data())<<endl;
	}
	infile.close();
	outfile.close();
	}
