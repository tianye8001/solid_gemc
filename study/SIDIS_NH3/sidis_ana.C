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

void sidis_ana(string input_filename)
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  
  const double DEG=180./3.1415926;
  
  bool Is_SIDIS_He3=false,Is_SIDIS_NH3=false;
  if (input_filename.find("SIDIS_He3",0) != string::npos) Is_SIDIS_He3=true;
  else if (input_filename.find("SIDIS_NH3",0) != string::npos) Is_SIDIS_NH3=true;
  else {cout << "not SIDIS " << endl; return;}
  
  ///radius cut standard as particles can travel 30cm in Z before leave calorimeter
  ///SIDIS largeangle EC outerradius is at 140cm
  double rout_cut_FA,rin_cut_FA,rout_cut_LA,rin_cut_LA;
  if (Is_SIDIS_He3 || Is_SIDIS_NH3){
    rout_cut_FA=220;     //target at -350,ec front at 415 with angle 15
    //   rin_cut_FA=98;   //cut at the actual edge 
    rin_cut_FA=105;   //cut at the actual edge
    rout_cut_LA=127;   //target at -350,ec front at -65 with angle 24
    rin_cut_LA=83;   //cut at the actual edge
    cout << " SIDIS_He3 and SIDIS_NH3 rcut " << rin_cut_FA << " " << rout_cut_FA << " " << rin_cut_LA << " " << rout_cut_LA <<  endl;
  }
  else {cout << "not SIDIS NH3 or He3" << endl; return;}
  
  
  char the_filename[200];
  sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());
  
  char output_filename[200];
  sprintf(output_filename, "%s_output.root",the_filename);
  TFile *outputfile=new TFile(output_filename, "recreate");
  
  TH2F *hacceptance_ThetaP_forwardangle,*hacceptance_ThetaP_largeangle,*hacceptance_ThetaP_overall;
  TH3F *hacceptance_ThetaPhiP_forwardangle,*hacceptance_ThetaPhiP_largeangle;
  
  const int n=2;
  
  TH2F *hgen_ThetaP=new TH2F("gen_ThetaP","gen_ThetaP",250,0,50,220,0,11);
  TH2F *hgen_ThetaPhi=new TH2F("gen_ThetaPhi","gen_ThetaPhi",250,0,50,360,-180,180);     
  TH2F *hgen_PhiP=new TH2F("gen_PhiP","gen_PhiP",360,-180,180,220,0,11);
  TH3F *hgen_ThetaPhiP=new TH3F("gen_ThetaPhiP","gen_ThetaPhiP",100,0,50,180,-180,180,110,0,11);   
  
  TH2F *hgen_ThetaVz=new TH2F("gen_ThetaVz","gen_ThetaVz",350,15,50,50,-15,35);
  TH2F *hgen_ThetaVr=new TH2F("gen_ThetaVr","gen_ThetaVr",350,15,50,50,0,1);
  
  TH2F *hhit_rMom[n];
  TH2F *hhit_phidiffMom[n],*hhit_thetadiffMom[n];
  TH2F *hhit_rz=new TH2F("hit_rz","hit_rz",1000,-400,600,300,0,300);  
  
  char *title[n]={"FAEC","LAEC"};
  for(int i=0;i<n;i++){
    char hstname[100];   
    sprintf(hstname,"hit_rMom_%i",i);
    hhit_rMom[i]=new TH2F(hstname,hstname,300,0,300,220,0,11);  
    sprintf(hstname,"hit_phidiffMom_%i",i);
    hhit_phidiffMom[i]=new TH2F(hstname,hstname,7200,-360,360,220,0,11);  
    sprintf(hstname,"hit_thetadiffMom_%i",i);
    hhit_thetadiffMom[i]=new TH2F(hstname,hstname,3600,-180,180,220,0,11);  
  }
  
  TH2F *hhit_xy_gem[6][2],*hhit_PhiR_gem[6][2];
  for(int i=0;i<6;i++){
    for(int j=0;j<2;j++){
      char hstname[100];
      sprintf(hstname,"hit_xy_gem_%i_%i",i,j);
      hhit_xy_gem[i][j]=new TH2F(hstname,hstname,300,-150,150,300,-150,150);        
      sprintf(hstname,"hit_PhiR_gem_%i_%i",i,j);
      hhit_PhiR_gem[i][j]=new TH2F(hstname,hstname,360,-180,180,300,0,150);   
    }
  }
  
  TH2F *hhit_xy_ec[n][2],*hhit_PhiR_ec[n][2];
  for(int i=0;i<n;i++){
    for(int j=0;j<2;j++){
      char hstname[100];
      sprintf(hstname,"hit_xy_ec_%i_%i",i,j);
      hhit_xy_ec[i][j]=new TH2F(hstname,hstname,600,-300,300,600,-300,300);        
      sprintf(hstname,"hit_PhiR_ec_%i_%i",i,j);
      hhit_PhiR_ec[i][j]=new TH2F(hstname,hstname,360,-180,180,300,0,300);       
    }
  }
   
  
  TFile *file=new TFile(input_filename.c_str());
  if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename << endl;    
  
  TTree *tree_header = (TTree*) file->Get("header");
  vector <int> *evn=0,*evn_type=0;
  vector <double> *beamPol=0;
  vector <int> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
  tree_header->SetBranchAddress("evn",&evn);
  tree_header->SetBranchAddress("evn_type",&evn_type);
  tree_header->SetBranchAddress("beamPol",&beamPol);
  tree_header->SetBranchAddress("var1",&var1);
  tree_header->SetBranchAddress("var2",&var2);
  tree_header->SetBranchAddress("var3",&var3);
  tree_header->SetBranchAddress("var4",&var4);
  tree_header->SetBranchAddress("var5",&var5);
  tree_header->SetBranchAddress("var6",&var6);
  tree_header->SetBranchAddress("var7",&var7);
  tree_header->SetBranchAddress("var8",&var8);
  
  TTree *tree_generated = (TTree*) file->Get("generated");
  vector <int> *gen_pid=0;
  vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
  tree_generated->SetBranchAddress("pid",&gen_pid);
  tree_generated->SetBranchAddress("px",&gen_px);
  tree_generated->SetBranchAddress("py",&gen_py);
  tree_generated->SetBranchAddress("pz",&gen_pz);
  tree_generated->SetBranchAddress("vx",&gen_vx);
  tree_generated->SetBranchAddress("vy",&gen_vy);
  tree_generated->SetBranchAddress("vz",&gen_vz);
  
  TTree *tree_flux = (TTree*) file->Get("flux");
  vector<int> *flux_id=0,*flux_hitn=0;
  vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
  vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
  tree_flux->SetBranchAddress("hitn",&flux_hitn);
  tree_flux->SetBranchAddress("id",&flux_id);
  tree_flux->SetBranchAddress("pid",&flux_pid);
  tree_flux->SetBranchAddress("mpid",&flux_mpid);
  tree_flux->SetBranchAddress("tid",&flux_tid);
  tree_flux->SetBranchAddress("mtid",&flux_mtid);
  tree_flux->SetBranchAddress("otid",&flux_otid);
  tree_flux->SetBranchAddress("trackE",&flux_trackE);
  tree_flux->SetBranchAddress("totEdep",&flux_totEdep);
  tree_flux->SetBranchAddress("avg_x",&flux_avg_x);
  tree_flux->SetBranchAddress("avg_y",&flux_avg_y);
  tree_flux->SetBranchAddress("avg_z",&flux_avg_z);
  tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);
  tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);
  tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);
  tree_flux->SetBranchAddress("px",&flux_px);
  tree_flux->SetBranchAddress("py",&flux_py);
  tree_flux->SetBranchAddress("pz",&flux_pz);
  tree_flux->SetBranchAddress("vx",&flux_vx);
  tree_flux->SetBranchAddress("vy",&flux_vy);
  tree_flux->SetBranchAddress("vz",&flux_vz);
  tree_flux->SetBranchAddress("mvx",&flux_mvx);
  tree_flux->SetBranchAddress("mvy",&flux_mvy);
  tree_flux->SetBranchAddress("mvz",&flux_mvz);
  tree_flux->SetBranchAddress("avg_t",&flux_avg_t);
  
  // cout << tree_flux->GetEntries() << " " << tree_header->GetEntries() << " " << tree_generated->GetEntries() << endl;
  
  int nevent = (int)tree_generated->GetEntries();
  int nselected = 0;
  cout << "nevent " << nevent << endl;
  
  for (Int_t i=0;i<nevent;i++) { 
    cout << i << "\r";
    //   cout << i << "\n";

    tree_header->GetEntry(i);
    
    tree_flux->GetEntry(i);    
    
    bool Is_out=false;
    for (Int_t j=0;j<flux_hitn->size();j++) {
      int detector_ID=flux_id->at(j)/1000000;
      int subdetector_ID=(flux_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;
      //     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID << endl;  
      
      double hit_r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2));
      double hit_y=flux_avg_y->at(j),hit_x=flux_avg_x->at(j);  
      double hit_phi=atan2(flux_avg_y->at(j),flux_avg_x->at(j))*DEG;
      //     double hit_theta=atan((hit_r/10-sqrt(vx_gen*vx_gen+vy_gen*vy_gen))/(320-vz_gen))*DEG;    
      
      hhit_rz->Fill(flux_avg_z->at(j)/10,hit_r/10);
      
      double Rin[6] = {36,21,25,32,42,55};
      double Rout[6] = {87,98,112,135,100,123};
      
      //check hit on GEM
      if (detector_ID==1) {
	//       if (flux_pid->at(j)==11) {
	hhit_xy_gem[subdetector_ID-1][0]->Fill(hit_x/10,hit_y/10);    
	hhit_PhiR_gem[subdetector_ID-1][0]->Fill(hit_phi,hit_r/10);
	//       }
	//       if (hit_r/10<Rin[subdetector_ID-1] || Rout[subdetector_ID-1]<hit_r/10) {Is_out=true; cout << flux_id->at(j) << endl; }
      }  
      if (detector_ID==3) {
	hhit_xy_ec[subdetector_ID-1][0]->Fill(hit_x/10,hit_y/10);    
	hhit_PhiR_ec[subdetector_ID-1][0]->Fill(hit_phi,hit_r/10);
      }    
       if (detector_ID==3) {
	 // hhit_phidiffMom[subdetector_ID-1]->Fill(hit_phi-phi_gen,p_gen);
	 // hhit_thetadiffMom[subdetector_ID-1]->Fill(hit_theta-theta_gen,p_gen);
	 // hhit_rMom[subdetector_ID-1]->Fill(hit_r/10,p_gen);         
	 
       }
       
       //cut out some part of viritual plane to consider "good" part of EC
       if ((detector_ID==3 && subdetector_ID==1) && (hit_r/10 < rin_cut_FA || rout_cut_FA < hit_r/10)) continue;        
       if ((detector_ID==3 && subdetector_ID==2) && (hit_r/10 < rin_cut_LA || rout_cut_LA < hit_r/10)) continue;
       
       if (Is_SIDIS_He3){
	 //       if(theta_gen>=8) {  //only acceptance 8 deg above
	 if (detector_ID==1) {
	   //       if (flux_pid->at(j)==11) {
	   hhit_xy_gem[subdetector_ID-1][1]->Fill(hit_x/10,hit_y/10);    
	   hhit_PhiR_gem[subdetector_ID-1][1]->Fill(hit_phi,hit_r/10);
	   //       }
	 }       
	 if (detector_ID==3) {
	   hhit_xy_ec[subdetector_ID-1][1]->Fill(hit_x/10,hit_y/10);    
	   hhit_PhiR_ec[subdetector_ID-1][1]->Fill(hit_phi,hit_r/10);
	 }
	 //       }
       }
       else if (Is_SIDIS_NH3){      
	 if ((detector_ID==3 && subdetector_ID==1) && ((-95<hit_phi && hit_phi<-30 && hit_r/10<210)||(48<hit_phi && hit_phi<92 && hit_r/10<205))) continue;
	 if ((detector_ID==3 && subdetector_ID==2) && ((-85<hit_phi && hit_phi<-60)||(65<hit_phi && hit_phi<85))) continue;
	 
	 if ((detector_ID==1 && subdetector_ID==1) && ((-93<hit_phi && hit_phi<-82)||(80<hit_phi && hit_phi<92))) continue;          
	 if ((detector_ID==1 && subdetector_ID==2) && ((-93<hit_phi && hit_phi<-78)||(78<hit_phi && hit_phi<92))) continue;          
	 if ((detector_ID==1 && subdetector_ID==3) && ((-92<hit_phi && hit_phi<-72)||(75<hit_phi && hit_phi<92))) continue;          
	 if ((detector_ID==1 && subdetector_ID==4) && ((-92<hit_phi && hit_phi<-62)||(65<hit_phi && hit_phi<92))) continue;          
	 if ((detector_ID==1 && subdetector_ID==5) && ((-92<hit_phi && hit_phi<-62)||(66<hit_phi && hit_phi<87))) continue;          
	 if ((detector_ID==1 && subdetector_ID==6) && ((-92<hit_phi && hit_phi<-55)||(60<hit_phi && hit_phi<95))) continue;  
	 
	 if (detector_ID==1) {
	   //       if (flux_pid->at(j)==11) {
	   hhit_xy_gem[subdetector_ID-1][1]->Fill(hit_x/10,hit_y/10);    
	   hhit_PhiR_gem[subdetector_ID-1][1]->Fill(hit_phi,hit_r/10);
	   //       }
	 }       
	 if (detector_ID==3) {
	   hhit_xy_ec[subdetector_ID-1][1]->Fill(hit_x/10,hit_y/10);    
	   hhit_PhiR_ec[subdetector_ID-1][1]->Fill(hit_phi,hit_r/10);
	 }	
       }     
       
    } // for loop of j      
    
  } // for loop on i
  file->Close();
  
  /*
  TCanvas *c_hit_rz = new TCanvas("hit_rz","hit_rz",1800,800);
  hhit_rz->Draw("colz");
  
  TCanvas *c_hit_rMom = new TCanvas("hit_rMom","hit_rMom",1800,800);
  c_hit_rMom->Divide(2,1);
  for(int k=0;k<n;k++){
    c_hit_rMom->cd(k+1);
    gPad->SetLogz(1);
    gPad->SetLogy(1);
    hhit_rMom[k]->Draw("colz");
  }
  // c_hit_rMom->SaveAs(Form("%s_%s",the_filename,"hit_rMom.png"));
  
  TCanvas *c_hit_phidiffMom = new TCanvas("hit_phidiffMom","hit_phidiffMom",1800,800);
  c_hit_phidiffMom->Divide(2,1);
  for(int k=0;k<n;k++){
    c_hit_phidiffMom->cd(k+1);
    gPad->SetLogz(1);
    hhit_phidiffMom[k]->Draw("colz");
  }
  // c_hit_phidiffMom->SaveAs(Form("%s_%s",the_filename,"hit_phidiffMom.png"));
  
  TCanvas *c_hit_thetadiffMom = new TCanvas("hit_thetadiffMom","hit_thetadiffMom",1800,800);
  c_hit_thetadiffMom->Divide(2,1);
for(int k=0;k<n;k++){
  c_hit_thetadiffMom->cd(k+1);
  gPad->SetLogz(1);
  hhit_thetadiffMom[k]->Draw("colz");
 }
// c_hit_thetadiffMom->SaveAs(Form("%s_%s",the_filename,"hit_thetadiffMom.png"));
 
*/
 
 TCanvas *c_hit_xy_gem = new TCanvas("hit_xy_gem","hit_xy_gem",1800,800);
 c_hit_xy_gem->Divide(6,2);
 for(int j=0;j<2;j++){
   for(int i=0;i<6;i++){
     c_hit_xy_gem->cd(j*6+i+1);
     gPad->SetLogz(1);
     hhit_xy_gem[i][j]->Draw("colz");
   }}
 
 TCanvas *c_hit_PhiR_gem = new TCanvas("hit_PhiR_gem","hit_PhiR_gem",1800,800);
 c_hit_PhiR_gem->Divide(6,2);
 for(int j=0;j<2;j++){
   for(int i=0;i<6;i++){
     c_hit_PhiR_gem->cd(j*6+i+1);
     gPad->SetLogz(1);
     hhit_PhiR_gem[i][j]->Draw("colz");
   }}
 
 TCanvas *c_hit_xy_ec = new TCanvas("hit_xy_ec","hit_xy_ec",1000,800);
 c_hit_xy_ec->Divide(2,2);
 for(int j=0;j<2;j++){
   for(int i=0;i<2;i++){
     c_hit_xy_ec->cd(j*2+i+1);
     gPad->SetLogz(1);
     hhit_xy_ec[i][j]->Draw("colz");
   }}
 
 TCanvas *c_hit_PhiR_ec = new TCanvas("hit_PhiR_ec","hit_PhiR_ec",1000,800);
 c_hit_PhiR_ec->Divide(2,2);
 for(int j=0;j<2;j++){
   for(int i=0;i<2;i++){
     c_hit_PhiR_ec->cd(j*2+i+1);
     gPad->SetLogz(1);
     hhit_PhiR_ec[i][j]->Draw("colz");
}}
 
 outputfile->Write();
 outputfile->Flush();
}
