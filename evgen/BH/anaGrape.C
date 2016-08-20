//#include "/home/mpaolone/work/anaLepv2/v3/set_style.h"
#include <iostream> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TRandom3.h>

#include "../../subsystem/gem/resolution/v1/Lresolution.h"    

using namespace std;

// void anaGrape(string input_filedir,string detector=""){
// void anaGrape(string detector="",bool Is_inter=false){
void anaGrape(string detector="",bool Is_res=false){
//  set_style();
// gROOT->Reset();
gStyle->SetPalette(1);
// gStyle->SetOptStat(11111111);
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);

      double count_convert;
      double rate_convert;
double thetamin,thetamax;
TH3F *hacceptance_PThetaPhi_positive,*hacceptance_PThetaPhi_negative;
TH2F *hacceptance_ThetaP_forwardangle,*hacceptance_ThetaP_largeangle;
TH2F *hacceptance_ThetaP_forwardangle_muon,*hacceptance_ThetaP_largeangle_muon;
TH2F *hacceptance_ThetaP_forwardangle_muonm,*hacceptance_ThetaP_largeangle_muonm;
TH2F *hacceptance_ThetaP_forwardangle_muonp,*hacceptance_ThetaP_largeangle_muonp;

if (detector=="CLAS12"){
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele.root");
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele_largebin.root");
  TFile *acceptancefile=new TFile("../clasev_acceptance.root");
  
  hacceptance_PThetaPhi_positive=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_pip");  
  hacceptance_PThetaPhi_negative=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_ele");

  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_PThetaPhi_positive->Draw();
  c_acceptance->cd(2);
  hacceptance_PThetaPhi_negative->Draw(); 
  
  thetamin=0;    
  thetamax=180;  

//      pb = 1e-36 cm2, lumi 1e35/cm2/s, 120 days, 0.85 eff
      rate_convert = 1e-36*1e35*0.85;  
      count_convert = rate_convert*3600*24*120;      
  
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;   
}
else if (detector=="SoLID_JPsi"){  
  TFile *acceptancefile=new TFile("../acceptance_solid_JPsi_electron_target315_output.root");  
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_largeangle");
  
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  c_acceptance->cd(2);
  hacceptance_ThetaP_largeangle->Draw("colz");  
  
  thetamin=0;    
  thetamax=60;  
  
//      pb = 1e-36 cm2, lumi 1.2e37/cm2/s, 50 days, 0.85 eff
      rate_convert = 1e-36*1.2e37*0.85;  
      count_convert = rate_convert*3600*24*50;      
  
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;     
}
else if (detector=="SoLID_DDVCS_JPsiSetup"){  
  TFile *acceptancefile=new TFile("../acceptance_solid_JPsi_electron_target315_output.root");  
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_largeangle");
  
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  c_acceptance->cd(2);
  hacceptance_ThetaP_largeangle->Draw("colz");  
  
  thetamin=0;    
  thetamax=60;  
  
//      pb = 1e-36 cm2, lumi 1.2e37/cm2/s, 50 days, 0.85 eff
      rate_convert = 1e-36*1.2e37*0.85;  
      count_convert = rate_convert*3600*24*50;      
  
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;   
      
//   TFile *acceptancefile_muon=new TFile("../acceptance_solid_DDVCS_JPsi_LH2_muonp_target315_output.root");       
// TFile *acceptancefile_muon=new TFile("../acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_1stFAMD_1stLAMD.root");             
// TFile *acceptancefile_muon=new TFile("../acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_2ndFAMD_1stLAMD.root");             
TFile *acceptancefile_muon=new TFile("../acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_3rdFAMD_1stLAMD.root");             
// TFile *acceptancefile_muon=new TFile("../acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_4thFAMD_1stLAMD.root");             

  
  hacceptance_ThetaP_forwardangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_largeangle");
  
  TCanvas *c_acceptance_muon = new TCanvas("acceptance_muon","acceptance_muon",1200,900);
  c_acceptance_muon->Divide(2,1);
  c_acceptance_muon->cd(1);
  hacceptance_ThetaP_forwardangle_muon->Draw("colz");
  c_acceptance_muon->cd(2);
  hacceptance_ThetaP_largeangle_muon->Draw("colz");  
  
}
else if (detector=="SoLID_DDVCS_PVDISSetup"){
  TFile *acceptancefile=new TFile("../acceptance_solid_PVDIS_electron_output.root");  
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
    
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1000,900);
  c_acceptance->Divide(1,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  
   TFile *acceptancefile_muonm=new TFile("../acceptance_solid_DDVCS_PVDIS_LH2_full_muonm_1e5_output_1stFAMD.root");             
   TFile *acceptancefile_muonp=new TFile("../acceptance_solid_DDVCS_PVDIS_LH2_full_muonp_1e5_output_1stFAMD.root");             
   
   hacceptance_ThetaP_forwardangle_muonm=(TH2F*) acceptancefile_muonm->Get("acceptance_ThetaP_forwardangle"); 
   hacceptance_ThetaP_forwardangle_muonp=(TH2F*) acceptancefile_muonp->Get("acceptance_ThetaP_forwardangle");    
  
  TCanvas *c_acceptance_muon = new TCanvas("acceptance_muon","acceptance_muon",1200,900);
  c_acceptance_muon->Divide(2,1);
  c_acceptance_muon->cd(1);
  hacceptance_ThetaP_forwardangle_muonm->Draw("colz");
  c_acceptance_muon->cd(2);
  hacceptance_ThetaP_forwardangle_muonp->Draw("colz");  
   
  thetamin=10;    
  thetamax=50;  
  
//      pb = 1e-36 cm2, lumi 0.53e39/cm2/s, 120 days, 0.85 eff
      rate_convert = 1e-36*0.53e39*0.85;  
      count_convert = rate_convert*3600*24*120;
}
else {cout << "wrong detector" << endl; return;}

  Lresolution track("JPsi"); 
  TRandom3 rnd;  
  
//   TFile *acceptancefile=new TFile("accep.root");
// TH2F *h2_acc=(TH2F*) acceptancefile->Get("h2");
// TH2F *h3_acc=(TH2F*) acceptancefile->Get("h3");
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,1);
//   c_acceptance->cd(1);
//   h2_acc->Draw("colz");
//   c_acceptance->cd(2);
//   h3_acc->Draw("colz");

//  bool conf_4fold=false,conf_3fold_NOp=false,conf_3fold_NOe=false;
//  bool conf_validation=false;
// if (input_filedir.find("4fold",0) != string::npos)  conf_4fold=true;
// if (input_filedir.find("3fold_NOp",0) != string::npos)  conf_3fold_NOp=true; 
// if (input_filedir.find("3fold_NOe",0) != string::npos)  conf_3fold_NOe=true;
// if (input_filedir.find("validation",0) != string::npos)  conf_validation=true; 
  
char output_filename[80];
// sprintf(output_filename, "%s.root",input_filedir.c_str());
sprintf(output_filename, "grp_out.root");
  
TFile *outputfile=new TFile(output_filename, "recreate");

TH1F *hPlog_plus_FA = new TH1F("Plog_plus_FA","mu+ FA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_plus_LA = new TH1F("Plog_plus_LA","mu+ LA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_minus_FA = new TH1F("Plog_minus_FA","mu- FA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_minus_LA = new TH1F("Plog_minus_LA","mu- LA;log(P) GeV;kHz",50,-6,1.3);

TH2F *hepscat = new TH2F("hepscat","",50,-1.0,1.0,60,-1.0,1.0);
TH2F *hemscat = new TH2F("hemscat","",50,-1.0,1.0,60,-1.0,1.0);

TH1F *hW = new TH1F("W","",50,4,4.5);
TH1F *hWstat = new TH1F("Wstat","",50,4,4.5);

TH1F *hkpth = new TH1F("hkpth","",100, 0.0, 40.0);
TH1F *hprth = new TH1F("hprth","",100, 0.0, 40.0);

TH1F *hkpph = new TH1F("hkpph","",100, -180., 180.);
TH1F *hprph = new TH1F("hprph","",100, -180., 180.);

TH1F *hkpp = new TH1F("hkpp","",100,0, 5);
TH1F *hprp = new TH1F("hprp","",100,0, 5);

TH1F *hMM = new TH1F("MM",";MM (GeV)",100,0.6,1.4);
TH2F *hMM_Q2 = new TH2F("MM_Q2","; MM (GeV);Q2 (GeV^{2})",100,0.6,1.4,100,0,10);
TH2F *hMM_Qp2 = new TH2F("MM_Qp2","; MM (GeV);Q'2 (GeV^{2})",100,0.6,1.4,100,0,10);
TH2F *hMM_t = new TH2F("MM_t","; MM (GeV);-t (GeV^{2})",100,0.6,1.4,100,0,2);

TH1F *ht = new TH1F("t","t",600,0,6);

TH2F *ht_Qp2 = new TH2F("t_Qp2",";-t (GeV^{2});Q'2 (GeV^{2})",100,0,2,100,0,10);
TH2F *ht_W = new TH2F("t_W",";-t (GeV^{2});W (GeV)",100,0,2,100,0,5);
TH2F *hQ2_W = new TH2F("Q2_W",";Q2 (GeV^{2});W (GeV)",100,0,10,100,0,5);
TH2F *ht_Q2 = new TH2F("t_Q2",";-t (GeV^{2});Q2 (GeV^{2})",100,0,2,100,0,10);
TH2F *ht_eta = new TH2F("t_eta",";-t (GeV^{2});-#eta",100,0,2,100,0,1);
TH2F *ht_xi = new TH2F("t_xi",";-t(GeV^{2});#xi",100,0,2,100,-1,1);

TH2F *hxbj_eta = new TH2F("xbj_eta",";x_{B};-#eta",100,0,1,100,0,1);
TH2F *hxbj_xi = new TH2F("xbj_xi",";x_{B};#xi",100,0,1,100,-1,1);
TH2F *hxbj_Q2= new TH2F("xbj_Q2",";x_{B};Q2(GeV^{2})",100,0,1,100,0,10);
TH2F *hxi_eta = new TH2F("xi_eta",";#xi;-#eta",100,-1,1,100,0,1);
TH2F *hQ2_Qp2 = new TH2F("Q2_Qp2",";Q2(GeV^{2});Q'2(GeV^{2})",100,0,10,100,0,10);

TH2F *htmin_W = new TH2F("tmin_W",";tmin (GeV^{2});W (GeV)",100,0,5,100,0,5);
TH2F *htmax_W = new TH2F("tmax_W",";tmax (GeV^{2});W (GeV)",100,0,5,100,0,5);	

const int m=4;

char *title[4]={"scattered lepton","recoil p","decay lepton^{-}","decay lepton^{+}"};
TH3F *ht_Qp2_eta[m];
TH2F *hQp2_eta[m],*hQp2_t[m];
TH1F *hlepIM1[m],*hlepIM2[m],*hlepIM[m];
TH1F *hlepIM1_error[m],*hlepIM2_error[m],*hlepIM_error[m];
TH2F *hlepIM_2D[m];
TH2F *hdecaymom1[m],*hdecaymom2[m];
TH2F *hdecayangle1[m],*hdecayangle2[m];
TH2F *hThetaP[4][m],*hThetaPhi[4][m];
TH1F *hnew_p[m],*hnew_theta[m],*hnew_phi[m];
for(int k=0;k<m;k++){
  char hstname[100];
  for(int l=0;l<4;l++){  
   sprintf(hstname,"ThetaP_%i_%i",l,k);
   hThetaP[l][k]=new TH2F(hstname,Form("%s;#theta_{lab} (deg);P (GeV)",title[l]),180,0,180,800,0,10);
   sprintf(hstname,"ThetaPhi_%i_%i",l,k);
   hThetaPhi[l][k]=new TH2F(hstname,";#theta_{lab} (deg);#phi_{lab} (deg)",180,0,180,100,-180.,180.);   
  }

  sprintf(hstname,"new_p_%i",k);
  hnew_p[k] = new TH1F(hstname,hstname,100,-0.1,0.1);
  sprintf(hstname,"new_theta_%i",k);
  hnew_theta[k] = new TH1F(hstname,hstname,100,-0.5,0.5);
  sprintf(hstname,"new_phi_%i",k);
  hnew_phi[k] = new TH1F(hstname,hstname,100,-1,1);
  
  sprintf(hstname,"decayangle1_%i",k);
  hdecayangle1[k] = new TH2F(hstname,";l^{+} #theta (deg);l^{-} #theta (deg)",100,0,40,100,0,40);

  sprintf(hstname,"decayangle2_%i",k);
  hdecayangle2[k] = new TH2F(hstname,";l^{+} #theta (deg);l^{-} #theta (deg)",100,0,40,100,0,40);  
  
  sprintf(hstname,"decaymom1_%i",k);
  hdecaymom1[k] = new TH2F(hstname,";l^{+} P (GeV);l^{-} P (GeV)",100,0,10,100,0,10);

  sprintf(hstname,"decaymom2_%i",k);
  hdecaymom2[k] = new TH2F(hstname,";l^{+} P (GeV);l^{-} P (GeV)",100,0,10,100,0,10);
  
  sprintf(hstname,"lepIM_2D_%i",k);
  hlepIM_2D[k] = new TH2F(hstname,";e+ e-(1st) Inv Mass (GeV);e+ e-(2nd) Inv Mass (GeV)",80,0,4.0,80,0,4.0);   
  
  sprintf(hstname,"lepIM1_%i",k);
  hlepIM1[k] = new TH1F(hstname,hstname,80,0,4.0);   
  sprintf(hstname,"lepIM2_%i",k);
  hlepIM2[k] = new TH1F(hstname,hstname,80,0,4.0);   
  sprintf(hstname,"lepIM_%i",k);
  hlepIM[k] = new TH1F(hstname,hstname,80,0,4.0);

  sprintf(hstname,"lepIM1_error_%i",k);
  hlepIM1_error[k] = new TH1F(hstname,hstname,20,0,4.0);   
  sprintf(hstname,"lepIM2_error_%i",k);
  hlepIM2_error[k] = new TH1F(hstname,hstname,20,0,4.0);   
  sprintf(hstname,"lepIM_error_%i",k);
  hlepIM_error[k] = new TH1F(hstname,hstname,20,0,4.0);
  
  sprintf(hstname,"t_Qp2_eta_%i",k);
  ht_Qp2_eta[k]=new TH3F(hstname,hstname,100,0,0.5,100,0,10,100,0,5);
  ht_Qp2_eta[k]->SetTitle(";#eta;Q'2(GeV^{2});t(GeV^{2})");      
  sprintf(hstname,"Qp2_eta_%i",k);
  hQp2_eta[k]=new TH2F(hstname,hstname,100,0,0.5,100,0,10);
  hQp2_eta[k]->SetTitle(";#eta;Q'2(GeV^{2})");
  sprintf(hstname,"Qp2_t_%i",k);  
  hQp2_t[k]=new TH2F(hstname,hstname,100,0,5,100,0,10);
  hQp2_t[k]->SetTitle(";t(GeV^{2});Q'2(GeV^{2})");  
}

double weight[m];

Double_t pi1 = TMath::Pi();
//   cout << pi1 << endl;

Double_t D2R = 3.1415/180.;

Double_t DEG = 180./3.1415;
   
// char input_filename[80];
// // sprintf(input_filename, "%s/grp.root",input_filedir.c_str());
// sprintf(input_filename, "grp.root");

// char* input_filename[5]={"grp.root_1","grp.root_2","grp.root_3","grp.root_4","grp.root_5"};
char* input_filename[1]={"grp.root"};
// sprintf(input_filename, "%s/grp.root",input_filedir.c_str());

  TChain *h11 = new TChain("h11");
  TChain *h1 = new TChain("h1");
  for(Int_t i=0; i < 1; i++){
    h11->Add(input_filename[i]);
    h1->Add(input_filename[i]);  
  }

  Double_t xsec[20];

  h11->SetBranchStatus("*",0);
  h11->SetBranchStatus("xsec",1);
  h11->SetBranchAddress("xsec",&xsec);
  h11->GetEntry(0);

  cout << "total Cross Section " << xsec[0] << " pb" << endl;
  // total Cross Section also can be found in the spring output on screen
  
  Float_t px[20];
  Float_t py[20];
  Float_t pz[20];
  Float_t pe[20];
  Float_t pm[20];
//   Short_t kf[15];
//   Bool_t sta[20];
//   Int_t npy;
  Float_t kf[20];  
  Float_t sta[20];
  Float_t npy[20]; 

  h1->SetBranchStatus("*",0);

  h1->SetBranchStatus("px",1);
  h1->SetBranchAddress("px",&px);
  h1->SetBranchStatus("py",1);
  h1->SetBranchAddress("py",&py);
  h1->SetBranchStatus("pz",1);
  h1->SetBranchAddress("pz",&pz);
  h1->SetBranchStatus("pe",1);
  h1->SetBranchAddress("pe",&pe);
  h1->SetBranchStatus("pm",1);
  h1->SetBranchAddress("pm",&pm);
  h1->SetBranchStatus("kf",1);
  h1->SetBranchAddress("kf",&kf);
  h1->SetBranchStatus("sta",1);
  h1->SetBranchAddress("sta",&sta);
  h1->SetBranchStatus("npy",1);
  h1->SetBranchAddress("npy",&npy);

  Int_t nevent = h1->GetEntries();

  cout << nevent << endl;
  TLorentzVector kp, prot, ep, em, ki, targ;

  Double_t effxsec = xsec[0]/(double)nevent;

  Bool_t scatPhiBool, scat_e_calo;

  int counter1=0,counter2=0,counter3=0,counter4=0,counter5=0,counter6=0;
  
  Int_t counter;
  Int_t countd = 1;
  cout << "|___________________|" << endl;
  cout << "|" << flush;
  
    double xsec_thisbin=0;  
  
  for(Int_t i=0; i < nevent; i++){
//     for(Int_t i=0; i < 10; i++){
    Double_t id = i;
    Double_t neventd = nevent;
    if(floor(id/neventd*20) == countd){
   
      cout << "=" << flush;
      countd++;
      if(countd == 20){
	cout << "|" << endl;
      }
    }
//     cout << i << endl;
    h1->GetEvent(i);

    //all entry http://research.kek.jp/people/tabe/grape/CPC/node8.html
    if(i<3) {
      for (Int_t j=0; j < 14; j++) {
	cout << j << "\t"  << px[j] <<  "\t"  << py[j] <<  "\t"  << pz[j] <<  "\t"  << pe[j] <<  "\t"  << pm[j] <<  "\t"  << kf[j] <<  "\t"  << sta[j] <<  "\t"  << npy[j] << endl; 
      }
      cout << "******************************"<< endl;
    }

//       for(Int_t j=0; j < 14; j++){
// // 	TLorentzVector par_tmp;
// // 	par_tmp.SetXYZT(px[j],py[j],pz[j],pe[j]);
// // 	cout <<  par_tmp.M() << " ";
// 	cout <<  pm[j] << " ";	
//       }
//       cout << endl;
    
//     targ.SetXYZT(px[0],py[0],pz[0],pe[0]);    
//     ki.SetXYZT(px[1],py[1],pz[1],pe[1]);    
//     targ.SetXYZT(px[3],py[3],pz[3],pe[3]);
//     ki.SetXYZT(px[4],py[4],pz[4],pe[4]);  //electron before ISR(initial state radiation)  
    targ.SetXYZT(px[4],py[4],pz[4],pe[4]);
    ki.SetXYZT(px[5],py[5],pz[5],pe[5]); //electron after ISR(initial state radiation)  
// cout <<  targ.P()  << " " <<  ki.P() << endl;

    //particle after FSR (not effective)
    prot.SetXYZT(px[10],py[10],pz[10],pe[10]);    
    kp.SetXYZT(px[11],py[11],pz[11],pe[11]);
    ep.SetXYZT(px[12],py[12],pz[12],pe[12]);
    em.SetXYZT(px[13],py[13],pz[13],pe[13]);
// cout <<  prot.M()  << " " <<  kp.M() << " " << ep.M() << " " << em.M() << endl;
    
    //this is before grape-dilepton use coordinate where electron beam goes along -z
    ki.RotateY(pi1);
    targ.RotateY(pi1);    
    prot.RotateY(pi1);    
    kp.RotateY(pi1);
    ep.RotateY(pi1);
    em.RotateY(pi1);  

    //get acceptance
      int whichone=0;      
      double acc=0;      
      double acc_prot=0,acc_kp=0,acc_em=0,acc_ep=0;
      double acc_em_FA=0,acc_em_LA=0,acc_ep_FA=0,acc_ep_LA=0;
      double acc_kp_FA=0,acc_kp_LA=0,acc_prot_FA=0,acc_prot_LA=0;      
      if (detector=="CLAS12"){
	  //note CLAS12 acceptance phi (0,360), TLonrenzvector.Phi (-180,180) 	
	  acc_prot=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(prot.Phi()*DEG+180,prot.Theta()*DEG,prot.P()));
	  acc_ep=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(ep.Phi()*DEG+180,ep.Theta()*DEG,ep.P()));
	  acc_kp=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(kp.Phi()*DEG+180,kp.Theta()*DEG,kp.P()));	  
	  acc_em=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(em.Phi()*DEG+180,em.Theta()*DEG,em.P()));	  	  
	  
// 	  if (acc_prot > 0) cout << "acc_prot " << acc_prot << endl;
// 	  if (acc_ep > 0) cout << "acc_ep " << acc_ep << endl;
// 	  if (acc_kp > 0) cout << "acc_kp " << acc_kp << endl;
// 	  if (acc_em > 0) cout << "acc_em " << acc_em << endl; 

// 	  //cut away unsure low acceptance		  
// 	  if (acc_prot < 0.9) acc_prot=0;
// 	  if (acc_ep < 0.9) acc_ep=0;
// 	  if (acc_kp < 0.9) acc_kp=0;
// 	  if (acc_em < 0.9) acc_em=0; 
	    	  
	  //lepton has no detection at central detector, nor when higher than 4.9GeV HTCC threshold at forward detetor
	  if (ep.Theta()*DEG>36 || (ep.Theta()*DEG<=36 && ep.P() > 4.9)) acc_ep=0;
	  if (em.Theta()*DEG>36 || (em.Theta()*DEG<=36 && em.P() > 4.9)) acc_em=0;
	  if (kp.Theta()*DEG>36 || (kp.Theta()*DEG<=36 && kp.P() > 4.9)) acc_kp=0;
	  
	  //for both electron
	  if (acc_ep>0 && acc_em>0 && acc_kp>0)	{acc=acc_ep*acc_em*acc_kp; whichone=1;}  //both in main detector
	  else if (acc_ep>0 && acc_em>0 && (2.5 <=kp.Theta()*DEG && kp.Theta()*DEG<=4.5)) {acc=acc_ep*acc_em*1; whichone=2;} //one in forard tagger
	  else if (acc_ep>0 && (2.5 <=em.Theta()*DEG && em.Theta()*DEG<=4.5) && acc_kp>0) {acc=acc_ep*1*acc_kp; whichone=3;}	//the other in forard tagger  
	  else if (acc_ep>0 && (2.5 <=em.Theta()*DEG && em.Theta()*DEG<=4.5) && (2.5 <=kp.Theta()*DEG && kp.Theta()*DEG<=4.5)) {acc=acc_ep*1*1; whichone=4;}	 //both in forard tagger 
	  else if (acc_ep>0) {acc=0; whichone=5;} //positron detected, but not both electron detected
	  else {acc=0; whichone=0;}  //all other cases
	  	    
// 	  if (prot.Theta()*DEG>36 && prot.P() > 1) acc_prot=0;
// 	  if (prot.Theta()*DEG<36 && prot.P() > 4) acc_prot=0;
	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;
// 	  acc=acc_ep*acc_kp*acc_em;	  

	  if (acc>0){
	    if (whichone==1) {counter1++; }
	    else if (whichone==2) counter2++;
	    else if (whichone==3) counter3++;
	    else if (whichone==4) counter4++;	    
	    else cout << "something wrong" << endl;
	  }
	  else {
	    if (whichone==5) counter5++;
	    else counter6++;
	  }
// 	  if (acc==0 && whichone!=4) cout << "kkkkkkkkkkkkkk" << endl;
	  
// 	  if (e_theta<=36) res_index_electron=0;
// 	  if (e_theta >36) res_index_electron=1;
// 	  if (ep.Theta()*DEG<=36) res_index_positron=0;
// 	  if (ep.Theta()*DEG >36) res_index_positron=1;
// 	  if (prot.Theta()*DEG<=36) res_index_proton=0;
// 	  if (prot.Theta()*DEG >36) res_index_proton=1;
	   
      }
      else if (detector=="SoLID_JPsi"){
	  //sim phi (-180,180)	
	  acc_prot_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(ep.Theta()*DEG,ep.P()));	  
	  acc_em_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(em.Theta()*DEG,em.P()));	  
	
	  acc_prot_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(ep.Theta()*DEG,ep.P()));  
	  acc_em_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(em.Theta()*DEG,em.P()));	
	   
	  acc_prot = acc_prot_FA+acc_prot_LA;
	  acc_kp= acc_kp_LA+acc_kp_FA;	  	  
	  acc_ep= acc_ep_LA+acc_ep_FA;
	  acc_em= acc_em_LA+acc_em_FA;
	  
	  //3fold_decaypairelectron
// 	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep;
// 	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep;	  

	  //4fold
 	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep*acc_prot;
	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep*acc_prot;	  
//  	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep*acc_prot_FA;
// 	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep*acc_prot_FA;	  

	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
// 	  acc=acc_kp*acc_ep*acc_em;	  	  	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
// 	  if (acc_kp_FA>0 && acc_em_LA>0)  {acc=acc_kp_FA*acc_ep*acc_em_LA;}
// 	  if (acc_kp_LA>0 && acc_em_FA>0)  {
// 	    acc=acc_kp_LA*acc_ep*acc_em_FA;
// // 	    cout << kp.P() << " " << em.P() << endl;
// 	    TLorentzVector v_tmp=kp;
// 	    kp=em;
// 	    em=v_tmp;
// // 	    cout << em.P() << " " << kp.P() << endl;	    
// 	  }		  
	  
// 	  if (acc>0){
// 	    if (whichone==1) {counter1++; acc=0;}
// 	    else if (whichone==2) counter2++;
// 	    else if (whichone==3) counter3++;
// 	    else cout << "something wrong" << endl;
// 	  }
// 	  else {
// 	    if (whichone==4) counter4++;
// 	    else counter5++;
// 	  }
      }            
      else if (detector=="SoLID_DDVCS_JPsiSetup"){
	  //sim phi (-180,180)	
	  acc_prot_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_FA=hacceptance_ThetaP_forwardangle_muon->GetBinContent(hacceptance_ThetaP_forwardangle_muon->FindBin(ep.Theta()*DEG,ep.P()));	  
	  acc_em_FA=hacceptance_ThetaP_forwardangle_muon->GetBinContent(hacceptance_ThetaP_forwardangle_muon->FindBin(em.Theta()*DEG,em.P()));	  
	
	  acc_prot_LA= hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_LA= hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_LA = hacceptance_ThetaP_largeangle_muon->GetBinContent(hacceptance_ThetaP_largeangle_muon->FindBin(ep.Theta()*DEG,ep.P()));  
	  acc_em_LA = hacceptance_ThetaP_largeangle_muon->GetBinContent(hacceptance_ThetaP_largeangle_muon->FindBin(em.Theta()*DEG,em.P()));	
	   
	  acc_prot = acc_prot_FA+acc_prot_LA;
	  acc_kp= acc_kp_LA+acc_kp_FA;	  	  
	  acc_ep= acc_ep_LA+acc_ep_FA;
	  acc_em= acc_em_LA+acc_em_FA;	  	  

	  acc=acc_kp*acc_ep*acc_em;
// 	  acc=acc_kp*acc_ep_FA*acc_em_FA;	  	  	  	  
	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
// 	  if (acc>0){
// 	    if (whichone==1) {counter1++; acc=0;}
// 	    else if (whichone==2) counter2++;
// 	    else if (whichone==3) counter3++;
// 	    else cout << "something wrong" << endl;
// 	  }
// 	  else {
// 	    if (whichone==4) counter4++;
// 	    else counter5++;
// 	  }
      }      
      else if (detector=="SoLID_DDVCS_PVDISSetup"){
	  //sim phi (-180,180)	

// 	  acc_prot=0;
// 	  acc_prot=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));	  
// 	  if (22<prot.Theta()*DEG && prot.Theta()*DEG<35) acc_prot=1;	
	
	  acc_kp=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  

	  acc_ep_FA=hacceptance_ThetaP_forwardangle_muonp->GetBinContent(hacceptance_ThetaP_forwardangle_muonp->FindBin(ep.Theta()*DEG,ep.P()));	acc_em_FA=hacceptance_ThetaP_forwardangle_muonm->GetBinContent(hacceptance_ThetaP_forwardangle_muonm->FindBin(em.Theta()*DEG,em.P()));	
	  
	  acc_ep= acc_ep_FA;
	  acc_em= acc_em_FA;	  
	  
// 	  if (22<ep.Theta()*DEG && ep.Theta()*DEG<35) acc_ep=1;
// 	  if (22<em.Theta()*DEG && em.Theta()*DEG<35) acc_em=1;
	  
// 	  	cout << acc_kp << "\t" << acc_ep << "\t" << acc_em << endl;
		
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
	  acc=acc_kp*acc_ep*acc_em;	  	  	  
// 	  	  acc=acc_ep*acc_em;	  	  	  
// 	  	  acc=acc_prot;	  	  	  	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
      }     
      else {cout << "wrong detector" << endl;}

      
//=== get resolution from tracking and apply it ==========================
/* Get resolution to res: p/GeV, theta/Deg, phi/Deg, vertexz/cm
  Kinematic variables kin: p/GeV, theta/Deg, phi/Deg
  Particle: e+(1), e-(-1), mu+(2), mu-(-2), pi+(3), pi-(-3), K+(4), K-(-4), p(5). Default with e-(-1)
  Return O:normal, 1:error */    
if (Is_res &&  acc>0){
//     Lresolution track("JPsi");
    double new_p,new_theta,new_phi;    
    double kin[3];
    double res[4];
    double res_factor=1;
    
    //scattered electron
    kin[0]=kp.P();
    kin[1]=kp.Theta()*DEG;
    kin[2]=kp.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,"e-")) {
      cout << "e-" << endl;            
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[0]->Fill(new_p/kin[0]-1);
    hnew_theta[0]->Fill(new_theta-kin[1]);
    hnew_phi[0]->Fill(new_phi-kin[2]);    
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    kp.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),kp.M());
//       cout << kp.P() << " " << kp.Theta()*DEG << " " << kp.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;    
    
    //recoil electron
    kin[0]=prot.P();
    kin[1]=prot.Theta()*DEG;
    kin[2]=prot.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,"p")) {
      cout << "p" << endl;      
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[1]->Fill(new_p/kin[0]-1);
    hnew_theta[1]->Fill(new_theta-kin[1]);
    hnew_phi[1]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    prot.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),prot.M());
//       cout << prot.P() << " " << prot.Theta()*DEG << " " << prot.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
     //decay neg
    kin[0]=em.P();
    kin[1]=em.Theta()*DEG;
    kin[2]=em.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
//     if (track.GetResolution(kin,res,"mu-")) {
//           cout << "mu-" << endl;
    if (track.GetResolution(kin,res,"e-")) {    
      cout << "e-" << endl;          
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[2]->Fill(new_p/kin[0]-1);
    hnew_theta[2]->Fill(new_theta-kin[1]);
    hnew_phi[2]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    em.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),em.M());
//       cout << em.P() << " " << em.Theta()*DEG << " " << em.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
    //decay pos
    kin[0]=ep.P();
    kin[1]=ep.Theta()*DEG;
    kin[2]=ep.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
//     if (track.GetResolution(kin,res,"mu+")) {
//       cout << "mu+" << endl;          
        if (track.GetResolution(kin,res,"e+")) {
      cout << "e+" << endl;          
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[3]->Fill(new_p/kin[0]-1);
    hnew_theta[3]->Fill(new_theta-kin[1]);
    hnew_phi[3]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    ep.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),ep.M());
//       cout << ep.P() << " " << ep.Theta()*DEG << " " << ep.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
}
    
// =========end of get resolution ==========================================     
    
    double MM=(ki+targ-kp-ep-em).M();
    
    double InvM_epm1=(ep+em).M();
    double InvM_epm2=(ep+kp).M();	
    double Qp2=InvM_epm1*InvM_epm1;    
      
    double Q2=-(ki-kp).M2();
    double W=(ki-kp+targ).M();
//         double W=(prot+ep+em).M();    
    //     double xbj=Q2/2/(ki*(ep+em)); ///wrong !!!!!!!
    double xbj=Q2/2./(targ*(ki-kp));
    
    double t=(prot-targ).M2();
    double delta2=t;    
    double m1=(ki-kp).M(),m2=targ.M(),m3=3.097,m4=prot.M();
    double s=W*W;
    
    double E1cm=(s+m1*m1-m2*m2)/(2*sqrt(s)),E3cm=(s+m3*m3-m4*m4)/(2*sqrt(s));
    double p1cm=sqrt(E1cm*E1cm-m1*m1),p3cm=sqrt(E3cm*E3cm-m3*m3);
    double tmin= -(pow(E1cm-E3cm,2) - pow(p1cm-p3cm,2));
    double tmax= -(pow(E1cm-E3cm,2) - pow(p1cm+p3cm,2));    
    
     double tau=Qp2*Qp2/(s-targ.M()*targ.M());
//       double eta=tau/(2-tau);   
//       double eta=Qp2/(2*s-2*M*M-Qp2);   //       tau/(2-tau)=Qp2/(2*s-2*M*M-Qp2)
//       double eta=Qp2/(2*(s-M*M)-Qp2-t);  //this is detailed defination  
//      double eta=Qp2/(2*s-Qp2);       //eta in TCS is similar to xi in DVCS 
     
     //according to DDVCS
     double xi=(Q2-Qp2+delta2/2.)/(2.*Q2/xbj-Q2-Qp2+delta2);
     double eta=-(Q2+Qp2)/(2.*Q2/xbj-Q2-Qp2+delta2);     
      
// cout << W << endl;
// cout << (kp+prot+ep+em).P() <<  " " << (kp+prot+ep+em).Theta() << endl;

    TLorentzVector LV_Recoil_lab=prot,LV_minus_lab=em,LV_plus_lab=ep,LV_el_in=ki,LV_el_out=kp;
     
    TVector3 Tang_plane_lab=((LV_Recoil_lab.Vect().Unit()).Cross((LV_minus_lab+LV_plus_lab).Vect().Unit() )).Unit();// final virtual photon x recoil proton	
    TVector3 Tang_el=((LV_el_in.Vect().Unit()).Cross(LV_el_out.Vect().Unit())).Unit();	
    //Phi_LH=Tang_el.Angle(Tang_plane); 
    double Phi_LH= TMath::ACos(Tang_el*Tang_plane_lab);
    if ((Tang_el*(LV_minus_lab+LV_plus_lab).Vect())<0.)Phi_LH=2*TMath::Pi()-Phi_LH;
		
    TLorentzVector LV_gamma_lab=LV_minus_lab+LV_plus_lab;
    TLorentzVector LV_plus_CMV=LV_plus_lab;
    LV_plus_CMV.Boost(-LV_gamma_lab.BoostVector());
    TLorentzVector LV_minus_CMV=LV_minus_lab;
    LV_minus_CMV.Boost(-LV_gamma_lab.BoostVector());

//     cout << "CMV " << LV_minus_CMV.Theta()*DEG << " " << 180-LV_plus_CMV.Theta()*DEG << " " << LV_minus_CMV.Phi()*DEG << " " << LV_plus_CMV.Phi()*DEG << endl;
    
    double Theta_CMV=LV_minus_CMV.Theta()*DEG;
    double Phi_CMV=LV_minus_CMV.Phi()*DEG;
    if (Phi_CMV<0) Phi_CMV=360+Phi_CMV;
           
// 4 Xbj (0.1-0.4), 6 tt (0.1-0.8), 6 Q2 (1-7), 6 Qp2 (2-9), 8 Phi_LH (0-2pi), 6 Theta_CMV(45-135),8 Phi_CMV(0-2pi),

    //scatPhiBool = TMath::Abs(kp.Phi()/D2R) < 40. && (TMath::Abs(prot.Phi()/D2R) < 30.);

    //scatPhiBool = TMath::Abs(kp.Phi()/D2R) < 40. && (TMath::Abs(prot.Phi()/D2R) > 150.);

    //scat_e_calo = ep.Angle(ki.Vect())/D2R < 45. && ep.Angle(ki.Vect())/D2R > 10.0 && em.Angle(ki.Vect())/D2R < 45. && em.Angle(ki.Vect())/D2R > 10.0;

    //   cout << em.Angle(ki.Vect())/D2R << endl;

//    if(scatPhiBool && scat_e_calo){

  //    if(kp.Angle(prot.Vect())/D2R > 25. || kp.Angle(prot.Vect())/D2R < 10.){
//	cout << "bad" << endl;
//      }

//      prot.RotateZ(pi1);

      //  hang_dist_scat_e->Fill(-(180.0 -kp.Theta()/D2R), kp.Phi()/D2R);
      //  hang_dist_scat_p->Fill(180.0 - prot.Theta()/D2R, prot.Phi()/D2R);

   // h2 is solid forward angle acceptance, h3 is largeangle
// 	double accet_cut=0;
// 	bool kp_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(kp.Theta()/D2R,kp.P())) > accet_cut;
// 	bool kp_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(kp.Theta()/D2R,kp.P())) > accet_cut;	
// 	bool ep_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(ep.Theta()/D2R,ep.P())) > accet_cut;
// 	bool ep_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(ep.Theta()/D2R,ep.P())) > accet_cut;
// 	bool em_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(em.Theta()/D2R,em.P())) > accet_cut;
// 	bool em_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(em.Theta()/D2R,em.P())) > accet_cut;
// 	bool prot_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(prot.Theta()/D2R,prot.P())) > accet_cut;
// 	bool prot_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(prot.Theta()/D2R,prot.P())) > accet_cut;	

// 	bool triggercut = true;
// 	if ((ep_accept_largeangle && ep.P() < 2.5) || (em_accept_largeangle && em.P() < 2.5) || (kp_accept_largeangle && kp.P() < 2.5)) triggercut=false;
// 
// 	    bool othercut= W < 4.44;
// 	    
// 	    bool cut=false;
// 	  if (conf_validation && ( (kp_accept_forwardangle || kp_accept_largeangle) && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle))) cut=true;
// 	  if (conf_4fold && (kp_accept_forwardangle && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle) && prot_accept_forwardangle) && othercut)  cut=true;
// 	  if (conf_3fold_NOp && (kp_accept_forwardangle && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle)) && othercut) cut=true;
// 	  if (conf_3fold_NOe && ((ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle) && prot_accept_forwardangle) && othercut) cut=true;
    
    if (fabs(xbj-0.1)<0.05 && fabs(-t-0.45)<0.1 && fabs(Q2-1.5)<0.1 && fabs(Qp2-4)<0.1){
//     cout << "bin " << xbj << " " << -t << " " << Q2 << " " << Qp2  << " " << Phi_LH << " " << Theta_CMV  << " " << Phi_CMV << endl;     
    xsec_thisbin += acc*effxsec;    
//       if(fabs(Phi_LH-1)<0.05 && fabs(Theta_CMV-30)<10 && fabs(Phi_CMV-30)<10) xsec_thisbin++;    
    }
      
      weight[0]=1;
      weight[1]=acc;
      weight[2]=acc*effxsec;
      weight[3]=acc*effxsec*count_convert;      
      
//      if (Q2<1) continue;     
//      if (Qp2<1) continue;          
//      if (Q2<Qp2) continue;     
//      if (W>3) continue;          
     

     {
// 	if ( 3 < Qp2 && Qp2 < 9 ) {      
// 	if (3.0 < InvM_epm1 && InvM_epm1 < 3.25) || (Is_inter && (3.0 < InvM_epm2 && InvM_epm2 < 3.25)) ) {
      
      for(Int_t k=0; k < m; k++){  
	if(k>0 && acc==0) continue;
	
	ht_Qp2_eta[k]->Fill(-eta,Qp2,-t,weight[k]);
	hQp2_eta[k]->Fill(-eta,Qp2,weight[k]);
	hQp2_t[k]->Fill(-t,Qp2,weight[k]);
	
	hThetaP[0][k]->Fill(kp.Theta()*DEG,kp.P(),weight[k]);
	hThetaP[1][k]->Fill(prot.Theta()*DEG,prot.P(),weight[k]);	
	hThetaP[2][k]->Fill(em.Theta()*DEG,em.P(),weight[k]);
	hThetaP[3][k]->Fill(ep.Theta()*DEG,ep.P(),weight[k]);

	hThetaPhi[0][k]->Fill(kp.Theta()*DEG,kp.Phi()*DEG,weight[k]);
	hThetaPhi[1][k]->Fill(prot.Theta()*DEG,prot.Phi()*DEG,weight[k]);	
	hThetaPhi[2][k]->Fill(em.Theta()*DEG,em.Phi()*DEG,weight[k]);
	hThetaPhi[3][k]->Fill(ep.Theta()*DEG,ep.Phi()*DEG,weight[k]);

	hdecayangle1[k]->Fill(ep.Theta()*DEG,em.Theta()*DEG,weight[k]);
	hdecayangle2[k]->Fill(ep.Theta()*DEG,kp.Theta()*DEG,weight[k]);		
// 	if (Is_inter) hdecayangle2[k]->Fill(ep.Theta()*DEG,kp.Theta()*DEG,weight[k]);	

	hdecaymom1[k]->Fill(ep.P(),em.P(),weight[k]);
	hdecaymom2[k]->Fill(ep.P(),kp.P(),weight[k]);		
// 	if (Is_inter) hdecaymom2[k]->Fill(ep.P(),kp.P(),weight[k]);	
	
	hlepIM_2D[k]->Fill(InvM_epm1,InvM_epm2,weight[k]);
	
	hlepIM1[k]->Fill(InvM_epm1,weight[k]);
	hlepIM2[k]->Fill(InvM_epm2,weight[k]);		
	hlepIM[k]->Fill(InvM_epm1,weight[k]);
	hlepIM[k]->Fill(InvM_epm2,weight[k]);

	hlepIM1_error[k]->Fill(InvM_epm1,weight[k]);
	hlepIM2_error[k]->Fill(InvM_epm2,weight[k]);		
	hlepIM_error[k]->Fill(InvM_epm1,weight[k]);
	hlepIM_error[k]->Fill(InvM_epm2,weight[k]);
	
// 	if (whichone==2) hlepIM[k]->Fill(InvM_epm1,weight[k]);
// 	else if (whichone==3) hlepIM[k]->Fill(InvM_epm2,weight[k]);
      }
	  
 	  if (acc_ep_FA>0) hPlog_plus_FA->Fill(log10(ep.P()),weight[2]*rate_convert/1e3);	  
 	  if (acc_em_FA>0) hPlog_minus_FA->Fill(log10(em.P()),weight[2]*rate_convert/1e3);
 	  if (acc_ep_LA>0) hPlog_plus_LA->Fill(log10(ep.P()),weight[2]*rate_convert/1e3);	  
	  if (acc_em_LA>0) hPlog_minus_LA->Fill(log10(em.P()),weight[2]*rate_convert/1e3);
      
	  hW->Fill(W,weight[3]);	  
	  hWstat->Fill(W,weight[3]);	    
	  htmin_W->Fill(W,tmin,weight[3]);    
	  htmax_W->Fill(W,tmax,weight[3]);
	  ht->Fill(-t,weight[3]);	  
	  
	  ht_Qp2->Fill(-t,Qp2,weight[3]);
	  ht_W->Fill(-t,W,weight[3]);
	  hQ2_W->Fill(Q2,W,weight[3]);	  
	  ht_Q2->Fill(-t,Q2,weight[3]);    	  	  
	  ht_eta->Fill(-t,-eta,weight[3]);  
	  ht_xi->Fill(-t,xi,weight[3]);	  
	  hxi_eta->Fill(xi,-eta,weight[3]);  
	  hxbj_eta->Fill(xbj,-eta,weight[3]);  
	  hxbj_xi->Fill(xbj,xi,weight[3]);
	  hxbj_Q2->Fill(xbj,Q2,weight[3]);
	  hQ2_Qp2->Fill(Q2,Qp2,weight[3]);

	  hMM->Fill(MM,weight[3]);	  	  
	  hMM_Q2->Fill(MM,Q2,weight[3]);		  
	  hMM_Qp2->Fill(MM,Qp2,weight[3]);	
	  hMM_t->Fill(MM,-t,weight[3]);		  
	  
	}
		
	  //      hkpth->Fill(180.0 -kp.Theta()/D2R, effxsec);
	  //   hprth->Fill(180.0 -prot.Theta()/D2R, effxsec);
// 	  hkpth->Fill(kp.Theta()/D2R, effxsec);
// 	  hprth->Fill(prot.Theta()/D2R, effxsec);
// 
// 	  hkpph->Fill(kp.Phi()/D2R, effxsec);
// 	  hprph->Fill(prot.Phi()/D2R, effxsec);
// 	  hkpp->Fill(kp.Vect().Mag(), effxsec);
// 	  hprp->Fill(prot.Vect().Mag(), effxsec);
// 
// 	  hepscat->Fill(sin(ep.Theta())*cos(ep.Phi()), sin(ep.Theta())*sin(ep.Phi()));
// 	  hemscat->Fill(sin(em.Theta())*cos(em.Phi()), sin(em.Theta())*sin(em.Phi()));   

//      cout << i << "\r"; 
//      cout << i << endl; 
  }
  
  cout << "counter " << counter1 << " " << counter2 << " " << counter3 << " " << counter4 << " " << counter5 << " " << counter6 <<  endl;

  cout << "xsec_thisbin " << xsec_thisbin << endl;
  
  TCanvas *c_ThetaP = new TCanvas("ThetaP","ThetaP",1200,900);
  c_ThetaP->Divide(4,m-2);
  for(int k=0;k<m-2;k++){
    for(int l=0;l<4;l++){
      gPad->SetLogz(1);
      c_ThetaP->cd(k*4+l+1);
      hThetaP[l][k]->Draw("colz");
      hThetaP[l][k]->SetAxisRange(thetamin,thetamax,"X");      
    }
  }
  
  TCanvas *c_ThetaP_final = new TCanvas("ThetaP_final","ThetaP_final",1200,900);
  c_ThetaP_final->Divide(2,2);
  for(int k=3;k<4;k++){
    for(int l=0;l<4;l++){
      c_ThetaP_final->cd(l+1);
      gPad->SetLogz(1);      
      hThetaP[l][k]->Draw("colz");
      hThetaP[l][k]->SetAxisRange(thetamin,thetamax,"X");      
    }
  }
  
  TCanvas *c_Plog = new TCanvas("Plog","Plog",1200,900);
  c_Plog->Divide(2,2);
  c_Plog->cd(1);  
  gPad->SetLogy(1);
  hPlog_plus_FA->Draw("colz");
TLegend* leg1 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);  
leg1->AddEntry(hPlog_plus_FA, Form("%02f",hPlog_plus_FA->Integral()),"l");  
leg1->Draw();    
  c_Plog->cd(2);  
  gPad->SetLogy(1);
  hPlog_minus_FA->Draw("colz");
TLegend* leg2 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg2->AddEntry(hPlog_minus_FA, Form("%02f",hPlog_minus_FA->Integral()),"l");  
leg2->Draw();    
  c_Plog->cd(3);  
  gPad->SetLogy(1);  
  hPlog_plus_LA->Draw("colz");
TLegend* leg3 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg3->AddEntry(hPlog_plus_LA, Form("%02f",hPlog_plus_LA->Integral()),"l");  
leg3->Draw();      
  c_Plog->cd(4);  
  gPad->SetLogy(1);
  hPlog_minus_LA->Draw("colz");
TLegend* leg4 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg4->AddEntry(hPlog_minus_LA, Form("%02f",hPlog_minus_LA->Integral()),"l");  
leg4->Draw();    

  TCanvas *c_ThetaPhi = new TCanvas("ThetaPhi","ThetaPhi",1200,900);
  c_ThetaPhi->Divide(4,m-2);
  for(int k=0;k<m-2;k++){
    for(int l=0;l<4;l++){
      gPad->SetLogz(1);
      c_ThetaPhi->cd(k*4+l+1);
      hThetaPhi[l][k]->Draw("colz");
      hThetaPhi[l][k]->SetAxisRange(thetamin,thetamax,"X");      
    }
  }
  
  
  TCanvas *c_decayangle1 = new TCanvas("decayangle1","decayangle1",1200,900);
  hdecayangle1[3]->Draw("colz");
  TCanvas *c_decayangle2 = new TCanvas("decayangle2","decayangle2",1200,900);
  hdecayangle2[3]->Draw("colz");  

  TCanvas *c_decaymom1 = new TCanvas("decaymom1","decaymom1",1200,900);
  hdecaymom1[3]->Draw("colz");
  TCanvas *c_decaymom2 = new TCanvas("decaymom2","decaymom2",1200,900);
  hdecaymom2[3]->Draw("colz");  
  
  TCanvas *c_lepIM1_xsec = new TCanvas("lepIM1_xsec","lepIM1_xsec",1200,900);
  hlepIM1[2]->SetTitle(";l^{+}l^{-} InvM (GeV);d#sigma (pb)/50MeV");  
  hlepIM1[2]->Draw();

  TCanvas *c_lepIM1_count = new TCanvas("lepIM1_count","lepIM1_count",1200,900);
  hlepIM1[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count/50MeV");    
  hlepIM1[3]->Draw();
  
  TCanvas *c_lepIM2_xsec = new TCanvas("lepIM2_xsec","lepIM2_xsec",1200,900);
  hlepIM2[2]->SetTitle(";l^{+}l^{-} InvM (GeV);d#sigma (pb)/50MeV");  
  hlepIM2[2]->Draw();

  TCanvas *c_lepIM2_count = new TCanvas("lepIM2_count","lepIM2_count",1200,900);
  hlepIM2[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count/50MeV");    
  hlepIM2[3]->Draw();  
  
  TCanvas *c_lepIM_xsec = new TCanvas("lepIM_xsec","lepIM_xsec",1200,900);
  hlepIM[2]->SetTitle(";l^{+}l^{-} InvM (GeV);d#sigma (pb)/50MeV");  
  hlepIM[2]->Draw();

  TCanvas *c_lepIM_count = new TCanvas("lepIM_count","lepIM_count",1200,900);
  hlepIM[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count/50MeV");    
  hlepIM[3]->Draw();

  TCanvas *c_lepIM = new TCanvas("lepIM","lepIM",1200,900);
  c_lepIM->Divide(4,m-2);
  for(int k=0;k<m-2;k++){
      c_lepIM->cd(k*4+1);
      hlepIM1[k]->Draw();
      c_lepIM->cd(k*4+2);
      hlepIM2[k]->Draw();
      c_lepIM->cd(k*4+3);
      hlepIM[k]->Draw();
      c_lepIM->cd(k*4+4);
      gPad->SetLogz(1);
      hlepIM_2D[k]->Draw("colz");   
  }    
  
  cout << "BH " <<  hlepIM[3]->Integral() << endl;
  
  TCanvas *c_lepIM1_error = new TCanvas("lepIM1_error","lepIM1_error",1200,900);
  hlepIM1_error[3]->SetTitle(";l^{+}l^{-} InvM (GeV);error(1/sqrt(count))/200MeV");    
  for (Int_t i=1;i<hlepIM1_error[3]->GetNbinsX();i++) {
    if (hlepIM1_error[3]->GetBinContent(i)>0){
      double error=1./sqrt(hlepIM1_error[3]->GetBinContent(i));
      hlepIM1_error[3]->SetBinContent(i,error);
    }
  }  
  hlepIM1_error[3]->Draw();  
  
TCanvas *c_t_Qp2_eta = new TCanvas("t_Qp2_eta","t_Qp2_eta",1600,800);
c_t_Qp2_eta->Divide(3,1);
c_t_Qp2_eta->cd(1);
gPad->SetLogz();
ht_Qp2_eta[0]->SetTitle("generated");
ht_Qp2_eta[0]->Draw("box");
c_t_Qp2_eta->cd(2);
gPad->SetLogz();
ht_Qp2_eta[1]->SetTitle("detected");
ht_Qp2_eta[1]->Draw("box");
c_t_Qp2_eta->cd(3);
gPad->SetLogz();
TH3F *hacc_t_Qp2_eta=(TH3F*)ht_Qp2_eta[1]->Clone();
hacc_t_Qp2_eta->Divide(ht_Qp2_eta[0]);
hacc_t_Qp2_eta->SetMinimum(0);
hacc_t_Qp2_eta->SetMaximum(1);
hacc_t_Qp2_eta->SetNameTitle("acc_t_Qp2_eta","acceptance");
hacc_t_Qp2_eta->Draw("box");

TCanvas *c_Qp2_eta = new TCanvas("Qp2_eta","Qp2_eta",1600,800);
c_Qp2_eta->Divide(3,1);
c_Qp2_eta->cd(1);
gPad->SetLogz();
hQp2_eta[0]->SetTitle("generated");
hQp2_eta[0]->Draw("colz");
c_Qp2_eta->cd(2);
gPad->SetLogz();
hQp2_eta[1]->SetTitle("detected");
hQp2_eta[1]->Draw("colz");
c_Qp2_eta->cd(3);
gPad->SetLogz();
TH2F *hacc_Qp2_eta=(TH2F*)hQp2_eta[1]->Clone();
hacc_Qp2_eta->Divide(hQp2_eta[0]);
hacc_Qp2_eta->SetMinimum(0);
hacc_Qp2_eta->SetMaximum(1);
hacc_Qp2_eta->SetNameTitle("acc_Qp2_eta","acceptance");
hacc_Qp2_eta->Draw("colz");

TCanvas *c_Qp2_t = new TCanvas("Qp2_t","Qp2_t",1600,800);
c_Qp2_t->Divide(3,1);
c_Qp2_t->cd(1);
gPad->SetLogz();
hQp2_t[0]->SetTitle("generated");
hQp2_t[0]->Draw("colz");
c_Qp2_t->cd(2);
gPad->SetLogz();
hQp2_t[1]->SetTitle("detected");
hQp2_t[1]->Draw("colz");
c_Qp2_t->cd(3);
gPad->SetLogz();
TH2F *hacc_Qp2_t=(TH2F*)hQp2_t[1]->Clone();
hacc_Qp2_t->Divide(hQp2_t[0]);
hacc_Qp2_t->SetMinimum(0);
hacc_Qp2_t->SetMaximum(1);
hacc_Qp2_t->SetNameTitle("acc_Qp2_t","acceptance");
hacc_Qp2_t->Draw("colz");

  TCanvas *c_kinematics = new TCanvas("kinematics","kinematics",1600,900);
  c_kinematics ->Divide(5,2);  
  c_kinematics ->cd(1);
  gPad->SetLogz(1);    
  ht_Qp2->Draw("colz");
  c_kinematics ->cd(2);
  gPad->SetLogz(1);    
  ht_W->Draw("colz");
  c_kinematics ->cd(3);
  gPad->SetLogz(1);    
  ht_Q2->Draw("colz");
  c_kinematics ->cd(4);
  gPad->SetLogz(1);    
  ht_eta->Draw("colz");
  c_kinematics ->cd(5);  
  gPad->SetLogz(1);  
  ht_xi->Draw("colz");
  c_kinematics ->cd(6);  
  gPad->SetLogz(1);  
  hxbj_Q2->Draw("colz");
  c_kinematics ->cd(7);  
  gPad->SetLogz(1);  
  hxbj_eta->Draw("colz");
  c_kinematics ->cd(8);  
  gPad->SetLogz(1);  
  hxbj_xi->Draw("colz");
  c_kinematics ->cd(9);  
  gPad->SetLogz(1);  
  hxi_eta->Draw("colz");
  c_kinematics ->cd(10);  
  gPad->SetLogz(1);  
  hQ2_Qp2->Draw("colz");
  
  TCanvas *c_kinematics_final = new TCanvas("kinematics_final","kinematics_final",1200,900);
  c_kinematics_final->Divide(2,2);   
  c_kinematics_final->cd(1);  
  gPad->SetLogz(1);  
  hxbj_Q2->Draw("colz");
  c_kinematics_final->cd(2);  
  gPad->SetLogz(1);  
  hxi_eta->Draw("colz");
  c_kinematics_final->cd(3);  
  gPad->SetLogz(1);  
  hQ2_Qp2->Draw("colz");
  c_kinematics_final->cd(4);  
  gPad->SetLogz(1);  
  ht_Qp2->Draw("colz");  
  
  TCanvas *c_Q2_W = new TCanvas("Q2_W","Q2_W",1200,900);
  gPad->SetLogz(1);    
  hQ2_W->Draw("colz"); 

  TCanvas *c_resolution = new TCanvas("resolution","resolution",1600,900);
  c_resolution->Divide(3,4);
  for(int k=0;k<m;k++){
      c_resolution->cd(k*3+1);
      hnew_p[k]->Draw();
      c_resolution->cd(k*3+2);
      hnew_theta[k]->Draw();
      c_resolution->cd(k*3+3);
      hnew_phi[k]->Draw();      
  }
  
  TCanvas *c_MM = new TCanvas("MM","MM",1600,900);
  c_MM->Divide(2,2);    
  c_MM->cd(1); 
  hMM->Draw();
  hMM->Fit("gaus");
  c_MM->cd(2);  
  hMM_t->Draw("colz");  
  c_MM->cd(3);  
  hMM_Q2->Draw("colz");    
  c_MM->cd(4);  
  hMM_Qp2->Draw("colz");  
  
//   TCanvas *can12 = new TCanvas("can12","",1200,900);
//   gStyle->SetOptStat(0);  
//   gStyle->SetTitleSize(0.1,"X");
//   gStyle->SetTitleSize(0.1,"Y");
//   can12->SetFillColor(10);
//   hlepIM_count->SetTitle("BH event counts VS e+ e- Inv Mass");
//   hlepIM_count->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
//   hlepIM_count->GetYaxis()->SetTitle("counts /50 MeV for 50 days");
// //   hlepIM_count->SetTitleSize(0.1);
//   hlepIM_count->Rebin(5);  
//   hlepIM_count->Draw();
//   hlepIM_count->SetLineWidth(3.5);

//   TCanvas *can = new TCanvas("can","can",1200,900);
//   can->Divide(3,2);  
//   can->cd(1);
//   hW->GetXaxis()->SetTitle("W");
//   hW->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
//   hW->Draw();  
//   can->cd(2);
//   hWstat->GetXaxis()->SetTitle("Wstat");
//   hWstat->GetYaxis()->SetTitle("number of event per day/ 10MeV");
//   hWstat->Draw();   
//   can->cd(3);
//   hQp2W->Draw("colz");
//   can->cd(4);
//   htW->Draw("colz");
//   can->cd(5);
//   htminW->Draw("colz");
//   htmaxW->Draw("colz same");  
//   can->cd(6);
//   ht->Draw();
  
//   TCanvas *can4 = new TCanvas("can4","can4",1200,800);
//   can4->Divide(3,2);
//   can4->cd(1);
//   hkpth->GetXaxis()->SetTitle("scattered electron #theta_{SHRS} (deg)");
//   hkpth->Draw();
//   can4->cd(4);
//   hprth->GetXaxis()->SetTitle("recoiling proton #theta_{HRS} (deg)");
//   hprth->Draw();
//   can4->cd(2);
//   hkpph->GetXaxis()->SetTitle("scattered electron #phi_{lab} (deg)");
//   hkpph->Draw();
//   can4->cd(5);
//   hprph->GetXaxis()->SetTitle("recoiling proton #phi_{lab} (deg)");
//   hprph->Draw();
//   can4->cd(3);
//   hkpp->GetXaxis()->SetTitle("scattered electron momentum (GeV)");
//   hkpp->Draw();
//   can4->cd(6);
//   hprp->GetXaxis()->SetTitle("recoiling proton momentum (GeV)");
//   hprp->Draw();
//   
//   TCanvas *can5 = new TCanvas("can5","",900,900);
//   hemscat->SetMarkerColor(kRed);
//   hepscat->SetMarkerColor(kBlue);
//   hepscat->GetXaxis()->SetTitle("x_{lab}");
//   hepscat->GetXaxis()->SetTitle("y_{lab}");
//   hepscat->Draw();
//   hemscat->Draw("same");

//   cout << "BH 3-3.25 GeV " <<  hlepIM2->Integral(20,45) << endl;  //pure sum to count , no width
  cout << "BH 2-3 GeV " <<  hlepIM[3]->Integral(40,60) << endl;  //pure sum to count , no width  
     
outputfile->Write();
outputfile->Flush();      

}
