/*
   Code for generation of initial baffle
   configuration

   This uses data from GEMC

   Seamus Riordan
   sriordan@physics.umass.edu
   April 12, 2011
   */

//#define NO_EXT_TARG

#define STRAIGHT_ENDS 

double DEG=180/3.1415926;

double beamE = 11.0;// GeV

double thmin = 22.0;// deg
double thmax = 35.0;// deg
// double thmin = 21.0;// deg
// double thmax = 36.0;// deg

double targ_len = 0.4;//
double targ_z   = 0.1;//

// double xmin  = 0.0;
double xmin  = 0.55;
// double xmin  = 0.35;
double xmax  = 0.8; // x = 0.8 is about the W2 < 4 cutoff
// double pmin  = 0.8;
double pmin  = 1.5;
// double SCALE_MIN_ANG = 1.4; // Artificial scale factor to increase
// double SCALE_MAX_ANG = 1.4; // Artificial scale factor to increase
                            // efficiency
                            
double SCALE_MIN_ANG = 1.0; // Artificial scale factor to increase
double SCALE_MAX_ANG = 1.0; // Artificial scale factor to increase
                            // efficiency                            

// double SCALE_LASTBAF = 0.20; // scale last width to block more gammas
double SCALE_LASTBAF = 0.; // scale last width to block more gammas

double abspmin  = 0.0; // Just ignore momenta less than this

#define nbaf 11
// double bafspace  = 0.3;// m
double bafspace  = 0.28;// m

double minsep_scale = 1.0; // Scale minsep to 
// help prevent more photons
double width_scale  = 1.00; // Scale width to 
// help prevent more photons

double baf_thick = 0.09;

double minr = 0.05;
double maxr = 1.42;

#define MAXSLIT 30

// Radial block granularity
#define NBLOCK 20

#define MASS_P 0.938
#define PI     3.1415927
#define MAXHIT 2000

#include "TFile.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TLine.h"
#include "TH2F.h"
#include "TF1.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"

double getEf(double, double);
void GetPhiWidth(TH1F *, double &, double &);

void GetEugene( int i, double R, double &in, double &out );

int  makebaffle(){

    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(1111111);

    int i, j;

    // Calculate minimum and maximum r for each range

    double dlmin, dlmax;

    double thrmin = thmin*PI/180.0;
    double thrmax = thmax*PI/180.0;
    
//     double rmin_det[nbaf], rmax_det[nbaf];
//     double z_det[nbaf]={0.375,0.655,0.955,1.255,1.555,1.855};  //in m
//     for( i = 0; i < nbaf; i++ ){
// 	printf("%d z_det = %f\n", i, z_det[i] );
// 	dlmin = z_det[i] - targ_len/2.0 - targ_z;
// 	dlmax = z_det[i] + targ_len/2.0 - targ_z;
// 
// 	rmin_det[i] = dlmin*tan(thrmin);
// 	rmax_det[i] = dlmax*tan(thrmax);
// 
// 	printf("rmax_det (%d) = %f\n", i,  rmax_det[i]);
// 	if( rmax_det[i] > maxr ){ printf("reducing %f to %f\n", rmax_det[i], maxr); rmax_det[i] = maxr; }
//     }    

    double rmin[nbaf], rmax[nbaf];
//     double zbaf[nbaf]={0.40,0.68,0.96,1.24,1.52,1.80};  
//     double zbaf[nbaf]={0.355,0.635,0.915,1.195,1.475,1.755};
    double zbaf[nbaf]={0.355,0.495,0.635,0.775,0.915,1.055,1.195,1.335,1.475,1.615,1.755};            
// my @PlateZ  = (30+$targetoff-4.5,44+$targetoff-4.5,58+$targetoff-4.5,72+$targetoff-4.5,86+$targetoff-4.5,100+$targetoff-4.5,114+$targetoff-4.5,128+$targetoff-4.5,142+$targetoff-4.5,156+$targetoff-4.5,170+$targetoff-4.5);
    
//     double lastz  = bafspace*nbaf + targ_z;
//     double firstz = bafspace + targ_z;
    double firstz = zbaf[0];
    double lastz  = zbaf[nbaf-1];     
    for( i = 0; i < nbaf; i++ ){
// 	zbaf[i] = targ_z + bafspace*(i+1);
	printf("%d zbaf = %f\n", i, zbaf[i] );

// 	dlmin = zbaf[i] - targ_len/2.0 - baf_thick/2.0;
// 	dlmax = zbaf[i] + targ_len/2.0 + baf_thick/2.0;
// 	dlmin = zbaf[i] - targ_len/2.0 - baf_thick - targ_z;
// 	dlmax = zbaf[i] + targ_len/2.0 + baf_thick - targ_z;
// 	dlmin = zbaf[i] - targ_len/2.0 - baf_thick/2. - targ_z;
// 	dlmax = zbaf[i] + targ_len/2.0 + baf_thick/2. - targ_z;
// 	dlmin = zbaf[i] - targ_len/2.0 - targ_z;
// 	dlmax = zbaf[i] + targ_len/2.0 + baf_thick - targ_z;	
	dlmin = zbaf[i] - targ_len/2.0 - targ_z;
	dlmax = zbaf[i] + targ_len/2.0 + baf_thick - targ_z;
// 	dlmin = zbaf[i] - targ_z;
// 	dlmax = zbaf[i] - targ_z;

	rmin[i] = dlmin*tan(thrmin);
	rmax[i] = dlmax*tan(thrmax);

	printf("rmin (%d) = %f\n", i,  rmin[i]);
	if( rmin[i] < minr ){ printf("elarging %f to %f\n", rmin[i], minr); rmin[i] = minr; }
	
	printf("rmax (%d) = %f\n", i,  rmax[i]);
	if( rmax[i] > maxr ){ printf("reducing %f to %f\n", rmax[i], maxr); rmax[i] = maxr; }
    }
    


//     double absminr[6] = {3.9,15.3,26.6,37.9,49.2,60.4}; // cm
// 	double absminr[6] = {3.8,14.5,25.3,36.0,46.8,57.5}; // cm    
// 	double absminr[6] = {3.,14.,25.,35.0,46.,57.}; // cm    

    // Make sure this has a minimum angle enforced
//     for( i = 0; i < nbaf; i++ ){
// 	if( rmin[i] < absminr[i]*0.01 ){
// 	    rmin[i] = absminr[i]*0.01;
// 	}
//     }

    //  Break down phi profiles

//     TChain *T = new TChain("fluxT");
//    T->Add("testcleo/solout_CLEO_LD2_120d_nobaf_11GeV.root");
    //  T->Add("solout_CLEO_LD2_120d_nobaf_11GeV.root");
//    T->Add("solout_BaBar_nobaf_LD2_120d_11GeV.root");
    //T->Add("oldcleo/solout_CLEO_nobaf_LD2_120d_11GeV.root");

//     T->Add("solout_CLEO_LD2_120d_nobaf_11GeV.root");
//     T->Add("../solout_CLEO_LD2_120d_nobaf_11GeV_narrowspac_raster.root");    
//      int nhit;
//     double x[MAXHIT],y[MAXHIT],z[MAXHIT],px[MAXHIT],py[MAXHIT],pz[MAXHIT],p0x[MAXHIT],p0y[MAXHIT],p0z[MAXHIT];
//     double v0x[MAXHIT],v0y[MAXHIT],v0z[MAXHIT],weight[MAXHIT], trid[MAXHIT];
// 
//     double th, phi, Ef, nu, xbj, Q2, phi2, W;
//     bool isfill;
// 
// 
//     T->SetBranchAddress("nhits", &nhit);
//     T->SetBranchAddress("x", x);
//     T->SetBranchAddress("y", y);
//     T->SetBranchAddress("z", z);
//     T->SetBranchAddress("px", px);
//     T->SetBranchAddress("py", py);
//     T->SetBranchAddress("pz", pz);
//     T->SetBranchAddress("p0x", p0x);
//     T->SetBranchAddress("p0y", p0y);
//     T->SetBranchAddress("p0z", p0z);
//     T->SetBranchAddress("v0x", v0x);
//     T->SetBranchAddress("v0y", v0y);
//     T->SetBranchAddress("v0z", v0z);
//     T->SetBranchAddress("weight", weight);
//     T->SetBranchAddress("trid", trid);
   
// TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_point_eDIS_1e6.root");   
TFile *file_rate=new TFile("/home/zwzhao/work_halla/solid/solid_svn/solid/evgen/eicRate_20101102/output/PVDIS_LD2/rate_solid_PVDIS_LD2_eDIS_1e6.root");

double pf,theta,phi,Q2,x,W,rate,Abeam,vx,vy,vz;
TTree *T = (TTree*) file_rate->Get("T");
T->SetBranchAddress("pf",&pf);
T->SetBranchAddress("theta",&theta);
T->SetBranchAddress("phi",&phi);
T->SetBranchAddress("Q2",&Q2);
T->SetBranchAddress("x",&x);
T->SetBranchAddress("W",&W);
T->SetBranchAddress("rate",&rate);
T->SetBranchAddress("Abeam",&Abeam);
T->SetBranchAddress("vx",&vx);
T->SetBranchAddress("vy",&vy);
T->SetBranchAddress("vz",&vz);


// TFile *file=new TFile("baffleCLEOv8_point_eDIS_nobaffle.root");
TFile *file=new TFile("baffleCLEOv8_eDIS_nobaffle.root");

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
Int_t flux_ID_array[1000],flux_pid_array[1000],flux_mpid_array[1000];
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

    TH1F *hblock[nbaf][NBLOCK];

    // Histograms will store information on phi distributions
    for( i = 0; i < nbaf; i++ ){
	for( j = 0; j < NBLOCK; j++ ){
	    hblock[i][j] = new TH1F(Form("hb_%d_%d", i,j), Form("hb_%d_%d", i, j),
		 300, -10., 20.);
	}
    }

for (Int_t i=0;i<T->GetEntries();i++) {  
  cout << i << "\r";
  T->GetEntry(i);
//   cout << i << "\n";
//   double theta=0,mom=0,phi=0,vx=0,vy=0,vz=0;  
  Tgen->GetEntry(i+1);  
//   for (Int_t j=0;j<gen_ngen;j++) {
// //       cout <<  gen_evn << " " << gen_ngen << " " << *(gen_id+j) << " " << *(gen_px+j) << " " << *(gen_py+j) << " " << *(gen_pz+j) << " " << *(gen_p+j) <<endl;
//       theta=*(gen_theta+j);
//       phi=*(gen_phi+j);      
//       mom=*(gen_p+j)/1e3;
//       vx=*(gen_vx+j);
//       vy=*(gen_vy+j);
//       vz=*(gen_vz+j);      
//       
//       hgen->Fill(theta,mom);
//       hgen_vertexZ->Fill(theta,vz);
//       hgen_vertexR->Fill(theta,sqrt(vx*vx+vy*vy));      
//   }  
  
    int counter_hit[2]={0,0};
//   int counter[n]={0,0,0,0,0,0,0,0,0,0};
    Tflux->GetEntry(i+1);    
    for (Int_t j=0;j<flux_nfluxhit;j++) {
//       cout << j << endl;
//       cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
    
//     int detector_ID=*(flux_ID+j)/1000000;
//     int subdetector_ID=(*(flux_ID+j)%1000000)/100000;
//     int subsubdetector_ID=((*(flux_ID+j)%1000000)%100000)/10000;
//     cout << detector_ID << " " << subdetector_ID << " "  << subsubdetector_ID << endl;  
    
//     if (detector_ID==0 && subsubdetector_ID==0) hbaffleplate[subdetector_ID-1]->Fill(*(flux_x+j)/10,*(flux_y+j)/10);
//     if (detector_ID==0 && subsubdetector_ID==1) hbaffleplate_observer[subdetector_ID-1]->Fill(*(flux_x+j)/10,*(flux_y+j)/10);

//     int hit_id=-1;
//     if (*(flux_ID+j)==3110000) hit_id=0;
//     if (*(flux_ID+j)==3210000) hit_id=1;    
//     if (hit_id==-1) continue;  //skip other subsubdetector

//     if (*(flux_pid+j)!=211) continue;

//     counter_hit[hit_id]++;
//      if (detector_ID != 0) continue; //not baffle observer
     
     int thisbaf=*(flux_ID+j)-1;
//      for (int k=0;k<nbaf;k++) if (fabs(/1000.-zbaf[k])<0.01) thisbaf=k;      
	// Base cuts
	if(  W < 2.0  ) continue;	//
        if( x < xmin || x > xmax || pf < pmin ) continue;

	double r=sqrt(pow(*(flux_x+j),2)+pow(*(flux_y+j),2))/1e3;	
	
	if( r < rmin[thisbaf] || r > rmax[thisbaf] ) continue;

	int thisblock = (r-rmin[thisbaf])*NBLOCK/(rmax[thisbaf]-rmin[thisbaf]);

// 	cout << "baf " << thisbaf << " block " << thisblock << endl;
	
	double hit_y=*(flux_y+j)-gen_vy[0],hit_x=*(flux_x+j)-gen_vx[0];
	double hit_phi=fabs(atan(hit_y/hit_x)*DEG);
	if (hit_y>0 && hit_x>0) hit_phi=hit_phi;
	if (hit_y>0 && hit_x<0) hit_phi=180-hit_phi;
	if (hit_y<0 && hit_x<0) hit_phi=180+hit_phi;
	if (hit_y<0 && hit_x>0) hit_phi=360-hit_phi;  
	if (gen_phi[0]>340 && hit_phi<20) hit_phi=hit_phi+360;
// 	double phi2 = atan2(hit_y,hit_x)*180/3.14159;
// 	cout << "phi " << phi2 << " " << hit_phi << endl;
// 	    printf("Filling %d block %d with %f\n", thisbaf, thisblock, (phi2-phi)*PI/180.0);

	    hblock[thisbaf][thisblock]->Fill(hit_phi-gen_phi[0], rate);
// 	if (hit_phi<=gen_phi[0])    cout << "negative " << hit_phi << " " <<  gen_phi[0] << " " << gen_theta[0] << " " << gen_p[0] << endl;
// 	if (fabs(hit_phi-gen_phi[0])>12)    cout << "too much             " << hit_phi << " " <<  gen_phi[0] << " " << gen_theta[0] << " " << gen_p[0] << endl;
	
  }  
}
	    
    double phimin[nbaf][NBLOCK], phimax[nbaf][NBLOCK];

    for( i = 0; i < nbaf; i++ ){
	for( j = 0; j < NBLOCK; j++ ){
// 	    cout << i << "  " << j << endl;	    	  
	    GetPhiWidth(hblock[i][j], phimin[i][j], phimax[i][j] );
	}
    }
    
//     TCanvas *c_block = new TCanvas("phi","phi",1500,900);
//     c_block->Divide(NBLOCK,nbaf);
//     for( i = 0; i < nbaf; i++ ){    
// 	for( j = 0; j < NBLOCK; j++ ){
// 	    c_block->cd(NBLOCK*i+j+1);
// 	    hblock[i][j]->Draw();
// 	}
//     }
    TCanvas *c_block0 = new TCanvas("0","1",1500,900);
    c_block0->Divide(5,4);          
    for( i = 0; i < 1; i++ ){    
	for( j = 0; j < NBLOCK; j++ ){
	    c_block0->cd(j+1);
// 	    gPad->SetLogx(1);
// 	    gPad->SetLogy(1);	    
	    hblock[i][j]->Draw();   
// 	    hblock[i][j]->Fit("gaus");
	    TLine *line1 = new TLine(phimin[i][j],0,phimin[i][j],hblock[i][j]->GetMaximum());
	    line1->SetLineColor(kRed);
	    line1->Draw();    
	    TLine *line2 = new TLine(phimax[i][j],0,phimax[i][j],hblock[i][j]->GetMaximum());
	    line2->SetLineColor(kRed);
	    line2->Draw();    
	}
    }  
    
    TCanvas *c_block10 = new TCanvas("10","10",1500,900);  
    c_block10->Divide(5,4);          
    for( i = 10; i < 11; i++ ){    
	for( j = 0; j < NBLOCK; j++ ){
	    c_block10->cd(j+1);
// 	    gPad->SetLogx(1);
// 	    gPad->SetLogy(1);	    
	    hblock[i][j]->Draw();
// 	    hblock[i][j]->Fit("gaus");   
	    TLine *line1 = new TLine(phimin[i][j],0,phimin[i][j],hblock[i][j]->GetMaximum());
	    line1->SetLineColor(kRed);
	    line1->Draw();    
	    TLine *line2 = new TLine(phimax[i][j],0,phimax[i][j],hblock[i][j]->GetMaximum());
	    line2->SetLineColor(kRed);
	    line2->Draw();    
	}
    }          

    double r[nbaf][NBLOCK+1];
    double sphi[nbaf][NBLOCK];
    double dphi[nbaf][NBLOCK];
    int bcnt,rcnt;
    for( bcnt = 0; bcnt < nbaf; bcnt++ ){
	for( rcnt = 0; rcnt < NBLOCK; rcnt++ ){
	    r[bcnt][rcnt] = (rmax[bcnt]-rmin[bcnt])*((double) rcnt)/((double) NBLOCK) + rmin[bcnt];
	    sphi[bcnt][rcnt]=phimin[bcnt][rcnt];
	    dphi[bcnt][rcnt]=phimax[bcnt][rcnt];
	}
	r[bcnt][NBLOCK] = rmax[bcnt];
    }
    
    for( bcnt = 0; bcnt < nbaf; bcnt++ ){
	printf("[\n");
	for( rcnt = 0; rcnt < NBLOCK; rcnt++ ){    
	    if (rcnt < NBLOCK-1) printf("%5.2f, %5.2f, %5.2f, %5.2f,\n", r[bcnt][rcnt]*100.0, r[bcnt][rcnt+1]*100.0, sphi[bcnt][rcnt], dphi[bcnt][rcnt]);
	    else printf("%5.2f, %5.2f, %5.2f, %5.2f\n", r[bcnt][rcnt]*100.0, r[bcnt][rcnt+1]*100.0, sphi[bcnt][rcnt], dphi[bcnt][rcnt]);	    
	}
	if (bcnt < nbaf-1) printf("],\n");
	else printf("]\n");
    }

    printf("(");
    for( bcnt = 0; bcnt < nbaf; bcnt++ ){
	printf("%5.2f, ", r[bcnt][0]*100.0);
    }
    printf(");\n");

    printf("( ");
    for( bcnt = 0; bcnt < nbaf; bcnt++ ){
// 	printf("%5.2f, ", r[bcnt][NBLOCK-1]*100.0);
	printf("%5.2f, ", r[bcnt][NBLOCK]*100.0);
    }
    printf(");\n");

//     printf("nslit = %d\n", nslit);
    
    // This block plots the widths
    /*
    for( i = 0; i < nbaf; i++ ){
	can = new TCanvas();
	can->Divide(5,4);
	for( j = 0; j < NBLOCK; j++ ){
	    can->cd(j+1);
//	    gPad->SetLogy();

	    hblock[i][j]->SetTitle(Form("Baffle %d, Block %d", i,j));
	    hblock[i][j]->GetXaxis()->SetTitle("#phi [deg]");
	    hblock[i][j]->GetXaxis()->CenterTitle();

	    hblock[i][j]->Draw();

	    TLine *minl = new TLine( phimin[i][j], 0, phimin[i][j], hblock[i][j]->GetMaximum()*0.9 );
	    TLine *maxl = new TLine( phimax[i][j], 0, phimax[i][j], hblock[i][j]->GetMaximum()*0.9 );

	    minl->SetLineColor(kRed);
	    maxl->SetLineColor(kGreen);

	    minl->Draw();
	    maxl->Draw();
	}
    }
    */


    return 0;
}

double getEf( double x, double th ){
    return x*MASS_P*beamE/(x*MASS_P + beamE*(1.0-cos(th)));
}


void GetPhiWidth(TH1F *h, double &min, double &max){
    int bin, i;
    double thresh;

    if( h->GetEntries() < 100 ){ 
	min = -1;
	max = -1;
	return;
    }

    // Use integral
    thresh = 0.02*h->Integral();

    /*
    thresh = 0.02*h->GetMaximum();
    for( i = h->GetMaximumBin(); i >= 1; i-- ){
	if( h->GetBinContent(i) < thresh ){
	    min = h->GetBinCenter(i);
	    break;
	}
    }
    */

    i = 1;
    while( h->Integral(1,i) < thresh ){ i++;}
    min = h->GetBinCenter(i);
    
    // Artificially scale this
    min *= SCALE_MIN_ANG;

    /*
    for( i = h->GetMaximumBin(); i < h->GetNbinsX(); i++ ){
	if( h->GetBinContent(i) < thresh ){
	    max = h->GetBinCenter(i);
	    break;
	}
    }
    */

    i = h->GetNbinsX();
    while( h->Integral(1,i) > h->Integral()-thresh ){ i--; }
    max = h->GetBinCenter(i);
    //     cout << "max " << max << " " << i << endl;    
    max *= SCALE_MAX_ANG;



    return;
}




void GetEugene( int pidx, double r, double &in, double &out ){
    // Eugene's Parameterization

    double baf[6][80] = {
	    {	 3.90 ,   5.44 ,  176.26 , 183.00 ,
	    5.44 ,   6.98 ,  176.44 , 182.13 ,
	    6.98 ,   8.52 ,  176.61 , 181.67 ,
	    8.52 ,  10.06 ,  176.75 , 181.78 ,
	    10.06 ,  11.60 ,  176.89 , 181.90 ,
	    11.60 ,  13.14 ,  177.03 , 182.01 ,
	    13.14 ,  14.68 ,  177.18 , 182.12 ,
	    14.68 ,  16.22 ,  177.32 , 182.24 ,
	    16.22 ,  17.76 ,  177.46 , 182.35 ,
	    17.76 ,  19.30 ,  177.60 , 182.46 ,
	    19.30 ,  20.84 ,  177.74 , 182.58 ,
	    20.84 ,  22.38 ,  177.88 , 182.69 ,
	    22.38 ,  23.92 ,  178.02 , 182.80 ,
	    23.92 ,  25.46 ,  178.16 , 182.92 ,
	    25.46 ,  27.00 ,  178.30 , 183.03 ,
	    27.00 ,  28.54 ,  178.44 , 183.15 ,
	    28.54 ,  30.08 ,  178.58 , 183.26 ,
	    30.08 ,  31.62 ,  178.72 , 183.37 ,
	    31.62 ,  33.16 ,  178.86 , 183.49 ,
	    33.16 ,  34.70 ,  179.00 , 183.60 	},
// #2
	    {	15.30 ,  17.25 ,  175.93 , 182.78 ,
	    17.25 ,  19.20 ,  176.14 , 182.56 ,
	    19.20 ,  21.15 ,  176.35 , 182.36 ,
	    21.15 ,  23.10 ,  176.58 , 182.19 ,
	    23.10 ,  25.05 ,  176.81 , 182.05 ,
	    25.05 ,  27.00 ,  177.06 , 181.93 ,
	    27.00 ,  28.95 ,  177.28 , 181.98 ,
	    28.95 ,  30.90 ,  177.46 , 182.12 ,
	    30.90 ,  32.85 ,  177.64 , 182.26 ,
	    32.85 ,  34.80 ,  177.82 , 182.41 ,
	    34.80 ,  36.75 ,  178.00 , 182.55 ,
	    36.75 ,  38.70 ,  178.18 , 182.70 ,
	    38.70 ,  40.65 ,  178.35 , 182.84 ,
	    40.65 ,  42.60 ,  178.53 , 182.98 ,
	    42.60 ,  44.55 ,  178.71 , 183.13 ,
	    44.55 ,  46.50 ,  178.89 , 183.27 ,
	    46.50 ,  48.45 ,  179.07 , 183.41 ,
	    48.45 ,  50.40 ,  179.25 , 183.56 ,
	    50.40 ,  52.35 ,  179.42 , 183.70 ,
	    52.35 ,  54.30 ,  179.60 , 183.84 	},
// #3 plate    
	    { 26.60 ,  28.96 ,  175.71 , 182.49 ,                    
	    28.96 ,  31.32 ,  175.95 , 182.40 ,                   
	    31.32 ,  33.68 ,  176.20 , 182.32 ,                   
	    33.68 ,  36.04 ,  176.46 , 182.27 ,                   
	    36.04 ,  38.40 ,  176.73 , 182.23 ,                   
	    38.40 ,  40.76 ,  177.02 , 182.22 ,                   
	    40.76 ,  43.12 ,  177.31 , 182.22 ,                   
	    43.12 ,  45.48 ,  177.62 , 182.23 ,                   
	    45.48 ,  47.84 ,  177.93 , 182.28 ,                   
	    47.84 ,  50.20 ,  178.15 , 182.46 ,                   
	    50.20 ,  52.56 ,  178.36 , 182.63 ,                   
	    52.56 ,  54.92 ,  178.58 , 182.81 ,                   
	    54.92 ,  57.28 ,  178.80 , 182.98 ,                   
	    57.28 ,  59.64 ,  179.01 , 183.16 ,                   
	    59.64 ,  62.00 ,  179.23 , 183.33 ,                   
	    62.00 ,  64.36 ,  179.45 , 183.51 ,                   
	    64.36 ,  66.72 ,  179.67 , 183.68 ,                   
	    66.72 ,  69.08 ,  179.88 , 183.85 ,                   
	    69.08 ,  71.44 ,  180.10 , 184.03 ,                   
	    71.44 ,  73.80 ,  180.32 , 184.21	},                  
//#4 plate
	    { 37.90  , 40.67  , 175.38 , 182.05 ,
	    40.67  , 43.44  , 175.66 , 182.04 ,
	    43.44  , 46.21  , 175.95 , 182.04 ,
	    46.21  , 48.98  , 176.25 , 182.05 ,
	    48.98  , 51.75  , 176.57 , 182.08 ,
	    51.75  , 54.52  , 176.89 , 182.13 ,
	    54.52  , 57.29  , 177.22 , 182.19 ,
	    57.29  , 60.06  , 177.57 , 182.27 ,
	    60.06  , 62.83  , 177.92 , 182.36 ,
	    62.83  , 65.60  , 178.29 , 182.47 ,
	    65.60  , 68.37  , 178.66 , 182.66 ,
	    68.37  , 71.14  , 178.90 , 182.84 ,
	    71.14  , 73.91  , 179.15 , 183.02 ,
	    73.91  , 76.68  , 179.39 , 183.22 ,
	    76.68  , 79.45  , 179.65 , 183.42 ,
	    79.45  , 82.22  , 179.90 , 183.62 ,
	    82.22  , 84.99  , 180.16 , 183.84 ,
	    84.99  , 87.76  , 180.43 , 184.06 ,
	    87.76  , 90.53  , 180.71 , 184.28 ,
	    90.53  , 93.30  , 180.98 , 184.51	},
//#5 plate
	    { 49.20  , 52.38  , 175.06 , 181.61 ,
	    52.38  , 55.56  , 175.37 , 181.64 ,
	    55.56  , 58.74  , 175.70 , 181.70 ,
	    58.74  , 61.92  , 176.04 , 181.76 ,
	    61.92  , 65.10  , 176.39 , 181.84 ,
	    65.10  , 68.28  , 176.76 , 181.94 ,
	    68.28  , 71.46  , 177.13 , 182.05 ,
	    71.46  , 74.64  , 177.52 , 182.17 ,
	    74.64  , 77.82  , 177.91 , 182.31 ,
	    77.82  , 81.00  , 178.32 , 182.46 ,
	    81.00  , 84.18  , 178.75 , 182.63 ,
	    84.18  , 87.36  , 179.20 , 182.85 ,
	    87.36  , 90.54  , 179.48 , 183.06 ,
	    90.54  , 93.72  , 179.76 , 183.28 ,
	    93.72  , 96.90  , 180.05 , 183.51 ,
	    96.90  ,100.08  , 180.35 , 183.75 ,
	    100.08 ,103.26  , 180.65 , 183.99 ,
	    103.26 ,106.44  , 180.96 , 184.24 ,
	    106.44 ,109.62  , 181.27 , 184.49 ,
	    109.62 ,112.80  , 181.59 , 184.75	},
//#6 plate
	    { 60.40  , 63.98  , 174.92 , 181.35 ,
	    63.98  , 67.56  , 175.27 , 181.43 ,
	    67.56  , 71.14  , 175.63 , 181.52 ,
	    71.14  , 74.72  , 176.00 , 181.63 ,
	    74.72  , 78.30  , 176.38 , 181.75 ,
	    78.30  , 81.88  , 176.78 , 181.88 ,
	    81.88  , 85.46  , 177.18 , 182.02 ,
	    85.46  , 89.04  , 177.60 , 182.18 ,
	    89.04  , 92.62  , 178.03 , 182.35 ,
	    92.62  , 96.20  , 178.47 , 182.53 ,
	    96.20  , 99.78  , 178.92 , 182.73 ,
	    99.78  ,103.36  , 179.39 , 182.94 ,
	    103.36 , 106.94 ,  179.88,  183.19,
	    106.94 , 110.52 ,  180.20,  183.43,
	    110.52 , 114.10 ,  180.52,  183.69,
	    114.10 , 117.68 ,  180.84,  183.94,
	    117.68 , 121.26 ,  181.17,  184.21,
	    121.26 , 124.84 ,  181.51,  184.48,
	    124.84 , 128.42 ,  181.86,  184.76,
	    128.42 , 132.00 ,  182.21,  185.04	}
    };

    ////   Find R for this

    int idx = 0;

    if( r*100.0 < baf[pidx][0] || baf[pidx][19*4+1] <= r*100 ){
	in  = 0.0;
	out = 0.0;
	return;
    }

    while( !( baf[pidx][idx*4] <= r*100.0 && r*100.0 < baf[pidx][idx*4+1] ) ) { 
	idx++; 
    }

    double scale = 0.0;
    scale = (r*100.0 - baf[pidx][idx])/(baf[pidx][idx+1] - baf[pidx][idx]);


    double thisin, thisout;

    thisin  = scale*( baf[pidx][(idx+1)*4+2]-baf[pidx][(idx)*4+2] ) + baf[pidx][(idx)*4+2];
    thisout = scale*( baf[pidx][(idx+1)*4+3]-baf[pidx][(idx)*4+3] ) + baf[pidx][(idx)*4+3];

    // These are the block positions.  The slits are complementary to them

    in  = thisout;
    out = (360.0/30.0 + thisin);

    return;
}
