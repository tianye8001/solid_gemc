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
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>

using namespace std;

// void anaGrape(string input_filedir,string detector=""){
void anaGrape(string detector=""){
//  set_style();
// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1000011);
//   gStyle->SetOptStat(1);

double thetamin,thetamax;
TH3F *hacceptance_PThetaPhi_positive,*hacceptance_PThetaPhi_negative;
TH2F *hacceptance_ThetaP_forwardangle,*hacceptance_ThetaP_largeangle;

if (detector=="CLAS12"){
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele.root");
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele_largebin.root");
  TFile *acceptancefile=new TFile("../clasev_acceptance.root");
  
  hacceptance_PThetaPhi_positive=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_pip");  
  hacceptance_PThetaPhi_negative=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_ele");

  thetamin=0;    
  thetamax=180;  
  
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,1);
//   c_acceptance->cd(1);
//   hacceptance_PThetaPhi_positive->Draw();
//   c_acceptance->cd(2);
//   hacceptance_PThetaPhi_negative->Draw();  
  
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
else if (detector=="SoLID"){
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
  thetamax=50;  
  
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
else {cout << "wrong detector" << endl;}
  
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

TH2F *hepscat = new TH2F("hepscat","",50,-1.0,1.0,60,-1.0,1.0);
TH2F *hemscat = new TH2F("hemscat","",50,-1.0,1.0,60,-1.0,1.0);

TH1F *hW = new TH1F("W","",50,4,4.5);
TH1F *hWstat = new TH1F("Wstat","",50,4,4.5);

TH1F *hem_theta = new TH1F("hem_theta","",100,-3.145,3.15);
TH1F *hem_phi = new TH1F("hem_phi","",100,-3.1415,3.1415);


TH1F *hkpth = new TH1F("hkpth","",100, 0.0, 40.0);
TH1F *hprth = new TH1F("hprth","",100, 0.0, 40.0);

TH1F *hkpph = new TH1F("hkpph","",100, -180., 180.);
TH1F *hprph = new TH1F("hprph","",100, -180., 180.);

TH1F *hkpp = new TH1F("hkpp","",100,0, 5);
TH1F *hprp = new TH1F("hprp","",100,0, 5);

TH2F *hQ2W = new TH2F("Q2W","Q2W",50,4,4.5,200,0,2);
TH2F *htW = new TH2F("tW","tW",50,4,4.5,600,0,6);
TH2F *htminW = new TH2F("tminW","tminW",50,4,4.5,600,0,6);
TH2F *htmaxW = new TH2F("tmaxW","tmaxW",50,4,4.5,600,0,6);
TH1F *ht = new TH1F("\t","\t",600,0,6);

TH2F *hlepIM_W = new TH2F("hlepIM_W",";e+ e- Inv Mass (GeV);W (GeV)",80,0,4.0,40,2,6); 

const int m=4;

char *title[m]={"scattered lepton","recoil p","decay lepton^{-}","decay lepton^{+}"};
TH1F *hlepIM1[m],*hlepIM2[m],*hlepIM[m];
TH2F *hlepIM_2D[m];
TH2F *hThetaP[4][m],*hThetaPhi[4][m];
for(int k=0;k<m;k++){
  char hstname[100];
  for(int l=0;l<4;l++){  
   sprintf(hstname,"ThetaP_%i_%i",l,k);
   hThetaP[l][k]=new TH2F(hstname,Form("%s;#theta_{lab} (deg);P (GeV)",title[l]),180,0,180,800,0,8);
   sprintf(hstname,"ThetaPhi_%i_%i",l,k);
   hThetaPhi[l][k]=new TH2F(hstname,";#theta_{lab} (deg);#phi_{lab} (deg)",180,0,180,100,-180.,180.);   
  }
    
  sprintf(hstname,"hlepIM_2D_%i",k);
  hlepIM_2D[k] = new TH2F(hstname,";e+ e-(1st) Inv Mass (GeV);e+ e-(2nd) Inv Mass (GeV)",80,0,4.0,80,0,4.0);   
  
  sprintf(hstname,"hlepIM1_%i",k);
  hlepIM1[k] = new TH1F(hstname,";e+ e- Inv Mass (GeV);",80,0,4.0);   
  sprintf(hstname,"hlepIM2_%i",k);
  hlepIM2[k] = new TH1F(hstname,";e+ e- Inv Mass (GeV);",80,0,4.0);   
  sprintf(hstname,"hlepIM_%i",k);
  hlepIM[k] = new TH1F(hstname,";e+ e- Inv Mass (GeV);",80,0,4.0);
}

double weight[m];

Double_t pi1 = TMath::Pi();
//   cout << pi1 << endl;

Double_t D2R = 3.1415/180.;

Double_t DEG = 180./3.1415;
   
char input_filename[80];
// sprintf(input_filename, "%s/grp.root",input_filedir.c_str());
sprintf(input_filename, "grp.root");

  TChain *h11 = new TChain("h11");
  h11->Add(input_filename);

  Double_t xsec[20];

  h11->SetBranchStatus("*",0);
  h11->SetBranchStatus("xsec",1);
  h11->SetBranchAddress("xsec",&xsec);
  h11->GetEntry(0);

  cout << "total Cross Section " << xsec[0] << " pb" << endl;
  // total Cross Section also can be found in the spring output on screen
  
  TChain *h1 = new TChain("h1");
  h1->Add(input_filename);  
  
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

  int counter1=0,counter2=0,counter3=0,counter4=0,counter5=0;
  
  Int_t counter;
  Int_t countd = 1;
  cout << "|___________________|" << endl;
  cout << "|" << flush;
  
  for(Int_t i=0; i < nevent; i++){
//     for(Int_t i=0; i < 1000; i++){
    Double_t id = i;
    Double_t neventd = nevent;
    if(floor(id/neventd*20) == countd){
   
      cout << "=" << flush;
      countd++;
      if(countd == 20){
	cout << "|" << endl;
      }
    }

    h1->GetEvent(i);

    if(i<3) {
      for (Int_t j=0; j < 14; j++) {
	cout << j << "\t"  << px[j] <<  "\t"  << py[j] <<  "\t"  << pz[j] <<  "\t"  << pe[j] <<  "\t"  << pm[j] <<  "\t"  << kf[j] <<  "\t"  << sta[j] <<  "\t"  << npy[j] << endl; 
      }
      cout << "******************************"<< endl;
    }

//     targ.SetXYZT(px[0],py[0],pz[0],pe[0]);    
//     ki.SetXYZT(px[1],py[1],pz[1],pe[1]);    
    targ.SetXYZT(px[4],py[4],pz[4],pe[4]);
    ki.SetXYZT(px[5],py[5],pz[5],pe[5]);    
// cout <<  ki.P() << " " << targ.P() << endl;
    
    
    prot.SetXYZT(px[10],py[10],pz[10],pe[10]);    
    kp.SetXYZT(px[11],py[11],pz[11],pe[11]);
    ep.SetXYZT(px[12],py[12],pz[12],pe[12]);
    em.SetXYZT(px[13],py[13],pz[13],pe[13]);
// cout <<  ep.M() << " " << em.M() << endl;
    
    ki.RotateY(pi1);
    targ.RotateY(pi1);    
    prot.RotateY(pi1);    
    kp.RotateY(pi1);
    ep.RotateY(pi1);
    em.RotateY(pi1);
    
    double InvM_epm1=(ep+em).M();
    double InvM_epm2=(ep+kp).M();	
	  
    double Q2=-(ki-kp).M2();
    double W=(ki-kp+targ).M();
//         double W=(prot+ep+em).M();    
    double t=-(prot-targ).M2();
    double m1=(ki-kp).M(),m2=targ.M(),m3=3.097,m4=prot.M();
    double s=W*W;
    double E1cm=(s+m1*m1-m2*m2)/(2*sqrt(s)),E3cm=(s+m3*m3-m4*m4)/(2*sqrt(s));
    double p1cm=sqrt(E1cm*E1cm-m1*m1),p3cm=sqrt(E3cm*E3cm-m3*m3);
    double tmin= -(pow(E1cm-E3cm,2) - pow(p1cm-p3cm,2));
    double tmax= -(pow(E1cm-E3cm,2) - pow(p1cm+p3cm,2));    
    
// cout << W << endl;
// cout << (kp+prot+ep+em).P() <<  " " << (kp+prot+ep+em).Theta() << endl;

    //    hem_theta->Fill(kp.Theta());
    //    hem_phi->Fill(kp.Phi());

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
    
      double prot_mom=prot.P(),em_mom=em.P(),kp_mom=kp.P(),ep_mom=ep.P();
      double prot_theta=prot.Theta()*DEG,em_theta=em.Theta()*DEG,kp_theta=kp.Theta()*DEG,ep_theta=ep.Theta()*DEG;
      double prot_phi=prot.Phi()*DEG,em_phi=em.Phi()*DEG,kp_phi=kp.Phi()*DEG,ep_phi=ep.Phi()*DEG;      
	
      int whichone=0;      
      double acc=0;      
      double acc_prot=0,acc_kp=0,acc_em=0,acc_ep=0;
      if (detector=="CLAS12"){
	  //note CLAS12 phi (0,360), TCS sim phi (-180,180) 	
	  acc_prot=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(prot_phi+180,prot_theta,prot_mom));
	  acc_ep=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(ep_phi+180,ep_theta,ep_mom));
	  acc_kp=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(kp_phi+180,kp_theta,kp_mom));	  
	  acc_em=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(em_phi+180,em_theta,em_mom));	  	  
	  
// 	  if (acc_prot > 0) cout << "acc_prot " << acc_prot << endl;
// 	  if (acc_ep > 0) cout << "acc_ep " << acc_ep << endl;
// 	  if (acc_kp > 0) cout << "acc_kp " << acc_kp << endl;
// 	  if (acc_em > 0) cout << "acc_em " << acc_em << endl; 

// 	  //cut away unsure low acceptance		  
// 	  if (acc_prot < 0.9) acc_prot=0;
// 	  if (acc_ep < 0.9) acc_ep=0;
// 	  if (acc_kp < 0.9) acc_kp=0;
// 	  if (acc_em < 0.9) acc_em=0; 
	    	  
	  //for with both electron
// 	  if ((acc_kp>0 && 5<em_theta && em_theta<36 && kp_mom < 4.9) && (acc_em>0 && 5<em_theta && em_theta<36 && em_mom < 4.9)) {whichone=1;} // both in main detector 
// 	  else if ((acc_kp>0 && 5<em_theta && em_theta<36 && kp_mom < 4.9) && 2.5<em_theta && em_theta <4.5) {acc_em=1.;whichone=2;}
// // 	  else if ((acc_em>0 && 5<em_theta && em_theta<36 && em_mom < 4.9) && 2.5<em_theta && em_theta <4.5) {acc_kp=1.;whichone=3;}
// 	  else {acc_kp=0; acc_em=0; whichone=4;}
 
// 	  if (ep_theta>36 || ep_mom > 4.9) acc_ep=0; //lepton has no detection at central detector
// 	  if (prot_theta>36 && prot_mom > 1) acc_prot=0;
// 	  if (prot_theta<36 && prot_mom > 4) acc_prot=0;
	  
	  acc=acc_prot*acc_ep*acc_kp*acc_em;
	  
	  if ((2.5 <=em_theta && em_theta<=4.5) || (2.5 <=kp_theta && kp_theta<=4.5)) {}
	  else acc=0;
	  
	  if (acc>0){
	    if (whichone==1) {counter1++; acc=0;}  //don't count both in main detector
	    else if (whichone==2) counter2++;
	    else if (whichone==3) counter3++;
	    else cout << "something wrong" << endl;
	  }
	  else {
	    if (whichone==4) counter4++;
	    else counter5++;
	  }
// 	  if (acc==0 && whichone!=4) cout << "kkkkkkkkkkkkkk" << endl;
	  
// 	  if (e_theta<=36) res_index_electron=0;
// 	  if (e_theta >36) res_index_electron=1;
// 	  if (ep_theta<=36) res_index_positron=0;
// 	  if (ep_theta >36) res_index_positron=1;
// 	  if (prot_theta<=36) res_index_proton=0;
// 	  if (prot_theta >36) res_index_proton=1;
	   
      }
      else if (detector=="SoLID"){
	  //sim phi (-180,180)	
	  acc_prot=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot_theta,prot_mom));
	  acc_ep=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(ep_theta,ep_mom));
	  acc_kp=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp_theta,kp_mom));	  
	  acc_em=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(em_theta,em_mom));	  
	
	  acc_prot += hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(prot_theta,prot_mom));
	  acc_ep += hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(ep_theta,ep_mom));
	  acc_kp += hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(kp_theta,kp_mom));	  
	  acc_em += hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(em_theta,em_mom));	
	   
	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
	  
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
      else {cout << "wrong detector" << endl;}
      
      //      pb = 1e-36 cm2, lumi 1e35/cm2/s, 120 days, 0.85 eff
      double count_convert = 1e-36*1e35*3600*24*120*0.85;
      
      weight[0]=1;
      weight[1]=acc;
      weight[2]=acc*effxsec;
      weight[3]=acc*effxsec*count_convert;      
	      
      for(Int_t k=0; k < m; k++){  
	if(k>0 && acc==0) continue;
	hThetaP[0][k]->Fill(kp_theta,kp_mom,weight[k]);
	hThetaP[1][k]->Fill(prot_theta,prot_mom,weight[k]);	
	hThetaP[2][k]->Fill(em_theta,em_mom,weight[k]);
	hThetaP[3][k]->Fill(ep_theta,ep_mom,weight[k]);

	hThetaPhi[0][k]->Fill(kp_theta,kp_phi,weight[k]);
	hThetaPhi[1][k]->Fill(prot_theta,prot_phi,weight[k]);	
	hThetaPhi[2][k]->Fill(em_theta,em_phi,weight[k]);
	hThetaPhi[3][k]->Fill(ep_theta,ep_phi,weight[k]);

	hlepIM_2D[k]->Fill(InvM_epm1,InvM_epm2,weight[k]);
	
	hlepIM1[k]->Fill(InvM_epm1,weight[k]);
	hlepIM2[k]->Fill(InvM_epm2,weight[k]);

	hlepIM[k]->Fill(InvM_epm1,weight[k]);
	hlepIM[k]->Fill(InvM_epm2,weight[k]);	
	
// 	if (whichone==2) hlepIM[k]->Fill(InvM_epm1,weight[k]);
// 	else if (whichone==3) hlepIM[k]->Fill(InvM_epm2,weight[k]);
      }
      
	if ( 3.0 < InvM_epm1 && InvM_epm1 < 3.25 ) {
	  hW->Fill(W,weight[2]);	  
	  hWstat->Fill(W,weight[2]);	  
	  hlepIM_W->Fill(InvM_epm1,W,weight[2]);
	  hlepIM_W->Fill(InvM_epm2,W,weight[2]);	  	  	  	  
	  hQ2W->Fill(W,Q2,weight[2]);
	  htW->Fill(W,t-tmin,weight[2]);    
	  htminW->Fill(W,tmin,weight[2]);    
	  htmaxW->Fill(W,tmax,weight[2]);
	  ht->Fill(t-tmin,weight[2]);	    
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
  
  cout << counter1 << " " << counter2 << " " << counter3 << " " << counter4 << " " << counter5 << endl;

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
  
  
  TCanvas *c_lepIM1_xsec = new TCanvas("lepIM1_xsec","lepIM1_xsec",900,900);
  hlepIM1[2]->SetTitle(";l^{+}l^{-} InvM (GeV);d#sigma (pb)");  
  hlepIM1[2]->Draw();

  TCanvas *c_lepIM1_count = new TCanvas("lepIM1_count","lepIM1_count",900,900);
  hlepIM1[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count of (lumi 1e35/cm2/s 120 days 85% eff)");    
  hlepIM1[3]->Draw();
  
  TCanvas *c_lepIM_xsec = new TCanvas("lepIM_xsec","lepIM_xsec",900,900);
  hlepIM[2]->SetTitle(";l^{+}l^{-} InvM (GeV);d#sigma (pb)");  
  hlepIM[2]->Draw();

  TCanvas *c_lepIM_count = new TCanvas("lepIM_count","lepIM_count",900,900);
  hlepIM[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count of (lumi 1e35/cm2/s 120 days 85% eff)");    
  hlepIM[3]->Draw();  

  cout << "BH " <<  hlepIM[3]->Integral();
/*  
  
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

  TCanvas *can = new TCanvas("can","can",1200,900);
  can->Divide(3,2);  
  can->cd(1);
  hW->GetXaxis()->SetTitle("W");
  hW->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
  hW->Draw();  
  can->cd(2);
  hWstat->GetXaxis()->SetTitle("Wstat");
  hWstat->GetYaxis()->SetTitle("number of event per day/ 10MeV");
  hWstat->Draw();   
  can->cd(3);
  hQ2W->Draw("colz");
  can->cd(4);
  htW->Draw("colz");
  can->cd(5);
  htminW->Draw("colz");
  htmaxW->Draw("colz same");  
  can->cd(6);
  ht->Draw();
  
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
  cout << "BH 1.3-1.55 GeV " <<  hlepIM[3]->Integral(130,155) << endl;  //pure sum to count , no width  
     
outputfile->Write();
outputfile->Flush();      
*/
}
