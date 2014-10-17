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

///read hits from a txt file produced by roo2hit.C
void background(string input_filename,int Nevent){
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(111111);

gSystem->Load("./response/FastResponse_C.so");

const double DEG=180./3.1415926;

char output_filename[80];
sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

const int n=29; // number of detector
const int m=11; //number of particles

char *label[m]={"photon+electron+positron","photon","electron+positron","neutron","proton","pip","pim","Kp","Km","Kl","other"};

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

ifstream input(input_filename.c_str());
if (!input.good()) {cout << "can't open file " << endl; return;}

// double Nevent;
// if (input_filename.find(".",0) != string::npos){
//   Nevent=atoi(input_filename.substr(input_filename.find(".")-3,3).c_str());
// //   cout << input_filename.substr(input_filename.find(".",0)-3,3) << endl;
//     cout << Nevent << endl;
//   
// }
  
bool Is_PVDIS=false,Is_SIDIS_He3=false,Is_SIDIS_He3_window=false;  
double current;
double target_center;  //in mm
if (input_filename.find("PVDIS",0) != string::npos){
  Is_PVDIS=true;
  current=50e-6/1.6e-19;  //50uA
  target_center=100;  //in mm
  cout << " PVDIS " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("SIDIS_He3",0) != string::npos){
  if (input_filename.find("SIDIS_He3_window",0) != string::npos) Is_SIDIS_He3_window=true;
  else Is_SIDIS_He3=true;
  current=15e-6/1.6e-19;   //15uA
  target_center=-3500;  //in mm  
  cout << " SIDIS_He3 " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("SIDIS_proton",0) != string::npos){
  current=100e-9/1.6e-19;   //100nA
  target_center=-3500;  //in mm  
  cout << " SIDIS_proton " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("JPsi",0) != string::npos){
  current=3e-6/1.6e-19;   //3uA
  target_center=-3000;  //in mm  
  cout << " JPsi " << current << " " << Nevent <<  endl;  
}
else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}

char rate_filename[500];
TFile *ratefile;
TTree *T;
double rate,theta,pf,W,Q2,x;

bool Is_eDIS=false;
bool Is_pip=false,Is_pim=false,Is_pi0=false,Is_Kp=false,Is_Km=false,Is_Ks=false,Is_Kl=false,Is_p=false;
bool Is_other=false;
bool Is_real=false;
if (input_filename.find("_other_",0) != string::npos) {
  Is_other=true;
  
  if (input_filename.find("_eDIS_",0) != string::npos) {Is_eDIS=true;}  
  
  if (input_filename.find("SIDIS_He3_window_upstream",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_upstream_p_1e6.root");
  }  
  else if (input_filename.find("SIDIS_He3_window_downstream",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_window_downstream_p_1e6.root");
  }
  else if (input_filename.find("SIDIS_He3",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/SIDIS_He3/rate_solid_SIDIS_He3_p_1e6.root");
  }  
  
  if (input_filename.find("PVDIS_LD2",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_p_1e6.root");
  }

  if (input_filename.find("PVDIS_LH2",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LH2/rate_solid_PVDIS_LH2_p_1e6.root");
  }
  
  if (input_filename.find("JPsi_LH2",0) != string::npos){
    if (input_filename.find("_eDIS_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_eDIS_1e6.root");
    if (input_filename.find("_pip_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_pip_1e6.root");
    if (input_filename.find("_pim_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_pim_1e6.root");
    if (input_filename.find("_pi0_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_pi0_1e6.root");
    if (input_filename.find("_eES_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_eES_1e6.root");
    if (input_filename.find("_Kp_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_Kp_1e6.root");
    if (input_filename.find("_Km_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_Km_1e6.root");
    if (input_filename.find("_Ks_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_Ks_1e6.root");
    if (input_filename.find("_Kl_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_Kl_1e6.root");
    if (input_filename.find("_p_",0) != string::npos) sprintf(rate_filename,"/home/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/JPsi_LH2/rate_solid_JPsi_LH2_p_1e6.root");
  }  
  
  ratefile=new TFile(rate_filename);  
  if (ratefile->IsZombie()) {
    cout << "Error opening ratefile " << rate_filename << endl;
    exit(-1);
  }
  else cout << "open file " << rate_filename << endl;

  T = (TTree*) ratefile->Get("T");
  T->SetBranchAddress("rate",&rate);
  T->SetBranchAddress("theta",&theta);  
  T->SetBranchAddress("pf",&pf);  
  T->SetBranchAddress("W",&W);  
  T->SetBranchAddress("Q2",&Q2);    
  T->SetBranchAddress("x",&x);  

  cout << " other background " <<  endl;  
}
else if(input_filename.find("_real_",0) != string::npos || input_filename.find("_actual_",0) != string::npos) {
  Is_real=true;
  if (Nevent!=1000000) {cout << "real for 1e6 events only" << endl; exit(-1);}
    if (input_filename.find("_pip_",0) != string::npos) {Is_pip=true;}
    if (input_filename.find("_pim_",0) != string::npos) {Is_pim=true;}
    if (input_filename.find("_pi0_",0) != string::npos) {Is_pi0=true;}
    if (input_filename.find("_Kp_",0) != string::npos) {Is_Kp=true;}
    if (input_filename.find("_Km_",0) != string::npos) {Is_Km=true;}    
    if (input_filename.find("_Ks_",0) != string::npos) {Is_Ks=true;}    
    if (input_filename.find("_Kl_",0) != string::npos) {Is_Kl=true;}        
    if (input_filename.find("_p_",0) != string::npos) {Is_p=true;} 
    
    cout << " real background " <<  endl;
}
else  cout << "EM background " <<  endl;

int evncounter=0;
int yescounter=0,Ek_nocounter=0,rate_nocounter=0;
int ratecounter=0;
int backscat_counter=0;
int counter_actualphoton=0,counter_acutalother=0;
// int counter_hit[n]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int count_SC_front=0,count_SC=0,count_SC_back=0;
int count_SC_act=0,count_SC_inact=0;
  
Int_t flux_evn_pre,flux_ID_pre,flux_pid_pre,flux_E_pre;

Int_t flux_evn,flux_nfluxhit,flux_ID,flux_pid,flux_mpid;
Float_t flux_Edep,flux_E,flux_x,flux_y,flux_z,flux_vx,flux_vy,flux_vz,flux_px,flux_py,flux_pz;
// cout << "ok" << endl;
while (!input.eof()){
  evncounter++;
//   cout << evncounter << endl;
//   if (evncounter>10) break;

  input >> flux_evn>> flux_nfluxhit >> flux_ID >> flux_pid >> flux_mpid >>  flux_Edep >> flux_E >> flux_x >> flux_y >> flux_z >> flux_vx >> flux_vy >> flux_vz  >> flux_px >> flux_py >> flux_pz;
  
// cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;

//   if (flux_nfluxhit>300) {cout << flux_evn << endl; break;}
//     if (!(flux_pid == 22 && fabs(flux_E-0.510999)<0.00001) ) {nocounter++; continue;}
  
//   if (flux_evn_pre != flux_evn) {
//       if (count_SC_front == 1 && count_SC_back ==1 && count_SC==1) count_SC_inact++;
//       if (count_SC_front == 2 && count_SC_back ==2 && count_SC==2) count_SC_inact=count_SC_inact+2;      
//       if (count_SC_front > 0 && count_SC_back>count_SC_front && count_SC>count_SC_front) count_SC_act=count_SC_act+count_SC_front;
//       
//        count_SC_front=0;
//        count_SC=0;
//        count_SC_back=0;
//   }  
//    if (flux_ID==1 && flux_pid==22) count_SC_front++;
//    if (flux_ID==3) count_SC_front++;
//    if (flux_ID==2) count_SC_back++;
  
//    if (flux_ID==4100000 && flux_pid==22 && flux_Edep !=0)  cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
  
//   cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
  
//     if (flux_ID_pre==flux_ID && flux_pid_pre==flux_pid && fabs(flux_E_pre-flux_E)<1e-3)  cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
//     else {flux_ID_pre=flux_ID,flux_pid_pre=flux_pid,flux_E_pre=flux_E;}
  
      switch (flux_pid){
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
    
//     int detector_ID=*(flux_ID+j)/1000000;
//     int subdetector_ID=(*(flux_ID+j)%1000000)/100000;
//     int subsubchannel_ID=((*(flux_ID+j)%1000000)%100000)/10000;
// //     cout << Detector_ID << " " << SubDetector_ID << " "  << channel_ID << endl;
// 
//     
//         int hit_id;
//      switch (detector_ID){
// 	case 1:     
// 		    switch (subdetector_ID){
// 			case 1: hit_id=0; break;
// 			case 2: hit_id=1; break;
// 			case 3: hit_id=2; break;
// 			case 4: hit_id=3; break;
// 			case 5: hit_id=4; break;
// 			case 6: hit_id=5; break;
// 			default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 		    }
// 		    break;
// 	case 2:      
// 		    switch (subdetector_ID){
// 			case 1: hit_id=6; break;
// 			case 2: hit_id=7; break;
// 		      default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 		    }
// 		    break;
// 	case 3:     
// 		    switch (subdetector_ID){
// 			case 1:   
// 				  switch (subsubdetector_ID){
// 				    case 1: hit_id=8; break;
// 				    case 2: hit_id=9; break;
// 				    case 3: hit_id=10; break;
// 				    case 4: hit_id=11; break;
// 				    default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 				  }
// 				  break;
// 			case 2:
// 				  switch (subsubdetector_ID){
// 				    case 1: hit_id=12; break;
// 				    case 2: hit_id=13; break;
// 				    case 3: hit_id=14; break;
// 				    case 4: hit_id=15; break;
// 				    default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 				  }
// 				  break;
// 			default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 		    }
// 		    break;
// 	case 4:     
// 		    switch (subdetector_ID){
// 			case 1:   
// 				  switch (subsubdetector_ID){
// 				    case 1: hit_id=16; break;
// 				    case 0: hit_id=17; break;
// 				    default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 				  }
// 				  break;
// 			default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
// 		    }
// 		    break;
// 	default: cout << "wrong flux_ID " << *(flux_ID+j) << endl; break;
//       }   
      
//     cout << flux_ID << endl;    
    int detector_ID=flux_ID/100000;
    if ( detector_ID !=11 && detector_ID !=12 &&  detector_ID !=13 && detector_ID !=14 && detector_ID !=15 && detector_ID !=16 && detector_ID !=31 && detector_ID !=32 && detector_ID!=21 && detector_ID!=22 && detector_ID!=41 && detector_ID!=51)    
//     if ( (detector_ID<11 || detector_ID >16) && detector_ID !=31 && detector_ID !=32 && detector_ID!=21 && detector_ID!=22 && detector_ID!=211 && detector_ID!=41)        
    {
      cout << "wrong flux_ID "  << flux_evn  << " " << flux_nfluxhit << " " << flux_ID << endl;
     
      cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
      
            continue;
    }
    
    int subdetector_ID=flux_ID/10000; 

///=========    hit_id and pid defination ==============
//   hitid =0 - 5  GEM plane 1 - 6
//         6       LGCC  PMT
//         18      LGCC  front
//         7       HGCC  PMT         
//         19      HGCC  front
//         8 - 11  FAEC front,middle,inner,rear 
//         12 -15  LAEC front,middle,inner,rear 
//         16 - 17 MRPC front,within
//         20 - 25  GEM plane 1 - 6 front
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
///=======================================================    

    int hit_id;
     switch (detector_ID){
	case 11:     if (subdetector_ID==110) hit_id=0;
		     else if (subdetector_ID==111) hit_id=20;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 12:     if (subdetector_ID==120) hit_id=1;
		     else if (subdetector_ID==121) hit_id=21;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 13:     if (subdetector_ID==130) hit_id=2;
		     else if (subdetector_ID==131) hit_id=22;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 14:     if (subdetector_ID==140) hit_id=3;
		     else if (subdetector_ID==141) hit_id=23;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 15:     if (subdetector_ID==150) hit_id=4;
		     else if (subdetector_ID==151) hit_id=24;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 16:     if (subdetector_ID==160) hit_id=5;
		     else if (subdetector_ID==161) hit_id=25;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 21:     if (subdetector_ID==210) hit_id=6;
		     else if (subdetector_ID==211) hit_id=18;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break; 
	case 22:     if (subdetector_ID==220) hit_id=7;
		     else if (subdetector_ID==221) hit_id=19;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 31:     if (subdetector_ID==311) hit_id=8;
		     else if (subdetector_ID==312) hit_id=9;
		     else if (subdetector_ID==313) hit_id=10;
		     else if (subdetector_ID==314) hit_id=11;  
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 32:     if (subdetector_ID==321) hit_id=12;
		     else if (subdetector_ID==322) hit_id=13;
		     else if (subdetector_ID==323) hit_id=14;
		     else if (subdetector_ID==324) hit_id=15;		     
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 41:     if (subdetector_ID==411) hit_id=16;
		     else if (subdetector_ID==410) hit_id=17;
		     else if (subdetector_ID==412) hit_id=26;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 51:     if (subdetector_ID==511) hit_id=27;
		     else if (subdetector_ID==510) hit_id=28;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;		     
	default:     cout << "wrong flux_ID " << flux_ID <<  endl; break;
      }    


    int par;
    if(flux_pid==22) par=1;  //photon    
    else if (abs(flux_pid)==11) par=2; //electron or positron
    else if(flux_pid==2112) par=3;  //neutron
    else if(flux_pid==2212) par=4;  //proton    
    else if(flux_pid==211)  par=5;  //pip
    else if(flux_pid==-211) par=6;  //pim
    else if(flux_pid==321)  par=7;  //Kp    
    else if(flux_pid==-321)  par=8;  //Km
    else if(flux_pid==130)  par=9;  //Kl    
    else par=10;  //all other

//   if (flux_vz<2000) {  
// if (flux_vz<-3700 || -3300<flux_vz) continue;
    
//       if ( 12<=abs(flux_pid) && abs(flux_pid) <=16 ) continue; ///cut away muon and neutrino

//       if ( flux_pid != 22 && abs(flux_pid) !=11 ) continue; ///anything except photon and electron/position

//       if ( flux_pid != 22 && abs(flux_pid) !=11 && flux_pid !=2112 ) { continue;} ///cut anything except photon and electron and neutron


      double phi=fabs(atan(flux_y/flux_x)/3.1416*180);
      if (flux_x > 0 && flux_y > 0) phi=phi;
      else if (flux_x < 0 && flux_y > 0) phi=180-phi;
      else if (flux_x < 0 && flux_y < 0) phi=180+phi;    
      else if (flux_x > 0 && flux_y < 0) phi=360-phi;
      else cout << " flux wrong? " << flux_x << " " <<  flux_y << endl; 
      
//       double arearatio_cutStraightPhoton=1;
//       bool cutStraightPhoton=false;   //cut away straight photon due to PVDIS baffle problem
//       if(input_filename.find("PVDIS",0) != string::npos){ 
// 	  if (par==1){
// 	    arearatio_cutStraightPhoton=1./2.;  //cut 180 degree away in total, 1/2 of azimuth left
// 	    for(int i=0;i<30;i++){
// 	      if(fabs(phi-(4.5+i*12))<3) cutStraightPhoton=true;
// 	    }
// 	  }
//       }      
//       if (cutStraightPhoton) continue;

    double r=sqrt(pow(flux_x,2)+pow(flux_y,2));  //in mm
    double Theta=atan(r/(flux_z-target_center))*DEG;
    double P=sqrt(pow(flux_px,2)+pow(flux_py,2)+pow(flux_pz,2));
//     double M;
//     if (par==1) M=0;
//     else if (par==2) M=0.511;
//     else M=sqrt(pow(flux_E,2)-pow(P,2));
//     double Ek=flux_E-M;
    double Ek;
    if (fabs(flux_E - P)<1) Ek=flux_E;
    else Ek=flux_E-sqrt(pow(flux_E,2)-pow(P,2));
    
    ///geant4 or gemc problem, misidentify photon and electron
//       if(par!=1){
// 	if( TMath::IsNaN(M)){ //photon misidentified as other
// 	par=1;
// 	hactualphotonpid->Fill(flux_pid);
// // 	cout << "actualphoton " << flux_ID << " " << flux_pid << " " << flux_E << " " << P << " " << M << endl;
// 	counter_actualphoton++;
// 	}
//       }
//       if(par==1){	 //electron or positron misidentified as photon
// 	if(TMath::IsNaN(M)){}
// 	else{
// 	hactualothermass->Fill(M);
// // 	  if(0.51<=M && M<=0.52){
// // 	    par=2;
// // 	    cout << "acutalother "  << flux_ID << " " << flux_pid << " " << flux_E << " " << P << " " << M << endl;
// // 	    counter_acutalother++;
// // 	  }
// 	}
//       }
      
    if ( TMath::IsNaN(Ek) || isinf(Ek) ) {
//     if ( TMath::IsNaN(Ek)) {  
      cout << Ek << " " << flux_E << " " << P << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
       cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;     
	  Ek_nocounter++; continue;
    } 

        yescounter++; 
	
    //100MeV cut used for photon in later calorimeter simulation    
    
//     if(1<flux_E && flux_E<100 ) {    
//       if(flux_E<100 ) {  
//     if(1<flux_E ) {      
  if (true){
//   if ( !Is_other || (Is_other && P > 100) ){
      
      ///cut away the back scattering from lead
      if (input_filename.find("PVDIS",0) != string::npos) {  //PVDIS case
// 	  if (r/10.<110 || 265<r/10.) {backscat_counter++; continue;}
	  if (hit_id==8 && flux_vz/10. > 318.2) {backscat_counter++; continue;}
      }
      if (input_filename.find("PVDIS",0) == string::npos) {  //non-PVDIS case
// 	  if ((hit_id==8 && flux_vz/10. > 403.2) || (hit_id==12 && flux_vz/10. > -66.8)) {backscat_counter++; continue;}
	  if ((hit_id==8 && flux_vz/10. > 413.2) || (hit_id==12 && flux_vz/10. > -66.8)){
	    backscat_counter++; 
//        cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;     
	    continue;    
	  }
      }

      ///cut away beamline and its shielding
//       if (input_filename.find("PVDIS",0) != string::npos) {  //PVDIS case
// 	  if (flux_vz/10. > 44 && flux_vz/10. < 140 && sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) < tan(9.5/180.*3.1415926)*(flux_vz/10.-44)) {
// // 	    cout << flux_vz/10. << " " << sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) << endl;
// 	    continue;	    
// 	  }
// 	  if(flux_vz/10. >= 140 && flux_vz/10. <= 150 && sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) < 41) {
// // 	    cout << flux_vz/10. << " " << sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) << endl;	    
// 	    continue;	    
// 	  }
//       }      

      ///cut first baffle 4cm
/*      if (input_filename.find("PVDIS",0) != string::npos) {  //PVDIS case
	  if(flux_vz/10. >= 35.5 && flux_vz/10. <= 44.5 && sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) < 4) {
// 	    cout << flux_vz/10. << " " << sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.) << endl;	    
	    continue;	    
	  }
      } */     
      
//     cout << flux_pid << " " << par << endl;
//       hvertex[hit_id][par]->Fill(flux_vz/10.,flux_vy/10.);
      hvertex[hit_id][par]->Fill(flux_vz/10.,sqrt(flux_vx/10.*flux_vx/10.+flux_vy/10.*flux_vy/10.));
      hvertexZ[hit_id][par]->Fill(flux_vz/10.);      

      double thisrate;
      double weight,weightR,weightPhi,weightTheta;
      double area,areaR,areaPhi,areaTheta;

      area=1.;      /// in 
      areaR=2*3.1415926*r*1.; /// in mm2
      areaPhi=1.;  /// in any deg      
      areaTheta=2*3.1415926*r*(flux_z*(tan((Theta+0.25)/DEG)-tan((Theta-0.25)/DEG))); ///0.5deg width
      if (Is_other) {
	T->GetEntry(flux_evn-1);
// 	cout << flux_evn << " " << pf << " " << theta << endl;
	thisrate=rate;
// 	thisrate=1;	
	if (input_filename.find("JPsi",0) != string::npos) thisrate=rate*1.2; ///use 1e37 while it should 1.2e37, may change later
	if (Is_eDIS && (W<2)) continue; /// cut for eDIS
// 	if (Is_eDIS && (W<2||Q2<1)) continue; /// cut for eDIS	
      }
      else if (Is_real){
	if(Is_PVDIS){
	  if (Is_pip || Is_pim || Is_pi0) thisrate=155000.;
	  if (Is_Kp || Is_Km) thisrate=3500.;
	  if (Is_Ks || Is_Kl) thisrate=1750.;
	  if (Is_p) thisrate=27000.;
	}
	else if(Is_SIDIS_He3_window){
	  if (Is_pip) thisrate=134.;
	  if (Is_pim) thisrate=136.;
	  if (Is_pi0) thisrate=136.;	  
	  if (Is_Kp) thisrate=3.0;
	  if (Is_Km) thisrate=3.4;
	  if (Is_Ks || Is_Kl) thisrate=1.53;
	  if (Is_p) thisrate=23.;  
	}
	else if(Is_SIDIS_He3){
	  if (Is_pip) thisrate=241.;
	  if (Is_pim) thisrate=183.;
	  if (Is_pi0) thisrate=212.;  
	  if (Is_Kp) thisrate=5.9;
	  if (Is_Km) thisrate=3.7;
	  if (Is_Ks || Is_Kl) thisrate=2.4;
	  if (Is_p) thisrate=37.;  
	}
      }
      else thisrate=current/Nevent;
      weight=thisrate/1e3/area;
      weightR=thisrate/1e3/areaR;
      weightPhi=thisrate/1e3/areaPhi;
      weightTheta=thisrate/1e3/areaTheta;     

      hhitXY[hit_id][par]->Fill(flux_x/10.,flux_y/10.,weight); 
      hPlog[hit_id][par]->Fill(log10(P/1e3),weight);
      hElog[hit_id][par]->Fill(log10(flux_E/1e3),weight);
      hEklog[hit_id][par]->Fill(log10(Ek/1e3),weight);
      hP_Theta[hit_id][par]->Fill(Theta,P/1e3,weightTheta); ///in 0.5deg bin      
      hP_R[hit_id][par]->Fill(r/10.,P/1e3,weightR/10.); ///in 1cm bin            
      hPlog_R[hit_id][par]->Fill(r/10.,log10(P/1e3),weightR/10.); ///in 1cm bin      
      hElog_R[hit_id][par]->Fill(r/10.,log10(flux_E/1e3),weightR/10.); ///in 1cm bin
      hEklog_R[hit_id][par]->Fill(r/10.,log10(Ek/1e3),weightR/10.); ///in 1cm bin
      
      double energy_depo_Preshower=0,energy_depo_Shower=0;   
      if (hit_id==8 || hit_id==12){	    	  
	  if(flux_pid==22) {
	    energy_depo_Preshower=FastResponse("gamma","PS","scint",Ek/1e3);  //photon    
	    energy_depo_Shower=FastResponse("gamma","S","scint",Ek/1e3);		    
	  }
	  else if (abs(flux_pid)==11) {
	    energy_depo_Preshower=FastResponse("e","PS","scint",Ek/1e3); //electron or positron
	    energy_depo_Shower=FastResponse("e","S","scint",Ek/1e3);		    
	  }		  
      //     else if(flux_pid==2112) energy_depo_Preshower=3;  //neutron
	  else if(flux_pid==2212) {
	    energy_depo_Preshower=FastResponse("p","PS","scint",Ek/1e3);  //proton    
	    energy_depo_Shower=FastResponse("p","S","scint",Ek/1e3);		    
	  }		  
	  else if(abs(flux_pid)==211)  {
	    energy_depo_Preshower=FastResponse("pi","PS","scint",Ek/1e3);  //pip or pim
	    energy_depo_Shower=FastResponse("pi","S","scint",Ek/1e3);		    
	  }		  
      //     else if(flux_pid==321)  energy_depo_Preshower=7;  //Kp    
      //     else if(flux_pid==-321)  energy_depo_Preshower=8;  //Km
      //     else if(flux_pid==130)  energy_depo_Preshower=9;  //Kl    
	  else energy_depo_Preshower=0;  //all other	    
// 	    cout << "flux_pid " << flux_pid << " energy_depo " << energy_depo << endl;    
	  hEdepR_Preshower[hit_id][par]->Fill(r/10.,energy_depo_Preshower*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2	    
	  hEdepR_Shower[hit_id][par]->Fill(r/10.,energy_depo_Shower*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2	  
      }      
      
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
      
      hEklog_R_Phi[hit_id][par]->Fill(phi-int(phi/12)*12,r/10.,log10(Ek/1e3),weight/30.);  // due to phi cover 12 degree, this will overlap 30 sector together, so we need to divide rate by 30
//       hEklog_R_Phi[hit_id][par]->Fill(phi,r/10.,log10(Ek/1e3),weight);    
              
	if (hit_id<6 && flux_Edep<26e-6){} //gem required >26eV energy deposit in first 2 gas layer
	else if ((hit_id==17 || hit_id==26) && flux_Edep<1e-10){
// 	  cout <<"flux_Edep " << flux_Edep << endl;  
	} //mrpc required >0 energy deposit
	else if (hit_id==28 && flux_Edep<1e-10){
// 	  cout <<"flux_Edep " << flux_Edep << endl;  	  
	} //spd required >0 energy deposit
	else {  // all other just counting
	    hfluxR[hit_id][par]->Fill(r/10.,weightR/50.);   ///in 5cm bin
	    hEfluxR[hit_id][par]->Fill(r/10.,Ek/1e3*weightR/100.*1e4); ///in 10cm bin and from mm2 to 100cm2
	    
	    
		///divide rate by 15 because it's 24 degree	    
	    hfluxPhi[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15);	    	    
	    hEfluxPhi[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15);    
	    if(-10. < flux_vz/10. && flux_vz/10. < 30. && fabs(flux_vx/10.)<5. && fabs(flux_vy/10.)< 5.){
		hfluxPhi_target[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15); 
		hEfluxPhi_target[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15);
	    }	
	    else{
		hfluxPhi_other[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi/15);	      
		hEfluxPhi_other[hit_id][par]->Fill(phi-int(phi/24)*24,weightPhi*Ek/15); 
	    }      
	    
	    hflux_x_y[hit_id][par]->Fill(flux_x/10.,flux_y/10.,weight/100.); //in 1cm2 bin	    
	    if (phi-int(phi/12)*12<6) hflux_x_y_high[hit_id][par]->Fill(flux_x/10.,flux_y/10.,weight/100.);
	    else hflux_x_y_low[hit_id][par]->Fill(flux_x/10.,flux_y/10.,weight/100.);    
	    hEflux_x_y[hit_id][par]->Fill(flux_x/10.,flux_y/10.,weight*Ek/100.*10.); ///in 1cm2 bin and from 1cm to 10cm	    
	    
				hfluxEklog_cut[hit_id][par]->Fill(log10(Ek),weight);
// 				hfluxEklog_cut_niel[hit_id][par]->Fill(log10(Ek),weight);
	    
	  }	
	
//     double rcut;  //in cm
//     if ((input_filename.find("SIDIS",0) != string::npos) || (input_filename.find("JPsi",0) != string::npos) ){
//       if(subdetector_ID==311 || subdetector_ID==312 || subdetector_ID==314) rcut=100+10;
//       else if (subdetector_ID==321 || subdetector_ID==322) rcut=75+10;
//       else rcut=0;          
//     }
//     else if (input_filename.find("PVDIS",0) != string::npos){
//       if(subdetector_ID==311 || subdetector_ID==312 || subdetector_ID==314) rcut=118+10;
//       else rcut=0;
//     }  
//     else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}  
    
//     if (r/10<rcut){
//      hfluxEklog_cut[hit_id][par]->Fill(log10(Ek),weight);       
//      if (par==1 || par==2) hfluxEklog_cut[hit_id][0]->Fill(log10(Ek),weight);  
//     }

//      hfluxEklog_cut[hit_id][par]->Fill(log10(Ek),(current/Nevent)/(3.1416*(pow(261.,2.)-pow(118.,2.))));
      

    }
    
    flux_evn_pre = flux_evn;
//      if (yescounter >100) break;
    
}

cout << "count_SC_act " << count_SC_act << " count_SC_inact " << count_SC_inact << endl;

cout << "yescounter " << yescounter << " Ek_nocounter " << Ek_nocounter << " rate_nocounter " << rate_nocounter << endl;
cout << "counter_actualphoton " << counter_actualphoton << " counter_acutalother " << counter_acutalother << endl;
cout << "ratecounter " << ratecounter << endl;
cout << "backscat_counter " << backscat_counter << endl;

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
// TText *text=pt->AddText(label[i]);
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
TText *text=pt1->AddText(label[i]);
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

outputfile->Write();
outputfile->Flush();

}
