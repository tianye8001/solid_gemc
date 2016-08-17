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

const double DEG=180./TMath::Pi();

vector<int> *solid_spd_id=0,*solid_spd_hitn=0;
vector<int> *solid_spd_pid=0,*solid_spd_mpid=0,*solid_spd_tid=0,*solid_spd_mtid=0,*solid_spd_otid=0;
vector<double> *solid_spd_trackE=0,*solid_spd_totEdep=0,*solid_spd_avg_x=0,*solid_spd_avg_y=0,*solid_spd_avg_z=0,*solid_spd_avg_lx=0,*solid_spd_avg_ly=0,*solid_spd_avg_lz=0,*solid_spd_px=0,*solid_spd_py=0,*solid_spd_pz=0,*solid_spd_vx=0,*solid_spd_vy=0,*solid_spd_vz=0,*solid_spd_mvx=0,*solid_spd_mvy=0,*solid_spd_mvz=0,*solid_spd_avg_t=0;

void setup_tree_solid_spd(TTree *tree_solid_spd)
{  
tree_solid_spd->SetBranchAddress("hitn",&solid_spd_hitn);
tree_solid_spd->SetBranchAddress("id",&solid_spd_id);
tree_solid_spd->SetBranchAddress("pid",&solid_spd_pid);
tree_solid_spd->SetBranchAddress("mpid",&solid_spd_mpid);
tree_solid_spd->SetBranchAddress("tid",&solid_spd_tid);
tree_solid_spd->SetBranchAddress("mtid",&solid_spd_mtid);
tree_solid_spd->SetBranchAddress("otid",&solid_spd_otid);
tree_solid_spd->SetBranchAddress("trackE",&solid_spd_trackE);
tree_solid_spd->SetBranchAddress("totEdep",&solid_spd_totEdep);
tree_solid_spd->SetBranchAddress("avg_x",&solid_spd_avg_x);
tree_solid_spd->SetBranchAddress("avg_y",&solid_spd_avg_y);
tree_solid_spd->SetBranchAddress("avg_z",&solid_spd_avg_z);
tree_solid_spd->SetBranchAddress("avg_lx",&solid_spd_avg_lx);
tree_solid_spd->SetBranchAddress("avg_ly",&solid_spd_avg_ly);
tree_solid_spd->SetBranchAddress("avg_lz",&solid_spd_avg_lz);
tree_solid_spd->SetBranchAddress("px",&solid_spd_px);
tree_solid_spd->SetBranchAddress("py",&solid_spd_py);
tree_solid_spd->SetBranchAddress("pz",&solid_spd_pz);
tree_solid_spd->SetBranchAddress("vx",&solid_spd_vx);
tree_solid_spd->SetBranchAddress("vy",&solid_spd_vy);
tree_solid_spd->SetBranchAddress("vz",&solid_spd_vz);
tree_solid_spd->SetBranchAddress("mvx",&solid_spd_mvx);
tree_solid_spd->SetBranchAddress("mvy",&solid_spd_mvy);
tree_solid_spd->SetBranchAddress("mvz",&solid_spd_mvz);
tree_solid_spd->SetBranchAddress("avg_t",&solid_spd_avg_t);

return ;

}

Bool_t process_trigger_spd(TTree *tree_solid_spd,int trigger_spd_FA[30][2][4],int trigger_spd_LA[30][2],double totEdep_FA_threshhold = 0.35, double totEdep_LA_threshhold = 0.35){
  //totEdep threshhold value is in MeV
  //FASPD has 60x4 segementation including 30 sectors,2 strips and 4 blocks
  //LASPD has 60x2 segementation including 30 sectors,2 strips
  //trigger_spd_FA and trigger_spd_LA return 1 as triggered, 0 as untriggered for all segmentation
  
  Double_t totEdep_FA[30][2][4] = {0};
  Double_t totEdep_LA[30][2] = {0};
  Int_t ntrig_FA =0;
  Int_t ntrig_LA =0;  
  
    for (Int_t j=0;j<solid_spd_hitn->size();j++) {
//       cout << "solid_spd " << " !!! " << solid_spd_hitn->at(j) << " " << solid_spd_id->at(j) << " " << solid_spd_pid->at(j) << " " << solid_spd_mpid->at(j) << " " << solid_spd_tid->at(j) << " " << solid_spd_mtid->at(j) << " " << solid_spd_trackE->at(j) << " " << solid_spd_totEdep->at(j) << " " << solid_spd_avg_x->at(j) << " " << solid_spd_avg_y->at(j) << " " << solid_spd_avg_z->at(j) << " " << solid_spd_avg_lx->at(j) << " " << solid_spd_avg_ly->at(j) << " " << solid_spd_avg_lz->at(j) << " " << solid_spd_px->at(j) << " " << solid_spd_py->at(j) << " " << solid_spd_pz->at(j) << " " << solid_spd_vx->at(j) << " " << solid_spd_vy->at(j) << " " << solid_spd_vz->at(j) << " " << solid_spd_mvx->at(j) << " " << solid_spd_mvy->at(j) << " " << solid_spd_mvz->at(j) << " " << solid_spd_avg_t->at(j) << endl;  

      double phi=atan2(solid_spd_avg_y->at(j),solid_spd_avg_x->at(j))*DEG; // range (-180,180)
      if (phi<0) phi=phi+360;  //range (0,360)

//       int sector=int(phi/12.)+1;
      int sector_strip_temp=0;
      if (phi>=90) sector_strip_temp=int((phi-90)/6+1);
      else sector_strip_temp=int((phi+360-90)/6+1);          
      
      if (sector_strip_temp<1 || sector_strip_temp >60){
	count << "spd sector_strip_temp problem " << " phi=" << phi << " sector_strip_temp=" << sector_strip_temp << endl;
	return false;
      }         
      
      int sector=sector_strip_temp/2+1;
      int strip=sector_strip_temp%2+1;
     
      if (sector<1 || sector >30){
	count << "spd sector problem " << " phi=" << phi << " sector=" << sector << endl;
	return false;
      }      
      if (strip !=1 || strip !=2){
	count << "spd strip problem " << " phi=" << phi << " strip=" << strip << endl;
	return false;	
      }
      
      double r=sqrt(solid_spd_avg_y->at(j)*solid_spd_avg_y->at(j)+solid_spd_avg_x->at(j)*solid_spd_avg_x->at(j))/10.; // in cm
                  
      int detector_ID=solid_spd_id->at(j)/1000000;
      int subdetector_ID=(solid_spd_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_spd_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_spd_id->at(j)%10000;
      
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_spd_totEdep->at(j) << endl;       
      
      if (detector_ID==5 && subdetector_ID == 1 && subsubdetector_ID == 0){
	int block=0;
	if (96<=r && r<105) block=1;
	else if (105<=r && r<125) block=2;
	else if (125<=r && r<160) block=3;
	else if (160<=r && r<210) block=4;	
	else {
	  count << "spd block problem " << " r=" << r << " block=" << block << endl;
	  return false;
	}      	  
	
	totEdep_FA[sector-1][strip-1][block-1] +=solid_spd_totEdep->at(j);     	
      }
      
      if (detector_ID==5 && subdetector_ID == 2 && subsubdetector_ID == 0){
	totEdep_LA[sector-1][strip-1] +=solid_spd_totEdep->at(j);         
      }
    }
    
  for(Int_t i = 0; i < 30; i++){
  for(Int_t k = 0; k < 2; k++){    
      for(Int_t l = 0; l < 4; l++){    
	if(totEdep_FA[i][k][l] >= totEdep_FA_threshhold) {trigger_spd_FA[i][k][l]=1; ntrig_FA++;}
	else {trigger_spd_FA[i][k][l]=0;}
      }
      
      if(totEdep_LA[i][k] >= totEdep_LA_threshhold) {trigger_spd_LA[i][k]=1; ntrig_LA++;}
      else {trigger_spd_LA[i][k]=0;}
  }
  }

    if(ntrig_FA>0 || ntrig_LA>0) return true;
    else return false;
}


double process_tree_solid_spd(TTree *tree_solid_spd)
{
  double totEdep=0;
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_spd_hitn->size();j++) {
//       cout << "solid_spd " << " !!! " << solid_spd_hitn->at(j) << " " << solid_spd_id->at(j) << " " << solid_spd_pid->at(j) << " " << solid_spd_mpid->at(j) << " " << solid_spd_tid->at(j) << " " << solid_spd_mtid->at(j) << " " << solid_spd_trackE->at(j) << " " << solid_spd_totEdep->at(j) << " " << solid_spd_avg_x->at(j) << " " << solid_spd_avg_y->at(j) << " " << solid_spd_avg_z->at(j) << " " << solid_spd_avg_lx->at(j) << " " << solid_spd_avg_ly->at(j) << " " << solid_spd_avg_lz->at(j) << " " << solid_spd_px->at(j) << " " << solid_spd_py->at(j) << " " << solid_spd_pz->at(j) << " " << solid_spd_vx->at(j) << " " << solid_spd_vy->at(j) << " " << solid_spd_vz->at(j) << " " << solid_spd_mvx->at(j) << " " << solid_spd_mvy->at(j) << " " << solid_spd_mvz->at(j) << " " << solid_spd_avg_t->at(j) << endl;  

      int detector_ID=solid_spd_id->at(j)/1000000;
      int subdetector_ID=(solid_spd_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_spd_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_spd_id->at(j)%10000;
      
    cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_spd_totEdep->at(j) << endl; 
           
      if (detector_ID==5 && subdetector_ID == 1 && subsubdetector_ID == 0) totEdep +=solid_spd_totEdep->at(j);     
         
    }    

return totEdep;

}

