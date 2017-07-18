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

#include "ecal_merge.h"


using namespace std;
using namespace std::tr1;
using std::vector;
using std::string;
using std::fstream;
#define __IO_MAXHIT 10000
#define __FILENAMELEN 255
//3rd one for the new TTRee 0,1, and 2 are for merging trees
#define __TREE_COUNT 5 
vector<Double_t>  *var8[__TREE_COUNT];
int fEvTimeWindow;
//FLUX bank

vector<int> *fFluxHit_id[__TREE_COUNT];
vector<Double_t> *fFluxHit_Px[__TREE_COUNT];
vector<Double_t> *fFluxHit_Py[__TREE_COUNT];
vector<Double_t> *fFluxHit_Pz[__TREE_COUNT];
vector<Double_t> *fFluxHit_Avg_x[__TREE_COUNT];
vector<Double_t> *fFluxHit_Avg_y[__TREE_COUNT];


vector<int> *fECHit_id[__TREE_COUNT];
vector<Double_t> *fECHit_totEdep[__TREE_COUNT];
vector<Double_t> *fECHit_Avg_z[__TREE_COUNT];

// merged output file tree variables
//header bank
vector<Double_t>  Mvar8;
//FLUX bank
vector<int> MfFluxHit_id;
vector<Double_t> MfFluxHit_Px;
vector<Double_t> MfFluxHit_Py;
vector<Double_t> MfFluxHit_Pz;
vector<Double_t> MfFluxHit_Avg_x;
vector<Double_t> MfFluxHit_Avg_y;;
//EC bank
vector<int> MfECHit_id;
vector<Double_t> MfECHit_totEdep;
vector<Double_t> MfECHit_Avg_z;




TFile *fFile;
TTree *fTree;
char fFilename[__FILENAMELEN];

Bool_t earlybreak=kFALSE;//kFALSE;//kTRUE;//kFALSE;//exit early from the main tree entries loop
Bool_t earlyMergebreak= kTRUE;//kFALSE;//exit early from the main tree entries loop

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
//singlegensum genhit;
singleevent ebeam_event;
vector<singleevent> ebeam_event_list;

const Int_t Sim_Count = 4;//3 bkg Pi+-0
Int_t simpid[Sim_Count]={-211,111,211,1};//simpid=1 is the ebeam events
Int_t FluxHit_detector_ID,FluxHit_subdetector_ID,FluxHit_subsubdetector_ID,FluxHit_component_ID;
Int_t FluxHit_detector_ID1,FluxHit_subdetector_ID1,FluxHit_subsubdetector_ID1,FluxHit_component_ID1;
Bool_t BKG1_ON = kTRUE;
Bool_t BKG2_ON = kTRUE;
Bool_t BKG3_ON = kTRUE;//kFALSE
Bool_t BKG4_ON = kTRUE;//e-beam
Bool_t BKG4_ECHIT = kFALSE;


int main(Int_t argc,Char_t* argv[]) { 
  
  //set the timer
  TStopwatch watch;
  watch.Start();
  TApplication theApp("App",&argc,argv);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("eMr");
  
  fTree = NULL;
  // Default filename
  strcpy(fFilename, "GEMC_merged_HallDpions_EMbkg_LD_SIDIS_allpions.root");
  
  InitializeTree();
  
  //load trees
  TFile *file1=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pimHallD_filenum500_5e6.root");
  TTree *TGEMC_header_pim = (TTree*) file1->Get("header");
  
  TGEMC_header_pim->SetBranchAddress("var8",&var8[0]);
  
  TTree *TGEMC_Flux_pim = (TTree*) file1->Get("flux");
  TGEMC_Flux_pim->SetBranchAddress("id",&fFluxHit_id[0]);
  TGEMC_Flux_pim->SetBranchAddress("avg_x",&fFluxHit_Avg_x[0]);
  TGEMC_Flux_pim->SetBranchAddress("avg_y",&fFluxHit_Avg_y[0]);
  TGEMC_Flux_pim->SetBranchAddress("px",&fFluxHit_Px[0]);
  TGEMC_Flux_pim->SetBranchAddress("py",&fFluxHit_Py[0]);
  TGEMC_Flux_pim->SetBranchAddress("pz",&fFluxHit_Pz[0]);
  
  TTree *TGEMC_EC_pim = (TTree*) file1->Get("solid_ec");
  
  TGEMC_EC_pim->SetBranchAddress("id",&fECHit_id[0]);
  TGEMC_EC_pim->SetBranchAddress("totEdep",&fECHit_totEdep[0]);
  TGEMC_EC_pim->SetBranchAddress("avg_z",&fECHit_Avg_z[0]);
  
  TFile *file2=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pi0HallD_filenum500_5e6.root"); 
  
  TTree *TGEMC_header_pi0 = (TTree*) file2->Get("header");
  
  TGEMC_header_pi0->SetBranchAddress("var8",&var8[1]);
  TTree *TGEMC_Flux_pi0 = (TTree*) file2->Get("flux");
  TGEMC_Flux_pi0->SetBranchAddress("id",&fFluxHit_id[1]);
  TGEMC_Flux_pi0->SetBranchAddress("avg_x",&fFluxHit_Avg_x[1]);
  TGEMC_Flux_pi0->SetBranchAddress("px",&fFluxHit_Px[1]);
  TGEMC_Flux_pi0->SetBranchAddress("py",&fFluxHit_Py[1]);
  TGEMC_Flux_pi0->SetBranchAddress("pz",&fFluxHit_Pz[1]);
  
  
  TTree *TGEMC_EC_pi0 = (TTree*) file2->Get("solid_ec");
  
  TGEMC_EC_pi0->SetBranchAddress("id",&fECHit_id[1]);
  TGEMC_EC_pi0->SetBranchAddress("totEdep",&fECHit_totEdep[1]);
  TGEMC_EC_pi0->SetBranchAddress("avg_z",&fECHit_Avg_z[1]);
  
  TFile *file3=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pipHallD_filenum500_5e6.root");
  TTree *TGEMC_header_pip = (TTree*) file3->Get("header");
  
  TGEMC_header_pip->SetBranchAddress("var8",&var8[2]);
  
  TTree *TGEMC_Flux_pip = (TTree*) file3->Get("flux");
  
  TGEMC_Flux_pip->SetBranchAddress("id",&fFluxHit_id[2]);
  TGEMC_Flux_pip->SetBranchAddress("avg_x",&fFluxHit_Avg_x[2]);
  TGEMC_Flux_pip->SetBranchAddress("avg_y",&fFluxHit_Avg_y[2]);
  TGEMC_Flux_pip->SetBranchAddress("px",&fFluxHit_Px[2]);
  TGEMC_Flux_pip->SetBranchAddress("py",&fFluxHit_Py[2]);
  TGEMC_Flux_pip->SetBranchAddress("pz",&fFluxHit_Pz[2]);
  
  TTree *TGEMC_EC_pip = (TTree*) file3->Get("solid_ec");
  
  TGEMC_EC_pip->SetBranchAddress("id",&fECHit_id[2]);
  TGEMC_EC_pip->SetBranchAddress("totEdep",&fECHit_totEdep[2]);
  TGEMC_EC_pip->SetBranchAddress("avg_z",&fECHit_Avg_z[2]);
  
  TFile *file4=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_BeamOnTargetEM_1e10_skim.root");
  TTree *TGEMC_header_EM= (TTree*) file4->Get("header");
  
  TGEMC_header_EM->SetBranchAddress("var8",&var8[3]);
  
  TTree *TGEMC_Flux_EM = (TTree*) file4->Get("flux");
  TGEMC_Flux_EM->SetBranchAddress("id",&fFluxHit_id[3]);
  TGEMC_Flux_EM->SetBranchAddress("avg_x",&fFluxHit_Avg_x[3]);
  TGEMC_Flux_EM->SetBranchAddress("avg_y",&fFluxHit_Avg_y[3]);
  TGEMC_Flux_EM->SetBranchAddress("px",&fFluxHit_Px[3]);
  TGEMC_Flux_EM->SetBranchAddress("py",&fFluxHit_Py[3]);
  TGEMC_Flux_EM->SetBranchAddress("pz",&fFluxHit_Pz[3]);
  
  TTree *TGEMC_EC_EM = (TTree*) file4->Get("solid_ec");
  TGEMC_EC_EM->SetBranchAddress("id",&fECHit_id[3]);
  TGEMC_EC_EM->SetBranchAddress("totEdep",&fECHit_totEdep[3]);
  TGEMC_EC_EM->SetBranchAddress("avg_z",&fECHit_Avg_z[3]);
  Double_t pf_flux;
  //this vector stores the event numbers but for ease of access store the tree index
  vector<Int_t> vec_evnum;
  //this vector stores the time stamp of the event. Time start at t=0 for the 1st event
  vector< vector<Double_t> > vec_timestamp;
  vec_timestamp.resize(__TREE_COUNT);
  
  Double_t total_rate[__TREE_COUNT-1]={0};
  Int_t nentries[__TREE_COUNT-1];
  nentries[0]= (Int_t)TGEMC_Flux_pim->GetEntries();
  nentries[1]= (Int_t)TGEMC_Flux_pi0->GetEntries();
  nentries[2]= (Int_t)TGEMC_Flux_pip->GetEntries();
  //bkg4 is for beam and not considered for computing max entries
  nentries[3]= 0;
  
  //compute the max entry tree
  Int_t nentries_max=0;
  
  for (Int_t c=0;c <3;c++){
    if (nentries[c]>nentries_max)
      nentries_max = nentries[c];
    printf(" tree %i has %i \n",c,nentries[c]);    
  }
  
  //bkg4 is for beam and not considered for computing max entries
  nentries[3]= (Int_t)TGEMC_Flux_EM->GetEntries();
  printf(" e-beam tree  has %i \n",nentries[3]);   
  //total pion rates from generator input,
  total_rate[0] = 1.55508e+09/500.0;//Hz Pi-   
  total_rate[1] = 2.53825e+09/500.0;//Hz Pi0   
  total_rate[2] = 1.98872e+09/500.0;//Hz Pi+    
  total_rate[3] = 1.36207e+10;//Hz EM only beam on target
  //bkg4 is for beam 
  Double_t beamRate;       
  Int_t beamEvents;
  //use this index to access events in the beam_event vector
  Int_t beamEvents_index=0;
  //Step 1 : generate list of primary e-beam events with hits that crossed the ECAL front face
  if(BKG4_ON){ 
    for (int i=0; i<nentries[3] ; i++) {
      TGEMC_Flux_EM->GetEntry(i);
      //tree_generated_EM->GetEntry(i);
      TGEMC_EC_EM->GetEntry(i);
      for (int j = 0; j<fFluxHit_id[3]->size(); j++){
	FluxHit_detector_ID=fFluxHit_id[3]->at(j)/1000000;
	FluxHit_subdetector_ID=(fFluxHit_id[3]->at(j)%1000000)/100000;
	FluxHit_subsubdetector_ID=((fFluxHit_id[3]->at(j)%1000000)%100000)/10000;
	FluxHit_component_ID=fFluxHit_id[3]->at(j)%10000;
	pf_flux=TMath::Sqrt(TMath::Power(fFluxHit_Px[3]->at(j),2)+TMath::Power(fFluxHit_Py[3]->at(j),2)+TMath::Power(fFluxHit_Pz[3]->at(j),2));
	if( FluxHit_detector_ID==3 && FluxHit_subdetector_ID == 1 && FluxHit_subsubdetector_ID == 1 && pf_flux>0 && pf_flux<12000){
	  
	  vec_evnum.push_back(beamEvents_index);
	  ebeam_event.fNGenDetHit = fFluxHit_id[3]->size();
	  ebeam_event.fNCalDetSum = fECHit_id[3]->size();
	  for (int k = 0; k<fFluxHit_id[3]->size(); k++){
	    dethit.MfFluxHit_id = fFluxHit_id[3]->at(k);
	    dethit.MfFluxHit_Avg_x = fFluxHit_Avg_x[3]->at(k);
	    dethit.MfFluxHit_Avg_y = fFluxHit_Avg_y[3]->at(k);
	    dethit.MfFluxHit_Px = fFluxHit_Px[3]->at(k);
	    dethit.MfFluxHit_Py = fFluxHit_Py[3]->at(k);
	    dethit.MfFluxHit_Pz = fFluxHit_Pz[3]->at(k);
	    ebeam_event.hitlist.push_back(dethit);
	    
	  }
	  
	  for (int k = 0; k<fECHit_id[3]->size(); k++){
	    detsum.MfECHit_id = fECHit_id[3]->at(k);
	    detsum.MfECHit_totEdep = fECHit_totEdep[3]->at(k);
	    detsum.MfECHit_Avg_z = fECHit_Avg_z[3]->at(k);
	    ebeam_event.sumlist.push_back(detsum);
	  }
	  ebeam_event_list.push_back(ebeam_event);
	  beamEvents_index++;//increment the beam event count
	  ebeam_event.hitlist.clear();
	  ebeam_event.sumlist.clear();
	  ebeam_event.genlist.clear();
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
      // cout<<"detlaT[0]=="<<detlaT[0]<<endl;
      vec_timestamp[0].push_back(t[0]);
      single_event.input=1;
      single_event.ev_num=i;//this is the index number that will be used to access the events 
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
  Double_t totaltime[3]={0};
  Int_t totalWindows[3]={0};
  
  //BKG1
  if (BKG1_ON){
    totaltime[0] = vec_timestamp[0][vec_timestamp[0].size()-1];
    totalWindows[0] = (Int_t)(totaltime[0]/timeWindow) + 1;
    printf("Total time from pi- %f ns \n Total events %i \n",totaltime[0],vec_timestamp[0].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[0]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[0]);
  }
  //BKG2
  if (BKG2_ON){
    totaltime[1] = vec_timestamp[1][vec_timestamp[1].size()-1];
    totalWindows[1] = (Int_t)(totaltime[1]/timeWindow) + 1;
    printf("Total time from pi0 %f ns \n Total events %i \n",totaltime[1],vec_timestamp[1].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[1]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[1]);
  }
  //BKG3
  if (BKG3_ON){
    totaltime[2] = vec_timestamp[2][vec_timestamp[2].size()-1];
    totalWindows[2] = (Int_t)(totaltime[2]/timeWindow) + 1;
    printf("Total time from pi+ %f ns \n Total events %i \n",totaltime[2],vec_timestamp[2].size());
    printf("Time window = %i ns, total windows = %i  \n",timeWindow,totalWindows[2]);
    printf("Total time in the time loop %i ns \n",timeWindow*totalWindows[2]);    
  }
  
  //to keep track of the event indices
  //time loop access  tracks in each timeWindow
  
  
  
  
  Int_t min_timewindows=1000000000;
  for (Int_t c=0;c < 3;c++){//ignore the e-beam (last index)
  if (totalWindows[c]<min_timewindows)
    min_timewindows = totalWindows[c];
  }
  long long int e_beam_entries = (Int_t) min_timewindows * 30 * total_rate[3]/1e9 + 1;
  cout<<" Total e-beam events to be merged"<<e_beam_entries<<endl;    
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
  std::sort(event_list.begin(),event_list.end());
  
  
  //step 4 : Merge Trees
  Int_t current_window=0;
  
  printf("Merging Trees Started \n");
  printf("Debug: Total events in the even_list vector %i \n",event_list.size());
  fEvTimeWindow=0;
  for (Int_t e=0; e<event_list.size();e++){
    //access the event
    single_event = event_list[e];
    
    current_window = (Int_t)single_event.timestamp/timeWindow;
    cout<<"event="<<e<<"bkg="<<single_event.input<<"current_window="<<current_window<<endl;
    if (current_window>=min_timewindows){
      printf("Minimum time windows allowed has reached : %i \n",current_window);
      break;
    }
    
    fEvTimeWindow=current_window;
    
    if (single_event.input==1){//BKG1
      TGEMC_Flux_pim->GetEntry(single_event.ev_num);
      TGEMC_EC_pim->GetEntry(single_event.ev_num);
      
      for (int j = 0; j<fFluxHit_id[0]->size(); j++){
	
	MfFluxHit_id.push_back(fFluxHit_id[0]->at(j));
	MfFluxHit_Avg_x.push_back(fFluxHit_Avg_x[0]->at(j));
	MfFluxHit_Avg_y.push_back(fFluxHit_Avg_y[0]->at(j));
	MfFluxHit_Px.push_back(fFluxHit_Px[0]->at(j));
	MfFluxHit_Py.push_back(fFluxHit_Py[0]->at(j));
	MfFluxHit_Pz.push_back(fFluxHit_Pz[0]->at(j));
	
      }
      for (int j = 0; j<fECHit_id[0]->size(); j++){
	MfECHit_id.push_back(fECHit_id[0]->at(j));
	MfECHit_totEdep.push_back(fECHit_totEdep[0]->at(j));
	MfECHit_Avg_z.push_back(fECHit_Avg_z[0]->at(j));
      }          
    }
    if (single_event.input==2){//BKG2
      TGEMC_Flux_pi0->GetEntry(single_event.ev_num);
      TGEMC_EC_pi0->GetEntry(single_event.ev_num);
      for (int j = 0; j<fFluxHit_id[1]->size(); j++){
	MfFluxHit_id.push_back(fFluxHit_id[1]->at(j));
	MfFluxHit_Avg_x.push_back(fFluxHit_Avg_x[1]->at(j));
	MfFluxHit_Avg_y.push_back(fFluxHit_Avg_y[1]->at(j));
	MfFluxHit_Px.push_back(fFluxHit_Px[1]->at(j));
	MfFluxHit_Py.push_back(fFluxHit_Py[1]->at(j));
	MfFluxHit_Pz.push_back(fFluxHit_Pz[1]->at(j));
      }
      for (int j = 0; j<fECHit_id[1]->size(); j++){
	MfECHit_id.push_back(fECHit_id[1]->at(j));
	MfECHit_totEdep.push_back(fECHit_totEdep[1]->at(j));
	MfECHit_Avg_z.push_back(fECHit_Avg_z[1]->at(j));
	
      }                     
    }
    if (single_event.input==3){//BKG3
      TGEMC_Flux_pip->GetEntry(single_event.ev_num);
      TGEMC_EC_pip->GetEntry(single_event.ev_num);
      
      for (int j = 0; j<fFluxHit_id[2]->size(); j++){
	MfFluxHit_id.push_back(fFluxHit_id[2]->at(j));
	MfFluxHit_Avg_x.push_back(fFluxHit_Avg_x[2]->at(j));
	MfFluxHit_Avg_y.push_back(fFluxHit_Avg_y[2]->at(j)); 
	MfFluxHit_Px.push_back(fFluxHit_Px[2]->at(j));
	MfFluxHit_Py.push_back(fFluxHit_Py[2]->at(j));
	MfFluxHit_Pz.push_back(fFluxHit_Pz[2]->at(j));
      }
      for (int j = 0; j<fECHit_id[2]->size(); j++){
	MfECHit_id.push_back(fECHit_id[2]->at(j));
	MfECHit_totEdep.push_back(fECHit_totEdep[2]->at(j));
	MfECHit_Avg_z.push_back(fECHit_Avg_z[2]->at(j));
      }            
    }
    if (single_event.input==4){//e-beam events
      ebeam_event = ebeam_event_list[single_event.ev_num];
      for (int j = 0; j<ebeam_event.fNGenDetHit; j++){
	MfFluxHit_id.push_back(dethit.MfFluxHit_id);
	MfFluxHit_Avg_x.push_back(dethit.MfFluxHit_Avg_x);
	MfFluxHit_Avg_y.push_back(dethit.MfFluxHit_Avg_y);
	MfFluxHit_Px.push_back(dethit.MfFluxHit_Px);
	MfFluxHit_Py.push_back(dethit.MfFluxHit_Py);
	MfFluxHit_Pz.push_back(dethit.MfFluxHit_Pz);
      }
      for (int j = 0; j<ebeam_event.fNCalDetSum; j++){
	MfECHit_id.push_back(detsum.MfECHit_id);
	MfECHit_totEdep.push_back(detsum.MfECHit_totEdep);
	MfECHit_Avg_z.push_back(detsum.MfECHit_Avg_z);
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
  
  fTree = new TTree("T", "Geant4 GEMC Simulation, Merged Tree");
  // flux
  fTree->Branch("FluxHit_id",&MfFluxHit_id,"id/I");
  fTree->Branch("avg_x",&MfFluxHit_Avg_x,"avg_x/D");
  fTree->Branch("avg_y",&MfFluxHit_Avg_y,"avg_y/D");
  fTree->Branch("px",&MfFluxHit_Px,"px/D");
  fTree->Branch("py",&MfFluxHit_Py,"py/D");
  fTree->Branch("pz",&MfFluxHit_Pz,"pz/D");
  
  //EC
  fTree->Branch("totEdep",&MfECHit_totEdep,"totEdep/D");
  fTree->Branch("ECHit_id",&MfECHit_id,"id/I");
  fTree->Branch("avg_z",&MfECHit_Avg_z,"id/D");
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
  MfFluxHit_id.clear();
  MfECHit_id.clear();
  Mvar8.clear();
  MfFluxHit_Avg_x.clear();
  MfFluxHit_Avg_y.clear();
  MfFluxHit_Px.clear();
  MfFluxHit_Py.clear();
  MfFluxHit_Pz.clear();
  MfECHit_totEdep.clear();
  MfECHit_Avg_z.clear();
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
