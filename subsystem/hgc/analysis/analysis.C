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

#include "analysis_tree_solid_hgc.C"

using namespace std;

double PhotonEnergy[42]={
2.04358, 2.0664, 2.09046, 2.14023, 
2.16601, 2.20587, 2.23327, 2.26137, 
2.31972, 2.35005, 2.38116, 2.41313, 
2.44598, 2.47968, 2.53081, 2.58354, 
2.6194, 2.69589, 2.73515, 2.79685, 
2.86139, 2.95271, 3.04884, 3.12665, 
3.2393, 3.39218, 3.52508, 3.66893,
3.82396, 3.99949, 4.13281, 4.27679, 
4.48244, 4.65057, 4.89476, 5.02774, 
5.16816, 5.31437, 5.63821, 5.90401, 
6.19921,6.49921,
// 8.3,  //down to 150nm
};  // in ev

const int n=41;
double QE_H8500_03[n] = {
0.008, 0.0124, 0.0157, 0.02125, 
0.0275, 0.034, 0.04, 0.048, 
0.062, 0.0753, 0.09, 0.1071, 
0.12144, 0.1428, 0.15, 0.16429, 
0.17857, 0.1928, 0.2, 0.2125,
0.225, 0.2375, 0.25, 0.2625, 
0.275, 0.275, 0.275, 0.275, 
0.275, 0.275, 0.2625, 0.25, 
0.2375, 0.2125, 0.192859, 0.185716, 
0.178573, 0.15714, 0.13572, 0.1143,
0.09  
}; 
double QE_H12700_03[n] = {
0.016,0.02,0.025,0.033,
0.042,0.048,0.056,0.06,
0.075,0.085,0.096,0.121,
0.147,0.166,0.182,0.194,
0.203,0.22,0.238,0.253,
0.269,0.287,0.3,0.31,
0.32,0.33,0.335,0.335,
0.335,0.33,0.325,0.31,
0.296,0.282,0.257,0.237,
0.22,0.197,0.165,0.139,
0.114
};
double QE_H12700_03_WLS_meas[n] = {
0.016,0.02,0.0243455,0.0349796,0.0400769,0.0495496,0.054666,0.0612895,0.0758019,0.0853365,0.100662,0.121331,0.144678,0.162644,0.180719,0.194414,0.202599,0.224051,0.235051,0.253334,0.268143,0.285398,0.30002,0.309013,0.319247,0.328839,0.333333,0.335,0.33337,0.327161,0.321697,0.328776,0.333637,0.318123,0.313051,0.326953,0.331335,0.331335,0.331335,0.331335,0.331335
};

// double *eff_PMT=QE_H12700_03;
double *eff_PMT=QE_H12700_03_WLS_meas;

//safety factor
//PMT and assmbly effective area
//for pion, manual reduce 2
double factor=0.8*0.5;  

void analysis(string input_filename)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetOptStat(1111111);
gStyle->SetOptFit(111111);
gStyle->SetPadRightMargin(0.15); 

const double DEG=180./3.1415926;

// cout << eff_PMT[0] << " " << eff_PMT[1] << " " << eff_PMT[2] << " " << eff_PMT[3] << " " << endl;

char the_filename[200];
sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());

// cout << the_filename << endl;

char output_filename[200];
sprintf(output_filename, "%s_output.root",the_filename);
TFile *outputfile=new TFile(output_filename, "recreate");

TH1F *hcount=new TH1F("hcount","hcount;number of photoelectron;count",100,0,50);

const int Nbin_Theta=140,Nbin_Phi=180;
double Max_Theta=35;
TH1F *hcount_ThetaPhi[Nbin_Theta][Nbin_Phi];
for(int i=0;i<Nbin_Theta;i++){
  for(int j=0;j<Nbin_Phi;j++){
   char hstname[100];   
   sprintf(hstname,"hcount_ThetaPhi_%i_%i",i,j);
   hcount_ThetaPhi[i][j]=new TH1F(hstname,";number of photoelectron;count",100,0,50);
  }
}
TH2F *havg_pe=new TH2F("havg_pe","avg number of photoelectron;#theta(deg);#phi(deg)",Nbin_Theta,0,Max_Theta,Nbin_Phi,-180,180);

TH2F *hhitxy_hgc=new TH2F("hhitxy_hgc","p.e. pattern; r (mm); #phi (mm)",32,-102,102,32,-102,102);

TH2F *hhitxy_hgc_mirror=new TH2F("hhitxy_hgc_mirror","photon pattern on mirror; r (mm); #phi (mm)",140,800,2200,60,-300,300);
TH2F *hhitxy_hgc_cone=new TH2F("hhitxy_hgc_cone","photon pattern on cone; r (mm); #phi (mm)",60,-300,300,60,-300,300);

TFile *file=new TFile(input_filename.c_str());
if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
}
// else cout << "open file " << input_filename << endl;    

TTree *tree_header = (TTree*) file->Get("header");
vector <int> *evn=0,*evn_type=0;
vector <double> *beamPol=0;
vector <int> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
tree_header->SetBranchAddress("evn",&evn);
tree_header->SetBranchAddress("evn_type",&evn_type);
tree_header->SetBranchAddress("beamPol",&beamPol);
tree_header->SetBranchAddress("var1",&var1);
tree_header->SetBranchAddress("var2",&var2);
tree_header->SetBranchAddress("var3",&var3);
tree_header->SetBranchAddress("var4",&var4);
tree_header->SetBranchAddress("var5",&var5);
tree_header->SetBranchAddress("var6",&var6);
tree_header->SetBranchAddress("var7",&var7);
tree_header->SetBranchAddress("var8",&var8);

TTree *tree_generated = (TTree*) file->Get("generated");
vector <int> *gen_pid=0;
vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
tree_generated->SetBranchAddress("pid",&gen_pid);
tree_generated->SetBranchAddress("px",&gen_px);
tree_generated->SetBranchAddress("py",&gen_py);
tree_generated->SetBranchAddress("pz",&gen_pz);
tree_generated->SetBranchAddress("vx",&gen_vx);
tree_generated->SetBranchAddress("vy",&gen_vy);
tree_generated->SetBranchAddress("vz",&gen_vz);

TTree *tree_flux = (TTree*) file->Get("flux");
vector<int> *flux_id=0,*flux_hitn=0;
vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
tree_flux->SetBranchAddress("hitn",&flux_hitn);
tree_flux->SetBranchAddress("id",&flux_id);
tree_flux->SetBranchAddress("pid",&flux_pid);
tree_flux->SetBranchAddress("mpid",&flux_mpid);
tree_flux->SetBranchAddress("tid",&flux_tid);
tree_flux->SetBranchAddress("mtid",&flux_mtid);
tree_flux->SetBranchAddress("otid",&flux_otid);
tree_flux->SetBranchAddress("trackE",&flux_trackE);
tree_flux->SetBranchAddress("totEdep",&flux_totEdep);
tree_flux->SetBranchAddress("avg_x",&flux_avg_x);
tree_flux->SetBranchAddress("avg_y",&flux_avg_y);
tree_flux->SetBranchAddress("avg_z",&flux_avg_z);
tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);
tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);
tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);
tree_flux->SetBranchAddress("px",&flux_px);
tree_flux->SetBranchAddress("py",&flux_py);
tree_flux->SetBranchAddress("pz",&flux_pz);
tree_flux->SetBranchAddress("vx",&flux_vx);
tree_flux->SetBranchAddress("vy",&flux_vy);
tree_flux->SetBranchAddress("vz",&flux_vz);
tree_flux->SetBranchAddress("mvx",&flux_mvx);
tree_flux->SetBranchAddress("mvy",&flux_mvy);
tree_flux->SetBranchAddress("mvz",&flux_mvz);
tree_flux->SetBranchAddress("avg_t",&flux_avg_t);

TTree *tree_solid_hgc = (TTree*) file->Get("solid_hgc");
setup_tree_solid_hgc(tree_solid_hgc);

int nevent = (int)tree_generated->GetEntries();
int nselected = 0;
// cout << "nevent " << nevent << endl;

for (Int_t i=0;i<nevent;i++) { 
// for (Int_t i=0;i<2;i++) { 
//   cout << i << "\r";
//   cout << i << "\n";

  tree_header->GetEntry(i);
  
  tree_generated->GetEntry(i);  
  int pid_gen=0;
  double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
  for (int j=0;j<gen_pid->size();j++) {
//       cout << gen_pid->at(j) << " " << gen_px->at(j) << " " << gen_py->at(j) << " " << gen_pz->at(j) << " " << gen_vx->at(j) << " " << gen_vy->at(j) << " " << gen_vz->at(j) << endl; 
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
      
//       cout << "p_gen " << p_gen << endl;
  }

    tree_flux->GetEntry(i);  
    
    for (Int_t j=0;j<flux_hitn->size();j++) {
//       cout << "flux " << " !!! " << flux_hitn->at(j) << " " << flux_id->at(j) << " " << flux_pid->at(j) << " " << flux_mpid->at(j) << " " << flux_tid->at(j) << " " << flux_mtid->at(j) << " " << flux_trackE->at(j) << " " << flux_totEdep->at(j) << " " << flux_avg_x->at(j) << " " << flux_avg_y->at(j) << " " << flux_avg_z->at(j) << " " << flux_avg_lx->at(j) << " " << flux_avg_ly->at(j) << " " << flux_avg_lz->at(j) << " " << flux_px->at(j) << " " << flux_py->at(j) << " " << flux_pz->at(j) << " " << flux_vx->at(j) << " " << flux_vy->at(j) << " " << flux_vz->at(j) << " " << flux_mvx->at(j) << " " << flux_mvy->at(j) << " " << flux_mvz->at(j) << " " << flux_avg_t->at(j) << endl;  

      int detector_ID=flux_id->at(j)/1000000;
      int subdetector_ID=(flux_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;
      int component_ID=flux_id->at(j)%10000;      
           
//       if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1)   cout << "particle mom entering EC " << flux_trackE->at(j) << endl;         
      
      if (flux_pid->at(j)!=0) continue;      
      
      if (flux_id->at(j)==2211023) hhitxy_hgc_mirror->Fill(flux_avg_lx->at(j),flux_avg_ly->at(j));	
      if (flux_id->at(j)==2212023) hhitxy_hgc_cone->Fill(flux_avg_lx->at(j),flux_avg_ly->at(j));	
      
    }	
    
    tree_solid_hgc->GetEntry(i);  
//   
//   double *lx_hgc=process_tree_solid_hgc_lx(tree_solid_hgc);
//   double *ly_hgc=process_tree_solid_hgc_ly(tree_solid_hgc);  
//   cout << "totEdep_hgc " << totEdep_hgc << endl;
  double count_this=0,count_that=0;
//     for (Int_t j=0;j<1;j++) {  
    for (Int_t j=0;j<solid_hgc_hitn->size();j++) {
//       cout << "solid_hgc " << " !!! " << solid_hgc_hitn->at(j) << " " << solid_hgc_id->at(j) << " " << solid_hgc_pid->at(j) << " " << solid_hgc_mpid->at(j) << " " << solid_hgc_tid->at(j) << " " << solid_hgc_mtid->at(j) << " " << solid_hgc_trackE->at(j) << " " << solid_hgc_totEdep->at(j) << " " << solid_hgc_avg_x->at(j) << " " << solid_hgc_avg_y->at(j) << " " << solid_hgc_avg_z->at(j) << " " << solid_hgc_avg_lx->at(j) << " " << solid_hgc_avg_ly->at(j) << " " << solid_hgc_avg_lz->at(j) << " " << solid_hgc_px->at(j) << " " << solid_hgc_py->at(j) << " " << solid_hgc_pz->at(j) << " " << solid_hgc_vx->at(j) << " " << solid_hgc_vy->at(j) << " " << solid_hgc_vz->at(j) << " " << solid_hgc_mvx->at(j) << " " << solid_hgc_mvy->at(j) << " " << solid_hgc_mvz->at(j) << " " << solid_hgc_avg_t->at(j) << endl;  

      int detector_ID=solid_hgc_id->at(j)/1000000;
      int subdetector_ID=(solid_hgc_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_hgc_id->at(j)%1000000)%100000)/10000;
      int component_ID=solid_hgc_id->at(j)%10000;
                 
      if (solid_hgc_pid->at(j)!=0) continue;
//       cout << "solid_hgc " << solid_hgc_id->at(j) << endl;
//       if (detector_ID==2 && subdetector_ID == 4 && subsubdetector_ID == 3) {	  
      if (true) {	        
	  double E_photon=solid_hgc_trackE->at(j)*1e6; //in eV
	  double weight=0; 	  
	  for (Int_t k=0;k<n;k++) {	      
// 	  for (Int_t k=0;k<25;k++) {	 // cut on 360nm/3.35eV
	    if (PhotonEnergy[k]<=E_photon && E_photon<PhotonEnergy[k+1]) {
	    weight=eff_PMT[k];
	    break;
	    }
	  }
	  count_this +=weight;	  
	  hhitxy_hgc->Fill(solid_hgc_avg_lx->at(j),solid_hgc_avg_ly->at(j),weight/double(nevent));	
      }
      else {
	count_that +=1;
// 	cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID  << " " << component_ID << ", " << solid_hgc_id->at(j) << endl; 	
      }
      
    }

    if (count_this>0){
       hcount->Fill(count_this*factor);
       
      if (theta_gen<=Max_Theta) {
	int bin_Theta=int(theta_gen/(Max_Theta/Nbin_Theta));
	int bin_Phi=int((phi_gen-(-180))/(360./Nbin_Phi));
// 	 cout << "bin_Theta " << bin_Theta << "theta_gen " << theta_gen << endl;	
	hcount_ThetaPhi[bin_Theta][bin_Phi]->Fill(count_this*factor);       
      }
      else cout << "theta_gen too large " << theta_gen << endl;
      
    }
     
//     cout << " count_this " << count_this << " count_that " << count_that << endl;    
  
}
file->Close();

for(int i=0;i<Nbin_Theta;i++){
  for(int j=0;j<Nbin_Phi;j++){
    havg_pe->SetBinContent(i+1,j+1,hcount_ThetaPhi[i][j]->GetMean());
    havg_pe->SetBinError(i+1,j+1,hcount_ThetaPhi[i][j]->GetRMS());
  }
}

outputfile->Write();
outputfile->Flush();

TCanvas *c_hitxy_hgc = new TCanvas("hhitxy_hgc","hhitxy_hgc",1000,1000);
hhitxy_hgc->Draw("colz");
c_hitxy_hgc->SaveAs(Form("%s_hitpmt.png",the_filename));

TCanvas *c_hitxy_hgc_mirror = new TCanvas("hitxy_hgc_mirror","hitxy_hgc_mirror",1000,1000);
hhitxy_hgc_mirror->Draw("colz");
c_hitxy_hgc_mirror->SaveAs(Form("%s_hitmirror.png",the_filename));

TCanvas *c_hitxy_hgc_cone = new TCanvas("hitxy_hgc_cone","hitxy_hgc_cone",1000,1000);
hhitxy_hgc_cone->Draw("colz");
c_hitxy_hgc_cone->SaveAs(Form("%s_hitcone.png",the_filename));

TCanvas *c_havg_pe = new TCanvas("havg_pe","havg_pe",1000,1000);
havg_pe->SetMaximum(50);
havg_pe->Draw("colz");
c_havg_pe->SaveAs(Form("%s_avg_pe.png",the_filename));

cout << hhitxy_hgc->GetSum() << endl;

}
