#include <iomanip>
#include <iostream>
using namespace std;

void background(string input_filename,int Nevent){

///read hits from a txt file produced by roo2hit.C
  
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(111111);

const double DEG=180./3.1415926;

char output_filename[80];
sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.find(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

const int n=15; // number of detector
const int m=4; //number of particles

TH2F *hhits[n][m],*hvertex[n][m];
TH1F *hrate[n][m],*hEflux[n][m];
TH1F *hP_log[n][m],*hE_log[n][m];
TH2F *hER_log[n][m];
TH2F *hEkR_log[n][m];
TH2F *hEkR_log_cut[n][m];

for(int k=0;k<n;k++){
  for(int l=0;l<m;l++){
   char hstname[100];
   sprintf(hstname,"hits_%i_%i",k,l);
   hhits[k][l]=new TH2F(hstname,hstname,300,-300,300,300,-300,300);
   sprintf(hstname,"vertex_%i_%i",k,l);
   hvertex[k][l]=new TH2F(hstname,hstname,500,-500,500,400,-400,400);
   sprintf(hstname,"rate_%i_%i",k,l);
   hrate[k][l]=new TH1F(hstname,hstname,300,0,300);
   hrate[k][l]->SetTitle(";R (cm);rate (kHz/mm2)");
   sprintf(hstname,"Eflux_%i_%i",k,l);
   hEflux[k][l]=new TH1F(hstname,hstname,300,0,300);
   hEflux[k][l]->SetTitle(";R (cm);Eflux (GeV/10cm2/s)");

    sprintf(hstname,"P_log_%i_%i",k,l);
    hP_log[k][l]=new TH1F(hstname,hstname,50, -6, 1.3);
    sprintf(hstname,"E_log_%i_%i",k,l);
    hE_log[k][l]=new TH1F(hstname,hstname,50, -6, 1.3);
    sprintf(hstname,"ER_log_%i_%i",k,l);
    hER_log[k][l]=new TH2F(hstname,hstname,50, -6, 1.3,300,0,300); 
    sprintf(hstname,"EkR_log_%i_%i",k,l);
    hEkR_log[k][l] = new TH2F(hstname, hstname, 50, -6, 1.3, 300, 0, 300);    
    sprintf(hstname,"EkR_log_cut_%i_%i",k,l);
    hEkR_log_cut[k][l] = new TH2F(hstname, hstname, 50, -6, 1.3, 300, 0, 300);       
 } 
}
TH1F *hpid=new TH1F("pid","pid",21,-10.5,10.5);

// ifstream input("out_fluxT.txt");

// ifstream input("out_fluxT.txt_solid_BaBar_SIDIS_QGSP_BERT");
// ifstream input("out_fluxT.txt_solid_BaBar_SIDIS_gemc");
// ifstream input("out_fluxT.txt_solid_BaBar_SIDIS_1e6");

// ifstream input("out_fluxT.txt_solid_BaBar_PVDIS");
// ifstream input("out_fluxT.txt_solid_BaBar_PVDIS_Nobaffle");

// ifstream input("out_fluxT.txt_solid_BaBar_PVDIS_Nobaffle_1");
// ifstream input("out_solid_BaBar_PVDIS_Nobaffle_1e5_fluxT.txt");

ifstream input(input_filename.c_str());

if (!input.good()) {cout << "can't open file " << endl; return;}

// double Nevent;
// if (input_filename.find(".",0) != string::npos){
//   Nevent=atoi(input_filename.substr(input_filename.find(".")-3,3).c_str());
// //   cout << input_filename.substr(input_filename.find(".",0)-3,3) << endl;
//     cout << Nevent << endl;
//   
// }
  
double current;
if (input_filename.find("PVDIS",0) != string::npos){
  current=50e-6/1.6e-19;  //50uA
//   Nevent=1*1e7;	//50 files, 1e7 events each
//   Nevent=1e6;
//   Nevent=8072221; //out_solid_BaBar_PVDIS_1e7_small.root
//   Nevent=4080250; out_solid_BaBar_PVDIS_CClightout_neutron_1e7_small.root  
  cout << " PVDIS " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("SIDIS_3he",0) != string::npos){
  current=15e-6/1.6e-19;   //15uA
//   Nevent=5e7;
//   Nevent=5e7;
  cout << " SIDIS_3he " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("SIDIS_proton",0) != string::npos){
  current=100e-9/1.6e-19;   //100nA
//   Nevent=5e7;
//   Nevent=5e7;
  cout << " SIDIS_proton " << current << " " << Nevent <<  endl;  
}
else if (input_filename.find("JPsi",0) != string::npos){
  current=3e-6/1.6e-19;   //3uA
//   Nevent=5e6;
  cout << " JPsi " << current << " " << Nevent <<  endl;  
}
else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}


int yescounter=0,nocounter=0;

Int_t flux_evn,flux_nfluxhit,flux_ID,flux_pid,flux_mpid;
Float_t flux_Edep,flux_E,flux_x,flux_y,flux_z,flux_vx,flux_vy,flux_vz,flux_px,flux_py,flux_pz;
do{
  input >> flux_evn>> flux_nfluxhit >> flux_ID >> flux_pid >> flux_mpid >>  flux_Edep >> flux_E >> flux_x >> flux_y >> flux_z >> flux_vx >> flux_vy >> flux_vz  >> flux_px >> flux_py >> flux_pz;
  
//   if (flux_nfluxhit>300) {cout << flux_evn << endl; break;}
//     if (!(flux_pid == 22 && fabs(flux_E-0.510999)<0.00001) ) {nocounter++; continue;}
  
        yescounter++; 
	
//   if ( flux_ID<1 || flux_ID >6) {cout << "wrong flux_ID " << flux_ID << " for event " << flux_evn << endl; continue;}    
//   hvertex[flux_ID-1]->Fill(flux_vz/10.,flux_vy/10.);
//   if (flux_vz<2000) {  
// // if (flux_vz<-3300 && flux_vz>-3700) {
//     hhits[flux_ID-1]->Fill(flux_x/10.,flux_y/10.);
//     
//     double current=15e-6/1.6e-19;
//     double area=2*3.1415926*sqrt(flux_x**2+flux_y**2)*10.; // in mm2
//     double kHz=1e-3;
//     double Nevent=100*1e7;
//     double weight=(current/Nevent)*kHz/area;
//     hrate[flux_ID-1]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);    
//   }
  
//     if (flux_Edep <=0 && flux_pid==11)  cout << " " <<  flux_evn<< " " <<  flux_nfluxhit << " " <<  flux_ID << " " <<  flux_pid << " " <<  flux_mpid << " " <<   flux_Edep << " " <<  flux_E << " " <<  flux_x << " " <<  flux_y << " " <<  flux_z << " " <<  flux_vx << " " <<  flux_vy << " " <<  flux_vz  << " " <<  flux_px << " " <<  flux_py << " " <<  flux_pz << endl;
  
      switch (flux_pid){
      case 22:     hpid->Fill(0); break;
      case 11:     hpid->Fill(1); break;
      case -11:     hpid->Fill(-1); break;
      case 12:     hpid->Fill(2); break;
      case 14:     hpid->Fill(2); break;      
      case 16:     hpid->Fill(2); break;
      case -12:     hpid->Fill(-2); break;
      case -14:     hpid->Fill(-2); break;      
      case -16:     hpid->Fill(-2); break;
      case 13:     hpid->Fill(3); break;
      case -13:     hpid->Fill(3); break; 
      case 211:     hpid->Fill(4); break;
      case -211:     hpid->Fill(-4); break; 
      case 111:     hpid->Fill(5); break;       
      case -111:     hpid->Fill(-5); break;      
      case 321:     hpid->Fill(6); break;
      case -321:     hpid->Fill(-6); break;
      case 130:     hpid->Fill(7); break; 
      case -130:     hpid->Fill(-7); break;       
      case 2212:     hpid->Fill(8); break;
      case -2212:     hpid->Fill(-8); break;       
      case 2112:     hpid->Fill(9); break; 
      case -2112:     hpid->Fill(-9); break;       
      default:      hpid->Fill(10); break;      
    }
    
//     cout << flux_ID << endl;    
    int detector_ID=flux_ID/100000;
    if ( (detector_ID<11 || detector_ID >16) && detector_ID !=31 && detector_ID !=32 && detector_ID!=21 && detector_ID!=22 && detector_ID!=41 )    
    {
      cout << "wrong flux_ID "  << flux_evn  << " " << flux_nfluxhit << " " << flux_ID << endl;
      continue;
    }
    
    int subdetector_ID=flux_ID/10000; 

    int hit_id=0;
     switch (detector_ID){
	case 11:     hit_id=0; break;
	case 12:     hit_id=1; break;
	case 13:     hit_id=2; break;
	case 14:     hit_id=3; break;
	case 15:     hit_id=4; break;    
	case 16:     hit_id=5; break;
	case 21:     hit_id=6; break;
	case 22:     hit_id=7; break;	
	case 31:     if (subdetector_ID==311) hit_id=8;
		     else if (subdetector_ID==312) hit_id=9;
		     else if (subdetector_ID==313) hit_id=10;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 32:     if (subdetector_ID==321) hit_id=11;
		     else if (subdetector_ID==322) hit_id=12;
		     else if (subdetector_ID==323) hit_id=13;
		     else cout << "wrong flux_ID " << flux_ID << endl;		      
		     break;
	case 40:     if (subdetector_ID==411) hit_id=14; break;
	default:     break;
      }    
    
    int par;
    if(flux_pid==22) par=1;  //photon    
    else if (abs(flux_pid)==11) par=2; //electron or positron
    else if(flux_pid==2112) par=3;  //neutron
    else par=-1;  //skip all other     

//   if (flux_vz<2000) {  
// if (flux_vz<-3700 || -3300<flux_vz) continue;
    
//       if ( 12<=abs(flux_pid) && abs(flux_pid) <=16 ) continue; ///cut away muon and neutrino

//       if ( flux_pid != 22 && abs(flux_pid) !=11 ) continue; ///anything except photon and electron/position

      if ( flux_pid != 22 && abs(flux_pid) !=11 && flux_pid !=2112 ) continue; ///anything except photon and electron and neutron

    
    hP_log[hit_id][par]->Fill(log10(sqrt(flux_px**2+flux_py**2+flux_pz**2)/1e3));
    hE_log[hit_id][par]->Fill(log10(flux_E/1e3)); 
    hER_log[hit_id][par]->Fill(log10(flux_E/1e3),sqrt(flux_x**2+flux_y**2)/10.);

    double Ek=flux_E-sqrt(flux_E**2-flux_px**2-flux_py**2-flux_pz**2);
    hEkR_log[hit_id][par]->Fill(log10(Ek/1e3),sqrt(flux_x**2+flux_y**2)/10.);
    if(flux_E<100 ) {        ///100MeV cut used for photon in later calorimeter simulation
      hEkR_log_cut[hit_id][par]->Fill(log10(Ek/1e3),sqrt(flux_x**2+flux_y**2)/10.);
    }
    
//     if(1<flux_E && flux_E<100 ) {    
//       if(flux_E<100 ) {  
//     if(100<flux_E ) {      
  if (true){

      hhits[hit_id][par]->Fill(flux_x/10.,flux_y/10.);
      hhits[hit_id][0]->Fill(flux_x/10.,flux_y/10.);      
      hvertex[hit_id][par]->Fill(flux_vz/10.,flux_vy/10.);
      hvertex[hit_id][0]->Fill(flux_vz/10.,flux_vy/10.);      

      double area=2*3.1415926*sqrt(flux_x**2+flux_y**2)*10.; // in mm2
      double kHz=1e-3;    
      double weight=(current/Nevent)*kHz/area;
	
	if (hit_id<6){
	  if (flux_Edep>0) { //gem required non-0 energy deposit
	    hrate[hit_id][par]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
	    hrate[hit_id][0]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
	  }
	}
	else { //other just counting
	  hrate[hit_id][par]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
	  hrate[hit_id][0]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
	}

	area=area/10/100;  //in 10cm2
  //       weight = (current/Nevent)*(flux_E/1e3)/area;
	weight = (current/Nevent)*(sqrt(flux_px**2+flux_py**2+flux_pz**2)/1e3)/area;
	
	hEflux[hit_id][par]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
	hEflux[hit_id][0]->Fill(sqrt(flux_x**2+flux_y**2)/10.,weight);
    }
//     nocounter++;
      
}while (!input.eof());

      cout << "yescounter " << yescounter << " nocounter " << nocounter << endl;
      
TCanvas *c_pid = new TCanvas("pid","pid",900,900);
gPad->SetLogy(1);
hpid->Draw();

TCanvas *c_hits = new TCanvas("hits","hits",1800,900);
c_hits->Divide(n,m);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_hits->cd(l*n+k+1);    
  hhits[k][l]->Draw("colz");
}
}

TCanvas *c_vertex = new TCanvas("vertex","vertex",1800,900);
c_vertex->Divide(n,m);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  gPad->SetLogz(1);  
  c_vertex->cd(l*n+k+1);    
  hvertex[k][l]->Draw("colz");
}
}


TCanvas *c_rate = new TCanvas("rate","rate",1800,900);
c_rate->Divide(n,m);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_rate->cd(l*n+k+1);    
  hrate[k][l]->Draw();
}
}

TCanvas *c_P_log = new TCanvas("P_log","P_log",1800,900);
c_P_log->Divide(n,m);
gPad->SetLogy(1);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_P_log->cd(l*n+k+1);    
  hP_log[k][l]->Draw(); 
}
}

TCanvas *c_E_log = new TCanvas("E_log","E_log",1800,900);
c_E_log->Divide(n,m);
gPad->SetLogy(1);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_E_log->cd(l*n+k+1);
  hE_log[k][l]->Draw();  
}
}

TCanvas *c_ER_log = new TCanvas("ER_log","ER_log",1800,900);
c_ER_log->Divide(n,m);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_ER_log->cd(l*n+k+1);
  hER_log[k][l]->Draw("colz");  
}
}

TCanvas *c_EkR_log = new TCanvas("EkR_log","EkR_log",1800,900);
c_EkR_log->Divide(n,m);
gPad->SetLogx(1);
gPad->SetLogy(1);
for(int l=0;l<m;l++){
for(int k=0;k<n;k++){
  c_EkR_log->cd(l*n+k+1);
  hEkR_log[k][l]->Draw("colz");  
}
}

gStyle->SetOptStat(0);

TCanvas *c_rateall_gem = new TCanvas("rateall_gem","rateall_gem",900,900);
int color[6]={2,1,3,4,7,6};
for(int k=0;k<6;k++){
  hrate[k][0]->SetLineColor(color[k]);
  hrate[k][0]->SetMarkerColor(color[k]);  
  hrate[k][0]->SetMaximum(100);
  if (k==0) hrate[k][3]->Draw();
  else hrate[k][3]->Draw("same");
}

TCanvas *c_rateall_cherenkov = new TCanvas("rateall_cherenkov","rateall_cherenkov",1200,600);
c_rateall_cherenkov->Divide(2,1);
for(int k=6;k<8;k++){
  c_rateall_cherenkov->cd(k-5);  
  for(int l=0;l<m;l++){
    hrate[k][l]->SetLineColor(l+1);
    if (l==0) hrate[k][l]->Draw();
    else hrate[k][l]->Draw("same");
  }
}

TCanvas *c_rateall_ec = new TCanvas("rateall_ec","rateall_ec",1600,900);
c_rateall_ec->Divide(3,2);
for(int k=8;k<14;k++){
  c_rateall_ec->cd(k-7);  
  for(int l=0;l<m;l++){
    hrate[k][l]->SetLineColor(l+1);
    if (l==0) hrate[k][l]->Draw();
    else hrate[k][l]->Draw("same");
  }
}

TCanvas *c_Eflux_ec = new TCanvas("Eflux_ec","Eflux_ec",1600,900);
c_Eflux_ec->Divide(3,2);
for(int k=8;k<14;k++){
  c_Eflux_ec->cd(k-7);
  gPad->SetLogy(1);
  for(int l=0;l<m;l++){
    hEflux[k][l]->SetMinimum(1e3);
    hEflux[k][l]->SetMaximum(1e8);
    hEflux[k][l]->SetLineColor(l+1);
    if (l==0) hEflux[k][l]->Draw();
    else hEflux[k][l]->Draw("same");
  }
}

outputfile->Write();
outputfile->Flush();
}
