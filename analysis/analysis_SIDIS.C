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

//the wiser curve
#include "ec_triggerfile/SIDIS_He3_JinHuang/SIDIS_He3_FAEC_electron_trigger_WiserJinHuang.C"
#include "ec_triggerfile/SIDIS_He3_JinHuang/SIDIS_He3_LAEC_electron_trigger_WiserJinHuang.C"
#include "ec_triggerfile/SIDIS_He3_JinHuang/SIDIS_He3_FAEC_hadron_trigger_WiserJinHuang.C"
// EC efficiency table inside

#include "analysis_tree_solid_lgc.C"
#include "analysis_tree_solid_hgc.C"
#include "analysis_tree_solid_spd.C"
#include "analysis_tree_solid_mrpc.C"
#include "analysis_tree_solid_ec.C"


// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 
// const double filenum=50; //file numbers while running GEMC in order to be correct for normalization
const int loop_time=1;   //electron to be 1, pion to be many times to take advantage of statistics, pion has low efficiency on EC
const int add_norm=1; // additional normalization factor

//distance between two ec cluster to have coincidance trigger
// const double threshold_distance=0;
// const double threshold_distance=0.1;
const double threshold_distance=32.5; 

const int with_background_on_lgc=0;     //0: no background on lgc, 1: yes background on lgc

//trigger threshold
// lgc 
const double PEthresh=2; //lgc pe shreshold for each pmt
const double PMTthresh=2; //lgc pmt shreshold, at least 2pmts are fired in each sector
//spd 
// const double trigger_threshold_spd_FA=0.35;         //in MeV
const double trigger_threshold_spd_FA=0.5;         //in MeV
const double trigger_threshold_spd_LA=1.5;         //in MeV
//mrpc threshold
const double mrpc_block_threshold_FA=5;  //how many layers are required to be fired

//occupancy threshold
// double occ_threshold_lgc=0,occ_threshold_hgc=0; //in N_p.e.
// double occ_threshold_spd_FA=trigger_threshold_spd_FA/5.,occ_threshold_spd_LA=trigger_threshold_spd_LA/5.; //in MeV
// double occ_threshold_ec_preshower=0.4,occ_threshold_ec_shower=6; //in MeV

double occ_threshold_lgc=1,occ_threshold_hgc=1; //in N_p.e.
// double occ_threshold_spd_FA=trigger_threshold_spd_FA/2.,occ_threshold_spd_LA=trigger_threshold_spd_LA/2.; //in MeV
double occ_threshold_spd_FA=0.5,occ_threshold_spd_LA=3.; 
double occ_threshold_ec_preshower=0.8,occ_threshold_ec_shower=12; //in MeV

//EC radius cut for physics result
double rout_cut_FA_phys=220;
double rin_cut_FA_phys=105;
double rout_cut_LA_phys=127;
double rin_cut_LA_phys=83; 
//EC radius cut for trigger
double rout_cut_FA_trigger=235;
double rin_cut_FA_trigger=105;
double rout_cut_LA_trigger=140; 
double rin_cut_LA_trigger=80;

bool Is_debug=false;

const double DEG=180./3.1415926;   //rad to degree

//#####################################################################################################################################################

int analysis_SIDIS(string inputfile_name,string runmode, bool Is_tellorig=false,string filetype=""){

// gStyle->SetOptStat(11111111);
  gStyle->SetOptStat(0);

double rout_cut_FA=0,rin_cut_FA=0,rout_cut_LA=0,rin_cut_LA=0;
if (runmode=="phys"){
 cout << "runmode: phys" << endl;  
 rout_cut_FA=rout_cut_FA_phys;
 rin_cut_FA=rin_cut_FA_phys;
 rout_cut_LA=rout_cut_LA_phys;
 rin_cut_LA=rin_cut_LA_phys;   
}else if(runmode=="trigger"){
 cout << "runmode: trigger" << endl;
 rout_cut_FA=rout_cut_FA_trigger;
 rin_cut_FA=rin_cut_FA_trigger;
 rout_cut_LA=rout_cut_LA_trigger;
 rin_cut_LA=rin_cut_LA_trigger;   
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

bool Is_SIDIS_He3=false,Is_SIDIS_NH3=false,Is_JPsi_LH2=false;
if(inputfile_name.find("SIDIS_He3",0) != string::npos) {
  Is_SIDIS_He3=true;
  cout << "SIDIS_He3 setup" << endl;  
}
else if(inputfile_name.find("SIDIS_NH3",0) != string::npos) {
  Is_SIDIS_NH3=true;
  cout << "SIDIS_NH3 setup" << endl;  
}
else if(inputfile_name.find("JPsi_LH2",0) != string::npos) {
  Is_JPsi_LH2=true;
  cout << "JPsi_LH2 setup" << endl;  
}
else {
    cout << "Not SIDIS_He3 or SIDIS_NH3 or JPsi_LH2 setup" << endl;    
    return 0;
}

TFile *file=new TFile(inputfile_name.c_str());

// 	TString background_inputfile_name="parametrized_lgc.root";      //h_pe is here	
// 	TFile *background_file=new TFile(background_inputfile_name);
// 	TH1F *h_pe=(TH1F*)background_file->Get("h_pe");

std::size_t found = inputfile_name.rfind("cache");
if (found!=std::string::npos)  inputfile_name.replace(found,5,"work");

char the_filename[200];
sprintf(the_filename, "%s",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());

char outputfile_name[200];
sprintf(outputfile_name, "%s_output.root",the_filename);
TFile *outputfile=new TFile(outputfile_name, "recreate");

// prepare for outputs
// define histograms, output txt files etc...

	TH1F *hhit_lgc=new TH1F("hit_lgc","hit,LGC;PMT;N_{p.e.} rate(kHz)",9,0,9);
	TH1F *hocc_lgc=new TH1F("occ_lgc","occupancy,LGC;PMT;event rate(kHz)",9,0,9);
	TH2F *hhit_lgc_2D=new TH2F("hit_lgc_2D","hit,LGC (rear view),N_{p.e.} rate(kHz);PMT_{#phi};PMT_{#theta}",3,0,3,3,0,3);
	TH2F *hocc_lgc_2D=new TH2F("occ_lgc_2D","occupancy,LGC (rear view),event rate(kHz);PMT_{#phi};PMT_{#theta}",3,0,3,3,0,3);

	TH1F *hhit_hgc=new TH1F("hit_hgc","hit,HGC;PMT;N_{p.e.} rate(kHz)",16,0,16);
	TH1F *hocc_hgc=new TH1F("occ_hgc","occupancy,HGC;PMT;event rate(kHz)",16,0,16);
	TH2F *hhit_hgc_2D=new TH2F("hit_hgc_2D","hit,HGC (rear view),N_{p.e.} rate(kHz);PMT_{#phi};PMT_{#theta}",4,0,4,4,0,4);
	TH2F *hocc_hgc_2D=new TH2F("occ_hgc_2D","occupancy,HGC (rear view),event rate(kHz);PMT_{#phi};PMT_{#theta}",4,0,4,4,0,4);

	TH1F *hhit_spd_FA=new TH1F("hit_spd_FA","hit,SPD FA;module;Edep rate (MeV/kHz)",240,0,240);
	TH1F *hocc_spd_FA=new TH1F("occ_spd_FA","occupancy,SPD FA;module;event rate (kHz)",240,0,240);	
	TH1F *hhit_spd_LA=new TH1F("hit_spd_LA","hit,SPD LA;module;Edep rate (MeV/kHz)",60,0,60);
	TH1F *hocc_spd_LA=new TH1F("occ_spd_LA","occupancy,SPD LA;module;event rate (kHz)",60,0,60);	
	
	TH1F *hhit_ec_preshower_FA=new TH1F("hit_ec_preshower_FA","hit,EC FA preshower;module;Edep rate (MeV/kHz)",2000,0,2000);
	TH1F *hocc_ec_preshower_FA=new TH1F("occ_ec_preshower_FA","occupancy,EC FA preshower;module;event rate (kHz)",2000,0,2000);	
	TH1F *hhit_ec_preshower_LA=new TH1F("hit_ec_preshower_LA","hit,EC LA preshower;module;Edep rate (MeV/kHz)",2000,0,2000);
	TH1F *hocc_ec_preshower_LA=new TH1F("occ_ec_preshower_LA","occupancy,EC LA preshower;module;event rate (kHz)",2000,0,2000);	
	TH1F *hhit_ec_shower_FA=new TH1F("hit_ec_shower_FA","hit,EC FA shower;module;Edep rate (MeV/kHz)",2000,0,2000);
	TH1F *hocc_ec_shower_FA=new TH1F("occ_ec_shower_FA","occupancy,EC FA shower;module;event rate (kHz)",2000,0,2000);	
	TH1F *hhit_ec_shower_LA=new TH1F("hit_ec_shower_LA","hit,EC LA shower;module;Edep rate (MeV/kHz)",2000,0,2000);
	TH1F *hocc_ec_shower_LA=new TH1F("occ_ec_shower_LA","occupancy,EC LA shower;module;event rate (kHz)",2000,0,2000);
	
	TH2F *hvertex_rz=new TH2F("hvertex_rz","hvertex_rz",1800,-400,500,600,0,300);
	
	TH1F *hangle_FAEC_FASPD=new TH1F("hangle_FAEC_FASPD","hangle_FAEC_FASPD",720,-360,360);
	TH1F *hangle_FAEC_LASPD=new TH1F("hangle_FAEC_LASPD","hangle_FAEC_LASPD",720,-360,360);	
	
	//LGC
	TH1F *h_n_trigger_sectors_LGC=new TH1F("h_n_trigger_sectors_LGC","number of triggered sectors",30,0,30);	
	//SPD
	TH1F *h_n_trigger_sectors_spd_FA=new TH1F("h_n_trigger_sectors_spd_FA","number of triggered sectors for spd at FA",240,0,240);
	TH1F *h_n_trigger_sectors_spd_LA=new TH1F("h_n_trigger_sectors_spd_LA","number of triggered sectors for spd at LA",240,0,240);	
	//MRPC
	TH1F *h_n_trigger_sectors_mrpc=new TH1F("h_n_trigger_sectors_mrpc","number of triggered sectors for mrpc",150,0,150);
	
	TH1F *h_counter_e_FA_EC=new TH1F("h_counter_e_FA_EC","e counter rate at forward angle", 10,0,10);
	TH1F *h_counter_e_FA_EC_lgc=new TH1F("h_counter_e_FA_EC_lgc","e counter rate at forward angle", 10,0,10);
	TH1F *h_counter_e_FA_EC_lgc_spd=new TH1F("h_counter_e_FA_EC_lgc_spd","e counter rate at forward angle", 10,0,10);	
	TH1F *h_counter_e_FA_EC_lgc_spd_mrpc=new TH1F("h_counter_e_FA_EC_lgc_spd_mrpc","e counter rate at forward angle", 10,0,10);
	
	TH1F *h_counter_e_LA_EC=new TH1F("h_counter_e_LA_EC","e counter rate at large angle", 10,0,10);
	TH1F *h_counter_e_LA_EC_spd=new TH1F("h_counter_e_LA_EC_spd","e counter rate at large angle", 10,0,10);

	TH1F *h_counter_h_FA_EC=new TH1F("h_counter_h_FA_EC","h counter rate on at forward angle", 10,0,10);
	TH1F *h_counter_h_FA_EC_spd=new TH1F("h_counter_h_FA_EC_spd","h counter rate on at forward angle", 10,0,10);
	TH1F *h_counter_h_FA_EC_spd_mrpc=new TH1F("h_counter_h_FA_EC_spd_mrpc","h counter rate on at forward angle", 10,0,10);
	
	// coin trigger rate with e forward angle and h forward angle
	TH1F *h_counter_e_FA_h_FA=new TH1F("h_counter_e_FA_h_FA","coincidence counter rate with e forward angle and h forward angle", 10,0,10);
	// coin counter rate with e large angle and h forward angle
	TH1F *h_counter_e_LA_h_FA=new TH1F("h_counter_e_LA_h_FA","coincidence counter rate with e large angle and h forward angle", 10,0,10);	

	TH1F *h_trigger_e_FA_EC=new TH1F("h_trigger_e_FA_EC","e trigger rate at forward angle", 60, 0, 300);
	TH1F *h_trigger_e_FA_EC_lgc=new TH1F("h_trigger_e_FA_EC_lgc","e trigger rate at forward angle", 60, 0, 300);
	TH1F *h_trigger_e_FA_EC_lgc_spd=new TH1F("h_trigger_e_FA_EC_lgc_spd","e trigger rate at forward angle", 60, 0, 300);	
	TH1F *h_trigger_e_FA_EC_lgc_spd_mrpc=new TH1F("h_trigger_e_FA_EC_lgc_spd_mrpc","e trigger rate at forward angle", 60, 0, 300);
	
	TH1F *h_trigger_e_LA_EC=new TH1F("h_trigger_e_LA_EC","e trigger rate at large angle", 60, 0, 300);
	TH1F *h_trigger_e_LA_EC_spd=new TH1F("h_trigger_e_LA_EC_spd","e trigger rate at large angle", 60, 0, 300);

	TH1F *h_trigger_h_FA_EC=new TH1F("h_trigger_h_FA_EC","h trigger rate on at forward angle", 60, 0, 300);
	TH1F *h_trigger_h_FA_EC_spd=new TH1F("h_trigger_h_FA_EC_spd","h trigger rate on at forward angle", 60, 0, 300);
	TH1F *h_trigger_h_FA_EC_spd_mrpc=new TH1F("h_trigger_h_FA_EC_spd_mrpc","h trigger rate on at forward angle", 60, 0, 300);
	
	// coin trigger rate with e forward angle and h forward angle
	TH1F *h_trigger_e_FA_h_FA=new TH1F("h_trigger_e_FA_h_FA","coincidence trigger rate with e forward angle and h forward angle", 60, 0, 300);
	// coin trigger rate with e large angle and h forward angle
	TH1F *h_trigger_e_LA_h_FA=new TH1F("h_trigger_e_LA_h_FA","coincidence trigger rate with e large angle and h forward angle", 60, 0, 300);
	
	TH2F *hgen_ThetaP=new TH2F("gen_ThetaP","generated events;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);  
	TH2F *hgen_ThetaPhi=new TH2F("gen_ThetaPhi","generated events;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);     
	TH2F *hgen_PhiP=new TH2F("gen_PhiP","generated events;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);	
	
	TH3F *hgen_ThetaPhiP=new TH3F("gen_ThetaPhiP","gen_ThetaPhiP",50,0,50,180,-180,180,55,0,11);   
	
	TH2F *hacceptance_ThetaP[2],*hacceptance_ThetaPhi[2],*hacceptance_PhiP[2];
	hacceptance_ThetaP[0]=new TH2F("acceptance_ThetaP_FA","acceptance by FA;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);     
	hacceptance_ThetaP[1]=new TH2F("acceptance_ThetaP_LA","acceptance by LA;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);
	hacceptance_ThetaPhi[0]=new TH2F("acceptance_ThetaPhi_FA","acceptance by FA;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);     
	hacceptance_ThetaPhi[1]=new TH2F("acceptance_ThetaPhi_LA","acceptance by LA;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);
	hacceptance_PhiP[0]=new TH2F("acceptance_PhiP_FA","acceptance by FA;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);     
	hacceptance_PhiP[1]=new TH2F("acceptance_PhiP_LA","acceptance by LA;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);

	TH3F *hacceptance_ThetaPhiP[2];
	hacceptance_ThetaPhiP[0]=new TH3F("acceptance_ThetaPhiP_FA","acceptance by FA",50,0,50,180,-180,180,55,0,11);   
	hacceptance_ThetaPhiP[1]=new TH3F("acceptance_ThetaPhiP_LA","acceptance by LA",50,0,50,180,-180,180,55,0,11);
	
// 	const int n=15;
// 	char *detname[n]={"GEM 1","GEM 2","GEM 3","GEM 4","GEM 5","GEM 6","LGC","HGC","FASPD","LASPD","FAEC","LAEC","FAMRPC","FAMUON","LAMUON"};	
	const int n=12;
	char *detname[n]={"GEM 1","GEM 2","GEM 3","GEM 4","GEM 5","GEM 6","LGC","HGC","FASPD","LASPD","FAEC","LAEC"};		
	TH2F *hhit_xy[n],*hhit_PhiR[n];
	for(int i=0;i<n;i++){
	  char hstname[100];
	  sprintf(hstname,"hit_xy_%i",i);
	  hhit_xy[i]=new TH2F(hstname,detname[i],600,-300,300,600,-300,300);        
	  sprintf(hstname,"hit_PhiR_%i",i);
	  hhit_PhiR[i]=new TH2F(hstname,detname[i],360,-180,180,300,0,300);
	}
	
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

	//---lgc
	//information recorded by lgc
	TTree* tree_solid_lgc= (TTree*) file->Get("solid_lgc");
	setup_tree_solid_lgc(tree_solid_lgc);
	
	//---hgc
	//information recorded by hgc
	TTree* tree_solid_hgc= (TTree*) file->Get("solid_hgc");
	setup_tree_solid_hgc(tree_solid_hgc);	

	//---SPD
	//information recorded by SPD
	TTree* tree_solid_spd= (TTree*) file->Get("solid_spd");
	setup_tree_solid_spd(tree_solid_spd);

	//---MRPC
	//information recorded by MRPC
	TTree *tree_solid_mrpc = (TTree*) file->Get("solid_mrpc");
	setup_tree_solid_mrpc(tree_solid_mrpc);


	//---EC
	//information recorded by EC
	TTree *tree_solid_ec = (TTree*) file->Get("solid_ec");
	setup_tree_solid_ec(tree_solid_ec);

	TRandom3 rand;
	rand.SetSeed(0);
	
	long int N_events = (long int)tree_header->GetEntries();

	cout << "total number of events : " << N_events << endl;	

	//----------------------------
	//      loop trees
	//---------------------------
	for(int loop_id=1;loop_id<=loop_time;loop_id++){
		cout<<"loop.....  "<<loop_id<<endl;
	
	for(long int i=0;i<N_events;i++){	  
// 			cout<<"event " << i<<endl;
// 			cout<<i<<"\r";
// 			cout<<i<<"\n";	  
		
		//---
		//---header tree
		//---
		tree_header->GetEntry(i);
		double rate=var8->at(0);
		if (filemode=="BeamOnTargetEM" || filemode=="BeamOnTarget") {
		  if(Is_SIDIS_He3) rate=15e-6/1.6e-19/event_actual/loop_time*add_norm;
		  else if(Is_SIDIS_NH3) rate=100e-9/1.6e-19/event_actual/loop_time*add_norm;
		  else if(Is_JPsi_LH2) rate=3e-6/1.6e-19/event_actual/loop_time*add_norm; 	  
		  else {
		    cout << "Not SIDIS_He3 or SIDIS_NH3  or JPsi_LH2 setup" << endl;    
		    return 0;
		  }
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
		
		//check on GEM by flux
		bool Is_passGEM=true;		
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
		
		  if(Is_SIDIS_NH3){
		    //oxford ptarget field pass3 (old)
// 		    if (flux_tid->at(j)==1){		      
// 		      if ((detector_ID==1 && subdetector_ID==1) && ((-95<hit_phi && hit_phi<-75)||(75<hit_phi && hit_phi<95))) Is_passGEM=false;          
// 		      if ((detector_ID==1 && subdetector_ID==2) && ((-95<hit_phi && hit_phi<-75)||(75<hit_phi && hit_phi<95))) Is_passGEM=false;          
// 		      if ((detector_ID==1 && subdetector_ID==3) && ((-95<hit_phi && hit_phi<-75)||(75<hit_phi && hit_phi<95))) Is_passGEM=false;          
// 		      if ((detector_ID==1 && subdetector_ID==4) && ((-95<hit_phi && hit_phi<-75)||(75<hit_phi && hit_phi<95))) Is_passGEM=false;          
// 		      if ((detector_ID==1 && subdetector_ID==5) && ((-85<hit_phi && hit_phi<-55)||(70<hit_phi && hit_phi<90))) Is_passGEM=false;          
// 		      if ((detector_ID==1 && subdetector_ID==6) && ((-85<hit_phi && hit_phi<-55)||(70<hit_phi && hit_phi<90))) Is_passGEM=false;
// 		    }
		    
		    
		  }
		  
		}
		
		//check on EC and other by flux
		double hit_phi_FAEC=1000,hit_phi_FASPD=1000,hit_phi_LASPD=1000;

		int pass_EC_electron_forward=0;
		int pass_EC_electron_large=0;
		int pass_EC_hadron=0;
		
		int trigger_e_FA_EC_sec[100],trigger_e_LA_EC_sec[100],trigger_h_FA_EC_sec[100];
		int trigger_e_FA_EC_pid[100],trigger_e_LA_EC_pid[100],trigger_h_FA_EC_pid[100];
		double trigger_e_FA_EC_p[100],trigger_e_LA_EC_p[100],trigger_h_FA_EC_p[100];
		double trigger_e_FA_EC_x[100],trigger_e_LA_EC_x[100],trigger_h_FA_EC_x[100];
		double trigger_e_FA_EC_y[100],trigger_e_LA_EC_y[100],trigger_h_FA_EC_y[100];
		double trigger_e_FA_EC_r[100],trigger_e_LA_EC_r[100],trigger_h_FA_EC_r[100];
		double trigger_e_FA_EC_vx[100],trigger_e_LA_EC_vx[100],trigger_h_FA_EC_vx[100];
		double trigger_e_FA_EC_vy[100],trigger_e_LA_EC_vy[100],trigger_h_FA_EC_vy[100];		
		double trigger_e_FA_EC_vr[100],trigger_e_LA_EC_vr[100],trigger_h_FA_EC_vr[100];
		double trigger_e_FA_EC_vz[100],trigger_e_LA_EC_vz[100],trigger_h_FA_EC_vz[100];		
		
		int counter_e_FA_EC=0,counter_e_LA_EC=0,counter_h_FA_EC=0;

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
		  
// 		  if ((0<=hit_id && hit_id<=9) || hit_id==12){
		  if (0<=hit_id && hit_id<=9){		  
		    if(abs(int(flux_pid->at(j))) == 11)	{		    
		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate);
		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate);		  
		    }
		    else if (int(flux_pid->at(j))==22){		      
		      //assume 5% photon conversion to hits for detector other than EC
		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate*0.05);
		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate*0.05);	
		    }
		  }
		  else if (10<=hit_id && hit_id<=11){	      
		      hhit_xy[hit_id]->Fill(hit_x,hit_y,rate);
		      hhit_PhiR[hit_id]->Fill(hit_phi,hit_r,rate);		  		      
		  }
// 		  else cout << flux_id->at(j) << endl;
		  
		  if(hit_id==10 && flux_tid->at(j)==1) hit_phi_FAEC=hit_phi;
		  if(hit_id==8 && flux_tid->at(j)==1) hit_phi_FASPD=hit_phi;
		  if(hit_id==9 && flux_tid->at(j)==1) hit_phi_LASPD=hit_phi;
		  
// 		  if (0<=hit_id && hit_id<=11) hflux_hitxy[hit_id]->Fill(flux_avg_x->at(j)/10.,flux_avg_y->at(j)/10.);
	    //       else cout << "flux_id->at(j) " << flux_id->at(j) << endl;
		  
		  //check hit on EC and find sec_ec
		  if(hit_id==10){   //FAEC 
		    if (hit_r<rin_cut_FA || hit_r>rout_cut_FA) continue; //trigger cut on R

		    int sec_ec=0;
		    int sec_shift=1.7;  // shift to match electron turning in field
		    if (hit_phi>=90+sec_shift) sec_ec=int((hit_phi-90-sec_shift)/12+1);
		    else sec_ec=int((hit_phi+360-90-sec_shift)/12+1);
// 	    	cout << " hit_phi " << hit_phi << " sec_ec " << sec_ec << endl;	
		    
		    //check trigger_e_FA_EC
		    double EC_efficiency=0;

		    if(Is_SIDIS_He3){
// 		    double hit_r_tmp;
// 		    if (105<=hit_r && hit_r<120) hit_r_tmp=100;     //trigger at 5GeV
// 		    else if(120<=hit_r && hit_r<135) hit_r_tmp=110; //trigger at 4GeV
// 		    else if(135<=hit_r && hit_r<149) hit_r_tmp=120; //trigger at 3GeV
// 		    else if(149<=hit_r && hit_r<163) hit_r_tmp=120; //trigger at 3GeV		    
// 		    else if(163<=hit_r && hit_r<177) hit_r_tmp=140; //trigger at 2GeV
// 		    else if(177<=hit_r && hit_r<191) hit_r_tmp=170; //trigger at 1GeV		    
// 		    else if(191<=hit_r && hit_r<235) hit_r_tmp=170; //trigger at 1GeV		       
// 		    else {hit_r_tmp=0; cout << "hit_r " << hit_r << " out of range"  << endl;}
		    
		    
// 		    double hit_r_tmp;
// 		    if (105<=hit_r && hit_r<115) hit_r_tmp=100;     //trigger at 5GeV
// 		    else if(115<=hit_r && hit_r<130) hit_r_tmp=110; //trigger at 4GeV
// 		    else if(130<=hit_r && hit_r<150) hit_r_tmp=120; //trigger at 3GeV
// 		    else if(150<=hit_r && hit_r<170) hit_r_tmp=120; //trigger at 3GeV		    
// 		    else if(170<=hit_r && hit_r<235) hit_r_tmp=120; //trigger at 3GeV		    
// 		    else {hit_r_tmp=0; cout << "hit_r " << hit_r << " out of range"  << endl;}
		    
		    //cut Q2>1.3		    
// 		    double hit_r_tmp;
// 		    if (105<=hit_r && hit_r<115) hit_r_tmp=100;     //trigger at 5GeV
// 		    else if(115<=hit_r && hit_r<130) hit_r_tmp=110; //trigger at 4GeV
// 		    else if(130<=hit_r && hit_r<150) hit_r_tmp=120; //trigger at 3GeV
// 		    else if(150<=hit_r && hit_r<170) hit_r_tmp=140; //trigger at 2GeV		    
// 		    else if(170<=hit_r && hit_r<235) hit_r_tmp=170; //trigger at 1GeV		    
// 		    else {hit_r_tmp=0; cout << "hit_r " << hit_r << " out of range"  << endl;}


		    //cut P>5GeV when theta<10deg, Q2>1.7GeV when theta>10deg		    
// 		    double hit_r_tmp;
// 		    if (105<=hit_r && hit_r<115) hit_r_tmp=100;     //trigger at 5GeV
// 		    else if(115<=hit_r && hit_r<130) hit_r_tmp=100; //trigger at 4GeV
// 		    else if(130<=hit_r && hit_r<150) hit_r_tmp=110; //trigger at 3GeV
// 		    else if(150<=hit_r && hit_r<170) hit_r_tmp=120; //trigger at 2GeV		    
// 		    else if(170<=hit_r && hit_r<235) hit_r_tmp=140; //trigger at 1GeV		    
// 		    else {hit_r_tmp=0; cout << "hit_r " << hit_r << " out of range"  << endl;}
		    
/*		    if(abs(int(flux_pid->at(j))) == 11)		      EC_efficiency=get_forward_electron_trigger_e_eff(hit_r_tmp, hit_p);		      
		    else if(int(flux_pid->at(j)) == 22)		      EC_efficiency=get_forward_electron_trigger_e_eff(hit_r_tmp, hit_p);	    
		    else if(abs(int(flux_pid->at(j))) == 211)		      EC_efficiency=get_forward_electron_trigger_pi_eff(hit_r_tmp, hit_p);		      
		    else if(abs(int(flux_pid->at(j))) == 321)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r_tmp, hit_p);		
		    else if(int(flux_pid->at(j)) == 130)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r_tmp, hit_p);   
		    else if(int(flux_pid->at(j)) == 2212)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r_tmp, hit_p);
		    else {EC_efficiency=0; 
		      if (Is_debug) cout << "unknown particle pid" << flux_pid->at(j) << endl;	      
		    }	*/	    
		    
			if(abs(int(flux_pid->at(j))) == 11)		      EC_efficiency=get_forward_electron_trigger_e_eff(hit_r, hit_p);		      
			else if(int(flux_pid->at(j)) == 22)		      EC_efficiency=get_forward_electron_trigger_e_eff(hit_r, hit_p);	    
			else if(abs(int(flux_pid->at(j))) == 211)		      EC_efficiency=get_forward_electron_trigger_pi_eff(hit_r, hit_p);		      
			else if(abs(int(flux_pid->at(j))) == 321)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r, hit_p);		
			else if(int(flux_pid->at(j)) == 130)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r, hit_p);   
			else if(int(flux_pid->at(j)) == 2212)		      EC_efficiency=0.5*get_forward_electron_trigger_pi_eff(hit_r, hit_p);
			else {EC_efficiency=0; 
			  if (Is_debug) cout << "unknown particle pid" << flux_pid->at(j) << endl;	      
			}
		    }
		    else if (Is_SIDIS_NH3){
			//EC sheet of flame cut		      
			if ((detector_ID==3 && subdetector_ID==1) && ((-92<hit_phi && hit_phi<-88 && hit_r/1e1<196)||(-78<hit_phi && hit_phi<-35 && hit_r/1e1<190)||(-35<hit_phi && hit_phi<-9 && hit_r/1e1<162)                                                  ||(23<hit_phi && hit_phi<39 && 131<hit_r/1e1 && hit_r/1e1<165)||(39<hit_phi && hit_phi<55 && hit_r/1e1<165)||(55<hit_phi && hit_phi<70 && hit_r/1e1<131))) EC_efficiency=0;
			else if {
			  // add NH3 FAEC trigger here
			  //if (trigger condition is good) EC_efficiency=1
			  
			}
			
		    }

		    //check to make sure eff is ok
		    if(isnan(EC_efficiency)) cout << "trigger_e_FA_EC " << EC_efficiency << " " << flux_pid->at(j) << endl;		    

		    if (rand.Uniform(0,1)<EC_efficiency){
		      bool Is_ok=false;
		      if (Is_tellorig){
			if (Is_singlefile){
			  if(Is_pi0){
			    if(abs(flux_pid->at(j))==11) Is_ok=true;
			  }
			  else {
			    if(flux_tid->at(j)==1) Is_ok=true;
			  }
			}
			else {
			  if(flux_tid->at(j)==1) Is_ok=true;
			}
		      }
		      else Is_ok=true;
			    
		      if(Is_ok){						
			pass_EC_electron_forward=1;
			counter_e_FA_EC++;
			trigger_e_FA_EC_sec[counter_e_FA_EC-1]=sec_ec;
			trigger_e_FA_EC_pid[counter_e_FA_EC-1]=flux_pid->at(j);		      
			trigger_e_FA_EC_p[counter_e_FA_EC-1]=hit_p;		      
			trigger_e_FA_EC_x[counter_e_FA_EC-1]=hit_x;
			trigger_e_FA_EC_y[counter_e_FA_EC-1]=hit_y;
			trigger_e_FA_EC_r[counter_e_FA_EC-1]=hit_r;		      		      
			trigger_e_FA_EC_vx[counter_e_FA_EC-1]=hit_vx;
			trigger_e_FA_EC_vy[counter_e_FA_EC-1]=hit_vy;
			trigger_e_FA_EC_vr[counter_e_FA_EC-1]=hit_vr;
			trigger_e_FA_EC_vz[counter_e_FA_EC-1]=hit_vz;			
		      }		      
		    }
		    
		    //check trigger_h_FA_EC
		    if(Is_SIDIS_He3){
		      
		    if(abs(int(flux_pid->at(j))) == 11){
		      double hit_Ekin=sqrt(hit_p*hit_p+0.511e-3*0.511e-3)-0.511e-3;
		      EC_efficiency=get_forward_hadron_trigger_e_eff(hit_Ekin);
		    }
		    else if(int(flux_pid->at(j)) == 22){
		      double hit_Ekin=hit_p;
		      EC_efficiency=get_forward_hadron_trigger_gamma_eff(hit_Ekin);	    
		    }
		    else if(abs(int(flux_pid->at(j))) == 211){ 		
		      double hit_Ekin=sqrt(hit_p*hit_p+0.14*0.14)-0.14;		      
		      EC_efficiency=get_forward_hadron_trigger_pion_eff(hit_Ekin);		      
		    }
		    else if(abs(int(flux_pid->at(j))) == 321){ 		
		      double hit_Ekin=sqrt(hit_p*hit_p+0.494*0.494)-0.494;		      
		      EC_efficiency=get_forward_hadron_trigger_pion_eff(hit_Ekin);		      
		    }
		    else if(int(flux_pid->at(j)) == 130){ 		
		      double hit_Ekin=sqrt(hit_p*hit_p+0.498*0.498)-0.498;		      
		      EC_efficiency=get_forward_hadron_trigger_pion_eff(hit_Ekin);		      
		    }		    
		    else if(int(flux_pid->at(j)) == 2212){
		      double hit_Ekin=sqrt(hit_p*hit_p+0.938*0.938)-0.938;		       
		      EC_efficiency=get_forward_hadron_trigger_proton_eff(hit_Ekin);
		    }
		    else {EC_efficiency=0; 
		      if (Is_debug) cout << "unknown particle pid" << flux_pid->at(j) << endl;	      
		    }
		    }
		    
		    //check to make sure eff is ok
		    if(isnan(EC_efficiency)) cout << "trigger_h_FA_EC " << EC_efficiency << " " << flux_pid->at(j) << endl;		    
		    
		    if (rand.Uniform(0,1)<EC_efficiency){
		      bool Is_ok=false;
		      if (Is_tellorig){
			if (Is_singlefile){
			  if(Is_pi0){
			    if(abs(flux_pid->at(j))==11) Is_ok=true;
			  }
			  else {
			    if(flux_tid->at(j)==1) Is_ok=true;
			  }
			}
			else {
			  if(flux_tid->at(j)==2) Is_ok=true;
			}
		      }
		      else Is_ok=true;
			    
		      if(Is_ok){     
		      pass_EC_hadron=1;		      
		      counter_h_FA_EC++;
		      trigger_h_FA_EC_sec[counter_h_FA_EC-1]=sec_ec;
		      trigger_h_FA_EC_pid[counter_h_FA_EC-1]=flux_pid->at(j);		      
		      trigger_h_FA_EC_p[counter_h_FA_EC-1]=hit_p;		      		      
		      trigger_h_FA_EC_x[counter_h_FA_EC-1]=hit_x;
		      trigger_h_FA_EC_y[counter_h_FA_EC-1]=hit_y;		      
		      trigger_h_FA_EC_r[counter_h_FA_EC-1]=hit_r;
		      trigger_h_FA_EC_vx[counter_h_FA_EC-1]=hit_vx;
		      trigger_h_FA_EC_vy[counter_h_FA_EC-1]=hit_vy;		      
		      trigger_h_FA_EC_vr[counter_h_FA_EC-1]=hit_vr;	
		      trigger_h_FA_EC_vz[counter_h_FA_EC-1]=hit_vz;		      
		      }
		    }	
		    
		  } //end of FAEC
		  
		  if(hit_id==11){   //LAEC 

		    if (hit_r<rin_cut_LA || hit_r>rout_cut_LA) continue; //trigger cut on R

		    int sec_ec=0;
		    int sec_shift=0;  // shift to match electron turning in field
		    if (hit_phi>=90+sec_shift) sec_ec=int((hit_phi-90-sec_shift)/12+1);
		    else sec_ec=int((hit_phi+360-90-sec_shift)/12+1);
	    // 	cout << " hit_phi " << hit_phi << " sec_ec " << sec_ec << endl;	
		    
		    //check trigger_e_FA_EC
		    double EC_efficiency=0;
		    
		    if(Is_SIDIS_He3){
		      
			if(abs(int(flux_pid->at(j))) == 11)		      EC_efficiency=get_large_electron_trigger_e_eff(hit_r, hit_p);		      
			else if(int(flux_pid->at(j)) == 22)		      EC_efficiency=get_large_electron_trigger_e_eff(hit_r, hit_p);	    
			else if(abs(int(flux_pid->at(j))) == 211)		      EC_efficiency=get_large_electron_trigger_pi_eff(hit_r, hit_p);		      
			else if(abs(int(flux_pid->at(j))) == 321)		      EC_efficiency=0.5*get_large_electron_trigger_pi_eff(hit_r, hit_p);		      
			else if(int(flux_pid->at(j)) == 130)		      EC_efficiency=0.5*get_large_electron_trigger_pi_eff(hit_r, hit_p);		      
			else if(int(flux_pid->at(j)) == 2212)		      EC_efficiency=0.5*get_large_electron_trigger_pi_eff(hit_r, hit_p);
			else {EC_efficiency=0; 
			  if (Is_debug) cout << "unknown particle pid" << flux_pid->at(j) << endl;	      
			}
		    }		    
		    else if (Is_SIDIS_NH3){
			//EC sheet of flame cut
			if ((detector_ID==3 && subdetector_ID==2) && ((-92<hit_phi && hit_phi<-88)||(-81<hit_phi && hit_phi<-56 && hit_r/1e1<131)||(-56<hit_phi && hit_phi<-47 && 100<hit_r/1e1 && hit_r/1e1<131)                                               ||(53<hit_phi && hit_phi<63 && 97<hit_r/1e1 && hit_r/1e1<131)||(63<hit_phi && hit_phi<71 && hit_r/1e1<131)||(71<hit_phi && hit_phi<77 && hit_r/1e1<96))) EC_efficiency=0;
		      	else if {
			  // add NH3 LAEC trigger here
			  //if (trigger condition is good) EC_efficiency=1
			  
			}		    
		    }	    
		    
		    //check to make sure eff is ok
		    if(isnan(EC_efficiency)) cout << "trigger_e_LA_EC " << EC_efficiency << " " << flux_pid->at(j) << endl;				    
		    
		    if (rand.Uniform(0,1)<EC_efficiency){
		      bool Is_ok=false;		      
		      if (Is_tellorig){
			if (Is_singlefile){
			  if(Is_pi0){
			    if(abs(flux_pid->at(j))==11) Is_ok=true;
			  }
			  else {
			    if(flux_tid->at(j)==1) Is_ok=true;
			  }
			}
			else {
			  if(flux_tid->at(j)==1) Is_ok=true;
			}
		      }
		      else Is_ok=true;
		      
		      if(Is_ok){
		      pass_EC_electron_large=1;
		      counter_e_LA_EC++;
		      trigger_e_LA_EC_sec[counter_e_LA_EC-1]=sec_ec;
		      trigger_e_LA_EC_pid[counter_e_LA_EC-1]=flux_pid->at(j);		      
		      trigger_e_LA_EC_p[counter_e_LA_EC-1]=hit_p;		      		      
		      trigger_e_LA_EC_x[counter_e_LA_EC-1]=hit_x;
		      trigger_e_LA_EC_y[counter_e_LA_EC-1]=hit_y;		      
		      trigger_e_LA_EC_r[counter_e_LA_EC-1]=hit_r;
		      trigger_e_LA_EC_vx[counter_e_LA_EC-1]=hit_vx;
		      trigger_e_LA_EC_vy[counter_e_LA_EC-1]=hit_vy;		      
		      trigger_e_LA_EC_vr[counter_e_LA_EC-1]=hit_vr;
		      trigger_e_LA_EC_vz[counter_e_LA_EC-1]=hit_vz;		      
		      }
		    }
		  } // end of LAEC 
		    		
		}			

		if(Is_debug){
		if (counter_e_FA_EC==1 && counter_h_FA_EC==1 && counter_e_LA_EC==0) {}
		else if (counter_e_FA_EC==0 && counter_h_FA_EC==0 && counter_e_LA_EC==1) {}
		else if (counter_e_FA_EC==0 && counter_h_FA_EC==1 && counter_e_LA_EC==0) {}			
		else if (counter_e_FA_EC==0 && counter_h_FA_EC==0 && counter_e_LA_EC==0) {}		
		else cout << counter_e_FA_EC << " " << counter_h_FA_EC << " " << counter_e_LA_EC  << endl;
		}
		
		if(counter_e_FA_EC>0) hangle_FAEC_FASPD->Fill(hit_phi_FAEC-hit_phi_FASPD);
		if(counter_e_FA_EC>0) hangle_FAEC_LASPD->Fill(hit_phi_FAEC-hit_phi_LASPD);	
// 		hangle_FAEC_FASPD->Fill(hit_phi_FAEC-hit_phi_FASPD);

		//---------------------
		//--- ec
		//---------------------
		tree_solid_ec->GetEntry(i);

		double hit_ec_preshower_FA[2000]={0},hit_ec_preshower_LA[2000]={0};
		double hit_ec_shower_FA[2000]={0},hit_ec_shower_LA[2000]={0};				
		process_tree_solid_ec(tree_solid_ec,hit_ec_preshower_FA,hit_ec_preshower_LA,hit_ec_shower_FA,hit_ec_shower_LA);
				
		for(int index=0;index<2000;index++){
		  if(hit_ec_preshower_FA[index]>0) hhit_ec_preshower_FA->Fill(index,hit_ec_preshower_FA[index]*rate/1e3);
		  if(hit_ec_shower_FA[index]>0) hhit_ec_shower_FA->Fill(index,hit_ec_shower_FA[index]*rate/1e3);
		  if(hit_ec_preshower_FA[index]>occ_threshold_ec_preshower) hocc_ec_preshower_FA->Fill(index,rate/1e3);
		  if(hit_ec_shower_FA[index]>occ_threshold_ec_shower) hocc_ec_shower_FA->Fill(index,rate/1e3);
		}
		for(int index=0;index<2000;index++){
		  if(hit_ec_preshower_LA[index]>0) hhit_ec_preshower_LA->Fill(index,hit_ec_preshower_LA[index]*rate/1e3);
		  if(hit_ec_shower_LA[index]>0) hhit_ec_shower_LA->Fill(index,hit_ec_shower_LA[index]*rate/1e3);		    
		  if(hit_ec_preshower_LA[index]>occ_threshold_ec_preshower) hocc_ec_preshower_LA->Fill(index,rate/1e3);
		  if(hit_ec_shower_LA[index]>occ_threshold_ec_shower) hocc_ec_shower_LA->Fill(index,rate/1e3);
		}		
		
		
		//-----------------------	
		//--- lgc 
		//-----------------------
		tree_solid_lgc->GetEntry(i);

		double hit_lgc[270]={0};
		int trigger_lgc[30]={0};
		int ntrigsecs_lgc=0;
		
		process_tree_solid_lgc(tree_solid_lgc,hit_lgc,trigger_lgc,ntrigsecs_lgc,PMTthresh,PEthresh);

		for(int index=0;index<270;index++){
		      int pmt_lgc=index%9;
			int pmt_x=0,pmt_y=0;
			switch (pmt_lgc){
			  case 0:	pmt_x=0; pmt_y=2; break;
			  case 1:	pmt_x=1; pmt_y=2; break;
			  case 2:	pmt_x=2; pmt_y=2; break;
			  case 3:	pmt_x=0; pmt_y=1; break;
			  case 4:	pmt_x=1; pmt_y=1; break;
			  case 5:	pmt_x=2; pmt_y=1; break;
			  case 6:	pmt_x=0; pmt_y=0; break;
			  case 7:	pmt_x=1; pmt_y=0; break;
			  case 8:	pmt_x=2; pmt_y=0; break;			  
			  default:      break;      
			}				
		      
		      if(hit_lgc[index]>0){		      
			hhit_lgc->Fill(pmt_lgc,hit_lgc[index]*rate/1e3/30.);	    
			hhit_lgc_2D->Fill(pmt_x,pmt_y,hit_lgc[index]*rate/1e3/30.);
		      }
		      if(hit_lgc[index]>occ_threshold_lgc){
			hocc_lgc->Fill(pmt_lgc,rate/1e3/30.);
			hocc_lgc_2D->Fill(pmt_x,pmt_y,rate/1e3/30.);
		      }		      
		}
//---------------------------------------------------------------------------------------------------------
		//add in backgrounds based on parametrized lgc study	
// 			if(with_background_on_lgc){	
// 				int N_random_pe=(int)h_pe->GetRandom();
// 				if(N_random_pe!=0){
// 					for(int id_random_pe=0; id_random_pe<N_random_pe;id_random_pe++){
// 						sectorhits[rand.Integer(30)][rand.Integer(9)] += 1;
// 					}
// 				}
// 			
// 			}  //scater random electrons on pmts based on parametrized EM-performance

	
		int pass_lgc=0;	
		if(ntrigsecs_lgc){
			pass_lgc=1;
			//cout<<"passed lgc"<<endl;
		}else{
			pass_lgc=0;
		}		
		
		//-----------------------	
		//--- hgc 
		//-----------------------
		tree_solid_hgc->GetEntry(i);

		double hit_hgc[480]={0};

		process_tree_solid_hgc(tree_solid_hgc,hit_hgc);

		for(int index=0;index<480;index++){
		      int pmt_hgc=index%16;
		      int pmt_x=0,pmt_y=0;
		      switch (pmt_hgc){
			case 0:	pmt_x=0; pmt_y=3; break;
			case 1:	pmt_x=1; pmt_y=3; break;
			case 2:	pmt_x=2; pmt_y=3; break;
			case 3:	pmt_x=3; pmt_y=3; break;			  
			case 4:	pmt_x=0; pmt_y=2; break;
			case 5:	pmt_x=1; pmt_y=2; break;
			case 6:	pmt_x=2; pmt_y=2; break;
			case 7:	pmt_x=3; pmt_y=2; break;			  
			case 8:	pmt_x=0; pmt_y=1; break;
			case 9:	pmt_x=1; pmt_y=1; break;
			case 10:	pmt_x=2; pmt_y=1; break;
			case 11:	pmt_x=3; pmt_y=1; break;			  
			case 12:	pmt_x=0; pmt_y=0; break;
			case 13:	pmt_x=1; pmt_y=0; break;
			case 14:	pmt_x=2; pmt_y=0; break;
			case 15:	pmt_x=3; pmt_y=0; break;			  
			default:      break;      
		      }				      
		      
		      if(hit_hgc[index]>0){		      
			hhit_hgc->Fill(pmt_hgc,hit_hgc[index]*rate/1e3/30.);	    
			hhit_hgc_2D->Fill(pmt_x,pmt_y,hit_hgc[index]*rate/1e3/30.);
		      } 

		      if(hit_hgc[index]>occ_threshold_hgc){
			hocc_hgc->Fill(pmt_hgc,rate/1e3/30.);
			hocc_hgc_2D->Fill(pmt_x,pmt_y,rate/1e3/30.);
		      }		      
		}
		
		//-----------------------	
		//--- spd 
		//-----------------------
		tree_solid_spd->GetEntry(i);

		double hit_spd_FA[240]={0},hit_spd_LA[60]={0};		
// 		int trigger_spd_FA[60][4]={0},trigger_spd_LA[60]={0};
		int trigger_spd_FA[240]={0},trigger_spd_LA[60]={0};
		int ntrigsecs_spd_FA=0,ntrigsecs_spd_LA=0;					
		process_tree_solid_spd(tree_solid_spd,hit_spd_FA,hit_spd_LA,trigger_spd_FA,trigger_spd_LA,ntrigsecs_spd_FA,ntrigsecs_spd_LA,trigger_threshold_spd_FA,trigger_threshold_spd_LA);

		for(int index=0;index<240;index++){
		  if(hit_spd_FA[index]>0){		      
		    hhit_spd_FA->Fill(index,hit_spd_FA[index]*rate/1e3);	
		  } 
		  if(hit_spd_FA[index]>occ_threshold_spd_FA){
		    hocc_spd_FA->Fill(index,rate/1e3);
		  }			
		}
		
		for(int index=0;index<60;index++){
		  if(hit_spd_LA[index]>0){		      
		    hhit_spd_LA->Fill(index,hit_spd_LA[index]*rate/1e3);	
		  } 
		  if(hit_spd_LA[index]>occ_threshold_spd_LA){
		    hocc_spd_LA->Fill(index,rate/1e3);
		  }			
		}		
		
		int pass_spd_forward=0;		
		if(ntrigsecs_spd_FA){
			pass_spd_forward=1;
		}else{
			pass_spd_forward=0;
		}
		
		int pass_spd_large=0;		
		if(ntrigsecs_spd_LA){
			pass_spd_large=1;
		}else{
			pass_spd_large=0;
		}
		
		//---------------------
		//--- MRPC 
		//---------------------
		tree_solid_mrpc->GetEntry(i);
		
// 		int trigger_mrpc_FA[50][3]={0};		
		int trigger_mrpc_FA[150]={0};					
		int ntrigsecs_mrpc_FA=0;					
		process_tree_solid_mrpc_trigger(tree_solid_mrpc,trigger_mrpc_FA,ntrigsecs_mrpc_FA,mrpc_block_threshold_FA);

		int pass_mrpc=0;		
		if(ntrigsecs_mrpc_FA){
			pass_mrpc=1;
		}else{
			pass_mrpc=0;
		}
 		
		//---
		//---fill histograms based on trigger flag
		//---		
		//LGC
		if(pass_lgc){
			h_n_trigger_sectors_LGC->Fill(ntrigsecs_lgc,rate);
		}

		//spd
		if(pass_spd_forward){
			h_n_trigger_sectors_spd_FA->Fill(ntrigsecs_spd_FA,rate);
		}		
		if(pass_spd_large){
			h_n_trigger_sectors_spd_LA->Fill(ntrigsecs_spd_LA,rate);
		}
		
		//mrpc
		if(pass_mrpc){
			h_n_trigger_sectors_mrpc->Fill(ntrigsecs_mrpc_FA,rate);
		}				


		int i_e_FA_EC_good[100]={0},i_e_LA_EC_good[100]={0},i_h_FA_EC_good[100]={0};
		
		//get single trigger rate, get counter first, then fill hist with correct weight	
		int counter_e_FA_EC_lgc=0,counter_e_FA_EC_lgc_spd=0,counter_e_FA_EC_lgc_spd_mrpc=0;
		for(int i_e_FA_EC=0; i_e_FA_EC<counter_e_FA_EC; i_e_FA_EC++){		  

		    int this_sec=trigger_e_FA_EC_sec[i_e_FA_EC];
		    int last_sec=-1,next_sec=-1;
		    if (this_sec==1) {last_sec=30;next_sec=2;}
		    else if (this_sec==30) {last_sec=29;next_sec=1;}
		    else {last_sec=this_sec-1;next_sec=this_sec+1;}		    		  

		    if (trigger_lgc[last_sec-1]==1 || trigger_lgc[this_sec-1]==1 || trigger_lgc[next_sec-1]==1){
		    
			counter_e_FA_EC_lgc++;			      
				
			double hit_phi=atan2(trigger_e_FA_EC_y[i_e_FA_EC], trigger_e_FA_EC_x[i_e_FA_EC])*DEG;			
			double hit_r=trigger_e_FA_EC_r[i_e_FA_EC]; // in cm			
			double hit_vr=trigger_e_FA_EC_vr[i_e_FA_EC]; // in cm
			double hit_vz=trigger_e_FA_EC_vz[i_e_FA_EC]; // in cm		

			hvertex_rz->Fill(hit_vz,hit_vr);			
			
			int sector_spd=0,block_spd=0;
// 			if(find_id_spd_LA(hit_phi,hit_r,sector_spd)){			
			if(find_id_spd_FA(hit_phi,hit_r,sector_spd,block_spd)){			
// 			 if(trigger_spd_FA[sector_spd-1][block_spd-1]==1){
			 if(trigger_spd_FA[(sector_spd-1)*4+block_spd-1]==1){	
// 			 if(trigger_spd_FA[(sector_spd-1)*4+1-1]==1){				  
// 			  if(ntrigsecs_spd_FA>0){
			  //from FAEC hit, check +-60 deg on FASPD to see any trigger
/*			 bool Is_ok=false;
			 for(int index_sector_spd=sector_spd-3; index_sector_spd<=sector_spd+3; index_sector_spd++){
			    int check_sector_spd=0;
			    if(index_sector_spd<1) check_sector_spd=index_sector_spd+60;
			    else if (index_sector_spd>60) check_sector_spd=index_sector_spd-60;
			    else check_sector_spd=index_sector_spd;

// 			    if (trigger_spd_LA[(check_sector_spd-1)]==1) Is_ok=true;	    
			    if (trigger_spd_FA[(check_sector_spd-1)*4+1-1]==1) Is_ok=true;
			 }
			 if(Is_ok){*/				 
// 			    if (hit_vz<95) counter_e_FA_EC_lgc_spd++;
			    counter_e_FA_EC_lgc_spd++;			    
			   
			    int sector_mrpc=0,block_mrpc=0;
// 			    if(find_id_mrpc_FA(hit_phi,hit_r,sector_mrpc,block_mrpc)){
// 			      if(trigger_mrpc_FA[sector_mrpc-1][block_mrpc-1]==1){			

				i_e_FA_EC_good[counter_e_FA_EC_lgc_spd_mrpc]=i_e_FA_EC;			
				
				counter_e_FA_EC_lgc_spd_mrpc++;				
				
// 				cout <<"event " << i<< " counter_e_FA " <<  counter_e_FA_EC_lgc_spd_mrpc << "\t" << trigger_e_FA_EC_pid[i_e_FA_EC] << " " << trigger_e_FA_EC_p[i_e_FA_EC] << " " << trigger_e_FA_EC_sec[i_e_FA_EC] << " " << 	trigger_e_FA_EC_r[i_e_FA_EC] << endl;	
// 			      }
// 			    }				   
			 }
			}	      
		    }	
		}
		h_counter_e_FA_EC->Fill(counter_e_FA_EC);		
		h_counter_e_FA_EC_lgc->Fill(counter_e_FA_EC_lgc);		
		h_counter_e_FA_EC_lgc_spd->Fill(counter_e_FA_EC_lgc_spd);			
		h_counter_e_FA_EC_lgc_spd_mrpc->Fill(counter_e_FA_EC_lgc_spd_mrpc);		
		for(int i_e_FA_EC=0; i_e_FA_EC<counter_e_FA_EC; i_e_FA_EC++){		  

		    h_trigger_e_FA_EC->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate/counter_e_FA_EC);	
// 		    h_trigger_e_FA_EC->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate); 
		    
		    int this_sec=trigger_e_FA_EC_sec[i_e_FA_EC];
		    int last_sec=-1,next_sec=-1;
		    if (this_sec==1) {last_sec=30;next_sec=2;}
		    else if (this_sec==30) {last_sec=29;next_sec=1;}
		    else {last_sec=this_sec-1;next_sec=this_sec+1;}		    		      

		    if (trigger_lgc[last_sec-1]==1 || trigger_lgc[this_sec-1]==1 || trigger_lgc[next_sec-1]==1){

			h_trigger_e_FA_EC_lgc->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate/counter_e_FA_EC_lgc);		      
// 			h_trigger_e_FA_EC_lgc->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate);		      		      
			hacceptance_ThetaP[0]->Fill(theta_gen,p_gen/1e3,rate/counter_e_FA_EC_lgc);		
			hacceptance_ThetaPhi[0]->Fill(theta_gen,phi_gen,rate/counter_e_FA_EC_lgc);			
			hacceptance_PhiP[0]->Fill(phi_gen,p_gen/1e3,rate/counter_e_FA_EC_lgc);
			hacceptance_ThetaPhiP[0]->Fill(theta_gen,phi_gen,p_gen/1e3,rate/counter_e_FA_EC_lgc);

			double hit_phi=atan2(trigger_e_FA_EC_y[i_e_FA_EC], trigger_e_FA_EC_x[i_e_FA_EC])*DEG;			
			double hit_r=trigger_e_FA_EC_r[i_e_FA_EC]; // in cm
			double hit_vr=trigger_e_FA_EC_vr[i_e_FA_EC]; // in cm
			double hit_vz=trigger_e_FA_EC_vz[i_e_FA_EC]; // in cm		
			
			int sector_spd=0,block_spd=0;
// 			if(find_id_spd_LA(hit_phi,hit_r,sector_spd)){			
			if(find_id_spd_FA(hit_phi,hit_r,sector_spd,block_spd)){
// 			 if(trigger_spd_FA[sector_spd-1][block_spd-1]==1){			   
			 if(trigger_spd_FA[(sector_spd-1)*4+block_spd-1]==1){			 
// 			 if(trigger_spd_FA[(sector_spd-1)*4+1-1]==1){				  	
// 			  if(ntrigsecs_spd_FA>0){			  
			  //from FAEC hit, check +-90 deg on FASPD to see any trigger
/*			 bool Is_ok=false;
			 for(int index_sector_spd=sector_spd-3; index_sector_spd<=sector_spd+3; index_sector_spd++){
			    int check_sector_spd=0;
			    if(index_sector_spd<1) check_sector_spd=index_sector_spd+60;
			    else if (index_sector_spd>60) check_sector_spd=index_sector_spd-60;
			    else check_sector_spd=index_sector_spd;

// 			    if (trigger_spd_LA[(check_sector_spd-1)]==1) Is_ok=true;	    
			    if (trigger_spd_FA[(check_sector_spd-1)*4+1-1]==1) Is_ok=true;
			 }			
			 if(Is_ok){*/				 
// 			    if (hit_vz<95) h_trigger_e_FA_EC_lgc_spd->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate/counter_e_FA_EC_lgc_spd);	
			    h_trigger_e_FA_EC_lgc_spd->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate/counter_e_FA_EC_lgc_spd);	
// 			    h_trigger_e_FA_EC_lgc_spd->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate);	
			    
			    int sector_mrpc=0,block_mrpc=0;
// 			    if(find_id_mrpc_FA(hit_phi,hit_r,sector_mrpc,block_mrpc)){
// 			      if(trigger_mrpc_FA[sector_mrpc-1][block_mrpc-1]==1){			   							
				h_trigger_e_FA_EC_lgc_spd_mrpc->Fill(trigger_e_FA_EC_r[i_e_FA_EC], rate/counter_e_FA_EC_lgc_spd_mrpc);	
				
// 				hacceptance_ThetaP[0]->Fill(theta_gen,p_gen/1e3,rate/counter_e_FA_EC_lgc_spd_mrpc);
				
// 			      }
// 			    }				   
			 }
			}	      
		    }	
		}		

		int counter_e_LA_EC_spd=0;
		for(int i_e_LA_EC=0; i_e_LA_EC<counter_e_LA_EC; i_e_LA_EC++){
		  
		    double hit_phi=atan2(trigger_e_LA_EC_y[i_e_LA_EC],trigger_e_LA_EC_x[i_e_LA_EC])*DEG;			
		    double hit_r=trigger_e_LA_EC_r[i_e_LA_EC]; // in cm
		    
		    int sector_spd=0;
		    if(find_id_spd_LA(hit_phi,hit_r,sector_spd)){
		      if(trigger_spd_LA[sector_spd-1]==1){			   

			    i_e_LA_EC_good[counter_e_LA_EC_spd]=i_e_LA_EC;
			    counter_e_LA_EC_spd++;				
			    
// 			    cout << "event " << i<< " counter_e_LA " <<  counter_e_LA_EC_spd << "\t" << trigger_e_LA_EC_pid[i_e_LA_EC] << " " << trigger_e_LA_EC_p[i_e_LA_EC] << " " << trigger_e_LA_EC_sec[i_e_LA_EC] << " " << 	trigger_e_LA_EC_r[i_e_LA_EC] << endl;			   
		      }
		    }	    	  
		}
		h_counter_e_LA_EC->Fill(counter_e_LA_EC);				
		h_counter_e_LA_EC_spd->Fill(counter_e_LA_EC_spd);
		for(int i_e_LA_EC=0; i_e_LA_EC<counter_e_LA_EC; i_e_LA_EC++){

		    h_trigger_e_LA_EC->Fill(trigger_e_LA_EC_r[i_e_LA_EC],rate/counter_e_LA_EC);	
		    
		    double hit_phi=atan2(trigger_e_LA_EC_y[i_e_LA_EC], trigger_e_LA_EC_x[i_e_LA_EC])*DEG;			
		    double hit_r=trigger_e_LA_EC_r[i_e_LA_EC]; // in cm
		    
		    int sector_spd=0;
		    if(find_id_spd_LA(hit_phi,hit_r,sector_spd)){
		      if(trigger_spd_LA[sector_spd-1]==1){			   
										    
			    h_trigger_e_LA_EC_spd->Fill(trigger_e_LA_EC_r[i_e_LA_EC], rate/counter_e_LA_EC_spd);
			    
			    hacceptance_ThetaP[1]->Fill(theta_gen,p_gen/1e3,rate/counter_e_LA_EC_spd);             
			    hacceptance_ThetaPhi[1]->Fill(theta_gen,phi_gen,rate/counter_e_LA_EC_spd);			
			    hacceptance_PhiP[1]->Fill(phi_gen,p_gen/1e3,rate/counter_e_LA_EC_spd);
			    hacceptance_ThetaPhiP[1]->Fill(theta_gen,phi_gen,p_gen/1e3,rate/counter_e_LA_EC_spd);     				    
		      }
		    }	      		  
		}		
		
		int counter_h_FA_EC_spd=0, counter_h_FA_EC_spd_mrpc=0;
		for(int i_h_FA_EC=0; i_h_FA_EC<counter_h_FA_EC; i_h_FA_EC++){
		  
			double hit_phi=atan2(trigger_h_FA_EC_y[i_h_FA_EC], trigger_h_FA_EC_x[i_h_FA_EC])*DEG;			
			double hit_r=trigger_h_FA_EC_r[i_h_FA_EC]; // in cm
			
			int sector_spd=0,block_spd=0;
			if(find_id_spd_FA(hit_phi,hit_r,sector_spd,block_spd)){

// 			 if(trigger_spd_FA[sector_spd-1][block_spd-1]==1){
			 if(trigger_spd_FA[(sector_spd-1)*4+block_spd-1]==1){			   
			  //from FAEC hit, check +-60 deg on FASPD to see any trigger
// 			 bool Is_ok=false;
// 			 for(int index_sector_spd=sector_spd-10; index_sector_spd<=sector_spd+10; index_sector_spd++){
// 			    int check_sector_spd=0;
// 			    if(index_sector_spd<1) check_sector_spd=index_sector_spd+60;
// 			    else if (index_sector_spd>60) check_sector_spd=index_sector_spd-60;
// 			    else check_sector_spd=index_sector_spd;
// 
// 			    if (trigger_spd_FA[(check_sector_spd-1)*4+1-1]==1) Is_ok=true;
// 			 }
// 			 if(Is_ok){
			    counter_h_FA_EC_spd++;			   
			   
			    int sector_mrpc=0,block_mrpc=0;
// 			    if(find_id_mrpc_FA(hit_phi,hit_r,sector_mrpc,block_mrpc)){
// 			      if(trigger_mrpc_FA[sector_mrpc-1][block_mrpc-1]==1){		   					
				i_h_FA_EC_good[counter_h_FA_EC_spd_mrpc]=i_h_FA_EC;
				
				counter_h_FA_EC_spd_mrpc++;
			
// 				cout << "event " << i<< " counter_h_FA " << counter_h_FA_EC_spd_mrpc << "\t" << trigger_h_FA_EC_pid[i_h_FA_EC] << " " << trigger_h_FA_EC_p[i_h_FA_EC] << " " << trigger_h_FA_EC_sec[i_h_FA_EC] << " " << 	trigger_h_FA_EC_r[i_h_FA_EC] << endl;	
// 			      }
// 			    }
			 }
			}			  
		}
		h_counter_h_FA_EC->Fill(counter_h_FA_EC);		
		h_counter_h_FA_EC_spd->Fill(counter_h_FA_EC_spd);			
		h_counter_h_FA_EC_spd_mrpc->Fill(counter_h_FA_EC_spd_mrpc);		
		for(int i_h_FA_EC=0; i_h_FA_EC<counter_h_FA_EC; i_h_FA_EC++){

			h_trigger_h_FA_EC->Fill(trigger_h_FA_EC_r[i_h_FA_EC], rate/counter_h_FA_EC);    
		    
			double hit_phi=atan2(trigger_h_FA_EC_y[i_h_FA_EC], trigger_h_FA_EC_x[i_h_FA_EC])*DEG;			
			double hit_r=trigger_h_FA_EC_r[i_h_FA_EC]; // in cm
			
			int sector_spd=0,block_spd=0;
			if(find_id_spd_FA(hit_phi,hit_r,sector_spd,block_spd)){
			  
// 			 if(trigger_spd_FA[sector_spd-1][block_spd-1]==1){			   
			 if(trigger_spd_FA[(sector_spd-1)*4+block_spd-1]==1){			   	
			  //from FAEC hit, check +-60 deg on FASPD to see any trigger
/*			 bool Is_ok=false;
			 for(int index_sector_spd=sector_spd-10; index_sector_spd<=sector_spd+10; index_sector_spd++){
			    int check_sector_spd=0;
			    if(index_sector_spd<1) check_sector_spd=index_sector_spd+60;
			    else if (index_sector_spd>60) check_sector_spd=index_sector_spd-60;
			    else check_sector_spd=index_sector_spd;

			    if (trigger_spd_FA[(check_sector_spd-1)*4+1-1]==1) Is_ok=true;
			 }
			 if(Is_ok){*/			  

			    h_trigger_h_FA_EC_spd->Fill(trigger_h_FA_EC_r[i_h_FA_EC], rate/counter_h_FA_EC_spd);				    
			   
			    int sector_mrpc=0,block_mrpc=0;
// 			    if(find_id_mrpc_FA(hit_phi,hit_r,sector_mrpc,block_mrpc)){
// 			      if(trigger_mrpc_FA[sector_mrpc-1][block_mrpc-1]==1){		   							
				h_trigger_h_FA_EC_spd_mrpc->Fill(trigger_h_FA_EC_r[i_h_FA_EC], rate/counter_h_FA_EC_spd_mrpc);	
// 			      }
// 			    }	
			 }
			}	  
		}	
		

		//=========== start get coin trigger from single trigger			
		int counter_e_FA_h_FA=0;
		for(int k=0; k<counter_e_FA_EC_lgc_spd_mrpc; k++){		
		  for(int j=0; j<counter_h_FA_EC_spd_mrpc; j++){
		    double dist=sqrt(pow(trigger_e_FA_EC_y[i_e_FA_EC_good[k]]-trigger_h_FA_EC_y[i_h_FA_EC_good[j]],2)+pow(trigger_e_FA_EC_x[i_e_FA_EC_good[k]]-trigger_h_FA_EC_x[i_h_FA_EC_good[j]],2));
		    if (dist>=threshold_distance){
		      counter_e_FA_h_FA++;
		      
// 		      cout << "event " << i<< " counter_e_FA_h_FA " << counter_e_FA_h_FA << "\t" << trigger_e_FA_EC_pid[i_e_FA_EC_good[k]] << " " << trigger_h_FA_EC_pid[i_h_FA_EC_good[j]] << " " <<  trigger_e_FA_EC_sec[i_e_FA_EC_good[k]] << " " << trigger_h_FA_EC_sec[i_h_FA_EC_good[j]] << " " <<		      trigger_e_FA_EC_p[i_e_FA_EC_good[k]] << " " << trigger_h_FA_EC_p[i_h_FA_EC_good[j]] << endl;			      		      
		    }
		  }
		}
		h_counter_e_FA_h_FA->Fill(counter_e_FA_h_FA);
		for(int k=0; k<counter_e_FA_EC_lgc_spd_mrpc; k++){		
		  for(int j=0; j<counter_h_FA_EC_spd_mrpc; j++){
		    double dist=sqrt(pow(trigger_e_FA_EC_y[i_e_FA_EC_good[k]]-trigger_h_FA_EC_y[i_h_FA_EC_good[j]],2)+pow(trigger_e_FA_EC_x[i_e_FA_EC_good[k]]-trigger_h_FA_EC_x[i_h_FA_EC_good[j]],2));
		    if (dist>=threshold_distance) h_trigger_e_FA_h_FA->Fill(trigger_e_FA_EC_r[i_e_FA_EC_good[k]],rate/counter_e_FA_h_FA);
		  }
		}			
				
		int counter_e_LA_h_FA=0;		
		for(int k=0; k<counter_e_LA_EC_spd; k++){		
		  for(int j=0; j<counter_h_FA_EC_spd_mrpc; j++){
		    counter_e_LA_h_FA++;
		    
// 		      cout << "event " << i<< " counter_e_LA_h_FA " << counter_e_LA_h_FA << "\t" << trigger_e_LA_EC_pid[i_e_LA_EC_good[k]] << " " << trigger_h_FA_EC_pid[i_h_FA_EC_good[j]] << " " << trigger_e_LA_EC_sec[i_e_LA_EC_good[k]] << " " << trigger_h_FA_EC_sec[i_h_FA_EC_good[j]] << " " << trigger_e_LA_EC_sec[i_e_LA_EC_good[k]] << " " << trigger_h_FA_EC_sec[i_h_FA_EC_good[j]] << endl;	 		      
		  }
		}
		h_counter_e_LA_h_FA->Fill(counter_e_LA_h_FA);
		for(int k=0; k<counter_e_LA_EC_spd; k++){		
		  for(int j=0; j<counter_h_FA_EC_spd_mrpc; j++){
		    h_trigger_e_LA_h_FA->Fill(trigger_e_LA_EC_r[i_e_LA_EC_good[k]],rate/counter_e_LA_h_FA);
		  }
		}		
		

	} //end event loop
	
	} //end loop time


/*
	TCanvas *can=new TCanvas("can","can");
	can->cd();

	h_flux_EC_lgc->Draw();
	cout<<"EC&lgc trigger rate:"<<h_flux_EC_lgc->Integral(1,60)<<endl;

*/
	//do outputs

TCanvas *c_flux_hit_xy = new TCanvas("flux_hit_xy","flux_hit_xy",1800,800);
c_flux_hit_xy->Divide(n/2,2);
for(int i=0;i<n;i++){
c_flux_hit_xy->cd(i+1);
gPad->SetLogz(1);
hhit_xy[i]->Draw("colz");
}

double cut1[12]={-95,-95,-95,-95,-85,-85,-85,-85,-75,-90,-75,-90};
double cut2[12]={-75,-75,-75,-75,-55,-55,-55,-40,-40,-60,-40,-60};
double cut3[12]={ 75, 75, 75, 75, 70, 70, 70, 65, 70, 60, 70, 60};
double cut4[12]={ 95, 95, 95, 95, 90, 90, 90, 90, 90, 95, 90, 95};
TCanvas *c_flux_hit_PhiR = new TCanvas("flux_hit_PhiR","flux_hit_PhiR",1800,800);
c_flux_hit_PhiR->Divide(n/2,2);
for(int i=0;i<n;i++){
c_flux_hit_PhiR->cd(i+1);
gPad->SetLogz(1);
hhit_PhiR[i]->Draw("colz");
TLine *l1=new TLine(cut1[i],0,cut1[i],195); l1->Draw();
TLine *l2=new TLine(cut2[i],0,cut2[i],195); l2->Draw();
TLine *l3=new TLine(cut3[i],0,cut3[i],195); l3->Draw();
TLine *l4=new TLine(cut4[i],0,cut4[i],195); l4->Draw();
}

TCanvas *c_hitocc_LGC = new TCanvas("hitocc_LGC","hitocc_LGC",1600,1000);
c_hitocc_LGC->Divide(2,2);
c_hitocc_LGC->cd(1);
hhit_lgc->Draw();
c_hitocc_LGC->cd(2);
hhit_lgc_2D->Draw("colz");
c_hitocc_LGC->cd(3);
hocc_lgc->Draw();
c_hitocc_LGC->cd(4);
hocc_lgc_2D->Draw("colz");

TCanvas *c_hitocc_HGC = new TCanvas("hitocc_HGC","hitocc_HGC",1600,1000);
c_hitocc_HGC->Divide(2,2);
c_hitocc_HGC->cd(1);
hhit_hgc->Draw();
c_hitocc_HGC->cd(2);
hhit_hgc_2D->Draw("colz");
c_hitocc_HGC->cd(3);
hocc_hgc->Draw();
c_hitocc_HGC->cd(4);
hocc_hgc_2D->Draw("colz");

TCanvas *c_hitocc_SPD = new TCanvas("hitocc_SPD","hitocc_SPD",1600,1000);
c_hitocc_SPD->Divide(2,2);
c_hitocc_SPD->cd(1);
hhit_spd_FA->Draw();
c_hitocc_SPD->cd(2);
hhit_spd_LA->Draw();
c_hitocc_SPD->cd(3);
hocc_spd_FA->Draw();
c_hitocc_SPD->cd(4);
hocc_spd_LA->Draw();

TCanvas *c_hitocc_EC = new TCanvas("hitocc_EC","hitocc_EC",1800,1000);
c_hitocc_EC->Divide(4,2);
c_hitocc_EC->cd(1);
hhit_ec_preshower_FA->Draw();
c_hitocc_EC->cd(2);
hhit_ec_shower_FA->Draw();
c_hitocc_EC->cd(3);
hhit_ec_preshower_LA->Draw();
c_hitocc_EC->cd(4);
hhit_ec_shower_LA->Draw();
c_hitocc_EC->cd(5);
hocc_ec_preshower_FA->Draw();
c_hitocc_EC->cd(6);
hocc_ec_shower_FA->Draw();
c_hitocc_EC->cd(7);
hocc_ec_preshower_LA->Draw();
c_hitocc_EC->cd(8);
hocc_ec_shower_LA->Draw();

TCanvas *c_gen = new TCanvas("gen","gen",1800,500);
c_gen->Divide(4,1);
c_gen->cd(1);
hgen_ThetaP->Draw("colz");
c_gen->cd(2);
hgen_ThetaPhi->Draw("colz");
c_gen->cd(3);
hgen_PhiP->Draw("colz");
c_gen->cd(4);
hgen_ThetaPhiP->Draw("colz");


hacceptance_ThetaP[0]->Divide(hacceptance_ThetaP[0],hgen_ThetaP);  
hacceptance_ThetaP[1]->Divide(hacceptance_ThetaP[1],hgen_ThetaP);  
hacceptance_ThetaPhi[0]->Divide(hacceptance_ThetaPhi[0],hgen_ThetaPhi);  
hacceptance_ThetaPhi[1]->Divide(hacceptance_ThetaPhi[1],hgen_ThetaPhi);  
hacceptance_PhiP[0]->Divide(hacceptance_PhiP[0],hgen_PhiP);  
hacceptance_PhiP[1]->Divide(hacceptance_PhiP[1],hgen_PhiP);  
hacceptance_ThetaPhiP[0]->Divide(hacceptance_ThetaPhiP[0],hgen_ThetaPhiP);  
hacceptance_ThetaPhiP[1]->Divide(hacceptance_ThetaPhiP[1],hgen_ThetaPhiP);  

// hacceptance_ThetaP[0]->SetMinimum(0);  
// hacceptance_ThetaP[0]->SetMaximum(1);  
// hacceptance_ThetaP[1]->SetMinimum(0);  
// hacceptance_ThetaP[1]->SetMaximum(1);  
// hacceptance_ThetaPhi[0]->SetMinimum(0);  
// hacceptance_ThetaPhi[0]->SetMaximum(1);    
// hacceptance_ThetaPhi[1]->SetMinimum(0);  
// hacceptance_ThetaPhi[1]->SetMaximum(1);    
// hacceptance_PhiP[0]->SetMinimum(0);  
// hacceptance_PhiP[0]->SetMaximum(1);  
// hacceptance_PhiP[1]->SetMinimum(0);  
// hacceptance_PhiP[1]->SetMaximum(1); 
// hacceptance_ThetaPhiP[0]->SetMinimum(0);  
// hacceptance_ThetaPhiP[0]->SetMaximum(1);
// hacceptance_ThetaPhiP[1]->SetMinimum(0);  
// hacceptance_ThetaPhiP[1]->SetMaximum(1);

TCanvas *c_acceptance_ThetaP = new TCanvas("acceptance_ThetaP","acceptance_ThetaP",1800,800);
c_acceptance_ThetaP->Divide(2,1);
c_acceptance_ThetaP->cd(1);
hacceptance_ThetaP[0]->Draw("colz");
c_acceptance_ThetaP->cd(2);  
hacceptance_ThetaP[1]->Draw("colz");

TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1800,800);
c_acceptance->Divide(4,2);
c_acceptance->cd(1);
hacceptance_ThetaP[0]->Draw("colz");
c_acceptance->cd(5);
hacceptance_ThetaP[1]->Draw("colz");
c_acceptance->cd(2);
hacceptance_ThetaPhi[0]->Draw("colz");
c_acceptance->cd(6);
hacceptance_ThetaPhi[1]->Draw("colz");
c_acceptance->cd(3);  
hacceptance_PhiP[0]->Draw("colz");
c_acceptance->cd(7);   
hacceptance_PhiP[1]->Draw("colz");
c_acceptance->cd(4);    
hacceptance_ThetaPhiP[0]->Draw("colz");
c_acceptance->cd(8);    
hacceptance_ThetaPhiP[1]->Draw("colz");

TH2F *hacceptance_ThetaP_overall=(TH2F*) hacceptance_ThetaP[0]->Clone();
hacceptance_ThetaP_overall->Add(hacceptance_ThetaP[1]);
hacceptance_ThetaP_overall->SetNameTitle("acceptance_ThetaP_overall","SIDIS electron acceptance & efficiency;vertex #theta (deg);vertex P (GeV)");
// hacceptance_ThetaP_overall->SetNameTitle("acceptance_ThetaP_overall","SIDIS electron efficiency;vertex #theta (deg);vertex P (GeV)");
hacceptance_ThetaP_overall->SetMinimum(0);  
hacceptance_ThetaP_overall->SetMaximum(1); 

TCanvas *c_acceptance_2D_both = new TCanvas("acceptance_2D_both","acceptance_2D_both",1200,1000);
c_acceptance_2D_both->Divide(1,1);
c_acceptance_2D_both->cd(1);
// gPad->SetLogy();
gPad->SetGrid();
hacceptance_ThetaP_overall->Draw("colz");
// c_acceptance_2D_both->SaveAs(Form("%s_%s",inputfile_name,"acceptance_2D_both.png"));

int NbinsX,NbinsY,NbinsZ;
NbinsX=hacceptance_ThetaP_overall->GetXaxis()->GetNbins();
NbinsY=hacceptance_ThetaP_overall->GetYaxis()->GetNbins();
double count_bincontent=0;
int count_bin=0;
for(int j=1;j<NbinsY;j++){
  for(int i=1;i<NbinsX;i++){
//         if (hacceptance_ThetaP_overall->GetBinContent(i,j)>1) cout << "what ? " <<   hacceptance_ThetaP_overall->GetBinContent(i,j) << endl;
    if (hacceptance_ThetaP_overall->GetBinContent(i,j)>0){
      count_bin++;
      count_bincontent += hacceptance_ThetaP_overall->GetBinContent(i,j);
    }
  }
}
// cout << "hacceptance_ThetaP_overall average is " << count_bincontent/count_bin << endl;

TCanvas *c_trigger_onedet = new TCanvas("trigger_onedet", "trigger_onedet",1400,900);
c_trigger_onedet->Divide(4,2);
c_trigger_onedet->cd(1);
h_trigger_e_FA_EC->Draw();
c_trigger_onedet->cd(2);
h_trigger_e_LA_EC->Draw();
c_trigger_onedet->cd(3);
h_trigger_h_FA_EC->Draw();
c_trigger_onedet->cd(4);
h_n_trigger_sectors_LGC->Draw();
c_trigger_onedet->cd(5);
h_n_trigger_sectors_spd_FA->Draw();
c_trigger_onedet->cd(6);
h_n_trigger_sectors_spd_LA->Draw();
c_trigger_onedet->cd(7);
h_n_trigger_sectors_mrpc->Draw();

cout<<"h_trigger_e_FA_EC in kHz: "<<h_trigger_e_FA_EC->Integral(1,60)/1e3<<endl;
cout<<"h_trigger_e_LA_EC in kHz: "<<h_trigger_e_LA_EC->Integral(1,60)/1e3<<endl;
cout<<"h_trigger_h_FA_EC in kHz: "<<h_trigger_h_FA_EC->Integral(1,60)/1e3<<endl;
cout<<"lgc in kHz: "<<h_n_trigger_sectors_LGC->Integral(1,30)/1e3<<endl;
cout<<"spd FA in kHz: "<<h_n_trigger_sectors_spd_FA->Integral(1,240)/1e3<<endl;
cout<<"spd LA in kHz: "<<h_n_trigger_sectors_spd_LA->Integral(1,240)/1e3<<endl;
cout<<"mrpc in kHz: "<<h_n_trigger_sectors_mrpc->Integral(1,240)/1e3<<endl;
// cout<<"EC lgc spd mrpc be fired in kHz: "<<h_flux_EC_lgc_spd_mrpc->Integral(1,60)<<endl;	

// cout<<"$$$$$$$$$$$$$$$   :"<<h_flux_EC_electron->Integral(1,60)<<"	"<<h_flux_EC_hadron->Integral(1,60)<<endl;

TCanvas *c_counter = new TCanvas("counter", "counter",1400,900);
c_counter->Divide(4,4);
c_counter->cd(1);
h_counter_e_FA_EC->Draw();
gPad->SetLogy();
c_counter->cd(2);
h_counter_e_FA_EC_lgc->Draw();
gPad->SetLogy();
c_counter->cd(3);
h_counter_e_FA_EC_lgc_spd->Draw();
gPad->SetLogy();
c_counter->cd(4);
h_counter_e_FA_EC_lgc_spd_mrpc->Draw();
gPad->SetLogy();
c_counter->cd(5);
h_counter_e_LA_EC->Draw();
gPad->SetLogy();
c_counter->cd(6);
h_counter_e_LA_EC_spd->Draw();
gPad->SetLogy();
c_counter->cd(9);
h_counter_h_FA_EC->Draw();
gPad->SetLogy();
c_counter->cd(10);
h_counter_h_FA_EC_spd->Draw();
gPad->SetLogy();
c_counter->cd(11);
h_counter_h_FA_EC_spd_mrpc->Draw();
gPad->SetLogy();
c_counter->cd(13);
h_counter_e_FA_h_FA->Draw();
gPad->SetLogy();
c_counter->cd(14);
h_counter_e_LA_h_FA->Draw();
gPad->SetLogy();



TCanvas *c_trigger = new TCanvas("trigger", "trigger",1400,900);
c_trigger->Divide(4,4);
c_trigger->cd(1);
h_trigger_e_FA_EC->Draw();
c_trigger->cd(2);
h_trigger_e_FA_EC_lgc->Draw();
c_trigger->cd(3);
h_trigger_e_FA_EC_lgc_spd->Draw();
c_trigger->cd(4);
h_trigger_e_FA_EC_lgc_spd_mrpc->Draw();
c_trigger->cd(5);
h_trigger_e_LA_EC->Draw();
c_trigger->cd(6);
h_trigger_e_LA_EC_spd->Draw();
c_trigger->cd(9);
h_trigger_h_FA_EC->Draw();
c_trigger->cd(10);
h_trigger_h_FA_EC_spd->Draw();
c_trigger->cd(11);
h_trigger_h_FA_EC_spd_mrpc->Draw();
c_trigger->cd(13);
h_trigger_e_FA_h_FA->Draw();
c_trigger->cd(14);
h_trigger_e_LA_h_FA->Draw();

   
cout<<"h_trigger_e_FA in kHz: "<<h_trigger_e_FA_EC->Integral(1,60)/1e3<<" "<<h_trigger_e_FA_EC_lgc->Integral(1,60)/1e3<<" "<<h_trigger_e_FA_EC_lgc_spd->Integral(1,60)/1e3<<" "<<h_trigger_e_FA_EC_lgc_spd_mrpc->Integral(1,60)/1e3<< endl;
cout<<"h_trigger_e_LA in kHz: "<<h_trigger_e_LA_EC->Integral(1,60)/1e3<<" "<<h_trigger_e_LA_EC_spd->Integral(1,60)/1e3<< endl;
cout<<"h_trigger_h_FA in kHz: "<<h_trigger_h_FA_EC->Integral(1,60)/1e3<<" "<<h_trigger_h_FA_EC_spd->Integral(1,60)/1e3<<" "<<h_trigger_h_FA_EC_spd_mrpc->Integral(1,60)/1e3<<" "<<endl;
cout<<"h_trigger_e_FA_h_FA in kHz: "<<h_trigger_e_FA_h_FA->Integral(1,60)/1e3<< endl; 
cout<<"h_trigger_e_LA_h_FA in kHz: "<<h_trigger_e_LA_h_FA->Integral(1,60)/1e3<< endl;

TCanvas *c_vertex = new TCanvas("vertex", "vertex",1400,900);
hvertex_rz->Draw("colz");

TCanvas *c_angle_FAEC_FASPD = new TCanvas("angle_FAEC_FASPD", "angle_FAEC_FASPD",1400,900);
hangle_FAEC_FASPD->Draw();

TCanvas *c_angle_FAEC_LASPD = new TCanvas("angle_FAEC_LASPD", "angle_FAEC_LASPD",1400,900);
hangle_FAEC_LASPD->Draw();

outputfile->Write();	
outputfile->Flush();


// 	h_flux_EC_electron->SetDirectory(output_file);
// 	output_file->Write();
/*

	ofstream OUTPUT_rate;
	
	//OUTPUT_rate.open("SIDIS_LGC_singles.txt");
	//OUTPUT_rate.open("SIDIS_EC_singles.txt");
	//OUTPUT_rate.open("SIDIS_spd_singles.txt");
	//OUTPUT_rate.open("SIDIS_mrpc_singles.txt");
	//OUTPUT_rate.open("SIDIS_EC_lgc_spd_mrpc.txt");
	
	OUTPUT_rate.open("SIDIS_truth.txt");
	
	if(!OUTPUT_rate){
		cout<<"can't open output file"<<endl;
		return 1;
	}
	
	//OUTPUT_rate<<"EC be fired only: "<<h_flux_EC->Integral(1,60)<<endl;
	//OUTPUT_rate<<"EC&lgc both fired:"<<h_flux_EC_lgc->Integral(1,60)<<endl;
	//OUTPUT_rate<<"EC but no lgc fired:"<<h_flux_EC_no_lgc->Integral(1,60)<<endl;
	//OUTPUT_rate<<"LGC be fired only: "<<h_n_trigger_sectors_LGC->Integral(1,30)<<endl;
	//OUTPUT_rate<<"SPD be fired only: "<<h_n_trigger_sectors_spd->Integral(1,240)<<endl;
	//OUTPUT_rate<<"mrpc be fired only: "<<h_n_trigger_sectors_mrpc->Integral(1,240)<<endl;
	OUTPUT_rate<<"SIDIS truth: "<<h_flux_EC->Integral(1,60)<<endl;

	TFile *output_file=new TFile("SIDIS_LGC_singles.root","RECREATE");
	//TFile *output_file=new TFile("SIDIS_EC_singles.root","RECREATE");
	//TFile *output_file=new TFile("SIDIS_spd_singles.root","RECREATE");
	//TFile *output_file=new TFile("SIDIS_mrpc_singles.root","RECREATE");
	//TFile *output_file=new TFile("SIDIS_EC_lgc_spd_mrpc.root","RECREATE");
	TFile *output_file=new TFile("SIDIS_truth.root","RECREATE");
	
	//h_flux_EC->SetDirectory(output_file);
	//h_flux_EC_lgc->SetDirectory(output_file);
	//h_flux_EC_no_lgc->SetDirectory(output_file);	
	//h_n_trigger_sectors_LGC->SetDirectory(output_file);
	//h_n_trigger_sectors_spd->SetDirectory(output_file);
	//h_n_trigger_sectors_mrpc->SetDirectory(output_file);
	//h_trigger_e_FA->SetDirectory(output_file);
	h_flux_EC->SetDirectory(output_file);
	
	output_file->Write();
*/	

}
