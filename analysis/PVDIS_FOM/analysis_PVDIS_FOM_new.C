#include <iostream> 
#include <fstream>
#include <cmath> 
#include "math.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMinuit.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TArc.h"
#include "TString.h"
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TFile.h"
#include "TMarker.h"

//#include "PVDIS_tri_eff.h"
#include "PVDIS_tri_eff_Rakitha1.h"
using namespace std;

//#define PVDIS_HYDROGEN

// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 
// const double filenum=50; //file numbers while running GEMC in order to be correct for normalization
const int loop_time=1;   //electron to be 1, pion to be many times to take advantage of statistics, pion has low efficiency on EC
const int add_norm=1; // additional normalization factor
const double runtime = 120.*86400; //LD2 120 days 11GeV
//const double runtime = 120.*86400; //LD2 120 days 6.6GeV
const double pb = 0.85;


bool Is_debug=false;
bool Is_Rad = false;
bool Require_GEM = false;

const double DEG=180./3.1415926;   //rad to degree




//binning for 6.6GeV with x only  
 /*const int Nbin=7;
 double bin[Nbin][4]={
 0.15,0.30,     0.0,14.0,
 0.30,0.35,     0.0,14.0,
 0.35,0.40,     0.0,14.0,
 0.40,0.45,     0.0,14.0,
 0.45,0.50,     0.0,14.0,
 0.50,0.55,     0.0,14.0,
 0.55,0.80,     0.0,14.0
 };      
*/

/*const int Nbin=9;
double bin[Nbin][4]={
0.20,0.30,     0.0,14.0,
0.30,0.35,     0.0,14.0,
0.35,0.40,     0.0,14.0,
0.40,0.45,     0.0,14.0,
0.45,0.50,     0.0,14.0,
0.50,0.55,     0.0,14.0,
0.55,0.60,     0.0,14.0,
0.60,0.67,     0.0,14.0,
0.67,0.80,     0.0,14.0
};*/

///binning for more1 block
#ifdef PVDIS_HYDROGEN
const int Nbin=8;
 double bin[8][4]={
 {0.0,0.365,     0.0,14.0},
 {0.365,0.395,     0.0,14.0},
 {0.395,0.445,     0.0,14.0},
 {0.445,0.495,     0.0,14.0},
 {0.495,0.545,     0.0,14.0},
 {0.545,0.595,     0.0,14.0},
 {0.595,0.665,     0.0,14.0},
 {0.665,0.8,     0.0,14.0},
 };
#else
 const int Nbin=15;
 double bin[15][4]={
 0.20,0.30,     0.0,14.0,
  0.30,0.35,     0.0,14.0,
 0.35,0.40,     0.0, 5.8,
 0.35,0.40,     5.8,14.0,
 0.40,0.45,     0.0, 6.4,
 0.40,0.45,     6.4,14.0,
 0.45,0.50,     0.0, 7.0,
 0.45,0.50,     7.0,14.0,
 0.50,0.55,     0.0, 7.6,
 0.50,0.55,     7.6,14.0,
 0.55,0.60,     0.0, 8.2,
 0.55,0.60,     8.2,14.0,
 0.60,0.67,     0.0, 8.8,
 0.60,0.67,     8.8,14.0,
 0.67,0.80,     0.0,14.0
 };
#endif

///binning for more1 block
//Q2 range by guessing
/* const int Nbin=15;
 double bin[15][4]={
 0.20,0.30,     2.5,5.5,
 0.30,0.35,     4.2,5.7,
 0.35,0.40,     4.7,5.8,
 0.35,0.40,     5.8,7.2,
 0.40,0.45,     5.0,6.4,
 0.40,0.45,     6.4,7.7,
 0.45,0.50,     5.5,7.0,
 0.45,0.50,     7.0,8.5,
 0.50,0.55,     5.8,7.6,
 0.50,0.55,     7.6,9.5,
 0.55,0.60,     6.2,8.2,
 0.55,0.60,     8.2,10.0,
 0.60,0.67,     6.5,8.8,
 0.60,0.67,     8.8,11.0,
 0.67,0.80,     9.0,12.5
 };
*/


//#####################################################################################################################################################

void analysis_PVDIS_FOM(string filename,bool Is_badroot=false){

    // gStyle->SetOptStat(11111111);
    gStyle->SetOptStat(0);
    
    //vector<string> input_gen_file;
    vector<string> input_sim_file;
    //add the files to analyze here 
    input_sim_file.push_back(filename);
    //need to add all the filenum by hand for now
    unsigned int numberOfFile = 100;//input_sim_file.size();
    
    double thatrate[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double Abeam_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double Apv_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double Q2_sum[15] = {0};
    double y_sum[15] = {0};
      
    double rout_cut_FA=270,rin_cut_FA=110,rout_cut_LA=0,rin_cut_LA=0;
    //double rmin[5] = {50,  61, 61, 110, 110};
    //double rmax[5] = {118, 140, 140, 228, 228};
    
    double rmin[5] = {0, 0, 0, 0, 0};
    double rmax[5] = {1000, 1000, 1000, 1000, 1000};

    TFile *outputfile=new TFile("output.root", "recreate");

	TH2F *hgen_ThetaP=new TH2F("gen_ThetaP","generated events;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);  
	TH2F *hgen_ThetaPhi=new TH2F("gen_ThetaPhi","generated events;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);     
	TH2F *hgen_PhiP=new TH2F("gen_PhiP","generated events;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);	
	
	TH3F *hgen_ThetaPhiP=new TH3F("gen_ThetaPhiP","gen_ThetaPhiP",50,0,50,180,-180,180,55,0,11);   
	

	TH1F *hrate_P_gen=new TH1F("rate_P_gen","rate_P_gen",110,0,11);
	TH1F *hrate_P_acc=new TH1F("rate_P_acc","rate_P_acc",110,0,11);
	TH1F *hacceptance_P=new TH1F("acceptance_P","acceptance_P",110,0,11);
	TH1F *hrate_Theta_gen=new TH1F("rate_Theta_gen","rate_Theta_gen",100,0,50);
	TH1F *hrate_Theta_acc=new TH1F("rate_Theta_acc","rate_Theta_acc",100,0,50);
	TH1F *hacceptance_Theta=new TH1F("acceptance_Theta","acceptance_Theta",100,0,50);
	TH1F *hrate_x_gen=new TH1F("rate_x_gen","rate_x_gen",100,0,1);
	TH1F *hrate_x_acc=new TH1F("rate_x_acc","rate_x_acc",100,0,1);
	TH1F *hacceptance_x=new TH1F("acceptance_x","acceptance_x",100,0,1);
	TH1F *hrate_Q2_gen=new TH1F("rate_Q2_gen","rate_Q2_gen",140,0,14);
	TH1F *hrate_Q2_acc=new TH1F("rate_Q2_acc","rate_Q2_acc",140,0,14);
	TH1F *hacceptance_Q2=new TH1F("acceptance_Q2","acceptance_Q2",140,0,14);

	TH2F *hrate_PTheta_gen=new TH2F("rate_PTheta_gen","rate_PTheta_gen",50,0,50,110,0,11);
	TH2F *hrate_PTheta_acc=new TH2F("rate_PTheta_acc","rate_PTheta_acc",50,0,50,110,0,11);
	TH2F *hacceptance_PTheta=new TH2F("acceptance_PTheta","acceptance_PTheta",50,0,50,110,0,11);
	TH2F *hrate_Q2x_gen=new TH2F("rate_Q2x_gen","rate_Q2x_gen",100,0,1,140,0,14);
	TH2F *hrate_Q2x_acc=new TH2F("rate_Q2x_acc","rate_Q2x_acc",100,0,1,140,0,14);
	TH2F *hacceptance_Q2x=new TH2F("acceptance_Q2x","acceptance_Q2x",100,0,1,140,0,14);
	
	TH2F *triEff_Q2x_gen = new TH2F("triEff_Q2x_gen","triEff_Q2x_gen",100,0,1,140,0,14);
	TH2F *triEff_Q2x_acc = new TH2F("triEff_Q2x_acc","triEff_Q2x_acc",100,0,1,140,0,14);
	triEff_Q2x_acc->GetXaxis()->SetTitle("x");
	triEff_Q2x_acc->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
	TH2F *triEff_pr_gen = new TH2F("triEff_pr_gen","triEff_pr_gen",100,0,8,100,100,300);
	TH2F *triEff_pr_acc = new TH2F("triEff_pr_acc","triEff_pr_acc",100,0,8,100,100,300);
	triEff_pr_acc->GetYaxis()->SetTitle("r [cm]");
	triEff_pr_acc->GetXaxis()->SetTitle("p [GeV]");

	TH2F *hAbeam_Q2x_gen=new TH2F("Abeam_Q2x_gen","Abeam_Q2x_gen",100,0,1,140,0,14);
	TH2F *hAbeam_Q2x_acc=new TH2F("Abeam_Q2x_acc","Abeam_Q2x_acc",100,0,1,140,0,14);
	TH2F *hAbeamErr_Q2x_gen=new TH2F("AbeamErr_Q2x_gen","AbeamErr_Q2x_gen",100,0,1,140,0,14);
	TH2F *hAbeamErr_Q2x_acc=new TH2F("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",100,0,1,140,0,14);
	TH2F *hApv_Q2x_gen=new TH2F("Apv_Q2x_gen","Apv_Q2x_gen",100,0,1,140,0,14);
	TH2F *hApv_Q2x_acc=new TH2F("Apv_Q2x_acc","Apv_Q2x_acc",100,0,1,140,0,14);
	TH2F *hApvErr_Q2x_gen=new TH2F("ApvErr_Q2x_gen","ApvErr_Q2x_gen",100,0,1,140,0,14);
	TH2F *hApvErr_Q2x_acc=new TH2F("ApvErr_Q2x_acc","ApvErr_Q2x_acc",100,0,1,140,0,14);

	TH2F *hrate_Q2x_acc_bin=new TH2F("rate_Q2x_acc_bin","rate_Q2x_acc_bin",10,0,1,7,0,15);
	TH2F *hApvErr_Q2x_acc_bin=new TH2F("ApvErr_Q2x_acc_bin","ApvErr_Q2x_acc_bin",10,0,1,7,0,15);

	TH2F *hrate_PTheta_zwzhao_gen=new TH2F("rate_PTheta_zwzhao_gen","rate_PTheta_zwzhao_gen",13,20,44,20,0,6);
	TH2F *hrate_PTheta_zwzhao_acc=new TH2F("rate_PTheta_zwzhao_acc","rate_PTheta_zwzhao_acc",13,20,44,20,0,6);
	TH2F *hrate_PTheta_seamus_gen=new TH2F("rate_PTheta_seamus_gen","rate_PTheta_seamus_gen",13,20,44,20,0,6);
	
	double thetaStart = 10;
    double thetaBinWidth = 10;
    const int NTHETABIN = 4;
    TH1D* histThetaP[NTHETABIN];
    for (int i=0; i<NTHETABIN; i++){
        double thismin = thetaStart + thetaBinWidth*i;
        double thismax = thismin + thetaBinWidth;
        histThetaP[i] = new TH1D(Form("hist_theta_p_%d_%d_deg", (int)thismin, (int)thismax), Form("hist_theta_p_%d_%d_deg", (int)thismin, (int)thismax), 100, 0, 11);
        histThetaP[i]->GetXaxis()->SetTitle("p' [GeV]");
        histThetaP[i]->GetYaxis()->SetTitle("rate [Hz/GeV]");
    }

	//-------------------------
	//   get trees in the real data file
	//-------------------------
	//open file from generator
	for (int ifile = 0; ifile < input_sim_file.size(); ifile++){
        
        
	    TFile *file=new TFile(input_sim_file[ifile].c_str(), "READ");
	    TTree *tree_header = 0;
	    vector <int> *evn=0,*evn_type=0;
            vector <double> *beamPol=0;
            vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0, *var9=0;
            tree_header = (TTree*) file->Get("userHeader");
            tree_header->SetBranchAddress("userVar001",&var1);     //1
	    tree_header->SetBranchAddress("userVar002",&var2);     //x
	    tree_header->SetBranchAddress("userVar003",&var3);     //y
	    tree_header->SetBranchAddress("userVar004",&var4);     //W
	    tree_header->SetBranchAddress("userVar005",&var5);     //Q2
	    tree_header->SetBranchAddress("userVar006",&var6);     //rate
	    tree_header->SetBranchAddress("userVar007",&var7);     //Wprate
	    tree_header->SetBranchAddress("userVar008",&var8);     //Wmrate
	    tree_header->SetBranchAddress("userVar009",&var9);     //Abeam

	    //---generated tree
	    //particle generated with certain momentum at certain vertex
	    TTree *tree_generated = (TTree*) file->Get("generated");
	    vector <int> *gen_pid=0;
	    vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	    tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID 
	    tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	    tree_generated->SetBranchAddress("py",&gen_py);
	    tree_generated->SetBranchAddress("pz",&gen_pz);
	    tree_generated->SetBranchAddress("vx",&gen_vx);    //vertex of the generated particle at target
	    tree_generated->SetBranchAddress("vy",&gen_vy);
	    tree_generated->SetBranchAddress("vz",&gen_vz);

	    //--- flux
	    //the real deal output from the GEMC simulation
	    TTree *tree_flux = (TTree*) file->Get("flux");
	    vector<int> *flux_id=0,*flux_hitn=0;
	    vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	    vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,
	    *flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	    
	    tree_flux->SetBranchAddress("hitn",&flux_hitn);     // hit number
	    tree_flux->SetBranchAddress("id",&flux_id);         //hitting detector ID
	    tree_flux->SetBranchAddress("pid",&flux_pid);       //pid
	    tree_flux->SetBranchAddress("mpid",&flux_mpid);     // mother pid
	    tree_flux->SetBranchAddress("tid",&flux_tid);       // track id
	    tree_flux->SetBranchAddress("mtid",&flux_mtid);     // mother track id
	    tree_flux->SetBranchAddress("otid",&flux_otid);     // original track id
	    tree_flux->SetBranchAddress("trackE",&flux_trackE);  // track energy of 1st step,  track here is G4 track
	    tree_flux->SetBranchAddress("totEdep",&flux_totEdep); // totEdep in all steps, track here is G4 track
	    tree_flux->SetBranchAddress("avg_x",&flux_avg_x);     //average x, weighted by energy deposition in each step
	    tree_flux->SetBranchAddress("avg_y",&flux_avg_y);     //average y
	    tree_flux->SetBranchAddress("avg_z",&flux_avg_z);     //average z
	    tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);   // local average x 
	    tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);   // local average y
	    tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);   // local average z
	    tree_flux->SetBranchAddress("px",&flux_px);          // px of 1st step
	    tree_flux->SetBranchAddress("py",&flux_py);          // py of 1st step
	    tree_flux->SetBranchAddress("pz",&flux_pz);          // pz of 1st step
	    tree_flux->SetBranchAddress("vx",&flux_vx);          // x coordinate of 1st step
	    tree_flux->SetBranchAddress("vy",&flux_vy);          // y coordinate of 1st step
	    tree_flux->SetBranchAddress("vz",&flux_vz);          // z coordinate of 1st step
	    tree_flux->SetBranchAddress("mvx",&flux_mvx);        // mother
	    tree_flux->SetBranchAddress("mvy",&flux_mvy);
	    tree_flux->SetBranchAddress("mvz",&flux_mvz);
	    tree_flux->SetBranchAddress("avg_t",&flux_avg_t);     //average time stamp


	    //TRandom3 rand;
	    //rand.SetSeed(0);
	    
	    long int N_events = (long int)tree_header->GetEntries();

    //cout << "generator has entry " <<  T->GetEntries() << endl;
    cout << "output has entry " << tree_header->GetEntries() << endl;;
	    
    // 	cout << "total number of events : " << N_events << endl;	

    

	    //----------------------------
	    //      loop trees
	    //---------------------------
	    for(int loop_id=1;loop_id<=loop_time;loop_id++){
		    cout<<"loop.....  "<<loop_id<<endl;
	    
	    if (Is_badroot) N_events=N_events-1; //for devel pass1 file with bad root entry
		    
	    for(long int i=0;i<N_events;i++){	  
   
	      
		    //T->GetEntry(i); //get entry from generator
      
		    //---
		    //---header tree
		    //---
		    tree_header->GetEntry(i);
		    tree_generated->GetEntry(i);
                    if (Is_badroot) tree_flux->GetEntry(i+1); //for devel pass1 file with bad root entry
		    else tree_flux->GetEntry(i);
            
		    double rate= 0, Abeam = 0;
		    rate = var6->at(0);
		    if (Is_Rad) rate = var7->at(0);
		    rate = rate/numberOfFile/loop_time*add_norm;
                    Abeam = var9->at(0);
                    //cout<<rate<<" "<<Abeam<<endl; 
		    double x = 0, y=0, W = 0, Q2 = 0;
	            x=var2->at(0);	
	            y=var3->at(0);
	            W=var4->at(0);		
	            Q2=var5->at(0);
		    
		    //if (fabs(W - W_gen) > 1e-4 || fabs(x - x_gen) > 1e-4 || fabs(Q2 - Q2_gen) > 1e-4) {
		    //    cout<<"may not be the same event"<<endl;
		    //    cout<<W - W_gen <<" "<<x - x_gen <<" "<<Q2 - Q2_gen<<endl;
		   // }
		    if (W<2) continue;
		    if (var6->size() != 1) cout<<var6->size()<<endl;
		    //---
		    //---generated tree
		    //---
		    

		    int n_gen=gen_pid->size();
		    //cout<<"generated : "<<n_gen<<endl;
		    int pid_gen=0;
		    double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      

		    for (int j=0;j<gen_pid->size();j++) {
    // 	            
		        pid_gen=gen_pid->at(j);
		        px_gen=gen_px->at(j);
		        py_gen=gen_py->at(j);
		        pz_gen=gen_pz->at(j);
		        vx_gen=gen_vx->at(j);
		        vy_gen=gen_vy->at(j);
		        vz_gen=gen_vz->at(j);
		        p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
		        theta_gen=acos(pz_gen/p_gen)*DEG;
		        phi_gen=atan2(py_gen,px_gen)*DEG;

                double thismass = 938.272046e-3;
		        double thismom      = sqrt(pow(px_gen/1000., 2) + pow(py_gen/1000., 2) + pow(pz_gen/1000., 2));
		        double thistheta    = atan(sqrt(pow(px_gen/1000., 2) + pow(py_gen/1000., 2))/(pz_gen/1000.));
		        double thisQ2       = 2.*11.*thismom*(1. - cos(thistheta));
		        double xBjorken     = thisQ2 / (2.*thismass*(11. - thismom));
		        double thisW        = sqrt(thismass*thismass + 2.*thismass*(11. - thismom) - thisQ2);
		        //cout<<thisQ2 - Q2<<" "<<xBjorken - x<<" "<<thisW - W<<endl;
		        //if (fabs(thisQ2 - Q2) > 1) cout<<px_gen<<" "<<py_gen<<" "<<pz_gen<<" "<<theta_gen<<endl;
		        
		    }
		    
            int binID = -1;
            for (int iangle = 0; iangle < NTHETABIN; iangle++){
                if (theta_gen < thetaStart + (iangle + 1)*thetaBinWidth && theta_gen >= thetaStart + iangle*thetaBinWidth)
                binID = iangle;
            }
            
            if (binID >=0 && binID < NTHETABIN) histThetaP[binID]->Fill(p_gen/1000., rate);

		    hgen_ThetaP->Fill(theta_gen,p_gen/1e3,rate);
		    hgen_ThetaPhi->Fill(theta_gen,phi_gen,rate);                  		
		    hgen_PhiP->Fill(phi_gen,p_gen/1e3,rate);                  				
		    hgen_ThetaPhiP->Fill(theta_gen,phi_gen,p_gen/1e3,rate);                  			
			    
		    //check on EC and other by flux
	    
		    double acc=0,eff=0;
		    bool   GEMFound[5] = {0};
		    
		    for (Int_t j=0;j<flux_hitn->size();j++) {

		      int detector_ID=flux_id->at(j)/1000000;
		      int subdetector_ID=(flux_id->at(j)%1000000)/100000;
		      int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;		  
		      int component_ID=flux_id->at(j)%10000;      

		    double hit_vr=sqrt(pow(flux_vx->at(j),2)+pow(flux_vy->at(j),2))/1e1; //mm to cm
		    double hit_vy=flux_vy->at(j)/1e1,hit_vx=flux_vx->at(j)/1e1,hit_vz=flux_vz->at(j)/1e1;           //mm to cm		  
		    double hit_r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/1e1; //mm to cm
		    double hit_y=flux_avg_y->at(j)/1e1,hit_x=flux_avg_x->at(j)/1e1,hit_z=flux_avg_z->at(j)/1e1;           //mm to cm		
		    double hit_phi=atan2(hit_y,hit_x)*DEG;       //rad to  deg
		    double hit_p=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j))/1e3;  //MeV to GeV
		      
		      int hit_id=-1;
		      if (detector_ID==1 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=0;
		      if (detector_ID==1 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=1;	  
		      if (detector_ID==1 && subdetector_ID == 3 && subsubdetector_ID == 1) hit_id=2;	  
		      if (detector_ID==1 && subdetector_ID == 4 && subsubdetector_ID == 1) hit_id=3;	  
		      if (detector_ID==1 && subdetector_ID == 5 && subsubdetector_ID == 1) hit_id=4;	  
		      if (detector_ID==1 && subdetector_ID == 6 && subsubdetector_ID == 1) hit_id=5;	        
		      if (detector_ID==2 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=6;
		      if (detector_ID==2 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=7;	              
		      if (detector_ID==5 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=8;
		      if (detector_ID==5 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=9;	                          
		      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=10;
		      if (detector_ID==3 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=11;
		      
		      if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=12;  
	     
		      if (detector_ID==6 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=13;
		      if (detector_ID==6 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=14;  
		      
		      //check hit on EC and find sec_ec
		      if(hit_id==10){   //FAEC 
     		     if (hit_r<rin_cut_FA || hit_r>rout_cut_FA) continue; //trigger cut on R

		        int sec_ec=0;
		        int sec_shift=1.7;  // shift to match electron turning in field
		        if (hit_phi>=90+sec_shift) sec_ec=int((hit_phi-90-sec_shift)/12+1);
		        else sec_ec=int((hit_phi+360-90-sec_shift)/12+1);
		        
		        if(TMath::Nint(flux_tid->at(j))==1) {
		            acc=1;
		            eff = GetElectronTriggerEffi(GetRadiusIndex(hit_r), GetMomentumIndex(hit_p));
		            //cout<<i<<" "<<p_gen/1000.<<" "<<hit_p<<endl;
                            //eff = 1.;
		            //cout<<hit_p<<" "<<hit_r<<endl;
		            triEff_Q2x_gen->Fill(x, Q2, rate);
		            triEff_Q2x_acc->Fill(x, Q2, rate*eff);
		            triEff_pr_gen->Fill(hit_p, hit_r, rate);
		            triEff_pr_acc->Fill(hit_p, hit_r, rate*eff);
		        }

		      }		
		      
		      if (detector_ID == 1 && TMath::Nint(flux_tid->at(j))==1){
		        if (hit_r <= rmax[hit_id] && hit_r >= rmin[hit_id]) GEMFound[hit_id] = true;
		      }
		      
		    }	//end of flux loop		
	        if (Require_GEM){
	            for (int j=0; j<5; j++) {
	                if (!GEMFound[j]) acc = 0;
	            }
	        }
	        
	          double pf=p_gen;
	          
	          if (22<theta_gen*DEG && theta_gen*DEG <35){ 
		          hrate_P_gen->Fill(pf,rate);
		          hrate_P_acc->Fill(pf,rate*acc*eff);
		          hrate_Theta_gen->Fill(theta_gen*DEG,rate);
		          hrate_Theta_acc->Fill(theta_gen*DEG,rate*acc*eff);
		          hrate_x_gen->Fill(x,rate);
		          hrate_x_acc->Fill(x,rate*acc*eff);
		          hrate_Q2_gen->Fill(Q2,rate);
		          hrate_Q2_acc->Fill(Q2,rate*acc*eff);
	          }
	          
	          hrate_PTheta_gen->Fill(theta_gen*DEG,pf,rate);
	          hrate_PTheta_acc->Fill(theta_gen*DEG,pf,rate*acc*eff);
	          hrate_PTheta_zwzhao_gen->Fill(theta_gen*DEG,pf,rate);
	          hrate_PTheta_zwzhao_acc->Fill(theta_gen*DEG,pf,rate*acc*eff);
	          
	          hrate_Q2x_gen->Fill(x,Q2,rate);
	          hrate_Q2x_acc->Fill(x,Q2,rate*acc*eff);
	          hrate_Q2x_acc_bin->Fill(x,Q2,rate*acc*eff);

	          hAbeam_Q2x_gen->Fill(x,Q2,-Abeam*rate);
	          hAbeam_Q2x_acc->Fill(x,Q2,-Abeam*rate*acc*eff);

	          double Apv=0.84e-4*Q2;  
	          hApv_Q2x_gen->Fill(x,Q2,Apv*rate);
	          hApv_Q2x_acc->Fill(x,Q2,Apv*rate*acc*eff);  
	          
	          hApvErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*runtime)/pb*100);
	          hAbeamErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*runtime)/pb*100);  
	          if (acc*eff !=0) {
		          hApvErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*runtime*acc*eff)/pb*100);
		          hAbeamErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*runtime*acc*eff)/pb*100);
	          }
	          
		      for(int k = 0; k < Nbin; k++){  
		        if (bin[k][0] <= x && x < bin[k][1] && bin[k][2] <= Q2 && Q2 < bin[k][3]){
		          thatrate[k] += rate*acc*eff;
		          Apv_sum[k] += Apv*rate*acc*eff;
		          Abeam_sum[k] += -Abeam*rate*acc*eff;
                          Q2_sum[k] += Q2*rate*acc*eff;
                          y_sum[k]  += y*rate*acc*eff;
		        }
		      }		

	    } //end event loop
	    
	    } //end loop time
	    //file_rate->Close(); delete file_rate;
	    file->Close(); delete file;
	}

//do outputs

hAbeam_Q2x_gen->Divide(hAbeam_Q2x_gen,hrate_Q2x_gen);
hAbeam_Q2x_acc->Divide(hAbeam_Q2x_acc,hrate_Q2x_acc);
hApv_Q2x_gen->Divide(hApv_Q2x_gen,hrate_Q2x_gen);
hApv_Q2x_acc->Divide(hApv_Q2x_acc,hrate_Q2x_acc);

hAbeamErr_Q2x_gen->Divide(hAbeamErr_Q2x_gen,hAbeam_Q2x_gen);
hAbeamErr_Q2x_acc->Divide(hAbeamErr_Q2x_acc,hAbeam_Q2x_acc);
hApvErr_Q2x_gen->Divide(hApvErr_Q2x_gen,hApv_Q2x_gen);
hApvErr_Q2x_acc->Divide(hApvErr_Q2x_acc,hApv_Q2x_acc);

TCanvas *c_rate_PTheta = new TCanvas("rate_PTheta","rate_PTheta",1800,600);
c_rate_PTheta->Divide(2,1);
c_rate_PTheta->cd(1);
gPad->SetLogz();
gPad->SetGrid();
hrate_PTheta_gen->Draw("colz");
c_rate_PTheta->cd(2);
gPad->SetLogz();
gPad->SetGrid();
hrate_PTheta_acc->Draw("colz");

TCanvas *c_rate_Q2x = new TCanvas("rate_Q2x","rate_Q2x",1800,600);
c_rate_Q2x->Divide(2,1);
c_rate_Q2x->cd(1);
gPad->SetLogz();
gPad->SetGrid();
// hrate_Q2x_gen->SetAxisRange(1,15,"Y");
hrate_Q2x_gen->Draw("colz");
c_rate_Q2x->cd(2);
gPad->SetLogz();
gPad->SetGrid();
// hrate_Q2x_acc->SetAxisRange(1,15,"Y");
hrate_Q2x_acc->Draw("colz");

hacceptance_P->Divide(hrate_P_acc,hrate_P_gen);
hacceptance_Theta->Divide(hrate_Theta_acc,hrate_Theta_gen);
hacceptance_x->Divide(hrate_x_acc,hrate_x_gen);
hacceptance_Q2->Divide(hrate_Q2_acc,hrate_Q2_gen);
hacceptance_PTheta->Divide(hrate_PTheta_acc,hrate_PTheta_gen);
hacceptance_Q2x->Divide(hrate_Q2x_acc,hrate_Q2x_gen);

TCanvas *c_acceptance_eDIS_1D = new TCanvas("acceptance_eDIS_1D","acceptance_eDIS_1D",1800,900);
c_acceptance_eDIS_1D->Divide(2,2);
c_acceptance_eDIS_1D->cd(1);
gPad->SetGrid();
hacceptance_P->SetMinimum(0);
hacceptance_P->SetMaximum(1);
hacceptance_P->Draw();
c_acceptance_eDIS_1D->cd(2);
gPad->SetGrid();
hacceptance_Theta->SetMinimum(0);
hacceptance_Theta->SetMaximum(1);
hacceptance_Theta->Draw();
c_acceptance_eDIS_1D->cd(3);
gPad->SetGrid();
hacceptance_x->SetMinimum(0);
hacceptance_x->SetMaximum(1);
hacceptance_x->Draw();
c_acceptance_eDIS_1D->cd(4);
gPad->SetGrid();
hacceptance_Q2->SetMinimum(0);
hacceptance_Q2->SetMaximum(1);
hacceptance_Q2->Draw();
c_acceptance_eDIS_1D->SaveAs("acceptance_eDIS_1D.png");

TCanvas *c_acceptance_eDIS_2D = new TCanvas("acceptance_eDIS_2D","acceptance_eDIS_2D",1800,600);
c_acceptance_eDIS_2D->Divide(2,1);
c_acceptance_eDIS_2D->cd(1);
gPad->SetGrid();
hacceptance_PTheta->SetMinimum(0);
hacceptance_PTheta->SetMaximum(1);
hacceptance_PTheta->Draw("colz");
c_acceptance_eDIS_2D->cd(2);
gPad->SetGrid();
hacceptance_Q2x->SetMinimum(0);
hacceptance_Q2x->SetMaximum(1);
hacceptance_Q2x->Draw("colz");
c_acceptance_eDIS_2D->SaveAs("acceptance_eDIS_2D.png");

TCanvas *c_Apv_ApvErr_Q2x = new TCanvas("Apv_ApvErr_Q2x","Apv_ApvErr_Q2x",1800,1200);
c_Apv_ApvErr_Q2x->Divide(2,2);
c_Apv_ApvErr_Q2x->cd(1);
gPad->SetGrid();
hApv_Q2x_gen->SetMinimum(0);
hApv_Q2x_gen->SetMaximum(0.002);
hApv_Q2x_gen->Draw("colz");
c_Apv_ApvErr_Q2x->cd(2);
gPad->SetGrid();
hApvErr_Q2x_gen->SetMinimum(0);
hApvErr_Q2x_gen->SetMaximum(50000);
hApvErr_Q2x_gen->Draw("colz");
c_Apv_ApvErr_Q2x->cd(3);
gPad->SetGrid();
hApv_Q2x_acc->SetMinimum(0);
hApv_Q2x_acc->SetMaximum(0.002);
hApv_Q2x_acc->Draw("colz");
c_Apv_ApvErr_Q2x->cd(4);
gPad->SetGrid();
hApvErr_Q2x_acc->SetMinimum(0);
hApvErr_Q2x_acc->SetMaximum(5000);
hApvErr_Q2x_acc->Draw("colz");

TCanvas *c_Abeam_AbeamErr_Q2x = new TCanvas("Abeam_AbeamErr_Q2x","Abeam_AbeamErr_Q2x",1800,1200);
c_Abeam_AbeamErr_Q2x->Divide(2,2);
c_Abeam_AbeamErr_Q2x->cd(1);
gPad->SetGrid();
hAbeam_Q2x_gen->SetMinimum(0);
hAbeam_Q2x_gen->SetMaximum(0.002);
hAbeam_Q2x_gen->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(2);
gPad->SetGrid();
hAbeamErr_Q2x_gen->SetMinimum(0);
hAbeamErr_Q2x_gen->SetMaximum(50000);
hAbeamErr_Q2x_gen->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(3);
gPad->SetGrid();
hAbeam_Q2x_acc->SetMinimum(0);
hAbeam_Q2x_acc->SetMaximum(0.002);
hAbeam_Q2x_acc->Draw("colz");
c_Abeam_AbeamErr_Q2x->cd(4);
gPad->SetGrid();
hAbeamErr_Q2x_acc->SetMinimum(0);
hAbeamErr_Q2x_acc->SetMaximum(5000);
hAbeamErr_Q2x_acc->Draw("colz");


  for( int i = 1; i < hrate_Q2x_acc_bin->GetNbinsX(); i++ ){
    for( int j = 1; j < hrate_Q2x_acc_bin->GetNbinsY(); j++ ){
      double thisrate=hrate_Q2x_acc_bin->GetBinContent(i,j);
      if (thisrate==0) continue;      
      double Apv = 0.84e-4*hrate_Q2x_acc_bin->GetYaxis()->GetBinCenter(j);
//       cout << hrate_Q2x_acc_bin->GetYaxis()->GetBinCenter(j) << endl; 
      double ApvErr = 1./sqrt(thisrate*runtime)/Apv/pb*100;     
      hApvErr_Q2x_acc_bin->SetBinContent(i,j,ApvErr);
    }
  }
  
TCanvas *c_rate_ApvErr_Q2x_bin = new TCanvas("rate_ApvErr_Q2x_bin","rate_ApvErr_Q2x_bin",1800,600);
c_rate_ApvErr_Q2x_bin->Divide(2,1);
c_rate_ApvErr_Q2x_bin->cd(1);
gPad->SetGrid();
// hrate_Q2x_acc_bin->SetAxisRange(1,15,"Y");
hrate_Q2x_acc_bin->Draw("text");
c_rate_ApvErr_Q2x_bin->cd(2);
gPad->SetGrid();
// hApvErr_Q2x_acc_bin->SetMaximum(5);
// hApvErr_Q2x_acc_bin->SetAxisRange(1,15,"Y");
hApvErr_Q2x_acc_bin->Draw("text");

double AbeamErr[Nbin],ApvErr[Nbin];
    cout << "y_ave"<<"\t"<<"Q2_ave" << "\t"<<"Apv_ave" << "\t" << "Abeam_ave" << "\t" << "rate" << "\t" << "ApvErr" << "\t" <<  "AbeamErr" << endl;
for(int k = 0; k < Nbin; k++){
//     double Apv = 0.84e-4*(bin[k][2]+bin[k][3])/2.;
    double Q2_ave = Q2_sum[k]/thatrate[k];
    double y_ave = y_sum[k]/thatrate[k];
    double Apv_ave = Apv_sum[k]/thatrate[k];
    ApvErr[k] = 1./sqrt(thatrate[k]*runtime)/Apv_ave/pb*100;   
    double Abeam_ave=Abeam_sum[k]/thatrate[k];
    AbeamErr[k] = 1./sqrt(thatrate[k]*runtime)/Abeam_ave/pb*100;      
    cout << y_ave<<"\t"<<Q2_ave<<"\t" << Apv_ave << "\t" << Abeam_ave << "\t" << int(thatrate[k]) << "\t" << ApvErr[k] << "\t" <<  AbeamErr[k] << endl;
}

cout << "ApvErr" << endl;
for(int k = 0; k < Nbin; k++) cout << Form("%.03f",ApvErr[k]) << "\t";
cout << endl;
cout << "AbeamErr" << endl;
for(int k = 0; k < Nbin; k++) cout << Form("%.03f",AbeamErr[k]) << "\t";
cout << endl;

TCanvas *c_AbeamErr_Q2x_acc = new TCanvas("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",900,600);
gPad->SetGrid();
hAbeamErr_Q2x_acc->SetTitle("Asymmetry Uncertainty (%) with 120 days of 85% polarized 50uA electron beam on 40cm LD2 target;x;Q^{2} (GeV^{2})");
hAbeamErr_Q2x_acc->SetMarkerColor(kGreen);
hAbeamErr_Q2x_acc->Draw();

#ifdef PVDIS_HYDROGEN
double x_cor[8]={0.31, 0.38, 0.42, 0.47, 0.52, 0.57, 0.63, 0.70};
double Q2_cor[8]={5.0, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0};
#else
double x_cor[15]={0.250,0.325,0.375,0.375,0.425,0.425,0.475,0.475,0.525,0.525,0.575,0.575,0.635,0.635,0.735};
double Q2_cor[15]={4.2,5.0,5.5,6.3,6.0,7.0,6.5,7.8,7.1,8.5,7.6,9.1,8.2,9.8,9.8};    
#endif
// double x_cor[7]={0.250,0.325,0.375,0.425,0.475,0.525,0.575};
// double Q2_cor[7]={2.0,2.5,3.0,3.5,4.0,4.5,5.0};
for(int k = 0; k < Nbin; k++){
TMarker marker;
marker.SetMarkerStyle(20);
marker.SetMarkerColor(kRed);
marker.DrawMarker(x_cor[k],Q2_cor[k]);
TText *label = new TText(x_cor[k],Q2_cor[k],Form("%.02f",AbeamErr[k]));
label->SetTextColor(kBlack);
label->SetTextSize(0.03);
label->Draw();
}

c_AbeamErr_Q2x_acc->SaveAs("AbeamErr_Q2x_acc.png");

outputfile->Write();	
outputfile->Flush();

TCanvas* cc = new TCanvas("cc", "cc", 1200, 600);
cc->Divide(2, 1);
triEff_Q2x_acc->Divide(triEff_Q2x_acc, triEff_Q2x_gen);
triEff_pr_acc->Divide(triEff_pr_acc, triEff_pr_gen);
cc->cd(1);
triEff_Q2x_acc->Draw("colz");
cc->cd(2);
triEff_pr_acc->Draw("colz");

TFile* outFile = new TFile("output_rate_by_theta_bin.root", "RECREATE");
outFile->cd();
for (int i=0; i<NTHETABIN; i++){
    double binwidth = histThetaP[i]->GetBinWidth(10);
    histThetaP[i]->Scale(1./binwidth);
    histThetaP[i]->Write();
}
outFile->Close();
}
