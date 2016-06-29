/*
Author : Rakitha Beminiwattha, rakithab@jlab.org
Wed Jun 29 12:58:25 EDT 2016
file name : ecal_energy_res.cc

This is the first script to access GEMC based ECAL. Ultimate goal is to get energy resolution for ECAL

to run,
       ./ecal_energy_res 
       
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
vector<Int_t> *fFluxHit_n=0;
vector<Int_t> *fFluxHit_id=0;
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

Int_t pid_gen=0;
Double_t theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;
Int_t FluxHit_detector_ID,FluxHit_subdetector_ID,FluxHit_subsubdetector_ID,FluxHit_component_ID;


using namespace std;
using namespace std::tr1;

void set_plot_style();


int main(Int_t argc,Char_t* argv[]) { 

  TVirtualFitter::SetDefaultFitter("Minuit2");

  TApplication theApp("App",&argc,argv);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("eMr");
  gStyle->SetOptFit();
  set_plot_style();

  //bin resolution for histograms
  Int_t mom_bins = 100;

  TH1F *Gen_mom_distr = new TH1F("Gen_mom_distr","Primary Track Momentum;Momentum (MeV)",mom_bins ,1000,8000);
  TH1F *Gen_theta_distr = new TH1F("Gentheta_distr","Primary Track Theta;#theta (deg)",mom_bins ,10,50);  
  TH1F *ECALDet_mom_distr = new TH1F("ECALDet_mom_distr","ECAL Front Primary Track Momentum;Momentum (MeV)",mom_bins ,1000,8000);

  //Generated input bank
  TChain * TGEMC_Gen =new TChain("generated");
  TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  TGEMC_Gen->SetBranchAddress("pid",&fGen_pid);
  TGEMC_Gen->SetBranchAddress("px",&fGen_Px);
  TGEMC_Gen->SetBranchAddress("py",&fGen_Py);
  TGEMC_Gen->SetBranchAddress("pz",&fGen_Pz);
  TGEMC_Gen->SetBranchAddress("vx",&fGen_vx);
  TGEMC_Gen->SetBranchAddress("vy",&fGen_vy);
  TGEMC_Gen->SetBranchAddress("vz",&fGen_vz);




  //Flux bank
  TChain * TGEMC_Flux =new TChain("flux");
  TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");

  TGEMC_Flux->SetBranchAddress("hitn",&fFluxHit_n);
  TGEMC_Flux->SetBranchAddress("id",&fFluxHit_id);
  TGEMC_Flux->SetBranchAddress("pid",&fFluxHit_pid);
  TGEMC_Flux->SetBranchAddress("mpid",&fFluxHit_mpid);
  TGEMC_Flux->SetBranchAddress("tid",&fFluxHit_tid);
  TGEMC_Flux->SetBranchAddress("mtid",&fFluxHit_mtid);
  TGEMC_Flux->SetBranchAddress("otid",&fFluxHit_otid);
  TGEMC_Flux->SetBranchAddress("trackE",&fFluxHit_trackE);
  TGEMC_Flux->SetBranchAddress("totEdep",&fFluxHit_totEdep);
  TGEMC_Flux->SetBranchAddress("avg_x",&fFluxHit_Avg_x);
  TGEMC_Flux->SetBranchAddress("avg_y",&fFluxHit_Avg_y);
  TGEMC_Flux->SetBranchAddress("avg_z",&fFluxHit_Avg_z);
  TGEMC_Flux->SetBranchAddress("avg_lx",&fFluxHit_Avg_lx);
  TGEMC_Flux->SetBranchAddress("avg_ly",&fFluxHit_Avg_ly);
  TGEMC_Flux->SetBranchAddress("avg_lz",&fFluxHit_Avg_lz);
  TGEMC_Flux->SetBranchAddress("px",&fFluxHit_Px);
  TGEMC_Flux->SetBranchAddress("py",&fFluxHit_Py);
  TGEMC_Flux->SetBranchAddress("pz",&fFluxHit_Pz);
  TGEMC_Flux->SetBranchAddress("vx",&fFluxHit_vx);
  TGEMC_Flux->SetBranchAddress("vy",&fFluxHit_vy);
  TGEMC_Flux->SetBranchAddress("vz",&fFluxHit_vz);
  TGEMC_Flux->SetBranchAddress("mvx",&fFluxHit_mvx);
  TGEMC_Flux->SetBranchAddress("mvy",&fFluxHit_mvy);
  TGEMC_Flux->SetBranchAddress("mvz",&fFluxHit_mvz);
  TGEMC_Flux->SetBranchAddress("avg_t",&fFluxHit_Avg_t);

  Int_t nentries = (Int_t)TGEMC_Flux->GetEntries();
  printf("Entries = %i \n",nentries);

  for (Int_t i=0; i<nentries; i++) {
    //Generated input bank
    TGEMC_Gen->GetEntry(i);
    for (int j=0;j<fGen_pid->size();j++) {
      pid_gen=fGen_pid->at(j);
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
    TGEMC_Flux->GetEntry(i);
    //printf("%i \n",fFluxHit_n->size());
    for (int j = 0; j<fFluxHit_n->size(); j++){
      FluxHit_detector_ID=fFluxHit_id->at(j)/1000000;
      FluxHit_subdetector_ID=(fFluxHit_id->at(j)%1000000)/100000;
      FluxHit_subsubdetector_ID=((fFluxHit_id->at(j)%1000000)%100000)/10000;
      FluxHit_component_ID=fFluxHit_id->at(j)%10000;      

      if (FluxHit_detector_ID==3 && FluxHit_subdetector_ID == 1 && FluxHit_subsubdetector_ID == 1){
	cout << "particle mom entering EC " << fFluxHit_trackE->at(j) << endl;         
	ECALDet_mom_distr->Fill(fFluxHit_trackE->at(j));
      }
    }
  }

  TCanvas * canvas_kinematics_ecal_front = new TCanvas("canvas_kinematics_ecal_front","canvas_kinematics_ecal_front",1400,400);
  canvas_kinematics_ecal_front->Divide(3,1);
  canvas_kinematics_ecal_front->cd(1);
  Gen_mom_distr->Draw();
  canvas_kinematics_ecal_front->cd(2);
  Gen_theta_distr->Draw();
  canvas_kinematics_ecal_front->cd(3);
  ECALDet_mom_distr->Draw();


  theApp.Run();
  return(1);
}


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
