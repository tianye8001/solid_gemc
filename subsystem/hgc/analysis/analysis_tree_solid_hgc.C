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
#include <TMath.h>

using namespace std;

vector<int> *solid_hgc_id=0,*solid_hgc_hitn=0;
vector<int> *solid_hgc_pid=0,*solid_hgc_mpid=0,*solid_hgc_tid=0,*solid_hgc_mtid=0,*solid_hgc_otid=0;
vector<double> *solid_hgc_trackE=0,*solid_hgc_totEdep=0,*solid_hgc_avg_x=0,*solid_hgc_avg_y=0,*solid_hgc_avg_z=0,*solid_hgc_avg_lx=0,*solid_hgc_avg_ly=0,*solid_hgc_avg_lz=0,*solid_hgc_px=0,*solid_hgc_py=0,*solid_hgc_pz=0,*solid_hgc_vx=0,*solid_hgc_vy=0,*solid_hgc_vz=0,*solid_hgc_mvx=0,*solid_hgc_mvy=0,*solid_hgc_mvz=0,*solid_hgc_avg_t=0;

void setup_tree_solid_hgc(TTree *tree_solid_hgc)
{  
tree_solid_hgc->SetBranchAddress("hitn",&solid_hgc_hitn);
tree_solid_hgc->SetBranchAddress("id",&solid_hgc_id);
tree_solid_hgc->SetBranchAddress("pid",&solid_hgc_pid);
tree_solid_hgc->SetBranchAddress("mpid",&solid_hgc_mpid);
tree_solid_hgc->SetBranchAddress("tid",&solid_hgc_tid);
tree_solid_hgc->SetBranchAddress("mtid",&solid_hgc_mtid);
tree_solid_hgc->SetBranchAddress("otid",&solid_hgc_otid);
tree_solid_hgc->SetBranchAddress("trackE",&solid_hgc_trackE);
tree_solid_hgc->SetBranchAddress("totEdep",&solid_hgc_totEdep);
tree_solid_hgc->SetBranchAddress("avg_x",&solid_hgc_avg_x);
tree_solid_hgc->SetBranchAddress("avg_y",&solid_hgc_avg_y);
tree_solid_hgc->SetBranchAddress("avg_z",&solid_hgc_avg_z);
tree_solid_hgc->SetBranchAddress("avg_lx",&solid_hgc_avg_lx);
tree_solid_hgc->SetBranchAddress("avg_ly",&solid_hgc_avg_ly);
tree_solid_hgc->SetBranchAddress("avg_lz",&solid_hgc_avg_lz);
tree_solid_hgc->SetBranchAddress("px",&solid_hgc_px);
tree_solid_hgc->SetBranchAddress("py",&solid_hgc_py);
tree_solid_hgc->SetBranchAddress("pz",&solid_hgc_pz);
tree_solid_hgc->SetBranchAddress("vx",&solid_hgc_vx);
tree_solid_hgc->SetBranchAddress("vy",&solid_hgc_vy);
tree_solid_hgc->SetBranchAddress("vz",&solid_hgc_vz);
tree_solid_hgc->SetBranchAddress("mvx",&solid_hgc_mvx);
tree_solid_hgc->SetBranchAddress("mvy",&solid_hgc_mvy);
tree_solid_hgc->SetBranchAddress("mvz",&solid_hgc_mvz);
tree_solid_hgc->SetBranchAddress("avg_t",&solid_hgc_avg_t);

return;
}

// double process_tree_solid_hgc(TTree *tree_solid_hgc,TH2F *hhitxy_hgc)
double process_tree_solid_hgc(TTree *tree_solid_hgc)
{
//   TH2F *hhitxy_hgc=new TH2F("hhitxy_hgc","x;y;",32,-102,102,32,-102,102);
  
  double count_photon=0;
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_hgc_hitn->size();j++) {
//       cout << "solid_hgc " << " !!! " << solid_hgc_hitn->at(j) << " " << solid_hgc_id->at(j) << " " << solid_hgc_pid->at(j) << " " << solid_hgc_mpid->at(j) << " " << solid_hgc_tid->at(j) << " " << solid_hgc_mtid->at(j) << " " << solid_hgc_trackE->at(j) << " " << solid_hgc_totEdep->at(j) << " " << solid_hgc_avg_x->at(j) << " " << solid_hgc_avg_y->at(j) << " " << solid_hgc_avg_z->at(j) << " " << solid_hgc_avg_lx->at(j) << " " << solid_hgc_avg_ly->at(j) << " " << solid_hgc_avg_lz->at(j) << " " << solid_hgc_px->at(j) << " " << solid_hgc_py->at(j) << " " << solid_hgc_pz->at(j) << " " << solid_hgc_vx->at(j) << " " << solid_hgc_vy->at(j) << " " << solid_hgc_vz->at(j) << " " << solid_hgc_mvx->at(j) << " " << solid_hgc_mvy->at(j) << " " << solid_hgc_mvz->at(j) << " " << solid_hgc_avg_t->at(j) << endl;  

      int detector_ID=solid_hgc_id->at(j)/1000000;
      int subdetector_ID=(solid_hgc_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_hgc_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_hgc_id->at(j)%10000;
      
    cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_hgc_totEdep->at(j) << endl; 
           
      if (detector_ID==2 && subdetector_ID == 2 && subsubdetector_ID == 0) {
// 	if (pid==0) count_photon +=1;
      }     
      
//       if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) totEdep +=solid_hgc_trackE->at(j);           
    }
    

// return totEdep;

}

