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

int accep(string output_filename)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const double DEG=180./3.1415926;
// const double DEG=1;

string type;
string treename;
int pid_decay;
double mass_decay;
if (output_filename.find("SoLID_TCS_ele",0) != string::npos) {
  type="SoLID_TCS_ele";
  pid_decay=11;mass_decay=0.000511;
  treename="TCS_Tree";
}
else if (output_filename.find("SoLID_DDVCS_muon",0) != string::npos) {
  type="SoLID_DDVCS_muon";
  pid_decay=13;mass_decay=0.10567;
  treename="DDVCS_Tree";
}
else {cout << "not sure what type" << endl; return 0;}

char *title_cut[5]={"gen","accep_individual","accep_3fold_recoildecaypair","accep_3fold_eloutdecaypair","accep_4fold"};
char *title_par[4]={"scattered e^{-}","recoil p","decay e^{-}","decay e^{+}"};  
TH2F *h[5][4];
for(int i=0;i<5;i++){
  for(int j=0;j<4;j++){    
   char hstname[100];  
   sprintf(hstname,"ThetaP_%i%i",i,j);   
   h[i][j]=new TH2F(hstname,hstname,100,0,100,220,0,11);
   h[i][j]->SetTitle(Form("BH, %s, %s;#theta (deg);P(GeV)",title_par[j],title_cut[i]));
  }
}

  TFile *acceptancefile=new TFile("acceptance_solid_JPsi_electron_target315_output.root");    
  TH2F *hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
  TH2F *hacceptance_ThetaP_largeangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_largeangle");
  TCanvas *c_acceptance_solid = new TCanvas("acceptance_solid","acceptance_solid",1200,900);
  c_acceptance_solid->Divide(2,1);
  c_acceptance_solid->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  c_acceptance_solid->cd(2);
  hacceptance_ThetaP_largeangle->Draw("colz");  

  TFile *acceptancefile_muon=new TFile("acceptance_solid_DDVCS_JPsi_LH2_muonp_target315_output.root");    
  TH2F *hacceptance_ThetaP_forwardangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_forwardangle");  
  TH2F *hacceptance_ThetaP_largeangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_largeangle");  
  TCanvas *c_acceptance_muon_solid = new TCanvas("acceptance_muon_solid","acceptance_muon_solid",1200,900);
  c_acceptance_muon_solid->Divide(2,1);
  c_acceptance_muon_solid->cd(1);
  hacceptance_ThetaP_forwardangle_muon->Draw("colz");
  c_acceptance_muon_solid->cd(2);
  hacceptance_ThetaP_largeangle_muon->Draw("colz"); 

// char output_filename[200];
// sprintf(output_filename,"%s_accep.root",input_filename.substr(0,input_filename.rfind(".")).c_str());

// cout << "copy " << input_filename << " to " << output_filename << endl;
// gSystem->Exec(Form("cp -f %s %s",input_filename.c_str(),output_filename.c_str()));

TFile *file=new TFile(output_filename.c_str(),"update");
if (file->IsZombie()) {
  cout << "Error opening file" << output_filename << endl;
  exit(-1);
}
else cout << "open file " << output_filename << endl;
 
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
// T->SetBranchAddress("Egamma",&Egamma);
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
TBranch *bnew1 = T->Branch("accep_el_out_1",&accep_el_out_1,"data/D");
TBranch *bnew2 = T->Branch("accep_minus_1",&accep_minus_1,"data/D");
TBranch *bnew3 = T->Branch("accep_plus_1",&accep_plus_1,"data/D");
TBranch *bnew4 = T->Branch("accep_recoil_1",&accep_recoil_1,"data/D");
TBranch *bnew5 = T->Branch("accep_el_out_2",&accep_el_out_2,"data/D");
TBranch *bnew6 = T->Branch("accep_minus_2",&accep_minus_2,"data/D");
TBranch *bnew7 = T->Branch("accep_plus_2",&accep_plus_2,"data/D");
TBranch *bnew8 = T->Branch("accep_recoil_2",&accep_recoil_2,"data/D");
TBranch *bnew9 = T->Branch("accep_3fold_recoildecaypair",&accep_3fold_recoildecaypair,"data/D");
TBranch *bnew10= T->Branch("accep_3fold_eloutdecaypair",&accep_3fold_eloutdecaypair,"data/D");
TBranch *bnew11= T->Branch("accep_4fold",&accep_4fold,"data/D");

//   ofstream OUT ("out.lund");

//  loop on entries
Int_t nentries = T->GetEntries();
cout << "nentries " << nentries << endl;

for (Int_t i=0;i<nentries;i++) {
// for (Int_t i=0;i<5;i++) {
//   cout << "EventNumber " << EventNumber << "\r";
  T->GetEvent(i);

  //testing things ===========================================================  
//   cout << sqrt(pow(*(ALV_Recoil_lab+0),2)-pow(*(ALV_Recoil_lab+1),2)-pow(*(ALV_Recoil_lab+2),2)-pow(*(ALV_Recoil_lab+3),2)) << endl;
  
//   Double_t E=*(ALV_Recoil_lab+0),Px=*(ALV_Recoil_lab+1),Py=*(ALV_Recoil_lab+2),Pz=*(ALV_Recoil_lab+3);
//   cout << sqrt(E*E-Px*Px-Py*Py-Pz*Pz) << endl;
//   cout << sqrt(pow(2.49211,2)-pow(0.307597,2)-pow(0.0249993,2)-pow(2.47292,2)) << endl;
//   cout << sqrt(pow(E,2.)-pow(Px,2.)-pow(Py,2.)-pow(Pz,2.)) << endl;  
  
//   cout << E*E << " " << pow(E,2) << " " << 2.49211*2.49211 << endl;
//   cout << sqrt(E*E) << " " << sqrt(pow(E,2)) << " " << sqrt(2.49211*2.49211) << endl;  
  
//       cout <<  E  << " " << Px << " " << Py  << " " << Pz << " "  << endl;

// sqrt(2.49211*2.49211-0.307597*0.307597-0.0249993*0.0249993-2.47292*2.47292)
// sqrt(2.49211*2.49211-0.307597*0.307597-0.0249993*0.0249993-2.47292*2.47292)
// sqrt(pow(2.49211,2)-pow(0.307597,2)-pow(0.0249993,2)-pow(2.47292,2))
  //testing things ===========================================================  
  
    //output to lund file=============================================================
//       OUT << "4" << " \t " << VirtualFlag  << " \t " << Q2  << " \t " << Qp2  << " \t " << "0" << " \t "  << Phi_CMV << " \t " << Theta_CMV  << " \t " << Egamma  << " \t " << tt  << " \t " << W_tot << endl;
//       
//       OUT << " \t " << "1" << " \t " << -1 << " \t " << "1" << " \t " << 11 << " \t " << "0" << " \t " << "0" << " \t " << *(ALV_el_out+1) << " \t " << *(ALV_el_out+2) << " \t " << *(ALV_el_out+3) << " \t " << *(ALV_el_out+0) << " \t " << 0.000511 << " \t " << 0  << " \t " << 0 << " \t " << -315 << endl;
//       OUT << " \t " << "1" << " \t " << -1 << " \t " << "1" << " \t " << 2212 << " \t " << "0" << " \t " << "0" << " \t " << *(ALV_Recoil_lab+1) << " \t " << *(ALV_Recoil_lab+2) << " \t " << *(ALV_Recoil_lab+3) << " \t " << *(ALV_Recoil_lab+0) << " \t " << 0.938 << " \t " << 0  << " \t " << 0 << " \t " << -315 << endl;
//       OUT << " \t " << "1" << " \t " << -1 << " \t " << "1" << " \t " << pid_decay << " \t " << "0" << " \t " << "0" << " \t " << *(ALV_minus_lab+1) << " \t " << *(ALV_minus_lab+2) << " \t " << *(ALV_minus_lab+3) << " \t " << *(ALV_minus_lab+0) << " \t " << mass_decay << " \t " << 0  << " \t " << 0 << " \t " << -315 << endl;
//       OUT << " \t " << "1" << " \t " << -1 << " \t " << "1" << " \t " << -pid_decay << " \t " << "0" << " \t " << "0" << " \t " << *(ALV_plus_lab+1) << " \t " << *(ALV_plus_lab+2) << " \t " << *(ALV_plus_lab+3) << " \t " << *(ALV_plus_lab+0) << " \t " << mass_decay << " \t " << 0  << " \t " << 0 << " \t " << -315 << endl;
    //output to lund file=============================================================
  
  TLorentzVector LV_minus_lab,LV_plus_lab,LV_recoil_lab,LV_el_out;
  
  LV_minus_lab.SetPxPyPzE(*(ALV_minus_lab+1),*(ALV_minus_lab+2),*(ALV_minus_lab+3),*(ALV_minus_lab+0));
  LV_plus_lab.SetPxPyPzE(*(ALV_plus_lab+1),*(ALV_plus_lab+2),*(ALV_plus_lab+3),*(ALV_plus_lab+0));
  LV_recoil_lab.SetPxPyPzE(*(ALV_Recoil_lab+1),*(ALV_Recoil_lab+2),*(ALV_Recoil_lab+3),*(ALV_Recoil_lab+0));
  LV_el_out.SetPxPyPzE(*(ALV_el_out+1),*(ALV_el_out+2),*(ALV_el_out+3),*(ALV_el_out+0));  
    
  int bin,binx,biny,binz;

  if (type=="SoLID_TCS_ele") {
    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_el_out.Theta()*DEG,LV_el_out.P());  
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_el_out_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);
    accep_el_out_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny);

    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_minus_lab.Theta()*DEG,LV_minus_lab.P());
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_minus_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);  
    accep_minus_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny);
    
    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_plus_lab.Theta()*DEG,LV_plus_lab.P());
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_plus_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);  
    accep_plus_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny);

    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P());  
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_recoil_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);
    accep_recoil_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny); 
    
    accep_4fold = 0;    
    accep_3fold_eloutdecaypair = 0;  
    // at least one decay particles goes forward to use Cherenkov
    if (accep_minus_2 > 0 && accep_plus_2 > 0) accep_3fold_recoildecaypair=0;
    else accep_3fold_recoildecaypair =  (accep_recoil_1+accep_recoil_2)*(accep_minus_1+accep_minus_2)*(accep_plus_1+accep_plus_2);
  }
  else if (type=="SoLID_DDVCS_muon") {  
    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_el_out.Theta()*DEG,LV_el_out.P());  
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_el_out_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);
    accep_el_out_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny);

    bin=hacceptance_ThetaP_forwardangle_muon->FindBin(LV_minus_lab.Theta()*DEG,LV_minus_lab.P());
    hacceptance_ThetaP_forwardangle_muon->GetBinXYZ(bin,binx,biny,binz);
    accep_minus_1 = hacceptance_ThetaP_forwardangle_muon->GetBinContent(binx,biny);  
    accep_minus_2 = hacceptance_ThetaP_largeangle_muon->GetBinContent(binx,biny);
    
    bin=hacceptance_ThetaP_forwardangle_muon->FindBin(LV_plus_lab.Theta()*DEG,LV_plus_lab.P());
    hacceptance_ThetaP_forwardangle_muon->GetBinXYZ(bin,binx,biny,binz);
    accep_plus_1 = hacceptance_ThetaP_forwardangle_muon->GetBinContent(binx,biny);  
    accep_plus_2 = hacceptance_ThetaP_largeangle_muon->GetBinContent(binx,biny);

    bin=hacceptance_ThetaP_forwardangle->FindBin(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P());  
    hacceptance_ThetaP_forwardangle->GetBinXYZ(bin,binx,biny,binz);
    accep_recoil_1 = hacceptance_ThetaP_forwardangle->GetBinContent(binx,biny);
    accep_recoil_2 = hacceptance_ThetaP_largeangle->GetBinContent(binx,biny); 
    
    accep_4fold =  (accep_el_out_1+accep_el_out_1)*(accep_recoil_1+accep_recoil_2)*(accep_minus_1+accep_minus_2)*(accep_plus_1+accep_plus_2);
    accep_3fold_eloutdecaypair =  (accep_el_out_1+accep_el_out_1)*(accep_minus_1+accep_minus_2)*(accep_plus_1+accep_plus_2);
    accep_3fold_recoildecaypair =  (accep_recoil_1+accep_recoil_2)*(accep_minus_1+accep_minus_2)*(accep_plus_1+accep_plus_2);
  }  
//   cout << "theta " << LV_el_out.Theta()*DEG << " " << LV_minus_lab.Theta()*DEG <<  " " << LV_plus_lab.Theta()*DEG << " " << LV_recoil_lab.Theta()*DEG <<endl;
//   cout << "p " << LV_el_out.P() << " " << LV_minus_lab.P() <<  " " << LV_plus_lab.P() << " " << LV_recoil_lab.P() <<endl;
  
  h[0][0]->Fill(LV_el_out.Theta()*DEG,LV_el_out.P(),W_BH);
  h[0][1]->Fill(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P(),W_BH);    
  h[0][2]->Fill(LV_minus_lab.Theta()*DEG,LV_minus_lab.P(),W_BH);    
  h[0][3]->Fill(LV_plus_lab.Theta()*DEG,LV_plus_lab.P(),W_BH);
  
  if (accep_el_out_1+accep_el_out_2 > 0) h[1][0]->Fill(LV_el_out.Theta()*DEG,LV_el_out.P(),W_BH);
  if (accep_recoil_1+accep_recoil_2 > 0) h[1][1]->Fill(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P(),W_BH);    
  if (accep_minus_1+accep_minus_2 > 0) h[1][2]->Fill(LV_minus_lab.Theta()*DEG,LV_minus_lab.P(),W_BH);    
  if (accep_plus_1+accep_plus_2 > 0) h[1][3]->Fill(LV_plus_lab.Theta()*DEG,LV_plus_lab.P(),W_BH);

  if (accep_3fold_recoildecaypair>0){
  h[2][0]->Fill(LV_el_out.Theta()*DEG,LV_el_out.P(),W_BH);
  h[2][1]->Fill(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P(),W_BH);    
  h[2][2]->Fill(LV_minus_lab.Theta()*DEG,LV_minus_lab.P(),W_BH);    
  h[2][3]->Fill(LV_plus_lab.Theta()*DEG,LV_plus_lab.P(),W_BH);
  }
  
  if (accep_3fold_eloutdecaypair>0){
  h[3][0]->Fill(LV_el_out.Theta()*DEG,LV_el_out.P(),W_BH);
  h[3][1]->Fill(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P(),W_BH);    
  h[3][2]->Fill(LV_minus_lab.Theta()*DEG,LV_minus_lab.P(),W_BH);    
  h[3][3]->Fill(LV_plus_lab.Theta()*DEG,LV_plus_lab.P(),W_BH);
  }

  if (accep_4fold>0){
  h[4][0]->Fill(LV_el_out.Theta()*DEG,LV_el_out.P(),W_BH);
  h[4][1]->Fill(LV_recoil_lab.Theta()*DEG,LV_recoil_lab.P(),W_BH);    
  h[4][2]->Fill(LV_minus_lab.Theta()*DEG,LV_minus_lab.P(),W_BH);    
  h[4][3]->Fill(LV_plus_lab.Theta()*DEG,LV_plus_lab.P(),W_BH);
  }
  
  
  //HallD
  // 		  if (3 < theta_je1 && theta_je1 <140)  accep_minus = 1.;
// 		  else accep_minus = 0;
// 		  if (3 < theta_je2 && theta_je2 <140)  accep_plus = 1.; 		    
// 		  else accep_plus = 0;		  
// 		  if (3 < theta_p && theta_p <150)  accep_p = 1.;
// 		  else accep_p = 0;		  
// // 		  if (8 < theta_je1 && theta_je1 <25)  accep_minus = 1.;
// // 		  else accep_minus = 0;
// // 		  if (8 < theta_je2 && theta_je2 <25)  accep_plus = 1.; 		    
// // 		  else accep_plus = 0;		  
// // 		  if (8 < theta_p && theta_p <25)  accep_p = 1.;
// // 		  else accep_p = 0;
		  
   bnew1->Fill();
   bnew2->Fill();
   bnew3->Fill();
   bnew4->Fill();
   bnew5->Fill();
   bnew6->Fill(); 
   bnew7->Fill();
   bnew8->Fill();
   bnew9->Fill();       
   bnew10->Fill();
   bnew11->Fill();          
}

int n;
if (type=="SoLID_TCS_ele") {n=3;}
else if (type=="SoLID_DDVCS_muon") {n=5;}

TCanvas *c_ThetaP = new TCanvas("ThetaP","ThetaP",1200,900);
c_ThetaP->Divide(4,n);
for(int i=0;i<n;i++){
  for(int j=0;j<4;j++){    
   c_ThetaP->cd(i*4+j+1);
   gPad->SetLogz();
   gPad->SetGrid();
   h[i][j]->SetMinimum(0);  
//     h[i][j]->SetMaximum(1);  
    h[i][j]->Draw("colz");
  }
}
c_ThetaP->SaveAs(Form("BH_ThetaP_%s.png",type.c_str()));

// OUT.close();
T->Write();
file->Write();
file->Close();
    
}