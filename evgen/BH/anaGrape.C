//#include "/home/mpaolone/work/anaLepv2/v3/set_style.h"
#include <iostream> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>

using namespace std;

void anaGrape(string input_filedir){

//  set_style();
// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1000011);
//   gStyle->SetOptStat(1);
  
//   TFile *acceptancefile=new TFile("accep.root");
// TH2F *h2_acc=(TH2F*) acceptancefile->Get("h2");
// TH2F *h3_acc=(TH2F*) acceptancefile->Get("h3");
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,1);
//   c_acceptance->cd(1);
//   h2_acc->Draw("colz");
//   c_acceptance->cd(2);
//   h3_acc->Draw("colz");

 bool conf_4fold=false,conf_3fold_NOp=false,conf_3fold_NOe=false;
 bool conf_validation=false;
if (input_filedir.find("4fold",0) != string::npos)  conf_4fold=true;
if (input_filedir.find("3fold_NOp",0) != string::npos)  conf_3fold_NOp=true; 
if (input_filedir.find("3fold_NOe",0) != string::npos)  conf_3fold_NOe=true;
if (input_filedir.find("validation",0) != string::npos)  conf_validation=true; 
  
char output_filename[80];
sprintf(output_filename, "%s.root",input_filedir.c_str());
  
TFile *outputfile=new TFile(output_filename, "recreate");

TH2F *hang_dist_scat_e = new TH2F("hang_dist_scat_e","",100,-40.,40,100,-180.,180.);
TH2F *hang_dist_scat_p = new TH2F("hang_dist_scat_p","",100,-40.,40,100,-180.,180.);

TH2F *hepscat = new TH2F("hepscat","",50,-1.0,1.0,60,-1.0,1.0);
TH2F *hemscat = new TH2F("hemscat","",50,-1.0,1.0,60,-1.0,1.0);

TH2F *hlepIM_2D = new TH2F("hlepIM_2D","",400,0.0,4.0,400,0.0,4.0);

TH1F *hlepIM = new TH1F("hlepIM","",400,0.0,4.0);

TH1F *hlepIM_count = new TH1F("hlepIM_count","",400,0.0,4.0);

TH1F *hlepIM2 = new TH1F("hlepIM2","",100,2.8,3.8);

TH2F *hlepIM_W = new TH2F("hlepIM_W","",400,0.0,4.0,40,2,6);
TH2F *hlepIM2_W = new TH2F("hlepIM2_W","",100,2.8,3.8,40,2,6);

TH1F *hW = new TH1F("W","",50,4,4.5);
TH1F *hWstat = new TH1F("Wstat","",50,4,4.5);

TH1F *hkp_theta = new TH1F("hkp_theta","",100,-3.145,3.15);
TH1F *hkp_phi = new TH1F("hkp_phi","",100,-3.1415,3.1415);


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

TH2F *hThetaP[4][4];
for(int k=0;k<4;k++){
  for(int l=0;l<4;l++){
   char hstname[100];
   sprintf(hstname,"ThetaP_%i_%i",k,l);
   hThetaP[k][l]=new TH2F(hstname,hstname,300,0,30,8000,0,8);
  }  
}

Double_t pi1 = TMath::Pi();

Double_t D2R = 3.1415/180.;
   
char input_filename[80];
sprintf(input_filename, "%s/grp.root",input_filedir.c_str());

  TChain *h11 = new TChain("h11");
  h11->Add(input_filename);

  TChain *eff = new TChain("h1");
  eff->Add(input_filename);


  Double_t xsec[20];

  h11->SetBranchStatus("*",0);
  h11->SetBranchStatus("xsec",1);
  h11->SetBranchAddress("xsec",&xsec);
  h11->GetEntry(0);

  cout << "total Cross Section " << xsec[0] << " pb" << endl;
  
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


  eff->SetBranchStatus("*",0);

  eff->SetBranchStatus("px",1);
  eff->SetBranchAddress("px",&px);
  eff->SetBranchStatus("py",1);
  eff->SetBranchAddress("py",&py);
  eff->SetBranchStatus("pz",1);
  eff->SetBranchAddress("pz",&pz);
  eff->SetBranchStatus("pe",1);
  eff->SetBranchAddress("pe",&pe);
  eff->SetBranchStatus("pm",1);
  eff->SetBranchAddress("pm",&pm);
  eff->SetBranchStatus("kf",1);
  eff->SetBranchAddress("kf",&kf);
  eff->SetBranchStatus("sta",1);
  eff->SetBranchAddress("sta",&sta);
  eff->SetBranchStatus("npy",1);
  eff->SetBranchAddress("npy",&npy);

//   cout << pi1 << endl;

  Int_t nevent = eff->GetEntries();

  cout << nevent << endl;
  TLorentzVector kp, prot, ep, em, ki, targ;

  Double_t effXsec = xsec[0]/(double)nevent;

  Bool_t scatPhiBool, scat_e_calo;

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

    eff->GetEvent(i);

    if(i<10) {
      for (Int_t j=0; j < 14; j++) {
	cout << j << "\t"  << px[j] <<  "\t"  << py[j] <<  "\t"  << pz[j] <<  "\t"  << pe[j] <<  "\t"  << pm[j] <<  "\t"  << kf[j] <<  "\t"  << sta[j] <<  "\t"  << npy[j] << endl; 
      }
      cout << "******************************"<< endl;
    }
    
    
    ki.SetXYZT(px[1],py[1],pz[1],pe[1]);
    targ.SetXYZT(px[0],py[0],pz[0],pe[0]);
// cout <<  ki.P() << " " << targ.P() << endl;
    kp.SetXYZT(px[11],py[11],pz[11],pe[11]);
    prot.SetXYZT(px[10],py[10],pz[10],pe[10]);
    ep.SetXYZT(px[12],py[12],pz[12],pe[12]);
    em.SetXYZT(px[13],py[13],pz[13],pe[13]);

    ki.RotateY(pi1);
    kp.RotateY(pi1);
    prot.RotateY(pi1);
    ep.RotateY(pi1);
    em.RotateY(pi1);
    
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

    //    hkp_theta->Fill(kp.Theta());
    //    hkp_phi->Fill(kp.Phi());

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

    int index=0;
    hThetaP[0][index]->Fill(kp.Theta()/D2R,kp.P(),effXsec);
    hThetaP[1][index]->Fill(em.Theta()/D2R,em.P(),effXsec);
    hThetaP[2][index]->Fill(ep.Theta()/D2R,ep.P(),effXsec);
    hThetaP[3][index]->Fill(prot.Theta()/D2R,prot.P(),effXsec);    
    
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
	  
	  	bool triggercut = true;
	  	bool cut = true;
	      
	  if (cut){     
	    index=1;
	    hThetaP[0][index]->Fill(kp.Theta()/D2R,kp.P(),effXsec);
	    hThetaP[1][index]->Fill(em.Theta()/D2R,em.P(),effXsec);
	    hThetaP[2][index]->Fill(ep.Theta()/D2R,ep.P(),effXsec);
	    hThetaP[3][index]->Fill(prot.Theta()/D2R,prot.P(),effXsec); 

	  if (triggercut) {
	    // cout << 1 << endl;
	    index=2;
	    hThetaP[0][index]->Fill(kp.Theta()/D2R,kp.P(),effXsec);
	    hThetaP[1][index]->Fill(em.Theta()/D2R,em.P(),effXsec);
	    hThetaP[2][index]->Fill(ep.Theta()/D2R,ep.P(),effXsec);
	    hThetaP[3][index]->Fill(prot.Theta()/D2R,prot.P(),effXsec); 
	
	  hang_dist_scat_e->Fill(kp.Theta()/D2R, kp.Phi()/D2R);
	  hang_dist_scat_p->Fill(prot.Theta()/D2R, prot.Phi()/D2R);
	  
	  double InvM_epm=(ep+em).M();

	  hlepIM_2D->Fill(InvM_epm,(ep+kp).M(),effXsec);
	  
	  hlepIM->Fill(InvM_epm, effXsec);
	  
	  //      pb = 1e-36 cm2, lumi 1e37/cm2/s, 50 days, 0.85 eff
	  double count_convert = 1e-36*1e37*24*3600*50*0.85;
	  
	  hlepIM_count->Fill(InvM_epm, effXsec*count_convert);

	  hlepIM2->Fill(InvM_epm, effXsec);
	  
	  hlepIM_W->Fill(InvM_epm, W,effXsec);
	  hlepIM2_W->Fill(InvM_epm, W, effXsec);

	  if ( 3.0 < InvM_epm && InvM_epm < 3.25 ) {
	    hW->Fill(W,effXsec);
	    hWstat->Fill(W,effXsec*count_convert);
	    
	    hQ2W->Fill(W,Q2,effXsec);
	    htW->Fill(W,t-tmin,effXsec);    
	    htminW->Fill(W,tmin,effXsec);    
	    htmaxW->Fill(W,tmax,effXsec);
	    ht->Fill(t-tmin,effXsec);	    

	    index=3;
	    hThetaP[0][index]->Fill(kp.Theta()/D2R,kp.P(),effXsec);
	    hThetaP[1][index]->Fill(em.Theta()/D2R,em.P(),effXsec);
	    hThetaP[2][index]->Fill(ep.Theta()/D2R,ep.P(),effXsec);
	    hThetaP[3][index]->Fill(prot.Theta()/D2R,prot.P(),effXsec);	
	  }
		
	  //      hkpth->Fill(180.0 -kp.Theta()/D2R, effXsec);
	  //   hprth->Fill(180.0 -prot.Theta()/D2R, effXsec);
	  hkpth->Fill(kp.Theta()/D2R, effXsec);
	  hprth->Fill(prot.Theta()/D2R, effXsec);

	  hkpph->Fill(kp.Phi()/D2R, effXsec);
	  hprph->Fill(prot.Phi()/D2R, effXsec);
	  hkpp->Fill(kp.Vect().Mag(), effXsec);
	  hprp->Fill(prot.Vect().Mag(), effXsec);

	  hepscat->Fill(sin(ep.Theta())*cos(ep.Phi()), sin(ep.Theta())*sin(ep.Phi()));
	  hemscat->Fill(sin(em.Theta())*cos(em.Phi()), sin(em.Theta())*sin(em.Phi()));
      }      
    }
//      cout << i << "\r"; 
//      cout << i << endl; 
  }
  
  TCanvas *can1 = new TCanvas("can1","",900,900);
  hang_dist_scat_e->SetMarkerColor(kRed);
  hang_dist_scat_e->SetLineColor(kRed);
  hang_dist_scat_e->GetXaxis()->SetTitle("#theta_{lab} (deg)");
  hang_dist_scat_e->GetYaxis()->SetTitle("#phi_{lab} (deg)");
  hang_dist_scat_e->Draw();
  hang_dist_scat_p->SetMarkerColor(kBlue);
  hang_dist_scat_p->SetLineColor(kBlue);
  hang_dist_scat_p->Draw("same");

  TCanvas *can2 = new TCanvas("can2","",1200,900);
  hlepIM->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
  hlepIM->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
  hlepIM->Draw();
  
  TCanvas *can12 = new TCanvas("can12","",1200,900);
  gStyle->SetOptStat(0);  
  gStyle->SetTitleSize(0.1,"X");
  gStyle->SetTitleSize(0.1,"Y");
  can12->SetFillColor(10);
  hlepIM_count->SetTitle("BH event counts VS e+ e- Inv Mass");
  hlepIM_count->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
  hlepIM_count->GetYaxis()->SetTitle("counts /50 MeV for 50 days");
//   hlepIM_count->SetTitleSize(0.1);
  hlepIM_count->Rebin(5);  
  hlepIM_count->Draw();
  hlepIM_count->SetLineWidth(3.5);

  TCanvas *can_lepIM_2D = new TCanvas("can_lepIM_2D","can_lepIM_2D",1200,900);
  hlepIM_2D->GetXaxis()->SetTitle("e+ e-(10th) Inv Mass (GeV)");
  hlepIM_2D->GetYaxis()->SetTitle("e+ e-(8th) Inv Mass (GeV)");
  hlepIM_2D->Draw("colz");

  TCanvas *can3 = new TCanvas("can3","",1200,900);
  hlepIM2->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
  hlepIM2->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
  hlepIM2->Draw();
  
  TCanvas *can22 = new TCanvas("can22","",1200,900);
  hlepIM_W->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
  hlepIM_W->GetYaxis()->SetTitle("W");
  hlepIM_W->Draw("colz");

  TCanvas *can33 = new TCanvas("can33","",1200,900);
  hlepIM2_W->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
  hlepIM2_W->GetYaxis()->SetTitle("W"); 
  hlepIM2_W->Draw("colz");  
  
  TCanvas *c_W = new TCanvas("W","W",1200,900);
  hW->GetXaxis()->SetTitle("W");
  hW->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
  hW->Draw();   
  
  TCanvas *c_Wstat = new TCanvas("Wstat","Wstat",1200,900);
  hWstat->GetXaxis()->SetTitle("Wstat");
  hWstat->GetYaxis()->SetTitle("number of event per day/ 10MeV");
  hWstat->Draw();   
  
  TCanvas *c_ThetaP = new TCanvas("ThetaP","ThetaP",1200,900);
  c_ThetaP->Divide(4,4);
  for(int k=0;k<4;k++){
    for(int l=0;l<4;l++){
      gPad->SetLogz(1);
      c_ThetaP->cd(k*4+l+1);
      hThetaP[k][l]->Draw("colz");
    }
  }
  
  TCanvas *c_kinematics = new TCanvas("kinematics","kinematics",1200,800);
  c_kinematics->Divide(2,2);  
  c_kinematics->cd(1);
  hQ2W->Draw("colz");
  c_kinematics->cd(2);
  htW->Draw("colz");
  c_kinematics->cd(3);
  htminW->Draw("colz");
  htmaxW->Draw("colz same");  
  c_kinematics->cd(4);
  ht->Draw(); 

  
  TCanvas *can4 = new TCanvas("can4","",1200,800);
  can4->Divide(3,2);

  can4->cd(1);
  hkpth->GetXaxis()->SetTitle("scattered electron #theta_{SHRS} (deg)");
  hkpth->Draw();
 

  can4->cd(4);
  hprth->GetXaxis()->SetTitle("recoiling proton #theta_{HRS} (deg)");
  hprth->Draw();


  can4->cd(2);
  hkpph->GetXaxis()->SetTitle("scattered electron #phi_{lab} (deg)");
  hkpph->Draw();

  can4->cd(5);
  hprph->GetXaxis()->SetTitle("recoiling proton #phi_{lab} (deg)");
  hprph->Draw();

  can4->cd(3);
  hkpp->GetXaxis()->SetTitle("scattered electron momentum (GeV)");
  hkpp->Draw();

  can4->cd(6);
  hprp->GetXaxis()->SetTitle("recoiling proton momentum (GeV)");
  hprp->Draw();

  TCanvas *can5 = new TCanvas("can5","",900,900);
  hemscat->SetMarkerColor(kRed);
  hepscat->SetMarkerColor(kBlue); 

  hepscat->GetXaxis()->SetTitle("x_{lab}");
  hepscat->GetXaxis()->SetTitle("y_{lab}");
  hepscat->Draw();
  hemscat->Draw("same");

  cout << "BH 3-3.25 GeV " <<  hlepIM2->Integral(20,45) << endl;  //pure sum to count , no width
  cout << "BH 1.3-1.55 GeV " <<  hlepIM->Integral(130,155) << endl;  //pure sum to count , no width  
     
outputfile->Write();
outputfile->Flush();      

}
