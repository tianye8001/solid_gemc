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
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>

using namespace std;

void GetMRPC(TString input_filename)
{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	const double DEG=180./3.1415926;

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
	
	/*EC Electron Trigger{{{*/
	const int Ntrigline=6,Ntriglinebin=21;
	int region_index;
	//	if (input_filename.Contains("SIDIS_FA")) region_index=0;
	//	else if (input_filename.Contains("SIDIS_LA")) region_index=1;
	//	else {cout << "need option for FA or LA region" << endl; exit(-1);}
	region_index = 0;

	int det[2]={8,12};  //detecor id
	double rmin[2]={105,80};
	double rmax[2]={235,140};

	TFile *file_trig_cut[2][Ntrigline][2];//[Det_ID][Cut_ID][PID], Det_DC: 0->FA, 1->LA, PID: 0->e, 1->pi
	// Radius(cm)  P Threshold (GeV)
	//   90 - 105      5.0    
	// 105 - 115      4.0    
	// 115 - 130      3.0    
	// 130 - 150      2.0    
	// 150 - 200      1.0 
	// 200 - 230      2.0 
	// 6 point cut, right on Q2=1 line and field bend line
	double trig_cut_range_R[Ntrigline+1]={0,105,115,130,150,200,300};

	TString Trigger_Dir_Rad="/w/work6501/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/background/SIDIS_He3/triggerfile/cutRadial_innerbackground/";
	file_trig_cut[0][0][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][0][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][1][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][1][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][2][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][2][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][3][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][3][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][4][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][4][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][5][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));
	file_trig_cut[0][5][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));

	///Large Angle Trigger   has no radial dependence
	TString Trigger_Dir_1GeVCut = "/w/work6501/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/background/SIDIS_He3/triggerfile/cut1GeV_innerbackground/";
	for (int i=0;i<Ntrigline;i++){
		file_trig_cut[1][i][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunElectron_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root",Trigger_Dir_1GeVCut.Data()));
		file_trig_cut[1][i][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunPion_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root",Trigger_Dir_1GeVCut.Data()));
	}


	char *gr_trig_cut_ele_name[2][Ntrigline],*gr_trig_cut_pi_name[2][Ntrigline];
	for(int j=0;j<2;j++){
		for(int i=0;i<Ntrigline;i++){
			gr_trig_cut_ele_name[j][i]="Graph";
			gr_trig_cut_pi_name[j][i]="Graph";    
		}  
	}

	double trig_cut[2][Ntrigline][Ntriglinebin+2][6];
	TGraphErrors *gr_trig_cut_ele[2][Ntrigline],*gr_trig_cut_pi[2][Ntrigline];
	for (int j=0;j<2;j++){
		for (int i=0;i<Ntrigline;i++){  
			gr_trig_cut_ele[j][i]=(TGraphErrors*) file_trig_cut[j][i][0]->Get(gr_trig_cut_ele_name[j][i]);
			gr_trig_cut_pi[j][i]=(TGraphErrors*) file_trig_cut[j][i][1]->Get(gr_trig_cut_pi_name[j][i]);
			double binwidth=gr_trig_cut_ele[j][i]->GetX()[1]-gr_trig_cut_ele[j][i]->GetX()[0];
			if (j==1) { //add one more point for LA to become 21 points like FA
				gr_trig_cut_ele[j][i]->SetPoint(20,gr_trig_cut_ele[j][i]->GetX()[19]+binwidth,gr_trig_cut_ele[j][i]->GetY()[19]);
				gr_trig_cut_pi[j][i]->SetPoint(20,gr_trig_cut_pi[j][i]->GetX()[19]+binwidth,gr_trig_cut_pi[j][i]->GetY()[19]);    
			}
			for (int k=0;k<Ntriglinebin;k++){ //set any point with eff <0.01 as 0
				if (gr_trig_cut_ele[j][i]->GetY()[k]<0.01) gr_trig_cut_ele[j][i]->SetPoint(k,gr_trig_cut_ele[j][i]->GetX()[k],0.);
				if (gr_trig_cut_pi[j][i]->GetY()[k]<0.01) gr_trig_cut_pi[j][i]->SetPoint(k,gr_trig_cut_pi[j][i]->GetX()[k],0.);
			}
			trig_cut[j][i][0][0]=trig_cut_range_R[i];
			trig_cut[j][i][0][1]=trig_cut_range_R[i+1];
			trig_cut[j][i][0][2]=0.;
			trig_cut[j][i][0][3]=gr_trig_cut_ele[j][i]->GetX()[0]-binwidth/2;
			trig_cut[j][i][0][4]=0.;
			trig_cut[j][i][0][5]=0.;
			//	cout << j << " " << i << " " << 0 << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[0] << "\t" << gr_trig_cut_ele[j][i]->GetY()[0] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[0] << "\t" << gr_trig_cut_pi[j][i]->GetY()[0] << endl;
			for (int k=0;k<Ntriglinebin;k++){
				trig_cut[j][i][k+1][0]=trig_cut_range_R[i];
				trig_cut[j][i][k+1][1]=trig_cut_range_R[i+1];
				trig_cut[j][i][k+1][2]=gr_trig_cut_ele[j][i]->GetX()[k]-binwidth/2;
				trig_cut[j][i][k+1][3]=gr_trig_cut_ele[j][i]->GetX()[k]+binwidth/2;
				trig_cut[j][i][k+1][4]=gr_trig_cut_ele[j][i]->GetY()[k];
				trig_cut[j][i][k+1][5]=gr_trig_cut_pi[j][i]->GetY()[k];
				//		cout << j << " " << i << " " << k+1 << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[k] << "\t" << gr_trig_cut_ele[j][i]->GetY()[k] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[k] << "\t" << gr_trig_cut_pi[j][i]->GetY()[k] << endl;
			}
			trig_cut[j][i][Ntriglinebin+1][0]=trig_cut_range_R[i];
			trig_cut[j][i][Ntriglinebin+1][1]=trig_cut_range_R[i+1];
			trig_cut[j][i][Ntriglinebin+1][2]=gr_trig_cut_ele[j][i]->GetX()[Ntriglinebin-1]+binwidth/2;
			trig_cut[j][i][Ntriglinebin+1][3]=11.;
			trig_cut[j][i][Ntriglinebin+1][4]=gr_trig_cut_ele[j][i]->GetY()[Ntriglinebin-1];
			trig_cut[j][i][Ntriglinebin+1][5]=gr_trig_cut_pi[j][i]->GetY()[Ntriglinebin-1];
			//	cout << j << " " << i << " " << Ntriglinebin+1 << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[Ntriglinebin-1] << "\t" << gr_trig_cut_ele[j][i]->GetY()[Ntriglinebin-1] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[Ntriglinebin-1] << "\t" << gr_trig_cut_pi[j][i]->GetY()[Ntriglinebin-1] << endl;
			gr_trig_cut_ele[j][i]->Delete();
			gr_trig_cut_pi[j][i]->Delete();
		}
	}
	/*}}}*/
	const int EC_Trigger_Slide = 6;// put 6 slides in each module just for check the R-dependence, 
	const int EC_Trigger_Mom_Bin = 23;
	
	/*Define MRPC{{{*/
	//In each segmentation, 40 slides, each slides has 2.5cm width, 0.3cm between two slides.
	const int MRPC_Module = 30; //30 module around the circle
	const int MRPC_Slide = 6;// put 6 slides in each module just for check the R-dependence, 
	double MRPC_R[MRPC_Slide];//Center location of each slide
	double MRPC_In_G[MRPC_Module][MRPC_Slide];// Number of photons going into the device
	double MRPC_In_E[MRPC_Module][MRPC_Slide];// Number of electrons going into the device
	double MRPC_Out_G[MRPC_Module][MRPC_Slide];// Number of photons going into the device
	double MRPC_Out_E[MRPC_Module][MRPC_Slide];// Number of electrons going into the device

	for(int i=0;i<MRPC_Slide;i++){//I just want to initialize everything
		MRPC_R[i] = trig_cut_range_R[i]; //{0,105,115,130,150,200,300};
		for(int j=0;j<MRPC_Module;j++){
			MRPC_In_G[j][i] =0.;
			MRPC_In_E[j][i] =0.;
			MRPC_Out_G[j][i] =0.;
			MRPC_Out_E[j][i] =0.;
		}
	}
	double EC_Threshold = 1.; //GeV for EC cut, the cut could be tight if using Jin's curves
	double MRPC_Threshold = 0.000001; //MeV for EC cut, the cut could be tight if using Jin's curves

	//After SPD 
    const int VP_Before = 4110000; //MRPC virtual plane
	const int VP_After  = 3110000; //EC virtual plane
	const double Z_MRPC = 408.0; //cm VP position, 410.0 is the real positon of MRPC
	const double R_Min = 96.0;//cm,
	const double R_Max = 210.0;//cm,
	const double Z_Out = 413.0; //cm EC VP position
	const double R_Min_Out = 105.0;//cm, HGC front
	const double R_Max_Out = 235.0;//cm,
	const double Z_EC = 427.5; //cm, EC front, VP position = 413cm
	const double R_Min_EC = 105.0;//cm
	const double R_Max_EC = 235.0;//cm
	
	
	//Other Definition	
	const int Electron = 11;
	const int Gamma = 22;
	const int Beam = 0;
	const int Neutron = 2112;
	const int Neutrino1 = 12;//Nu_e
	const int Neutrino2 = 14;//Nu_Mu
	const int Neutrino3 = 16;//Nu_Tao
	 
	double r = -1000.0, z = -1000.0, R_EC = -1000.0;//cm
	int Slide_ID = 0;
	int Module_ID = 0;

	/*}}}*/

	/*Read in each event{{{*/
	//Int_t nselected = 1e5;
	Int_t nselected = nevent;
	double In_G = 0, In_E = 0, Out_G = 0, Out_E = 0;
	double Count_High = 0, Count_Low = 0;
	int Count_Ep =0, Count_Em=0, Count_Both=0;
	double Count_Cut_Ep =0, Count_Cut_Em=0;
	double EC_Cut = 0.0;
	double fmom_old = 0.0;
	double x_EC = 0.0, y_EC = 0.0, vertex_theta, vertex_phi, VR;
    double rate = 0.0;
	int Double_Count = 0;
	int FirstOne0 = 0; //incoming electron with E<1GeV
	int FirstOne1 = 0; //incoming electron with E>1GeV
	int FirstOne2 = 0; //incoming electron with R-dependence E-cut
	int FirstOne5 = 0; //outgoing positron with R-dependence E-cut
	int FirstOne3 = 0; //incoming electron with R-dependence E-cut by slides
	int FirstOne4 = 0; //outgoing electron with R-dependence E-cut by slides
	int FirstOne6 = 0; //outgoing electron with R-dependence E-cut by slides
	cerr<<"++++++++++++++++ "<<endl;
	for(Int_t i=0;i<nselected;i++){
		cout<<i<<"\r";
		header->GetEntry(i);
        rate = head_rate->at(0);
		generated->GetEntry(i);
		const int ng = gen_pid->size();//Normally there is only one particle in the gen
		double gen_theta[ng], gen_phi[ng], gen_mom[ng];
		int Is_Electron = -1;
		for(unsigned int ig=0;ig<ng;ig++){
			gen_mom[ig]=0.0; gen_phi[ig]=0.0; gen_theta[ig]=0.0;
          if((int)gen_pid->at(ig)==Electron)
             Is_Electron = ig;
		  gen_mom[ig] = sqrt( pow(gen_px->at(ig),2)+pow(gen_py->at(ig),2)+pow(gen_pz->at(ig),2) ); 
		  gen_theta[ig] = acos(gen_pz->at(ig)/gen_mom[ig])*DEG;
		  gen_phi[ig] = atan2( gen_py->at(ig), gen_px->at(ig))*DEG;
		}

		//if(gen_theta[Is_Electron]>=7.0){
		if(1){
			flux->GetEntry(i);
			FirstOne0 = 0;
			FirstOne1 = 0;
			FirstOne2 = 0;
			FirstOne3 = 0;
			FirstOne5 = 0;
			FirstOne6 = 0;
			//Double_Count = 0;

			/*Into the Device{{{*/
			double EC_Cut_Max = 0.0;
			for (Int_t j=0;j<flux_hitn->size();j++) {
				r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/10.;//cm
				if(r > R_Max||r<R_Min) continue;//The radius of a mrpc sector is 210cm;

				if(flux_pz->at(j)<1e-9)continue;//Cout out backward particles

				double fmom=sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2)+pow(flux_pz->at(j),2))/1e3;//GeV
				if(fmom<1e-9) continue; //Cut out Zero-E particles
			
				double vertex_theta = atan(sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2))/(flux_pz->at(j)))*DEG;
				R_EC = abs((Z_EC - Z_Out) * tan(vertex_theta/DEG) + r);
				if(R_EC>R_Max_EC || R_EC<R_Min_EC) continue;

				int ID_Pick = VP_Before;
				int ID_flux = (int) (flux_id->at(j));
				int PID_flux = (int) (flux_pid->at(j));

				//Selct the right Cut	
				//cut[Det_ID][Cut_ID][Data_Point][Cut_Info]: Cut_Info: R_Min, R_Max, P_Min, P_Max, e_Eff, pi_Eff
				EC_Cut = 0;
				if((abs(PID_flux)==Electron||PID_flux==Gamma)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 

					/*Look at the EC to check E-Cut{{{*/ 
					int JustOnceHere=0;
					for (Int_t m=0;m<flux_hitn->size();m++) {
						int ID_flux_m = (int) (flux_id->at(m));
						int PID_flux_m = (int) (flux_pid->at(m));

						if(ID_flux_m==3110000){//On EC VP
							double r_EC=sqrt(pow(flux_avg_x->at(m),2)+pow(flux_avg_y->at(m),2))/10.;//cm
							if(r_EC>R_Max_EC||r_EC<R_Min_EC) continue;//The radius of a mrpc sector is 210cm;

							if(flux_pz->at(m)<1e-9)continue;//Cut out backward particles
							double fmom_EC=sqrt(pow(flux_px->at(m),2)+pow(flux_py->at(m),2)+pow(flux_pz->at(m),2))/1e3;//GeV
							if(fmom_EC<1e-9) continue; //Cut out Zero-E particles

							if(abs(fmom_EC-fmom)/fmom<0.20){//Alow 20% Eloss--FIX_HERE
								if(abs(PID_flux_m)==Electron)
									JustOnceHere++;
								/*Find E-Cut{{{*/
								for(int k=0;k<EC_Trigger_Slide;k++){
									for(int l=0;l<EC_Trigger_Mom_Bin;l++){
										if(r_EC>trig_cut[0][k][l][0]&&r_EC<=trig_cut[0][k][l][1]){
											if(fmom_EC>trig_cut[0][k][l][2]&&fmom_EC<=trig_cut[0][k][l][3]){
												EC_Cut =trig_cut[0][k][l][4]; 
												Slide_ID = k;
											}
										}
									}
								}
								/*}}}*/
							}
							//if(JustOnceHere>1&&EC_Cut>0.5)
							//	cerr<<"No! More than one !!!"<<endl;
						}
						if(EC_Cut>EC_Cut_Max)
							EC_Cut_Max = EC_Cut;
					}//for (Int_t m=0;m<flux_hitn->size();m++) 
					/*}}}*/

					if(EC_Cut_Max<-1e-9||EC_Cut_Max>1){
						EC_Cut_Max = 0.0;
						cerr<<"----In: I can't find the cut!"<<Form(" --- R= %f,  E =%f", r, fmom)<<endl;
						return;
					}
				}

				//Low Energy Electron <1GeV
				if((PID_flux==Electron||PID_flux==-Electron)&&ID_flux==ID_Pick && fmom<EC_Threshold){//#Electrons going out 
					if(FirstOne0<1)
						Count_Low+=1.0*rate;
					FirstOne0 ++;;
				}
				//High Energy Electron >1GeV
				if((PID_flux==Electron||PID_flux==-Electron)&&ID_flux==ID_Pick && fmom>=EC_Threshold){//#Electrons going out 
					if(FirstOne1<1)
						Count_High+=1.0*rate;
					FirstOne1 ++;;

					Count_Both++;
					if(PID_flux==Electron)
						Count_Em++;
					if(PID_flux==-Electron)
						Count_Ep++;
				}
				//High Energy Electron with EC R-Cut 
				if((PID_flux==Electron)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 
					//Count_Em++;
					if(FirstOne2<1)
						Count_Cut_Em+=EC_Cut_Max*rate;
					FirstOne2 ++;;
				}
				//High Energy Positron with EC R-Cut 
				if((PID_flux==-Electron)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 
					//Count_Ep++;
					if(FirstOne5<1)
						Count_Cut_Ep+=EC_Cut_Max*rate;
					FirstOne5 ++;;
				}

				//Count by slides
				double hit_y = flux_avg_y->at(j), hit_x = flux_avg_x->at(j);	
				double hit_phi = fabs(atan(hit_y/hit_x)*DEG);
				Module_ID = (int) hit_phi/(360./MRPC_Module);

				if(PID_flux==Gamma&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Photons going in
					if(FirstOne6<1)
						MRPC_In_G[Module_ID][Slide_ID]+=EC_Cut_Max*rate;
					FirstOne6++;
				}
				if((PID_flux==Electron||PID_flux==-Electron)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 
					if(FirstOne3<1){
						MRPC_In_E[Module_ID][Slide_ID]+=EC_Cut_Max*rate;
					}
					FirstOne3 ++;;
				}
			}
			/*}}}*/

			//		if((FirstOne2>=1) && (FirstOne5>=1))
			//			cerr<<" Oh! Double Counting !!!  "<< ++Double_Count<<endl;

			/*Out from the Device{{{*/
			FirstOne4 = 0;
			if(1){
				for (Int_t j=0;j<flux_hitn->size();j++) {
					r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/10.;//cm
					if(r<R_Min_Out && r>R_Max_Out) continue;

					double fmom=sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2)+pow(flux_pz->at(j),2))/1e3;//GeV
					if(flux_pz->at(j)<1e-9)continue;
					if(fmom<1e-9) continue;

					double vertex_theta = atan(sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2))/(flux_pz->at(j)))*DEG;
					R_EC = abs((Z_EC - Z_Out) * tan(vertex_theta/DEG) + r);
					if(R_EC>R_Max_EC || R_EC<R_Min_EC) continue;


					int ID_Pick = VP_After;
					int ID_flux = (int) (flux_id->at(j));
					int PID_flux = (int) (flux_pid->at(j));
					
					//Selct the right Cut	
					//cut[Det_ID][Cut_ID][Data_Point][Cut_Info]: Cut_Info: R_Min, R_Max, P_Min, P_Max, e_Eff, pi_Eff
					EC_Cut = 0;
					if((abs(PID_flux)==Electron||PID_flux==Gamma)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 

						/*Look at the EC to check E-Cut{{{*/ 
						int JustOnceHere=0;
						for (Int_t m=0;m<flux_hitn->size();m++) {
							int ID_flux_m = (int) (flux_id->at(m));
							int PID_flux_m = (int) (flux_pid->at(m));

							if(ID_flux_m==3110000){//On EC VP
								double r_EC=sqrt(pow(flux_avg_x->at(m),2)+pow(flux_avg_y->at(m),2))/10.;//cm
								if(r_EC>R_Max_EC||r_EC<R_Min_EC) continue;//The radius of a mrpc sector is 210cm;

								if(flux_pz->at(m)<1e-9)continue;//Cut out backward particles
								double fmom_EC=sqrt(pow(flux_px->at(m),2)+pow(flux_py->at(m),2)+pow(flux_pz->at(m),2))/1e3;//GeV
								if(fmom_EC<1e-9) continue; //Cut out Zero-E particles

								if(abs(fmom_EC-fmom)/fmom<0.20){//Alow 20% Eloss--FIX_HERE
									if(abs(PID_flux_m)==Electron)
										JustOnceHere++;
									/*Find E-Cut{{{*/
									for(int k=0;k<EC_Trigger_Slide;k++){
										for(int l=0;l<EC_Trigger_Mom_Bin;l++){
											if(r_EC>trig_cut[0][k][l][0]&&r_EC<=trig_cut[0][k][l][1]){
												if(fmom_EC>trig_cut[0][k][l][2]&&fmom_EC<=trig_cut[0][k][l][3]){
													EC_Cut =trig_cut[0][k][l][4]; 
													Slide_ID = k;
												}
											}
										}
									}
									/*}}}*/
								}
							//	if(JustOnceHere>1&&EC_Cut>0.5)
							//		cerr<<"No! More than one !!!"<<endl;
							}
							if(EC_Cut>EC_Cut_Max)
								EC_Cut_Max = EC_Cut;
						}//for (Int_t m=0;m<flux_hitn->size();m++) 
						/*}}}*/

						if(EC_Cut_Max<-1e-9||EC_Cut_Max>1){
							EC_Cut_Max = 0.0;
							cerr<<"----In: I can't find the cut!"<<Form(" --- R= %f,  E =%f", r, fmom)<<endl;
							return;
						}
					}

					double hit_y = flux_avg_y->at(j), hit_x = flux_avg_x->at(j);	
					double hit_phi = fabs(atan(hit_y/hit_x)*DEG);
					Module_ID = (int) hit_phi/(360./MRPC_Module);

					if(PID_flux==Gamma&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Photons going out 
						MRPC_Out_G[Module_ID][Slide_ID]+=EC_Cut_Max*rate;
					}
					if((PID_flux==Electron||PID_flux==-Electron)&&ID_flux==ID_Pick && fmom>=0.95*EC_Threshold){//#Electrons going out 
						if(FirstOne4<1)
							MRPC_Out_E[Module_ID][Slide_ID]+=EC_Cut_Max*rate;
						FirstOne4 ++;;
					}
				}//Flux particles in one event
			}//if(1)
			/*}}}*/
		}
	}
	/*End Read in each event}}}*/
	
	/*Count_Rate_Ractor{{{*/
	double Count_To_Rate = 0.0;
	if(input_filename.Contains("EM"))
		Count_To_Rate = (((1.5e-5)/(1.6e-19))/nevent)/1e3; //Count to KHz for 15uA electron events;
	else
        Count_To_Rate = 1.0/1e3;
	/*}}}*/

	/*Output Results{{{*/
	cerr<<" --- Using Converting Factor = "<<Count_To_Rate<<endl;

	TString input_out = input_filename;
	input_out.ReplaceAll(".root",".out");
	ofstream outfile(Form("MRPC_%s",input_out.Data()));
	for(int k=0;k<MRPC_Slide;k++){
		for(int l=0;l<MRPC_Module;l++){
			 In_G +=MRPC_In_G[l][k];
			 In_E +=MRPC_In_E[l][k];
			 Out_E +=MRPC_Out_E[l][k];
			 Out_G +=MRPC_Out_G[l][k];
		}
	}
	cerr<<" ====== In_E = "<< In_E*Count_To_Rate<<endl;
	cerr<<" ====== In_G = "<< In_G*Count_To_Rate<<endl;
	cerr<<" ====== Out_E = "<< Out_E*Count_To_Rate<<endl;
	cerr<<" ====== Out_G = "<< Out_G*Count_To_Rate<<endl;

	cerr<< Form("&&&& N (P<1GeV) = %d, N (P>1.0GeV) = %d, 1GeV Cut N = (-)%d / (+)%d /(+-)%d",
		   	(int)(Count_Low), (int)(Count_High), (int)(Count_Em), (int)(Count_Ep), (int)(Count_Both))<<endl;
	cerr<< Form("                                        R-Cut Cut N = (-)%d / (+)%d /(+-)%d", (int)(Count_Cut_Em),
		   	(int)(Count_Cut_Ep), (int)(In_E))<<endl;

	outfile<<" ====== In_E = "<< In_E*Count_To_Rate<<endl;
	outfile<<" ====== In_G = "<< In_G*Count_To_Rate<<endl;
	outfile<<" ====== Out_E = "<< Out_E*Count_To_Rate<<endl;
	outfile<<" ====== Out_G = "<< Out_G*Count_To_Rate<<endl;
    /*}}}*/
}
