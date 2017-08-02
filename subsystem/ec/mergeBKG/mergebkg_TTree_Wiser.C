#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <new>
#include <cstdlib>
#include <math.h>
#include <functional>
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
using namespace std;
using std::vector;
using std::string;
using std::fstream;
#define __IO_MAXHIT 1000
void mergebkg_TTree()
{
  
 
  TFile *f1=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pimWiser_filenum100_1e6.root");
  TFile *f3=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pi0Wiser_filenum100_1e6.root");
  TFile *f4=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_dirty_normalized_pipWiser_filenum100_1e6.root");
  TFile *f5=new TFile("/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass7/background_solid_SIDIS_He3_BeamOnTargetEM_1e10_skim.root");
  TFile *f2 = new TFile("mergetree_SIDIS_allpions_total_wiser.root", "RECREATE");
  //calculate background rate at ECal frong vitual plane
  Double_t total_rate[4]={0};
  total_rate[0] = 4.15547e+08/100.0;//Hz Pi-   
  total_rate[1] = 7.28475e+08/100.0;//Hz Pi0   
  total_rate[2] = 3.93825e+08/100.0;//Hz Pi+    
  total_rate[3] = 1.36207e+10;	
  Double_t t[4]={0};
  Double_t detlaT[4]={0};
  detlaT[0] = 1e9/total_rate[0];
  detlaT[1] = 1e9/total_rate[1];
  detlaT[2] = 1e9/total_rate[2];
  detlaT[3] = 1e9/total_rate[3];
  // load background trees
  //TTree *generated_EM;
  Int_t simpid[4]={-211,111,211,1};//simpid=1 is the ebeam events
  
  //generated_pim = (TTree*)f1->Get("generated");
  TTree *flux_pim = (TTree*)f1->Get("flux");
  TTree *solid_ec_pim = (TTree*)f1->Get("solid_ec");
  //generated_pi0 = (TTree*)f3->Get("generated");
  TTree *flux_pi0 = (TTree*)f3->Get("flux");
  TTree *solid_ec_pi0 = (TTree*)f3->Get("solid_ec");
  //generated_pip = (TTree*)f4->Get("generated");
  TTree *flux_pip = (TTree*)f4->Get("flux");
  TTree *solid_ec_pip = (TTree*)f4->Get("solid_ec");
  //generated_EM = (TTree*)f5->Get("generated");
  TTree *flux_EM = (TTree*)f5->Get("flux");
  TTree *solid_ec_EM = (TTree*)f5->Get("solid_ec");
	
 TTree *output_flux = new TTree("output_flux", "output_flux"); 
 TTree *output_solid_ec = new TTree("output_solid_ec", "output_solid_ec");
 TTree *output_generate = new TTree("output_generate", "output_generate");
  Int_t fEv_simpid;
  Double_t fEvTimeStamp;
  Int_t fEvTimeWindow;
  output_generate->Branch("simpid",     &fEv_simpid,   "simpid/I");
  output_generate->Branch("ev.evtimestamp",  &fEvTimeStamp,   "ev.evtimestamp/D");
  output_generate->Branch("ev.evtimewindow",  &fEvTimeWindow,"ev.evtimewindow/I");
  int flux_hitn,flux_id[__IO_MAXHIT],flux_pid[__IO_MAXHIT],flux_mpid[__IO_MAXHIT],flux_tid[__IO_MAXHIT],flux_mtid[__IO_MAXHIT],flux_otid[__IO_MAXHIT];
  double flux_trackE[__IO_MAXHIT],flux_totEdep[__IO_MAXHIT],flux_avg_x[__IO_MAXHIT],flux_avg_y[__IO_MAXHIT],flux_avg_z[__IO_MAXHIT],flux_avg_lx[__IO_MAXHIT],flux_avg_ly[__IO_MAXHIT],flux_avg_lz[__IO_MAXHIT],flux_px[__IO_MAXHIT],flux_py[__IO_MAXHIT],flux_pz[__IO_MAXHIT],flux_vx[__IO_MAXHIT],flux_vy[__IO_MAXHIT],flux_vz[__IO_MAXHIT],flux_mvx[__IO_MAXHIT],flux_mvy[__IO_MAXHIT],flux_mvz[__IO_MAXHIT],flux_avg_t[__IO_MAXHIT];
  output_flux->Branch("hitn", &flux_hitn,"hitn/I");
  output_flux->Branch("id", &flux_id,"id[hitn]/I");
  output_flux->Branch("pid", &flux_pid,"pid[hitn]/I");
  output_flux->Branch("mpid", &flux_mpid,"mpid[hitn]/I");
  output_flux->Branch("tid", &flux_tid,"tid[hitn]/I");
  output_flux->Branch("mtid", &flux_mtid,"mtid[hitn]/I");
  output_flux->Branch("otid", &flux_otid,"otid[hitn]/I");
  output_flux->Branch("trackE", &flux_trackE,"trackE[hitn]/D");
  output_flux->Branch("totEdep", &flux_totEdep,"totEdep[hitn]/D");
  output_flux->Branch("avg_x", &flux_avg_x,"avg_x[hitn]/D");
  output_flux->Branch("avg_y", &flux_avg_y,"avg_y[hitn]/D");
  output_flux->Branch("avg_z", &flux_avg_z,"avg_z[hitn]/D");
  output_flux->Branch("avg_lx", &flux_avg_lx,"avg_lx[hitn]/D");
  output_flux->Branch("avg_ly", &flux_avg_ly,"avg_ly[hitn]/D");
  output_flux->Branch("avg_lz", &flux_avg_lz,"avg_lz[hitn]/D");
  output_flux->Branch("px", &flux_px,"px[hitn]/D");
  output_flux->Branch("py", &flux_py,"py[hitn]/D");
  output_flux->Branch("pz", &flux_pz,"pz[hitn]/D");
  output_flux->Branch("vx", &flux_vx,"vz[hitn]/D");
  output_flux->Branch("vy", &flux_vy,"vy[hitn]/D");
  output_flux->Branch("vz", &flux_vz,"vz[hitn]/D");
  output_flux->Branch("mvx", &flux_mvx,"mvx[hitn]/D");
  output_flux->Branch("mvy", &flux_mvy,"mvy[hitn]/D");
  output_flux->Branch("mvz", &flux_mvz,"mvz[hitn]/D");
  output_flux->Branch("avg_t", &flux_avg_t,"avg_t[hitn]/D");


 int solid_ec_pid[__IO_MAXHIT],solid_ec_mpid[__IO_MAXHIT],solid_ec_tid[__IO_MAXHIT],solid_ec_mtid[__IO_MAXHIT],solid_ec_otid[__IO_MAXHIT],solid_ec_id[__IO_MAXHIT],solid_ec_hitn;
 double solid_ec_trackE[__IO_MAXHIT],solid_ec_totEdep[__IO_MAXHIT],solid_ec_avg_x[__IO_MAXHIT],solid_ec_avg_y[__IO_MAXHIT],solid_ec_avg_z[__IO_MAXHIT],solid_ec_avg_lx[__IO_MAXHIT],solid_ec_avg_ly[__IO_MAXHIT],solid_ec_avg_lz[__IO_MAXHIT],solid_ec_px[__IO_MAXHIT],solid_ec_py[__IO_MAXHIT],solid_ec_pz[__IO_MAXHIT],solid_ec_vx[__IO_MAXHIT],solid_ec_vy[__IO_MAXHIT],solid_ec_vz[__IO_MAXHIT],solid_ec_mvx[__IO_MAXHIT],solid_ec_mvy[__IO_MAXHIT],solid_ec_mvz[__IO_MAXHIT],solid_ec_avg_t[__IO_MAXHIT];
  output_solid_ec->Branch("hitn", &solid_ec_hitn,"hitn/I");
  output_solid_ec->Branch("id", &solid_ec_id,"id[hitn]/I");
  output_solid_ec->Branch("pid", &solid_ec_pid,"pid[hitn]/I");
  output_solid_ec->Branch("mpid", &solid_ec_mpid,"mpid[hitn]/I");
  output_solid_ec->Branch("tid", &solid_ec_tid,"tid[hitn]/I");
  output_solid_ec->Branch("mtid", &solid_ec_mtid,"mtid[hitn]/I");
  output_solid_ec->Branch("otid", &solid_ec_otid,"otid[hitn]/I");
  output_solid_ec->Branch("trackE", &solid_ec_trackE,"trackE[hitn]/D");
  output_solid_ec->Branch("totEdep", &solid_ec_totEdep,"totEdep[hitn]/D");
  output_solid_ec->Branch("avg_x", &solid_ec_avg_x,"avg_x[hitn]/D");
  output_solid_ec->Branch("avg_y", &solid_ec_avg_y,"avg_y[hitn]/D");
  output_solid_ec->Branch("avg_z", &solid_ec_avg_z,"avg_z[hitn]/D");
  output_solid_ec->Branch("avg_lx", &solid_ec_avg_lx,"avg_lx[hitn]/D");
  output_solid_ec->Branch("avg_ly", &solid_ec_avg_ly,"avg_ly[hitn]/D");
  output_solid_ec->Branch("avg_lz", &solid_ec_avg_lz,"avg_lz[hitn]/D");
  output_solid_ec->Branch("px", &solid_ec_px,"px[hitn]/D");
  output_solid_ec->Branch("py", &solid_ec_py,"py[hitn]/D");
  output_solid_ec->Branch("pz", &solid_ec_pz,"pz[hitn]/D");
  output_solid_ec->Branch("vx", &solid_ec_vx,"vz[hitn]/D");
  output_solid_ec->Branch("vy", &solid_ec_vy,"vy[hitn]/D");
  output_solid_ec->Branch("vz", &solid_ec_vz,"vz[hitn]/D");
  output_solid_ec->Branch("mvx", &solid_ec_mvx,"mvx[hitn]/D");
  output_solid_ec->Branch("mvy", &solid_ec_mvy,"mvy[hitn]/D");
  output_solid_ec->Branch("mvz", &solid_ec_mvz,"mvz[hitn]/D");
  output_solid_ec->Branch("avg_t", &solid_ec_avg_t,"avg_t[hitn]/D");



 // get cloned output_flux's branches
  vector<int> *Mflux_hitn[4],*Mflux_id[4],*Mflux_pid[4],*Mflux_mpid[4],*Mflux_tid[4],*Mflux_mtid[4],*Mflux_otid[4];
  vector<double> *Mflux_trackE[4],*Mflux_totEdep[4],*Mflux_avg_x[4],*Mflux_avg_y[4],*Mflux_avg_z[4],*Mflux_avg_lx[4],*Mflux_avg_ly[4],*Mflux_avg_lz[4],*Mflux_px[4],*Mflux_py[4],*Mflux_pz[4],*Mflux_vx[4],*Mflux_vy[4],*Mflux_vz[4],*Mflux_mvx[4],*Mflux_mvy[4],*Mflux_mvz[4],*Mflux_avg_t[4];
  
  flux_EM->SetBranchAddress("hitn", &Mflux_hitn[0]);
  flux_EM->SetBranchAddress("id", &Mflux_id[0]);
  flux_EM->SetBranchAddress("pid", &Mflux_pid[0]);
  flux_EM->SetBranchAddress("mpid", &Mflux_mpid[0]);
  flux_EM->SetBranchAddress("tid", &Mflux_tid[0]);
  flux_EM->SetBranchAddress("mtid", &Mflux_mtid[0]);
  flux_EM->SetBranchAddress("otid", &Mflux_otid[0]);
  flux_EM->SetBranchAddress("trackE", &Mflux_trackE[0]);
  flux_EM->SetBranchAddress("totEdep", &Mflux_totEdep[0]);
  flux_EM->SetBranchAddress("avg_x", &Mflux_avg_x[0]);
  flux_EM->SetBranchAddress("avg_y", &Mflux_avg_y[0]);
  flux_EM->SetBranchAddress("avg_z", &Mflux_avg_z[0]);
  flux_EM->SetBranchAddress("avg_lx", &Mflux_avg_lx[0]);
  flux_EM->SetBranchAddress("avg_ly", &Mflux_avg_ly[0]);
  flux_EM->SetBranchAddress("avg_lz", &Mflux_avg_lz[0]);
  flux_EM->SetBranchAddress("px", &Mflux_px[0]);
  flux_EM->SetBranchAddress("py", &Mflux_py[0]);
  flux_EM->SetBranchAddress("pz", &Mflux_pz[0]);
  flux_EM->SetBranchAddress("vx", &Mflux_vx[0]);
  flux_EM->SetBranchAddress("vy", &Mflux_vy[0]);
  flux_EM->SetBranchAddress("vz", &Mflux_vz[0]);
  flux_EM->SetBranchAddress("mvx", &Mflux_mvx[0]);
  flux_EM->SetBranchAddress("mvy", &Mflux_mvy[0]);
  flux_EM->SetBranchAddress("mvz", &Mflux_mvz[0]);
  flux_EM->SetBranchAddress("avg_t", &Mflux_avg_t[0]);



  flux_pim->SetBranchAddress("hitn", &Mflux_hitn[1]);
  flux_pim->SetBranchAddress("id", &Mflux_id[1]);
  flux_pim->SetBranchAddress("pid", &Mflux_pid[1]);
  flux_pim->SetBranchAddress("mpid", &Mflux_mpid[1]);
  flux_pim->SetBranchAddress("tid", &Mflux_tid[1]);
  flux_pim->SetBranchAddress("mtid", &Mflux_mtid[1]);
  flux_pim->SetBranchAddress("otid", &Mflux_otid[1]);
  flux_pim->SetBranchAddress("trackE", &Mflux_trackE[1]);
  flux_pim->SetBranchAddress("totEdep", &Mflux_totEdep[1]);
  flux_pim->SetBranchAddress("avg_x", &Mflux_avg_x[1]);
  flux_pim->SetBranchAddress("avg_y", &Mflux_avg_y[1]);
  flux_pim->SetBranchAddress("avg_z", &Mflux_avg_z[1]);
  flux_pim->SetBranchAddress("avg_lx", &Mflux_avg_lx[1]);
  flux_pim->SetBranchAddress("avg_ly", &Mflux_avg_ly[1]);
  flux_pim->SetBranchAddress("avg_lz", &Mflux_avg_lz[1]);
  flux_pim->SetBranchAddress("px", &Mflux_px[1]);
  flux_pim->SetBranchAddress("py", &Mflux_py[1]);
  flux_pim->SetBranchAddress("pz", &Mflux_pz[1]);
  flux_pim->SetBranchAddress("vx", &Mflux_vx[1]);
  flux_pim->SetBranchAddress("vy", &Mflux_vy[1]);
  flux_pim->SetBranchAddress("vz", &Mflux_vz[1]);
  flux_pim->SetBranchAddress("mvx", &Mflux_mvx[1]);
  flux_pim->SetBranchAddress("mvy", &Mflux_mvy[1]);
  flux_pim->SetBranchAddress("mvz", &Mflux_mvz[1]);
  flux_pim->SetBranchAddress("avg_t", &Mflux_avg_t[1]);



  flux_pi0->SetBranchAddress("hitn", &Mflux_hitn[2]);
  flux_pi0->SetBranchAddress("id", &Mflux_id[2]);
  flux_pi0->SetBranchAddress("pid", &Mflux_pid[2]);
  flux_pi0->SetBranchAddress("mpid", &Mflux_mpid[2]);
  flux_pi0->SetBranchAddress("tid", &Mflux_tid[2]);
  flux_pi0->SetBranchAddress("mtid", &Mflux_mtid[2]);
  flux_pi0->SetBranchAddress("otid", &Mflux_otid[2]);
  flux_pi0->SetBranchAddress("trackE", &Mflux_trackE[2]);
  flux_pi0->SetBranchAddress("totEdep", &Mflux_totEdep[2]);
  flux_pi0->SetBranchAddress("avg_x", &Mflux_avg_x[2]);
  flux_pi0->SetBranchAddress("avg_y", &Mflux_avg_y[2]);
  flux_pi0->SetBranchAddress("avg_z", &Mflux_avg_z[2]);
  flux_pi0->SetBranchAddress("avg_lx", &Mflux_avg_lx[2]);
  flux_pi0->SetBranchAddress("avg_ly", &Mflux_avg_ly[2]);
  flux_pi0->SetBranchAddress("avg_lz", &Mflux_avg_lz[2]);
  flux_pi0->SetBranchAddress("px", &Mflux_px[2]);
  flux_pi0->SetBranchAddress("py", &Mflux_py[2]);
  flux_pi0->SetBranchAddress("pz", &Mflux_pz[2]);
  flux_pi0->SetBranchAddress("vx", &Mflux_vx[2]);
  flux_pi0->SetBranchAddress("vy", &Mflux_vy[2]);
  flux_pi0->SetBranchAddress("vz", &Mflux_vz[2]);
  flux_pi0->SetBranchAddress("mvx", &Mflux_mvx[2]);
  flux_pi0->SetBranchAddress("mvy", &Mflux_mvy[2]);
  flux_pi0->SetBranchAddress("mvz", &Mflux_mvz[2]);
  flux_pi0->SetBranchAddress("avg_t", &Mflux_avg_t[2]);



  flux_pip->SetBranchAddress("hitn", &Mflux_hitn[3]);
  flux_pip->SetBranchAddress("id", &Mflux_id[3]);
  flux_pip->SetBranchAddress("pid", &Mflux_pid[3]);
  flux_pip->SetBranchAddress("mpid", &Mflux_mpid[3]);
  flux_pip->SetBranchAddress("tid", &Mflux_tid[3]);
  flux_pip->SetBranchAddress("mtid", &Mflux_mtid[3]);
  flux_pip->SetBranchAddress("otid", &Mflux_otid[3]);
  flux_pip->SetBranchAddress("trackE", &Mflux_trackE[3]);
  flux_pip->SetBranchAddress("totEdep", &Mflux_totEdep[3]);
  flux_pip->SetBranchAddress("avg_x", &Mflux_avg_x[3]);
  flux_pip->SetBranchAddress("avg_y", &Mflux_avg_y[3]);
  flux_pip->SetBranchAddress("avg_z", &Mflux_avg_z[3]);
  flux_pip->SetBranchAddress("avg_lx", &Mflux_avg_lx[3]);
  flux_pip->SetBranchAddress("avg_ly", &Mflux_avg_ly[3]);
  flux_pip->SetBranchAddress("avg_lz", &Mflux_avg_lz[3]);
  flux_pip->SetBranchAddress("px", &Mflux_px[3]);
  flux_pip->SetBranchAddress("py", &Mflux_py[3]);
  flux_pip->SetBranchAddress("pz", &Mflux_pz[3]);
  flux_pip->SetBranchAddress("vx", &Mflux_vx[3]);
  flux_pip->SetBranchAddress("vy", &Mflux_vy[3]);
  flux_pip->SetBranchAddress("vz", &Mflux_vz[3]);
  flux_pip->SetBranchAddress("mvx", &Mflux_mvx[3]);
  flux_pip->SetBranchAddress("mvy", &Mflux_mvy[3]);
  flux_pip->SetBranchAddress("mvz", &Mflux_mvz[3]);
  flux_pip->SetBranchAddress("avg_t", &Mflux_avg_t[3]);
  // 
// get cloned output_solid_ec's branches
 vector<int> *Msolid_ec_pid[4],*Msolid_ec_mpid[4],*Msolid_ec_tid[4],*Msolid_ec_mtid[4],*Msolid_ec_otid[4],*Msolid_ec_id[4],*Msolid_ec_hitn[4];
 vector<double> *Msolid_ec_trackE[4],*Msolid_ec_totEdep[4],*Msolid_ec_avg_x[4],*Msolid_ec_avg_y[4],*Msolid_ec_avg_z[4],*Msolid_ec_avg_lx[4],*Msolid_ec_avg_ly[4],*Msolid_ec_avg_lz[4],*Msolid_ec_px[4],*Msolid_ec_py[4],*Msolid_ec_pz[4],*Msolid_ec_vx[4],*Msolid_ec_vy[4],*Msolid_ec_vz[4],*Msolid_ec_mvx[4],*Msolid_ec_mvy[4],*Msolid_ec_mvz[4],*Msolid_ec_avg_t[4];
 solid_ec_EM->SetBranchAddress("pid", &Msolid_ec_pid[0]);
 solid_ec_EM->SetBranchAddress("mpid", &Msolid_ec_mpid[0]);
 solid_ec_EM->SetBranchAddress("tid", &Msolid_ec_tid[0]);
 solid_ec_EM->SetBranchAddress("mtid", &Msolid_ec_mtid[0]);
 solid_ec_EM->SetBranchAddress("otid", &Msolid_ec_otid[0]);
 solid_ec_EM->SetBranchAddress("trackE", &Msolid_ec_trackE[0]);
 solid_ec_EM->SetBranchAddress("totEdep", &Msolid_ec_totEdep[0]);
 solid_ec_EM->SetBranchAddress("avg_x", &Msolid_ec_avg_x[0]);
 solid_ec_EM->SetBranchAddress("avg_y", &Msolid_ec_avg_y[0]);
 solid_ec_EM->SetBranchAddress("avg_z", &Msolid_ec_avg_z[0]);
 solid_ec_EM->SetBranchAddress("avg_lx", &Msolid_ec_avg_lx[0]);
 solid_ec_EM->SetBranchAddress("avg_ly", &Msolid_ec_avg_ly[0]);
 solid_ec_EM->SetBranchAddress("avg_lz", &Msolid_ec_avg_lz[0]);
 solid_ec_EM->SetBranchAddress("px", &Msolid_ec_px[0]);
 solid_ec_EM->SetBranchAddress("py", &Msolid_ec_py[0]);
 solid_ec_EM->SetBranchAddress("pz", &Msolid_ec_pz[0]);
 solid_ec_EM->SetBranchAddress("vx", &Msolid_ec_vx[0]);
 solid_ec_EM->SetBranchAddress("vy", &Msolid_ec_vy[0]);
 solid_ec_EM->SetBranchAddress("vz", &Msolid_ec_vz[0]);
 solid_ec_EM->SetBranchAddress("mvx", &Msolid_ec_mvx[0]);
 solid_ec_EM->SetBranchAddress("mvy", &Msolid_ec_mvy[0]);
 solid_ec_EM->SetBranchAddress("mvz", &Msolid_ec_mvz[0]);
 solid_ec_EM->SetBranchAddress("avg_t", &Msolid_ec_avg_t[0]);
 solid_ec_EM->SetBranchAddress("id", &Msolid_ec_id[0]);
 solid_ec_EM->SetBranchAddress("hitn", &Msolid_ec_hitn[0]);  


 solid_ec_pim->SetBranchAddress("pid", &Msolid_ec_pid[1]);
 solid_ec_pim->SetBranchAddress("mpid", &Msolid_ec_mpid[1]);
 solid_ec_pim->SetBranchAddress("tid", &Msolid_ec_tid[1]);
 solid_ec_pim->SetBranchAddress("mtid", &Msolid_ec_mtid[1]);
 solid_ec_pim->SetBranchAddress("otid", &Msolid_ec_otid[1]);
 solid_ec_pim->SetBranchAddress("trackE", &Msolid_ec_trackE[1]);
 solid_ec_pim->SetBranchAddress("totEdep", &Msolid_ec_totEdep[1]);
 solid_ec_pim->SetBranchAddress("avg_x", &Msolid_ec_avg_x[1]);
 solid_ec_pim->SetBranchAddress("avg_y", &Msolid_ec_avg_y[1]);
 solid_ec_pim->SetBranchAddress("avg_z", &Msolid_ec_avg_z[1]);
 solid_ec_pim->SetBranchAddress("avg_lx", &Msolid_ec_avg_lx[1]);
 solid_ec_pim->SetBranchAddress("avg_ly", &Msolid_ec_avg_ly[1]);
 solid_ec_pim->SetBranchAddress("avg_lz", &Msolid_ec_avg_lz[1]);
 solid_ec_pim->SetBranchAddress("px", &Msolid_ec_px[1]);
 solid_ec_pim->SetBranchAddress("py", &Msolid_ec_py[1]);
 solid_ec_pim->SetBranchAddress("pz", &Msolid_ec_pz[1]);
 solid_ec_pim->SetBranchAddress("vx", &Msolid_ec_vx[1]);
 solid_ec_pim->SetBranchAddress("vy", &Msolid_ec_vy[1]);
 solid_ec_pim->SetBranchAddress("vz", &Msolid_ec_vz[1]);
 solid_ec_pim->SetBranchAddress("mvx", &Msolid_ec_mvx[1]);
 solid_ec_pim->SetBranchAddress("mvy", &Msolid_ec_mvy[1]);
 solid_ec_pim->SetBranchAddress("mvz", &Msolid_ec_mvz[1]);
 solid_ec_pim->SetBranchAddress("avg_t", &Msolid_ec_avg_t[1]);
 solid_ec_pim->SetBranchAddress("id", &Msolid_ec_id[1]);
 solid_ec_pim->SetBranchAddress("hitn", &Msolid_ec_hitn[1]);  

 solid_ec_pi0->SetBranchAddress("pid", &Msolid_ec_pid[2]);
 solid_ec_pi0->SetBranchAddress("mpid", &Msolid_ec_mpid[2]);
 solid_ec_pi0->SetBranchAddress("tid", &Msolid_ec_tid[2]);
 solid_ec_pi0->SetBranchAddress("mtid", &Msolid_ec_mtid[2]);
 solid_ec_pi0->SetBranchAddress("otid", &Msolid_ec_otid[2]);
 solid_ec_pi0->SetBranchAddress("trackE", &Msolid_ec_trackE[2]);
 solid_ec_pi0->SetBranchAddress("totEdep", &Msolid_ec_totEdep[2]);
 solid_ec_pi0->SetBranchAddress("avg_x", &Msolid_ec_avg_x[2]);
 solid_ec_pi0->SetBranchAddress("avg_y", &Msolid_ec_avg_y[2]);
 solid_ec_pi0->SetBranchAddress("avg_z", &Msolid_ec_avg_z[2]);
 solid_ec_pi0->SetBranchAddress("avg_lx", &Msolid_ec_avg_lx[2]);
 solid_ec_pi0->SetBranchAddress("avg_ly", &Msolid_ec_avg_ly[2]);
 solid_ec_pi0->SetBranchAddress("avg_lz", &Msolid_ec_avg_lz[2]);
 solid_ec_pi0->SetBranchAddress("px", &Msolid_ec_px[2]);
 solid_ec_pi0->SetBranchAddress("py", &Msolid_ec_py[2]);
 solid_ec_pi0->SetBranchAddress("pz", &Msolid_ec_pz[2]);
 solid_ec_pi0->SetBranchAddress("vx", &Msolid_ec_vx[2]);
 solid_ec_pi0->SetBranchAddress("vy", &Msolid_ec_vy[2]);
 solid_ec_pi0->SetBranchAddress("vz", &Msolid_ec_vz[2]);
 solid_ec_pi0->SetBranchAddress("mvx", &Msolid_ec_mvx[2]);
 solid_ec_pi0->SetBranchAddress("mvy", &Msolid_ec_mvy[2]);
 solid_ec_pi0->SetBranchAddress("mvz", &Msolid_ec_mvz[2]);
 solid_ec_pi0->SetBranchAddress("avg_t", &Msolid_ec_avg_t[2]);
 solid_ec_pi0->SetBranchAddress("id", &Msolid_ec_id[2]);
 solid_ec_pi0->SetBranchAddress("hitn", &Msolid_ec_hitn[2]); 

 solid_ec_pip->SetBranchAddress("pid", &Msolid_ec_pid[3]);
 solid_ec_pip->SetBranchAddress("mpid", &Msolid_ec_mpid[3]);
 solid_ec_pip->SetBranchAddress("tid", &Msolid_ec_tid[3]);
 solid_ec_pip->SetBranchAddress("mtid", &Msolid_ec_mtid[3]);
 solid_ec_pip->SetBranchAddress("otid", &Msolid_ec_otid[3]);
 solid_ec_pip->SetBranchAddress("trackE", &Msolid_ec_trackE[3]);
 solid_ec_pip->SetBranchAddress("totEdep", &Msolid_ec_totEdep[3]);
 solid_ec_pip->SetBranchAddress("avg_x", &Msolid_ec_avg_x[3]);
 solid_ec_pip->SetBranchAddress("avg_y", &Msolid_ec_avg_y[3]);
 solid_ec_pip->SetBranchAddress("avg_z", &Msolid_ec_avg_z[3]);
 solid_ec_pip->SetBranchAddress("avg_lx", &Msolid_ec_avg_lx[3]);
 solid_ec_pip->SetBranchAddress("avg_ly", &Msolid_ec_avg_ly[3]);
 solid_ec_pip->SetBranchAddress("avg_lz", &Msolid_ec_avg_lz[3]);
 solid_ec_pip->SetBranchAddress("px", &Msolid_ec_px[3]);
 solid_ec_pip->SetBranchAddress("py", &Msolid_ec_py[3]);
 solid_ec_pip->SetBranchAddress("pz", &Msolid_ec_pz[3]);
 solid_ec_pip->SetBranchAddress("vx", &Msolid_ec_vx[3]);
 solid_ec_pip->SetBranchAddress("vy", &Msolid_ec_vy[3]);
 solid_ec_pip->SetBranchAddress("vz", &Msolid_ec_vz[3]);
 solid_ec_pip->SetBranchAddress("mvx", &Msolid_ec_mvx[3]);
 solid_ec_pip->SetBranchAddress("mvy", &Msolid_ec_mvy[3]);
 solid_ec_pip->SetBranchAddress("mvz", &Msolid_ec_mvz[3]);
 solid_ec_pip->SetBranchAddress("avg_t", &Msolid_ec_avg_t[3]);
 solid_ec_pip->SetBranchAddress("id", &Msolid_ec_id[3]);
 solid_ec_pip->SetBranchAddress("hitn", &Msolid_ec_hitn[3]); 
  
vector<double> timeT1;
vector<double> timeT2;
vector<double> timeT3;
vector<double> timeT4;
double totalT1=0,totalT2=0, totalT3=0,totalT4=0;
int nentries= flux_pim->GetEntries();
 for(int i=0; i<nentries; i++){
      totalT1 += detlaT[3];
      timeT1.push_back(totalT1);
      totalT2 += detlaT[0];
      timeT2.push_back(totalT2);
      totalT3 += detlaT[1];
      timeT3.push_back(totalT3);
      totalT4 += detlaT[2];
      timeT4.push_back(totalT4);
}

int n[3]={0},m=0,d=0,e=0,q=0;
  //std::vector<double> flux_timestamp;
  //output_flux->Branch("flux_timestamp", &flux_timestamp);
  //output_flux->SetBranchAddress("flux_timestamp", &flux_timestamp);
  
  long long int fNentries=flux_EM->GetEntries();
  //nentries[0]= (Int_t)flux_pim->GetEntries();
  //nentries[1]= (Int_t)flux_pi0->GetEntries();
  //nentries[2]= (Int_t)flux_pip->GetEntries();

 for (int i=0; i<fNentries; i++){
  
 n[0]= (int)timeT2[d]/detlaT[3]-1;
 n[1]= (int)timeT3[e]/detlaT[3]-1; 
 n[2]= (int)timeT4[q]/detlaT[3]-1;
 //cout<<"m"<<m<<"timeT2"<<n[0]<<"timeT3="<<n[1]<<"timeT4="<<n[2]<<endl;

if(m != n[0] || m != n[1] || m != n[2]){
  fEvTimeWindow = (Int_t)timeT1[m]/30;
  flux_EM->GetEntry(m);
  solid_ec_EM->GetEntry(m);
  fEvTimeStamp=timeT1[m];
  fEv_simpid=1;
 // cout<<"Mflux_hitn[0]->size()="<<Mflux_hitn[0]->size()<<endl;
  for (int j = 0; j<Mflux_hitn[0]->size(); j++){
  flux_hitn=Mflux_hitn[0]->at(j);
  //cout<<"Mflux_hitn[0]->at(j)=="<<Mflux_hitn[0]->at(j)<<"Mflux_hitn[0]->size()="<<Mflux_hitn[0]->size()<<endl;
  flux_id[j]=Mflux_id[0]->at(j);
  flux_pid[j]=Mflux_pid[0]->at(j);
  flux_mpid[j]=Mflux_mpid[0]->at(j);
  flux_tid[j]=Mflux_tid[0]->at(j);
  flux_mtid[j]=Mflux_mtid[0]->at(j);
  flux_otid[j]=Mflux_otid[0]->at(j);
  flux_trackE[j]=Mflux_trackE[0]->at(j);
  flux_totEdep[j]=Mflux_totEdep[0]->at(j);
  flux_avg_x[j]=Mflux_avg_x[0]->at(j);
  flux_avg_y[j]=Mflux_avg_y[0]->at(j);
  flux_avg_z[j]=Mflux_avg_z[0]->at(j);
  flux_avg_lx[j]=Mflux_avg_lx[0]->at(j);
  flux_avg_ly[j]=Mflux_avg_ly[0]->at(j);
  flux_avg_lz[j]=Mflux_avg_lz[0]->at(j);
  flux_px[j]=Mflux_px[0]->at(j);
  flux_py[j]=Mflux_py[0]->at(j);
  flux_pz[j]=Mflux_pz[0]->at(j);
  flux_vx[j]=Mflux_vx[0]->at(j);
  flux_vy[j]=Mflux_vy[0]->at(j);
  flux_vz[j]=Mflux_vz[0]->at(j);
  flux_mvx[j]=Mflux_mvx[0]->at(j);
  flux_mvy[j]=Mflux_mvy[0]->at(j);
  flux_mvz[j]=Mflux_mvz[0]->at(j);
  flux_avg_t[j]=Mflux_avg_t[0]->at(j);
  }
 for (int j = 0; j<Msolid_ec_hitn[0]->size(); j++){
   solid_ec_hitn =Msolid_ec_hitn[0]->at(j);
  //solid_ec_hitn[j]=Msolid_ec_hitn[0]->at(j);
  solid_ec_id[j]=Msolid_ec_id[0]->at(j);
  solid_ec_pid[j]=Msolid_ec_pid[0]->at(j);
  solid_ec_mpid[j]=Msolid_ec_mpid[0]->at(j);
  solid_ec_tid[j]=Msolid_ec_tid[0]->at(j);
  solid_ec_mtid[j]=Msolid_ec_mtid[0]->at(j);
  solid_ec_otid[j]=Msolid_ec_otid[0]->at(j);
  solid_ec_trackE[j]=Msolid_ec_trackE[0]->at(j);
  solid_ec_totEdep[j]=Msolid_ec_totEdep[0]->at(j);
  solid_ec_avg_x[j]=Msolid_ec_avg_x[0]->at(j);
  solid_ec_avg_y[j]=Msolid_ec_avg_y[0]->at(j);
  solid_ec_avg_z[j]=Msolid_ec_avg_z[0]->at(j);
  solid_ec_avg_lx[j]=Msolid_ec_avg_lx[0]->at(j);
  solid_ec_avg_ly[j]=Msolid_ec_avg_ly[0]->at(j);
  solid_ec_avg_lz[j]=Msolid_ec_avg_lz[0]->at(j);
  solid_ec_px[j]=Msolid_ec_px[0]->at(j);
  solid_ec_py[j]=Msolid_ec_py[0]->at(j);
  solid_ec_pz[j]=Msolid_ec_pz[0]->at(j);
  solid_ec_vx[j]=Msolid_ec_vx[0]->at(j);
  solid_ec_vy[j]=Msolid_ec_vy[0]->at(j);
  solid_ec_vz[j]=Msolid_ec_vz[0]->at(j);
  solid_ec_mvx[j]=Msolid_ec_mvx[0]->at(j);
  solid_ec_mvy[j]=Msolid_ec_mvy[0]->at(j);
  solid_ec_mvz[j]=Msolid_ec_mvz[0]->at(j);
  solid_ec_avg_t[j]=Msolid_ec_avg_t[0]->at(j);
  }
    output_flux->Fill();		
    output_solid_ec->Fill();
    output_generate->Fill();
}
 if (m==n[0]){
  if(timeT1[m-1]<timeT2[d]<timeT1[m]){
  fEvTimeWindow = (Int_t)timeT2[d]/30;
  flux_pim->GetEntry(d);
  solid_ec_pim->GetEntry(d);
  fEvTimeStamp=timeT2[d];
  fEv_simpid=-211;
  for (int j = 0; j<Mflux_hitn[1]->size(); j++){
  flux_hitn =Mflux_hitn[1]->at(j);
  flux_id[j]=Mflux_id[1]->at(j);
  flux_pid[j]=Mflux_pid[1]->at(j);
  flux_mpid[j]=Mflux_mpid[1]->at(j);
  flux_tid[j]=Mflux_tid[1]->at(j);
  flux_mtid[j]=Mflux_mtid[1]->at(j);
  flux_otid[j]=Mflux_otid[1]->at(j);
  flux_trackE[j]=Mflux_trackE[1]->at(j);
  flux_totEdep[j]=Mflux_totEdep[1]->at(j);
  flux_avg_x[j]=Mflux_avg_x[1]->at(j);
  flux_avg_y[j]=Mflux_avg_y[1]->at(j);
  flux_avg_z[j]=Mflux_avg_z[1]->at(j);
  flux_avg_lx[j]=Mflux_avg_lx[1]->at(j);
  flux_avg_ly[j]=Mflux_avg_ly[1]->at(j);
  flux_avg_lz[j]=Mflux_avg_lz[1]->at(j);
  flux_px[j]=Mflux_px[1]->at(j);
  flux_py[j]=Mflux_py[1]->at(j);
  flux_pz[j]=Mflux_pz[1]->at(j);
  flux_vx[j]=Mflux_vx[1]->at(j);
  flux_vy[j]=Mflux_vy[1]->at(j);
  flux_vz[j]=Mflux_vz[1]->at(j);
  flux_mvx[j]=Mflux_mvx[1]->at(j);
  flux_mvy[j]=Mflux_mvy[1]->at(j);
  flux_mvz[j]=Mflux_mvz[1]->at(j);
  flux_avg_t[j]=Mflux_avg_t[1]->at(j);
  }
  for (int j = 0; j<Msolid_ec_hitn[1]->size(); j++){
  
  solid_ec_hitn =Msolid_ec_hitn[1]->at(j);
  solid_ec_id[j]=Msolid_ec_id[1]->at(j);
  solid_ec_pid[j]=Msolid_ec_pid[1]->at(j);
  solid_ec_mpid[j]=Msolid_ec_mpid[1]->at(j);
  solid_ec_tid[j]=Msolid_ec_tid[1]->at(j);
  solid_ec_mtid[j]=Msolid_ec_mtid[1]->at(j);
  solid_ec_otid[j]=Msolid_ec_otid[1]->at(j);
  solid_ec_trackE[j]=Msolid_ec_trackE[1]->at(j);
  solid_ec_totEdep[j]=Msolid_ec_totEdep[1]->at(j);
  solid_ec_avg_x[j]=Msolid_ec_avg_x[1]->at(j);
  solid_ec_avg_y[j]=Msolid_ec_avg_y[1]->at(j);
  solid_ec_avg_z[j]=Msolid_ec_avg_z[1]->at(j);
  solid_ec_avg_lx[j]=Msolid_ec_avg_lx[1]->at(j);
  solid_ec_avg_ly[j]=Msolid_ec_avg_ly[1]->at(j);
  solid_ec_avg_lz[j]=Msolid_ec_avg_lz[1]->at(j);
  solid_ec_px[j]=Msolid_ec_px[1]->at(j);
  solid_ec_py[j]=Msolid_ec_py[1]->at(j);
  solid_ec_pz[j]=Msolid_ec_pz[1]->at(j);
  solid_ec_vx[j]=Msolid_ec_vx[1]->at(j);
  solid_ec_vy[j]=Msolid_ec_vy[1]->at(j);
  solid_ec_vz[j]=Msolid_ec_vz[1]->at(j);
  solid_ec_mvx[j]=Msolid_ec_mvx[1]->at(j);
  solid_ec_mvy[j]=Msolid_ec_mvy[1]->at(j);
  solid_ec_mvz[j]=Msolid_ec_mvz[1]->at(j);
  solid_ec_avg_t[j]=Msolid_ec_avg_t[1]->at(j);
  }
    output_flux->Fill();		
    output_solid_ec->Fill();
    output_generate->Fill();
  d +=1;
  }
 }else {d=d;}

if (m==n[1]){
  if(timeT1[m-1]<timeT3[e]<timeT1[m]){
  fEvTimeWindow = (Int_t)timeT3[e]/30;
  flux_pi0->GetEntry(e);
  solid_ec_pi0->GetEntry(e);
  fEvTimeStamp=timeT3[e];
  fEv_simpid=111;
  for (int j = 0; j<Mflux_hitn[2]->size(); j++){
  flux_hitn =Mflux_hitn[2]->at(j);
  flux_id[j]=Mflux_id[2]->at(j);
  flux_pid[j]=Mflux_pid[2]->at(j);
  flux_mpid[j]=Mflux_mpid[2]->at(j);
  flux_tid[j]=Mflux_tid[2]->at(j);
  flux_mtid[j]=Mflux_mtid[2]->at(j);
  flux_otid[j]=Mflux_otid[2]->at(j);
  flux_trackE[j]=Mflux_trackE[2]->at(j);
  flux_totEdep[j]=Mflux_totEdep[2]->at(j);
  flux_avg_x[j]=Mflux_avg_x[2]->at(j);
  flux_avg_y[j]=Mflux_avg_y[2]->at(j);
  flux_avg_z[j]=Mflux_avg_z[2]->at(j);
  flux_avg_lx[j]=Mflux_avg_lx[2]->at(j);
  flux_avg_ly[j]=Mflux_avg_ly[2]->at(j);
  flux_avg_lz[j]=Mflux_avg_lz[2]->at(j);
  flux_px[j]=Mflux_px[2]->at(j);
  flux_py[j]=Mflux_py[2]->at(j);
  flux_pz[j]=Mflux_pz[2]->at(j);
  flux_vx[j]=Mflux_vx[2]->at(j);
  flux_vy[j]=Mflux_vy[2]->at(j);
  flux_vz[j]=Mflux_vz[2]->at(j);
  flux_mvx[j]=Mflux_mvx[2]->at(j);
  flux_mvy[j]=Mflux_mvy[2]->at(j);
  flux_mvz[j]=Mflux_mvz[2]->at(j);
  flux_avg_t[j]=Mflux_avg_t[2]->at(j);
  }
  for (int j = 0; j<Msolid_ec_hitn[2]->size(); j++){
  solid_ec_hitn =Msolid_ec_hitn[2]->at(j);
  solid_ec_id[j]=Msolid_ec_id[2]->at(j);
  solid_ec_pid[j]=Msolid_ec_pid[2]->at(j);
  solid_ec_mpid[j]=Msolid_ec_mpid[2]->at(j);
  solid_ec_tid[j]=Msolid_ec_tid[2]->at(j);
  solid_ec_mtid[j]=Msolid_ec_mtid[2]->at(j);
  solid_ec_otid[j]=Msolid_ec_otid[2]->at(j);
  solid_ec_trackE[j]=Msolid_ec_trackE[2]->at(j);
  solid_ec_totEdep[j]=Msolid_ec_totEdep[2]->at(j);
  solid_ec_avg_x[j]=Msolid_ec_avg_x[2]->at(j);
  solid_ec_avg_y[j]=Msolid_ec_avg_y[2]->at(j);
  solid_ec_avg_z[j]=Msolid_ec_avg_z[2]->at(j);
  solid_ec_avg_lx[j]=Msolid_ec_avg_lx[2]->at(j);
  solid_ec_avg_ly[j]=Msolid_ec_avg_ly[2]->at(j);
  solid_ec_avg_lz[j]=Msolid_ec_avg_lz[2]->at(j);
  solid_ec_px[j]=Msolid_ec_px[2]->at(j);
  solid_ec_py[j]=Msolid_ec_py[2]->at(j);
  solid_ec_pz[j]=Msolid_ec_pz[2]->at(j);
  solid_ec_vx[j]=Msolid_ec_vx[2]->at(j);
  solid_ec_vy[j]=Msolid_ec_vy[2]->at(j);
  solid_ec_vz[j]=Msolid_ec_vz[2]->at(j);
  solid_ec_mvx[j]=Msolid_ec_mvx[2]->at(j);
  solid_ec_mvy[j]=Msolid_ec_mvy[2]->at(j);
  solid_ec_mvz[j]=Msolid_ec_mvz[2]->at(j);
  solid_ec_avg_t[j]=Msolid_ec_avg_t[2]->at(j);
  }

  output_flux->Fill();		
  output_solid_ec->Fill();
    output_generate->Fill();
  e +=1;
  }

}else {e=e;}
if (m==n[2]){
 if(timeT1[m-1]<timeT4[q]<timeT1[m]){
  fEvTimeWindow = (Int_t)timeT4[q]/30;
  flux_EM->GetEntry(q);
  solid_ec_EM->GetEntry(q);
  fEvTimeStamp=timeT4[q];
  fEv_simpid=211;
  for (int j = 0; j<Mflux_hitn[3]->size(); j++){
  flux_hitn =Mflux_hitn[3]->at(j);
  flux_id[j]=Mflux_id[3]->at(j);
  flux_pid[j]=Mflux_pid[3]->at(j);
  flux_mpid[j]=Mflux_mpid[3]->at(j);
  flux_tid[j]=Mflux_tid[3]->at(j);
  flux_mtid[j]=Mflux_mtid[3]->at(j);
  flux_otid[j]=Mflux_otid[3]->at(j);
  flux_trackE[j]=Mflux_trackE[3]->at(j);
  flux_totEdep[j]=Mflux_totEdep[3]->at(j);
  flux_avg_x[j]=Mflux_avg_x[3]->at(j);
  flux_avg_y[j]=Mflux_avg_y[3]->at(j);
  flux_avg_z[j]=Mflux_avg_z[3]->at(j);
  flux_avg_lx[j]=Mflux_avg_lx[3]->at(j);
  flux_avg_ly[j]=Mflux_avg_ly[3]->at(j);
  flux_avg_lz[j]=Mflux_avg_lz[3]->at(j);
  flux_px[j]=Mflux_px[3]->at(j);
  flux_py[j]=Mflux_py[3]->at(j);
  flux_pz[j]=Mflux_pz[3]->at(j);
  flux_vx[j]=Mflux_vx[3]->at(j);
  flux_vy[j]=Mflux_vy[3]->at(j);
  flux_vz[j]=Mflux_vz[3]->at(j);
  flux_mvx[j]=Mflux_mvx[3]->at(j);
  flux_mvy[j]=Mflux_mvy[3]->at(j);
  flux_mvz[j]=Mflux_mvz[3]->at(j);
  flux_avg_t[j]=Mflux_avg_t[3]->at(j);
  }
  for (int j = 0; j<Msolid_ec_hitn[3]->size(); j++){
  solid_ec_hitn =Msolid_ec_hitn[3]->at(j);
  solid_ec_id[j]=Msolid_ec_id[3]->at(j);
  solid_ec_pid[j]=Msolid_ec_pid[3]->at(j);
  solid_ec_mpid[j]=Msolid_ec_mpid[3]->at(j);
  solid_ec_tid[j]=Msolid_ec_tid[3]->at(j);
  solid_ec_mtid[j]=Msolid_ec_mtid[3]->at(j);
  solid_ec_otid[j]=Msolid_ec_otid[3]->at(j);
  solid_ec_trackE[j]=Msolid_ec_trackE[3]->at(j);
  solid_ec_totEdep[j]=Msolid_ec_totEdep[3]->at(j);
  solid_ec_avg_x[j]=Msolid_ec_avg_x[3]->at(j);
  solid_ec_avg_y[j]=Msolid_ec_avg_y[3]->at(j);
  solid_ec_avg_z[j]=Msolid_ec_avg_z[3]->at(j);
  solid_ec_avg_lx[j]=Msolid_ec_avg_lx[3]->at(j);
  solid_ec_avg_ly[j]=Msolid_ec_avg_ly[3]->at(j);
  solid_ec_avg_lz[j]=Msolid_ec_avg_lz[3]->at(j);
  solid_ec_px[j]=Msolid_ec_px[3]->at(j);
  solid_ec_py[j]=Msolid_ec_py[3]->at(j);
  solid_ec_pz[j]=Msolid_ec_pz[3]->at(j);
  solid_ec_vx[j]=Msolid_ec_vx[3]->at(j);
  solid_ec_vy[j]=Msolid_ec_vy[3]->at(j);
  solid_ec_vz[j]=Msolid_ec_vz[3]->at(j);
  solid_ec_mvx[j]=Msolid_ec_mvx[3]->at(j);
  solid_ec_mvy[j]=Msolid_ec_mvy[3]->at(j);
  solid_ec_mvz[j]=Msolid_ec_mvz[3]->at(j);
  solid_ec_avg_t[j]=Msolid_ec_avg_t[3]->at(j);
  }
  output_flux->Fill();		
  output_solid_ec->Fill();
  output_generate->Fill();
  q +=1;
 }

}else{q=q;}

m +=1;


}
  
  
  
  f2->cd();
  // output_flux->SetName("flux");
  //output_flux->Write(0,kWriteDelete);
  output_flux->Write();		
  output_solid_ec->Write();
  output_generate->Write();
  f2->Close();
  f1->Close();
  f3->Close();
  f4->Close();
  f5->Close();
  
};
