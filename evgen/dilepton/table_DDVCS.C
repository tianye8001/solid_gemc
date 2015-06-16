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
int table_DDVCS()
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const double DEG=180./3.1415926;
//4 Xbj (0.1-0.4), 6 tt (0.1-0.8), 6 Q2 (1-7), 6 Qp2 (2-9), 8 Phi_LH (0-2pi), 6 Theta_CMV(45-135),8 Phi_CMV(0-2pi),
const int Nbin_Xbj=4,Nbin_tt=6,Nbin_Q2=6,Nbin_Qp2=6,Nbin_Phi_LH=8,Nbin_Theta_CMV=6,Nbin_Phi_CMV=8;

Double_t gen[Nbin_Xbj][Nbin_tt][Nbin_Q2][Nbin_Qp2][Nbin_Phi_LH][Nbin_Theta_CMV][Nbin_Phi_CMV];
Double_t acc_3fold_recoildecaypair[Nbin_Xbj][Nbin_tt][Nbin_Q2][Nbin_Qp2][Nbin_Phi_LH][Nbin_Theta_CMV][Nbin_Phi_CMV];
Double_t acc_3fold_eloutdecaypair[Nbin_Xbj][Nbin_tt][Nbin_Q2][Nbin_Qp2][Nbin_Phi_LH][Nbin_Theta_CMV][Nbin_Phi_CMV];
Double_t acc_4fold[Nbin_Xbj][Nbin_tt][Nbin_Q2][Nbin_Qp2][Nbin_Phi_LH][Nbin_Theta_CMV][Nbin_Phi_CMV];

for (Int_t a1=0;a1<Nbin_Xbj;a1++) {
  for (Int_t a2=0;a2<Nbin_tt;a2++) {
    for (Int_t a3=0;a3<Nbin_Q2;a3++) {
    for (Int_t a4=0;a4<Nbin_Qp2;a4++) {      
      for (Int_t a5=0;a5<Nbin_Phi_LH;a5++) {      
      for (Int_t a6=0;a6<Nbin_Theta_CMV;a6++) {
	for (Int_t a7=0;a7<Nbin_Phi_CMV;a7++) {
	  gen[a1][a2][a3][a4][a5][a6][a7]=0;	  
	  acc_3fold_recoildecaypair[a1][a2][a3][a4][a5][a6][a7]=0;
	  acc_3fold_eloutdecaypair[a1][a2][a3][a4][a5][a6][a7]=0;
	  acc_4fold[a1][a2][a3][a4][a5][a6][a7]=0;
//   cout << " " <<  a1 <<  " " << a2<< " " << a3 << " " <<a4 << " " << a5 << " " << "\r";  	  
	}
      }
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

string type="SoLID_DDVCS_JPsiSetup_muon"; 
string treename="DDVCS_Tree";

string filename[10]={
"DDVCSfiles/DDVCS_electroprod_muons_10_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_11_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_12_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_13_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_14_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_15_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_16_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_17_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_18_SoLID_DDVCS_JPsiSetup_muon.root",
"DDVCSfiles/DDVCS_electroprod_muons_19_SoLID_DDVCS_JPsiSetup_muon.root",
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
Double_t Q2,theta_beam,phi_beam,yy,Qp2,tt,RotAxis,Psi_p,Psi_g,ttmin,Phi_CMV,Theta_CMV;
Double_t cross_tot,cross_tot_unpol,cross_BH,cross_TCS;
Double_t W_tot,W_tot_unpol,W_BH,W_TCS;
Double_t DeltaBin,LinPol,CircPol,TargetPol,Flux_qr,Flux_bmr,epsilon;
Double_t Abeam_polcirc,Abeam_pollin,Atarget_long,Atarget_trans,Atarget_trans_2,A_circ_long,A_circ_trans,A_circ_trans_2,A_lin_long,A_lin_trans,A_lin_trans_2;

Double_t Xbj,Phi_LH,W_DDVCS; //special entry for DDVCS_Tree

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
// T->SetBranchAddress("Xbj",&Xbj);
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

 //special entry for DDVCS_Tree
T->SetBranchAddress("Xbj",&Xbj);
T->SetBranchAddress("Phi_LH",&Phi_LH);
T->SetBranchAddress("W_DDVCS",&W_DDVCS);

Double_t accep_el_out_1,accep_minus_1,accep_plus_1,accep_recoil_1;
Double_t accep_el_out_2,accep_minus_2,accep_plus_2,accep_recoil_2;
Double_t accep_3fold_recoildecaypair;
Double_t accep_3fold_eloutdecaypair;
Double_t accep_4fold;

T->SetBranchAddress("accep_3fold_recoildecaypair", &accep_3fold_recoildecaypair);
T->SetBranchAddress("accep_3fold_eloutdecaypair", &accep_3fold_eloutdecaypair);
T->SetBranchAddress("accep_4fold", &accep_4fold);



int counter_outside=0;

//  loop on entries
Int_t nentries = T->GetEntries();
cout << "nentries " << nentries << endl;

for (Int_t i=0;i<nentries;i++) {
// for (Int_t i=0;i<5;i++) {
  cout << i << "\r";    
//   cout << "EventNumber " << EventNumber << "\r";   
  
  T->GetEvent(i);
  int bin_Xbj=int((Xbj-0.1)/((0.4-0.1)/Nbin_Xbj));
  int bin_tt=int((-tt-0.1)/((0.8-0.1)/Nbin_tt));
  int bin_Q2=int((Q2-1.)/((7.-1.)/Nbin_Q2));    
  int bin_Qp2=int((Qp2-2.)/((9.-2.)/Nbin_Qp2));  
  int bin_Phi_LH=int((Phi_LH*DEG-0.)/((360.-0.)/Nbin_Phi_LH));  
  int bin_Theta_CMV=int((Theta_CMV*DEG-45)/((135.-45.)/Nbin_Theta_CMV)); 
  int bin_Phi_CMV=int((Phi_CMV*DEG-0.)/((360.-0.)/Nbin_Phi_CMV));  

//   if (bin_Qp2>0){
//   cout << "value " << Xbj <<  " " << -tt<< " " << Qp2 << " " <<Phi_CMV*DEG << " " << Theta_CMV*DEG << " " << "\n";    
//   cout << "bin " <<  bin_Xbj <<  " " << bin_tt<< " " << bin_Qp2 << " " <<bin_Phi_CMV << " " << bin_Theta_CMV << " " << "\n";  
//       cout << "accep " <<  accep_3fold_recoildecaypair <<  " " << accep_3fold_eloutdecaypair << " " << accep_4fold << "\n";  
//   }
  
  if ((bin_Xbj<Nbin_Xbj && bin_tt<Nbin_tt && bin_Q2<Nbin_Q2 && bin_Qp2<Nbin_Qp2 &&  bin_Phi_LH<Nbin_Phi_LH && bin_Theta_CMV<Nbin_Theta_CMV &&  bin_Phi_CMV<Nbin_Phi_CMV) && (0<=bin_Xbj && 0<=bin_tt && 0<=bin_Q2 && 0<=bin_Qp2 &&  0<=bin_Phi_LH && 0<=bin_Theta_CMV &&  0<=bin_Phi_CMV)){  
	  gen[bin_Xbj][bin_tt][bin_Q2][bin_Qp2][bin_Phi_LH][bin_Theta_CMV][bin_Phi_CMV] +=1;  
	  acc_3fold_recoildecaypair[bin_Xbj][bin_tt][bin_Q2][bin_Qp2][bin_Phi_LH][bin_Theta_CMV][bin_Phi_CMV] += accep_3fold_recoildecaypair;
	  acc_3fold_eloutdecaypair[bin_Xbj][bin_tt][bin_Q2][bin_Qp2][bin_Phi_LH][bin_Theta_CMV][bin_Phi_CMV] +=accep_3fold_eloutdecaypair;
	  acc_4fold[bin_Xbj][bin_tt][bin_Q2][bin_Qp2][bin_Phi_LH][bin_Theta_CMV][bin_Phi_CMV] +=accep_4fold;
  }
  else counter_outside++;
        
}

cout << endl << "counter_outside " << counter_outside << endl;    

file->Close();
}
//end of looping through file list

int Nbin=Nbin_Xbj*Nbin_tt*Nbin_Q2*Nbin_Qp2*Nbin_Phi_LH*Nbin_Theta_CMV*Nbin_Phi_CMV;
TH1F *hacc_3fold_recoildecaypair=new TH1F("acc_3fold_recoildecaypair","acc_3fold_recoildecaypair",Nbin,0,Nbin);
TH1F *hacc_3fold_eloutdecaypair=new TH1F("acc_3fold_eloutdecaypair","acc_3fold_eloutdecaypair",Nbin,0,Nbin);
TH1F *hacc_4fold=new TH1F("acc_4fold","acc_4fold",Nbin,0,Nbin);
TH1F *hNgen=new TH1F("Ngen","Ngen",Nbin,0,Nbin);

ofstream OUT(Form("table_%s.dat",type.c_str()));

int counter=0;
for (Int_t a1=0;a1<Nbin_Xbj;a1++) {
  for (Int_t a2=0;a2<Nbin_tt;a2++) {
    for (Int_t a3=0;a3<Nbin_Q2;a3++) {
    for (Int_t a4=0;a4<Nbin_Qp2;a4++) {      
      for (Int_t a5=0;a5<Nbin_Phi_LH;a5++) {      
      for (Int_t a6=0;a6<Nbin_Theta_CMV;a6++) {
	for (Int_t a7=0;a7<Nbin_Phi_CMV;a7++) {
	  double b1=0,b2=0,b3=0;
	  if (gen[a1][a2][a3][a4][a5][a6][a7]>0) {
	    b1=acc_3fold_recoildecaypair[a1][a2][a3][a4][a5][a6][a7]/gen[a1][a2][a3][a4][a5][a6][a7];
	    b2=acc_3fold_eloutdecaypair[a1][a2][a3][a4][a5][a6][a7]/gen[a1][a2][a3][a4][a5][a6][a7];
	    b3=acc_4fold[a1][a2][a3][a4][a5][a6][a7]/gen[a1][a2][a3][a4][a5][a6][a7];
	  }	  
	  OUT << a1 << "\t" << a2 << "\t" << a3 << "\t" << a4 << "\t" << a5 << "\t" << a6 << "\t" << a7 << "\t";
	  OUT << b1 << "\t" << b2 << "\t" << b3 << "\t";
	  OUT << gen[a1][a2][a3][a4][a5][a6][a7] << "\n"; 
	  
	  counter++;
	  hacc_3fold_recoildecaypair->Fill(counter,b1);
	  hacc_3fold_eloutdecaypair->Fill(counter,b2);
	  hacc_4fold->Fill(counter,b3);
	  hNgen->Fill(counter,gen[a1][a2][a3][a4][a5][a6][a7]);
	}
      }
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
hacc_3fold_recoildecaypair->SetTitle("acc_3fold_recoildecaypair in black,acc_3fold_eloutdecaypair in red,acc_4fold in blue");
hacc_3fold_eloutdecaypair->SetLineColor(kRed);
hacc_3fold_eloutdecaypair->Draw("same");
hacc_4fold->SetLineColor(kBlue);
hacc_4fold->Draw("same");
c->SaveAs(Form("table_%s.png",type.c_str()));
}