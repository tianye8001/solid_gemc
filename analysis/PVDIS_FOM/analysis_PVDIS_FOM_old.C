#include <iostream> 
#include <fstream>
#include <cmath> 
#include "math.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMinuit.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TArc.h"
#include "TString.h"
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TFile.h"

using namespace std;

// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 
// const double filenum=50; //file numbers while running GEMC in order to be correct for normalization
const int loop_time=1;   //electron to be 1, pion to be many times to take advantage of statistics, pion has low efficiency on EC
const int add_norm=1; // additional normalization factor

bool Is_debug=false;

const double DEG=180./3.1415926;   //rad to degree

//#####################################################################################################################################################

int analysis_PVDIS_FOM(string inputfile_name,string genfile_name,string runmode="phys", bool Is_tellorig=false,string filetype=""){

// gStyle->SetOptStat(11111111);
  gStyle->SetOptStat(0);

  //open file from generator
TFile *file_rate=new TFile(genfile_name.c_str());
// TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_6.6GeV_eDIS_1e6.root");
  
//     if (file->IsZombie()) {
//        cout << "Error opening file" << input_filename << endl;
//        exit(-1);
//     }
//     else cout << "open file " << input_filename << endl;

// double pf,theta,phi,Q2,x,W,rate,Abeam;
double Abeam;
TTree *T = (TTree*) file_rate->Get("T");
// T->SetBranchAddress("pf",&pf);
// T->SetBranchAddress("theta",&theta);
// T->SetBranchAddress("phi",&phi);
// T->SetBranchAddress("Q2",&Q2);
// T->SetBranchAddress("x",&x);
// T->SetBranchAddress("W",&W);
// T->SetBranchAddress("rate",&rate);
T->SetBranchAddress("Abeam",&Abeam);  
  
double rout_cut_FA=0,rin_cut_FA=0,rout_cut_LA=0,rin_cut_LA=0;
if (runmode=="phys"){
 cout << "runmode: phys" << endl;
}else if(runmode=="trigger"){
 cout << "runmode: trigger" << endl;
}
else {cout << "need to know runmode: phys or trigger" << endl; return 0;}
  
bool Is_singlefile=false;
bool Is_pi0=false;
if(Is_tellorig){
if(filetype.find("single",0) != string::npos) {
  Is_singlefile=true;
  cout << "this is a single file" << endl;  
}
else if(filetype.find("sidis",0) != string::npos) {
  Is_singlefile=false;
  cout << "this is a sidis file" << endl;      
}
else {cout << "unknown file type, choose either single or sidis" << endl;return 0;}

if (inputfile_name.find("pi0",0) != string::npos) {
  Is_pi0=true;
  cout << "this is a pi0 file" << endl;  
}
else {cout << "this is NOT a pi0 file" << endl;}
}

string filemode;
double event_actual=1;
if (inputfile_name.find("BeamOnTargetEM",0) != string::npos) {
  filemode="BeamOnTargetEM";
  cout << "this is a BeamOnTargetEM file" << endl;  
  
  event_actual=atof(inputfile_name.substr(inputfile_name.find("BeamOnTargetEM",0)+15,inputfile_name.find("_")).c_str());
  cout << "event_actual " << event_actual <<  endl;  
}
else if (inputfile_name.find("BeamOnTarget",0) != string::npos) {
  filemode="BeamOnTarget";
  cout << "this is a BeamOnTarget file" << endl;  
  
  event_actual=atof(inputfile_name.substr(inputfile_name.find("BeamOnTarget",0)+13,inputfile_name.find("_")).c_str());
  cout << "event_actual " << event_actual <<  endl;  
}
else if (inputfile_name.find("even",0) != string::npos) {
  filemode="even";
  cout << "this is a evenly distributed file" << endl;  
}
else {
  filemode="rate";  
  cout << "this is rate dependent file" << endl;  
}

double filenum=1;
if (inputfile_name.find("_filenum",0) != string::npos) {
  filenum=atof(inputfile_name.substr(inputfile_name.find("_filenum")+8,inputfile_name.find("_")).c_str());
    cout << "filenum " << filenum << " for addtional normalization, YOU Need to Make Sure It's CORRECT!" <<  endl;
}
else {
  if (filemode=="rate"){
    cout << "this file is rate dependent, but has no filenum, something is wrong" << endl;  
    return 0;
  }
  else{
    cout << "this file has no filenum, please check if you need filenum for addtional normalization" << endl;      
  }
}

TFile *file=new TFile(inputfile_name.c_str());

// 	TString background_inputfile_name="parametrized_lgc.root";      //h_pe is here	
// 	TFile *background_file=new TFile(background_inputfile_name);
// 	TH1F *h_pe=(TH1F*)background_file->Get("h_pe");

// std::size_t found = inputfile_name.rfind("cache");
// if (found!=std::string::npos)  inputfile_name.replace(found,5,"/home/$USER");

// char the_filename[200];
// sprintf(the_filename, "%s",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());

// char outputfile_name[200];
// sprintf(outputfile_name, "%s_output.root",the_filename);
// TFile *outputfile=new TFile(outputfile_name, "recreate");

TFile *outputfile=new TFile("output.root", "recreate");

// prepare for outputs
// define histograms, output txt files etc...

	TH2F *hgen_ThetaP=new TH2F("gen_ThetaP","generated events;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);  
	TH2F *hgen_ThetaPhi=new TH2F("gen_ThetaPhi","generated events;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);     
	TH2F *hgen_PhiP=new TH2F("gen_PhiP","generated events;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);	
	
	TH3F *hgen_ThetaPhiP=new TH3F("gen_ThetaPhiP","gen_ThetaPhiP",50,0,50,180,-180,180,55,0,11);   
	

	TH1F *hrate_P_gen=new TH1F("rate_P_gen","rate_P_gen",110,0,11);
	TH1F *hrate_P_acc=new TH1F("rate_P_acc","rate_P_acc",110,0,11);
	TH1F *hacceptance_P=new TH1F("acceptance_P","acceptance_P",110,0,11);
	TH1F *hrate_Theta_gen=new TH1F("rate_Theta_gen","rate_Theta_gen",100,0,50);
	TH1F *hrate_Theta_acc=new TH1F("rate_Theta_acc","rate_Theta_acc",100,0,50);
	TH1F *hacceptance_Theta=new TH1F("acceptance_Theta","acceptance_Theta",100,0,50);
	TH1F *hrate_x_gen=new TH1F("rate_x_gen","rate_x_gen",100,0,1);
	TH1F *hrate_x_acc=new TH1F("rate_x_acc","rate_x_acc",100,0,1);
	TH1F *hacceptance_x=new TH1F("acceptance_x","acceptance_x",100,0,1);
	TH1F *hrate_Q2_gen=new TH1F("rate_Q2_gen","rate_Q2_gen",140,0,14);
	TH1F *hrate_Q2_acc=new TH1F("rate_Q2_acc","rate_Q2_acc",140,0,14);
	TH1F *hacceptance_Q2=new TH1F("acceptance_Q2","acceptance_Q2",140,0,14);

	TH2F *hrate_PTheta_gen=new TH2F("rate_PTheta_gen","rate_PTheta_gen",50,0,50,110,0,11);
	TH2F *hrate_PTheta_acc=new TH2F("rate_PTheta_acc","rate_PTheta_acc",50,0,50,110,0,11);
	TH2F *hacceptance_PTheta=new TH2F("acceptance_PTheta","acceptance_PTheta",50,0,50,110,0,11);
	TH2F *hrate_Q2x_gen=new TH2F("rate_Q2x_gen","rate_Q2x_gen",100,0,1,140,0,14);
	TH2F *hrate_Q2x_acc=new TH2F("rate_Q2x_acc","rate_Q2x_acc",100,0,1,140,0,14);
	TH2F *hacceptance_Q2x=new TH2F("acceptance_Q2x","acceptance_Q2x",100,0,1,140,0,14);

	TH2F *hAbeam_Q2x_gen=new TH2F("Abeam_Q2x_gen","Abeam_Q2x_gen",100,0,1,140,0,14);
	TH2F *hAbeam_Q2x_acc=new TH2F("Abeam_Q2x_acc","Abeam_Q2x_acc",100,0,1,140,0,14);
	TH2F *hAbeamErr_Q2x_gen=new TH2F("AbeamErr_Q2x_gen","AbeamErr_Q2x_gen",100,0,1,140,0,14);
	TH2F *hAbeamErr_Q2x_acc=new TH2F("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",100,0,1,140,0,14);
	TH2F *hApv_Q2x_gen=new TH2F("Apv_Q2x_gen","Apv_Q2x_gen",100,0,1,140,0,14);
	TH2F *hApv_Q2x_acc=new TH2F("Apv_Q2x_acc","Apv_Q2x_acc",100,0,1,140,0,14);
	TH2F *hApvErr_Q2x_gen=new TH2F("ApvErr_Q2x_gen","ApvErr_Q2x_gen",100,0,1,140,0,14);
	TH2F *hApvErr_Q2x_acc=new TH2F("ApvErr_Q2x_acc","ApvErr_Q2x_acc",100,0,1,140,0,14);

	TH2F *hrate_Q2x_acc_bin=new TH2F("rate_Q2x_acc_bin","rate_Q2x_acc_bin",10,0,1,7.5,0,15);
	TH2F *hApvErr_Q2x_acc_bin=new TH2F("ApvErr_Q2x_acc_bin","ApvErr_Q2x_acc_bin",10,0,1,7.5,0,15);

	TH2F *hrate_PTheta_zwzhao_gen=new TH2F("rate_PTheta_zwzhao_gen","rate_PTheta_zwzhao_gen",13,20,44,20,0,6);
	TH2F *hrate_PTheta_zwzhao_acc=new TH2F("rate_PTheta_zwzhao_acc","rate_PTheta_zwzhao_acc",13,20,44,20,0,6);
	TH2F *hrate_PTheta_seamus_gen=new TH2F("rate_PTheta_seamus_gen","rate_PTheta_seamus_gen",13,20,44,20,0,6);

	//-------------------------
	//   get trees in the real data file
	//-------------------------
	
	//---header tree
	TTree *tree_header = (TTree*) file->Get("header");
	vector <int> *evn=0,*evn_type=0;
	vector <double> *beamPol=0;
	vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
	tree_header->SetBranchAddress("evn",&evn);      // event number 
	tree_header->SetBranchAddress("evn_type",&evn_type);  // evn_type==-1 for simulated events
	tree_header->SetBranchAddress("beamPol",&beamPol);   //beam polarization
	tree_header->SetBranchAddress("var1",&var1);     // W+ rate
	tree_header->SetBranchAddress("var2",&var2);     // W- rate
	tree_header->SetBranchAddress("var3",&var3);     // target pol
	tree_header->SetBranchAddress("var4",&var4);     //x
	tree_header->SetBranchAddress("var5",&var5);     //y
	tree_header->SetBranchAddress("var6",&var6);     //w
	tree_header->SetBranchAddress("var7",&var7);     //Q2
	tree_header->SetBranchAddress("var8",&var8);     //rate, Hz, should check the input file of the simulation

	//---generated tree
	//particle generated with certain momentum at certain vertex
	TTree *tree_generated = (TTree*) file->Get("generated");
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID 
	tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	tree_generated->SetBranchAddress("py",&gen_py);
	tree_generated->SetBranchAddress("pz",&gen_pz);
	tree_generated->SetBranchAddress("vx",&gen_vx);    //vertex of the generated particle at target
	tree_generated->SetBranchAddress("vy",&gen_vy);
	tree_generated->SetBranchAddress("vz",&gen_vz);

	//--- flux
	//the real deal output from the GEMC simulation
	TTree *tree_flux = (TTree*) file->Get("flux");
	vector<int> *flux_id=0,*flux_hitn=0;
	vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	tree_flux->SetBranchAddress("hitn",&flux_hitn);     // hit number
	tree_flux->SetBranchAddress("id",&flux_id);         //hitting detector ID
	tree_flux->SetBranchAddress("pid",&flux_pid);       //pid
	tree_flux->SetBranchAddress("mpid",&flux_mpid);     // mother pid
	tree_flux->SetBranchAddress("tid",&flux_tid);       // track id
	tree_flux->SetBranchAddress("mtid",&flux_mtid);     // mother track id
	tree_flux->SetBranchAddress("otid",&flux_otid);     // original track id
	tree_flux->SetBranchAddress("trackE",&flux_trackE);  // track energy of 1st step,  track here is G4 track
	tree_flux->SetBranchAddress("totEdep",&flux_totEdep); // totEdep in all steps, track here is G4 track
	tree_flux->SetBranchAddress("avg_x",&flux_avg_x);     //average x, weighted by energy deposition in each step
	tree_flux->SetBranchAddress("avg_y",&flux_avg_y);     //average y
	tree_flux->SetBranchAddress("avg_z",&flux_avg_z);     //average z
	tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);   // local average x 
	tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);   // local average y
	tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);   // local average z
	tree_flux->SetBranchAddress("px",&flux_px);          // px of 1st step
	tree_flux->SetBranchAddress("py",&flux_py);          // py of 1st step
	tree_flux->SetBranchAddress("pz",&flux_pz);          // pz of 1st step
	tree_flux->SetBranchAddress("vx",&flux_vx);          // x coordinate of 1st step
	tree_flux->SetBranchAddress("vy",&flux_vy);          // y coordinate of 1st step
	tree_flux->SetBranchAddress("vz",&flux_vz);          // z coordinate of 1st step
	tree_flux->SetBranchAddress("mvx",&flux_mvx);        // mother
	tree_flux->SetBranchAddress("mvy",&flux_mvy);
	tree_flux->SetBranchAddress("mvz",&flux_mvz);
	tree_flux->SetBranchAddress("avg_t",&flux_avg_t);     //average time stamp


	TRandom3 rand;
	rand.SetSeed(0);
	
	long int N_events = (long int)tree_header->GetEntries();

cout << "generator has entry " <<  T->GetEntries() << endl;
cout << "output has entry " << tree_header->GetEntries() << endl;;
	
// 	cout << "total number of events : " << N_events << endl;	

double thatrate[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Abeam_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Apv_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//----------------------------
	//      loop trees
	//---------------------------
	for(int loop_id=1;loop_id<=loop_time;loop_id++){
		cout<<"loop.....  "<<loop_id<<endl;
	
	for(long int i=0;i<N_events;i++){	  
// 			cout<<"event " << i<<endl;
// 			cout<<i<<"\r";
// 			cout<<i<<"\n";	  
	  
		T->GetEntry(i); //get entry from generator
  
		//---
		//---header tree
		//---
		tree_header->GetEntry(i);
		double rate=var8->at(0);
		if (filemode=="BeamOnTargetEM" || filemode=="BeamOnTarget") {
// 		  if(Is_SIDIS_He3) rate=15e-6/1.6e-19/event_actual/loop_time*add_norm;
// 		  else if(Is_SIDIS_NH3) rate=100e-9/1.6e-19/event_actual/loop_time*add_norm;
// 		  else if(Is_JPsi_LH2) rate=3e-6/1.6e-19/event_actual/loop_time*add_norm; 	  
// 		  else {
// 		    cout << "Not SIDIS_He3 or SIDIS_NH3  or JPsi_LH2 setup" << endl;    
// 		    return 0;
// 		  }
		}
		else if (filemode=="even") rate=1;
		else if (filemode=="rate") rate=rate/filenum/loop_time*add_norm;
		else {
		    cout << "Not right filemode" << endl;    
		    return 0; 
		}
		
		double x=var4->at(0);	
		double y=var5->at(0);
		double W=var6->at(0);		
		double Q2=var7->at(0);		
		
		//cout<<"header tree: "<<rate<<endl;	

		//---
		//---generated tree
		//---
		tree_generated->GetEntry(i);
		int n_gen=gen_pid->size();
		//cout<<"generated : "<<n_gen<<endl;
		int pid_gen=0;
		double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
	      //       cout << "gen_pid->size() " << gen_pid->size() << endl;        
		for (int j=0;j<gen_pid->size();j++) {
// 	            cout << gen_pid->at(j) << " " << gen_px->at(j) << " " << gen_py->at(j) << " " << gen_pz->at(j) << " " << gen_vx->at(j) << " " << gen_vy->at(j) << " " << gen_vz->at(j) << endl; 
		    pid_gen=gen_pid->at(j);
		    px_gen=gen_px->at(j);
		    py_gen=gen_py->at(j);
		    pz_gen=gen_pz->at(j);
		    vx_gen=gen_vx->at(j);
		    vy_gen=gen_vy->at(j);
		    vz_gen=gen_vz->at(j);
		    p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
		    theta_gen=acos(pz_gen/p_gen)*DEG;
		    phi_gen=atan2(py_gen,px_gen)*DEG;
	      //       cout << "p_gen " << p_gen << endl; 
		    
		}		

// 		if (vz_gen<-3550 || -3450<vz_gen) continue;

		hgen_ThetaP->Fill(theta_gen,p_gen/1e3,rate);
		hgen_ThetaPhi->Fill(theta_gen,phi_gen,rate);                  		
		hgen_PhiP->Fill(phi_gen,p_gen/1e3,rate);                  				
		hgen_ThetaPhiP->Fill(theta_gen,phi_gen,p_gen/1e3,rate);                  			
		///////////////////////////////////////////////////////////////////////////////////////
		//       do trigger
		////////////////////////////////////////////////////////////////////////////////////////
		//---	
		//---flux tree
		//---
		tree_flux->GetEntry(i);
			
		//check on EC and other by flux
	
		double acc=0,eff=0;
		
		for (Int_t j=0;j<flux_hitn->size();j++) {
	    //       cout << "flux " << " !!! " << flux_hitn->at(j) << " " << flux_id->at(j) << " " << flux_pid->at(j) << " " << flux_mpid->at(j) << " " << flux_tid->at(j) << " " << flux_mtid->at(j) << " " << flux_trackE->at(j) << " " << flux_totEdep->at(j) << " " << flux_avg_x->at(j) << " " << flux_avg_y->at(j) << " " << flux_avg_z->at(j) << " " << flux_avg_lx->at(j) << " " << flux_avg_ly->at(j) << " " << flux_avg_lz->at(j) << " " << flux_px->at(j) << " " << flux_py->at(j) << " " << flux_pz->at(j) << " " << flux_vx->at(j) << " " << flux_vy->at(j) << " " << flux_vz->at(j) << " " << flux_mvx->at(j) << " " << flux_mvy->at(j) << " " << flux_mvz->at(j) << " " << flux_avg_t->at(j) << endl;  

		  int detector_ID=flux_id->at(j)/1000000;
		  int subdetector_ID=(flux_id->at(j)%1000000)/100000;
		  int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;		  
		  int component_ID=flux_id->at(j)%10000;      

		double hit_vr=sqrt(pow(flux_vx->at(j),2)+pow(flux_vy->at(j),2))/1e1; //mm to cm
		double hit_vy=flux_vy->at(j)/1e1,hit_vx=flux_vx->at(j)/1e1,hit_vz=flux_vz->at(j)/1e1;           //mm to cm		  
		double hit_r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/1e1; //mm to cm
		double hit_y=flux_avg_y->at(j)/1e1,hit_x=flux_avg_x->at(j)/1e1,hit_z=flux_avg_z->at(j)/1e1;           //mm to cm		
		double hit_phi=atan2(hit_y,hit_x)*DEG;       //rad to  deg
		double hit_p=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j))/1e3;  //MeV to GeV
		  
		  int hit_id=-1;
		  if (detector_ID==1 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=0;
		  if (detector_ID==1 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=1;	  
		  if (detector_ID==1 && subdetector_ID == 3 && subsubdetector_ID == 1) hit_id=2;	  
		  if (detector_ID==1 && subdetector_ID == 4 && subsubdetector_ID == 1) hit_id=3;	  
		  if (detector_ID==1 && subdetector_ID == 5 && subsubdetector_ID == 1) hit_id=4;	  
		  if (detector_ID==1 && subdetector_ID == 6 && subsubdetector_ID == 1) hit_id=5;	        
		  if (detector_ID==2 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=6;
		  if (detector_ID==2 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=7;	              
		  if (detector_ID==5 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=8;
		  if (detector_ID==5 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=9;	                          
		  if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=10;
		  if (detector_ID==3 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=11;
		  
		  if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=12;  
	 
		  if (detector_ID==6 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=13;
		  if (detector_ID==6 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=14;  
		  
// // 		  if ((0<=hit_id && hit_id<=9) || hit_id==12){
// 		  if (0<=hit_id && hit_id<=9){		  
// 		    if(abs(int(flux_pid->at(j))) == 11)	{		    
// 		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate);
// 		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate);		  
// 		    }
// 		    else if (int(flux_pid->at(j))==22){		      
// 		      //assume 5% photon conversion to hits for detector other than EC
// 		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate*0.05);
// 		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate*0.05);	
// 		    }
// 		  }
// 		  else if (10<=hit_id && hit_id<=11){	      
// 		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate);
// 		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate);		  		      
// 		  }
// // 		  else cout << flux_id->at(j) << endl;
		  
		  if(hit_id==10 && flux_tid->at(j)==1) hit_phi_FAEC=hit_phi;
		  if(hit_id==8 && flux_tid->at(j)==1) hit_phi_FASPD=hit_phi;
		  if(hit_id==9 && flux_tid->at(j)==1) hit_phi_LASPD=hit_phi;
		  
// 		  if (0<=hit_id && hit_id<=11) hflux_hitxy[hit_id]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.);
	    //       else cout << "flux_id->at(j) " << flux_id->at(j) << endl;
		  
		  //check hit on EC and find sec_ec
		  if(hit_id==10){   //FAEC 
// 		    if (hit_r<rin_cut_FA || hit_r>rout_cut_FA) continue; //trigger cut on R

		    int sec_ec=0;
		    int sec_shift=1.7;  // shift to match electron turning in field
		    if (hit_phi>=90+sec_shift) sec_ec=int((hit_phi-90-sec_shift)/12+1);
		    else sec_ec=int((hit_phi+360-90-sec_shift)/12+1);
// 	    	cout << " hit_phi " << hit_phi << " sec_ec " << sec_ec << endl;	
		    
		    if(flux_tid->at(j)==1) {acc=1;}
		    eff=1;
		    			     
		  }		
		}	//end of flux loop		
	
	      double pf=p_gen;
	      
	      if (22<theta*DEG && theta*DEG <35){ 
		  hrate_P_gen->Fill(pf,rate);
		  hrate_P_acc->Fill(pf,rate*acc*eff);
		  hrate_Theta_gen->Fill(theta*DEG,rate);
		  hrate_Theta_acc->Fill(theta*DEG,rate*acc*eff);
		  hrate_x_gen->Fill(x,rate);
		  hrate_x_acc->Fill(x,rate*acc*eff);
		  hrate_Q2_gen->Fill(Q2,rate);
		  hrate_Q2_acc->Fill(Q2,rate*acc*eff);
	      }
	      
	      hrate_PTheta_gen->Fill(theta*DEG,pf,rate);
	      hrate_PTheta_acc->Fill(theta*DEG,pf,rate*acc*eff);
	      hrate_PTheta_zwzhao_gen->Fill(theta*DEG,pf,rate);
	      hrate_PTheta_zwzhao_acc->Fill(theta*DEG,pf,rate*acc*eff);
	      
	      hrate_Q2x_gen->Fill(x,Q2,rate);
	      hrate_Q2x_acc->Fill(x,Q2,rate*acc*eff);
	      hrate_Q2x_acc_bin->Fill(x,Q2,rate*acc*eff);

	      hAbeam_Q2x_gen->Fill(x,Q2,-Abeam*rate);
	      hAbeam_Q2x_acc->Fill(x,Q2,-Abeam*rate*acc*eff);

	      double Apv=0.84e-4*Q2;  
	      hApv_Q2x_gen->Fill(x,Q2,Apv*rate);
	      hApv_Q2x_acc->Fill(x,Q2,Apv*rate*acc*eff);  
	      
	      hApvErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*time)/pb*100);
	      hAbeamErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*time)/pb*100);  
	      if (acc*eff !=0) {
		hApvErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*time*acc*eff)/pb*100);
		hAbeamErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*time*acc*eff)/pb*100);
	      }
	      
		  for(int k = 0; k < Nbin; k++){  
		    if (bin[k][0] <= x && x < bin[k][1] && bin[k][2] <= Q2 && Q2 < bin[k][3]){
		      thatrate[k] += rate*acc*eff;
		      Apv_sum[k] += Apv*rate*acc*eff;
		      Abeam_sum[k] += -Abeam*rate*acc*eff;
		    }
		  }		

	} //end event loop
	
	} //end loop time

//do outputs

hAbeam_Q2x_gen->Divide(hAbeam_Q2x_gen,hrate_Q2x_gen);
hAbeam_Q2x_acc->Divide(hAbeam_Q2x_acc,hrate_Q2x_acc);
hApv_Q2x_gen->Divide(hApv_Q2x_gen,hrate_Q2x_gen);
hApv_Q2x_acc->Divide(hApv_Q2x_acc,hrate_Q2x_acc);

hAbeamErr_Q2x_gen->Divide(hAbeamErr_Q2x_gen,hAbeam_Q2x_gen);
hAbeamErr_Q2x_acc->Divide(hAbeamErr_Q2x_acc,hAbeam_Q2x_acc);
hApvErr_Q2x_gen->Divide(hApvErr_Q2x_gen,hApv_Q2x_gen);
hApvErr_Q2x_acc->Divide(hApvErr_Q2x_acc,hApv_Q2x_acc);

TCanvas *c_rate_PTheta = new TCanvas("rate_PTheta","rate_PTheta",1800,600);
c_rate_PTheta->Divide(2,1);
c_rate_PTheta->cd(1);
gPad->SetLogz();
gPad->SetGrid();
hrate_PTheta_gen->Draw("colz");
c_rate_PTheta->cd(2);
gPad->SetLogz();
gPad->SetGrid();
hrate_PTheta_acc->Draw("colz");

TCanvas *c_rate_Q2x = new TCanvas("rate_Q2x","rate_Q2x",1800,600);
c_rate_Q2x->Divide(2,1);
c_rate_Q2x->cd(1);
gPad->SetLogz();
gPad->SetGrid();
// hrate_Q2x_gen->SetAxisRange(1,15,"Y");
hrate_Q2x_gen->Draw("colz");
c_rate_Q2x->cd(2);
gPad->SetLogz();
gPad->SetGrid();
// hrate_Q2x_acc->SetAxisRange(1,15,"Y");
hrate_Q2x_acc->Draw("colz");

hacceptance_P->Divide(hrate_P_acc,hrate_P_gen);
hacceptance_Theta->Divide(hrate_Theta_acc,hrate_Theta_gen);
hacceptance_x->Divide(hrate_x_acc,hrate_x_gen);
hacceptance_Q2->Divide(hrate_Q2_acc,hrate_Q2_gen);
hacceptance_PTheta->Divide(hrate_PTheta_acc,hrate_PTheta_gen);
hacceptance_Q2x->Divide(hrate_Q2x_acc,hrate_Q2x_gen);

TCanvas *c_acceptance_eDIS_1D = new TCanvas("acceptance_eDIS_1D","acceptance_eDIS_1D",1800,900);
c_acceptance_eDIS_1D->Divide(2,2);
c_acceptance_eDIS_1D->cd(1);
gPad->SetGrid();
hacceptance_P->SetMinimum(0);
hacceptance_P->SetMaximum(1);
hacceptance_P->Draw();
c_acceptance_eDIS_1D->cd(2);
gPad->SetGrid();
hacceptance_Theta->SetMinimum(0);
hacceptance_Theta->SetMaximum(1);
hacceptance_Theta->Draw();
c_acceptance_eDIS_1D->cd(3);
gPad->SetGrid();
hacceptance_x->SetMinimum(0);
hacceptance_x->SetMaximum(1);
hacceptance_x->Draw();
c_acceptance_eDIS_1D->cd(4);
gPad->SetGrid();
hacceptance_Q2->SetMinimum(0);
hacceptance_Q2->SetMaximum(1);
hacceptance_Q2->Draw();
c_acceptance_eDIS_1D->SaveAs("acceptance_eDIS_1D.png");

TCanvas *c_acceptance_eDIS_2D = new TCanvas("acceptance_eDIS_2D","acceptance_eDIS_2D",1800,600);
c_acceptance_eDIS_2D->Divide(2,1);
c_acceptance_eDIS_2D->cd(1);
gPad->SetGrid();
hacceptance_PTheta->SetMinimum(0);
hacceptance_PTheta->SetMaximum(1);
hacceptance_PTheta->Draw("colz");
c_acceptance_eDIS_2D->cd(2);
gPad->SetGrid();
hacceptance_Q2x->SetMinimum(0);
hacceptance_Q2x->SetMaximum(1);
hacceptance_Q2x->Draw("colz");
c_acceptance_eDIS_2D->SaveAs("acceptance_eDIS_2D.png");

TCanvas *c_Apv_ApvErr_Q2x = new TCanvas("Apv_ApvErr_Q2x","Apv_ApvErr_Q2x",1800,1200);
c_Apv_ApvErr_Q2x->Divide(2,2);
c_Apv_ApvErr_Q2x->cd(1);
gPad->SetGrid();
hApv_Q2x_gen->SetMinimum(0);
hApv_Q2x_gen->SetMaximum(0.002);
hApv_Q2x_gen->Draw("colz");
c_Apv_ApvErr_Q2x->cd(2);
gPad->SetGrid();
hApvErr_Q2x_gen->SetMinimum(0);
hApvErr_Q2x_gen->SetMaximum(50000);
hApvErr_Q2x_gen->Draw("colz");
c_Apv_ApvErr_Q2x->cd(3);
gPad->SetGrid();
hApv_Q2x_acc->SetMinimum(0);
hApv_Q2x_acc->SetMaximum(0.002);
hApv_Q2x_acc->Draw("colz");
c_Apv_ApvErr_Q2x->cd(4);
gPad->SetGrid();
hApvErr_Q2x_acc->SetMinimum(0);
hApvErr_Q2x_acc->SetMaximum(5000);
hApvErr_Q2x_acc->Draw("colz");

TCanvas *c_Abeam_AbeamErr_Q2x = new TCanvas("Abeam_AbeamErr_Q2x","Abeam_AbeamErr_Q2x",1800,1200);
c_Abeam_AbeamErr_Q2x->Divide(2,2);
c_Abeam_AbeamErr_Q2x->cd(1);
gPad->SetGrid();
hAbeam_Q2x_gen->SetMinimum(0);
hAbeam_Q2x_gen->SetMaximum(0.002);
hAbeam_Q2x_gen->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(2);
gPad->SetGrid();
hAbeamErr_Q2x_gen->SetMinimum(0);
hAbeamErr_Q2x_gen->SetMaximum(50000);
hAbeamErr_Q2x_gen->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(3);
gPad->SetGrid();
hAbeam_Q2x_acc->SetMinimum(0);
hAbeam_Q2x_acc->SetMaximum(0.002);
hAbeam_Q2x_acc->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(4);
gPad->SetGrid();
hAbeamErr_Q2x_acc->SetMinimum(0);
hAbeamErr_Q2x_acc->SetMaximum(5000);
hAbeamErr_Q2x_acc->Draw("colz");


  for( int i = 1; i < hrate_Q2x_acc_bin->GetNbinsX(); i++ ){
    for( int j = 1; j < hrate_Q2x_acc_bin->GetNbinsY(); j++ ){
      double thisrate=hrate_Q2x_acc_bin->GetBinContent(i,j);
      if (thisrate==0) continue;      
      double Apv = 0.84e-4*hrate_Q2x_acc_bin->GetYaxis()->GetBinCenter(j);
//       cout << hrate_Q2x_acc_bin->GetYaxis()->GetBinCenter(j) << endl; 
      double ApvErr = 1./sqrt(thisrate*time)/Apv/pb*100;     
      hApvErr_Q2x_acc_bin->SetBinContent(i,j,ApvErr);
    }
  }
  
TCanvas *c_rate_ApvErr_Q2x_bin = new TCanvas("rate_ApvErr_Q2x_bin","rate_ApvErr_Q2x_bin",1800,600);
c_rate_ApvErr_Q2x_bin->Divide(2,1);
c_rate_ApvErr_Q2x_bin->cd(1);
gPad->SetGrid();
// hrate_Q2x_acc_bin->SetAxisRange(1,15,"Y");
hrate_Q2x_acc_bin->Draw("text");
c_rate_ApvErr_Q2x_bin->cd(2);
gPad->SetGrid();
// hApvErr_Q2x_acc_bin->SetMaximum(5);
// hApvErr_Q2x_acc_bin->SetAxisRange(1,15,"Y");
hApvErr_Q2x_acc_bin->Draw("text");

double AbeamErr[Nbin],ApvErr[Nbin];
    cout << "Apv_ave" << "\t" << "Abeam_ave" << "\t" << "rate" << "\t" << "ApvErr" << "\t" <<  "AbeamErr" << endl;
for(int k = 0; k < Nbin; k++){
//     double Apv = 0.84e-4*(bin[k][2]+bin[k][3])/2.;
    double Apv_ave = Apv_sum[k]/thatrate[k];
    ApvErr[k] = 1./sqrt(thatrate[k]*time)/Apv_ave/pb*100;   
    double Abeam_ave=Abeam_sum[k]/thatrate[k];
    AbeamErr[k] = 1./sqrt(thatrate[k]*time)/Abeam_ave/pb*100;      
    cout << Apv_ave << "\t" << Abeam_ave << "\t" << int(thatrate[k]) << "\t" << ApvErr[k] << "\t" <<  AbeamErr[k] << endl;
}

cout << "ApvErr" << endl;
for(int k = 0; k < Nbin; k++) cout << Form("%.03f",ApvErr[k]) << "\t";
cout << endl;
cout << "AbeamErr" << endl;
for(int k = 0; k < Nbin; k++) cout << Form("%.03f",AbeamErr[k]) << "\t";
cout << endl;

TCanvas *c_AbeamErr_Q2x_acc = new TCanvas("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",900,600);
gPad->SetGrid();
hAbeamErr_Q2x_acc->SetTitle("Asymmetry Uncertainty (%) with 120 days of 85% polarized 50uA electron beam on 40cm LD2 target;x;Q^{2} (GeV^{2})");
hAbeamErr_Q2x_acc->SetMarkerColor(kGreen);
hAbeamErr_Q2x_acc->Draw();

double x_cor[15]={0.250,0.325,0.375,0.375,0.425,0.425,0.475,0.475,0.525,0.525,0.575,0.575,0.635,0.635,0.735};
double Q2_cor[15]={4.2,5.0,5.5,6.3,6.0,7.0,6.5,7.8,7.1,8.5,7.6,9.1,8.2,9.8,9.8};    

// double x_cor[7]={0.250,0.325,0.375,0.425,0.475,0.525,0.575};
// double Q2_cor[7]={2.0,2.5,3.0,3.5,4.0,4.5,5.0};
for(int k = 0; k < Nbin; k++){
TMarker marker;
marker.SetMarkerStyle(20);
marker.SetMarkerColor(kRed);
marker.DrawMarker(x_cor[k],Q2_cor[k]);
TText *label = new TText(x_cor[k],Q2_cor[k],Form("%.02f",AbeamErr[k]));
label->SetTextColor(kBlack);
label->SetTextSize(0.03);
label->Draw();
}

c_AbeamErr_Q2x_acc->SaveAs("AbeamErr_Q2x_acc.png");

outputfile->Write();	
outputfile->Flush();


}
