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

vector<int> *solid_lgc_hitn=0;
vector<int> *solid_lgc_sector=0,*solid_lgc_pmt=0,*solid_lgc_pixel=0,*solid_lgc_nphe=0;
vector<double> *solid_lgc_avg_t=0;

void setup_tree_solid_lgc(TTree *tree_solid_lgc)
{  
tree_solid_lgc->SetBranchAddress("sector",&solid_lgc_sector);
tree_solid_lgc->SetBranchAddress("pmt",&solid_lgc_pmt);
tree_solid_lgc->SetBranchAddress("pixel",&solid_lgc_pixel);
tree_solid_lgc->SetBranchAddress("nphe",&solid_lgc_nphe);
tree_solid_lgc->SetBranchAddress("avg_t",&solid_lgc_avg_t);

return;
}

double process_tree_solid_lgc(TTree *tree_solid_lgc)
{
  double totEdep=0;
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_lgc_hitn->size();j++) {
//       cout << "solid_lgc " << " !!! " << solid_lgc_hitn->at(j) << " " << solid_lgc_id->at(j) << " " << solid_lgc_pid->at(j) << " " << solid_lgc_mpid->at(j) << " " << solid_lgc_tid->at(j) << " " << solid_lgc_mtid->at(j) << " " << solid_lgc_trackE->at(j) << " " << solid_lgc_totEdep->at(j) << " " << solid_lgc_avg_x->at(j) << " " << solid_lgc_avg_y->at(j) << " " << solid_lgc_avg_z->at(j) << " " << solid_lgc_avg_lx->at(j) << " " << solid_lgc_avg_ly->at(j) << " " << solid_lgc_avg_lz->at(j) << " " << solid_lgc_px->at(j) << " " << solid_lgc_py->at(j) << " " << solid_lgc_pz->at(j) << " " << solid_lgc_vx->at(j) << " " << solid_lgc_vy->at(j) << " " << solid_lgc_vz->at(j) << " " << solid_lgc_mvx->at(j) << " " << solid_lgc_mvy->at(j) << " " << solid_lgc_mvz->at(j) << " " << solid_lgc_avg_t->at(j) << endl;  

//       int detector_ID=solid_lgc_id->at(j)/1000000;
//       int subdetector_ID=(solid_lgc_id->at(j)%1000000)/100000;
//       int subsubdetector_ID=((solid_lgc_id->at(j)%1000000)%100000)/10000;
//       int component_ID=solid_lgc_id->at(j)%10000;
      
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_lgc_totEdep->at(j) << endl; 
           
//       if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 0) totEdep +=solid_lgc_totEdep->at(j);     
      
//       if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) totEdep +=solid_lgc_trackE->at(j);           
    }
    

return totEdep;

}

