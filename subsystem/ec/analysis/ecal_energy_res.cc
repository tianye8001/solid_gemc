/*
Author : Rakitha Beminiwattha, rakithab@jlab.org
Wed Jun 29 12:58:25 EDT 2016
file name : ecal_energy_res.cc

This is the first script to access GEMC based ECAL. Ultimate goal is to get energy resolution for ECAL

to run,
       ./ecal_energy_res 

It is problematic to access Trees with std::vector data in it using TChain. The issues fixed by following the thread discussion at, https://root.cern.ch/phpBB3/viewtopic.php?t=4939
       
 */

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <new>
#include <cstdlib>
#include <math.h>

#include <TRandom.h>
#include <TRandom3.h>
#include <TApplication.h>
#include <TSystem.h>

#include <TH2F.h>
#include <TTree.h>
#include <TF1.h>
#include <TProfile.h>
#include <Rtypes.h>
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TString.h> 
#include <TDatime.h>
#include <TStopwatch.h>
#include <stdexcept>
#include <time.h>
#include <cstdio>
#include <map>
#include <cassert>

#include <TMath.h>
#include <TStyle.h>
#include <TPaveStats.h>

#include <TCanvas.h>
#include <TLine.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFrame.h>
#include <TObjArray.h>
#include <TVector2.h>
#include <TVirtualFitter.h>

#include "ecal.h"

#define __IO_MAXHIT 10000

const Double_t DEG=180./3.1415926;


//Generated input bank
vector<Int_t> *fGen_pid=0;
vector<Double_t> *fGen_Px=0;
vector<Double_t> *fGen_Py=0;
vector<Double_t> *fGen_Pz=0;
vector<Double_t> *fGen_vx=0;
vector<Double_t> *fGen_vy=0;
vector<Double_t> *fGen_vz=0;

//FLUX bank
vector<int> *fFluxHit_n=0;
vector<int> *fFluxHit_id=0;
vector<Int_t> *fFluxHit_tid=0;
vector<Int_t> *fFluxHit_mtid=0;
vector<Int_t> *fFluxHit_otid=0;
vector<Int_t> *fFluxHit_pid=0;
vector<Int_t> *fFluxHit_mpid=0;
vector<Double_t> *fFluxHit_trackE=0;
vector<Double_t> *fFluxHit_totEdep=0;
vector<Double_t> *fFluxHit_Px=0;
vector<Double_t> *fFluxHit_Py=0;
vector<Double_t> *fFluxHit_Pz=0;
vector<Double_t> *fFluxHit_Avg_x=0;
vector<Double_t> *fFluxHit_Avg_y=0;
vector<Double_t> *fFluxHit_Avg_z=0;
vector<Double_t> *fFluxHit_Avg_lx=0;
vector<Double_t> *fFluxHit_Avg_ly=0;
vector<Double_t> *fFluxHit_Avg_lz=0;
vector<Double_t> *fFluxHit_vx=0;
vector<Double_t> *fFluxHit_vy=0;
vector<Double_t> *fFluxHit_vz=0;
vector<Double_t> *fFluxHit_mvx=0;
vector<Double_t> *fFluxHit_mvy=0;
vector<Double_t> *fFluxHit_mvz=0;
vector<Double_t> *fFluxHit_Avg_t=0;

TBranch *bFluxHit_id = 0;
TBranch *bFluxHit_n = 0;
TBranch *bFluxHit_pid = 0;
TBranch *bFluxHit_mpid = 0;
TBranch *bFluxHit_tid = 0;
TBranch *bFluxHit_mtid = 0;
TBranch *bFluxHit_otid = 0;
TBranch *bFluxHit_trackE = 0;
TBranch *bFluxHit_totEdep = 0;
TBranch *bFluxHit_Avg_x = 0;
TBranch *bFluxHit_Avg_y = 0;
TBranch *bFluxHit_Avg_z = 0;
TBranch *bFluxHit_Avg_lx = 0;
TBranch *bFluxHit_Avg_ly = 0;
TBranch *bFluxHit_Avg_lz = 0;
TBranch *bFluxHit_Px = 0;
TBranch *bFluxHit_Py = 0;
TBranch *bFluxHit_Pz = 0;
TBranch *bFluxHit_vx = 0;
TBranch *bFluxHit_vy = 0;
TBranch *bFluxHit_vz = 0;
TBranch *bFluxHit_mvx = 0;
TBranch *bFluxHit_mvy = 0;
TBranch *bFluxHit_mvz = 0;
TBranch *bFluxHit_t = 0;

TChain * TGEMC_Flux;

//EC bank
vector<int> *fECHit_n=0;
vector<int> *fECHit_id=0;
vector<Int_t> *fECHit_tid=0;
vector<Int_t> *fECHit_mtid=0;
vector<Int_t> *fECHit_otid=0;
vector<Int_t> *fECHit_pid=0;
vector<Int_t> *fECHit_mpid=0;
vector<Double_t> *fECHit_trackE=0;
vector<Double_t> *fECHit_totEdep=0;
vector<Double_t> *fECHit_Px=0;
vector<Double_t> *fECHit_Py=0;
vector<Double_t> *fECHit_Pz=0;
vector<Double_t> *fECHit_Avg_x=0;
vector<Double_t> *fECHit_Avg_y=0;
vector<Double_t> *fECHit_Avg_z=0;
vector<Double_t> *fECHit_Avg_lx=0;
vector<Double_t> *fECHit_Avg_ly=0;
vector<Double_t> *fECHit_Avg_lz=0;
vector<Double_t> *fECHit_vx=0;
vector<Double_t> *fECHit_vy=0;
vector<Double_t> *fECHit_vz=0;
vector<Double_t> *fECHit_mvx=0;
vector<Double_t> *fECHit_mvy=0;
vector<Double_t> *fECHit_mvz=0;
vector<Double_t> *fECHit_Avg_t=0;

TBranch *bECHit_id = 0;
TBranch *bECHit_n = 0;
TBranch *bECHit_pid = 0;
TBranch *bECHit_mpid = 0;
TBranch *bECHit_tid = 0;
TBranch *bECHit_mtid = 0;
TBranch *bECHit_otid = 0;
TBranch *bECHit_trackE = 0;
TBranch *bECHit_totEdep = 0;
TBranch *bECHit_Avg_x = 0;
TBranch *bECHit_Avg_y = 0;
TBranch *bECHit_Avg_z = 0;
TBranch *bECHit_Avg_lx = 0;
TBranch *bECHit_Avg_ly = 0;
TBranch *bECHit_Avg_lz = 0;
TBranch *bECHit_Px = 0;
TBranch *bECHit_Py = 0;
TBranch *bECHit_Pz = 0;
TBranch *bECHit_vx = 0;
TBranch *bECHit_vy = 0;
TBranch *bECHit_vz = 0;
TBranch *bECHit_mvx = 0;
TBranch *bECHit_mvy = 0;
TBranch *bECHit_mvz = 0;
TBranch *bECHit_t = 0;

TChain * TGEMC_EC;


Int_t pid_gen=0;
Double_t theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;
Int_t FluxHit_detector_ID,FluxHit_subdetector_ID,FluxHit_subsubdetector_ID,FluxHit_component_ID;
Int_t ECHit_detector_ID,ECHit_subdetector_ID,ECHit_subsubdetector_ID,ECHit_component_ID;


//routines for properly access vector based TTree using TChain
void SetFluxBranchAddresses();
void GetFluxEntryByBranch(Long64_t local);

void SetECBranchAddresses();
void GetECEntryByBranch(Long64_t local);

using namespace std;
using namespace std::tr1;

void set_plot_style();


int main(Int_t argc,Char_t* argv[]) { 

  //set the timer
  TStopwatch watch;
  watch.Start();


  TVirtualFitter::SetDefaultFitter("Minuit2");

  TApplication theApp("App",&argc,argv);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("eMr");
  gStyle->SetOptFit();
  set_plot_style();

  Int_t pid_ec;

  //bin resolution for histograms
  Int_t mom_bins = 100;

  TH1F *Gen_mom_distr = new TH1F("Gen_mom_distr","Primary Track Momentum;Momentum (MeV)",mom_bins ,1000,8000);
  TH1F *Gen_theta_distr = new TH1F("Gentheta_distr","Primary Track Theta;#theta (deg)",mom_bins ,10,50);  
  TH1F *ECALDet_mom_distr = new TH1F("ECALDet_mom_distr","ECAL Front All e^{-} Track Momentum;Momentum (MeV)",mom_bins ,1000,8000);
  TH1F *htotEdep_ec_shower=new TH1F("htotEdep_ec_shower","ec shower;totEdep(MeV);",100,0,4000);
  TH1F *htotEdep_ec_preshower=new TH1F("htotEdep_ec_preshower","ec preshower;totEdep(MeV);",100,0,500);
  //Generated input bank
  TChain * TGEMC_Gen =new TChain("generated");
  
  //TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1001.root");
  Int_t err = TGEMC_Gen->SetBranchAddress("pid",&fGen_pid);
  printf(" TGEMC_Gen branch status %i \n",err);
  TGEMC_Gen->SetBranchAddress("px",&fGen_Px);
  TGEMC_Gen->SetBranchAddress("py",&fGen_Py);
  TGEMC_Gen->SetBranchAddress("pz",&fGen_Pz);
  TGEMC_Gen->SetBranchAddress("vx",&fGen_vx);
  TGEMC_Gen->SetBranchAddress("vy",&fGen_vy);
  TGEMC_Gen->SetBranchAddress("vz",&fGen_vz);

  


  //Flux bank
  
  //TFile *file=new TFile("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1001.root");
  //TTree *TGEMC_Flux = (TTree*) file->Get("flux");
  TGEMC_Flux =new TChain("flux");
  //TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1001.root");

  SetFluxBranchAddresses();
  
  //EC bank
  TGEMC_EC =new TChain("solid_ec");
  //TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1001.root");

  SetECBranchAddresses();

  Int_t nentries = (Int_t)TGEMC_Flux->GetEntries();
  printf("Entries = %i \n",nentries);
  Int_t treenumber=-1;
  Int_t ECtreenumber=-1;

  for (Int_t i=0; i<nentries; i++) {
    Long64_t local;
    //Generated input bank
    /*
    TGEMC_Gen->GetEntry(i);
    for (int j=0;j<fGen_pid->size();j++) {
      pid_gen=fGen_pid->at(j);
      //printf("pid  %i \n",pid_gen);
      px_gen=fGen_Px->at(j);
      py_gen=fGen_Py->at(j);
      pz_gen=fGen_Pz->at(j);
      vx_gen=fGen_vx->at(j);
      vy_gen=fGen_vy->at(j);
      vz_gen=fGen_vz->at(j);
      p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
      theta_gen=TMath::ACos(pz_gen/p_gen)*DEG;
      phi_gen=TMath::ATan2(py_gen,px_gen)*DEG;
      Gen_mom_distr->Fill(p_gen);
      Gen_theta_distr->Fill(theta_gen);
    }
    
    //FLUX bank
    
    //TGEMC_Flux->GetEntry(i);
    local = TGEMC_Flux->GetEntry(i);
    if (treenumber != TGEMC_Flux->GetTreeNumber()){
      SetFluxBranchAddresses();
      treenumber = TGEMC_Flux->GetTreeNumber();
    }
    GetFluxEntryByBranch(local);
    //printf("%i %i \n",fFluxHit_id->size(),fFluxHit_trackE->size());
    
    for (int j = 0; j<fFluxHit_id->size(); j++){
      FluxHit_detector_ID=fFluxHit_id->at(j)/1000000;
      FluxHit_subdetector_ID=(fFluxHit_id->at(j)%1000000)/100000;
      FluxHit_subsubdetector_ID=((fFluxHit_id->at(j)%1000000)%100000)/10000;
      FluxHit_component_ID=fFluxHit_id->at(j)%10000; 
      if (FluxHit_detector_ID==3 && FluxHit_subdetector_ID == 1 && FluxHit_subsubdetector_ID == 1 && fFluxHit_pid->at(j)==11){
	//cout << "particle mom entering EC " << fFluxHit_trackE->at(j) << endl;         
	ECALDet_mom_distr->Fill(fFluxHit_trackE->at(j));	
      }
    }
    */
    //EC bank
    local = TGEMC_EC->GetEntry(i);
    if (ECtreenumber != TGEMC_Flux->GetTreeNumber()){
      SetECBranchAddresses();
      ECtreenumber = TGEMC_EC->GetTreeNumber();
    }
    GetECEntryByBranch(local);
    Double_t totEdep_shower=0;
    Double_t totEdep_preshower=0;
    for (int j = 0; j<fECHit_id->size(); j++){
      ECHit_detector_ID=fECHit_id->at(j)/1000000;
      ECHit_subdetector_ID=(fECHit_id->at(j)%1000000)/100000;
      ECHit_subsubdetector_ID=((fECHit_id->at(j)%1000000)%100000)/10000;
      ECHit_component_ID=fECHit_id->at(j)%10000;
       if (ECHit_detector_ID==3 && ECHit_subdetector_ID == 1 && ECHit_subsubdetector_ID == 0){
	 totEdep_shower+=fECHit_totEdep->at(j);
       }
       if (ECHit_detector_ID==3 && ECHit_subdetector_ID == 1 && ECHit_subsubdetector_ID == 1){
	 totEdep_preshower+=fECHit_totEdep->at(j);
       }

    }
    //fill the histogram
    htotEdep_ec_shower->Fill(totEdep_shower);
    htotEdep_ec_preshower->Fill(totEdep_preshower);
  }

  TCanvas * canvas_kinematics_ecal_front = new TCanvas("canvas_kinematics_ecal_front","canvas_kinematics_ecal_front",1400,400);
  canvas_kinematics_ecal_front->Divide(3,1);
  canvas_kinematics_ecal_front->cd(1);
  Gen_mom_distr->Draw();
  canvas_kinematics_ecal_front->cd(2);
  Gen_theta_distr->Draw();
  canvas_kinematics_ecal_front->cd(3);
  ECALDet_mom_distr->Draw();

  TCanvas * canvas_ecal_edep = new TCanvas("canvas_ecal_edep","canvas_ecal_edep",1000,400);
  canvas_ecal_edep->Divide(2,1);
  canvas_ecal_edep->cd(1);
  htotEdep_ec_shower->Draw();
  canvas_ecal_edep->cd(2);
  htotEdep_ec_preshower->Draw();

  watch.Stop();
  printf("Total Time %3.4f min \n Completed, Exit now :) \n",watch.RealTime()/60);
  theApp.Run();
  return(1);
}

void SetFluxBranchAddresses(){
  TGEMC_Flux->SetBranchAddress("hitn",&fFluxHit_n,&bFluxHit_n);
  TGEMC_Flux->SetBranchAddress("id",&fFluxHit_id,&bFluxHit_id);
  TGEMC_Flux->SetBranchAddress("pid",&fFluxHit_pid,&bFluxHit_pid);
  TGEMC_Flux->SetBranchAddress("mpid",&fFluxHit_mpid,&bFluxHit_mpid);
  TGEMC_Flux->SetBranchAddress("tid",&fFluxHit_tid,&bFluxHit_tid);
  TGEMC_Flux->SetBranchAddress("mtid",&fFluxHit_mtid,&bFluxHit_mtid);
  TGEMC_Flux->SetBranchAddress("otid",&fFluxHit_otid,&bFluxHit_otid);
  TGEMC_Flux->SetBranchAddress("trackE",&fFluxHit_trackE,&bFluxHit_trackE);
  TGEMC_Flux->SetBranchAddress("totEdep",&fFluxHit_totEdep,&bFluxHit_totEdep);
  TGEMC_Flux->SetBranchAddress("avg_x",&fFluxHit_Avg_x,&bFluxHit_Avg_x);
  TGEMC_Flux->SetBranchAddress("avg_y",&fFluxHit_Avg_y,&bFluxHit_Avg_y);
  TGEMC_Flux->SetBranchAddress("avg_z",&fFluxHit_Avg_z,&bFluxHit_Avg_z);
  TGEMC_Flux->SetBranchAddress("avg_lx",&fFluxHit_Avg_lx,&bFluxHit_Avg_lx);
  TGEMC_Flux->SetBranchAddress("avg_ly",&fFluxHit_Avg_ly,&bFluxHit_Avg_ly);
  TGEMC_Flux->SetBranchAddress("avg_lz",&fFluxHit_Avg_lz,&bFluxHit_Avg_lz);
  TGEMC_Flux->SetBranchAddress("px",&fFluxHit_Px,&bFluxHit_Px);
  TGEMC_Flux->SetBranchAddress("py",&fFluxHit_Py,&bFluxHit_Py);
  TGEMC_Flux->SetBranchAddress("pz",&fFluxHit_Pz,&bFluxHit_Pz);
  TGEMC_Flux->SetBranchAddress("vx",&fFluxHit_vx,&bFluxHit_vx);
  TGEMC_Flux->SetBranchAddress("vy",&fFluxHit_vy,&bFluxHit_vy);
  TGEMC_Flux->SetBranchAddress("vz",&fFluxHit_vz,&bFluxHit_vz);
  TGEMC_Flux->SetBranchAddress("mvx",&fFluxHit_mvx,&bFluxHit_mvx);
  TGEMC_Flux->SetBranchAddress("mvy",&fFluxHit_mvy,&bFluxHit_mvy);
  TGEMC_Flux->SetBranchAddress("mvz",&fFluxHit_mvz,&bFluxHit_mvz);
  TGEMC_Flux->SetBranchAddress("avg_t",&fFluxHit_Avg_t,&bFluxHit_t);  

};

void GetFluxEntryByBranch(Long64_t local){
  bFluxHit_id->GetEntry(local);  
  bFluxHit_n->GetEntry(local);
  bFluxHit_pid->GetEntry(local);  
  bFluxHit_mpid->GetEntry(local);  
  bFluxHit_tid->GetEntry(local);  
  bFluxHit_mtid->GetEntry(local);  
  bFluxHit_otid->GetEntry(local);  
  bFluxHit_trackE->GetEntry(local); 
  bFluxHit_totEdep->GetEntry(local);  
  bFluxHit_Avg_x->GetEntry(local);  
  bFluxHit_Avg_y->GetEntry(local);  
  bFluxHit_Avg_z->GetEntry(local);  
  bFluxHit_Avg_lx->GetEntry(local);  
  bFluxHit_Avg_ly->GetEntry(local);  
  bFluxHit_Avg_lz->GetEntry(local);  
  bFluxHit_Px->GetEntry(local);  
  bFluxHit_Py->GetEntry(local);  
  bFluxHit_Pz->GetEntry(local);  
  bFluxHit_vx->GetEntry(local);  
  bFluxHit_vy->GetEntry(local);  
  bFluxHit_vz->GetEntry(local);  
  bFluxHit_mvx->GetEntry(local);  
  bFluxHit_mvy->GetEntry(local);  
  bFluxHit_mvz->GetEntry(local);  
  bFluxHit_t->GetEntry(local);
};

void SetECBranchAddresses(){
  //TGEMC_EC->SetBranchAddress("hitn",&fECHit_n,&bECHit_n);
  TGEMC_EC->SetBranchAddress("id",&fECHit_id,&bECHit_id);
  /*
  TGEMC_EC->SetBranchAddress("pid",&fECHit_pid,&bECHit_pid);
  TGEMC_EC->SetBranchAddress("mpid",&fECHit_mpid,&bECHit_mpid);
  TGEMC_EC->SetBranchAddress("tid",&fECHit_tid,&bECHit_tid);
  TGEMC_EC->SetBranchAddress("mtid",&fECHit_mtid,&bECHit_mtid);
  TGEMC_EC->SetBranchAddress("otid",&fECHit_otid,&bECHit_otid);
  TGEMC_EC->SetBranchAddress("trackE",&fECHit_trackE,&bECHit_trackE);
  */
  TGEMC_EC->SetBranchAddress("totEdep",&fECHit_totEdep,&bECHit_totEdep);
  /*
  TGEMC_EC->SetBranchAddress("avg_x",&fECHit_Avg_x,&bECHit_Avg_x);
  TGEMC_EC->SetBranchAddress("avg_y",&fECHit_Avg_y,&bECHit_Avg_y);
  TGEMC_EC->SetBranchAddress("avg_z",&fECHit_Avg_z,&bECHit_Avg_z);
  TGEMC_EC->SetBranchAddress("avg_lx",&fECHit_Avg_lx,&bECHit_Avg_lx);
  TGEMC_EC->SetBranchAddress("avg_ly",&fECHit_Avg_ly,&bECHit_Avg_ly);
  TGEMC_EC->SetBranchAddress("avg_lz",&fECHit_Avg_lz,&bECHit_Avg_lz);
  TGEMC_EC->SetBranchAddress("px",&fECHit_Px,&bECHit_Px);
  TGEMC_EC->SetBranchAddress("py",&fECHit_Py,&bECHit_Py);
  TGEMC_EC->SetBranchAddress("pz",&fECHit_Pz,&bECHit_Pz);
  TGEMC_EC->SetBranchAddress("vx",&fECHit_vx,&bECHit_vx);
  TGEMC_EC->SetBranchAddress("vy",&fECHit_vy,&bECHit_vy);
  TGEMC_EC->SetBranchAddress("vz",&fECHit_vz,&bECHit_vz);
  TGEMC_EC->SetBranchAddress("mvx",&fECHit_mvx,&bECHit_mvx);
  TGEMC_EC->SetBranchAddress("mvy",&fECHit_mvy,&bECHit_mvy);
  TGEMC_EC->SetBranchAddress("mvz",&fECHit_mvz,&bECHit_mvz);
  TGEMC_EC->SetBranchAddress("avg_t",&fECHit_Avg_t,&bECHit_t);  
  */
};

void GetECEntryByBranch(Long64_t local){
  bECHit_id->GetEntry(local);  
  /*  
  bECHit_n->GetEntry(local);  
  bECHit_pid->GetEntry(local);  
  bECHit_mpid->GetEntry(local);  
  bECHit_tid->GetEntry(local);  
  bECHit_mtid->GetEntry(local);  
  bECHit_otid->GetEntry(local);  
  bECHit_trackE->GetEntry(local); 
  */
  bECHit_totEdep->GetEntry(local);  
  /*
  bECHit_Avg_x->GetEntry(local);  
  bECHit_Avg_y->GetEntry(local);  
  bECHit_Avg_z->GetEntry(local);  
  bECHit_Avg_lx->GetEntry(local);  
  bECHit_Avg_ly->GetEntry(local);  
  bECHit_Avg_lz->GetEntry(local);  
  bECHit_Px->GetEntry(local);  
  bECHit_Py->GetEntry(local);  
  bECHit_Pz->GetEntry(local);  
  bECHit_vx->GetEntry(local);  
  bECHit_vy->GetEntry(local);  
  bECHit_vz->GetEntry(local);  
  bECHit_mvx->GetEntry(local);  
  bECHit_mvy->GetEntry(local);  
  bECHit_mvz->GetEntry(local);  
  bECHit_t->GetEntry(local);
  */
};

void set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}
