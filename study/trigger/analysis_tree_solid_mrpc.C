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

vector<int> *solid_mrpc_id=0,*solid_mrpc_hitn=0;
vector<int> *solid_mrpc_pid=0,*solid_mrpc_mpid=0,*solid_mrpc_tid=0,*solid_mrpc_mtid=0,*solid_mrpc_otid=0;
vector<double> *solid_mrpc_trackE=0,*solid_mrpc_totEdep=0,*solid_mrpc_avg_x=0,*solid_mrpc_avg_y=0,*solid_mrpc_avg_z=0,*solid_mrpc_avg_lx=0,*solid_mrpc_avg_ly=0,*solid_mrpc_avg_lz=0,*solid_mrpc_px=0,*solid_mrpc_py=0,*solid_mrpc_pz=0,*solid_mrpc_vx=0,*solid_mrpc_vy=0,*solid_mrpc_vz=0,*solid_mrpc_mvx=0,*solid_mrpc_mvy=0,*solid_mrpc_mvz=0,*solid_mrpc_avg_t=0;

void setup_tree_solid_mrpc(TTree *tree_solid_mrpc)
{  
tree_solid_mrpc->SetBranchAddress("hitn",&solid_mrpc_hitn);
tree_solid_mrpc->SetBranchAddress("id",&solid_mrpc_id);
tree_solid_mrpc->SetBranchAddress("pid",&solid_mrpc_pid);
tree_solid_mrpc->SetBranchAddress("mpid",&solid_mrpc_mpid);
tree_solid_mrpc->SetBranchAddress("tid",&solid_mrpc_tid);
tree_solid_mrpc->SetBranchAddress("mtid",&solid_mrpc_mtid);
tree_solid_mrpc->SetBranchAddress("otid",&solid_mrpc_otid);
tree_solid_mrpc->SetBranchAddress("trackE",&solid_mrpc_trackE);
tree_solid_mrpc->SetBranchAddress("totEdep",&solid_mrpc_totEdep);
tree_solid_mrpc->SetBranchAddress("avg_x",&solid_mrpc_avg_x);
tree_solid_mrpc->SetBranchAddress("avg_y",&solid_mrpc_avg_y);
tree_solid_mrpc->SetBranchAddress("avg_z",&solid_mrpc_avg_z);
tree_solid_mrpc->SetBranchAddress("avg_lx",&solid_mrpc_avg_lx);
tree_solid_mrpc->SetBranchAddress("avg_ly",&solid_mrpc_avg_ly);
tree_solid_mrpc->SetBranchAddress("avg_lz",&solid_mrpc_avg_lz);
tree_solid_mrpc->SetBranchAddress("px",&solid_mrpc_px);
tree_solid_mrpc->SetBranchAddress("py",&solid_mrpc_py);
tree_solid_mrpc->SetBranchAddress("pz",&solid_mrpc_pz);
tree_solid_mrpc->SetBranchAddress("vx",&solid_mrpc_vx);
tree_solid_mrpc->SetBranchAddress("vy",&solid_mrpc_vy);
tree_solid_mrpc->SetBranchAddress("vz",&solid_mrpc_vz);
tree_solid_mrpc->SetBranchAddress("mvx",&solid_mrpc_mvx);
tree_solid_mrpc->SetBranchAddress("mvy",&solid_mrpc_mvy);
tree_solid_mrpc->SetBranchAddress("mvz",&solid_mrpc_mvz);
tree_solid_mrpc->SetBranchAddress("avg_t",&solid_mrpc_avg_t);

return ;

}

Bool_t process_trigger_mrpc(TTree *tree_solid_mrpc,int trigger_mrpc_FA[30][2][4],double nlayer_FA_threshhold = 5){
  //totEdep threshhold value is in MeV
  //FA has 60x4 segementation including 30 sectors,2 strips and 4 blocks
  //trigger_mrpc_FA return 1 as triggered, 0 as untriggered for all segmentation
  
  //assume
//   1. at least a single particle will have energy deposition > 16eV for ionization in one layer of Freon gas will fire this layer	
// 2. the mrpc fires when the number of layers fires is at least 5
  
  Double_t counter_FA[30][2][4][10] = {0};
  Int_t ntrig_FA =0;
  
    for (Int_t j=0;j<solid_mrpc_hitn->size();j++) {
//       cout << "solid_mrpc " << " !!! " << solid_mrpc_hitn->at(j) << " " << solid_mrpc_id->at(j) << " " << solid_mrpc_pid->at(j) << " " << solid_mrpc_mpid->at(j) << " " << solid_mrpc_tid->at(j) << " " << solid_mrpc_mtid->at(j) << " " << solid_mrpc_trackE->at(j) << " " << solid_mrpc_totEdep->at(j) << " " << solid_mrpc_avg_x->at(j) << " " << solid_mrpc_avg_y->at(j) << " " << solid_mrpc_avg_z->at(j) << " " << solid_mrpc_avg_lx->at(j) << " " << solid_mrpc_avg_ly->at(j) << " " << solid_mrpc_avg_lz->at(j) << " " << solid_mrpc_px->at(j) << " " << solid_mrpc_py->at(j) << " " << solid_mrpc_pz->at(j) << " " << solid_mrpc_vx->at(j) << " " << solid_mrpc_vy->at(j) << " " << solid_mrpc_vz->at(j) << " " << solid_mrpc_mvx->at(j) << " " << solid_mrpc_mvy->at(j) << " " << solid_mrpc_mvz->at(j) << " " << solid_mrpc_avg_t->at(j) << endl;  

      double phi=atan2(solid_mrpc_avg_y->at(j),solid_mrpc_avg_x->at(j))*DEG; // range (-180,180)
      if (phi<0) phi=phi+360;  //range (0,360)

//       int sector=int(phi/12.)+1;
      int sector_strip_temp=0;
      if (phi>=90) sector_strip_temp=int((phi-90)/6+1);
      else sector_strip_temp=int((phi+360-90)/6+1);          
      
      if (sector_strip_temp<1 || sector_strip_temp >60){
	count << "mrpc sector_strip_temp problem " << " phi=" << phi << " sector_strip_temp=" << sector_strip_temp << endl;
	return false;
      }         
      
      int sector=sector_strip_temp/2+1;
      int strip=sector_strip_temp%2+1;
     
      if (sector<1 || sector >30){
	count << "mrpc sector problem " << " phi=" << phi << " sector=" << sector << endl;
	return false;
      }      
      if (strip !=1 || strip !=2){
	count << "mrpc strip problem " << " phi=" << phi << " strip=" << strip << endl;
	return false;	
      }
      
      double r=sqrt(solid_mrpc_avg_y->at(j)*solid_mrpc_avg_y->at(j)+solid_mrpc_avg_x->at(j)*solid_mrpc_avg_x->at(j))/10.; // in cm
                  
      int detector_ID=solid_mrpc_id->at(j)/1000000;
      int subdetector_ID=(solid_mrpc_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_mrpc_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_mrpc_id->at(j)%10000;
      
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_mrpc_totEdep->at(j) << endl;       
      
	if (component_ID<1 || component_ID>10) {
	  count << "mrpc layer problem " << " id=" << solid_mrpc_id->at(j) << " layer=" << component_ID << endl;
	  return false;
	}
      
      //in gas
      if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 0){
	int block=0;
	if (96<=r && r<105) block=1;
	else if (105<=r && r<125) block=2;
	else if (125<=r && r<160) block=3;
	else if (160<=r && r<210) block=4;	
	else {
	  count << "mrpc block problem " << " r=" << r << " block=" << block << endl;
	  return false;
	}      	  
	
	//assume energy deposition > 16eV for ionization in one layer of Freon will fire this layer	
	if (solid_mrpc_totEdep->at(j)>16e-6){
	  counter_FA[sector-1][strip-1][block-1][component_ID-1]++;
	}
      }
      
      //in glass
//       if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 2){
//       }

    }    

  for(Int_t i = 0; i < 30; i++){
  for(Int_t k = 0; k < 2; k++){    
  for(Int_t l = 0; l < 4; l++){ 
	int counter_sum=0;
	for(Int_t m = 0; m < 10; m++){	
	  if(counter_FA[i][k][l][m] > 0) counter_sum++;	
	}
	
	//assume mrpc fires when number of layers fires is at least nlayer_FA_threshhold 
	if (counter_sum>=nlayer_FA_threshhold) {trigger_mrpc_FA[i][k][l]=1; ntrig_FA++;}
	else {trigger_mrpc_FA[i][k][l]=0;}
  }
  }
  }

    if(ntrig_FA>0) return true;
    else return false;
}

double process_tree_solid_mrpc(TTree *tree_solid_mrpc)
{
  double totEdep=0;
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_mrpc_hitn->size();j++) {
//       cout << "solid_mrpc " << " !!! " << solid_mrpc_hitn->at(j) << " " << solid_mrpc_id->at(j) << " " << solid_mrpc_pid->at(j) << " " << solid_mrpc_mpid->at(j) << " " << solid_mrpc_tid->at(j) << " " << solid_mrpc_mtid->at(j) << " " << solid_mrpc_trackE->at(j) << " " << solid_mrpc_totEdep->at(j) << " " << solid_mrpc_avg_x->at(j) << " " << solid_mrpc_avg_y->at(j) << " " << solid_mrpc_avg_z->at(j) << " " << solid_mrpc_avg_lx->at(j) << " " << solid_mrpc_avg_ly->at(j) << " " << solid_mrpc_avg_lz->at(j) << " " << solid_mrpc_px->at(j) << " " << solid_mrpc_py->at(j) << " " << solid_mrpc_pz->at(j) << " " << solid_mrpc_vx->at(j) << " " << solid_mrpc_vy->at(j) << " " << solid_mrpc_vz->at(j) << " " << solid_mrpc_mvx->at(j) << " " << solid_mrpc_mvy->at(j) << " " << solid_mrpc_mvz->at(j) << " " << solid_mrpc_avg_t->at(j) << endl;  

      int detector_ID=solid_mrpc_id->at(j)/1000000;
      int subdetector_ID=(solid_mrpc_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_mrpc_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_mrpc_id->at(j)%10000;
      
    cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_mrpc_totEdep->at(j) << endl; 
           
      if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 0) totEdep +=solid_mrpc_totEdep->at(j);     
         
    }    

return totEdep;

}

