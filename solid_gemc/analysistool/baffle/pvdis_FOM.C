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
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>
#include <TMarker.h>

using namespace std;

void pvdis_FOM(string input_filename,bool Is_trig=false)
{
   gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  
const double DEG=180./3.1415926;


TFile *file_trig_cut[2];

//trig cut file for more1
// file_trig_cut[0]=new TFile("Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Real_Eklog_R_high_R0_ALL.rootTriggerSummaryhigh.root");
// file_trig_cut[1]=new TFile("Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Real_Eklog_R_low_R0_ALL.rootTriggerSummarylow.root");

//trig cut file for more1 block
file_trig_cut[0]=new TFile("Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_high_R0_ALL.rootTriggerSummaryhigh.root");
file_trig_cut[1]=new TFile("Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_low_R0_ALL.rootTriggerSummarylow.root");

char *gr_trig_cut_ele_name[2][5]={
"Graph_Electron_Eklog_R_high_R113",
"Graph_Electron_Eklog_R_high_R120",
"Graph_Electron_Eklog_R_high_R150",
"Graph_Electron_Eklog_R_high_R180",
"Graph_Electron_Eklog_R_high_R230",

"Graph_Electron_Eklog_R_low_R113",
"Graph_Electron_Eklog_R_low_R120",
"Graph_Electron_Eklog_R_low_R150",
"Graph_Electron_Eklog_R_low_R180",
"Graph_Electron_Eklog_R_low_R230"
};
char *gr_trig_cut_pi_name[2][5]={
"Graph_Pion_Eklog_R_high_R113",
"Graph_Pion_Eklog_R_high_R120",
"Graph_Pion_Eklog_R_high_R150",
"Graph_Pion_Eklog_R_high_R180",
"Graph_Pion_Eklog_R_high_R230",

"Graph_Pion_Eklog_R_low_R113",
"Graph_Pion_Eklog_R_low_R120",
"Graph_Pion_Eklog_R_low_R150",
"Graph_Pion_Eklog_R_low_R180",
"Graph_Pion_Eklog_R_low_R230"
};

double trig_cut_range_R[6]={110,116,124,165,205,265}; //113,120,150,180,230

double trig_cut[2][5][26][6];
TGraphErrors *gr_trig_cut_ele[2],*gr_trig_cut_pi[2];
for (int j=0;j<2;j++){
for (int i=0;i<5;i++){  
gr_trig_cut_ele[j]=(TGraphErrors*) file_trig_cut[j]->Get(gr_trig_cut_ele_name[j][i]);
gr_trig_cut_pi[j]=(TGraphErrors*) file_trig_cut[j]->Get(gr_trig_cut_pi_name[j][i]);
trig_cut[j][i][0][0]=trig_cut_range_R[i];
trig_cut[j][i][0][1]=trig_cut_range_R[i+1];
trig_cut[j][i][0][2]=0.5;
trig_cut[j][i][0][3]=1.;
trig_cut[j][i][0][4]=0.5*gr_trig_cut_ele[j]->GetY()[0];
trig_cut[j][i][0][5]=0.5*gr_trig_cut_pi[j]->GetY()[0];
// cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[0] << "\t" << gr_trig_cut_ele[j]->GetY()[0] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[0] << "\t" << gr_trig_cut_pi[j]->GetY()[0] << endl;
for (int k=0;k<25;k++){
trig_cut[j][i][k+1][0]=trig_cut_range_R[i];
trig_cut[j][i][k+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][k+1][2]=1.+k*0.2;
trig_cut[j][i][k+1][3]=1.+(k+1)*0.2;
trig_cut[j][i][k+1][4]=gr_trig_cut_ele[j]->GetY()[k];
trig_cut[j][i][k+1][5]=gr_trig_cut_pi[j]->GetY()[k];
// cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[k] << "\t" << gr_trig_cut_ele[j]->GetY()[k] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[k] << "\t" << gr_trig_cut_pi[j]->GetY()[k] << endl;
}
trig_cut[j][i][25][0]=trig_cut_range_R[i];
trig_cut[j][i][25][1]=trig_cut_range_R[i+1];
trig_cut[j][i][25][2]=6.;
trig_cut[j][i][25][3]=11.;
trig_cut[j][i][25][4]=gr_trig_cut_ele[j]->GetY()[24];
trig_cut[j][i][25][5]=gr_trig_cut_pi[j]->GetY()[24];
// cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[24] << "\t" << gr_trig_cut_ele[j]->GetY()[24] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[24] << "\t" << gr_trig_cut_pi[j]->GetY()[24] << endl;
}
}
  
// double trig_cut[4][10][6]={
// // 110,160,0.5,1.0,0.10,0.10,
// // 110,160,1.0,1.3,0.32,0.15,
// // 110,160,1.3,1.7,0.44,0.18,
// // 110,160,1.7,2.0,0.65,0.22,
// // 110,160,2.0,2.3,0.85,0.27,
// // 110,160,2.3,2.7,0.97,0.34,
// // 110,160,2.7,3.0,1.00,0.35,
// // 110,160,3.0,3.3,1.00,0.38,
// // 110,160,3.3,3.6,1.00,0.42,
// // 110,160,3.6,11.,1.00,0.47,
// 
// 110,160,0.5,1.0,0.10,0.02,
// 110,160,1.0,1.3,0.32,0.07,
// 110,160,1.3,1.7,0.44,0.08,
// 110,160,1.7,2.0,0.65,0.09,
// 110,160,2.0,2.3,0.85,0.13,
// 110,160,2.3,2.7,0.97,0.18,
// 110,160,2.7,3.0,1.00,0.19,
// 110,160,3.0,3.3,1.00,0.23,
// 110,160,3.3,3.6,1.00,0.28,
// 110,160,3.6,11.,1.00,0.31,
// 
// 160,205,0.5,1.0,0.01,0.02,
// 160,205,1.0,1.3,0.12,0.06,
// 160,205,1.3,1.7,0.25,0.10,
// 160,205,1.7,2.0,0.35,0.11,
// 160,205,2.0,2.3,0.62,0.13,
// 160,205,2.3,2.7,0.95,0.22,
// 160,205,2.7,3.0,1.00,0.25,
// 160,205,3.0,3.3,1.00,0.28,
// 160,205,3.3,3.6,1.00,0.32,
// 160,205,3.6,11.,1.00,0.38,
// 
// // 160,205,0.5,1.0,0.10,0.10,
// // 160,205,1.0,1.3,0.30,0.17,
// // 160,205,1.3,1.7,0.55,0.22,
// // 160,205,1.7,2.0,0.83,0.26,
// // 160,205,2.0,2.3,0.98,0.35,
// // 160,205,2.3,2.7,1.00,0.42,
// // 160,205,2.7,3.0,1.00,0.44,
// // 160,205,3.0,3.3,1.00,0.43,
// // 160,205,3.3,3.6,1.00,0.50,
// // 160,205,3.6,11.,1.00,0.52,
// 
// 205,235,0.5,1.0,0.05,0.01,
// 205,235,1.0,1.3,0.15,0.05,
// 205,235,1.3,1.7,0.31,0.08,
// 205,235,1.7,2.0,0.70,0.12,
// 205,235,2.0,2.3,0.98,0.18,
// 205,235,2.3,11.,1.00,0.27,
// 205,235,2.7,3.0,1.00,0.28,
// 205,235,3.0,3.3,1.00,0.33,
// 205,235,3.3,3.6,1.00,0.38,
// 205,235,3.6,11.,1.00,0.42,
// 
// 235,265,0.5,1.0,0.00,0.00,
// 235,265,1.0,1.3,0.00,0.00,
// 235,265,1.3,1.7,0.05,0.01,
// 235,265,1.7,2.0,0.50,0.03,
// 235,265,2.0,2.3,0.96,0.10,
// 235,265,2.3,11.,1.00,0.16,
// 235,265,2.7,3.0,1.00,0.22,
// 235,265,3.0,3.3,1.00,0.26,
// 235,265,3.3,3.6,1.00,0.32,
// 235,265,3.6,11.,1.00,0.35
// };

TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eDIS_1e6.root");
// TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_6.6GeV_eDIS_1e6.root");
  
//     if (file->IsZombie()) {
//        cout << "Error opening file" << input_filename << endl;
//        exit(-1);
//     }
//     else cout << "open file " << input_filename << endl;

double pf,theta,phi,Q2,x,W,rate,Abeam;
TTree *T = (TTree*) file_rate->Get("T");
T->SetBranchAddress("pf",&pf);
T->SetBranchAddress("theta",&theta);
T->SetBranchAddress("phi",&phi);
T->SetBranchAddress("Q2",&Q2);
T->SetBranchAddress("x",&x);
T->SetBranchAddress("W",&W);
T->SetBranchAddress("rate",&rate);
T->SetBranchAddress("Abeam",&Abeam);

// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.4_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.3_tweak1deg_output.root");
// TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.2_tweak2deg_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.1_tweak3deg_extra_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.0_tweak4deg_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.0_tweak4deg_new_output.root");
// 
// TH2F *hacceptance_negative=(TH2F*) acceptancefile_negative->Get("acceptance");

  TFile *file=new TFile(input_filename.c_str());
    if (file->IsZombie()) {
       cout << "Error opening file" << input_filename << endl;
//        continue;
       exit(-1);
    }
    else cout << "open file " << input_filename << endl;

TTree *Tgen = (TTree*) file->Get("genT");
Int_t gen_evn,gen_ngen;
Int_t gen_id_array[1000];
Int_t *gen_id=gen_id_array;
Float_t gen_px_array[1000],gen_py_array[1000],gen_pz_array[1000],gen_p_array[1000],gen_phi_array[1000],gen_theta_array[1000],gen_vx_array[1000],gen_vy_array[1000],gen_vz_array[1000];
Float_t *gen_px=gen_px_array,*gen_py=gen_py_array,*gen_pz=gen_pz_array,*gen_p=gen_p_array,*gen_phi=gen_phi_array,*gen_theta=gen_theta_array,*gen_vx=gen_vx_array,*gen_vy=gen_vy_array,*gen_vz=gen_vz_array;
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
Float_t flux_Edep_array[1000],flux_E_array[1000],flux_x_array[1000],flux_y_array[1000],flux_z_array[1000],flux_lx_array[1000],flux_ly_array[1000],flux_lz_array[1000],flux_t_array[1000],flux_px_array[1000],flux_py_array[1000],flux_pz_array[1000],flux_vx_array[1000],flux_vy_array[1000],flux_vz_array[1000],flux_mvx_array[1000],flux_mvy_array[1000],flux_mvz_array[1000];
Float_t *flux_Edep=flux_Edep_array,*flux_E=flux_E_array,*flux_x=flux_x_array,*flux_y=flux_y_array,*flux_z=flux_z_array,*flux_lx=flux_lx_array,*flux_ly=flux_ly_array,*flux_lz=flux_lz_array,*flux_t=flux_t_array,*flux_px=flux_px_array,*flux_py=flux_py_array,*flux_pz=flux_pz_array,*flux_vx=flux_vx_array,*flux_vy=flux_vy_array,*flux_vz=flux_vz_array,*flux_mvx=flux_mvx_array,*flux_mvy=flux_mvy_array,*flux_mvz=flux_mvz_array;
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

char output_filename[200];
if (Is_trig) sprintf(output_filename, "%s_trig_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
else sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

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


//   double rout_cut_FA = 250;  //target at 10,ec front at 320 back at 370 with angle 36
//   double rin_cut_FA = 0;  //as the detector edge
//   cout << " PVDIS rcut " << rin_cut_FA << " " << rout_cut_FA <<  endl;
  
Int_t nevent = (Int_t)Tflux->GetEntries();
cout << "nevent " << nevent << endl;

cout << "generator has entry " <<  T->GetEntries() << endl;
cout << "output has entry " << Tflux->GetEntries() << endl;;

double time = 120*3600*24;  //number of days in seconds
// double time = 60*3600*24;  //number of days in seconds
double pb = 0.85; 

//binning for 6.6GeV with x only  
// const int Nbin=7;
// double bin[Nbin][4]={
// 0.15,0.30,     0.0,14.0,
// 0.30,0.35,     0.0,14.0,
// 0.35,0.40,     0.0,14.0,
// 0.40,0.45,     0.0,14.0,
// 0.45,0.50,     0.0,14.0,
// 0.50,0.55,     0.0,14.0,
// 0.55,0.80,     0.0,14.0
// };      

//binning for x only  
const int Nbin=9;
double bin[Nbin][4]={
0.20,0.30,     0.0,14.0,
0.30,0.35,     0.0,14.0,
0.35,0.40,     0.0,14.0,
0.40,0.45,     0.0,14.0,
0.45,0.50,     0.0,14.0,
0.50,0.55,     0.0,14.0,
0.55,0.60,     0.0,14.0,
0.60,0.67,     0.0,14.0,
0.67,0.80,     0.0,14.0
};      
   
///binning for more1 block
// const int Nbin=15;
// double bin[15][4]={
// 0.20,0.30,     0.0,14.0,
// 0.30,0.35,     0.0,14.0,
// 0.35,0.40,     0.0, 5.8,
// 0.35,0.40,     5.8,14.0,
// 0.40,0.45,     0.0, 6.4,
// 0.40,0.45,     6.4,14.0,
// 0.45,0.50,     0.0, 7.0,
// 0.45,0.50,     7.0,14.0,
// 0.50,0.55,     0.0, 7.6,
// 0.50,0.55,     7.6,14.0,
// 0.55,0.60,     0.0, 8.2,
// 0.55,0.60,     8.2,14.0,
// 0.60,0.67,     0.0, 8.8,
// 0.60,0.67,     8.8,14.0,
// 0.67,0.80,     0.0,14.0
// };

///binning for SCALEMIN1.4MAX1.4
// const int Nbin=15;
// double bin[15][4]={
// 0.20,0.30,     0.0,14.0,
// 0.30,0.35,     0.0,14.0,
// 0.35,0.40,     0.0, 6.1,
// 0.35,0.40,     6.1,14.0,
// 0.40,0.45,     0.0, 6.7,
// 0.40,0.45,     6.7,14.0,
// 0.45,0.50,     0.0, 7.3,
// 0.45,0.50,     7.3,14.0,
// 0.50,0.55,     0.0, 7.9,
// 0.50,0.55,     7.9,14.0,
// 0.55,0.60,     0.0, 8.5,
// 0.55,0.60,     8.5,14.0,
// 0.60,0.67,     0.0, 9.1,
// 0.60,0.67,     9.1,14.0,
// 0.67,0.80,     0.0,14.0
// };

///binning in proposal      
// double bin[15][4]={
// 0.20,0.31,     3.0, 5.0,
// 0.31,0.35,     3.5, 6.5,
// 0.35,0.40,     4.5, 5.9,
// 0.35,0.40,     5.9, 7.5,
// 0.40,0.45,     5.0, 6.5,
// 0.40,0.45,     6.5, 8.5,
// 0.45,0.50,     5.0, 7.2,
// 0.45,0.50,     7.2,10.0,
// 0.50,0.55,     5.0, 7.7,
// 0.50,0.55,     7.7,10.0,
// 0.55,0.60,     5.0, 8.1,
// 0.55,0.60,     8.1,11.0,
// 0.60,0.67,     5.5, 8.7,
// 0.60,0.67,     8.7,11.0,
// 0.67,0.82,     7.0,12.0 
// };

// 	  cout << bin[1][0] << " "<< bin[1][1] << " " << bin[1][2] << " " << bin[1][3] << endl; 

double thatrate[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Abeam_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Apv_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

for (Int_t i=0;i<nevent;i++) {
//   for (Int_t i=0;i<10;i++) {
      cout << i << "\r";    
  T->GetEntry(i);
    
//   cout << W << " " << sqrt(0.938**2+2*0.938*(11-pf)-Q2) << endl;
  if (W<2) continue;
//     if (pf<2) continue;
  bool Is_pf=true;
    
//     cout << theta*DEG << " " << pf  << endl;
 
//     Tgen->GetEntry(i);  
//   for (Int_t j=0;j<gen_ngen;j++) {
//       cout <<  gen_evn << " " << gen_ngen << " " << *(gen_id+j) << " " << *(gen_px+j) << " " << *(gen_py+j) << " " << *(gen_pz+j) << " " << *(gen_p+j) << " " << *(gen_theta+j)  <<endl;
//       theta=*(gen_theta+j);
//       mom=*(gen_p+j)/1e3;
//   }
  
    double acc=0;
    double eff=0;
    Tflux->GetEntry(i+1);     //gemc_evio has bug output tree starting from index 1
    for (Int_t j=0;j<flux_nfluxhit;j++) {
//       if (flux_nfluxhit>1){
//             cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
//       }
      int detector_ID=*(flux_ID+j)/1000000;
      int subdetector_ID=(*(flux_ID+j)%1000000)/100000;
      int subsubdetector_ID=((*(flux_ID+j)%1000000)%100000)/10000;
  //     cout << Detector_ID << " " << SubDetector_ID << " "  << channel_ID << endl;
      if (detector_ID==3 && subdetector_ID==1 && subsubdetector_ID==1) {
//       if (detector_ID==1 && subdetector_ID==5 && subsubdetector_ID==1) {  
	
	double r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2))/10.;
	double p=sqrt(pow(*(flux_px+j),2)+pow(*(flux_py+j),2)+pow(*(flux_pz+j),2))/1e3;
	
	if (110 <= r && r < 250) {; //EC range cut
// 	if (115 <= r && r <= 228) {; //GEM range cut	
	acc=1;
//       cout << j << endl;
//       cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;

      double phi=fabs(atan((*(flux_x+j))/(*(flux_x+j)))/3.1416*180);
      if (*(flux_x+j) > 0 && *(flux_y+j) > 0) phi=phi;
      else if (*(flux_x+j) < 0 && *(flux_y+j) > 0) phi=180-phi;
      else if (*(flux_x+j) < 0 && *(flux_y+j) < 0) phi=180+phi;    
      else if (*(flux_x+j) > 0 && *(flux_y+j) < 0) phi=360-phi;
      else cout << " flux wrong? " << *(flux_x+j) << " " <<  *(flux_y+j) << endl; 
	
      int region_index;
      if (phi-int(phi/12)*12<6) region_index=0;
      else region_index=1;
	
	if(Is_trig){
	  for(int a=0;a<5;a++){      
	    for(int b=0;b<26;b++){
		if (trig_cut[region_index][a][b][0] <= r && r < trig_cut[region_index][a][b][1] && trig_cut[region_index][a][b][2] <= p && p < trig_cut[region_index][a][b][3]){	      
		  eff=trig_cut[region_index][a][b][4];
		}
	    }
	  }
	}
	else eff=1;
	
// 	cout << r << endl;
// 	if (pf<3 && 1100 < r && r < 1400) Is_pf=false;
// 	if (pf<2.5 && 1100 < r && r < 1400) Is_pf=false;	
// 	if (pf<2.5 && 1400 < r && r < 1700) Is_pf=false;
// 	if (pf<2 && 1700 < r && r < 2700) Is_pf=false;
	}
      }
      
    }
    
//      if(!Is_pf) continue;
  
  //   double acc=hacceptance_negative->GetBinContent(hacceptance_negative->FindBin(theta*DEG,pf)); 
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
      
}

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
if (Is_trig) c_acceptance_eDIS_1D->SaveAs("acceptance_eDIS_1D_trig.png");
else c_acceptance_eDIS_1D->SaveAs("acceptance_eDIS_1D.png");

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
if (Is_trig) c_acceptance_eDIS_2D->SaveAs("acceptance_eDIS_2D_trig.png");
else c_acceptance_eDIS_2D->SaveAs("acceptance_eDIS_2D.png");

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

if (Is_trig) c_AbeamErr_Q2x_acc->SaveAs("AbeamErr_Q2x_acc_trig.png");
else c_AbeamErr_Q2x_acc->SaveAs("AbeamErr_Q2x_acc.png");

outputfile->Write();
outputfile->Flush();

ifstream input("solid_LD2_120d_11GeV.sollund");
if (!input.good()) {cout << "can't open file " << endl; return;}

double a1,weight,a3,a4,a5,a6,a7,a8,a9,a10,a11;
double b1,b2,b3,b4,b5,b6,px,py,pz,E,b11,b12,b13,b14;
int evncounter=0;
while (!input.eof()){
  evncounter++;
//   cout << evncounter << "\n";      
  input >> a1 >> weight >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9 >> a10>> a11;
  input >> b1 >> b2 >> b3 >> b4 >> b5 >> b6 >> px >> py >> pz >> E >> b11 >> b12 >> b13 >> b14;  
//  if (evncounter<3) {
//      cout << a1 << "\t" << weight << "\t" << a3 << "\t" << a4 << "\t" << a5 << "\t" << a6 << "\t" << a7 << "\t" << a8 << "\t" << a9 << "\t" << a10 << "\t" << a11 << endl;
//      cout << b1 << "\t" << b2 << "\t" << b3 << "\t" << b4 << "\t" << b5 << "\t" << b6 << "\t" << px << "\t" << py << "\t" << pz << "\t" << E << "\t" << b11 << "\t" << b12 << "\t" << b13 << "\t" << b14 << endl;  
//      cout << acos(pz/sqrt(px*px+py*py+pz*pz))*DEG << endl;
//      cout << sqrt(px*px+py*py+pz*pz) << endl;      
//  }  
  if (0.938*0.938+2.*0.938*(11.-sqrt(px*px+py*py+pz*pz))-2.*11.*sqrt(px*px+py*py+pz*pz)*(1-pz/sqrt(px*px+py*py+pz*pz)) < 4) continue;
  hrate_PTheta_seamus_gen->Fill(acos(pz/sqrt(px*px+py*py+pz*pz))*DEG,sqrt(px*px+py*py+pz*pz),weight);
}
// cout << "evncounter " << evncounter << endl;

TCanvas *c_rate_PTheta_compare = new TCanvas("rate_PTheta_compare","rate_PTheta_compare",2200,1200);
c_rate_PTheta_compare->Divide(2,2);
c_rate_PTheta_compare->cd(1);
gPad->SetLogz();
hrate_PTheta_zwzhao_gen->Scale(1/1000.);
hrate_PTheta_zwzhao_gen->SetMinimum(1e-2);
hrate_PTheta_zwzhao_gen->SetMaximum(12);
hrate_PTheta_zwzhao_gen->Draw("colz text");
c_rate_PTheta_compare->cd(2);
gPad->SetLogz();
hrate_PTheta_zwzhao_acc->Scale(1/1000.);
hrate_PTheta_zwzhao_acc->SetMinimum(1e-2);
hrate_PTheta_zwzhao_acc->SetMaximum(12);
hrate_PTheta_zwzhao_acc->Draw("colz text");
c_rate_PTheta_compare->cd(3);
gPad->SetLogz();
hrate_PTheta_seamus_gen->Scale(1./1000.*1.21/120./24./3600.);
hrate_PTheta_seamus_gen->SetMinimum(1e-2);
hrate_PTheta_seamus_gen->SetMaximum(12);
hrate_PTheta_seamus_gen->Draw("colz text");
c_rate_PTheta_compare->cd(4);
gPad->SetLogz();
TH2F *hrate_PTheta_seamus_zwzhao_ratio_gen=(TH2F*) hrate_PTheta_seamus_gen->Clone();
hrate_PTheta_seamus_zwzhao_ratio_gen->Divide(hrate_PTheta_seamus_gen,hrate_PTheta_zwzhao_gen);
hrate_PTheta_seamus_zwzhao_ratio_gen->SetTitle("rate seamus/zwzhao ratio gen");
hrate_PTheta_seamus_zwzhao_ratio_gen->Draw("colz text");

}