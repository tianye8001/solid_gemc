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
#include <TArc.h>

using namespace std;

// int table(string filename)
int table()
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const double DEG=180./3.1415926;

//8 Egamma (5-11), 8 tt (0.1-1), 8 Qp2 (4-9), 10 Phi_CMV(0-2pi), 15 Theta_CMV(45-135)
const int Nbin_Egamma=8,Nbin_tt=8,Nbin_Qp2=8,Nbin_Phi_CMV=10,Nbin_Theta_CMV=15;

Double_t gen[Nbin_Egamma][Nbin_tt][Nbin_Qp2][Nbin_Phi_CMV][Nbin_Theta_CMV];
Double_t acc_3fold_recoildecaypair[Nbin_Egamma][Nbin_tt][Nbin_Qp2][Nbin_Phi_CMV][Nbin_Theta_CMV];
Double_t acc_3fold_eloutdecaypair[Nbin_Egamma][Nbin_tt][Nbin_Qp2][Nbin_Phi_CMV][Nbin_Theta_CMV];
Double_t acc_4fold[Nbin_Egamma][Nbin_tt][Nbin_Qp2][Nbin_Phi_CMV][Nbin_Theta_CMV];

for (Int_t a1=0;a1<Nbin_Egamma;a1++) {
  for (Int_t a2=0;a2<Nbin_tt;a2++) {
    for (Int_t a3=0;a3<Nbin_Qp2;a3++) {
      for (Int_t a4=0;a4<Nbin_Phi_CMV;a4++) {
	for (Int_t a5=0;a5<Nbin_Theta_CMV;a5++) {
	  gen[a1][a2][a3][a4][a5]=0;	  
	  acc_3fold_recoildecaypair[a1][a2][a3][a4][a5]=0;
	  acc_3fold_eloutdecaypair[a1][a2][a3][a4][a5]=0;
	  acc_4fold[a1][a2][a3][a4][a5]=0;
//   cout << " " <<  a1 <<  " " << a2<< " " << a3 << " " <<a4 << " " << a5 << " " << "\r";  	  
	}
      }
    }
  }
}

// string type;
// string treename;
// int pid_decay;
// double mass_decay;
// if (filename.find("CLAS12_TCS_FTSetup_ele",0) != string::npos) {
//   type="CLAS12_TCS_FTSetup_ele";
//   pid_decay=11;mass_decay=0.000511;
//   treename="TCS_Tree";
// }
// else if (filename.find("SoLID_TCS_JPsiSetup_ele",0) != string::npos) {
//   type="SoLID_TCS_JPsiSetup_ele";
//   pid_decay=11;mass_decay=0.000511;
//   treename="TCS_Tree";
// }
// else if (filename.find("SoLID_DDVCS_JPsiSetup_muon",0) != string::npos) {
//   type="SoLID_DDVCS_JPsiSetup_muon";
//   pid_decay=13;mass_decay=0.10567;
//   treename="DDVCS_Tree";
// }
// else {cout << "not sure what type" << endl; return 0;}

string type="SoLID_TCS_JPsiSetup_ele";
string treename="TCS_Tree";

string filename[10]={
"TCSfiles/TCS_electroprod_100_SoLID_TCS_JPsiSetup_ele.root",  
"TCSfiles/TCS_electroprod_101_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_102_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_103_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_104_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_105_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_106_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_107_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_108_SoLID_TCS_JPsiSetup_ele.root",
"TCSfiles/TCS_electroprod_109_SoLID_TCS_JPsiSetup_ele.root",
};

//start of looping through file list
for (Int_t j=0;j<10;j++) {
  
TFile *file=new TFile(filename[j].c_str());
if (file->IsZombie()) {
  cout << "Error opening file" << filename[j] << endl;
  exit(-1);
}
else cout << "open file " << filename[j] << endl;
 
TTree *T = (TTree*) file->Get(treename.c_str());

Long64_t EventNumber;
Int_t VirtualFlag;
Double_t ALV_minus_lab[4],ALV_plus_lab[4],ALV_gamma_in[4],ALV_el_in[4],ALV_Recoil_lab[4],ALV_el_out[4];
Double_t AV_PolTarget[3],AV_PolBeam[3],AV_PolBeam_Lin[3];
Double_t Q2,theta_beam,phi_beam,yy,Qp2,tt,RotAxis,Psi_p,Psi_g,ttmin,Phi_CMV,Theta_CMV,Egamma;
Double_t cross_tot,cross_tot_unpol,cross_BH,cross_TCS;
Double_t W_tot,W_tot_unpol,W_BH,W_TCS;
Double_t DeltaBin,LinPol,CircPol,TargetPol,Flux_qr,Flux_bmr,epsilon;
Double_t Abeam_polcirc,Abeam_pollin,Atarget_long,Atarget_trans,Atarget_trans_2,A_circ_long,A_circ_trans,A_circ_trans_2,A_lin_long,A_lin_trans,A_lin_trans_2;

T->SetBranchAddress("ALV_minus_lab",ALV_minus_lab);
T->SetBranchAddress("ALV_plus_lab",&ALV_plus_lab);
T->SetBranchAddress("ALV_gamma_in",&ALV_gamma_in);
T->SetBranchAddress("ALV_el_in",&ALV_el_in);
T->SetBranchAddress("ALV_Recoil_lab",&ALV_Recoil_lab);
T->SetBranchAddress("ALV_el_out",&ALV_el_out);
// T->SetBranchAddress("AV_PolTarget",&AV_PolTarget);
// T->SetBranchAddress("AV_PolBeam",&AV_PolBeam);
// T->SetBranchAddress("AV_PolBeam_Lin",&AV_PolBeam_Lin);
T->SetBranchAddress("Q2",&Q2);
// T->SetBranchAddress("theta_beam",&theta_beam);
// T->SetBranchAddress("phi_beam",&phi_beam);
// T->SetBranchAddress("yy",&yy);
T->SetBranchAddress("Qp2",&Qp2);
T->SetBranchAddress("tt",&tt);
// T->SetBranchAddress("RotAxis",&RotAxis);
// T->SetBranchAddress("Psi_p",&Psi_p);
// T->SetBranchAddress("Psi_g",&Psi_g);
// T->SetBranchAddress("ttmin",&ttmin);
T->SetBranchAddress("Phi_CMV",&Phi_CMV);
T->SetBranchAddress("Theta_CMV",&Theta_CMV);
T->SetBranchAddress("Egamma",&Egamma);
// T->SetBranchAddress("cross_tot",&cross_tot);
// T->SetBranchAddress("cross_tot_unpol",&cross_tot_unpol);
// T->SetBranchAddress("cross_BH",&cross_BH);
// T->SetBranchAddress("cross_TCS",&cross_TCS);
// T->SetBranchAddress("W_tot",&W_tot);
// T->SetBranchAddress("W_tot_unpol",&W_tot_unpol);
T->SetBranchAddress("W_BH",&W_BH);
// T->SetBranchAddress("W_TCS",&W_TCS);
// T->SetBranchAddress("DeltaBin",&DeltaBin);
// T->SetBranchAddress("LinPol",&LinPol);
// T->SetBranchAddress("CircPol",&CircPol);
// T->SetBranchAddress("TargetPol",&TargetPol);
// T->SetBranchAddress("VirtualFlag",&VirtualFlag);
// T->SetBranchAddress("Flux_qr",&Flux_qr);
// T->SetBranchAddress("Flux_bmr",&Flux_bmr);
// T->SetBranchAddress("epsilon",&epsilon);
// T->SetBranchAddress("Abeam_polcirc",&Abeam_polcirc);
// T->SetBranchAddress("Abeam_pollin",&Abeam_pollin);
// T->SetBranchAddress("Atarget_long",&Atarget_long);
// T->SetBranchAddress("Atarget_trans",&Atarget_trans);
// T->SetBranchAddress("Atarget_trans_2",&Atarget_trans_2);
// T->SetBranchAddress("A_circ_long",&A_circ_long);
// T->SetBranchAddress("A_circ_trans",&A_circ_trans);
// T->SetBranchAddress("A_circ_trans_2",&A_circ_trans_2);
// T->SetBranchAddress("A_lin_long",&A_lin_long);
// T->SetBranchAddress("A_lin_trans",&A_lin_trans);
// T->SetBranchAddress("A_lin_trans_2",&A_lin_trans_2);
T->SetBranchAddress("EventNumber", &EventNumber);

Double_t accep_el_out_1,accep_minus_1,accep_plus_1,accep_recoil_1;
Double_t accep_el_out_2,accep_minus_2,accep_plus_2,accep_recoil_2;
Double_t accep_3fold_recoildecaypair;
Double_t accep_3fold_eloutdecaypair;
Double_t accep_4fold;

T->SetBranchAddress("accep_3fold_recoildecaypair", &accep_3fold_recoildecaypair);
T->SetBranchAddress("accep_3fold_eloutdecaypair", &accep_3fold_eloutdecaypair);
T->SetBranchAddress("accep_4fold", &accep_4fold);

// cout << endl << "ok" << endl;

int counter_outside=0;

//  loop on entries
Int_t nentries = T->GetEntries();
cout << "nentries " << nentries << endl;

for (Int_t i=0;i<nentries;i++) {
// for (Int_t i=0;i<5;i++) {
  cout << i << "\r";    
//   cout << "EventNumber " << EventNumber << "\r";   
  
  T->GetEvent(i);
  int bin_Egamma=int((Egamma-5)/((11.-5.)/Nbin_Egamma));
  int bin_tt=int((-tt-0.1)/((1.-0.1)/Nbin_tt));
  int bin_Qp2=int((Qp2-4.)/((9.-4.)/Nbin_Qp2));  
  int bin_Phi_CMV=int((Phi_CMV*DEG-0.)/((360.-0.)/Nbin_Phi_CMV));
  int bin_Theta_CMV=int((Theta_CMV*DEG-45)/((135.-45.)/Nbin_Theta_CMV)); 

//   if (bin_Qp2>0){
//   cout << "value " << Egamma <<  " " << -tt<< " " << Qp2 << " " <<Phi_CMV*DEG << " " << Theta_CMV*DEG << " " << "\n";    
//   cout << "bin " <<  bin_Egamma <<  " " << bin_tt<< " " << bin_Qp2 << " " <<bin_Phi_CMV << " " << bin_Theta_CMV << " " << "\n";  
//       cout << "accep " <<  accep_3fold_recoildecaypair <<  " " << accep_3fold_eloutdecaypair << " " << accep_4fold << "\n";  
//   }
  
  if ((bin_Egamma<Nbin_Egamma && bin_tt<Nbin_tt && bin_Qp2<Nbin_Qp2 &&  bin_Phi_CMV<Nbin_Phi_CMV && bin_Theta_CMV<Nbin_Theta_CMV) && (0<=bin_Egamma && 0<=bin_tt && 0<=bin_Qp2 &&  0<=bin_Phi_CMV && 0<=bin_Theta_CMV)){  
	  gen[bin_Egamma][bin_tt][bin_Qp2][bin_Phi_CMV][bin_Theta_CMV] +=1;  
	  acc_3fold_recoildecaypair[bin_Egamma][bin_tt][bin_Qp2][bin_Phi_CMV][bin_Theta_CMV] += accep_3fold_recoildecaypair;
	  acc_3fold_eloutdecaypair[bin_Egamma][bin_tt][bin_Qp2][bin_Phi_CMV][bin_Theta_CMV] +=accep_3fold_eloutdecaypair;
	  acc_4fold[bin_Egamma][bin_tt][bin_Qp2][bin_Phi_CMV][bin_Theta_CMV] +=accep_4fold;
  }
  else counter_outside++;
        
}

cout << endl << "counter_outside " << counter_outside << endl;    

file->Close();
}
//end of looping through file list

int Nbin=Nbin_Egamma*Nbin_tt*Nbin_Qp2*Nbin_Phi_CMV*Nbin_Theta_CMV;
TH1F *hacc_3fold_recoildecaypair=new TH1F("acc_3fold_recoildecaypair","acc_3fold_recoildecaypair",Nbin,0,Nbin);
TH1F *hacc_3fold_eloutdecaypair=new TH1F("acc_3fold_eloutdecaypair","acc_3fold_eloutdecaypair",Nbin,0,Nbin);
TH1F *hacc_4fold=new TH1F("acc_4fold","acc_4fold",Nbin,0,Nbin);
TH1F *hNgen=new TH1F("Ngen","Ngen",Nbin,0,Nbin);

ofstream OUT(Form("table_%s.dat",type.c_str()));

int counter=0;
for (Int_t a1=0;a1<Nbin_Egamma;a1++) {
  for (Int_t a2=0;a2<Nbin_tt;a2++) {
    for (Int_t a3=0;a3<Nbin_Qp2;a3++) {
      for (Int_t a4=0;a4<Nbin_Phi_CMV;a4++) {
	for (Int_t a5=0;a5<Nbin_Theta_CMV;a5++) {	  
	  double b1=0,b2=0,b3=0;
	  if (gen[a1][a2][a3][a4][a5]>0) {
	    b1=acc_3fold_recoildecaypair[a1][a2][a3][a4][a5]/gen[a1][a2][a3][a4][a5];
	    b2=acc_3fold_eloutdecaypair[a1][a2][a3][a4][a5]/gen[a1][a2][a3][a4][a5];
	    b3=acc_4fold[a1][a2][a3][a4][a5]/gen[a1][a2][a3][a4][a5];
	  }	  
	  OUT << a1 << "\t" << a2 << "\t" << a3 << "\t" << a4 << "\t" << a5 << "\t";
	  OUT << b1 << "\t" << b1 << "\t" << b1 << "\t";
	  OUT << gen[a1][a2][a3][a4][a5] << "\n"; 
	  
	  counter++;
	  hacc_3fold_recoildecaypair->Fill(counter,b1);
	  hacc_3fold_eloutdecaypair->Fill(counter,b2);
	  hacc_4fold->Fill(counter,b3);
	  hNgen->Fill(counter,gen[a1][a2][a3][a4][a5]);
	}
      }
    }
  }
}

OUT.close();

TCanvas *c = new TCanvas("c","c",1200,900);
c->Divide(1,2);
c->cd(2);
hNgen->Draw();
c->cd(1);
hacc_3fold_recoildecaypair->SetLineColor(kBlack);
hacc_3fold_recoildecaypair->Draw();
hacc_3fold_eloutdecaypair->SetLineColor(kRed);
hacc_3fold_eloutdecaypair->Draw("same");
hacc_4fold->SetLineColor(kBlue);
hacc_4fold->Draw("same");
    
}