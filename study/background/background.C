///////////////////////////////////////////
//Log:
//--- Z. Ye (10/01), change the readin format to read GEMC.v2 files, 
//
//
///////////////////////////////////////////

#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include "./response/FastResponse.C"
#include "./niel/niel_fun.cc"

using namespace std;

//read hits from a root file produced by GEMC2 and EVIO2ROOT
void background(string input_filename){
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(111111);
	gSystem->Load("./response/FastResponse_C.so");
	const double DEG=180./3.1415926;

	TFile *file=new TFile(input_filename.c_str());
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
	vector <double> *header_evn=0,*header_evn_type=0; //Note: Vectors have to be initialized at first!!!
	vector <double> *header_beamPol=0;
	vector<double> *header_Wmrate=0, *header_Wprate=0, *header_targetPol=0, *header_x=0, *header_Q2=0, *header_W=0, *header_rate=0, *header_y=0;
	header->SetBranchAddress("evn",&header_evn);
	header->SetBranchAddress("evn_type",&header_evn_type);
	header->SetBranchAddress("beamPol",&header_beamPol);
	header->SetBranchAddress("var1",    &header_Wprate);
	header->SetBranchAddress("var2",    &header_Wmrate);
	header->SetBranchAddress("var3",    &header_targetPol);
	header->SetBranchAddress("var4",    &header_x);
	header->SetBranchAddress("var5",    &header_y);
	header->SetBranchAddress("var6",    &header_W);
	header->SetBranchAddress("var7",    &header_Q2);
	header->SetBranchAddress("var8",    &header_rate);

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
	int Nevent = (int)header->GetEntries();
	cout << "Nevent = " << Nevent << endl;

	char output_filename[80];
	sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
	TFile *outputfile=new TFile(output_filename, "recreate");

	const int n=43; // number of detector
	const int m=11; //number of particles

	TString label[m]={"photon+electron+positron","photon","electron+positron","neutron","proton","pip","pim","Kp","Km","Kl","other"};

	/*Define Histograms{{{*/
	TH1F *hvertexZ[n][m];
	TH2F *hhitXY[n][m],*hvertex[n][m];
	TH1F *hfluxR[n][m];
	TH1F *hfluxPhi[n][m],*hfluxPhi_target[n][m],*hfluxPhi_other[n][m];
	TH1F *hEfluxR[n][m];
	TH1F *hEdepR_Preshower[n][m],*hEdepR_Shower[n][m];
	TH1F *hEdepR_Preshower_high[n][m],*hEdepR_Shower_high[n][m];
	TH1F *hEdepR_Preshower_low[n][m],*hEdepR_Shower_low[n][m];
	TH1F *hEfluxPhi[n][m],*hEfluxPhi_target[n][m],*hEfluxPhi_other[n][m];
	TH2F *hflux_x_y[n][m],*hflux_x_y_high[n][m],*hflux_x_y_low[n][m],*hEflux_x_y[n][m];
	TH1F *hPlog[n][m],*hElog[n][m],*hEklog[n][m];
	TH1F *hfluxEklog_cut[n][m],*hfluxEklog_cut_niel[n][m];
	TH2F *hP_Theta[n][m],*hP_Theta_high[n][m],*hP_Theta_low[n][m];
	TH2F *hP_R[n][m],*hP_R_high[n][m],*hP_R_low[n][m];
	TH2F *hPlog_R[n][m],*hPlog_R_high[n][m],*hPlog_R_low[n][m];
	TH2F *hElog_R[n][m];
	TH2F *hEklog_R[n][m],*hEklog_R_high[n][m],*hEklog_R_low[n][m];
	TH3F *hEklog_R_Phi[n][m];

	for(int k=0;k<n;k++){
		for(int l=0;l<m;l++){
			char hstname[100];
			sprintf(hstname,"hitXY_%i_%i",k,l);
			hhitXY[k][l]=new TH2F(hstname,hstname,600,-300,300,600,-300,300);
			sprintf(hstname,"vertex_%i_%i",k,l);
			hvertex[k][l]=new TH2F(hstname,hstname,5000,-500,500,800,0,400);
			sprintf(hstname,"vertexZ_%i_%i",k,l);   
			hvertexZ[k][l]=new TH1F(hstname,hstname,5000,-500,500);   
			hvertexZ[k][l]->SetTitle(";vertex Z (cm);");

			sprintf(hstname,"fluxR_%i_%i",k,l);
			hfluxR[k][l]=new TH1F(hstname,hstname,60,0,300);
			hfluxR[k][l]->SetTitle(";R (cm);flux (kHz/mm2)");
			sprintf(hstname,"EfluxR_%i_%i",k,l);
			hEfluxR[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEfluxR[k][l]->SetTitle(";R (cm);Eflux (1e3*GeV/100cm2/s)");

			sprintf(hstname,"EdepR_Preshower_%i_%i",k,l);
			hEdepR_Preshower[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Preshower[k][l]->SetTitle("Preshower;R (cm);Edep in scint (1e3*GeV/100cm2/s)");
			sprintf(hstname,"EdepR_Shower_%i_%i",k,l);
			hEdepR_Shower[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Shower[k][l]->SetTitle("Shower;R (cm);Edep in scint (1e3*GeV/100cm2/s)");
			sprintf(hstname,"EdepR_Preshower_high_%i_%i",k,l);
			hEdepR_Preshower_high[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Preshower_high[k][l]->SetTitle("Preshower_high;R (cm);Edep in scint (1e3*GeV/100cm2/s)");
			sprintf(hstname,"EdepR_Shower_high_%i_%i",k,l);
			hEdepR_Shower_high[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Shower_high[k][l]->SetTitle("Shower_high;R (cm);Edep in scint (1e3*GeV/100cm2/s)");
			sprintf(hstname,"EdepR_Preshower_low_%i_%i",k,l);
			hEdepR_Preshower_low[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Preshower_low[k][l]->SetTitle("Preshower_low;R (cm);Edep in scint (1e3*GeV/100cm2/s)");
			sprintf(hstname,"EdepR_Shower_low_%i_%i",k,l);
			hEdepR_Shower_low[k][l]=new TH1F(hstname,hstname,30,0,300);
			hEdepR_Shower_low[k][l]->SetTitle("Shower_low;R (cm);Edep in scint (1e3*GeV/100cm2/s)");

			sprintf(hstname,"fluxPhi_%i_%i",k,l);   
			hfluxPhi[k][l]=new TH1F(hstname,hstname,96,0,24);
			hfluxPhi[k][l]->SetTitle(";#phi (deg);flux (kHz/deg)");   
			sprintf(hstname,"fluxPhi_target_%i_%i",k,l);   
			hfluxPhi_target[k][l]=new TH1F(hstname,hstname,96,0,24);
			hfluxPhi_target[k][l]->SetTitle(";#phi (deg);flux (kHz/deg)");   
			sprintf(hstname,"fluxPhi_other_%i_%i",k,l);   
			hfluxPhi_other[k][l]=new TH1F(hstname,hstname,96,0,24);
			hfluxPhi_other[k][l]->SetTitle(";#phi (deg);flux (kHz/deg)");    
			sprintf(hstname,"EfluxPhi_%i_%i",k,l);   
			hEfluxPhi[k][l]=new TH1F(hstname,hstname,96,0,24);
			hEfluxPhi[k][l]->SetTitle(";#phi (deg);Eflux (GeV/deg/s)");   
			sprintf(hstname,"EfluxPhi_target_%i_%i",k,l);   
			hEfluxPhi_target[k][l]=new TH1F(hstname,hstname,96,0,24);
			hEfluxPhi_target[k][l]->SetTitle(";#phi (deg);Eflux (GeV/deg/s)");   
			sprintf(hstname,"EfluxPhi_other_%i_%i",k,l);   
			hEfluxPhi_other[k][l]=new TH1F(hstname,hstname,96,0,24);
			hEfluxPhi_other[k][l]->SetTitle(";#phi (deg);Eflux (GeV/deg/s)");

			sprintf(hstname,"flux_x_y_%i_%i",k,l);
			hflux_x_y[k][l] = new TH2F(hstname, hstname, 600, -300, 300,600, -300, 300);
			hflux_x_y[k][l]->SetTitle("flux (kHz/mm2);x (cm));y (cm)");
			sprintf(hstname,"flux_x_y_high_%i_%i",k,l);
			hflux_x_y_high[k][l] = new TH2F(hstname, hstname, 600, -300, 300,600, -300, 300);
			hflux_x_y_high[k][l]->SetTitle("flux (kHz/mm2);x (cm));y (cm)");
			sprintf(hstname,"flux_x_y_low_%i_%i",k,l);
			hflux_x_y_low[k][l] = new TH2F(hstname, hstname, 600, -300, 300,600, -300, 300);
			hflux_x_y_low[k][l]->SetTitle("flux (kHz/mm2);x (cm));y (cm)");   
			sprintf(hstname,"Eflux_x_y_%i_%i",k,l);
			hEflux_x_y[k][l] = new TH2F(hstname, hstname, 600, -300, 300,600, -300, 300);
			hEflux_x_y[k][l]->SetTitle("Eflux (GeV/10cm2/s);x (cm));y (cm)");

			sprintf(hstname,"Plog_%i_%i",k,l);
			hPlog[k][l]=new TH1F(hstname,hstname,50,-6,1.3);
			hPlog[k][l]->SetTitle(";log(P) GeV;counts");        
			sprintf(hstname,"Elog_%i_%i",k,l);
			hElog[k][l]=new TH1F(hstname,hstname,50,-6,1.3);
			hElog[k][l]->SetTitle(";log(E) GeV;counts");    
			sprintf(hstname,"Eklog_%i_%i",k,l);
			hEklog[k][l]=new TH1F(hstname,hstname,50,-6,1.3);
			hEklog[k][l]->SetTitle(";log(Ek) GeV;counts");    

			sprintf(hstname,"P_Theta_%i_%i",k,l);
			hP_Theta[k][l]=new TH2F(hstname,hstname,100, 0, 50, 1100,0,11);    
			hP_Theta[k][l]->SetTitle("rate(kHz)/0.5deg/10MeV;Theta (deg);P (GeV)");    
			sprintf(hstname,"P_Theta_high_%i_%i",k,l);
			hP_Theta_high[k][l]=new TH2F(hstname,hstname,100, 0, 50, 1100,0,11);    
			hP_Theta_high[k][l]->SetTitle("rate(kHz)/0.5deg/10MeV;Theta (deg);P (GeV)");        
			sprintf(hstname,"P_Theta_low_%i_%i",k,l);
			hP_Theta_low[k][l]=new TH2F(hstname,hstname,100, 0, 50, 1100,0,11);    
			hP_Theta_low[k][l]->SetTitle("rate(kHz)/0.5deg/10MeV;Theta (deg);P (GeV)"); 

			sprintf(hstname,"P_R_%i_%i",k,l);
			hP_R[k][l]=new TH2F(hstname,hstname,300, 0, 300, 1100,0,11);    
			hP_R[k][l]->SetTitle(";R (cm);P (GeV)");    
			sprintf(hstname,"P_R_high_%i_%i",k,l);
			hP_R_high[k][l]=new TH2F(hstname,hstname,300, 0, 300, 1100,0,11);    
			hP_R_high[k][l]->SetTitle(";R (cm);P (GeV)");        
			sprintf(hstname,"P_R_low_%i_%i",k,l);
			hP_R_low[k][l]=new TH2F(hstname,hstname,300, 0, 300, 1100,0,11);    
			hP_R_low[k][l]->SetTitle(";R (cm);P (GeV)");        

			sprintf(hstname,"Plog_R_%i_%i",k,l);
			hPlog_R[k][l]=new TH2F(hstname,hstname,300, 0, 300, 200,-6,1.3);    
			hPlog_R[k][l]->SetTitle(";R (cm);log(P) (GeV)");      
			sprintf(hstname,"Plog_high_R_%i_%i",k,l);
			hPlog_R_high[k][l]=new TH2F(hstname,hstname,300, 0, 300, 200,-6,1.3);    
			hPlog_R_high[k][l]->SetTitle(";R (cm);log(P) (GeV)");          
			sprintf(hstname,"Plog_R_low_%i_%i",k,l);
			hPlog_R_low[k][l]=new TH2F(hstname,hstname,300, 0, 300, 200,-6,1.3);    
			hPlog_R_low[k][l]->SetTitle(";R (cm);log(P) (GeV)");          

			sprintf(hstname,"Elog_R_%i_%i",k,l);
			hElog_R[k][l]=new TH2F(hstname,hstname,300, 0, 300, 200,-6,1.3);    
			hElog_R[k][l]->SetTitle(";R (cm);log(E) (GeV)");    

			sprintf(hstname,"Eklog_R_%i_%i",k,l);
			hEklog_R[k][l] = new TH2F(hstname, hstname, 300, 0, 300, 200,-6,1.3);    
			hEklog_R[k][l]->SetTitle(";R (cm);log(Ek) (GeV)");
			sprintf(hstname,"Eklog_R_high_%i_%i",k,l);
			hEklog_R_high[k][l] = new TH2F(hstname, hstname, 300, 0, 300, 200,-6,1.3);    
			hEklog_R_high[k][l]->SetTitle(";R (cm);log(Ek) (GeV)");
			sprintf(hstname,"Eklog_R_low_%i_%i",k,l);
			hEklog_R_low[k][l] = new TH2F(hstname, hstname, 300, 0, 300, 200,-6,1.3);    
			hEklog_R_low[k][l]->SetTitle(";R (cm);log(Ek) (GeV)");

			sprintf(hstname,"Eklog_R_Phi_%i_%i",k,l);
			hEklog_R_Phi[k][l] = new TH3F(hstname, hstname, 48,0,12,300, 0, 300, 200,-6,1.3);    
			hEklog_R_Phi[k][l]->SetTitle(";Phi (deg);R (cm);log(Ek) (GeV)");

			sprintf(hstname,"fluxEklog_cut_%i_%i",k,l);
			hfluxEklog_cut[k][l]=new TH1F(hstname,hstname,100,-6,2);
			hfluxEklog_cut[k][l]->SetTitle("without 1MeV neutron fluence equivalent NIEL;log(Ek) MeV;flux (kHz)");    
			sprintf(hstname,"fluxEklog_cut_niel_%i_%i",k,l);
			hfluxEklog_cut_niel[k][l]=new TH1F(hstname,hstname,100,-6,2);
			hfluxEklog_cut_niel[k][l]->SetTitle("with 1MeV neutron fluence equivalent NIEL;log(Ek) MeV;flux (kHz)*niel");

		} 
	}
	TH1F *hpid=new TH1F("pid","pid",21,-10.5,10.5);

	TH1F *hactualphotonpid=new TH1F("actualphotonpid","actualphotonpid",21,-10.5,10.5);
	TH1F *hactualothermass=new TH1F("actualothermass","actualothermass",1000,0.,10.);
	/*End Define Histogram}}}*/

	/*Define run condition{{{*/
	bool Is_PVDIS=false,Is_SIDIS_He3=false,Is_SIDIS_NH3=false,Is_JPsi_LH2=false;  
	double current;
	double target_center;  //in mm
	if (input_filename.find("PVDIS",0) != string::npos){
		Is_PVDIS=true;
		current=50e-6/1.6e-19;  //50uA
		target_center=100;  //in mm
		cout << " PVDIS " << current << " " << Nevent << endl;  
	}
	else if (input_filename.find("SIDIS_He3",0) != string::npos){
		Is_SIDIS_He3=true;
		current=15e-6/1.6e-19;   //15uA
		target_center=-3500;  //in mm  
		cout << " SIDIS_He3 " << current << " " << Nevent <<  endl;  
	}
	else if (input_filename.find("SIDIS_NH3",0) != string::npos){
		Is_SIDIS_NH3=true;	  
		current=100e-9/1.6e-19;   //100nA
		target_center=-3500;  //in mm  
		cout << " SIDIS_NH3 " << current << " " << Nevent <<  endl;  
	}
	else if (input_filename.find("JPsi_LH2",0) != string::npos){
		Is_JPsi_LH2=true;
		current=3e-6/1.6e-19;   //3uA
		target_center=-3150;  //in mm  
		cout << " JPsi_LH2 " << current << " " << Nevent <<  endl;  
	}
	else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}

	// there are different ways to get correct normalization for different files
	//EM just need current and total number of event
	//source from weighted or normalized event generator need rate and total file number, assume there are 100 files, each file has 10000 events, the rate in each file has normalized by 10000, then add 100 files with root tree together, the final result needs normalization by 10000*100=1e6, so the addtional factor is the file num 100
	double filenum=1.;
	bool Is_EM=false,Is_clean_weighted=false,Is_dirty_normalized=false;
	if (input_filename.find("_EM_",0) != string::npos) {
		Is_EM=true;
		cout << "EM background from beam on target" <<  endl;
	}
	else if (input_filename.find("_clean_weighted_",0) != string::npos) {
		Is_clean_weighted=true;
		cout << "background from weighted event generator with no interaction except decay" <<  endl;
	    if (input_filename.find("_file",0) != string::npos) {
		filenum=atof(input_filename.substr(input_filename.find("_filenum")+8,input_filename.find("_")).c_str());
		cout << "filenum " << filenum << " for addtional normalization, YOU Need to Make Sure It's CORRECT!" <<  endl;
	    }
	    else {cout << "we need filenum for addtional normalization" << endl; return;}		
	}	  
	else if (input_filename.find("_dirty_normalized_",0) != string::npos) {
		Is_dirty_normalized=true;
		cout << "background from normalized event generator with all interaction" <<  endl;
	    if (input_filename.find("_file",0) != string::npos) {
		filenum=atof(input_filename.substr(input_filename.find("_filenum")+8,input_filename.find("_")).c_str());
		cout << "filenum " << filenum << " for addtional normalization, YOU Need to Make Sure It's CORRECT!" <<  endl;
	    }
	    else {cout << "we need filenum for addtional normalization" << endl; return;}
	}	  	
	else {cout << "not EM or clean_weighted or dirty_normalized " << endl; return;}

// 	bool Is_eDIS=false;
// 	if (input_filename.find("_eDIS_",0) != string::npos) {
// 		Is_eDIS=true;
// 		cout << "eDIS has W<2 cut" <<  endl;
// 	}
	/*End of Define run condition}}}*/

	/*Loop events{{{*/    
	//int evncounter=0;
	int yescounter=0,Ek_nocounter=0,rate_nocounter=0;
	int ratecounter=0;
	int backscat_counter=0;
	int counter_actualphoton=0,counter_acutalother=0;

	//int count_SC_front=0,count_SC=0,count_SC_back=0;
	int count_SC_act=0,count_SC_inact=0;

	for(int i=0;i<Nevent;i++) {
		cout << i << "\r";

		header->GetEntry(i);
		double rate = header_rate->at(0);
		double W = header_W->at(0);
		double Q2 = header_Q2->at(0);
		double x = header_x->at(0);

		flux->GetEntry(i);
		/*Loop fluxes{{{*/
		for(unsigned int j=0;j<flux_hitn->size();j++) {
			int particle_ID = (int) flux_pid->at(j);
			/*Check PID{{{*/
			switch (particle_ID){
				case 22:     hpid->Fill(0); break;
				case 11:     hpid->Fill(1); break;
				case -11:     hpid->Fill(-1); break;
				case 12:     hpid->Fill(2); break;
				case 14:     hpid->Fill(2); break;      
				case 16:     hpid->Fill(2); break;
				case -12:     hpid->Fill(-2); break;
				case -14:     hpid->Fill(-2); break;      
				case -16:     hpid->Fill(-2); break;
				case 13:     hpid->Fill(3); break;
				case -13:     hpid->Fill(3); break; 
				case 211:     hpid->Fill(4); break;
				case -211:     hpid->Fill(-4); break; 
				case 111:     hpid->Fill(5); break;       
				case -111:     hpid->Fill(-5); break;      
				case 321:     hpid->Fill(6); break;
				case -321:     hpid->Fill(-6); break;
				case 130:     hpid->Fill(7); break; 
				case -130:     hpid->Fill(-7); break;       
				case 2212:     hpid->Fill(8); break;
				case -2212:     hpid->Fill(-8); break;       
				case 2112:     hpid->Fill(9); break; 
				case -2112:     hpid->Fill(-9); break;       
				default:      hpid->Fill(10); break;      
			}
			int par;
			if(particle_ID==22) par=1;  //photon    
			else if (abs(particle_ID)==11) par=2; //electron or positron
			else if(particle_ID==2112) par=3;  //neutron
			else if(particle_ID==2212) par=4;  //proton    
			else if(particle_ID==211)  par=5;  //pip
			else if(particle_ID==-211) par=6;  //pim
			else if(particle_ID==321)  par=7;  //Kp    
			else if(particle_ID==-321)  par=8;  //Km
			else if(particle_ID==130)  par=9;  //Kl    
			else par=10;  //all other
			/*End of Check PID}}}*/

			int detector_ID= (int) flux_id->at(j);
			detector_ID/=100000;
			/*Check Detector ID{{{*/
			if ( detector_ID !=11 && detector_ID !=12 &&  detector_ID !=13 && detector_ID !=14 && detector_ID !=15 
					&& detector_ID !=16 && detector_ID !=31 && detector_ID !=32 
					&& detector_ID!=21 && detector_ID!=22 && detector_ID!=41 && detector_ID!=42 && detector_ID!=51 && detector_ID!=52){
				cout << "wrong detector_ID "  << i  << " " << j << " " << flux_id->at(j) << endl;
				cout << " " <<  flux_id->at(j) << " " <<  particle_ID << " " <<  flux_mpid->at(j) 
					<< " " <<   flux_totEdep->at(j) << " " <<  flux_trackE->at(j) << " " 
					<< flux_avg_x->at(j) << " " <<  flux_avg_y->at(j) << " " <<  flux_avg_z->at(j) 
					<< " " <<  flux_vx->at(j) << " " <<  flux_vy->at(j) << " " <<  flux_vz->at(j)  
					<< " " <<  flux_px->at(j) << " " <<  flux_py->at(j) << " " <<  flux_pz->at(j) << endl;
				continue;
			}

			int subdetector_ID= (int) flux_id->at(j);
			subdetector_ID/=10000; 
			//=========    hit_id and pid defination ==============
			// hitid  =0 - 5 6 GEM planes, unused
			//         29 - 40  6 GEM plane,1st layer (odd) and 2nd layer (even) of gas		
			//         20 - 25  6 GEM plane front			
			//         6,18    LGCC  PMT, front
			//         7,19    HGCC  PMT,  front
			//         8 - 11  FAEC front,middle,inner,rear 
			//         12 -15  LAEC front,middle,inner,rear 
			//         16,17,26 MRPC front,gas,glass
			//         27-28 FASPD front, inner
			//         41-42 LASPD front inner
			//   pid =0   photon+electron+positron
			//        1   photon    
			//        2   electron + positron
			//        3   neutron
			//        4   proton
			//        5   pip
			//        6   pim
			//        7   Kp
			//        8   Km
			//        9   Kl
			//       10   other    
			//=======================================================    

			int hit_id=-1;
			switch (detector_ID){
				case 11:    if (subdetector_ID==110) hit_id=0;
					    else if (subdetector_ID==111) hit_id=20;
					    else if (subdetector_ID==112) hit_id=29;
					    else if (subdetector_ID==113) hit_id=30;
					    else cout << "wrong flux_ID 11 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 12:    if (subdetector_ID==120) hit_id=1;
					    else if (subdetector_ID==121) hit_id=21;
					    else if (subdetector_ID==122) hit_id=31;//#6 layer
					    else if (subdetector_ID==123) hit_id=32;//#10 layers
					    else cout << "wrong flux_ID 12 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 13:    if (subdetector_ID==130) hit_id=2;
					    else if (subdetector_ID==131) hit_id=22;
					    else if (subdetector_ID==132) hit_id=33;
					    else if (subdetector_ID==133) hit_id=34;
					    else cout << "wrong flux_ID 13 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 14:    if (subdetector_ID==140) hit_id=3;
					    else if (subdetector_ID==141) hit_id=23;
					    else if (subdetector_ID==142) hit_id=35;
					    else if (subdetector_ID==143) hit_id=36;
					    else cout << "wrong flux_ID 14 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 15:    if (subdetector_ID==150) hit_id=4;
					    else if (subdetector_ID==151) hit_id=24;
					    else if (subdetector_ID==152) hit_id=37;
					    else if (subdetector_ID==153) hit_id=38;
					    else cout << "wrong flux_ID 15 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 16:    if (subdetector_ID==160) hit_id=5;
					    else if (subdetector_ID==161) hit_id=25;
					    else if (subdetector_ID==162) hit_id=39;
					    else if (subdetector_ID==163) hit_id=40;
					    else cout << "wrong flux_ID 16 " << (int)flux_id->at(j)<< endl;		      
					    break;
				case 21:    if (subdetector_ID==210) hit_id=6;
					    else if (subdetector_ID==211) hit_id=18;
					    else cout << "wrong flux_ID 21 " << (int)flux_id->at(j)<< endl;		      
					    break; 
				case 22:    if (subdetector_ID==220) hit_id=7;
					    else if (subdetector_ID==221) hit_id=19;
					    else cout << "wrong flux_ID 22 " << (int)flux_id->at(j)<< endl;		      
					    break;
				case 31:    if (subdetector_ID==311) hit_id=8;
					    else if (subdetector_ID==312) hit_id=9;
					    else if (subdetector_ID==313) hit_id=10;
					    else if (subdetector_ID==314) hit_id=11;  
					    else cout << "wrong flux_ID 31 " << (int)flux_id->at(j)<< endl;		      
					    break;
				case 32:     if (subdetector_ID==321) hit_id=12;
					    else if (subdetector_ID==322) hit_id=13;
					    else if (subdetector_ID==323) hit_id=14;
					    else if (subdetector_ID==324) hit_id=15;		     
					    else cout << "wrong flux_ID 32 " << (int)flux_id->at(j)<< endl;		      
					    break;
				case 41:     if (subdetector_ID==411) hit_id=16;
					    else if (subdetector_ID==410) hit_id=17;
					    else if (subdetector_ID==412) hit_id=26;
					    else cout << "wrong flux_ID 41 " << (int)flux_id->at(j)<< endl;		      
					    break;
				case 51:     if (subdetector_ID==511) hit_id=27;
					    else if (subdetector_ID==510) hit_id=28;
					    else cout << "wrong flux_ID 51 " << (int)flux_id->at(j)<< endl;		      
					    break;		     
				case 52:     if (subdetector_ID==521) hit_id=41;
					    else if (subdetector_ID==520) hit_id=42;
					    else cout << "wrong flux_ID 52 " << (int)flux_id->at(j)<< endl;
					    break;		     
				default:     cout << "wrong flux_ID 00 " << (int)flux_id->at(j)
							 <<" ID="<<detector_ID<<  endl;
			}    
			/*End of Check Detector ID}}}*/

			/*Check and Debug{{{*/
			double phi=fabs(atan(flux_avg_y->at(j)/flux_avg_x->at(j))/3.1416*180);
			if (flux_avg_x->at(j) > 0 && flux_avg_y->at(j) > 0) phi=phi;
			else if (flux_avg_x->at(j) < 0 && flux_avg_y->at(j) > 0) phi=180-phi;
			else if (flux_avg_x->at(j) < 0 && flux_avg_y->at(j) < 0) phi=180+phi;    
			else if (flux_avg_x->at(j) > 0 && flux_avg_y->at(j) < 0) phi=360-phi;
			else cout << " flux wrong? " << flux_avg_x->at(j) << " " <<  flux_avg_y->at(j) << endl; 

			double r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2));  //in mm
			double Theta=atan(r/(flux_avg_z->at(j)-target_center))*DEG;
			double P=sqrt(pow(flux_px->at(j),2)+pow(flux_py->at(j),2)+pow(flux_pz->at(j),2));
			double Ek;
			if (fabs(flux_trackE->at(j) - P)<1) 
				Ek=flux_trackE->at(j);
			else 
				Ek=flux_trackE->at(j)-sqrt(pow(flux_trackE->at(j),2)-pow(P,2));

			if ( TMath::IsNaN(Ek) || isinf(Ek) ) {
				//     if ( TMath::IsNaN(Ek)) {  
				cout << Ek << " " << flux_trackE->at(j) << " " << P << " " <<  flux_px->at(j) << " " <<  flux_py->at(j) << " " <<  flux_pz->at(j) << endl;
				cout << " " <<  i<< " " <<  j << " " <<  (int)flux_id->at(j) << " " <<  particle_ID << " " <<  flux_mpid << " " <<   flux_totEdep->at(j) 
					<< " " <<  flux_trackE->at(j) << " " <<  flux_avg_x->at(j) << " " <<  flux_avg_y->at(j) << " " <<  flux_avg_z->at(j) 
					<< " " <<  flux_vx->at(j) << " " <<  flux_vy->at(j) << " " <<  flux_vz->at(j)  << " " 
					<<  flux_px->at(j) << " " <<  flux_py->at(j) << " " <<  flux_pz->at(j) << endl;     
				Ek_nocounter++; continue;
			} 

			yescounter++;
			/*End of Check and Debugs}}}*/

			///cut away the back scattering from lead
			// 			if (input_filename.find("PVDIS",0) != string::npos) {  //PVDIS case
			// // 					  if (r/10.<110 || 265<r/10.) {backscat_counter++; continue;}
			// 				if (hit_id==8 && flux_vz->at(j)/10. > 318.2) {backscat_counter++; continue;}
			// 			}
			// 			if (input_filename.find("PVDIS",0) == string::npos) {  //non-PVDIS case
			// 				// 	  if ((hit_id==8 && flux_vz->at(j)/10. > 403.2) || (hit_id==12 && flux_vz->at(j)/10. > -66.8)) {backscat_counter++; continue;}
			// 				if ((hit_id==8 && flux_vz->at(j)/10. > 413.2) || (hit_id==12 && flux_vz->at(j)/10. > -66.8)){
			// 
			// 					backscat_counter++; 
			// 					continue;    
			// 				}
			// 			}

			///cut away the back scattering from lead			
			if ((hit_id==8 || hit_id==12) && flux_pz->at(j) < 0.){
				backscat_counter++; 
				continue;    
			}

// 			if (Is_eDIS && (W<2)) continue; /// cut for eDIS			
// 			cout << "W " << W << " rate " << rate <<  endl;

			/*Calculate Weight{{{*/
			double thisrate=0.0;
			double weight=0.0,weightR=0.0,weightPhi=0.0,weightTheta=0.0;
			double area=1.;      /// in 
			double areaR=2*3.1415926*r*1.; /// in mm2
			double areaPhi=1.;  /// in any deg      
			double areaTheta=2*3.1415926*r*(flux_avg_z->at(j)*(tan((Theta+0.25)/DEG)-tan((Theta-0.25)/DEG))); ///0.5deg width

			if (Is_EM) thisrate=current/Nevent;			
			else thisrate=rate/filenum;			
// 			cout << "thisrate" << rate << endl;
			
			weight=thisrate/1e3/area;
			weightR=thisrate/1e3/areaR;
			weightPhi=thisrate/1e3/areaPhi;
			weightTheta=thisrate/1e3/areaTheta;     
			/*End of Caluclate Weight}}}*/
	
			/*Start to Fill Histograms{{{*/			
			if (29<=hit_id && hit_id<=40 && flux_totEdep->at(j)<26e-6){} //gem required >26eV energy deposit in first 2 gas layer
			else if ((hit_id==17 || hit_id==26) && flux_totEdep->at(j)<1e-10){
				// 	  cout <<"flux_totEdep->at(j) " << flux_totEdep->at(j) << endl;  
			} //mrpc required >0 energy deposit			
			else if ((hit_id==28 || hit_id==42) && flux_totEdep->at(j)<1e-10){
				// 	  cout <<"flux_totEdep->at(j) " << flux_totEdep->at(j) << endl;  	  
			} //spd required >0 energy deposit
			else {  // all other just counting
				hvertex[hit_id][par]->Fill(flux_vz->at(j)/10.,sqrt(flux_vx->at(j)/10.*flux_vx->at(j)/10.+flux_vy->at(j)/10.*flux_vy->at(j)/10.));
				hvertexZ[hit_id][par]->Fill(flux_vz->at(j)/10.);      
			  
				hhitXY[hit_id][par]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.,weight); 
				hPlog[hit_id][par]->Fill(log10(P/1e3),weight);
				hElog[hit_id][par]->Fill(log10(flux_trackE->at(j)/1e3),weight);
				hEklog[hit_id][par]->Fill(log10(Ek/1e3),weight);
				hP_Theta[hit_id][par]->Fill(Theta,P/1e3,weightTheta); ///in 0.5deg bin      
				hP_R[hit_id][par]->Fill(r/10.,P/1e3,weightR/10.); ///in 1cm bin            
				hPlog_R[hit_id][par]->Fill(r/10.,log10(P/1e3),weightR/10.); ///in 1cm bin      
				hElog_R[hit_id][par]->Fill(r/10.,log10(flux_trackE->at(j)/1e3),weightR/10.); ///in 1cm bin
				hEklog_R[hit_id][par]->Fill(r/10.,log10(Ek/1e3),weightR/10.); ///in 1cm bin
				
				hEklog_R_Phi[hit_id][par]->Fill(phi-int(phi/12)*12,r/10.,log10(Ek/1e3),weight/30.);  // due to phi cover 12 degree, this will overlap 30 sector together, so we need to divide rate by 30
			
				/*EC front, to calculate EC energy deposit*/
				double energy_depo_Preshower=0,energy_depo_Shower=0;   
				if (hit_id==8 || hit_id==12){	    	  
					if(particle_ID==22) {
						energy_depo_Preshower=FastResponse("gamma","PS","scint",Ek/1e3);  //photon    
						energy_depo_Shower=FastResponse("gamma","S","scint",Ek/1e3);		    
					}
					else if (abs(particle_ID)==11) {
						energy_depo_Preshower=FastResponse("e","PS","scint",Ek/1e3); //electron or positron
						energy_depo_Shower=FastResponse("e","S","scint",Ek/1e3);		    
					}		  
					//     else if(particle_ID==2112) energy_depo_Preshower=3;  //neutron
					else if(particle_ID==2212) {
						energy_depo_Preshower=FastResponse("p","PS","scint",Ek/1e3);  //proton    
						energy_depo_Shower=FastResponse("p","S","scint",Ek/1e3);		    
					}		  
					else if(abs(particle_ID)==211)  {
						energy_depo_Preshower=FastResponse("pi","PS","scint",Ek/1e3);  //pip or pim
						energy_depo_Shower=FastResponse("pi","S","scint",Ek/1e3);		    
					}		  
					//     else if(particle_ID==321)  energy_depo_Preshower=7;  //Kp    
					//     else if(particle_ID==-321)  energy_depo_Preshower=8;  //Km
					//     else if(particle_ID==130)  energy_depo_Preshower=9;  //Kl    
					else energy_depo_Preshower=0;  //all other	    
					// 	    cout << "particle_ID " << particle_ID << " energy_depo " << energy_depo << endl;    
					hEdepR_Preshower[hit_id][par]->Fill(r/10.,energy_depo_Preshower*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2	    
					hEdepR_Shower[hit_id][par]->Fill(r/10.,energy_depo_Shower*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2	  
				}			

				//deal with high and low area for PVDIS
				if (phi-int(phi/12)*12<6) {
					hP_R_high[hit_id][par]->Fill(r/10.,P/1e3,weightR/10.*2.); /// in 1cm bin	
					hPlog_R_high[hit_id][par]->Fill(r/10.,log10(P/1e3),weightR/10.*2.); /// in 1cm bin	
					hEklog_R_high[hit_id][par]->Fill(r/10.,log10(Ek/1e3),weightR/10.*2.); /// in 1cm bin	
					if (hit_id==8 || hit_id==12){
						hEdepR_Preshower_high[hit_id][par]->Fill(r/10.,energy_depo_Preshower*weightR/100.*1e4*2.); ///in 10cm bin and from mm2 to 100cm2	    
						hEdepR_Shower_high[hit_id][par]->Fill(r/10.,energy_depo_Shower*weightR/100.*1e4*2.); ///in 10cm bin and from mm2 to 100cm2	  
					}
				}
				else {
					hP_R_low[hit_id][par]->Fill(r/10.,P/1e3,weightR/10.*2.); /// in 1cm bin	
					hPlog_R_low[hit_id][par]->Fill(r/10.,log10(P/1e3),weightR/10.*2.); /// in 1cm bin	
					hEklog_R_low[hit_id][par]->Fill(r/10.,log10(Ek/1e3),weightR/10.*2.); /// in 1cm bin	
					if (hit_id==8 || hit_id==12){
						hEdepR_Preshower_low[hit_id][par]->Fill(r/10.,energy_depo_Preshower*weightR/100.*1e4*2.); ///in 10cm bin and from mm2 to 100cm2	    
						hEdepR_Shower_low[hit_id][par]->Fill(r/10.,energy_depo_Shower*weightR/100.*1e4*2.); ///in 10cm bin and from mm2 to 100cm2	  
					}	
				}	
			
				hfluxR[hit_id][par]->Fill(r/10.,weightR/50.);   ///in 5cm bin
				hEfluxR[hit_id][par]->Fill(r/10.,Ek/1e3*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2

				///divide rate by 15 because it's 24 degree	    
				hfluxPhi[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15);	    	    
				hEfluxPhi[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15);    
				if(-10. < flux_vz->at(j)/10. && flux_vz->at(j)/10. < 30. && fabs(flux_vx->at(j)/10.)<5. && fabs(flux_vy->at(j)/10.)< 5.){
					hfluxPhi_target[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15); 
					hEfluxPhi_target[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15);
				}	
				else{
					hfluxPhi_other[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15);	      
					hEfluxPhi_other[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15); 
				}      

				hflux_x_y[hit_id][par]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.,weight/100.); //in 1cm2 bin	    
				if (phi-int(phi/12)*12<6) hflux_x_y_high[hit_id][par]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.,weight/100.);
				else hflux_x_y_low[hit_id][par]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.,weight/100.);    
				hEflux_x_y[hit_id][par]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.,weight*Ek/100.*10.); ///in 1cm2 bin and from 1cm to 10cm	   				
				hfluxEklog_cut[hit_id][par]->Fill(log10(Ek),weight);
// 				hfluxEklog_cut_niel[hit_id][par]->Fill(log10(Ek),weight);
			}
			/*End of Fill Histograms}}}*/
		}
		/*End of Looping flux}}}*/
	}
	/*End of Looping events}}}*/

	cout << "count_SC_act " << count_SC_act << " count_SC_inact " << count_SC_inact << endl;
	cout << "yescounter " << yescounter << " Ek_nocounter " << Ek_nocounter << " rate_nocounter " << rate_nocounter << endl;
	cout << "counter_actualphoton " << counter_actualphoton << " counter_acutalother " << counter_acutalother << endl;
	cout << "ratecounter " << ratecounter << endl;
	cout << "backscat_counter " << backscat_counter << endl;

	/*Operate Histograms{{{*/
	for(int k=0;k<n;k++){
		hhitXY[k][0]->Add(hhitXY[k][1],hhitXY[k][2]);
		hvertex[k][0]->Add(hvertex[k][1],hvertex[k][2]);
		hfluxR[k][0]->Add(hfluxR[k][1],hfluxR[k][2]);
		hfluxPhi[k][0]->Add(hfluxPhi[k][1],hfluxPhi[k][2]);
		hfluxPhi_target[k][0]->Add(hfluxPhi_target[k][1],hfluxPhi_target[k][2]);      
		hfluxPhi_other[k][0]->Add(hfluxPhi_other[k][1],hfluxPhi_other[k][2]);      
		hEfluxR[k][0]->Add(hEfluxR[k][1],hEfluxR[k][2]);
		hEdepR_Preshower[k][0]->Add(hEdepR_Preshower[k][1],hEdepR_Preshower[k][2]);
		hEdepR_Shower[k][0]->Add(hEdepR_Shower[k][1],hEdepR_Shower[k][2]);      
		hEdepR_Preshower_high[k][0]->Add(hEdepR_Preshower_high[k][1],hEdepR_Preshower_high[k][2]);
		hEdepR_Shower_high[k][0]->Add(hEdepR_Shower_high[k][1],hEdepR_Shower_high[k][2]);      
		hEdepR_Preshower_low[k][0]->Add(hEdepR_Preshower_low[k][1],hEdepR_Preshower_low[k][2]);
		hEdepR_Shower_low[k][0]->Add(hEdepR_Shower_low[k][1],hEdepR_Shower_low[k][2]);     

		hEfluxPhi[k][0]->Add(hEfluxPhi[k][1],hEfluxPhi[k][2]);
		hEfluxPhi_target[k][0]->Add(hEfluxPhi_target[k][1],hEfluxPhi_target[k][2]);
		hEfluxPhi_other[k][0]->Add(hEfluxPhi_other[k][1],hEfluxPhi_other[k][2]);   
		hflux_x_y[k][0]->Add(hflux_x_y[k][1],hflux_x_y[k][2]);
		hflux_x_y_high[k][0]->Add(hflux_x_y_high[k][1],hflux_x_y_high[k][2]);
		hflux_x_y_low[k][0]->Add(hflux_x_y_low[k][1],hflux_x_y_low[k][2]);   
		hEflux_x_y[k][0]->Add(hEflux_x_y[k][1],hEflux_x_y[k][2]);   
		hPlog[k][0]->Add(hPlog[k][1],hPlog[k][2]);
		hElog[k][0]->Add(hElog[k][1],hElog[k][2]);
		hEklog[k][0]->Add(hEklog[k][1],hEklog[k][2]);
		hfluxEklog_cut[k][0]->Add(hfluxEklog_cut[k][1],hfluxEklog_cut[k][2]);
		hfluxEklog_cut_niel[k][0]->Add(hfluxEklog_cut_niel[k][1],hfluxEklog_cut_niel[k][2]);
		hP_Theta[k][0]->Add(hP_Theta[k][1],hP_Theta[k][2]);
		hP_Theta_high[k][0]->Add(hP_Theta_high[k][1],hP_Theta_high[k][2]);   
		hP_Theta_low[k][0]->Add(hP_Theta_low[k][1],hP_Theta_low[k][2]);         
		hP_R[k][0]->Add(hP_R[k][1],hP_R[k][2]);
		hP_R_high[k][0]->Add(hP_R_high[k][1],hP_R_high[k][2]);   
		hP_R_low[k][0]->Add(hP_R_low[k][1],hP_R_low[k][2]);      
		hPlog_R[k][0]->Add(hPlog_R[k][1],hPlog_R[k][2]);
		hPlog_R_high[k][0]->Add(hPlog_R_high[k][1],hPlog_R_high[k][2]);
		hPlog_R_low[k][0]->Add(hPlog_R_low[k][1],hPlog_R_low[k][2]);   
		hEklog_R[k][0]->Add(hEklog_R[k][1],hEklog_R[k][2]);
		hEklog_R_high[k][0]->Add(hEklog_R_high[k][1],hEklog_R_high[k][2]);
		hEklog_R_low[k][0]->Add(hEklog_R_low[k][1],hEklog_R_low[k][2]);   
		hElog_R[k][0]->Add(hElog_R[k][1],hElog_R[k][2]);   
	}
	/*End of Operate Histograms}}}*/

	/*Plot and Save{{{*/
	TCanvas *c_pid = new TCanvas("pid","pid",900,900);
	gPad->SetLogy(1);
	hpid->Draw();

	TCanvas *c_mispid = new TCanvas("mispid","mispid",1200,900);
	c_mispid->Divide(2,1);
	c_mispid->cd(1);
	hactualphotonpid->Draw();
	c_mispid->cd(2);
	hactualothermass->Draw();

	TCanvas *c_hits = new TCanvas("hits","hits",1800,900);
	c_hits->Divide(n,m);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_hits->cd(l*n+k+1);    
			hhitXY[k][l]->Draw("colz");
		}
	}

	TCanvas *c_vertex = new TCanvas("vertex","vertex",1800,900);
	c_vertex->Divide(n,m);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			gPad->SetLogz(1);  
			c_vertex->cd(l*n+k+1);    
			hvertex[k][l]->Draw("colz");
		}
	}

	TCanvas *c_fluxR = new TCanvas("fluxR","fluxR",1800,900);
	c_fluxR->Divide(n,m);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_fluxR->cd(l*n+k+1);    
			hfluxR[k][l]->Draw();
		}
	}

	TCanvas *c_Plog = new TCanvas("Plog","Plog",1800,900);
	c_Plog->Divide(n,m);
	gPad->SetLogy(1);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_Plog->cd(l*n+k+1);    
			hPlog[k][l]->Draw(); 
		}
	}

	TCanvas *c_Elog = new TCanvas("Elog","Elog",1800,900);
	c_Elog->Divide(n,m);
	gPad->SetLogy(1);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_Elog->cd(l*n+k+1);
			hElog[k][l]->Draw();  
		}
	}

	TCanvas *c_Eklog = new TCanvas("Eklog","Eklog",1800,900);
	c_Eklog->Divide(n,m);
	gPad->SetLogy(1);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_Eklog->cd(l*n+k+1);
			hEklog[k][l]->Draw();  
		}
	}

	TCanvas *c_Eklog_R = new TCanvas("Eklog_R","Eklog_R",1800,900);
	c_Eklog_R->Divide(n,m);
	gPad->SetLogx(1);
	gPad->SetLogy(1);
	for(int l=0;l<m;l++){
		for(int k=0;k<n;k++){
			c_Eklog_R->cd(l*n+k+1);
			hEklog_R[k][l]->Draw("colz");
		}
	}

	// gStyle->SetOptStat(0);

	int color[6]={2,1,3,4,7,6};
	TCanvas *c_fluxR_gem = new TCanvas("fluxR_gem","fluxR_gem",900,900);
	gPad->SetLogy(1);  
	for(int k=0;k<6;k++){
		hfluxR[k][0]->SetLineColor(color[k]);
		hfluxR[k][0]->SetMarkerColor(color[k]);  
		hfluxR[k][0]->SetMaximum(100);
		hfluxR[k][0]->SetMinimum(0.01);  
		if (k==0) hfluxR[k][0]->Draw();
		else hfluxR[k][0]->Draw("same");
	}

	TCanvas *c_fluxPhi_gem = new TCanvas("fluxPhi_gem","fluxPhi_gem",900,900);
	gPad->SetLogy(1);  
	for(int k=0;k<6;k++){
		hfluxPhi[k][0]->SetLineColor(color[k]);
		hfluxPhi[k][0]->SetMarkerColor(color[k]);  
		hfluxPhi[k][0]->SetMaximum(100);
		hfluxPhi[k][0]->SetMinimum(0.01);  
		if (k==0) hfluxPhi[k][0]->Draw();
		else hfluxPhi[k][0]->Draw("same");
	}

	TCanvas *c_fluxR_cherenkov = new TCanvas("fluxR_cherenkov","fluxR_cherenkov",1200,600);
	c_fluxR_cherenkov->Divide(2,1);
	for(int k=6;k<8;k++){
		c_fluxR_cherenkov->cd(k-5);  
		for(int l=0;l<m;l++){
			hfluxR[k][l]->SetLineColor(l+1);
			if (l==0) hfluxR[k][l]->Draw();
			else hfluxR[k][l]->Draw("same");
		}
	}

	TCanvas *c_fluxR_mrpc = new TCanvas("fluxR_mrpc","fluxR_mrpc",1200,600);
	c_fluxR_mrpc->Divide(2,1);
	for(int k=16;k<18;k++){
		c_fluxR_mrpc->cd(k-15);    
		gPad->SetLogy(1);  
		for(int l=0;l<m;l++){
			hfluxR[k][l]->SetLineColor(l+1);
			if (l==0) hfluxR[k][l]->Draw();
			else hfluxR[k][l]->Draw("same");
		}
	}
	// //add text
	// TPaveText *pt = new TPaveText(0.6,0.6,0.95,0.9,"brNDC");
	// pt->SetFillColor(17);
	// pt->SetTextAlign(12);
	// pt->Draw();
	// for(int i=0;i<m;i++){
	// TText *text=pt->AddText(label[i].Data());
	// text->SetTextColor(i+1);
	// text->SetTextSize(0.024);
	// }

	TCanvas *c_Eklog_mrpc = new TCanvas("Eklog_mrpc","Eklog_mrpc",1200,600);
	c_Eklog_mrpc->Divide(2,1);
	for(int k=16;k<18;k++){
		c_Eklog_mrpc->cd(k-15);    
		gPad->SetLogy(1);    
		for(int l=0;l<m;l++){
			hEklog[k][l]->SetLineColor(l+1);
			if (l==0) hEklog[k][l]->Draw();
			else hEklog[k][l]->Draw("same");
		}
	}

	TCanvas *c_Eklog_R_mrpc = new TCanvas("Eklog_R_mrpc","Eklog_R_mrpc",300,900);
	c_Eklog_R_mrpc->Divide(2,m);
	for(int k=16;k<18;k++){
		for(int l=0;l<m;l++){
			c_Eklog_R_mrpc->cd(l*2+(k-15));
			hEklog_R[k][l]->Draw("colz");
		}
	}

	TCanvas *c_fluxR_ec = new TCanvas("fluxR_ec","fluxR_ec",1600,900);
	c_fluxR_ec->Divide(4,2);
	for(int k=8;k<16;k++){
		c_fluxR_ec->cd(k-7);
		gPad->SetLogy(1);  
		for(int l=0;l<m;l++){
			hfluxR[k][l]->SetMinimum(1e-7);
			hfluxR[k][l]->SetMaximum(1e7);    
			hfluxR[k][l]->SetLineColor(l+1);
			if (l==0) hfluxR[k][l]->Draw();
			else hfluxR[k][l]->Draw("same");
		}
	}
	// add text
	TPaveText *pt1 = new TPaveText(0.6,0.6,0.95,0.9,"brNDC");
	pt1->SetFillColor(17);
	pt1->SetTextAlign(12);
	pt1->Draw();
	for(int i=0;i<m;i++){
		TText *text=pt1->AddText(label[i].Data());
		text->SetTextColor(i+1);
		text->SetTextSize(0.024);
	}

	TCanvas *c_fluxPhi_ec = new TCanvas("fluxPhi_ec","fluxPhi_ec",1600,900);
	c_fluxPhi_ec->Divide(4,2);
	for(int k=8;k<16;k++){
		c_fluxPhi_ec->cd(k-7);
		gPad->SetLogy(1);  
		for(int l=0;l<m;l++){
			hfluxPhi[k][l]->SetMinimum(1e-7);
			hfluxPhi[k][l]->SetMaximum(1e7);    
			hfluxPhi[k][l]->SetLineColor(l+1);
			if (l==0) hfluxPhi[k][l]->Draw();
			else hfluxPhi[k][l]->Draw("same");
		}
	}

	// TCanvas *c_EdepR_Preshower_ec = new TCanvas("EdepR_Preshower_ec","EdepR_Preshower_ec",1600,900);
	// c_EdepR_Preshower_ec->Divide(2,1);
	// { int k=8;
	//   c_EdepR_Preshower_ec->cd(1);
	//   gPad->SetLogy(1);
	//   for(int l=0;l<m;l++){
	// //     hEdepR_Preshower[k][l]->SetMinimum(1e0);
	// //     hEdepR_Preshower[k][l]->SetMaximum(1e8);
	//     hEdepR_Preshower[k][l]->SetLineColor(l+1);
	//     if (l==0) hEdepR_Preshower[k][l]->Draw();
	//     else hEdepR_Preshower[k][l]->Draw("same");
	//   }
	// }
	// { int k=12;
	//   c_EdepR_Preshower_ec->cd(2);
	//   gPad->SetLogy(1);
	//   for(int l=0;l<m;l++){
	// //     hEdepR_Preshower[k][l]->SetMinimum(1e0);
	// //     hEdepR_Preshower[k][l]->SetMaximum(1e8);
	//     hEdepR_Preshower[k][l]->SetLineColor(l+1);
	//     if (l==0) hEdepR_Preshower[k][l]->Draw();
	//     else hEdepR_Preshower[k][l]->Draw("same");
	//   }
	// }

	TCanvas *c_EfluxR_ec = new TCanvas("EfluxR_ec","EfluxR_ec",1600,900);
	c_EfluxR_ec->Divide(4,2);
	for(int k=8;k<16;k++){
		c_EfluxR_ec->cd(k-7);
		gPad->SetLogy(1);
		for(int l=0;l<m;l++){
			hEfluxR[k][l]->SetMinimum(1e0);
			hEfluxR[k][l]->SetMaximum(1e8);
			hEfluxR[k][l]->SetLineColor(l+1);
			if (l==0) hEfluxR[k][l]->Draw();
			else hEfluxR[k][l]->Draw("same");
		}
	}

	TCanvas *c_EfluxPhi_ec = new TCanvas("EfluxPhi_ec","EfluxPhi_ec",1600,900);
	c_EfluxPhi_ec->Divide(4,2);
	for(int k=8;k<16;k++){
		c_EfluxPhi_ec->cd(k-7);
		gPad->SetLogy(1);
		for(int l=0;l<m;l++){
			//     hEfluxPhi[k][l]->SetMinimum(1e0);
			//     hEfluxPhi[k][l]->SetMaximum(1e8);
			hEfluxPhi[k][l]->SetLineColor(l+1);
			if (l==0) hEfluxPhi[k][l]->Draw();
			else hEfluxPhi[k][l]->Draw("same");
		}
	}

	/*Neutrons{{{*/	

	gSystem->Load("./niel/niel_fun_cc.so"); 
	TNiel niel_proton("./niel/niel_proton.txt");
	TNiel niel_electron("./niel/niel_electron.txt");
	TNiel niel_pions("./niel/niel_pions.txt");
	TNiel niel_neutron("./niel/niel_neutron.txt");
	TH1F *hniel_proton=new TH1F("niel_proton","niel_proton",100,-6,2);	
	TH1F *hniel_electron=new TH1F("niel_electron","niel_electron",100,-6,2);	
	TH1F *hniel_pions=new TH1F("niel_pions","niel_pions",100,-6,2);	
	TH1F *hniel_neutron=new TH1F("niel_neutron","niel_neutron",100,-6,2);
	for(int i=0;i<100;i++) hniel_proton->SetBinContent(i+1,niel_proton.GetNielFactor(pow(10,(i*(8./100.)-6))));
	for(int i=0;i<100;i++) hniel_electron->SetBinContent(i+1,niel_electron.GetNielFactor(pow(10,(i*(8./100.)-6))));	
	for(int i=0;i<100;i++) hniel_pions->SetBinContent(i+1,niel_pions.GetNielFactor(pow(10,(i*(8./100.)-6))));
	for(int i=0;i<100;i++) hniel_neutron->SetBinContent(i+1,niel_neutron.GetNielFactor(pow(10,(i*(8./100.)-6))));
	
	TCanvas *c_niel = new TCanvas("niel","niel",900,900);
	gPad->SetLogy(1);
	hniel_proton->SetMinimum(1e-5);
	hniel_proton->SetMaximum(1e4);		
	hniel_proton->Draw();
	hniel_electron->Draw("same");
	hniel_pions->Draw("same");
	hniel_neutron->Draw("same");	

	for(int k=0;k<n;k++){	
			//   pid =0   photon+electron+positron
			//        1   photon    
			//        2   electron + positron
			//        3   neutron
			//        4   proton
			//        5   pip
			//        6   pim
			//        7   Kp
			//        8   Km
			//        9   Kl
			//       10   other  	  
	  hfluxEklog_cut_niel[k][2]->Multiply(hfluxEklog_cut[k][2],hniel_electron);	  
	  hfluxEklog_cut_niel[k][3]->Multiply(hfluxEklog_cut[k][3],hniel_neutron);
	  hfluxEklog_cut_niel[k][4]->Multiply(hfluxEklog_cut[k][4],hniel_proton);
	  hfluxEklog_cut_niel[k][5]->Multiply(hfluxEklog_cut[k][5],hniel_pions);
	  hfluxEklog_cut_niel[k][6]->Multiply(hfluxEklog_cut[k][6],hniel_pions);	  	  
	}

	cout << hfluxEklog_cut_niel[8][3]->Integral() << endl;
	cout << hfluxEklog_cut_niel[11][3]->Integral() << endl;
	cout << hfluxEklog_cut_niel[12][3]->Integral() << endl;
	cout << hfluxEklog_cut_niel[15][3]->Integral() << endl;

	TCanvas *c_neutron_ec = new TCanvas("neutron_ec","neutron_ec",1600,900);
	c_neutron_ec->Divide(4,2);
	c_neutron_ec->cd(1);
	gPad->SetLogy(1);
	// hfluxR[8][3]->SetLineColor(1);
	hfluxR[8][3]->Draw();
	// hfluxR[11][3]->SetLineColor(2);
	hfluxR[11][3]->Draw("same");
	c_neutron_ec->cd(2);
	gPad->SetLogy(1);
	// hEklog[8][3]->SetLineColor(1);
	hEklog[8][3]->Draw();
	// hEklog[11][3]->SetLineColor(2);
	hEklog[11][3]->Draw("same");
	c_neutron_ec->cd(3);
	gPad->SetLogy(1);
	hfluxEklog_cut[8][3]->SetLineColor(1);
	hfluxEklog_cut[8][3]->Draw();
	hfluxEklog_cut[11][3]->SetLineColor(2);
	hfluxEklog_cut[11][3]->Draw("same");
	c_neutron_ec->cd(4);
	gPad->SetLogy(1);
	hfluxEklog_cut_niel[8][3]->SetLineColor(1);
	hfluxEklog_cut_niel[8][3]->Draw();
	hfluxEklog_cut_niel[11][3]->SetLineColor(2);
	hfluxEklog_cut_niel[11][3]->Draw("same");
	c_neutron_ec->cd(5);
	gPad->SetLogy(1);
	// hfluxR[12][3]->SetLineColor(1);
	hfluxR[12][3]->Draw();
	// hfluxR[15][3]->SetLineColor(2);
	hfluxR[15][3]->Draw("same");
	c_neutron_ec->cd(6);
	gPad->SetLogy(1);
	// hEklog[12][3]->SetLineColor(1);
	hEklog[12][3]->Draw();
	// hEklog[15][3]->SetLineColor(2);
	hEklog[15][3]->Draw("same");
	c_neutron_ec->cd(7);
	gPad->SetLogy(1);
	hfluxEklog_cut[12][3]->SetLineColor(1);
	hfluxEklog_cut[12][3]->Draw();
	hfluxEklog_cut[15][3]->SetLineColor(2);
	hfluxEklog_cut[15][3]->Draw("same");
	c_neutron_ec->cd(8);
	gPad->SetLogy(1);
	hfluxEklog_cut_niel[12][3]->SetLineColor(1);
	hfluxEklog_cut_niel[12][3]->Draw();
	hfluxEklog_cut_niel[15][3]->SetLineColor(2);
	hfluxEklog_cut_niel[15][3]->Draw("same");

	/*Neutrons}}}*/
	/*End of Plot and Save}}}*/

	outputfile->Write();
	outputfile->Flush();
}
