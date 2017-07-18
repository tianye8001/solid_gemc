/*
Rakitha Fri Feb  6 11:30:33 EST 2015
to merge Pion background rootfiles and generate single root file with all the tracks and their timestamps

./mergeBkgTrees
 */


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <new>
#include <cstdlib>
#include <math.h>

#include "TRandom.h"
#include "TRandom3.h"
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
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFrame.h>
#include <TObjArray.h>
#include <TVector2.h>

#include "ecal.h"


using namespace std;
using namespace std::tr1;

#define __IO_MAXHIT 10000
#define __FILENAMELEN 255
//3rd one for the new TTRee 0,1, and 2 are for merging trees
#define __TREE_COUNT 5 

Int_t fEv_num[__TREE_COUNT];
Int_t fEv_simpid[__TREE_COUNT];//save the main pid of the simulation
Double_t fEv_ratefactor[__TREE_COUNT];
Double_t fEvTimeStamp[__TREE_COUNT];
Int_t fEvTimeWindow[__TREE_COUNT];
Double_t fEvRate[__TREE_COUNT];
Double_t fEvPf[__TREE_COUNT];
Double_t fEvTh[__TREE_COUNT];
Double_t fEvW2[__TREE_COUNT];
Double_t fEvXbj[__TREE_COUNT];


//for generic hits
Int_t fNGenDetHit[__TREE_COUNT];
Int_t fGenDetHit_det[__TREE_COUNT][__IO_MAXHIT];
Int_t fGenDetHit_trid[__TREE_COUNT][__IO_MAXHIT];
Int_t fGenDetHit_mtrid[__TREE_COUNT][__IO_MAXHIT];
Int_t fGenDetHit_pid[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_P[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_PZ[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_X[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_Y[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_Z[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_VZ[__TREE_COUNT][__IO_MAXHIT];
Double_t fGenDetHit_T[__TREE_COUNT][__IO_MAXHIT];


//for ecal sum hits
Int_t fNCalDetSum[__TREE_COUNT];
Int_t fCalDetSum_det[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetSum_edep[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetSum_photon[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetSum_x[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetSum_y[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetPos_X[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetPos_Y[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDetPos_Z[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDet_ST[__TREE_COUNT][__IO_MAXHIT];
Double_t fCalDet_ET[__TREE_COUNT][__IO_MAXHIT];

TFile *fFile;
TTree *fTree;
char fFilename[__FILENAMELEN];

Bool_t earlybreak=kFALSE;//kFALSE;//kTRUE;//kFALSE;//exit early from the main tree entries loop
Bool_t earlyMergebreak= kFALSE;//kTRUE;//kFALSE;//exit early from the main tree entries loop

void InitializeTree();
void FillTree();
void Flush();
void WriteTree();

struct event {
  Int_t ev_num;
  Int_t input;
  Double_t timestamp;

  bool operator < (const event& str) const {
    return (timestamp < str.timestamp);
  }
};

vector<event> event_list;

singledethit dethit;
singledetsum detsum;
singleevent ebeam_event;
vector<singleevent> ebeam_event_list;

const Int_t Sim_Count = 4;//3 bkg Pi+-0
Int_t simpid[Sim_Count]={-211,111,211,1};//simpid=1 is the ebeam events

Bool_t BKG1_ON = kTRUE;
Bool_t BKG2_ON = kTRUE;
Bool_t BKG3_ON = kTRUE;//kFALSE
Bool_t BKG4_ON = kTRUE;//e-beam



int main(Int_t argc,Char_t* argv[]) { 

  //set the timer
  TStopwatch watch;
  watch.Start();
  TApplication theApp("App",&argc,argv);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("eMr");

  //load the remoll lib if statement checks su-work or my laptop directory
  gSystem->Load("libremollroot.so");

  TH1F *LastGEM_mom_distr_bkg1 = new TH1F("LastGEM_mom_distr_bkg1","#pi^{-}: Det. DS of Target;Momentum (MeV);Rate (KHz)",100 ,0,8000);
  TH1F *LastGEM_mom_distr_bkg2 = new TH1F("LastGEM_mom_distr_bkg2","#pi^{0}: Det. DS of Target;Momentum (MeV);Rate (KHz)",100 ,0,8000);
  TH1F *LastGEM_mom_distr_bkg3 = new TH1F("LastGEM_mom_distr_bkg3","#pi^{+}: Det. DS of Target;Momentum (MeV);Rate (KHz)",100 ,0,8000);

  fTree = NULL;
  // Default filename
  strcpy(fFilename, "remoll_merged_HallDpions_EMbkg_LD_test_1.root");
 
  InitializeTree();

  //load trees
  TChain * Tremoll_bkg1 =new TChain("T");
  //Tremoll_bkg1->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_krypto_pi_m_LD_krypto_10k_1.root"); 
  //simulation with krypto baffles  
  //Tremoll_bkg1->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_m_D_1M_krypto_1.root"); 
  //simulation with lead baffles using hall d generator
  Tremoll_bkg1->Add("/work/halla/solid/tianye/mergBKG_output/remoll_LD_HallD_pim_1M.root");
  //simulation with lead baffles + lead photon blocker  
  //Tremoll_bkg1->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1Blocked_uniformpi_m_D_1M_1.root"); 
  Tremoll_bkg1->SetBranchAddress("ev.evnum",&fEv_num[0]);
  Tremoll_bkg1->SetBranchAddress("rate",&fEvRate[0]);   
  Tremoll_bkg1->SetBranchAddress("ev.W2",&fEvW2[0]); 
  Tremoll_bkg1->SetBranchAddress("ev.xbj",&fEvXbj[0]); 
  //generic hit (for GEMs)
  Tremoll_bkg1->SetBranchAddress("hit.n",&fNGenDetHit[0]);
  Tremoll_bkg1->SetBranchAddress("hit.det",&fGenDetHit_det[0]);
  Tremoll_bkg1->SetBranchAddress("hit.pid",&fGenDetHit_pid[0]);
  Tremoll_bkg1->SetBranchAddress("hit.trid",&fGenDetHit_trid[0]);
  Tremoll_bkg1->SetBranchAddress("hit.mtrid",&fGenDetHit_mtrid[0]);
  Tremoll_bkg1->SetBranchAddress("hit.p",&fGenDetHit_P[0]);
  Tremoll_bkg1->SetBranchAddress("hit.pz",&fGenDetHit_PZ[0]);
  Tremoll_bkg1->SetBranchAddress("hit.x",&fGenDetHit_X[0]);
  Tremoll_bkg1->SetBranchAddress("hit.y",&fGenDetHit_Y[0]);
  Tremoll_bkg1->SetBranchAddress("hit.z",&fGenDetHit_Z[0]);
  Tremoll_bkg1->SetBranchAddress("hit.vz",&fGenDetHit_VZ[0]);
  Tremoll_bkg1->SetBranchAddress("hit.t",&fGenDetHit_T[0]);

  //ecal sum hits
  Tremoll_bkg1->SetBranchAddress("cal.n",&fNCalDetSum[0]);
  Tremoll_bkg1->SetBranchAddress("cal.det",&fCalDetSum_det[0]);
  Tremoll_bkg1->SetBranchAddress("cal.edep",&fCalDetSum_edep[0]);
  Tremoll_bkg1->SetBranchAddress("cal.det_x",&fCalDetPos_X[0]);
  Tremoll_bkg1->SetBranchAddress("cal.det_y",&fCalDetPos_Y[0]);
  Tremoll_bkg1->SetBranchAddress("cal.x",&fCalDetSum_x[0]);
  Tremoll_bkg1->SetBranchAddress("cal.y",&fCalDetSum_y[0]);
  Tremoll_bkg1->SetBranchAddress("cal.st",&fCalDet_ST[0]);
  Tremoll_bkg1->SetBranchAddress("cal.et",&fCalDet_ST[0]);

  TChain * Tremoll_bkg2 =new TChain("T");
  //Tremoll_bkg2->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_0_D_1M.root");
  //Tremoll_bkg2->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_krypto_pi_0_LD_krypto_10k_1.root");
  //simulation with krypto baffles
  //Tremoll_bkg2->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_0_D_1M_krypto_1.root");  
  //simulation with lead baffles  
  //Tremoll_bkg2->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_0_D_1M_1.root"); 
  //simulation with lead baffles using hall d generator
  Tremoll_bkg2->Add("/work/halla/solid/tianye/mergBKG_output/remoll_LD_HallD_pi0_1M.root");
  //simulation with lead baffles + lead photon blocker  
  //Tremoll_bkg2->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1Blocked_uniformpi_0_D_1M_1.root");  
  Tremoll_bkg2->SetBranchAddress("ev.evnum",&fEv_num[1]);
  Tremoll_bkg2->SetBranchAddress("rate",&fEvRate[1]);   
  Tremoll_bkg2->SetBranchAddress("ev.W2",&fEvW2[1]); 
  Tremoll_bkg2->SetBranchAddress("ev.xbj",&fEvXbj[1]); 
  //generic hit (for GEMs)
  Tremoll_bkg2->SetBranchAddress("hit.n",&fNGenDetHit[1]);
  Tremoll_bkg2->SetBranchAddress("hit.det",&fGenDetHit_det[1]);
  Tremoll_bkg2->SetBranchAddress("hit.pid",&fGenDetHit_pid[1]);
  Tremoll_bkg2->SetBranchAddress("hit.trid",&fGenDetHit_trid[1]);
  Tremoll_bkg2->SetBranchAddress("hit.mtrid",&fGenDetHit_mtrid[1]);
  Tremoll_bkg2->SetBranchAddress("hit.p",&fGenDetHit_P[1]);
  Tremoll_bkg2->SetBranchAddress("hit.pz",&fGenDetHit_PZ[1]);
  Tremoll_bkg2->SetBranchAddress("hit.x",&fGenDetHit_X[1]);
  Tremoll_bkg2->SetBranchAddress("hit.y",&fGenDetHit_Y[1]);
  Tremoll_bkg2->SetBranchAddress("hit.z",&fGenDetHit_Z[1]);
  Tremoll_bkg2->SetBranchAddress("hit.vz",&fGenDetHit_VZ[1]);
  Tremoll_bkg2->SetBranchAddress("hit.t",&fGenDetHit_T[1]);

  //ecal sum hits
  Tremoll_bkg2->SetBranchAddress("cal.n",&fNCalDetSum[1]);
  Tremoll_bkg2->SetBranchAddress("cal.det",&fCalDetSum_det[1]);
  Tremoll_bkg2->SetBranchAddress("cal.edep",&fCalDetSum_edep[1]);
  Tremoll_bkg2->SetBranchAddress("cal.det_x",&fCalDetPos_X[1]);
  Tremoll_bkg2->SetBranchAddress("cal.det_y",&fCalDetPos_Y[1]);
  Tremoll_bkg2->SetBranchAddress("cal.x",&fCalDetSum_x[1]);
  Tremoll_bkg2->SetBranchAddress("cal.y",&fCalDetSum_y[1]);
  Tremoll_bkg2->SetBranchAddress("cal.st",&fCalDet_ST[1]);
  Tremoll_bkg2->SetBranchAddress("cal.et",&fCalDet_ST[1]);

  TChain * Tremoll_bkg3 =new TChain("T");
  //Tremoll_bkg3->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_p_D_1M.root"); 
  //simulation with lead baffles
  //Tremoll_bkg3->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_p_D_1M_1.root"); 
  //simulation with lead baffles + lead photon blocker  
  //Tremoll_bkg3->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1Blocked_uniformpi_p_D_1M_1.root"); 
  //simulation with lead baffles using hall d generator
  Tremoll_bkg3->Add("/work/halla/solid/tianye/mergBKG_output/remoll_LD_HallD_pip_1M.root");
  Tremoll_bkg3->SetBranchAddress("ev.evnum",&fEv_num[2]);
  Tremoll_bkg3->SetBranchAddress("rate",&fEvRate[2]);   
  Tremoll_bkg3->SetBranchAddress("ev.W2",&fEvW2[2]); 
  Tremoll_bkg3->SetBranchAddress("ev.xbj",&fEvXbj[2]); 
  //generic hit (for GEMs)
  Tremoll_bkg3->SetBranchAddress("hit.n",&fNGenDetHit[2]);
  Tremoll_bkg3->SetBranchAddress("hit.det",&fGenDetHit_det[2]);
  Tremoll_bkg3->SetBranchAddress("hit.pid",&fGenDetHit_pid[2]);
  Tremoll_bkg3->SetBranchAddress("hit.trid",&fGenDetHit_trid[2]);
  Tremoll_bkg3->SetBranchAddress("hit.mtrid",&fGenDetHit_mtrid[2]);
  Tremoll_bkg3->SetBranchAddress("hit.p",&fGenDetHit_P[2]);
  Tremoll_bkg3->SetBranchAddress("hit.pz",&fGenDetHit_PZ[2]);
  Tremoll_bkg3->SetBranchAddress("hit.x",&fGenDetHit_X[2]);
  Tremoll_bkg3->SetBranchAddress("hit.y",&fGenDetHit_Y[2]);
  Tremoll_bkg3->SetBranchAddress("hit.z",&fGenDetHit_Z[2]);
  Tremoll_bkg3->SetBranchAddress("hit.vz",&fGenDetHit_VZ[2]);
  Tremoll_bkg3->SetBranchAddress("hit.t",&fGenDetHit_T[2]);

  //ecal sum hits
  Tremoll_bkg3->SetBranchAddress("cal.n",&fNCalDetSum[2]);
  Tremoll_bkg3->SetBranchAddress("cal.det",&fCalDetSum_det[2]);
  Tremoll_bkg3->SetBranchAddress("cal.edep",&fCalDetSum_edep[2]);
  Tremoll_bkg3->SetBranchAddress("cal.det_x",&fCalDetPos_X[2]);
  Tremoll_bkg3->SetBranchAddress("cal.det_y",&fCalDetPos_Y[2]);
  Tremoll_bkg3->SetBranchAddress("cal.x",&fCalDetSum_x[2]);
  Tremoll_bkg3->SetBranchAddress("cal.y",&fCalDetSum_y[2]);
  Tremoll_bkg3->SetBranchAddress("cal.st",&fCalDet_ST[2]);
  Tremoll_bkg3->SetBranchAddress("cal.et",&fCalDet_ST[2]);

  TChain * Tremoll_bkg4 =new TChain("T");
  //Tremoll_bkg4->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_p_D_1M.root"); 
  //simulation with lead baffles
  //Tremoll_bkg4->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1_uniformpi_p_D_1M_1.root"); 
  //simulation with lead baffles + lead photon blocker  
  //Tremoll_bkg4->Add("/home/rakithab/Simulation_Analysis/Remoll/SoLID/Rootfiles/remoll_babarmore1Blocked_uniformpi_p_D_1M_1.root"); 
  //simulation with lead baffles using G4 only EM 
  Tremoll_bkg4->Add("/work/halla/solid/tianye/mergBKG_output/remoll_e_beam_EMOnly_LD_1M_*.root");
  Tremoll_bkg4->SetBranchAddress("ev.evnum",&fEv_num[3]);
  Tremoll_bkg4->SetBranchAddress("rate",&fEvRate[3]);   
  Tremoll_bkg4->SetBranchAddress("ev.W2",&fEvW2[3]); 
  Tremoll_bkg4->SetBranchAddress("ev.xbj",&fEvXbj[3]); 
  //generic hit (for GEMs)
  Tremoll_bkg4->SetBranchAddress("hit.n",&fNGenDetHit[3]);
  Tremoll_bkg4->SetBranchAddress("hit.det",&fGenDetHit_det[3]);
  Tremoll_bkg4->SetBranchAddress("hit.pid",&fGenDetHit_pid[3]);
  Tremoll_bkg4->SetBranchAddress("hit.trid",&fGenDetHit_trid[3]);
  Tremoll_bkg4->SetBranchAddress("hit.mtrid",&fGenDetHit_mtrid[3]);
  Tremoll_bkg4->SetBranchAddress("hit.p",&fGenDetHit_P[3]);
  Tremoll_bkg4->SetBranchAddress("hit.pz",&fGenDetHit_PZ[3]);
  Tremoll_bkg4->SetBranchAddress("hit.x",&fGenDetHit_X[3]);
  Tremoll_bkg4->SetBranchAddress("hit.y",&fGenDetHit_Y[3]);
  Tremoll_bkg4->SetBranchAddress("hit.z",&fGenDetHit_Z[3]);
  Tremoll_bkg4->SetBranchAddress("hit.vz",&fGenDetHit_VZ[3]);
  Tremoll_bkg4->SetBranchAddress("hit.t",&fGenDetHit_T[3]);

  //ecal sum hits
  Tremoll_bkg4->SetBranchAddress("cal.n",&fNCalDetSum[3]);
  Tremoll_bkg4->SetBranchAddress("cal.det",&fCalDetSum_det[3]);
  Tremoll_bkg4->SetBranchAddress("cal.edep",&fCalDetSum_edep[3]);
  Tremoll_bkg4->SetBranchAddress("cal.det_x",&fCalDetPos_X[3]);
  Tremoll_bkg4->SetBranchAddress("cal.det_y",&fCalDetPos_Y[3]);
  Tremoll_bkg4->SetBranchAddress("cal.x",&fCalDetSum_x[3]);
  Tremoll_bkg4->SetBranchAddress("cal.y",&fCalDetSum_y[3]);
  Tremoll_bkg4->SetBranchAddress("cal.st",&fCalDet_ST[3]);
  Tremoll_bkg4->SetBranchAddress("cal.et",&fCalDet_ST[3]);

  //this vector stores the event numbers but for ease of access store the tree index
  vector<Int_t> vec_evnum;
  //this vector stores the time stamp of the event. Time start at t=0 for the 1st event
  vector< vector<Double_t> > vec_timestamp;
  vec_timestamp.resize(__TREE_COUNT);

  Double_t total_rate[__TREE_COUNT-1]={0,0,0};
  Int_t nentries[__TREE_COUNT-1];
  nentries[0]= (Int_t)Tremoll_bkg1->GetEntries();
  nentries[1]= (Int_t)Tremoll_bkg2->GetEntries();
  nentries[2]= (Int_t)Tremoll_bkg3->GetEntries();
  //bkg4 is for beam and not considered for computing max entries
  nentries[3]= 0;

  //compute the max entry tree
  Int_t nentries_max=0;
  
  for (Int_t c=0;c < __TREE_COUNT-1;c++){
    if (nentries[c]>nentries_max)
      nentries_max = nentries[c];
    printf(" tree %i has %i \n",c,nentries[c]);    
  }

  //bkg4 is for beam and not considered for computing max entries
  nentries[3]= (Int_t)Tremoll_bkg4->GetEntries();
  printf(" e-beam tree  has %i \n",nentries[3]);   

  //Int_t good_event[__TREE_COUNT-1]={0};

  //total pion rates from generator input with full rad length used for bremss
  /*
  total_rate[0] = 41400187473.632812;//Hz Pi-
  total_rate[1] = 39758723512.207031;//Hz Pi0
  total_rate[2] = 41400187473.632812;//Hz Pi+ 
  */
  

  //total pion rates from generator input,
  total_rate[0] = 28510143471.984863;//Hz Pi-   
  total_rate[1] = 27359099079.223633;//Hz Pi0   
  total_rate[2] = 28510143471.984863;//Hz Pi+    
  //bkg4 is for beam 
  Double_t beamRate; 
  Int_t beamEvents;
  total_rate[3] = 0;//6.241e+12*50;//Hz for e-beam                                                                              

  //use this index to access events in the beam_event vector
  Int_t beamEvents_index=0;
  
  //Step 1 : generate list of primary e-beam events with hits that crossed the ECAL front face
  if(BKG4_ON){
    beamRate = 6.241e+12*50/nentries[3];//Hz per event for e-beam   
    for (int i=0; i<nentries[3] ; i++) {
      Tremoll_bkg4->GetEntry(i);
      for (int j = 0; j<fNGenDetHit[3]; j++){
	if( fGenDetHit_det[3][j]==70002 && fGenDetHit_PZ[3][j] > 0 && (fGenDetHit_P[3][j] > 0 && fGenDetHit_P[3][j] <= 12)){//id 70002 is front face of ecal // && fGenDetHit_VZ[j] < 3.265 && fGenDetHit_T[j] <= DelayedHitTimeLimit
	  total_rate[3]+=beamRate;
	  vec_evnum.push_back(beamEvents_index);
	  ebeam_event.fEv_num = beamEvents_index;//or use sequential index
	  ebeam_event.fNGenDetHit = fNGenDetHit[3];
	  ebeam_event.fNCalDetSum = fNCalDetSum[3];
	  for (int k = 0; k<fNGenDetHit[3]; k++){
	    dethit.fGenDetHit_det = fGenDetHit_det[3][k];
	    dethit.fGenDetHit_trid = fGenDetHit_trid[3][k];
	    dethit.fGenDetHit_mtrid = fGenDetHit_mtrid[3][k];
	    dethit.fGenDetHit_pid = fGenDetHit_pid[3][k];
	    dethit.fGenDetHit_P = fGenDetHit_P[3][k];
	    dethit.fGenDetHit_PZ = fGenDetHit_PZ[3][k];
	    dethit.fGenDetHit_X = fGenDetHit_X[3][k];
	    dethit.fGenDetHit_Y = fGenDetHit_Y[3][k];
	    dethit.fGenDetHit_Z = fGenDetHit_Z[3][k];
	    dethit.fGenDetHit_VZ = fGenDetHit_VZ[3][k];
	    dethit.fGenDetHit_T = fGenDetHit_T[3][k];
	    ebeam_event.hitlist.push_back(dethit);
	  }
	  for (int k = 0; k<fNCalDetSum[3]; k++){
	    detsum.fCalDetSum_det = fCalDetSum_det[3][k];
	    detsum.fCalDetSum_edep = fCalDetSum_edep[3][k];
	    detsum.fCalDetSum_x = fCalDetSum_x[3][k];
	    detsum.fCalDetSum_y = fCalDetSum_y[3][k];
	    detsum.fCalDetPos_X = fCalDetPos_X[3][k];
	    detsum.fCalDetPos_Y = fCalDetPos_Y[3][k];
	    detsum.fCalDetPos_Z = fCalDetPos_Z[3][k];
	    detsum.fCalDet_ST = fCalDet_ST[3][k];
	    detsum.fCalDet_ET = fCalDet_ET[3][k];
	    ebeam_event.sumlist.push_back(detsum);
	  }
	  ebeam_event_list.push_back(ebeam_event);
	  beamEvents_index++;//increment the beam event count
	  ebeam_event.hitlist.clear();
	  ebeam_event.sumlist.clear();
	  break;	  
	}
      }
    }
    beamEvents=vec_evnum.size();
  }


  printf("pi- = %3.3f kHz, pi0 = %3.3f kHz, pi+ = %3.3f kHz e-beam = %3.3f kHz \n",total_rate[0]/1000,total_rate[1]/1000,total_rate[2]/1000,total_rate[3]/1000);
  //end of step 1

  //step 2 : generate time sequences,
  Double_t t[__TREE_COUNT-1]={0};
  //reference for the following can be found at http://root.cern.ch/root/html/TRandom.html
  TRandom *r3 = new TRandom3();
  Double_t detlaT[__TREE_COUNT-1]={0};

  event single_event;

  printf("pi- Total Rate %3.3f kHz detlaT = 1e9/Rate = %3.3f ns Total events %i \n",total_rate[0]/1000,1e9/total_rate[0],nentries[0]);
  printf("pi0 Total Rate %3.3f kHz detlaT = 1e9/Rate = %3.3f ns Total events %i \n",total_rate[1]/1000,1e9/total_rate[1],nentries[1]);
  printf("pi+ Total Rate %3.3f kHz detlaT = 1e9/Rate = %3.3f ns Total events %i \n",total_rate[2]/1000,1e9/total_rate[2],nentries[2]);
  printf("e-beam Total Rate %3.3f kHz detlaT = 1e9/Rate = %3.3e ns Total events %i %i \n",total_rate[3]/1000,1e9/total_rate[3],beamEvents,ebeam_event_list.size());

  //exit(1);

  detlaT[0] = 1e9/total_rate[0];
  detlaT[1] = 1e9/total_rate[1];
  detlaT[2] = 1e9/total_rate[2];
  detlaT[3] = 1e9/total_rate[3];
  for(Int_t i=0; i<nentries_max; i++){
    if(BKG1_ON){
      t[0] += detlaT[0];
      vec_timestamp[0].push_back(t[0]);
      single_event.input=1;
      single_event.ev_num=i;//this is the index number that will be used to access the events :  TChain->GetEntry(index)
      single_event.timestamp=t[0];
      event_list.push_back(single_event);
    }
    if(BKG2_ON){
      t[1] += detlaT[1];
      vec_timestamp[1].push_back(t[1]);
      single_event.input=2;
      single_event.ev_num=i;
      single_event.timestamp=t[1];
      event_list.push_back(single_event);
    }
    if(BKG3_ON){
      t[2] += detlaT[2];
      vec_timestamp[2].push_back(t[2]);
      single_event.input=3;
      single_event.ev_num=i;
      single_event.timestamp=t[2];
      event_list.push_back(single_event);
    }
  }


  //end of step 2

  //Step 3 : check to see totaltime<=totaltime_bkg1 otherwise extend the background events to match total time for main tracks
  Int_t timeWindow = 30; //integration time window in ns
  //get the total length of the time sequence for main tracks (DIS)
  Double_t totaltime[3]={0};
  Int_t totalWindows[3]={0};

  //BKG1
  if (BKG1_ON){
    totaltime[0] = vec_timestamp[0][vec_timestamp[0].size()-1];
    totalWindows[0] = (Int_t)totaltime[0]/timeWindow + 1;
    printf("Total time from pi- %f ns \n Total events %i \n",totaltime[0],vec_timestamp[0].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[0]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[0]);
  }
  //BKG2
  if (BKG2_ON){
    totaltime[1] = vec_timestamp[1][vec_timestamp[1].size()-1];
    totalWindows[1] = (Int_t)totaltime[1]/timeWindow + 1;
    printf("Total time from pi0 %f ns \n Total events %i \n",totaltime[1],vec_timestamp[1].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[1]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[1]);
  }
  //BKG3
  if (BKG3_ON){
    totaltime[2] = vec_timestamp[2][vec_timestamp[2].size()-1];
    totalWindows[2] = (Int_t)totaltime[2]/timeWindow + 1;
    printf("Total time from pi+ %f ns \n Total events %i \n",totaltime[2],vec_timestamp[2].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[2]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[2]);    
  }

  Double_t currenttime=0;
  //to keep track of the event indices
  Int_t event_count[__TREE_COUNT-1]={0,0,0};
  //time loop access  tracks in each timeWindow




  Int_t min_timewindows=100000;
  for (Int_t c=0;c < (__TREE_COUNT-2);c++){//ignore the e-beam (last index)
    if (totalWindows[c]<min_timewindows)
      min_timewindows = totalWindows[c];
  }
  Int_t e_beam_entries =  (Int_t) min_timewindows * 30 * total_rate[3]/1e9 + 1;

  printf(" Total e-beam events to be merged %i \n",e_beam_entries);    

  printf(" Time windows added to merged root file %i \n",min_timewindows);    

  //need to fill the event_list with e-beam events as much as total time for hadron backgrounds ie upto min_timewindows
  if (BKG4_ON){
    for(Int_t i=0; i<e_beam_entries; i++){
      t[3] += detlaT[3];
      vec_timestamp[3].push_back(t[3]);
      single_event.input=4;
      single_event.ev_num=vec_evnum[r3->Integer(beamEvents)];//randomly fill a event number
      single_event.timestamp=t[3];
      event_list.push_back(single_event);      
    }
  }

  //For now next steps in step 3 are not added. Here all the vectors are set to same lenght in time

  //exit(1);
  //sort out three time sequences and merge entries to the new tree

  //TStopwatch watch;//DEBUG
  //watch.Start();//DEBUG
  std::sort(event_list.begin(),event_list.end());


  //step 4 : Merge Trees
  Int_t current_window=0;
  Int_t timestamp_int;

  printf("Merging Trees Started \n");
  printf("Debug: Total events in the even_list vector %i \n",event_list.size());
  fEvTimeWindow[__TREE_COUNT-1]=0;
  for (Int_t e=0; e<event_list.size();e++){
   
    //access the event
    single_event = event_list[e];

    current_window = (Int_t)single_event.timestamp/timeWindow;
    cout<<"event="<<e<<"bkg="<<single_event.input<<"current_window="<<current_window<<endl;
    if (current_window>=min_timewindows){
      printf("Minimum time windows allowed has reached : %i \n",current_window);
      break;
    }
    //printf("Debug: trigger window %i current time %__TREE_COUNT-1.3f\n",current_window,single_event.timestamp);
    /*
    timestamp_int = (Int_t)floor(single_event.timestamp+0.500000);
    if (timestamp_int%timeWindow != 0){
      current_window++;
      printf("Debug: Incremnting trigger window %i \n",current_window);
    }
    */
    fEvTimeWindow[__TREE_COUNT-1]=current_window;

    if (single_event.input==1){//BKG1
      Tremoll_bkg1->GetEntry(single_event.ev_num);
      fNGenDetHit[__TREE_COUNT-1]=fNGenDetHit[0];
      fEvRate[__TREE_COUNT-1]=fEvRate[0];
      //give a new unique event number
      fEv_num[__TREE_COUNT-1]=e+1;
      fEvTimeStamp[__TREE_COUNT-1]=single_event.timestamp;
      fEv_simpid[__TREE_COUNT-1]=simpid[0];
      fEv_ratefactor[__TREE_COUNT-1]=1;
      fEvW2[__TREE_COUNT-1]=fEvW2[0];
      fEvXbj[__TREE_COUNT-1]=fEvXbj[0];
      //set hit info
      for (int j = 0; j<fNGenDetHit[0]; j++){
	fGenDetHit_det[__TREE_COUNT-1][j]=fGenDetHit_det[0][j];
	fGenDetHit_trid[__TREE_COUNT-1][j]=fGenDetHit_trid[0][j];
	fGenDetHit_mtrid[__TREE_COUNT-1][j]=fGenDetHit_mtrid[0][j];
	fGenDetHit_pid[__TREE_COUNT-1][j]=fGenDetHit_pid[0][j];
	fGenDetHit_P[__TREE_COUNT-1][j]=fGenDetHit_P[0][j];
	fGenDetHit_PZ[__TREE_COUNT-1][j]=fGenDetHit_PZ[0][j];
	fGenDetHit_X[__TREE_COUNT-1][j]=fGenDetHit_X[0][j];
	fGenDetHit_Y[__TREE_COUNT-1][j]=fGenDetHit_Y[0][j];
	fGenDetHit_Z[__TREE_COUNT-1][j]=fGenDetHit_Z[0][j];
	fGenDetHit_VZ[__TREE_COUNT-1][j]=fGenDetHit_VZ[0][j];
	fGenDetHit_T[__TREE_COUNT-1][j]=fGenDetHit_T[0][j];
      }
      //set ecal info
      fNCalDetSum[__TREE_COUNT-1]=fNCalDetSum[0];
      for (int j = 0; j<fNCalDetSum[0]; j++){
	fCalDetSum_det[__TREE_COUNT-1][j]=fCalDetSum_det[0][j];
	fCalDetSum_edep[__TREE_COUNT-1][j]=fCalDetSum_edep[0][j];
	fCalDetPos_X[__TREE_COUNT-1][j]=fCalDetPos_X[0][j];
	fCalDetPos_Y[__TREE_COUNT-1][j]=fCalDetPos_Y[0][j];
	fCalDetPos_Z[__TREE_COUNT-1][j]=fCalDetPos_Z[0][j];
	fCalDetSum_x[__TREE_COUNT-1][j]=fCalDetSum_x[0][j];
	fCalDetSum_y[__TREE_COUNT-1][j]=fCalDetSum_y[0][j];
	fCalDet_ST[__TREE_COUNT-1][j]=fCalDet_ST[0][j];
	fCalDet_ET[__TREE_COUNT-1][j]=fCalDet_ET[0][j];
      }            
    }
    if (single_event.input==2){//BKG2
      Tremoll_bkg2->GetEntry(single_event.ev_num);
      fNGenDetHit[__TREE_COUNT-1]=fNGenDetHit[1];
      fEvRate[__TREE_COUNT-1]=fEvRate[1];
      //give a new unique event number
      fEv_num[__TREE_COUNT-1]=e+1;
      fEvTimeStamp[__TREE_COUNT-1]=single_event.timestamp;
      fEv_simpid[__TREE_COUNT-1]=simpid[1];
      fEv_ratefactor[__TREE_COUNT-1]=1;
      fEvW2[__TREE_COUNT-1]=fEvW2[1];
      fEvXbj[__TREE_COUNT-1]=fEvXbj[1];
      //set hit info
      for (int j = 0; j<fNGenDetHit[1]; j++){
	fGenDetHit_det[__TREE_COUNT-1][j]=fGenDetHit_det[1][j];
	fGenDetHit_trid[__TREE_COUNT-1][j]=fGenDetHit_trid[1][j];
	fGenDetHit_mtrid[__TREE_COUNT-1][j]=fGenDetHit_mtrid[1][j];
	fGenDetHit_pid[__TREE_COUNT-1][j]=fGenDetHit_pid[1][j];
	fGenDetHit_P[__TREE_COUNT-1][j]=fGenDetHit_P[1][j];
	fGenDetHit_PZ[__TREE_COUNT-1][j]=fGenDetHit_PZ[1][j];
	fGenDetHit_X[__TREE_COUNT-1][j]=fGenDetHit_X[1][j];
	fGenDetHit_Y[__TREE_COUNT-1][j]=fGenDetHit_Y[1][j];
	fGenDetHit_Z[__TREE_COUNT-1][j]=fGenDetHit_Z[1][j];
	fGenDetHit_VZ[__TREE_COUNT-1][j]=fGenDetHit_VZ[1][j];
	fGenDetHit_T[__TREE_COUNT-1][j]=fGenDetHit_T[1][j];
      }
      //set ecal info
      fNCalDetSum[__TREE_COUNT-1]=fNCalDetSum[1];
      for (int j = 0; j<fNCalDetSum[1]; j++){
	fCalDetSum_det[__TREE_COUNT-1][j]=fCalDetSum_det[1][j];
	fCalDetSum_edep[__TREE_COUNT-1][j]=fCalDetSum_edep[1][j];
	fCalDetPos_X[__TREE_COUNT-1][j]=fCalDetPos_X[1][j];
	fCalDetPos_Y[__TREE_COUNT-1][j]=fCalDetPos_Y[1][j];
	fCalDetPos_Z[__TREE_COUNT-1][j]=fCalDetPos_Z[1][j];
	fCalDetSum_x[__TREE_COUNT-1][j]=fCalDetSum_x[1][j];
	fCalDetSum_y[__TREE_COUNT-1][j]=fCalDetSum_y[1][j];
	fCalDet_ST[__TREE_COUNT-1][j]=fCalDet_ST[1][j];
	fCalDet_ET[__TREE_COUNT-1][j]=fCalDet_ET[1][j];
      }            
    }
    if (single_event.input==3){//BKG3
      Tremoll_bkg3->GetEntry(single_event.ev_num);
      fNGenDetHit[__TREE_COUNT-1]=fNGenDetHit[2];
      fEvRate[__TREE_COUNT-1]=fEvRate[2];
      //give a new unique event number
      fEv_num[__TREE_COUNT-1]=e+1;
      fEvTimeStamp[__TREE_COUNT-1]=single_event.timestamp;
      fEv_simpid[__TREE_COUNT-1]=simpid[2];
      fEv_ratefactor[__TREE_COUNT-1]=1;
      fEvW2[__TREE_COUNT-1]=fEvW2[2];
      fEvXbj[__TREE_COUNT-1]=fEvXbj[2];
      //set hit info
      for (int j = 0; j<fNGenDetHit[2]; j++){
	fGenDetHit_det[__TREE_COUNT-1][j]=fGenDetHit_det[2][j];
	fGenDetHit_trid[__TREE_COUNT-1][j]=fGenDetHit_trid[2][j];
	fGenDetHit_mtrid[__TREE_COUNT-1][j]=fGenDetHit_mtrid[2][j];
	fGenDetHit_pid[__TREE_COUNT-1][j]=fGenDetHit_pid[2][j];
	fGenDetHit_P[__TREE_COUNT-1][j]=fGenDetHit_P[2][j];
	fGenDetHit_PZ[__TREE_COUNT-1][j]=fGenDetHit_PZ[2][j];
	fGenDetHit_X[__TREE_COUNT-1][j]=fGenDetHit_X[2][j];
	fGenDetHit_Y[__TREE_COUNT-1][j]=fGenDetHit_Y[2][j];
	fGenDetHit_Z[__TREE_COUNT-1][j]=fGenDetHit_Z[2][j];
	fGenDetHit_VZ[__TREE_COUNT-1][j]=fGenDetHit_VZ[2][j];
	fGenDetHit_T[__TREE_COUNT-1][j]=fGenDetHit_T[2][j];
      }
      //set ecal info
      fNCalDetSum[__TREE_COUNT-1]=fNCalDetSum[2];
      for (int j = 0; j<fNCalDetSum[2]; j++){
	fCalDetSum_det[__TREE_COUNT-1][j]=fCalDetSum_det[2][j];
	fCalDetSum_edep[__TREE_COUNT-1][j]=fCalDetSum_edep[2][j];
	fCalDetPos_X[__TREE_COUNT-1][j]=fCalDetPos_X[2][j];
	fCalDetPos_Y[__TREE_COUNT-1][j]=fCalDetPos_Y[2][j];
	fCalDetPos_Z[__TREE_COUNT-1][j]=fCalDetPos_Z[2][j];
	fCalDetSum_x[__TREE_COUNT-1][j]=fCalDetSum_x[2][j];
	fCalDetSum_y[__TREE_COUNT-1][j]=fCalDetSum_y[2][j];
	fCalDet_ST[__TREE_COUNT-1][j]=fCalDet_ST[2][j];
	fCalDet_ET[__TREE_COUNT-1][j]=fCalDet_ET[2][j];
      }            
    }
    if (single_event.input==4){//e-beam events
      ebeam_event = ebeam_event_list[single_event.ev_num];  //read the event ev_num from the ebeam_event_list into the  ebeam_event      
      //Tremoll_bkg4->GetEntry(single_event.ev_num);
      fNGenDetHit[__TREE_COUNT-1]=ebeam_event.fNGenDetHit;
      fEvRate[__TREE_COUNT-1]=beamRate;
      //give a new unique event number
      fEv_num[__TREE_COUNT-1]=e+1;
      fEvTimeStamp[__TREE_COUNT-1]=single_event.timestamp;
      fEv_simpid[__TREE_COUNT-1]=simpid[3];
      fEv_ratefactor[__TREE_COUNT-1]=1;
      fEvW2[__TREE_COUNT-1]=0;
      fEvXbj[__TREE_COUNT-1]=0;
      
      //set hit info
      for (int j = 0; j<ebeam_event.fNGenDetHit; j++){
	dethit = ebeam_event.hitlist[j];
	fGenDetHit_det[__TREE_COUNT-1][j]=dethit.fGenDetHit_det;
	fGenDetHit_trid[__TREE_COUNT-1][j]=dethit.fGenDetHit_trid;
	fGenDetHit_mtrid[__TREE_COUNT-1][j]=dethit.fGenDetHit_mtrid;
	fGenDetHit_pid[__TREE_COUNT-1][j]=dethit.fGenDetHit_pid;
	fGenDetHit_P[__TREE_COUNT-1][j]=dethit.fGenDetHit_P;
	fGenDetHit_PZ[__TREE_COUNT-1][j]=dethit.fGenDetHit_PZ;
	fGenDetHit_X[__TREE_COUNT-1][j]=dethit.fGenDetHit_X;
	fGenDetHit_Y[__TREE_COUNT-1][j]=dethit.fGenDetHit_Y;
	fGenDetHit_Z[__TREE_COUNT-1][j]=dethit.fGenDetHit_Z;
	fGenDetHit_VZ[__TREE_COUNT-1][j]=dethit.fGenDetHit_VZ;
	fGenDetHit_T[__TREE_COUNT-1][j]=dethit.fGenDetHit_T;
      }
      
      //set ecal info
      fNCalDetSum[__TREE_COUNT-1]=ebeam_event.fNCalDetSum;
      for (int j = 0; j<ebeam_event.fNCalDetSum; j++){
	detsum = ebeam_event.sumlist[j];
	fCalDetSum_det[__TREE_COUNT-1][j]=detsum.fCalDetSum_det;
	fCalDetSum_edep[__TREE_COUNT-1][j]=detsum.fCalDetSum_edep;
	fCalDetPos_X[__TREE_COUNT-1][j]=detsum.fCalDetPos_X;
	fCalDetPos_Y[__TREE_COUNT-1][j]=detsum.fCalDetPos_Y;
	fCalDetPos_Z[__TREE_COUNT-1][j]=detsum.fCalDetPos_Z;
	fCalDetSum_x[__TREE_COUNT-1][j]=detsum.fCalDetSum_x;
	fCalDetSum_y[__TREE_COUNT-1][j]=detsum.fCalDetSum_y;
	fCalDet_ST[__TREE_COUNT-1][j]=detsum.fCalDet_ST;
	fCalDet_ET[__TREE_COUNT-1][j]=detsum.fCalDet_ET;
      }      
            
    }
    FillTree();
    Flush();
    if (e%1000000==0)
      printf("Current entry %d and %2.1f completed \n",e,(Double_t)e*100/event_list.size());
    if (e>100000 && earlyMergebreak)
      break;
  }

  WriteTree();
  watch.Stop();
  //std::cout<<"Total Time "<<watch.RealTime()/60<<" min "<<std::endl;
  printf("Total Time %3.4f min \n Completed, Exit now :) \n",watch.RealTime()/60);

  theApp.Run();
  return(1);
}

void InitializeTree(){
  if( fFile ){
    fFile->Close();
    delete fFile;
  }
  fFile = new TFile(fFilename, "RECREATE");
  
  if( fTree ){ delete fTree; }
  
  fTree = new TTree("T", "Geant4 Remoll Simulation, Merged Tree");
  fTree->Branch("rate",     &fEvRate[__TREE_COUNT-1],   "rate/D");
  //we need to know where each event came from an index for each individual simulation, and use this as array index to get rate factor
  //fTree->Branch("ratefactor",     &fEvRateFactor[,   "rate/D");//multiple rate factor one each for BKG to get correct rate
  fTree->Branch("simpid",     &fEv_simpid[__TREE_COUNT-1],   "simpid/I");
  fTree->Branch("ratefactor",     &fEv_ratefactor[__TREE_COUNT-1],   "ratefactor/D");
  fTree->Branch("ev.evnum",  &fEv_num[__TREE_COUNT-1],   "ev.evnum/I");
  fTree->Branch("ev.evtimestamp",  &fEvTimeStamp[__TREE_COUNT-1],   "ev.evtimestamp/D");
  fTree->Branch("ev.evtimewindow",  &fEvTimeWindow[__TREE_COUNT-1],"ev.evtimewindow/I");
  fTree->Branch("ev.W2",     &fEvW2[__TREE_COUNT-1],   "ev.W2/D");
  fTree->Branch("ev.xbj",     &fEvXbj[__TREE_COUNT-1],   "ev.xbj/D");  

  // GenericDetectorHit
  fTree->Branch("hit.n",    &fNGenDetHit[__TREE_COUNT-1],     "hit.n/I");
  fTree->Branch("hit.det",  &fGenDetHit_det[__TREE_COUNT-1],  "hit.det[hit.n]/I");
  fTree->Branch("hit.pid",  &fGenDetHit_pid[__TREE_COUNT-1],   "hit.pid[hit.n]/I");
  fTree->Branch("hit.trid", &fGenDetHit_trid[__TREE_COUNT-1],  "hit.trid[hit.n]/I");
  fTree->Branch("hit.mtrid", &fGenDetHit_mtrid[__TREE_COUNT-1],  "hit.mtrid[hit.n]/I");
  fTree->Branch("hit.p",    &fGenDetHit_P[__TREE_COUNT-1],   "hit.p[hit.n]/D");
  fTree->Branch("hit.pz",    &fGenDetHit_PZ[__TREE_COUNT-1],   "hit.pz[hit.n]/D");
  fTree->Branch("hit.x",    &fGenDetHit_X[__TREE_COUNT-1],   "hit.x[hit.n]/D");
  fTree->Branch("hit.y",    &fGenDetHit_Y[__TREE_COUNT-1],   "hit.y[hit.n]/D");
  fTree->Branch("hit.z",    &fGenDetHit_Z[__TREE_COUNT-1],   "hit.z[hit.n]/D");
  fTree->Branch("hit.vz",    &fGenDetHit_VZ[__TREE_COUNT-1],   "hit.vz[hit.n]/D");
  fTree->Branch("hit.t",    &fGenDetHit_T[__TREE_COUNT-1],   "hit.t[hit.n]/D");

    // CalDetectorSum
  fTree->Branch("cal.n",    &fNCalDetSum[__TREE_COUNT-1],     "cal.n/I");
  fTree->Branch("cal.det",  &fCalDetSum_det[__TREE_COUNT-1],  "cal.det[cal.n]/I");
  fTree->Branch("cal.edep", &fCalDetSum_edep[__TREE_COUNT-1], "cal.edep[cal.n]/D");
  fTree->Branch("cal.det_x",    &fCalDetPos_X[__TREE_COUNT-1],    "cal.det_x[cal.n]/D");
  fTree->Branch("cal.det_y",    &fCalDetPos_Y[__TREE_COUNT-1],    "cal.det_y[cal.n]/D");
  fTree->Branch("cal.det_z",    &fCalDetPos_Z[__TREE_COUNT-1],    "cal.det_z[cal.n]/D");
  fTree->Branch("cal.x",    &fCalDetSum_x[__TREE_COUNT-1],    "cal.x[cal.n]/D");
  fTree->Branch("cal.y",    &fCalDetSum_y[__TREE_COUNT-1],    "cal.y[cal.n]/D");
  fTree->Branch("cal.st",    &fCalDet_ST[__TREE_COUNT-1],    "cal.st[cal.n]/D");
  fTree->Branch("cal.et",    &fCalDet_ET[__TREE_COUNT-1],    "cal.et[cal.n]/D");
  return;
}
void FillTree(){
    if( !fTree ){ 
	fprintf(stderr, "Error %s: %s line %d - Trying to fill non-existant tree\n", __PRETTY_FUNCTION__, __FILE__, __LINE__ );
	return; 
    }

    fTree->Fill();
}

void Flush(){
    //  Set arrays to 0
    fNGenDetHit[__TREE_COUNT-1] = 0;
    fNCalDetSum[__TREE_COUNT-1] = 0;
}

void WriteTree(){
    assert( fFile );
    assert( fTree );

    if( !fFile->IsOpen() ){
	cout << "ERROR: " << __FILE__ << " line " << __LINE__ << ": TFile not open" << endl;
	exit(1);
    }

    cout << "Writing output to " << fFile->GetName() << "... ";

    fFile->cd();

    fTree->Write("T", TObject::kOverwrite);

    fTree->ResetBranchAddresses();
    delete fTree;
    fTree = NULL;

    fFile->Close();

    delete fFile;
    fFile = NULL;

    cout << "written" << endl;

    return;
}
