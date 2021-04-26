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

vector<int> *solid_ec_id=0,*solid_ec_hitn=0, *solid_ec_id_ps=0,*solid_ec_hitn_ps=0;
vector<int> *solid_ec_pid=0,*solid_ec_mpid=0,*solid_ec_tid=0,*solid_ec_mtid=0,*solid_ec_otid=0;
vector<double> *solid_ec_trackE=0,*solid_ec_totEdep=0,*solid_ec_totEdepB=0, *solid_ec_totEend=0,*solid_ec_avg_x=0,*solid_ec_avg_y=0,*solid_ec_avg_z=0,*solid_ec_avg_lx=0,*solid_ec_avg_ly=0,*solid_ec_avg_lz=0,*solid_ec_px=0,*solid_ec_py=0,*solid_ec_pz=0,*solid_ec_vx=0,*solid_ec_vy=0,*solid_ec_vz=0,*solid_ec_mvx=0,*solid_ec_mvy=0,*solid_ec_mvz=0,*solid_ec_avg_t=0,*solid_ec_totEdep_ps=0,*solid_ec_totEdepB_ps=0, *solid_ec_totEend_ps=0,*solid_ec_pz_ps=0,*solid_ec_avg_z_ps=0;
void setup_tree_solid_ec(TTree *tree_solid_ec, TTree *tree_solid_ec_ps)
{  

tree_solid_ec->SetBranchAddress("hitn",&solid_ec_hitn);
tree_solid_ec->SetBranchAddress("id",&solid_ec_id);
tree_solid_ec->SetBranchAddress("pid",&solid_ec_pid);
tree_solid_ec->SetBranchAddress("mpid",&solid_ec_mpid);
tree_solid_ec->SetBranchAddress("tid",&solid_ec_tid);
tree_solid_ec->SetBranchAddress("mtid",&solid_ec_mtid);
tree_solid_ec->SetBranchAddress("otid",&solid_ec_otid);
tree_solid_ec->SetBranchAddress("trackE",&solid_ec_trackE);
tree_solid_ec->SetBranchAddress("totEdep",&solid_ec_totEdep);
tree_solid_ec->SetBranchAddress("totEdepB",&solid_ec_totEdepB);
tree_solid_ec->SetBranchAddress("totEend",&solid_ec_totEend);
tree_solid_ec->SetBranchAddress("avg_x",&solid_ec_avg_x);
tree_solid_ec->SetBranchAddress("avg_y",&solid_ec_avg_y);
tree_solid_ec->SetBranchAddress("avg_z",&solid_ec_avg_z);
tree_solid_ec->SetBranchAddress("avg_lx",&solid_ec_avg_lx);
tree_solid_ec->SetBranchAddress("avg_ly",&solid_ec_avg_ly);
tree_solid_ec->SetBranchAddress("avg_lz",&solid_ec_avg_lz);
tree_solid_ec->SetBranchAddress("px",&solid_ec_px);
tree_solid_ec->SetBranchAddress("py",&solid_ec_py);
tree_solid_ec->SetBranchAddress("pz",&solid_ec_pz);
tree_solid_ec->SetBranchAddress("vx",&solid_ec_vx);
tree_solid_ec->SetBranchAddress("vy",&solid_ec_vy);
tree_solid_ec->SetBranchAddress("vz",&solid_ec_vz);
tree_solid_ec->SetBranchAddress("mvx",&solid_ec_mvx);
tree_solid_ec->SetBranchAddress("mvy",&solid_ec_mvy);
tree_solid_ec->SetBranchAddress("mvz",&solid_ec_mvz);
tree_solid_ec->SetBranchAddress("avg_t",&solid_ec_avg_t); 

tree_solid_ec_ps->SetBranchAddress("hitn",&solid_ec_hitn_ps);
tree_solid_ec_ps->SetBranchAddress("id",&solid_ec_id_ps);
tree_solid_ec_ps->SetBranchAddress("totEdep",&solid_ec_totEdep_ps);
tree_solid_ec_ps->SetBranchAddress("totEdepB",&solid_ec_totEdepB_ps);
tree_solid_ec_ps->SetBranchAddress("totEend",&solid_ec_totEend_ps);
tree_solid_ec_ps->SetBranchAddress("avg_z",&solid_ec_avg_z_ps);
tree_solid_ec_ps->SetBranchAddress("pz",&solid_ec_pz_ps);
return;
}

double  process_tree_solid_ec(TTree *tree_solid_ec,double &totEdep, double &Edep_module1, double &Edep_module2, double &Edep_module3, double &EdepB_module1, double &EdepB_module2, double &EdepB_module3, double &EdepEnd_module1, double &EdepEnd_module2, double &EdepEnd_module3)
{
 int component_ID=0;
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {

      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      component_ID=solid_ec_id->at(j)%10;
      int layer_ID=(((solid_ec_id->at(j)%1000000)%100000)%10000)/10;      
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 0) {  
       if(solid_ec_avg_z->at(j)>2000 ){
        totEdep +=solid_ec_totEdep->at(j);
          
       if(component_ID==1){
        Edep_module1 +=solid_ec_totEdep->at(j);
        EdepB_module1 +=solid_ec_totEdepB->at(j);
        EdepEnd_module1 +=solid_ec_totEend->at(j);
      }     
       if(component_ID==2){
        Edep_module2 +=solid_ec_totEdep->at(j);
        EdepB_module2 +=solid_ec_totEdepB->at(j);
        EdepEnd_module2 +=solid_ec_totEend->at(j);
      }     
       if(component_ID==3){
        Edep_module3 +=solid_ec_totEdep->at(j);
        EdepB_module3 +=solid_ec_totEdepB->at(j);
        EdepEnd_module3 +=solid_ec_totEend->at(j);
      }     
     } 
    }
   }
    return 0;
}
double  process_tree_solid_ec_lead(TTree *tree_solid_ec, double &totEdep_lead,double &Edep_lead_module1,double &Edep_lead_module2, double &Edep_lead_module3)
{
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
      
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
           
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 3) {  
       if(solid_ec_avg_z->at(j)>2000){
	totEdep_lead +=solid_ec_totEdep->at(j);
        if(component_ID==1){
         Edep_lead_module1 +=solid_ec_totEdep->at(j); 
         }
        if(component_ID==2){
         Edep_lead_module2 +=solid_ec_totEdep->at(j); 
         }
        if(component_ID==3){
         Edep_lead_module3 +=solid_ec_totEdep->at(j); 
         }
        }    
      }               
    }
    
  return 0;
}

double  process_tree_solid_ec_preshower(TTree *tree_solid_ec_ps, double &totEdep_preshower, double &Edep_pre_module1, double &Edep_pre_module2, double &Edep_pre_module3, double &EdepB_pre_module1, double &EdepB_pre_module2, double &EdepB_pre_module3, double &EdepEnd_pre_module1, double &EdepEnd_pre_module2, double &EdepEnd_pre_module3)
{
    for (Int_t j=0;j<solid_ec_hitn_ps->size();j++) {
      
      int detector_ID=solid_ec_id_ps->at(j)/1000000;
      int subdetector_ID=(solid_ec_id_ps->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id_ps->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id_ps->at(j)%10000;
           
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1 && solid_ec_pz_ps->at(j)>0) {  
       if(solid_ec_avg_z_ps->at(j)>2000){
 	totEdep_preshower +=solid_ec_totEdep_ps->at(j);
        if(component_ID==1){
        Edep_pre_module1 +=solid_ec_totEdep_ps->at(j); 
        EdepB_pre_module1 +=solid_ec_totEdepB_ps->at(j); 
        EdepEnd_pre_module1 +=solid_ec_totEend_ps->at(j); 
        }    
        if(component_ID==2){
        Edep_pre_module2 +=solid_ec_totEdep_ps->at(j); 
        EdepB_pre_module2 +=solid_ec_totEdepB_ps->at(j); 
        EdepEnd_pre_module2 +=solid_ec_totEend_ps->at(j); 
        }    
        if(component_ID==3){
        Edep_pre_module3 +=solid_ec_totEdep_ps->at(j); 
        EdepB_pre_module3 +=solid_ec_totEdepB_ps->at(j); 
        EdepEnd_pre_module3 +=solid_ec_totEend_ps->at(j); 
        }    
      }               
    }
   } 
  return 0;
}

double  process_tree_solid_ec_Al(TTree *tree_solid_ec, double &totEdep_Al, double &Edep_Al_module1, double &Edep_Al_module2, double &Edep_Al_module3)
{
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
      
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
           
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 2) {  
       if(solid_ec_avg_z->at(j)>2000){
	totEdep_Al +=solid_ec_totEdep->at(j);
        if(component_ID==1){
         Edep_Al_module1 +=solid_ec_totEdep->at(j);        
        }    
        if(component_ID==2){
         Edep_Al_module2 +=solid_ec_totEdep->at(j);        
        }    
        if(component_ID==3){
         Edep_Al_module3 +=solid_ec_totEdep->at(j);        
        }    
      }               
    }
  }  
  return 0;
}

double  process_tree_solid_ec_Al2(TTree *tree_solid_ec,double &totEdep_Al2,double &Edep_Al2_module1,double &Edep_Al2_module2, double &Edep_Al2_module3)
{
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {

      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
           
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 7 && solid_ec_pz->at(j)>0) {
       if (solid_ec_avg_z->at(j)>2000 ){

        totEdep_Al2 +=solid_ec_totEdep->at(j);
        if(component_ID==1){
        Edep_Al2_module1 +=solid_ec_totEdep->at(j); 
        }
        if(component_ID==2){
        Edep_Al2_module2 +=solid_ec_totEdep->at(j); 
        }
        if(component_ID==3){
        Edep_Al2_module3 +=solid_ec_totEdep->at(j); 
        }
      }
    }
  }  
  return 0;
}


double  process_tree_solid_ec_Tylar1(TTree *tree_solid_ec,double &totEdep_Tylar1,double &Edep_Tylar1_module1,double &Edep_Tylar1_module2, double &Edep_Tylar1_module3)
{
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
      
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
           
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 4) {  
       if(solid_ec_avg_z->at(j)>2000){	
        totEdep_Tylar1 +=solid_ec_totEdep->at(j);
        if(component_ID==1){
        Edep_Tylar1_module1 +=solid_ec_totEdep->at(j); 
        }    
        if(component_ID==2){
        Edep_Tylar1_module2 +=solid_ec_totEdep->at(j); 
        }    
        if(component_ID==3){
        Edep_Tylar1_module3 +=solid_ec_totEdep->at(j); 
        }    
      }               
    }
   } 
  return 0;
}
double  process_tree_solid_ec_Tylar2(TTree *tree_solid_ec,double &totEdep_Tylar2,double &Edep_Tylar2_module1,double &Edep_Tylar2_module2,double &Edep_Tylar2_module3)
{
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
      
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
      
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 5) {  
       if(solid_ec_avg_z->at(j)>2000){
	totEdep_Tylar2 +=solid_ec_totEdep->at(j);
        if(component_ID==1){
         Edep_Tylar2_module1 +=solid_ec_totEdep->at(j);
        }    
        if(component_ID==2){
         Edep_Tylar2_module2 +=solid_ec_totEdep->at(j);
        }    
        if(component_ID==3){
         Edep_Tylar2_module3 +=solid_ec_totEdep->at(j);
        }    
      }               
    }
  }  
  return 0;
}

double  process_tree_solid_ec_prelead(TTree *tree_solid_ec,double &totEdep_prelead,double &Edep_prelead_module1,double &Edep_prelead_module2,double &Edep_prelead_module3)
{
      for (Int_t j=0;j<solid_ec_hitn->size();j++) {
  
            int detector_ID=solid_ec_id->at(j)/1000000;
            int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
            int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
            int component_ID=solid_ec_id->at(j)%10000;

                if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 6) {
                   if(solid_ec_avg_z->at(j)>2000){
                     totEdep_prelead +=solid_ec_totEdep->at(j);
                    if(component_ID==1){
                     Edep_prelead_module1 +=solid_ec_totEdep->at(j);
                }
                    if(component_ID==2){
                     Edep_prelead_module2 +=solid_ec_totEdep->at(j);
                }
                    if(component_ID==3){
                     Edep_prelead_module3 +=solid_ec_totEdep->at(j);
                }
              }
            }
         }
     return 0;
    }
TVector2  process_tree_solid_ec_scinlead(TTree *tree_solid_ec)
{
  double totEdep_scinlead=0;
  TVector2 vec_ecalEblock_scinlead;
 double averageZ_scinlead=0.0;

  double totEdep_lead=0;
  double averageZ_lead=0.0;
  double totEdep=0;
  double averageZ=0.0;
  double totEdep_preshower=0;
  double averageZ_preshower=0.0;
  double totEdep_prelead=0;
  double averageZ_prelead=0.0;
  double totEdep_Al=0;
  double averageZ_Al=0.0;
  double totEdep_Tylar1=0;
  double totEdep_Tylar2=0;
  //double totEmodul[7]=0.0
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
      
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_ec_id->at(j)%10000;
   if(solid_ec_avg_z->at(j)>2000){
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 0) {  

	totEdep +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
           
      } if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 3) {  
	totEdep_lead +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
      } if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1){ 
       totEdep_preshower +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
      } if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 2){
       totEdep_Al +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
      }if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 4){
       totEdep_Tylar1 +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
      }if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 5){
       totEdep_Tylar2 +=solid_ec_totEdep->at(j);
        averageZ_scinlead=solid_ec_avg_z->at(j)/10;
      }if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 6){
       totEdep_prelead +=solid_ec_totEdep->at(j);
        averageZ_prelead=solid_ec_avg_z->at(j)/10;
      }

     totEdep_scinlead=totEdep+totEdep_lead+totEdep_preshower+totEdep_Al+totEdep_Tylar1+totEdep_Tylar2+totEdep_prelead;
     //cout<<"Etotal="<<totEdep_scinlead<<endl;              
    }
   }
    vec_ecalEblock_scinlead.Set(totEdep_scinlead,averageZ_scinlead);
  return vec_ecalEblock_scinlead;
}



