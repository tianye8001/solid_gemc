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


//routine to load ecal block id,coordinates, and sector information
void LoadEC_map(TString map_file);
//routine to return ecal block x,y
TVector2 GetECALBlock_coord(Int_t block_id);
Int_t GetECALBlock_sector(Int_t block_id);
//return an pointer to energy deposit for 6 neighboring ecal blocks
Int_t GetECALCluser(Int_t block_id,Int_t *cluster_edep_blockid);

//save x,y,id and sectors and status for which moudles are active only for SIDIS case
Int_t sector[54][50]={{100000}};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
Int_t id[54][50]={{100000}};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
Int_t num_module_in_row[54]={0};
Double_t x[54][50]={{100000}};           
Double_t y[54][50]={{100000}}; 
Int_t status[54][50]={{100000}};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
std::pair<Int_t,Int_t> block_map[2000];

//routines for properly access vector based TTree using TChain
void SetFluxBranchAddresses();
void GetFluxEntryByBranch(Long64_t local);

void SetECBranchAddresses();
void GetECEntryByBranch(Long64_t local);

//get energy resolution
TGraphErrors * GetRMSReolution(TH2F * Difference, Double_t fit_range_up, Double_t fit_range_low);

Bool_t bEarlyBeak = kFALSE;//kTRUE;

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

  //Energy resolution plots
  Double_t EoverPElec_low_limit = 0;//0. for electron shower, -0.1 for pre shower//-2. for pions
  Double_t EoverPElec_up_limit = 0.25;//0.5 for electronshower, 0.1 for pre shower//2. for pions
  EoverPElec_low_limit = 1.2;//0.90; defalut from remoll
  EoverPElec_up_limit = 1.5;//1.05; defalut from remoll
  //for Pre-Shower+Shower Cluster
  TH2F * EoverPElec_total_ecal_fullsum = new TH2F("EoverPElec_total_ecal_fullsum","Total PS+Sh Edep over Pf Ratio;Momentum (GeV); Edep/Pf",mom_bins,2,7,400,EoverPElec_low_limit,EoverPElec_up_limit);
  //EoverPElec_low_limit = 0.98;//for sampling fraction related use  0.85 to 1.1 limit//for all simulation based estimation use 0.985 to 1.0
  //EoverPElec_up_limit = 0.995;  //with holes use
  //EoverPElec_low_limit = 0.85;

  TH2F * EoverPElec_total_ecal_6p1sum = new TH2F("EoverPElec_total_ecal_6p1sum","6+1 PS+Sh Edep over Pf Ratio;Momentum (GeV); Edep/Pf",mom_bins,2,7,400,EoverPElec_low_limit,EoverPElec_up_limit);

  //sampling frac for lead
  Double_t f_samp = 0.199776;
  Double_t f_samp_PS = 0.290808;


  //Generated input bank
  TChain * TGEMC_Gen =new TChain("generated");
  
  //TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  TGEMC_Gen->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1002.root");
  Int_t err = TGEMC_Gen->SetBranchAddress("pid",&fGen_pid);
  printf(" TGEMC_Gen branch status %i \n",err);
  TGEMC_Gen->SetBranchAddress("px",&fGen_Px);
  TGEMC_Gen->SetBranchAddress("py",&fGen_Py);
  TGEMC_Gen->SetBranchAddress("pz",&fGen_Pz);
  TGEMC_Gen->SetBranchAddress("vx",&fGen_vx);
  TGEMC_Gen->SetBranchAddress("vy",&fGen_vy);
  TGEMC_Gen->SetBranchAddress("vz",&fGen_vz);

  


  //Flux bank
  
  TFile *file=new TFile("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1002.root");
  TTree *TGEMC_Flux = (TTree*) file->Get("flux");
  //TGEMC_Flux =new TChain("flux");
  //TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  //TGEMC_Flux->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1002.root");

  //SetFluxBranchAddresses();

  TGEMC_Flux->SetBranchAddress("hitn",&fFluxHit_n);
  TGEMC_Flux->SetBranchAddress("id",&fFluxHit_id);
  TGEMC_Flux->SetBranchAddress("pid",&fFluxHit_pid);
  TGEMC_Flux->SetBranchAddress("tid",&fFluxHit_tid);
  TGEMC_Flux->SetBranchAddress("trackE",&fFluxHit_trackE);
  TGEMC_Flux->SetBranchAddress("avg_x",&fFluxHit_Avg_x);
  TGEMC_Flux->SetBranchAddress("avg_y",&fFluxHit_Avg_y);
  TGEMC_Flux->SetBranchAddress("avg_z",&fFluxHit_Avg_z);
  TGEMC_Flux->SetBranchAddress("px",&fFluxHit_Px);
  TGEMC_Flux->SetBranchAddress("py",&fFluxHit_Py);
  TGEMC_Flux->SetBranchAddress("pz",&fFluxHit_Pz);


  //EC bank
  TFile *file2=new TFile("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1002.root");
  TTree *TGEMC_EC = (TTree*) file2->Get("solid_ec");

  //TGEMC_EC =new TChain("solid_ec");
  //TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/GEMC_ECAL_e_5GeV_25deg_1k_output.root");
  //0-8GeV electron from target 
  //TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out*.root");
  //TGEMC_EC->Add("/home/rakithab/Simulation_Analysis/GEMC/rootfiles/farm_background_solid_PVDIS_ec_dirty_even_e/out.1002.root");

  //SetECBranchAddresses();

  TGEMC_EC->SetBranchAddress("id",&fECHit_id);
  TGEMC_EC->SetBranchAddress("totEdep",&fECHit_totEdep);


  Int_t nentries = (Int_t)TGEMC_Flux->GetEntries();
  printf("Entries = %i \n",nentries);
  Int_t treenumber=-1;
  Int_t ECtreenumber=-1;

  Bool_t Fillecal=kFALSE;  

  //flux hits
  Double_t pf;//for ECAL front det
  Double_t th;//for ECAL front det
  Double_t r;//for ECAL front det


  //2D hash map to store hits in time window interval and other ecal related parameters
  //TPoint2DMap ecalPSMap;//map for pre-shower
  //TPoint2DMap ecalShMap;//map for shower
  std::map<Int_t,Double_t> ecalPSMap;//map for pre-shower
  std::map<Int_t,Double_t> ecalShMap;//map for shower
  ecalPSMap.clear();
  ecalShMap.clear();

  //load EC map file
  LoadEC_map("../layout/map_FAEC_ANL_20130628.txt");

  //vector to store ecal hit coordinates
  TVector2 vec_ecalBlock;
  Double_t ecalBlock_x;
  Double_t ecalBlock_y;
  Int_t ecal_blockID;
  Double_t ecalBlock_x0;
  Double_t ecalBlock_y0;
  Int_t ecal_blockID0;
  Double_t ecalBlock_z0;
  Double_t ecalPos_x0;//store main(center) block location of the 6+1 cluster
  Double_t ecalPos_y0;
  Double_t ecalBlock_x0_2p1;//store main(center) block location of the 2+1 cluster
  Double_t ecalBlock_y0_2p1;
  Double_t ecal_offset=3.5;//global center of the ecal wrt remoll setup in m
  Double_t targ_offset=0.1;//in m

  Double_t ecalClustBlock_x;
  Double_t ecalClustBlock_y;
  Double_t cluster_edep[7]={0};
  Int_t cluster_edep_blockid[7]={0};
  Int_t block_count=0;

  Double_t edep_6p1_sum;  //sum of 6+1 blocks 
  Double_t edep_total_sum;  //sum ofall the ecal blocks 
  Double_t edep_1block_sum;//photon sum of the main ecal block
  Double_t edep_6p1_max=0;
  Double_t radius_6p1_max=0;

  Double_t edep_sum0;  //photon sum of the  ecalBlock_x0,ecalBlock_y0 ecal block
  //Double_t edep_2p1_sum1; //sum1 of 2+1 blocks in each 6+1 blocks
  //Double_t edep_2p1_sum2; //sum2 of 2+1 blocks in each 6+1 blocks
  //Double_t edep_2p1_sum3; //sum3 of 2+1 blocks in each 6+1 blocks
  //Double_t edep_2p1_sum0;  //photon sum of the  ecalBlock_x0,ecalBlock_y0 ecal block

  Double_t edep_6p1_PS_sum;  //sum of 6+1 blocks 
  Double_t edep_total_PS_sum;  //sum ofall the ecal blocks 
  //Double_t edep_2p1_PS_sum;  //sum of 6+1 blocks 


  for (Int_t i=0; i<nentries; i++) {
    Long64_t local;
    //Generated input bank
    
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
      //pf=p_gen;
    }
    
    //FLUX bank
    
    TGEMC_Flux->GetEntry(i);
    /*
    local = TGEMC_Flux->GetEntry(i);
    if (treenumber != TGEMC_Flux->GetTreeNumber()){
      SetFluxBranchAddresses();
      treenumber = TGEMC_Flux->GetTreeNumber();
    }
    GetFluxEntryByBranch(local);
    //printf("%i %i \n",fFluxHit_id->size(),fFluxHit_trackE->size());
    */
    for (int j = 0; j<fFluxHit_id->size(); j++){
      FluxHit_detector_ID=fFluxHit_id->at(j)/1000000;
      FluxHit_subdetector_ID=(fFluxHit_id->at(j)%1000000)/100000;
      FluxHit_subsubdetector_ID=((fFluxHit_id->at(j)%1000000)%100000)/10000;
      FluxHit_component_ID=fFluxHit_id->at(j)%10000; 
      if (FluxHit_detector_ID==3 && FluxHit_subdetector_ID == 1 && FluxHit_subsubdetector_ID == 1 && fFluxHit_pid->at(j)==11 && fFluxHit_tid->at(j)==1){
      //if (fFluxHit_tid->at(j)==1){
	//cout << "particle mom entering EC " << fFluxHit_trackE->at(j) << endl;         
	
	pf=TMath::Sqrt(TMath::Power(fFluxHit_Px->at(j),2)+TMath::Power(fFluxHit_Py->at(j),2)+TMath::Power(fFluxHit_Pz->at(j),2));
	r = TMath::Sqrt(TMath::Power(fFluxHit_Avg_x->at(j),2)+TMath::Power(fFluxHit_Avg_y->at(j),2));
	th=TMath::ATan(r/(fFluxHit_Avg_z->at(j) - targ_offset))*DEG;
	//ECALDet_mom_distr->Fill(fFluxHit_trackE->at(j));
	ECALDet_mom_distr->Fill(pf);
	Fillecal=kTRUE;
	break;
      } else
	Fillecal=kFALSE;  
    }
    
    
    //EC bank
    if (Fillecal){
      TGEMC_EC->GetEntry(i);
      /*
      local = TGEMC_EC->GetEntry(i);
      if (ECtreenumber != TGEMC_EC->GetTreeNumber()){
	SetECBranchAddresses();
	ECtreenumber = TGEMC_EC->GetTreeNumber();
      }
      GetECEntryByBranch(local);
      */
      Double_t totEdep_shower=0;
      Double_t totEdep_preshower=0;
      for (int j = 0; j<fECHit_id->size(); j++){
	ECHit_detector_ID=fECHit_id->at(j)/1000000;
	ECHit_subdetector_ID=(fECHit_id->at(j)%1000000)/100000;
	ECHit_subsubdetector_ID=((fECHit_id->at(j)%1000000)%100000)/10000;
	ECHit_component_ID=fECHit_id->at(j)%10000;
	//save rounded ecal hit coordinates
	//printf("DEBUG : ecal id %i \n",ECHit_component_ID);
	//vec_ecalBlock = GetECALBlock_coord(ECHit_component_ID);
	
	
	if (ECHit_detector_ID==3 && ECHit_subdetector_ID == 1 && ECHit_subsubdetector_ID == 0){//shower 
	  totEdep_shower+=fECHit_totEdep->at(j);
	  if (ecalShMap.count(ECHit_component_ID)){
	    ecalShMap[ECHit_component_ID]+=fECHit_totEdep->at(j);// MeV
	  } else {
	    ecalShMap[ECHit_component_ID]=fECHit_totEdep->at(j);// MeV
	  }
	}
	if (ECHit_detector_ID==3 && ECHit_subdetector_ID == 1 && ECHit_subsubdetector_ID == 1){//pershower
	  totEdep_preshower+=fECHit_totEdep->at(j);
	  if (ecalPSMap.count(ECHit_component_ID)){
	    ecalPSMap[ECHit_component_ID]+=fECHit_totEdep->at(j);// MeV
	  } else {
	    ecalPSMap[ECHit_component_ID]=fECHit_totEdep->at(j);// MeV
	  }
	}
	
      }
      
      //fill the histogram
      htotEdep_ec_shower->Fill(totEdep_shower);
      htotEdep_ec_preshower->Fill(totEdep_preshower);
      //process the ECAL preshower hits : max cluster find 
      
      edep_6p1_sum = 0;
      //start dissecting this ecal with a primary track
      edep_6p1_max = 0;
      edep_1block_sum = 0;
      edep_sum0 = 0;
      edep_total_sum = 0;
      
      //PS ecal cluster information
      edep_6p1_PS_sum=0;
      edep_total_PS_sum=0;
      
      for (std::map<Int_t,Double_t>::iterator it = ecalPSMap.begin(); it != ecalPSMap.end(); ++it ){
	edep_1block_sum = it->second;
	edep_total_sum+=edep_1block_sum;
      }
      edep_total_PS_sum = edep_total_sum;
      
      //Start processing the ecal shower maps
      edep_6p1_sum = 0.;
      //start dissecting this ecal with a primary track
      edep_6p1_max = 0.;
      edep_1block_sum = 0.;
      edep_sum0 = 0.;
      edep_total_sum = 0.;
      ecal_blockID0 = 0;
      
      //process the ECAL shower hits : max cluster find 
      for (std::map<Int_t,Double_t>::iterator it = ecalShMap.begin(); it != ecalShMap.end(); ++it ){
	edep_1block_sum = it->second;
	edep_total_sum+=edep_1block_sum;
	ecal_blockID = it->first;
	//get ecal x,y vector
	vec_ecalBlock = GetECALBlock_coord(ecal_blockID);
	ecalBlock_x = vec_ecalBlock.Px();
	ecalBlock_y = vec_ecalBlock.Py();
	TVector2 vec_neighbor;	
	//for 3 block sum use, add to current block; 1+3, 4+2, and 5+6		
	edep_6p1_sum=0;
	for (Int_t c=0;c<7;c++){//init cluster array
	  cluster_edep[c]=0;
	  cluster_edep_blockid[c]=0;
	}
	block_count = GetECALCluser(ecal_blockID,cluster_edep_blockid);
	//compare main block id from GetECALCluser routine before and after
	//printf("DEBUG : %d %d %d \n",ecal_blockID,block_count,cluster_edep_blockid[0]);
	cluster_edep[0]=ecalShMap[cluster_edep_blockid[0]];
	//compare edep of the main block before and after
	//printf("DEBUG : %f %f \n",cluster_edep[0],edep_1block_sum);
	//get edep for all the neighbor blocks 
	edep_6p1_sum = cluster_edep[0];
	for(Int_t j=0;j<block_count;j++){
	  cluster_edep[j+1]=ecalShMap[cluster_edep_blockid[j+1]];
	  edep_6p1_sum +=cluster_edep[j+1];
	}
	//done summing all the 6+1 ecal block. Now see if this cluster is the maximum
	if (edep_6p1_sum >= edep_6p1_max){
	  ecalBlock_x0=ecalBlock_x;
	  ecalBlock_y0=ecalBlock_y;
	  ecal_blockID0 = ecal_blockID;
	  radius_6p1_max=TMath::Sqrt(TMath::Power(ecalBlock_x,2)+TMath::Power(ecalBlock_y,2));
	  edep_sum0 = edep_1block_sum;//this is the photon sum for the main block in the max cluster
	  edep_6p1_max=edep_6p1_sum;
	}
      }
      //printf("DEBUG : Entry : %i, Total edep %f, max 6+1 cluser edep %f, block id %d \n",i,edep_total_sum,edep_6p1_max,ecal_blockID0);
      
      if ( (pf>=2000 && pf<=14000)  ){//&& r>= 1.2 && r<=2 // && th<25 && (th>=24 && th<30) && r>= 1.4 && r<=2.2 // (th>=22 && th<=35) preffered angle range
	//using sampling fraction to compute the calibrated energy for shower and PS sampling fraction for pre shower as well
	EoverPElec_total_ecal_fullsum->Fill(pf/1000,(edep_total_PS_sum/f_samp_PS + edep_total_sum/f_samp)/(pf),1);
	EoverPElec_total_ecal_6p1sum->Fill(pf/1000,(edep_total_PS_sum/f_samp_PS + edep_6p1_max/f_samp)/(pf),1);
      }
    }
      //clear memory for this event
    ecalPSMap.clear();
    ecalShMap.clear();
    
    Fillecal=kFALSE;

    if (i>10000 && bEarlyBeak)
      break;
    if (i%200000==0)
      printf("Event %d \n",i);
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

  //For PS+Sh 
  TCanvas * canvas_run_level_e_res_PS_shower = new TCanvas("canvas_run_level_e_res_PS_shower","canvas_run_level_e_res_PS_shower",1000,1400);
  canvas_run_level_e_res_PS_shower->Divide(2,2);
  //canvas_run_level_e_res_PS_shower->Divide(2,2);
  canvas_run_level_e_res_PS_shower->cd(1);
  EoverPElec_total_ecal_fullsum->Draw("colz");
  canvas_run_level_e_res_PS_shower->cd(2);
  EoverPElec_total_ecal_6p1sum->Draw("colz");
  canvas_run_level_e_res_PS_shower->cd(3);
  TProfile * EoverPElec_total_ecal_fullsum_x = EoverPElec_total_ecal_fullsum->ProfileX();
  EoverPElec_total_ecal_fullsum_x->Draw();
  EoverPElec_total_ecal_fullsum_x->Fit("pol0");
  canvas_run_level_e_res_PS_shower->cd(4);
  TProfile * EoverPElec_total_ecal_6p1sum_x = EoverPElec_total_ecal_6p1sum->ProfileX();
  EoverPElec_total_ecal_6p1sum_x->Draw();
  EoverPElec_total_ecal_6p1sum_x->Fit("pol0");

  TCanvas * canvas_run_level_e_res_PS_shower_final = new TCanvas("canvas_run_level_e_res_PS_shower_final","canvas_run_level_e_res_PS_shower_final",1000,700);
  canvas_run_level_e_res_PS_shower_final->Divide(2,1);
  
  canvas_run_level_e_res_PS_shower_final->cd(1);
  TGraph * EoverpRMS_total_fullsum = GetRMSReolution(EoverPElec_total_ecal_fullsum,0.92,1.04);//0.94,1.02 for limited angle simulation //0.96,1.02 for all angle range
  EoverpRMS_total_fullsum->SetTitle("ECAL PS+Sh Total Energy Resolution VS p; Momentum (GeV/c); #DeltaE/E");
  TF1 * total_f1 = new TF1("total_Eres1", "sqrt([0]*[0]+[1]*[1]/x)", 2, 7);//1,10 is this in GeV?
  total_f1->SetLineColor(kRed);
  EoverpRMS_total_fullsum->Fit(total_f1, "M");
  canvas_run_level_e_res_PS_shower_final->cd(2);
  TGraph * EoverpRMS_total_6p1sum = GetRMSReolution(EoverPElec_total_ecal_6p1sum,0.88,1.04);//combined PS+sh 0.84,0.98//if actual edep on material used 0.93,0.995
  EoverpRMS_total_6p1sum->SetTitle("ECAL PS+Sh 6+1 Energy Resolution VS p; Momentum (GeV/c); #DeltaE/E");
  TF1 * total_f2 = new TF1("total_Eres2", "sqrt([0]*[0]+[1]*[1]/x)", 2, 7);
  total_f2->SetLineColor(kRed);
  EoverpRMS_total_6p1sum->Fit(total_f2, "M");


  watch.Stop();
  printf("Total Time %3.4f min \n Completed, Exit now :) \n",watch.RealTime()/60);
  theApp.Run();
  return(1);
}

void SetFluxBranchAddresses(){
  TGEMC_Flux->SetBranchAddress("hitn",&fFluxHit_n,&bFluxHit_n);
  TGEMC_Flux->SetBranchAddress("id",&fFluxHit_id,&bFluxHit_id);
  TGEMC_Flux->SetBranchAddress("pid",&fFluxHit_pid,&bFluxHit_pid);
  //TGEMC_Flux->SetBranchAddress("mpid",&fFluxHit_mpid,&bFluxHit_mpid);
  TGEMC_Flux->SetBranchAddress("tid",&fFluxHit_tid,&bFluxHit_tid);
  /*
  TGEMC_Flux->SetBranchAddress("mtid",&fFluxHit_mtid,&bFluxHit_mtid);
  TGEMC_Flux->SetBranchAddress("otid",&fFluxHit_otid,&bFluxHit_otid);
  */
  TGEMC_Flux->SetBranchAddress("trackE",&fFluxHit_trackE,&bFluxHit_trackE);
  //TGEMC_Flux->SetBranchAddress("totEdep",&fFluxHit_totEdep,&bFluxHit_totEdep);
  TGEMC_Flux->SetBranchAddress("avg_x",&fFluxHit_Avg_x,&bFluxHit_Avg_x);
  TGEMC_Flux->SetBranchAddress("avg_y",&fFluxHit_Avg_y,&bFluxHit_Avg_y);
  TGEMC_Flux->SetBranchAddress("avg_z",&fFluxHit_Avg_z,&bFluxHit_Avg_z);
  /*
  TGEMC_Flux->SetBranchAddress("avg_lx",&fFluxHit_Avg_lx,&bFluxHit_Avg_lx);
  TGEMC_Flux->SetBranchAddress("avg_ly",&fFluxHit_Avg_ly,&bFluxHit_Avg_ly);
  TGEMC_Flux->SetBranchAddress("avg_lz",&fFluxHit_Avg_lz,&bFluxHit_Avg_lz);
  */
  TGEMC_Flux->SetBranchAddress("px",&fFluxHit_Px,&bFluxHit_Px);
  TGEMC_Flux->SetBranchAddress("py",&fFluxHit_Py,&bFluxHit_Py);
  TGEMC_Flux->SetBranchAddress("pz",&fFluxHit_Pz,&bFluxHit_Pz);
  /*
  TGEMC_Flux->SetBranchAddress("vx",&fFluxHit_vx,&bFluxHit_vx);
  TGEMC_Flux->SetBranchAddress("vy",&fFluxHit_vy,&bFluxHit_vy);
  TGEMC_Flux->SetBranchAddress("vz",&fFluxHit_vz,&bFluxHit_vz);
  TGEMC_Flux->SetBranchAddress("mvx",&fFluxHit_mvx,&bFluxHit_mvx);
  TGEMC_Flux->SetBranchAddress("mvy",&fFluxHit_mvy,&bFluxHit_mvy);
  TGEMC_Flux->SetBranchAddress("mvz",&fFluxHit_mvz,&bFluxHit_mvz);
  TGEMC_Flux->SetBranchAddress("avg_t",&fFluxHit_Avg_t,&bFluxHit_t);  
  */
};

void GetFluxEntryByBranch(Long64_t local){
  bFluxHit_id->GetEntry(local);  
  bFluxHit_n->GetEntry(local);
  bFluxHit_pid->GetEntry(local);
  //bFluxHit_mpid->GetEntry(local);  
  bFluxHit_tid->GetEntry(local);  
  /*
  bFluxHit_mtid->GetEntry(local);  
  bFluxHit_otid->GetEntry(local);  
  */
  bFluxHit_trackE->GetEntry(local); 
  
  //bFluxHit_totEdep->GetEntry(local);  

  bFluxHit_Avg_x->GetEntry(local);  
  bFluxHit_Avg_y->GetEntry(local);  
  bFluxHit_Avg_z->GetEntry(local);
  /*  
  bFluxHit_Avg_lx->GetEntry(local);  
  bFluxHit_Avg_ly->GetEntry(local);  
  bFluxHit_Avg_lz->GetEntry(local);  
  */
  bFluxHit_Px->GetEntry(local);  
  bFluxHit_Py->GetEntry(local);  
  bFluxHit_Pz->GetEntry(local);  
  /*
  bFluxHit_vx->GetEntry(local);  
  bFluxHit_vy->GetEntry(local);  
  bFluxHit_vz->GetEntry(local);  
  bFluxHit_mvx->GetEntry(local);  
  bFluxHit_mvy->GetEntry(local);  
  bFluxHit_mvz->GetEntry(local);  
  bFluxHit_t->GetEntry(local);
  */
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
  TGEMC_EC->SetBranchAddress("avg_x",&fECHit_Avg_x,&bECHit_Avg_x);
  TGEMC_EC->SetBranchAddress("avg_y",&fECHit_Avg_y,&bECHit_Avg_y);
  TGEMC_EC->SetBranchAddress("avg_z",&fECHit_Avg_z,&bECHit_Avg_z);
  /*
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
  bECHit_Avg_x->GetEntry(local);  
  bECHit_Avg_y->GetEntry(local);  
  bECHit_Avg_z->GetEntry(local);  
  /*
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

void LoadEC_map(TString map_file){
  //std. map file in the svn repo  ../layout/map_FAEC_ANL_20130628.txt
  ifstream INPUT_file;
  INPUT_file.open(map_file.Data());
  if(!INPUT_file){ 
    printf("ERROR!!! Can't open %s \n",map_file.Data());	
    exit(1);
  }

  Double_t y_bak[54]={100000};
  
  //load x,y locations and block id
  Double_t total_module=0;
  Int_t counter_id=0;
  for(int i=0;i<54;i++){ //54 rows
    INPUT_file>>num_module_in_row[i];
    //std::cout<<num_module_in_row[i]<<" ";
    num_module_in_row[i]=num_module_in_row[i]-1;  //first one is y coordinate
    total_module+=num_module_in_row[i];
    Double_t tmp_y;
    INPUT_file>>tmp_y;
    y_bak[i]=tmp_y;       //make a backup in order to judge which row a certain particle hits the EC
    for(Int_t j=0;j<num_module_in_row[i];j++){
      INPUT_file>>x[i][j];
       y[i][j]=tmp_y;     // in each row , y coordinate is the same
      counter_id++;
      id[i][j]=counter_id;
      //update the pair array
      block_map[counter_id].first = i;
      block_map[counter_id].second = j;
      //printf("DEBUG EC map update : ecal id %i [%i,%i],[%f,%f] \n",counter_id,j,i,x[i][j],y[i][j]);//vec_ecalBlock.Px(),vec_ecalBlock.Py()
      //sector
      TVector2 vec(x[i][j],y[i][j]);
      Double_t phi_module=vec.Phi();
      for(int k=0;k<30;k++){   //30 sectors
	if(phi_module>=k*12.0/180.0*3.141592 && phi_module<(k+1.0)*12.0/180.0*3.141592){  //sector k
	  sector[i][j]=k+1;
	  // 				    cout << sector[i][j] << endl;				
	}
      }
      
    }
    //cout<<num_module_in_row[i]<<"	"<<y[i][0]<<endl;
    //std::cout<<" "<<std::endl;
  }
    printf("Total ECAL Modules loaded %i \n",counter_id);

  /* //moved to single loops above
  //generate block id
  for(Int_t i=0;i<54;i++){
    for(Int_t j=0;j<num_module_in_row[i];j++){
      counter_id++;
      id[i][j]=counter_id;			
      // 			cout << id[i][j] << endl;
    }
  }
  */	
  /* //moved to single loops above
  //generate sector id
  for(Int_t i=0;i<54;i++){
    for(Int_t j=0;j<num_module_in_row[i];j++){
      TVector2 vec(x[i][j],y[i][j]);
      Double_t phi_module=vec.Phi();
      for(int k=0;k<30;k++){   //30 sectors
	if(phi_module>=k*12.0/180.0*3.141592 && phi_module<(k+1.0)*12.0/180.0*3.141592){  //sector k
	  sector[i][j]=k+1;
	  // 				    cout << sector[i][j] << endl;				
	}
      }
    }
  }
  */
  
  Int_t total_module_active=0;
  for(Int_t i=0;i<54;i++){
    for(Int_t j=0;j<num_module_in_row[i];j++){
      status[i][j]=1; //all active for PVDIS FAEC
      if (status[i][j]==1) total_module_active++;
    }
  }
  
  
  
  
};

TVector2 GetECALBlock_coord(Int_t block_id){
  Int_t idx=-1,idy=-1;
  TVector2 vec_ecalBlock;
  idx = block_map[block_id].second;
  idy = block_map[block_id].first;
  vec_ecalBlock.Set(floor(x[idy][idx]*100+0.5)/100,floor(y[idy][idx]*100+0.5)/100); 
  //printf("DEBUG : ecal id %i [%i,%i],[%f,%f] \n",block_id,idx,idy,x[idy][idx],y[idy][idx]);//vec_ecalBlock.Px(),vec_ecalBlock.Py()
  return vec_ecalBlock;
};

Int_t GetECALBlock_sector(Int_t block_id){
  Int_t idx = block_map[block_id].second;
  Int_t idy = block_map[block_id].first;

  return sector[idy][idx];
};

Int_t GetECALCluser(Int_t block_id,Int_t *cluster_edep_blockid){
  Int_t hit_idx = block_map[block_id].second;
  Int_t hit_idy = block_map[block_id].first;
  Int_t hit_around_idx[6]={100000};      //around 6 modules, a variable label indicates how many surrounded modules are around the hitted module
  Int_t hit_around_idy[6]={100000};
  //__________________________________find the surrounded other 6 modules________________________
  Int_t tmp_idx[15]={hit_idx-7, hit_idx-6, hit_idx-5, hit_idx-4, hit_idx-3, hit_idx-2, hit_idx-1, hit_idx, hit_idx+1, hit_idx+2, hit_idx+3, hit_idx+4, hit_idx+5, hit_idx+6, hit_idx+7};
  Int_t tmp_idy[3]={hit_idy-1, hit_idy, hit_idy+1};
  Int_t label=0;
  for(Int_t i=0;i<15;i++){// x scan
    for(Int_t j=0;j<3;j++){  //y scan
      if(tmp_idy[j]>=0 && tmp_idy[j]<54 && tmp_idx[i]>=0 && tmp_idx[i]<num_module_in_row[tmp_idy[j]] && (tmp_idx[i]!=hit_idx || tmp_idy[j]!=hit_idy) ){ // in range
	if(sqrt( pow( (x[tmp_idy[j]][tmp_idx[i]]-x[hit_idy][hit_idx]),2 )+ pow((y[tmp_idy[j]][tmp_idx[i]]-y[hit_idy][hit_idx]),2 ))<15.0){
	  hit_around_idx[label]=tmp_idx[i];
	  hit_around_idy[label]=tmp_idy[j];
	  label++;
	}
      }
    }
  }
  Bool_t bDEBUG = kFALSE;//kTRUE;
  if (bDEBUG){
    cout<<"find  "<<label<<" around the ecal module"<<endl;
    cout<<"idy | idx | block_id | sector_id"<<endl;
    cout<<hit_idy+1<<"\t"<<hit_idx+1<<"\t"<<id[hit_idy][hit_idx]<<"\t"<<sector[hit_idy][hit_idx]<<" ----> main block!"<<endl;
  }
  cluster_edep_blockid[0] = id[hit_idy][hit_idx];
  for(int l=0;l<label;l++){
    if (bDEBUG)
      cout<<hit_around_idy[l]+1<<"\t"<<hit_around_idx[l]+1<<"\t"<<id[hit_around_idy[l]][hit_around_idx[l]]<< "\t"<<sector[hit_around_idy[l]][hit_around_idx[l]]<<endl;
    cluster_edep_blockid[l+1]=id[hit_around_idy[l]][hit_around_idx[l]];
  }
  
  

  return label;
};

TGraphErrors * GetRMSReolution(TH2F * Difference, Double_t fit_range_up, Double_t fit_range_low){
	assert(Difference);

	TH1D * hpt = Difference->ProjectionX();

	int cnt = 0;
	Double_t pt[1000] = { 0 };
	Double_t resolution[2][1000]={0};
	Double_t resolution_error[2][1000]={0};

	//TCanvas *c2 = new TCanvas("GetEnergyRes2", "GetEnergyRes2", 800 * 1.5, 600 * 1);//DEBUG
	for ( int i = 0; i < Difference->GetNbinsX() / 8; i++ )
	{
	  //pt[cnt] = Difference->GetXaxis()->GetBinCenter(i * 10 + 10 / 2);//in GeV
		
		TH1D * proj = Difference->ProjectionY("_py", i * 10 + 1, (i + 1) * 10);
		
		if ( proj->GetSum() > 100 )//check for entries
		{
		  pt[cnt] = Difference->GetXaxis()->GetBinCenter(i * 10 + 10 / 2);//in GeV
		  //with no fits
		  /*
		  RMS[cnt] = proj->GetRMS();
		  RMSErr[cnt] = proj->GetRMSError();
		  printf("cnt=%d i=%d bin cen %d pf %4.2f GeV  [%d to %d] bins mean %2.4f rms %2.4f entries = %d \n",cnt,i,i * 10 + 10 / 2,pt[cnt],i * 10 + 1,(i + 1) * 10,proj->GetMean(),proj->GetRMS(),proj->GetEntries());
		  cnt++;
		  */
		  //printf("%i Mean %f RMS %f entries %4.0f %4.0f \n",cnt,proj->GetMean(),proj->GetRMS(),proj->GetSum(),proj->GetEntries());
		  //using a gaussian fit
		  	  
		  //TF1 * gaus = new TF1("gausEoverP", "gaus", 0.9, 1.2);//a gausian fit in the range 0.9 to 1.2 for 6+1 cluster
		  TF1 * gaus = new TF1("gausEoverP", "gaus", fit_range_low, fit_range_up);
		  //gaus->SetParameters(1, 1, .10);//f(x) = p0*exp(-0.5*((x-p1)/p2)^2)) where p0,p1, and p2 are parameters
		  proj -> Fit(gaus, "R0");
		  //proj->Fit("gaus");
		  //printf("\n %i  M=%2.4f Sig=%2.4f +/- %2.4f Eff. = %2.4f +/- %2.4f \n",cnt,gaus->GetParameter(1),gaus->GetParameter(2),gaus->GetParError(2),gaus->GetParameter(2)/gaus->GetParameter(1),gaus->GetParError(2)/gaus->GetParameter(1));
		  //proj -> Draw();//DEBUG
		  //c2 -> SaveAs(Form("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Plots/ECAL/energy_res/calibratedEnergy/EBins/histo_6p1_SH_%i_wthcuts.png",cnt));//DEBUG

		  //if ( abs(gaus->GetParameter(1) - 1) < .1 )
		  //{
		  //RMS[cnt] = gaus->GetParameter(2)/gaus->GetParameter(1);
		  resolution[0][cnt] = gaus->GetParameter(2)/gaus->GetParameter(1);//RMS[cnt];
		  resolution[1][cnt] = proj->GetRMS()/proj->GetMean();
		  //RMS[cnt] = proj->GetRMS()/proj->GetMean();
		  //RMSErr[cnt] = gaus->GetParError(2)/gaus->GetParameter(1);
		  resolution_error[0][cnt] = TMath::Sqrt(TMath::Power(gaus->GetParError(1),2)+TMath::Power(gaus->GetParError(2),2));//RMSErr[cnt];
		  resolution_error[1][cnt] = TMath::Sqrt(TMath::Power(proj->GetRMSError(),2)+TMath::Power(proj->GetMeanError(),2));//proj->GetRMSError()/proj->GetMean();
		  //RMSErr[cnt] = proj->GetRMSError()/proj->GetMean();
		  cnt++;
		  //}

		  
		}

		delete proj;
	}

	//    delete Difference;
	TGraphErrors * gptRMS = new TGraphErrors(cnt, pt, resolution[1], 0, resolution_error[1]);
	gptRMS -> SetLineWidth(3);
	gptRMS -> Draw("*A");
	gptRMS -> GetYaxis()->CenterTitle();

	// degub print
	for(Int_t i=0;i<cnt;i++){
	  printf(" %13.2f  %13.3f %13.3f %13.3f %13.5f \n",pt[i],resolution[0][i],resolution_error[0][i],resolution[1][i],resolution_error[1][i]);
	}

	return gptRMS;  
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
