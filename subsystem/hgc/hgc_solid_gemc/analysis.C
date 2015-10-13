#include <string>
#include <iterator>
#include <algorithm>
#include <iostream> 
#include <fstream>
#include <cmath> 
#include <stdio.h>
#include <vector>
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraph2D.h>
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
// gStyle->SetOptStat(0);
gStyle->SetOptStat(111111);

const double DEG=180./3.1415926;

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
};  // in ev
double eff_PMT[41] = {
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

//safety factor
double factor=0.8;  //PMT and assmbly effective area
factor=factor*0.5;  //for pion, manual reduce 2

char the_filename[200];
sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());

char output_filename[200];
sprintf(output_filename, "%s_output.root",the_filename);
TFile *outputfile=new TFile(output_filename, "recreate");

TH1F *hQE_E=new TH1F("hQE_E","hQE_E;E(eV);QE(%)",50,0,10);
for(int i=0;i<41;i++){
hQE_E->Fill(PhotonEnergy[i],eff_PMT[i]);
}
TH1F *hQE_WL=new TH1F("hQE_WL","hQE_WL;wavelength(nm);QE(%)",50,0,1000);
for(int i=0;i<41;i++){
hQE_WL->Fill(1.24/PhotonEnergy[i]*1e3,eff_PMT[i]);
}

TH1F *hspectrum_E_photon=new TH1F("hspectrum_E_photon",";E (eV);number of photon",100,0,10);
TH1F *hspectrum_WL_photon=new TH1F("hspectrum_WL_photon",";wavelength (nm);number of photon",100,0,1000);

TH1F *hspectrum_E=new TH1F("hspectrum_E",";E (eV);number of photoelectron",100,0,10);
TH1F *hspectrum_WL=new TH1F("hspectrum_WL",";wavelength (nm);number of photoelectron",100,0,1000);

TH1F *hcount=new TH1F("hcount","hcount;number of photoelectron;count",100,0,50);

TH1F *hedep_spd=new TH1F("hedep_spd","hedep_spd;edep;count",500,0,50);

TH2F *hcount_edep_spd=new TH2F("hcount_edep_spd","hcount_edep_spd;hgc_PEcount;spd_edep",100,0,50,500,0,50);

const int n=30; //total number of sector

TH1F *hcount_p_sector[n];
TH2F *hvertexRZ_sector[n],*hvertexXY_sector[n];
// TH1F *hcount_total=new TH1F("hcount_total",,220,0,11);
// hcount_total->SetTitle(Form("photoelectron count in sector %i;P (GeV)",i);  
TH1F *hcount_total_p=new TH1F("hcount_total_p",";P (GeV);number of photoelectron",600,2,8);
TH2F *hcount_total_2D=new TH2F("hcount_total_2D",";P (GeV);#phi (deg); number of photoelectron",600,2,8,360,-180,180);

// char *title[n]={"FA","LA"};
for(int i=0;i<n;i++){
   char hstname[100];   
   sprintf(hstname,"hcount_p_sector%i",i+1);
   hcount_p_sector[i]=new TH1F(hstname,hstname,600,2,8);
   hcount_p_sector[i]->SetTitle(Form("photoelectron in sector %i;P (GeV);count",i+1));  
   sprintf(hstname,"hvertexRZ_sector%i",i+1);
   hvertexRZ_sector[i]=new TH2F(hstname,hstname,130,290,420,300,0,300);
   hvertexRZ_sector[i]->SetTitle(Form("photon vertex RZ in sector %i; Z(cm);R(cm);",i+1));       
   sprintf(hstname,"hvertexXY_sector%i",i+1);
   hvertexXY_sector[i]=new TH2F(hstname,hstname,600,-300,300,600,-300,300);
   hvertexXY_sector[i]->SetTitle(Form("photon vertex XY in sector %i;X(cm); Y(cm)",i+1));         
} 

// std::array<std::vector<int>, 10> vector_p_gen{{std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5),
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5), 
//                                     std::vector<int>(5)
//                                     }};
				    
// std::vector<std::vector<double>> vector_p_gen(30, std::vector<double>);
// std::vector<std::vector<double>> vector_count(30, std::vector<double>);

// array<std::vector<double>, n> vector_p_gen;
// array<std::vector<double>, n> vector_count;

// std::array<std::vector<int>, 30> vector_p_gen;
// std::array<std::vector<int>, 30> vector_count;

// vector<double> vector_p_gen[n];
// vector<double> vector_count[n];
// vector<double> vector_p_gen;
// vector<double> vector_count;

vector<double> vector_p_gen;
vector<double> vector_phi_gen;
vector<double> vector_count;

vector<double> vector_p_gen_1;
vector<double> vector_p_gen_2;
vector<double> vector_p_gen_3;
vector<double> vector_p_gen_4;
vector<double> vector_p_gen_5;
vector<double> vector_p_gen_6;
vector<double> vector_p_gen_7;
vector<double> vector_p_gen_8;
vector<double> vector_p_gen_9;
vector<double> vector_p_gen_10;
vector<double> vector_p_gen_11;
vector<double> vector_p_gen_12;
vector<double> vector_p_gen_13;
vector<double> vector_p_gen_14;
vector<double> vector_p_gen_15;
vector<double> vector_p_gen_16;
vector<double> vector_p_gen_17;
vector<double> vector_p_gen_18;
vector<double> vector_p_gen_19;
vector<double> vector_p_gen_20;
vector<double> vector_p_gen_21;
vector<double> vector_p_gen_22;
vector<double> vector_p_gen_23;
vector<double> vector_p_gen_24;
vector<double> vector_p_gen_25;
vector<double> vector_p_gen_26;
vector<double> vector_p_gen_27;
vector<double> vector_p_gen_28;
vector<double> vector_p_gen_29;
vector<double> vector_p_gen_30;

vector<double> vector_phi_gen_1;
vector<double> vector_phi_gen_2;
vector<double> vector_phi_gen_3;
vector<double> vector_phi_gen_4;
vector<double> vector_phi_gen_5;
vector<double> vector_phi_gen_6;
vector<double> vector_phi_gen_7;
vector<double> vector_phi_gen_8;
vector<double> vector_phi_gen_9;
vector<double> vector_phi_gen_10;
vector<double> vector_phi_gen_11;
vector<double> vector_phi_gen_12;
vector<double> vector_phi_gen_13;
vector<double> vector_phi_gen_14;
vector<double> vector_phi_gen_15;
vector<double> vector_phi_gen_16;
vector<double> vector_phi_gen_17;
vector<double> vector_phi_gen_18;
vector<double> vector_phi_gen_19;
vector<double> vector_phi_gen_20;
vector<double> vector_phi_gen_21;
vector<double> vector_phi_gen_22;
vector<double> vector_phi_gen_23;
vector<double> vector_phi_gen_24;
vector<double> vector_phi_gen_25;
vector<double> vector_phi_gen_26;
vector<double> vector_phi_gen_27;
vector<double> vector_phi_gen_28;
vector<double> vector_phi_gen_29;
vector<double> vector_phi_gen_30;

vector<double> vector_count_1;
vector<double> vector_count_2;
vector<double> vector_count_3;
vector<double> vector_count_4;
vector<double> vector_count_5;
vector<double> vector_count_6;
vector<double> vector_count_7;
vector<double> vector_count_8;
vector<double> vector_count_9;
vector<double> vector_count_10;
vector<double> vector_count_11;
vector<double> vector_count_12;
vector<double> vector_count_13;
vector<double> vector_count_14;
vector<double> vector_count_15;
vector<double> vector_count_16;
vector<double> vector_count_17;
vector<double> vector_count_18;
vector<double> vector_count_19;
vector<double> vector_count_20;
vector<double> vector_count_21;
vector<double> vector_count_22;
vector<double> vector_count_23;
vector<double> vector_count_24;
vector<double> vector_count_25;
vector<double> vector_count_26;
vector<double> vector_count_27;
vector<double> vector_count_28;
vector<double> vector_count_29;
vector<double> vector_count_30;

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

// TTree *tree_solid_cc = (TTree*) file->Get("solid_cc");
// vector<int> *solid_cc_id=0,*solid_cc_hitn=0;
// tree_solid_cc->SetBranchAddress("hitn",&solid_cc_hitn);
// tree_solid_cc->SetBranchAddress("id",&solid_cc_id);

// cout << tree_solid_gem->GetEntries() << " " << tree_header->GetEntries() << " " << tree_generated->GetEntries() << endl;

int nevent = (int)tree_generated->GetEntries();
int nselected = 0;
cout << "nevent " << nevent << endl;

// for (Int_t i=0;i<1000;i++) { 
for (Int_t i=0;i<nevent;i++) { 
  cout << i << "\r";
//   cout << i << "\n";

  tree_header->GetEntry(i);
  
  tree_generated->GetEntry(i);  
  
  int pid_gen=0;
  double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
  for (int j=0;j<gen_pid->size();j++) {
//       cout << gen_pid->at(j) << " " << gen_px->at(j) << " " << gen_py->at(j) << " " << gen_pz->at(j) << " " << gen_vx->at(j) << " " << gen_vy->at(j) << " " << gen_vz->at(j) << endl; 
      pid_gen=gen_pid->at(j);
      px_gen=gen_px->at(j)/1e3;    	//in MeV, convert to GeV
      py_gen=gen_py->at(j)/1e3;		//in MeV, convert to GeV
      pz_gen=gen_pz->at(j)/1e3;      	//in MeV, convert to GeV
      vx_gen=gen_vx->at(j)/1e1;    	//in mm, convert to cm
      vy_gen=gen_vy->at(j)/1e1;		//in mm, convert to cm
      vz_gen=gen_vz->at(j)/1e1;     	//in mm, convert to cm
      p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
      theta_gen=acos(pz_gen/p_gen)*DEG;  	//in deg
      phi_gen=atan2(py_gen,px_gen)*DEG;     	//in deg            
  }  
  
    tree_flux->GetEntry(i);  
    
//     cout << "nhits " << flux_hitn->size() << "\n";

    double edep_spd=0;
    double photon_count[n];
    for (Int_t k=0;k<n;k++) {photon_count[k]=0;}
    
    for (Int_t j=0;j<flux_hitn->size();j++) {
//             cout << "flux " << j << " !!! " << flux_id->at(j) << " " << flux_pid->at(j) << " " << flux_mpid->at(j) << " " << flux_tid->at(j) << " " << flux_mtid->at(j) << " " << flux_trackE->at(j) << " " << flux_totEdep->at(j) << " " << flux_avg_x->at(j) << " " << flux_avg_y->at(j) << " " << flux_avg_z->at(j) << " " << flux_avg_lx->at(j) << " " << flux_avg_ly->at(j) << " " << flux_avg_lz->at(j) << " " << flux_px->at(j) << " " << flux_py->at(j) << " " << flux_pz->at(j) << " " << flux_vx->at(j) << " " << flux_vy->at(j) << " " << flux_vz->at(j) << " " << flux_mvx->at(j) << " " << flux_mvy->at(j) << " " << flux_mvz->at(j) << " " << flux_avg_t->at(j) << endl;           
            
      
    int detector_ID=flux_id->at(j)/1000000;
    int subdetector_ID=(flux_id->at(j)%1000000)/100000;
    int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID << endl;  
    
     if (detector_ID ==2 || subdetector_ID ==2) {
//        cout << "not optical photon? " << flux_pid->at(j) << endl; 
	if (flux_pid->at(j) !=0 ) {
//        cout << "not optical photon? " << flux_pid->at(j) << endl; 
	  continue;    
	}
    }    
//     else continue;

     if (flux_id->at(j) == 5100000) {
       edep_spd += flux_totEdep->at(j);
     }
           

     if (flux_pid->at(j) !=0 ) {
//        cout << "not optical photon? " << flux_pid->at(j) << endl; 
       continue;    
    }    
    
//     int sector_new=(flux_id->at(j)-2200000)/10000;
//     if (sector_new != sector) { cout << "from other sector? " << sector << " " << sector_new << endl;} 
//     sector=sector_new;
       int sector_this=(flux_id->at(j)-2200000)/10000;
//     cout << "sector " << sector << endl;
       
       double E_flux=flux_trackE->at(j)*1e6; //in eV
       double weight=0;
       for (Int_t k=0;k<42;k++) {
	if (PhotonEnergy[k]<=E_flux && E_flux<PhotonEnergy[k+1]) {
	  weight=eff_PMT[k];
	  break;
	}
       }
       
//        weight=1;
	      
       photon_count[sector_this-1] += weight;    

       hspectrum_E->Fill(E_flux,weight);
       double WL_flux=1.24/E_flux*1e3;
       hspectrum_WL->Fill(WL_flux,weight); 
       
       hspectrum_E_photon->Fill(E_flux);
       hspectrum_WL_photon->Fill(WL_flux);        
       
       
       double vx_flux=flux_vx->at(j)/10.;  //in cm
       double vy_flux=flux_vy->at(j)/10.;  //in cm     
     double vr_flux=sqrt(vx_flux*vx_flux+vy_flux*vy_flux); 
     double vz_flux=flux_vz->at(j)/10.; //in cm

     hvertexRZ_sector[sector_this-1]->Fill(vz_flux,vr_flux);
     hvertexXY_sector[sector_this-1]->Fill(vx_flux,vy_flux);    
     
    }
    
    double  counter_total=0;
    int sector=1;
    for (Int_t k=0;k<n;k++) { 
// 	  cout <<k << " " << photon_count[k] << ", "; 
	  if(photon_count[k]>=photon_count[sector-1]) {sector=k+1;}
	  counter_total += photon_count[k]*factor;		  
    }
//     cout << endl;

    hcount->Fill(counter_total);
    
    hedep_spd->Fill(edep_spd);

    hcount_edep_spd->Fill(counter_total,edep_spd);        
    
    double counter = photon_count[sector-1]*factor;

	vector_p_gen.push_back(p_gen); 
	vector_phi_gen.push_back(fmod(phi_gen+180,12.));	
	vector_count.push_back(counter_total); 	
    
       switch(sector){
	case 1: vector_p_gen_1.push_back(p_gen); break;
	case 2: vector_p_gen_2.push_back(p_gen); break;
	case 3: vector_p_gen_3.push_back(p_gen); break;
	case 4: vector_p_gen_4.push_back(p_gen); break;
	case 5: vector_p_gen_5.push_back(p_gen); break;
	case 6: vector_p_gen_6.push_back(p_gen); break;
	case 7: vector_p_gen_7.push_back(p_gen); break;
	case 8: vector_p_gen_8.push_back(p_gen); break;
	case 9: vector_p_gen_9.push_back(p_gen); break;
	case 10: vector_p_gen_10.push_back(p_gen); break;
	case 11: vector_p_gen_11.push_back(p_gen); break;
	case 12: vector_p_gen_12.push_back(p_gen); break;
	case 13: vector_p_gen_13.push_back(p_gen); break;
	case 14: vector_p_gen_14.push_back(p_gen); break;
	case 15: vector_p_gen_15.push_back(p_gen); break;
	case 16: vector_p_gen_16.push_back(p_gen); break;
	case 17: vector_p_gen_17.push_back(p_gen); break;
	case 18: vector_p_gen_18.push_back(p_gen); break;
	case 19: vector_p_gen_19.push_back(p_gen); break;
	case 20: vector_p_gen_20.push_back(p_gen); break;
	case 21: vector_p_gen_21.push_back(p_gen); break;
	case 22: vector_p_gen_22.push_back(p_gen); break;
	case 23: vector_p_gen_23.push_back(p_gen); break;
	case 24: vector_p_gen_24.push_back(p_gen); break;
	case 25: vector_p_gen_25.push_back(p_gen); break;
	case 26: vector_p_gen_26.push_back(p_gen); break;
	case 27: vector_p_gen_27.push_back(p_gen); break;
	case 28: vector_p_gen_28.push_back(p_gen); break;
	case 29: vector_p_gen_29.push_back(p_gen); break;
	case 30: vector_p_gen_30.push_back(p_gen); break;
	default: cout << "wrong sector? " << sector << endl;
    }	
       switch(sector){
	case 1: vector_phi_gen_1.push_back(fmod(phi_gen+180,12.)); break;
	case 2: vector_phi_gen_2.push_back(fmod(phi_gen+180,12.)); break;
	case 3: vector_phi_gen_3.push_back(fmod(phi_gen+180,12.)); break;
	case 4: vector_phi_gen_4.push_back(fmod(phi_gen+180,12.)); break;
	case 5: vector_phi_gen_5.push_back(fmod(phi_gen+180,12.)); break;
	case 6: vector_phi_gen_6.push_back(fmod(phi_gen+180,12.)); break;
	case 7: vector_phi_gen_7.push_back(fmod(phi_gen+180,12.)); break;
	case 8: vector_phi_gen_8.push_back(fmod(phi_gen+180,12.)); break;
	case 9: vector_phi_gen_9.push_back(fmod(phi_gen+180,12.)); break;
	case 10: vector_phi_gen_10.push_back(fmod(phi_gen+180,12.)); break;
	case 11: vector_phi_gen_11.push_back(fmod(phi_gen+180,12.)); break;
	case 12: vector_phi_gen_12.push_back(fmod(phi_gen+180,12.)); break;
	case 13: vector_phi_gen_13.push_back(fmod(phi_gen+180,12.)); break;
	case 14: vector_phi_gen_14.push_back(fmod(phi_gen+180,12.)); break;
	case 15: vector_phi_gen_15.push_back(fmod(phi_gen+180,12.)); break;
	case 16: vector_phi_gen_16.push_back(fmod(phi_gen+180,12.)); break;
	case 17: vector_phi_gen_17.push_back(fmod(phi_gen+180,12.)); break;
	case 18: vector_phi_gen_18.push_back(fmod(phi_gen+180,12.)); break;
	case 19: vector_phi_gen_19.push_back(fmod(phi_gen+180,12.)); break;
	case 20: vector_phi_gen_20.push_back(fmod(phi_gen+180,12.)); break;
	case 21: vector_phi_gen_21.push_back(fmod(phi_gen+180,12.)); break;
	case 22: vector_phi_gen_22.push_back(fmod(phi_gen+180,12.)); break;
	case 23: vector_phi_gen_23.push_back(fmod(phi_gen+180,12.)); break;
	case 24: vector_phi_gen_24.push_back(fmod(phi_gen+180,12.)); break;
	case 25: vector_phi_gen_25.push_back(fmod(phi_gen+180,12.)); break;
	case 26: vector_phi_gen_26.push_back(fmod(phi_gen+180,12.)); break;
	case 27: vector_phi_gen_27.push_back(fmod(phi_gen+180,12.)); break;
	case 28: vector_phi_gen_28.push_back(fmod(phi_gen+180,12.)); break;
	case 29: vector_phi_gen_29.push_back(fmod(phi_gen+180,12.)); break;
	case 30: vector_phi_gen_30.push_back(fmod(phi_gen+180,12.)); break;
	default: cout << "wrong sector? " << sector << endl;
    }	    
        switch(sector){
	case 1: vector_count_1.push_back(counter); break;
	case 2: vector_count_2.push_back(counter); break;
	case 3: vector_count_3.push_back(counter); break;
	case 4: vector_count_4.push_back(counter); break;
	case 5: vector_count_5.push_back(counter); break;
	case 6: vector_count_6.push_back(counter); break;
	case 7: vector_count_7.push_back(counter); break;
	case 8: vector_count_8.push_back(counter); break;
	case 9: vector_count_9.push_back(counter); break;
	case 10: vector_count_10.push_back(counter); break;
	case 11: vector_count_11.push_back(counter); break;
	case 12: vector_count_12.push_back(counter); break;
	case 13: vector_count_13.push_back(counter); break;
	case 14: vector_count_14.push_back(counter); break;
	case 15: vector_count_15.push_back(counter); break;
	case 16: vector_count_16.push_back(counter); break;
	case 17: vector_count_17.push_back(counter); break;
	case 18: vector_count_18.push_back(counter); break;
	case 19: vector_count_19.push_back(counter); break;
	case 20: vector_count_20.push_back(counter); break;
	case 21: vector_count_21.push_back(counter); break;
	case 22: vector_count_22.push_back(counter); break;
	case 23: vector_count_23.push_back(counter); break;
	case 24: vector_count_24.push_back(counter); break;
	case 25: vector_count_25.push_back(counter); break;
	case 26: vector_count_26.push_back(counter); break;
	case 27: vector_count_27.push_back(counter); break;
	case 28: vector_count_28.push_back(counter); break;
	case 29: vector_count_29.push_back(counter); break;
	case 30: vector_count_30.push_back(counter); break;
	default: cout << "wrong sector? " << sector << endl;
    }
    
//      vector_p_gen[sector-1].push_back(p_gen);
//      vector_count[sector-1].push_back(counter);             
//      vector_p_gen.push_back(p_gen);
//      vector_count.push_back(counter);             

    
//     hcount_p_sector[sector-1]->Fill(p_gen);          
    
//     tree_solid_cc->GetEntry(i);   
    
//     for (Int_t j=0;j<solid_cc_hitn->size();j++) {     
//       cout << "solid_gem " << j << " !!! " << solid_gem_id->at(j) << " " << solid_gem_hitn->at(j) << " " << solid_gem_pid->at(j) << " " << solid_gem_trid->at(j) << " " << solid_gem_x->at(j) << " " << solid_gem_y->at(j) << " " << solid_gem_z->at(j) << " " << solid_gem_lxin->at(j) << " " << solid_gem_lyin->at(j) << " " << solid_gem_lzin->at(j) << " " << solid_gem_tin->at(j) << " " << solid_gem_lxout->at(j) << " " << solid_gem_lyout->at(j) << " " << solid_gem_lzout->at(j) << " " << solid_gem_tout->at(j) << " " << solid_gem_px->at(j) << " " << solid_gem_py->at(j) << " " << solid_gem_pz->at(j) << " " << solid_gem_vx->at(j) << " " << solid_gem_vy->at(j) << " " << solid_gem_vz->at(j) << " " << solid_gem_ETot->at(j) << " " << solid_gem_trE->at(j) << " " << solid_gem_weight->at(j) << endl; 
//     }    
    
}
file->Close();

TGraph *gcount_total_p;
TGraph *gcount_total_phi;
TGraph2D *gcount_total_2D;
TGraph *gcount_p_sector[n];

gcount_total_p = new TGraph(vector_p_gen.size(), &(vector_p_gen[0]), &(vector_count[0]));
gcount_total_phi= new TGraph(vector_phi_gen.size(), &(vector_phi_gen[0]), &(vector_count[0]));
gcount_total_2D= new TGraph2D(vector_p_gen.size(), &(vector_p_gen[0]),&(vector_phi_gen[0]), &(vector_count[0]));

// gcount_total_p->Write();
outputfile->WriteObject(gcount_total_p,"gcount_total_p");
outputfile->WriteObject(gcount_total_phi,"gcount_total_phi");
outputfile->WriteObject(gcount_total_2D,"gcount_total_2D");
// outputfile->Append(gcount_total_p);
// outputfile->Append(gcount_total_phi);
// gcount_total_2D->SetDirectory(outputfile);

for (int i=0;i<n;i++){
//       outputfile->WriteObject(*gcount_p_sector+i,Form("gcount_p_sector%i",i+1)); 
//         outputfile->WriteObject(gcount_p_sector[i],Form("gcount_p_sector")); 
      
//   gcount_p_sector[i] = new TGraph(vector_count_1.size(), &(vector_p_gen_1[0]), &(vector_count_1[0])); 
        switch(i+1){
	case 1:  gcount_p_sector[i] = new TGraph(vector_count_1.size(), &(vector_p_gen_1[0]), &(vector_count_1[0])); break;
	case 2:  gcount_p_sector[i] = new TGraph(vector_count_2.size(), &(vector_p_gen_2[0]), &(vector_count_2[0])); break;
	case 3:  gcount_p_sector[i] = new TGraph(vector_count_3.size(), &(vector_p_gen_3[0]), &(vector_count_3[0])); break;
	case 4:  gcount_p_sector[i] = new TGraph(vector_count_4.size(), &(vector_p_gen_4[0]), &(vector_count_4[0])); break;
	case 5:  gcount_p_sector[i] = new TGraph(vector_count_5.size(), &(vector_p_gen_5[0]), &(vector_count_5[0])); break;
	case 6:  gcount_p_sector[i] = new TGraph(vector_count_6.size(), &(vector_p_gen_6[0]), &(vector_count_6[0])); break;
	case 7:  gcount_p_sector[i] = new TGraph(vector_count_7.size(), &(vector_p_gen_7[0]), &(vector_count_7[0])); break;
	case 8:  gcount_p_sector[i] = new TGraph(vector_count_8.size(), &(vector_p_gen_8[0]), &(vector_count_8[0])); break;
	case 9:  gcount_p_sector[i] = new TGraph(vector_count_9.size(), &(vector_p_gen_9[0]), &(vector_count_9[0])); break;
	case 10:  gcount_p_sector[i] = new TGraph(vector_count_10.size(), &(vector_p_gen_10[0]), &(vector_count_10[0])); break;
	case 11:  gcount_p_sector[i] = new TGraph(vector_count_11.size(), &(vector_p_gen_11[0]), &(vector_count_11[0])); break;
	case 12:  gcount_p_sector[i] = new TGraph(vector_count_12.size(), &(vector_p_gen_12[0]), &(vector_count_12[0])); break;
	case 13:  gcount_p_sector[i] = new TGraph(vector_count_13.size(), &(vector_p_gen_13[0]), &(vector_count_13[0])); break;
	case 14:  gcount_p_sector[i] = new TGraph(vector_count_14.size(), &(vector_p_gen_14[0]), &(vector_count_14[0])); break;
	case 15:  gcount_p_sector[i] = new TGraph(vector_count_15.size(), &(vector_p_gen_15[0]), &(vector_count_15[0])); break;
	case 16:  gcount_p_sector[i] = new TGraph(vector_count_16.size(), &(vector_p_gen_16[0]), &(vector_count_16[0])); break;
	case 17:  gcount_p_sector[i] = new TGraph(vector_count_17.size(), &(vector_p_gen_17[0]), &(vector_count_17[0])); break;
	case 18:  gcount_p_sector[i] = new TGraph(vector_count_18.size(), &(vector_p_gen_18[0]), &(vector_count_18[0])); break;
	case 19:  gcount_p_sector[i] = new TGraph(vector_count_19.size(), &(vector_p_gen_19[0]), &(vector_count_19[0])); break;
	case 20:  gcount_p_sector[i] = new TGraph(vector_count_20.size(), &(vector_p_gen_20[0]), &(vector_count_20[0])); break;
	case 21:  gcount_p_sector[i] = new TGraph(vector_count_21.size(), &(vector_p_gen_21[0]), &(vector_count_21[0])); break;
	case 22:  gcount_p_sector[i] = new TGraph(vector_count_22.size(), &(vector_p_gen_22[0]), &(vector_count_22[0])); break;
	case 23:  gcount_p_sector[i] = new TGraph(vector_count_23.size(), &(vector_p_gen_23[0]), &(vector_count_23[0])); break;
	case 24:  gcount_p_sector[i] = new TGraph(vector_count_24.size(), &(vector_p_gen_24[0]), &(vector_count_24[0])); break;
	case 25:  gcount_p_sector[i] = new TGraph(vector_count_25.size(), &(vector_p_gen_25[0]), &(vector_count_25[0])); break;
	case 26:  gcount_p_sector[i] = new TGraph(vector_count_26.size(), &(vector_p_gen_26[0]), &(vector_count_26[0])); break;
	case 27:  gcount_p_sector[i] = new TGraph(vector_count_27.size(), &(vector_p_gen_27[0]), &(vector_count_27[0])); break;
	case 28:  gcount_p_sector[i] = new TGraph(vector_count_28.size(), &(vector_p_gen_28[0]), &(vector_count_28[0])); break;
	case 29:  gcount_p_sector[i] = new TGraph(vector_count_29.size(), &(vector_p_gen_29[0]), &(vector_count_29[0])); break;
	case 30:  gcount_p_sector[i] = new TGraph(vector_count_30.size(), &(vector_p_gen_30[0]), &(vector_count_30[0])); break;
	default: cout << "wrong sector? " << i+1 << endl;
	}
}

TCanvas *c_spectrum = new TCanvas("spectrum","spectrum",1600,800);
c_spectrum->Divide(2,1);
c_spectrum->cd(1);
hspectrum_E->Draw();
c_spectrum->cd(2);
hspectrum_WL->Draw();

TCanvas *c_spectrum_photon = new TCanvas("spectrum_photon","spectrum_photon",1600,800);
c_spectrum_photon->Divide(2,1);
c_spectrum_photon->cd(1);
hspectrum_E_photon->Draw();
c_spectrum_photon->cd(2);
hspectrum_WL_photon->Draw();

TCanvas *c_QE = new TCanvas("QE","QE",1600,800);
c_QE->Divide(2,1);
c_QE->cd(1);
hQE_E->Draw();
gPad->SetLogy(1);
c_QE->cd(2);
hQE_WL->Draw();
gPad->SetLogy(1);

TCanvas *c = new TCanvas("c","c",1600,800);
c->Divide(3,1);
c->cd(1);
hcount->Draw();
c->cd(2);
hedep_spd->Draw();
c->cd(3);
hcount_edep_spd->Draw();

TCanvas *c_count_total_2D = new TCanvas("count_total_2D","count_total_2D",1000,800);
hcount_total_2D->SetAxisRange(2,8,"X");
hcount_total_2D->SetAxisRange(-180,180,"Y");
hcount_total_2D->SetAxisRange(0,50,"Z");    
// hcount_total_2D->Draw("LEGO");      
hcount_total_2D->Draw();
gcount_total_2D->Draw("P"); 

TCanvas *c_count_total_p = new TCanvas("count_total_p","count_total_p",1000,800);
hcount_total_p->SetAxisRange(2,8,"X");
//   hcount_total->SetAxisRange(0,500,"Y");  
hcount_total_p->SetAxisRange(0,50,"Y");    
hcount_total_p->Draw();      
gcount_total_p->Draw("P"); 

TCanvas *c_count_total_phi = new TCanvas("count_total_phi","count_total_phi",1000,800);
// hcount_total->SetAxisRange(2,8,"X");
//   hcount_total->SetAxisRange(0,500,"Y");  
// hcount_total->SetAxisRange(0,50,"Y");    
// hcount_total->Draw();      
gcount_total_phi->Draw("AP"); 

TCanvas *c_count_p_sector = new TCanvas("count_p_sector","count_p_sector",1800,1000);
c_count_p_sector->Divide(6,5);
for (int i=0;i<n;i++){
  c_count_p_sector->cd(i+1);      
//   hcount_p_sector[i]->SetMarkerColor(kBlue);    
  hcount_p_sector[i]->Draw();      
  hcount_p_sector[i]->SetAxisRange(2,8,"X");
//   hcount_p_sector[i]->SetAxisRange(0,500,"Y");  
  hcount_p_sector[i]->SetAxisRange(0,50,"Y");    
  
  gcount_p_sector[i]->Draw("P"); 
//   gcount_p_sector[i]->GetXaxis()->SetRange(2,8);
//   gcount_p_sector[i]->GetYaxis()->SetRange(0,1000);     
}

TCanvas *c_vertexRZ_sector = new TCanvas("vertexRZ_sector","vertexRZ_sector",1800,1000);
c_vertexRZ_sector->Divide(6,5);
for (int i=0;i<n;i++){
  c_vertexRZ_sector->cd(i+1);      
//   hcount_p_sector[i]->SetMarkerColor(kBlue);  
  hvertexRZ_sector[i]->Draw("colz");
  gPad->SetLogz(1);
}


TCanvas *c_vertexXY_sector = new TCanvas("vertexXY_sector","vertexXY_sector",1800,1000);
c_vertexXY_sector->Divide(6,5);
for (int i=0;i<n;i++){
  c_vertexXY_sector->cd(i+1);      
//   hcount_p_sector[i]->SetMarkerColor(kBlue);  
  hvertexXY_sector[i]->Draw("colz");
  gPad->SetLogz(1);
}

outputfile->Write();
outputfile->Flush();
}
