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

using namespace std;

void analysis(string input_filename)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(111111);
gStyle->SetOptFit(111111);

const double DEG=180./3.1415926;

char the_filename[200];
sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());

// char output_filename[200];
// sprintf(output_filename, "%s_output.root",the_filename);
// TFile *outputfile=new TFile(output_filename, "recreate");

TH1F *htotEdep=new TH1F("totEdep","totEdep",350,0,3500);

TFile *file=new TFile(input_filename.c_str());
if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
}
else cout << "open file " << input_filename << endl;    

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

TTree *tree_solid_ec = (TTree*) file->Get("solid_ec");
vector<int> *solid_ec_id=0,*solid_ec_hitn=0;
vector<int> *solid_ec_pid=0,*solid_ec_mpid=0,*solid_ec_tid=0,*solid_ec_mtid=0,*solid_ec_otid=0;
vector<double> *solid_ec_trackE=0,*solid_ec_totEdep=0,*solid_ec_avg_x=0,*solid_ec_avg_y=0,*solid_ec_avg_z=0,*solid_ec_avg_lx=0,*solid_ec_avg_ly=0,*solid_ec_avg_lz=0,*solid_ec_px=0,*solid_ec_py=0,*solid_ec_pz=0,*solid_ec_vx=0,*solid_ec_vy=0,*solid_ec_vz=0,*solid_ec_mvx=0,*solid_ec_mvy=0,*solid_ec_mvz=0,*solid_ec_avg_t=0;
tree_solid_ec->SetBranchAddress("hitn",&solid_ec_hitn);
tree_solid_ec->SetBranchAddress("id",&solid_ec_id);
tree_solid_ec->SetBranchAddress("pid",&solid_ec_pid);
tree_solid_ec->SetBranchAddress("mpid",&solid_ec_mpid);
tree_solid_ec->SetBranchAddress("tid",&solid_ec_tid);
tree_solid_ec->SetBranchAddress("mtid",&solid_ec_mtid);
tree_solid_ec->SetBranchAddress("otid",&solid_ec_otid);
tree_solid_ec->SetBranchAddress("trackE",&solid_ec_trackE);
tree_solid_ec->SetBranchAddress("totEdep",&solid_ec_totEdep);
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

// cout << tree_solid_ec->GetEntries() << " " << tree_header->GetEntries() << " " << tree_generated->GetEntries() << endl;

int nevent = (int)tree_generated->GetEntries();
int nselected = 0;
cout << "nevent " << nevent << endl;

for (Int_t i=0;i<nevent;i++) { 
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
      theta_gen=acos(pz_gen/p_gen);
      phi_gen=atan2(py_gen,px_gen);
  }  
  
  double totEdep=0;
  
    tree_solid_ec->GetEntry(i);    
//     cout << solid_ec_hitn->size() << endl;        
    for (Int_t j=0;j<solid_ec_hitn->size();j++) {
//       cout << "solid_ec " << " !!! " << solid_ec_hitn->at(j) << " " << solid_ec_id->at(j) << " " << solid_ec_pid->at(j) << " " << solid_ec_mpid->at(j) << " " << solid_ec_tid->at(j) << " " << solid_ec_mtid->at(j) << " " << solid_ec_trackE->at(j) << " " << solid_ec_totEdep->at(j) << " " << solid_ec_avg_x->at(j) << " " << solid_ec_avg_y->at(j) << " " << solid_ec_avg_z->at(j) << " " << solid_ec_avg_lx->at(j) << " " << solid_ec_avg_ly->at(j) << " " << solid_ec_avg_lz->at(j) << " " << solid_ec_px->at(j) << " " << solid_ec_py->at(j) << " " << solid_ec_pz->at(j) << " " << solid_ec_vx->at(j) << " " << solid_ec_vy->at(j) << " " << solid_ec_vz->at(j) << " " << solid_ec_mvx->at(j) << " " << solid_ec_mvy->at(j) << " " << solid_ec_mvz->at(j) << " " << solid_ec_avg_t->at(j) << endl;         
    
      int detector_ID=solid_ec_id->at(j)/1000000;
      int subdetector_ID=(solid_ec_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((solid_ec_id->at(j)%1000000)%100000)/10000;
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID << endl;  
      
       totEdep +=solid_ec_totEdep->at(j);     
    }
    
    htotEdep->Fill(totEdep);
    
}
file->Close();

// outputfile->Write();
// outputfile->Flush();

TCanvas *c = new TCanvas("totEdep","totEdep",1000,900);
htotEdep->Draw();
htotEdep->Fit("gaus");
}
