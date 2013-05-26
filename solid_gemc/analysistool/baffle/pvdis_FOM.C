using namespace std;

void pvdis_FOM(string input_filename){
   gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  
const double DEG=180./3.1415926;
  
TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eDIS_1e6.root");
// TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eDIS_ras0.2cm_1e6.root");
  
//     if (file->IsZombie()) {
//        cout << "Error opening file" << input_filename << endl;
//        exit(-1);
//     }
//     else cout << "open file " << input_filename << endl;

double pf,theta,phi,Q2,x,W,rate,Abeam;
TTree *T = (TTree*) file_rate->Get("T");
T->SetBranchAddress("pf",&pf);
T->SetBranchAddress("theta",&theta);
T->SetBranchAddress("phi",&phi);
T->SetBranchAddress("Q2",&Q2);
T->SetBranchAddress("x",&x);
T->SetBranchAddress("W",&W);
T->SetBranchAddress("rate",&rate);
T->SetBranchAddress("Abeam",&Abeam);

// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.4_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.3_tweak1deg_output.root");
// TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.2_tweak2deg_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.1_tweak3deg_extra_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.0_tweak4deg_output.root");
// // TFile *acceptancefile_negative=new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/acceptance_solid_CLEO_PVDIS_negative_SCALANG1.0_tweak4deg_new_output.root");
// 
// TH2F *hacceptance_negative=(TH2F*) acceptancefile_negative->Get("acceptance");

  TFile *file=new TFile(input_filename.c_str());
    if (file->IsZombie()) {
       cout << "Error opening file" << input_filename << endl;
       continue;
//        exit(-1);
    }
    else cout << "open file " << input_filename << endl;

TTree *Tgen = (TTree*) file->Get("genT");
Int_t gen_evn,gen_ngen;
Int_t gen_id_array[1000];
Int_t *gen_id=gen_id_array;
Float_t gen_px_array[1000],gen_py_array[1000],gen_pz_array[1000],gen_p_array[1000],gen_phi_array[1000],gen_theta_array[1000],gen_vx_array[1000],gen_vy_array[1000],gen_vz_array[1000];
Float_t *gen_px=gen_px_array,*gen_py=gen_py_array,*gen_pz=gen_pz_array,*gen_p=gen_p_array,*gen_phi=gen_phi_array,*gen_theta=gen_theta_array,*gen_vx=gen_vx_array,*gen_vy=gen_vy_array,*gen_vz=gen_vz_array;
Tgen->SetBranchAddress("evn",&gen_evn);
Tgen->SetBranchAddress("ngen",&gen_ngen);
Tgen->SetBranchAddress("id",gen_id);
Tgen->SetBranchAddress("px",gen_px);
Tgen->SetBranchAddress("py",gen_py);
Tgen->SetBranchAddress("pz",gen_pz);
Tgen->SetBranchAddress("p",gen_p);
Tgen->SetBranchAddress("phi",gen_phi);
Tgen->SetBranchAddress("theta",gen_theta);
Tgen->SetBranchAddress("vx",gen_vx);
Tgen->SetBranchAddress("vy",gen_vy);
Tgen->SetBranchAddress("vz",gen_vz);

TTree *Tflux = (TTree*) file->Get("fluxT");
Int_t flux_evn,flux_nfluxhit;
Int_t flux_ID_array[1000],*flux_pid_array[1000],*flux_mpid_array[1000];
Int_t *flux_ID=flux_ID_array,*flux_pid=flux_pid_array,*flux_mpid=flux_mpid_array;
Float_t flux_Edep_array[1000],flux_E_array[1000],flux_x_array[1000],flux_y_array[1000],flux_z_array[1000],flux_lx_array[1000],flux_ly_array[1000],flux_lz_array[1000],flux_t_array[1000],flux_px_array[1000],flux_py_array[1000],flux_pz_array[1000],flux_vx_array[1000],flux_vy_array[1000],flux_vz_array[1000],flux_mvx_array[1000],flux_mvy_array[1000],flux_mvz_array[1000];
Float_t *flux_Edep=flux_Edep_array,*flux_E=flux_E_array,*flux_x=flux_x_array,*flux_y=flux_y_array,*flux_z=flux_z_array,*flux_lx=flux_lx_array,*flux_ly=flux_ly_array,*flux_lz=flux_lz_array,*flux_t=flux_t_array,*flux_px=flux_px_array,*flux_py=flux_py_array,*flux_pz=flux_pz_array,*flux_vx=flux_vx_array,*flux_vy=flux_vy_array,*flux_vz=flux_vz_array,*flux_mvx=flux_mvx_array,*flux_mvy=flux_mvy_array,*flux_mvz=flux_mvz_array;
Tflux->SetBranchAddress("evn",&flux_evn);
Tflux->SetBranchAddress("nfluxhit",&flux_nfluxhit);
Tflux->SetBranchAddress("ID",flux_ID);
Tflux->SetBranchAddress("Edep",flux_Edep);
Tflux->SetBranchAddress("E",flux_E);
Tflux->SetBranchAddress("x",flux_x);
Tflux->SetBranchAddress("y",flux_y);
Tflux->SetBranchAddress("z",flux_z);
Tflux->SetBranchAddress("lx",flux_lx);
Tflux->SetBranchAddress("ly",flux_ly);
Tflux->SetBranchAddress("lz",flux_lz);
Tflux->SetBranchAddress("t",flux_t);
Tflux->SetBranchAddress("pid",flux_pid);
Tflux->SetBranchAddress("mpid",flux_mpid);
Tflux->SetBranchAddress("px",flux_px);
Tflux->SetBranchAddress("py",flux_py);
Tflux->SetBranchAddress("pz",flux_pz);
Tflux->SetBranchAddress("vx",flux_vx);
Tflux->SetBranchAddress("vy",flux_vy);
Tflux->SetBranchAddress("vz",flux_vz);
Tflux->SetBranchAddress("mvx",flux_mvx);
Tflux->SetBranchAddress("mvy",flux_mvy);
Tflux->SetBranchAddress("mvz",flux_mvz);

char output_filename[80];
sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

TH2F *hrate_PTheta_gen=new TH2F("rate_PTheta_gen","rate_PTheta_gen",50,0,50,110,0,11);
TH2F *hrate_PTheta_acc=new TH2F("rate_PTheta_acc","rate_PTheta_acc",50,0,50,110,0,11);
TH2F *hacceptance_PTheta=new TH2F("acceptance_PTheta","acceptance_PTheta",50,0,50,110,0,11);
TH2F *hrate_Q2x_gen=new TH2F("rate_Q2x_gen","rate_Q2x_gen",100,0,1,140,0,14);
TH2F *hrate_Q2x_acc=new TH2F("rate_Q2x_acc","rate_Q2x_acc",100,0,1,140,0,14);
TH2F *hacceptance_Q2x=new TH2F("acceptance_Q2x","acceptance_Q2x",100,0,1,140,0,14);

TH2F *hAbeam_Q2x_gen=new TH2F("Abeam_Q2x_gen","Abeam_Q2x_gen",100,0,1,140,0,14);
TH2F *hAbeam_Q2x_acc=new TH2F("Abeam_Q2x_acc","Abeam_Q2x_acc",100,0,1,140,0,14);
TH2F *hAbeamErr_Q2x_gen=new TH2F("AbeamErr_Q2x_gen","AbeamErr_Q2x_gen",100,0,1,140,0,14);
TH2F *hAbeamErr_Q2x_acc=new TH2F("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",100,0,1,140,0,14);
TH2F *hApv_Q2x_gen=new TH2F("Apv_Q2x_gen","Apv_Q2x_gen",100,0,1,140,0,14);
TH2F *hApv_Q2x_acc=new TH2F("Apv_Q2x_acc","Apv_Q2x_acc",100,0,1,140,0,14);
TH2F *hApvErr_Q2x_gen=new TH2F("ApvErr_Q2x_gen","ApvErr_Q2x_gen",100,0,1,140,0,14);
TH2F *hApvErr_Q2x_acc=new TH2F("ApvErr_Q2x_acc","ApvErr_Q2x_acc",100,0,1,140,0,14);

TH2F *hrate_Q2x_acc_bin=new TH2F("rate_Q2x_acc_bin","rate_Q2x_acc_bin",10,0,1,7.5,0,15);
TH2F *hApvErr_Q2x_acc_bin=new TH2F("ApvErr_Q2x_acc_bin","ApvErr_Q2x_acc_bin",10,0,1,7.5,0,15);

TH2F *hrate_PTheta_zwzhao_gen=new TH2F("rate_PTheta_zwzhao_gen","rate_PTheta_zwzhao_gen",13,20,44,20,0,6);
TH2F *hrate_PTheta_zwzhao_acc=new TH2F("rate_PTheta_zwzhao_acc","rate_PTheta_zwzhao_acc",13,20,44,20,0,6);
TH2F *hrate_PTheta_seamus_gen=new TH2F("rate_PTheta_seamus_gen","rate_PTheta_seamus_gen",13,20,44,20,0,6);


  double rout_cut_FA = 250;  //target at 10,ec front at 320 back at 370 with angle 36
  double rin_cut_FA = 0;  //as the detector edge
  cout << " PVDIS rcut " << rin_cut_FA << " " << rout_cut_FA <<  endl;
  
Int_t nevent = (Int_t)Tflux->GetEntries();
cout << "nevent " << nevent << endl;

cout << "generator has entry " <<  T->GetEntries() << endl;
cout << "output has entry " << Tflux->GetEntries() << endl;;

      double time = 120*3600*24;  //number of days in seconds
      double pb = 0.85; 
   
///binning for SCALEMIN1.4MAX1.4
double bin[15][4]={
0.20,0.30,     0.0,14.0,
0.30,0.35,     0.0,14.0,
0.35,0.40,     0.0, 6.1,
0.35,0.40,     6.1,14.0,
0.40,0.45,     0.0, 6.7,
0.40,0.45,     6.7,14.0,
0.45,0.50,     0.0, 7.3,
0.45,0.50,     7.3,14.0,
0.50,0.55,     0.0, 7.9,
0.50,0.55,     7.9,14.0,
0.55,0.60,     0.0, 8.5,
0.55,0.60,     8.5,14.0,
0.60,0.67,     0.0, 9.1,
0.60,0.67,     9.1,14.0,
0.67,0.80,     0.0,14.0
};

///binning in proposal      
// double bin[15][4]={
// 0.20,0.31,     3.0, 5.0,
// 0.31,0.35,     3.5, 6.5,
// 0.35,0.40,     4.5, 5.9,
// 0.35,0.40,     5.9, 7.5,
// 0.40,0.45,     5.0, 6.5,
// 0.40,0.45,     6.5, 8.5,
// 0.45,0.50,     5.0, 7.2,
// 0.45,0.50,     7.2,10.0,
// 0.50,0.55,     5.0, 7.7,
// 0.50,0.55,     7.7,10.0,
// 0.55,0.60,     5.0, 8.1,
// 0.55,0.60,     8.1,11.0,
// 0.60,0.67,     5.5, 8.7,
// 0.60,0.67,     8.7,11.0,
// 0.67,0.82,     7.0,12.0 
// };

// 	  cout << bin[1][0] << " "<< bin[1][1] << " " << bin[1][2] << " " << bin[1][3] << endl; 

double thatrate[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Abeam_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double Apv_sum[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

for (Int_t i=0;i<nevent;i++) {
//   for (Int_t i=0;i<10;i++) {
      cout << i << "\r";    
  T->GetEntry(i);
    
//   cout << W << " " << sqrt(0.938**2+2*0.938*(11-pf)-Q2) << endl;
  if (W<2) continue;
//     if (pf<2) continue;
  bool Is_pf=true;
    
//     cout << theta*DEG << " " << pf  << endl;
 
//     Tgen->GetEntry(i);  
//   for (Int_t j=0;j<gen_ngen;j++) {
//       cout <<  gen_evn << " " << gen_ngen << " " << *(gen_id+j) << " " << *(gen_px+j) << " " << *(gen_py+j) << " " << *(gen_pz+j) << " " << *(gen_p+j) << " " << *(gen_theta+j)  <<endl;
//       theta=*(gen_theta+j);
//       mom=*(gen_p+j)/1e3;
//   }
  
    double acc=0;
    Tflux->GetEntry(i+1);     //gemc_evio has bug output tree starting from index 1
    for (Int_t j=0;j<flux_nfluxhit;j++) {
//       if (flux_nfluxhit>1){
//             cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
//       }
      int detector_ID=*(flux_ID+j)/1000000;
      int subdetector_ID=(*(flux_ID+j)%1000000)/100000;
      int subsubdetector_ID=((*(flux_ID+j)%1000000)%100000)/10000;
  //     cout << Detector_ID << " " << SubDetector_ID << " "  << channel_ID << endl;
      if (detector_ID==3 && subdetector_ID==1 && subsubdetector_ID==1) {
	acc=1;
//       cout << j << endl;
//       cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
	double r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2));
// 	cout << r << endl;
// 	if (pf<3 && 1100 < r && r < 1400) Is_pf=false;
	if (pf<2.5 && 1100 < r && r < 1400) Is_pf=false;	
	if (pf<2.5 && 1400 < r && r < 1700) Is_pf=false;
	if (pf<2 && 1700 < r && r < 2700) Is_pf=false;
      }
    }
    
     if(!Is_pf) continue;
  
  //   double acc=hacceptance_negative->GetBinContent(hacceptance_negative->FindBin(theta*DEG,pf)); 
  
  hrate_PTheta_gen->Fill(theta*DEG,pf,rate);
  hrate_PTheta_acc->Fill(theta*DEG,pf,rate*acc);
  hrate_PTheta_zwzhao_gen->Fill(theta*DEG,pf,rate);
  hrate_PTheta_zwzhao_acc->Fill(theta*DEG,pf,rate*acc);
  
  hrate_Q2x_gen->Fill(x,Q2,rate);
  hrate_Q2x_acc->Fill(x,Q2,rate*acc);
  hrate_Q2x_acc_bin->Fill(x,Q2,rate*acc);

  hAbeam_Q2x_gen->Fill(x,Q2,-Abeam*rate);
  hAbeam_Q2x_acc->Fill(x,Q2,-Abeam*rate*acc);

  double Apv=0.84e-4*Q2;  
  hApv_Q2x_gen->Fill(x,Q2,Apv*rate);
  hApv_Q2x_acc->Fill(x,Q2,Apv*rate*acc);  
  
  hApvErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*time)/pb*100);
  hAbeamErr_Q2x_gen->Fill(x,Q2,1./sqrt(rate*time)/pb*100);  
  if (acc!=0) {
    hApvErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*time*acc)/pb*100);
    hAbeamErr_Q2x_acc->Fill(x,Q2,1./sqrt(rate*time*acc)/pb*100);
  }
  
      for(int k = 0; k < 15; k++){
	if (bin[k][0] <= x && x < bin[k][1] && bin[k][2] <= Q2 && Q2 < bin[k][3]){
	  thatrate[k] += rate*acc;
	  Apv_sum[k] += Apv*rate*acc;
	  Abeam_sum[k] += -Abeam*rate*acc;
	}
      }
	
}

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

hacceptance_PTheta->Divide(hrate_PTheta_acc,hrate_PTheta_gen);
hacceptance_Q2x->Divide(hrate_Q2x_acc,hrate_Q2x_gen);
TCanvas *c_acceptance_eDIS = new TCanvas("acceptance_eDIS","acceptance_eDIS",1800,600);
c_acceptance_eDIS->Divide(2,1);
c_acceptance_eDIS->cd(1);
gPad->SetGrid();
hacceptance_PTheta->SetMinimum(0);
hacceptance_PTheta->SetMaximum(1);
hacceptance_PTheta->Draw("colz");
c_acceptance_eDIS->cd(2);
gPad->SetGrid();
hacceptance_Q2x->SetMinimum(0);
hacceptance_Q2x->SetMaximum(1);
hacceptance_Q2x->Draw("colz");

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
      double ApvErr = 1./sqrt(thisrate*time)/Apv/pb*100;     
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

double AbeamErr[15],ApvErr[15];
    cout << "Apv_ave" << "\t" << "Abeam_ave" << "\t" << "rate" << "\t" << "ApvErr" << "\t" <<  "AbeamErr" << endl;
for(int k = 0; k < 15; k++){
//     double Apv = 0.84e-4*(bin[k][2]+bin[k][3])/2.;
    double Apv_ave = Apv_sum[k]/thatrate[k];
    ApvErr[k] = 1./sqrt(thatrate[k]*time)/Apv_ave/pb*100;   
    double Abeam_ave=Abeam_sum[k]/thatrate[k];
    AbeamErr[k] = 1./sqrt(thatrate[k]*time)/Abeam_ave/pb*100;      
    cout << Apv_ave << "\t" << Abeam_ave << "\t" << int(thatrate[k]) << "\t" << ApvErr[k] << "\t" <<  AbeamErr[k] << endl;
}

cout << "ApvErr" << endl;
for(int k = 0; k < 15; k++) cout << ApvErr[k] << ",";
cout << endl;
cout << "AbeamErr" << endl;
for(int k = 0; k < 15; k++) cout << AbeamErr[k] << ",";
cout << endl;

TCanvas *c_AbeamErr_Q2x_acc = new TCanvas("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",900,600);
gPad->SetGrid();
hAbeamErr_Q2x_acc->SetTitle("Asymmetry Uncertainty (%) with 120 days of 85% polarized 50uA electron beam on 40cm LD2 target;x;Q^{2} (GeV^{2})");
hAbeamErr_Q2x_acc->SetMarkerColor(kGreen);
hAbeamErr_Q2x_acc->Draw();
/*
0.20,0.30,     0.0,14.0,
0.30,0.35,     0.0,14.0,
0.35,0.40,     0.0, 6.1,
0.35,0.40,     6.1,14.0,
0.40,0.45,     0.0, 6.7,
0.40,0.45,     6.7,14.0,
0.45,0.50,     0.0, 7.3,
0.45,0.50,     7.3,14.0,
0.50,0.55,     0.0, 7.9,
0.50,0.55,     7.9,14.0,
0.55,0.60,     0.0, 8.5,
0.55,0.60,     8.5,14.0,
0.60,0.67,     0.0, 9.1,
0.60,0.67,     9.1,14.0,
0.67,0.80,     0.0,14.0*/

double x_cor[15]={0.250,0.325,0.375,0.375,0.425,0.425,0.475,0.475,0.525,0.525,0.575,0.575,0.635,0.635,0.735};
double Q2_cor[15]={4.2,5.0,5.5,6.3,6.0,7.0,6.5,7.8,7.1,8.5,7.6,9.1,8.2,9.8,9.8};
for(int k = 0; k < 15; k++){
TMarker marker;
marker.SetMarkerStyle(20);
marker.SetMarkerColor(kRed);
marker.DrawMarker(x_cor[k],Q2_cor[k]);
TText *label = new TText(x_cor[k],Q2_cor[k],Form("%.02f",AbeamErr[k]));
label->SetTextColor(kBlack);
label->SetTextSize(0.03);
label->Draw();
}

outputfile->Write();
outputfile->Flush();

ifstream input("solid_LD2_120d_11GeV.sollund");
if (!input.good()) {cout << "can't open file " << endl; return;}

double a1,weight,a3,a4,a5,a6,a7,a8,a9,a10,a11;
double b1,b2,b3,b4,b5,b6,px,py,pz,E,b11,b12,b13,b14;
int evncounter=0;
while (!input.eof()){
  evncounter++;
//   cout << evncounter << "\n";      
  input >> a1 >> weight >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9 >> a10>> a11;
  input >> b1 >> b2 >> b3 >> b4 >> b5 >> b6 >> px >> py >> pz >> E >> b11 >> b12 >> b13 >> b14;  
/*  if (evncounter<3) {
      cout << a1 << "\t" << weight << "\t" << a3 << "\t" << a4 << "\t" << a5 << "\t" << a6 << "\t" << a7 << "\t" << a8 << "\t" << a9 << "\t" << a10 << "\t" << a11 << endl;
      cout << b1 << "\t" << b2 << "\t" << b3 << "\t" << b4 << "\t" << b5 << "\t" << b6 << "\t" << px << "\t" << py << "\t" << pz << "\t" << E << "\t" << b11 << "\t" << b12 << "\t" << b13 << "\t" << b14 << endl;  
      cout << acos(pz/sqrt(px*px+py*py+pz*pz))*DEG << endl;
      cout << sqrt(px*px+py*py+pz*pz) << endl;      
  }   */ 
  if (0.938*0.938+2.*0.938*(11.-sqrt(px*px+py*py+pz*pz))-2.*11.*sqrt(px*px+py*py+pz*pz)*(1-pz/sqrt(px*px+py*py+pz*pz)) < 4) continue;
  hrate_PTheta_seamus_gen->Fill(acos(pz/sqrt(px*px+py*py+pz*pz))*DEG,sqrt(px*px+py*py+pz*pz),weight);
}
// cout << "evncounter " << evncounter << endl;

TCanvas *c_rate_PTheta_compare = new TCanvas("rate_PTheta_compare","rate_PTheta_compare",2200,1200);
c_rate_PTheta_compare->Divide(2,2);
c_rate_PTheta_compare->cd(1);
gPad->SetLogz();
hrate_PTheta_zwzhao_gen->Scale(1/1000.);
hrate_PTheta_zwzhao_gen->SetMinimum(1e-2);
hrate_PTheta_zwzhao_gen->SetMaximum(12);
hrate_PTheta_zwzhao_gen->Draw("colz text");
c_rate_PTheta_compare->cd(2);
gPad->SetLogz();
hrate_PTheta_zwzhao_acc->Scale(1/1000.);
hrate_PTheta_zwzhao_acc->SetMinimum(1e-2);
hrate_PTheta_zwzhao_acc->SetMaximum(12);
hrate_PTheta_zwzhao_acc->Draw("colz text");
c_rate_PTheta_compare->cd(3);
gPad->SetLogz();
hrate_PTheta_seamus_gen->Scale(1./1000.*1.21/120./24./3600.);
hrate_PTheta_seamus_gen->SetMinimum(1e-2);
hrate_PTheta_seamus_gen->SetMaximum(12);
hrate_PTheta_seamus_gen->Draw("colz text");
c_rate_PTheta_compare->cd(4);
gPad->SetLogz();
TH2F *hrate_PTheta_seamus_zwzhao_ratio_gen=(TH2F*) hrate_PTheta_seamus_gen->Clone();
hrate_PTheta_seamus_zwzhao_ratio_gen->Divide(hrate_PTheta_seamus_gen,hrate_PTheta_zwzhao_gen);
hrate_PTheta_seamus_zwzhao_ratio_gen->SetTitle("rate seamus/zwzhao ratio gen");
hrate_PTheta_seamus_zwzhao_ratio_gen->Draw("colz text");}