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

#include "analysis_tree_solid_ec_beamtest_2021_ps.C"

using namespace std;

void analysis_beamtest_2021_ps(string input_filename, int Eng)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(111111);
gStyle->SetOptFit(111111);

const double DEG=180./3.1415926;
const double pmax=Eng;
const double pmin=0;
const int pbins=200;
char the_filename[200];
sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());
  TFile* f_outFile = new TFile(Form("e_%dMeV_newECAL_beamsize1cm_leftmodule_center.root",Eng), "RECREATE");
// char output_filename[200];
// sprintf(output_filename, "%s_output.root",the_filename);
// TFile *outputfile=new TFile(output_filename, "recreate");
TH1F *htotEdep_ec=new TH1F("htotEdep_ec","ec sum of shower scin;totEdep_scin(MeV);",pbins,pmin,pmax);
TH1F *htotEdep_ec_preshower=new TH1F("htotEdep_ec_preshower","ec sum of preshower;totEdep_prescin(MeV);",150,0,300);
TH1F *htotEdep_ec_lead=new TH1F("htotEdep_ec_lead","ec;totEdep_lead(MeV);",500,0,1000);
TH1F *htotEdep_ec_Al=new TH1F("htotEdep_ec_Al","ec;totEdep_Al(MeV);",500,0,1000);
TH1F *htotEdep_ec_Al_shower=new TH1F("htotEdep_ec_Al_shower","ec;totEdep_Al_shower(MeV);",500,0,1000);
TH1F *htotEdep_ec_prelead=new TH1F("htotEdep_ec_prelead","ec;totEdep_prelead(MeV);",500,0,1000);
TH1F *htotEdep_ec_Tylar=new TH1F("htotEdep_ec_Tylar","ec;totEdep_Tylar(MeV);",500,0,1000);
TH1F *htotEdep_ec_shower=new TH1F("htotEdep_ec_shower","ec sum of shower(scin+lead+Tylar);totEdep_shower(MeV);",pbins,0,pmax);
TH1F *htotEdep_ec_total=new TH1F("htotEdep_ec_total","ec;totEdep_total(MeV);",pbins,0,pmax);
TH1F *htotEdep_ec_shower_preshower=new TH1F("htotEdep_ec_shower_preshower","ec sum of shower+preshower;totEdep_shower_preshower(MeV);",pbins,0,pmax);
TH1F *htotEdep_ec_shower_preshower_scin=new TH1F("htotEdep_ec_shower_preshower_scin","ec sum of shower+preshower scin ;totEdep_shower_preshower(MeV);",pbins,0,pmax);
TH2F *prescin_vs_scin_hist =new TH2F("prescin_vs_scin_hist","ec;shower scin(MeV);preshower scin (MeV)",250,0,pmax,100,0,250);
TH2F *hp_gen_flux=new TH2F("hp_gen_flux",";p_gen(MeV);p_flux(MeV)",110,0,11000,110,0,11000);
TH1F *htotEdep_shower_module[4];
TH1F *htotEdep_preshower_shower_module[4];
TH1F *htotEdep_ec_module[4];
TH1F *htotEdepB_ec_module[4];
TH1F *htotEdepEnd_ec_module[4];
TH1F *htotEdep_preshower_module[4];
TH2F *prescin_vs_scin_hist_module[4];
TH1F *presh_htotEdep_ec_module[4];
TH1F *presh_htotEdepB_ec_module[4];
TH1F *presh_htotEdepEnd_ec_module[4];
for(int i=0;i<4;i++){
htotEdep_shower_module[i]=new TH1F(Form("htotEdep_shower_module%d",i),Form("ec shower(scin+lead+Tylar) module%d;totEdep(MeV);",i),pbins,0,pmax);
htotEdep_preshower_shower_module[i]=new TH1F(Form("htotEdep_preshower_shower_module%d",i),Form("ec shower+preshower module%d;totEdep(MeV);",i),pbins,0,pmax/4);
htotEdep_ec_module[i]=new TH1F(Form("htotEdep_ec_module%d",i),Form("ec shower scin module%d;totEdep_scin(MeV);",i),pbins,0,pmax/4);
htotEdepB_ec_module[i]=new TH1F(Form("htotEdepB_ec_module%d",i),Form("ec shower scin module%d;totEdepB_scin(MeV);",i),pbins,0,pmax/4);
htotEdepEnd_ec_module[i]=new TH1F(Form("htotEdepEnd_ec_module%d",i),Form("ec shower scin module%d;totEdepEnd_scin(MeV);",i),pbins,0,pmax/4);
htotEdep_preshower_module[i]=new TH1F(Form("htotEdep_preshower_module%d",i),Form("ec preshower module%d;totEdep(MeV);",i),150,0,150);
prescin_vs_scin_hist_module[i] =new TH2F(Form("prescin_vs_scin_hist_module%d",i), Form("ec module%d;shower scin(MeV);preshower scin (MeV)",i),250,0,pmax,100,0,250);
presh_htotEdep_ec_module[i]=new TH1F(Form("presh_htotEdep_ec_module%d",i),Form("preshower scin module%d;totEdep_scin(MeV);",i),pbins,0,pmax/10);
presh_htotEdepB_ec_module[i]=new TH1F(Form("presh_htotEdepB_ec_module%d",i),Form("preshower scin module%d;totEdepB_scin(MeV);",i),pbins,0,pmax/10);
presh_htotEdepEnd_ec_module[i]=new TH1F(Form("presh_htotEdepEnd_ec_module%d",i),Form("preshower scin module%d;totEdepEnd_scin(MeV);",i),pbins,0,pmax/10);
}
TFile *file=new TFile(input_filename.c_str());
if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
}
else cout << "open file " << input_filename << endl;    

TTree *tree_header = (TTree*) file->Get("header");
vector <int> *evn=0,*evn_type=0;
vector <double> *beamPol=0;
 vector <int> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0; //var8 is the rate
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

TTree *tree_solid_ec = (TTree*) file->Get("solid_ec");
TTree *tree_solid_ec_ps = (TTree*) file->Get("solid_ec_ps");
cout<<"so far so good"<<endl;
setup_tree_solid_ec(tree_solid_ec,tree_solid_ec_ps);
int nevent = (int)tree_generated->GetEntries();
int nselected = 0;
cout << "nevent " << nevent << endl;
int trigger=0;
for (Int_t i=0;i<nevent;i++) { 
// for (Int_t i=0;i<2;i++) { 
  cout << i << "\r";
//   cout << i << "\n";

  tree_header->GetEntry(i);
  
  tree_generated->GetEntry(i);  
  int pid_gen=0;
  double r_gen=0,theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
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
      r_gen=sqrt(gen_vx->at(j)*gen_vx->at(j)+gen_vy->at(j)*gen_vy->at(j));
//       cout << "p_gen " << p_gen << endl;
  }

    tree_flux->GetEntry(i);  
   //if(r_gen>1300 && r_gen<1320){ 
   //if(r_gen>1255 && r_gen<1275){ 
   //if(r_gen>1251 && r_gen<1271){ 
   //if(vx_gen>-361&& vx_gen<-341 && vy_gen>-1180 && vy_gen<-1160){ 
//if(vx_gen>-401&& vx_gen<-381 && vy_gen>-1180 && vy_gen<-1160){ //y2cm rightmodule
//if(vx_gen>-457&& vx_gen<-437 && vy_gen>-1083 && vy_gen<-1063){ //y2cm topmodule
//if(vx_gen>-457&& vx_gen<-437 && vy_gen>-1123 && vy_gen<-1103){ //center topmodule
//if(vx_gen>-513 && vx_gen<-493 && vy_gen>-1220 && vy_gen<-1200){ //center leftmodule
//if(vx_gen>-401&& vx_gen<-381 && vy_gen>-1220 && vy_gen<-1200){ //center rightmodule

  
// if(r_gen>1227.5 && r_gen<1287.5){ 
  //if(r_gen>1217.5 && r_gen<1297.5){ 
    for (Int_t j=0;j<flux_hitn->size();j++) {
      int detector_ID=flux_id->at(j)/1000000;
      int subdetector_ID=(flux_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;
      int component_ID=flux_id->at(j)%10000;             
      double p_flux=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j));
    //cout<<"tid="<<flux_tid->at(j)<<"mtid="<<flux_mtid->at(j)<<endl;
    if(flux_pid->at(j)==22 || flux_pid->at(j)==11 ){
          trigger=1;
	  hp_gen_flux->Fill(p_gen,p_flux);
     }else{
          trigger=0;
     }
  }      
 //if(trigger==1){												
  tree_solid_ec->GetEntry(i);  
  tree_solid_ec_ps->GetEntry(i);  
  double totEdep_ec=0, Edep_ec_module1=0, Edep_ec_module2=0, Edep_ec_module3=0, EdepB_ec_module1=0, EdepB_ec_module2=0, EdepB_ec_module3=0, EdepEnd_ec_module1=0, EdepEnd_ec_module2=0, EdepEnd_ec_module3=0;
   process_tree_solid_ec(tree_solid_ec,totEdep_ec,Edep_ec_module1,Edep_ec_module2,Edep_ec_module3,EdepB_ec_module1,EdepB_ec_module2,EdepB_ec_module3,EdepEnd_ec_module1,EdepEnd_ec_module2,EdepEnd_ec_module3);
  double totEdep_ec_lead=0, Edep_ec_lead_module1=0, Edep_ec_lead_module2=0, Edep_ec_lead_module3=0;
   process_tree_solid_ec_lead(tree_solid_ec,totEdep_ec_lead,Edep_ec_lead_module1,Edep_ec_lead_module2,Edep_ec_lead_module3);
  double totEdep_ec_prelead=0, Edep_ec_prelead_module1=0, Edep_ec_prelead_module2=0, Edep_ec_prelead_module3=0;
   process_tree_solid_ec_prelead(tree_solid_ec,totEdep_ec_prelead,Edep_ec_prelead_module1,Edep_ec_prelead_module2,Edep_ec_prelead_module3);
  double totEdep_ec_preshower=0, Edep_ec_preshower_module1=0, Edep_ec_preshower_module2=0, Edep_ec_preshower_module3=0,EdepB_ec_preshower_module1=0, EdepB_ec_preshower_module2=0, EdepB_ec_preshower_module3=0,EdepEnd_ec_preshower_module1=0, EdepEnd_ec_preshower_module2=0, EdepEnd_ec_preshower_module3=0;
   process_tree_solid_ec_preshower(tree_solid_ec,totEdep_ec_preshower,Edep_ec_preshower_module1,Edep_ec_preshower_module2,Edep_ec_preshower_module3,EdepB_ec_preshower_module1,EdepB_ec_preshower_module2,EdepB_ec_preshower_module3,EdepEnd_ec_preshower_module1,EdepEnd_ec_preshower_module2,EdepEnd_ec_preshower_module3);
  double totEdep_ec_Al=0, Edep_ec_Al_module1=0, Edep_ec_Al_module2=0, Edep_ec_Al_module3=0;
   process_tree_solid_ec_Al(tree_solid_ec,totEdep_ec_Al,Edep_ec_Al_module1,Edep_ec_Al_module2,Edep_ec_Al_module3);
  double totEdep_ec_Al2=0, Edep_ec_Al2_module1=0,Edep_ec_Al2_module2=0,Edep_ec_Al2_module3=0;
   process_tree_solid_ec_Al2(tree_solid_ec,totEdep_ec_Al2,Edep_ec_Al2_module1,Edep_ec_Al2_module2,Edep_ec_Al2_module3);
  double totEdep_ec_Tylar1=0,Edep_ec_Tylar1_module1=0,Edep_ec_Tylar1_module2=0,Edep_ec_Tylar1_module3=0;
   process_tree_solid_ec_Tylar1(tree_solid_ec,totEdep_ec_Tylar1,Edep_ec_Tylar1_module1,Edep_ec_Tylar1_module2,Edep_ec_Tylar1_module3);
  double totEdep_ec_Tylar2=0,Edep_ec_Tylar2_module1=0,Edep_ec_Tylar2_module2=0,Edep_ec_Tylar2_module3=0;
   process_tree_solid_ec_Tylar2(tree_solid_ec,totEdep_ec_Tylar2,Edep_ec_Tylar2_module1,Edep_ec_Tylar2_module2,Edep_ec_Tylar2_module3);
   htotEdep_ec->Fill(totEdep_ec);
   htotEdep_ec_shower->Fill(totEdep_ec_lead+totEdep_ec+totEdep_ec_Tylar1+totEdep_ec_Tylar2);
   htotEdep_ec_shower_preshower->Fill(totEdep_ec_lead+totEdep_ec+totEdep_ec_Tylar1+totEdep_ec_Tylar2+totEdep_ec_preshower);
   htotEdep_ec_shower_preshower_scin->Fill(totEdep_ec+totEdep_ec_preshower);
   htotEdep_ec_total->Fill(totEdep_ec_Al2+totEdep_ec_lead+totEdep_ec+totEdep_ec_Tylar1+totEdep_ec_Tylar2+totEdep_ec_Al+totEdep_ec_preshower+totEdep_ec_prelead);
   prescin_vs_scin_hist->Fill(totEdep_ec,totEdep_ec_preshower);
   prescin_vs_scin_hist_module[0]->Fill((Edep_ec_module1+Edep_ec_module2+Edep_ec_module3),(Edep_ec_preshower_module1+Edep_ec_preshower_module2+Edep_ec_preshower_module3));
   prescin_vs_scin_hist_module[1]->Fill((Edep_ec_module1),(Edep_ec_preshower_module1));
   prescin_vs_scin_hist_module[2]->Fill((Edep_ec_module2),(Edep_ec_preshower_module2));
   prescin_vs_scin_hist_module[3]->Fill((Edep_ec_module3),(Edep_ec_preshower_module3));
   htotEdep_ec_lead->Fill(totEdep_ec_lead);
   htotEdep_ec_preshower->Fill(totEdep_ec_preshower);
   htotEdep_preshower_module[0]->Fill(Edep_ec_preshower_module1+Edep_ec_preshower_module2+Edep_ec_preshower_module3);
   htotEdep_preshower_module[1]->Fill(Edep_ec_preshower_module1);
   htotEdep_preshower_module[2]->Fill(Edep_ec_preshower_module2);
   htotEdep_preshower_module[3]->Fill(Edep_ec_preshower_module3);
   htotEdep_shower_module[0]->Fill(Edep_ec_module1+Edep_ec_lead_module1+Edep_ec_Tylar1_module1+Edep_ec_Tylar2_module1+Edep_ec_module2+Edep_ec_lead_module2+Edep_ec_Tylar1_module2+Edep_ec_Tylar2_module2+Edep_ec_module3+Edep_ec_lead_module3+Edep_ec_Tylar1_module3+Edep_ec_Tylar2_module3);
   htotEdep_shower_module[1]->Fill(Edep_ec_module1+Edep_ec_lead_module1+Edep_ec_Tylar1_module1+Edep_ec_Tylar2_module1);
   htotEdep_shower_module[2]->Fill(Edep_ec_module2+Edep_ec_lead_module2+Edep_ec_Tylar1_module2+Edep_ec_Tylar2_module2);
   htotEdep_shower_module[3]->Fill(Edep_ec_module3+Edep_ec_lead_module3+Edep_ec_Tylar1_module3+Edep_ec_Tylar2_module3);
   htotEdep_ec_module[0]->Fill(Edep_ec_module1+Edep_ec_module2+Edep_ec_module3);
   htotEdep_ec_module[1]->Fill(Edep_ec_module1);
   htotEdep_ec_module[2]->Fill(Edep_ec_module2);
   htotEdep_ec_module[3]->Fill(Edep_ec_module3);
   htotEdepB_ec_module[0]->Fill(EdepB_ec_module1+EdepB_ec_module2+EdepB_ec_module3);
   htotEdepB_ec_module[1]->Fill(EdepB_ec_module1);
   htotEdepB_ec_module[2]->Fill(EdepB_ec_module2);
   htotEdepB_ec_module[3]->Fill(EdepB_ec_module3);
   htotEdepEnd_ec_module[0]->Fill(EdepEnd_ec_module1+EdepEnd_ec_module2+EdepEnd_ec_module3);
   htotEdepEnd_ec_module[1]->Fill(EdepEnd_ec_module1);
   htotEdepEnd_ec_module[2]->Fill(EdepEnd_ec_module2);
   htotEdepEnd_ec_module[3]->Fill(EdepEnd_ec_module3);
   htotEdep_preshower_shower_module[0]->Fill(Edep_ec_module1+Edep_ec_preshower_module1+Edep_ec_module2+Edep_ec_preshower_module2+Edep_ec_module3+Edep_ec_preshower_module3);
   htotEdep_preshower_shower_module[1]->Fill(Edep_ec_module1+Edep_ec_preshower_module1);
   htotEdep_preshower_shower_module[2]->Fill(Edep_ec_module2+Edep_ec_preshower_module2);
   htotEdep_preshower_shower_module[3]->Fill(Edep_ec_module3+Edep_ec_preshower_module3);
   htotEdep_ec_Al->Fill(totEdep_ec_Al);  
   htotEdep_ec_Al_shower->Fill(totEdep_ec_Al2);
   htotEdep_ec_prelead->Fill(totEdep_ec_prelead);
   htotEdep_ec_Tylar->Fill(totEdep_ec_Tylar1+totEdep_ec_Tylar2);
   presh_htotEdep_ec_module[0]->Fill(Edep_ec_preshower_module1+Edep_ec_preshower_module2+Edep_ec_preshower_module3);
   presh_htotEdep_ec_module[1]->Fill(Edep_ec_preshower_module1);
   presh_htotEdep_ec_module[2]->Fill(Edep_ec_preshower_module2);
   presh_htotEdep_ec_module[3]->Fill(Edep_ec_preshower_module3);
   presh_htotEdepB_ec_module[0]->Fill(EdepB_ec_preshower_module1+EdepB_ec_preshower_module2+EdepB_ec_preshower_module3);
   presh_htotEdepB_ec_module[1]->Fill(EdepB_ec_preshower_module1);
   presh_htotEdepB_ec_module[2]->Fill(EdepB_ec_preshower_module2);
   presh_htotEdepB_ec_module[3]->Fill(EdepB_ec_preshower_module3);
   presh_htotEdepEnd_ec_module[0]->Fill(EdepEnd_ec_preshower_module1+EdepEnd_ec_preshower_module2+EdepEnd_ec_preshower_module3);
   presh_htotEdepEnd_ec_module[1]->Fill(EdepEnd_ec_preshower_module1);
   presh_htotEdepEnd_ec_module[2]->Fill(EdepEnd_ec_preshower_module2);
   presh_htotEdepEnd_ec_module[3]->Fill(EdepEnd_ec_preshower_module3);
 //   }
 //}
}
    f_outFile->Write();
    f_outFile->Close();
    file->Close();
}
