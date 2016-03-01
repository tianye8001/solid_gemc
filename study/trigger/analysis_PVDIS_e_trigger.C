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
#include <TString.h>

#include "analysis_tree_solid_ec.C"
#include "analysis_tree_solid_lgc.C"

#include "triggerfile/Get_PVDIS_trigger_efficiency_EC.C"

using namespace std;

void analysis_PVDIS_e_trigger(string input_filename)
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

// TH1F *htotEdep_spd=new TH1F("htotEdep_spd","htotEdep_spd",100,0,5);
// TH1F *htotEdep_mrpc=new TH1F("htotEdep_mrpc","htotEdep_mrpc",100,0,0.1);
// TH1F *htotEdep_ec=new TH1F("htotEdep_ec","htotEdep_ec",100,0,2000);
// 
// TH2F *htotEdep_ec_gen=new TH2F("htotEdep_ec_gen","htotEdep_ec_gen",100,0,2000,110,0,11000);
// TH2F *htotEdep_ec_spd=new TH2F("htotEdep_ec_spd","htotEdep_ec_spd",100,0,2000,100,0,5);
// TH2F *htotEdep_ec_mrpc=new TH2F("htotEdep_ec_mrpc","htotEdep_ec_mrpc",100,0,2000,100,0,0.1);
// TH2F *htotEdep_spd_mrpc=new TH2F("htotEdep_spd_mrpc","htotEdep_spd_mrpc",100,0,5,100,0,0.1);

	TH1F *hfluxR,*hfluxR_trig;
	char hstname[100];	
	sprintf(hstname,"fluxR");
	hfluxR=new TH1F(hstname,hstname,60,0,300);
	hfluxR->SetTitle(";R (cm);flux (kHz/mm2)");
	sprintf(hstname,"fluxR_trig");
	hfluxR_trig=new TH1F(hstname,hstname,60,0,300);
	hfluxR_trig->SetTitle(";R (cm);flux_trig (kHz/mm2)");
	
TFile *file=new TFile(input_filename.c_str());
if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
}
else cout << "open file " << input_filename << endl;   

	/*Define run condition{{{*/
	bool Is_PVDIS=false,Is_SIDIS_He3=false,Is_SIDIS_NH3=false,Is_JPsi_LH2=false;  
	double current;
	double target_center;  //in mm
	if (input_filename.find("PVDIS",0) != string::npos){
		Is_PVDIS=true;
		current=50e-6/1.6e-19;  //50uA
		target_center=100;  //in mm
		cout << " PVDIS " << current  << endl;  
	}
	else if (input_filename.find("SIDIS_He3",0) != string::npos){
		Is_SIDIS_He3=true;
		current=15e-6/1.6e-19;   //15uA
		target_center=-3500;  //in mm  
		cout << " SIDIS_He3 " << current  <<  endl;  
	}
	else if (input_filename.find("SIDIS_NH3",0) != string::npos){
		Is_SIDIS_NH3=true;	
		current=100e-9/1.6e-19;   //100nA
		target_center=-3500;  //in mm  
		cout << " SIDIS_NH3 " << current  <<  endl;  
	}
	else if (input_filename.find("JPsi_LH2",0) != string::npos){
		Is_JPsi_LH2=true;
		current=3e-6/1.6e-19;   //3uA
		target_center=-3150;  //in mm  
		cout << " JPsi_LH2 " << current  <<  endl;  
	}
	else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}
	
	// there are different ways to get correct normalization for different files
	//EM just need current and total number of event
	//source from weighted or normalized event generator need rate and total file number, assume there are 100 files, each file has 10000 events, the rate in each file has normalized by 10000, then add 100 files with root tree together, the final result needs normalization by 10000*100=1e6, so the addtional factor is the file num 100
	//dirty or clean means put in realmaterial or not

	bool Is_EM=false,Is_weighted=false,Is_normalized=false;
	if (input_filename.find("_EM_",0) != string::npos) {
		Is_EM=true;
		cout << "EM background from beam on target" <<  endl;
	}
	else if (input_filename.find("_weighted_",0) != string::npos) {
		Is_weighted=true;
		cout << "background from weighted event generator" <<  endl;
	}	  
	else if (input_filename.find("_normalized_",0) != string::npos) {
		Is_normalized=true;
		cout << "background from normalized event generator" <<  endl;
	}	  	
	else {cout << "not EM or weighted or normalized " << endl; return;}
	
	double filenum=1.;
	if (!Is_EM){   //for non-EM background
	  if (input_filename.find("_filenum",0) != string::npos) {
	    filenum=atof(input_filename.substr(input_filename.find("_filenum")+8,input_filename.find("_")).c_str());
	      cout << "filenum " << filenum << " for addtional normalization, YOU Need to Make Sure It's CORRECT!" <<  endl;
	  }
	  else {cout << "we need filenum for addtional normalization" << endl; return;}		
	}
		

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

TTree *tree_solid_ec = (TTree*) file->Get("solid_ec");
setup_tree_solid_ec(tree_solid_ec);

TTree *tree_solid_lgc = (TTree*) file->Get("solid_lgc");
setup_tree_solid_lgc(tree_solid_lgc);

int Nevent = (int)tree_header->GetEntries();
cout << "Nevent = " << Nevent << endl;

for (Int_t i=0;i<1000;i++) { 
// for (Int_t i=0;i<2;i++) { 
//   cout << i << "\r";
//   cout << i << "\n";

  tree_header->GetEntry(i);
  double rate = var8->at(0);
//   double W = header_W->at(0);
//   double Q2 = header_Q2->at(0);
//   double x = header_x->at(0);
//cout << Q2 << " " << x << endl;  
   
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
      
//       cout << "p_gen " << p_gen << endl;
  }

  tree_solid_lgc->GetEntry(i);  
  bool Is_trigger_lgc=lgc_trigger(tree_solid_lgc);
  
//   bool Is_trigger_lgc = process_tree_solid_lgc_trigger(tree_solid_lgc);

//   tree_solid_ec->GetEntry(i);  
//   bool Is_trigger_ec = process_tree_solid_ec_trigger(tree_solid_ec);
  
    tree_flux->GetEntry(i);      
    for (Int_t j=0;j<flux_hitn->size();j++) {
//       cout << "flux " << " !!! " << flux_hitn->at(j) << " " << flux_id->at(j) << " " << flux_pid->at(j) << " " << flux_mpid->at(j) << " " << flux_tid->at(j) << " " << flux_mtid->at(j) << " " << flux_trackE->at(j) << " " << flux_totEdep->at(j) << " " << flux_avg_x->at(j) << " " << flux_avg_y->at(j) << " " << flux_avg_z->at(j) << " " << flux_avg_lx->at(j) << " " << flux_avg_ly->at(j) << " " << flux_avg_lz->at(j) << " " << flux_px->at(j) << " " << flux_py->at(j) << " " << flux_pz->at(j) << " " << flux_vx->at(j) << " " << flux_vy->at(j) << " " << flux_vz->at(j) << " " << flux_mvx->at(j) << " " << flux_mvy->at(j) << " " << flux_mvz->at(j) << " " << flux_avg_t->at(j) << endl;  

      int detector_ID=flux_id->at(j)/1000000;
      int subdetector_ID=(flux_id->at(j)%1000000)/100000;
      int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;
      int component_ID=flux_id->at(j)%10000;
      
     
      if (detector_ID==2 && subdetector_ID == 1 && subsubdetector_ID == 1)   cout << "particle mom entering LGC " << flux_trackE->at(j) << endl;    
      
      if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) {	
	double flux_r=sqrt(flux_avg_x->at(j)*flux_avg_x->at(j)+flux_avg_y->at(j)*flux_avg_y->at(j));
	double flux_mom=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j));
	
	TString pid;
	if (abs(flux_pid->at(j))==11) pid="electron";	
	else if (abs(flux_pid->at(j))==211) pid="pion";
	else if (abs(flux_pid->at(j))==22) pid="gamma";
	else if (abs(flux_pid->at(j))==2212) pid="proton";
	else {
// 	  cout << flux_pid->at(j) << " pid not supported " << endl; 
	  continue;	  
	}

	TString region;		
	double flux_phi=fabs(atan(flux_avg_y->at(j)/flux_avg_x->at(j))/3.1416*180);	
	if (flux_phi-int(flux_phi/12)*12<6) region="high";
	else region="low";

	double PVDIS_trigger_efficiency_EC=Get_PVDIS_trigger_efficiency_EC(region,pid,flux_r/10,flux_mom/1e3);
	if (PVDIS_trigger_efficiency_EC>0){
// 	  Get_PVDIS_trigger_efficiency_EC(region,pid,flux_r/10,flux_mom/1e3,true);
	cout << "EC trigger " << PVDIS_trigger_efficiency_EC  << " at ";
	cout << " region " << region << ", pid " << pid << ", flux_r " << flux_r/10 << ", cm flux_mom " << flux_mom/1e3 << " GeV" << endl;
	}
	
      /*Calculate Weight{{{*/
      double thisrate=0.0;
      double weight=0.0,weightR=0.0,weightPhi=0.0,weightTheta=0.0;
      double area=1.;      /// in 
      double areaR=2*3.1415926*flux_r*1.; /// in mm2
      double areaPhi=1.;  /// in any deg      
//       double areaTheta=2*3.1415926*flux_r*(flux_avg_z->at(j)*(tan((Theta+0.25)/DEG)-tan((Theta-0.25)/DEG))); ///0.5deg width

      if (Is_EM) thisrate=current/Nevent;			
      else thisrate=rate/filenum;			
// 			cout << "thisrate" << rate << endl;
      
      weight=thisrate/1e3/area;
      weightR=thisrate/1e3/areaR;
      weightPhi=thisrate/1e3/areaPhi;
//       weightTheta=thisrate/1e3/areaTheta;     
      /*End of Caluclate Weight}}}*/
	
      double Is_trigger=PVDIS_trigger_efficiency_EC*Is_trigger_lgc;      

      hfluxR->Fill(flux_r/10.,weightR/50.);   ///in 5cm bin
      hfluxR_trig->Fill(flux_r/10.,weightR/50.*Is_trigger);   ///in 5cm bin    
      
      }
    }
    
   
}
file->Close();

TCanvas *c_fluxR = new TCanvas("fluxR","fluxR",1600,900);
c_fluxR->Divide(2,1);
hfluxR->SetMinimum(1e-7);
hfluxR->SetMaximum(1e7);    
hfluxR->SetLineColor(1);
hfluxR->Draw();
hfluxR_trig->SetLineColor(2);
hfluxR_trig->Draw("same");

      int nbins=hfluxR->GetNbinsX();
      double binwidth=hfluxR->GetBinWidth(1);
//       cout << nbins << " " << binwidth << endl;
      double sum=0,sum_trig=0;
      double sum_R[5]={0,0,0,0,0},sum_R_trig[5]={0,0,0,0,0};
      for(int k=1;k<nbins;k++){
// 	double r=hfluxR_proj[j][i]->GetBinCenter(k);
// 	if (r < Rmin || Rmax< r) continue;
// 	if (hfluxR_proj[j][i]->GetBinCenter(k) < 60 || 150< hfluxR_proj[j][i]->GetBinCenter(k)) continue;
	double thisrate=2*3.1415926*hfluxR->GetBinCenter(k)*binwidth*100*hfluxR->GetBinContent(k);
	double thisrate_trig=2*3.1415926*hfluxR_trig->GetBinCenter(k)*binwidth*100*hfluxR_trig->GetBinContent(k);
	sum += thisrate;
	sum_trig += thisrate_trig;
      }
      
      cout << sum << endl;
      
      cout << sum_trig << endl;      
      

// 	// add text
// 	TPaveText *pt1 = new TPaveText(0.6,0.6,0.95,0.9,"brNDC");
// 	pt1->SetFillColor(17);
// 	pt1->SetTextAlign(12);
// 	pt1->Draw();
// 	for(int i=0;i<m;i++){
// 		TText *text=pt1->AddText();
// 		text->SetTextColor(i+1);
// 		text->SetTextSize(0.024);
// 	}

// outputfile->Write();
// outputfile->Flush();


}
