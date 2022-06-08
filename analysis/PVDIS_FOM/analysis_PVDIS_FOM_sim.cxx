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

#include "PVDIS_tri_eff_Rakitha1.h"
using namespace std;

const double pb = 0.85; //beam polarization
bool Is_Rad = false;//whether we use the rate w/o ineternal and pre-vertex rad effects
                    //for eDIS generator, there is no internal and pre-vertex rad effects
                    //only the eAll generator has
                    
const double Mass = 0.938;

//if using 6.6 GeV simulation, comment out the next line
#define USE11GeV

#ifdef USE11GeV
const double BeamEnergy = 11.;
const double runtime = 120.*86400; //LD2 120 days 11GeV
const int Nbin=15;
double bin[Nbin][4]={
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
#else
const double BeamEnergy = 6.6;
const double runtime = 30.*86400; //LD2 120 days 11GeV
const int Nbin = 7;
double bin[Nbin][4]={
0.15,0.30,     0.0,14.0,
0.30,0.35,     0.0,14.0,
0.35,0.40,     0.0,14.0,
0.40,0.45,     0.0,14.0,
0.45,0.50,     0.0,14.0,
0.50,0.55,     0.0,14.0,
0.55,0.80,     0.0,14.0

};
#endif

void analysis_PVDIS_FOM_sim()
{
    //use the output from the fileReducer
    gStyle->SetOptStat(0);
    TFile* f = new TFile("/home/wxiong/Documents/resonance_more/output_PVDIS_fileReducer_11GeV_21_redo.root", "READ");
    TTree* t = (TTree*)f->Get("T_T");
    double Q2 = 0;
    double W = 0;
    double x = 0;
    double y = 0;
    double Abeam = 0;
    double px_gen = 0;
    double py_gen = 0;
    double pz_gen = 0;
    double vx_gen = 0;
    double vy_gen = 0;
    double vz_gen = 0;
    double rate = 0;
    double rateRad = 0;
    double ecR = 0;
    double ecP = 0;
    
    t->SetBranchAddress("Q2",       &Q2     );
    t->SetBranchAddress("W",        &W      );
    t->SetBranchAddress("x",        &x      );
    t->SetBranchAddress("y",        &y      );
    t->SetBranchAddress("Abeam",    &Abeam  );
    
    t->SetBranchAddress("vx",       &vx_gen );
    t->SetBranchAddress("vy",       &vy_gen );
    t->SetBranchAddress("vz",       &vz_gen );
    t->SetBranchAddress("px",       &px_gen );
    t->SetBranchAddress("py",       &py_gen );
    t->SetBranchAddress("pz",       &pz_gen );
    t->SetBranchAddress("rate",     &rate   );
    t->SetBranchAddress("rateRad",  &rateRad);
    
    t->SetBranchAddress("ecR",      &ecR    );
    t->SetBranchAddress("ecP",      &ecP    );
    
    double thatrate[Nbin]={0};
    double Abeam_sum[Nbin]={0};
    double Q2_sum[Nbin] = {0};
    double y_sum[Nbin] = {0};
    
    TH2F *hAbeamErr_Q2x_acc=new TH2F("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",100,0,1,140,0,14);
    TH2F *hAbeam_Q2x_acc=new TH2F("Abeam_Q2x_acc","Abeam_Q2x_acc",100,0,1,140,0,14);
    TH2F *hrate_Q2x_acc=new TH2F("rate_Q2x_acc","rate_Q2x_acc",100,0,1,140,0,14);
    //this histogram just get the rate in Q2 and x bin
    TH2D* tmpRate = new TH2D("rate_Q2x", "rate_Q2x", 10, 0, 1, 14, 0, 14); tmpRate->GetXaxis()->SetTitle("x"); tmpRate->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
    
    for (unsigned int entry = 0; entry < t->GetEntries(); entry++){
        t->GetEntry(entry);
        
        double mom   = sqrt(px_gen*px_gen + py_gen*py_gen + pz_gen*pz_gen);
        double theta = acos(pz_gen/mom);

        Q2           = 2.*BeamEnergy*mom*(1. - cos(theta));
        x            = Q2/(2.*Mass*(BeamEnergy - mom));
        y            = (BeamEnergy - mom)/BeamEnergy;
        W            = sqrt(Mass*Mass + 2.*Mass*(BeamEnergy - mom) - Q2);
        
        if (W < 2) continue; //W < 2 GeV cut
        
        double thisrate = rate;
        if (Is_Rad) thisrate = rateRad;

        //get the trigger efficiency from EC
        double eff = 1.;
#ifdef USE11GeV
        eff = GetElectronTriggerEffi(GetRadiusIndex(ecR), GetMomentumIndex(ecP));
#else
        eff = GetElectronTriggerEffi6GeV(GetRadiusIndex6GeV(ecR), GetMomentumIndex6GeV(ecP));
#endif  
        //for acceptance, we only consider whether the scattered e-/e+ hit the virtual
        //plane in front of the EC or not. This has already been ensured in the fileReducer
        //so acc is always 1 for now.
        double acc = 1.;

        hAbeam_Q2x_acc->Fill(x,Q2,-Abeam*thisrate*acc*eff);
        hrate_Q2x_acc->Fill(x,Q2,thisrate*acc*eff);
        
        tmpRate->Fill(x,Q2,thisrate*acc*eff/1000.); //Get the rate in kHz

        
        if (acc*eff !=0 && thisrate > 1e-9) {
            hAbeamErr_Q2x_acc->Fill(x,Q2,1./sqrt(thisrate*runtime*acc*eff)/pb*100);
        }
        
        for(int k = 0; k < Nbin; k++){  
            if (bin[k][0] <= x && x < bin[k][1] && bin[k][2] <= Q2 && Q2 < bin[k][3]){
                thatrate[k] += thisrate*acc*eff;
                Abeam_sum[k] += -Abeam*thisrate*acc*eff;
                Q2_sum[k] += Q2*thisrate*acc*eff;
                y_sum[k]  += y*thisrate*acc*eff;
            }
        }
    }
    
    hAbeam_Q2x_acc->Divide(hAbeam_Q2x_acc,hrate_Q2x_acc);
    hAbeamErr_Q2x_acc->Divide(hAbeamErr_Q2x_acc,hAbeam_Q2x_acc);
    
    TCanvas *c_AbeamErr_Q2x_acc = new TCanvas("AbeamErr_Q2x_acc","AbeamErr_Q2x_acc",900,600);
    gPad->SetGrid();

    hAbeamErr_Q2x_acc->SetMarkerColor(kGreen+2);
    hAbeamErr_Q2x_acc->SetTitle("");
    hAbeamErr_Q2x_acc->GetXaxis()->SetTitle("x");
    hAbeamErr_Q2x_acc->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
    hAbeamErr_Q2x_acc->GetYaxis()->CenterTitle();
    hAbeamErr_Q2x_acc->GetXaxis()->CenterTitle();
    hAbeamErr_Q2x_acc->Draw();

    //relative statistical uncertainty of the parity violating asymmetry
    double AbeamErr[Nbin];
    cout << "y_ave"<<"\t"<<"Q2_ave" << "\t" << "Abeam_ave" << "\t" << "rate" << "\t" <<  "AbeamErr" << endl;
for(int k = 0; k < Nbin; k++){
//     double Apv = 0.84e-4*(bin[k][2]+bin[k][3])/2.;
    double Q2_ave = Q2_sum[k]/thatrate[k];
    double y_ave = y_sum[k]/thatrate[k];
    double Abeam_ave=Abeam_sum[k]/thatrate[k];
    AbeamErr[k] = 1./sqrt(thatrate[k]*runtime)/Abeam_ave/pb*100;      
    cout << y_ave<<"\t"<<Q2_ave << "\t" << Abeam_ave << "\t" << int(thatrate[k]) << "\t" <<  AbeamErr[k] << " "<<thatrate[k]<<endl;
}
    
#ifdef USE11GeV
    double x_cor[Nbin]={0.250,0.325,0.375,0.375,0.425,0.425,0.475,0.475,0.525,0.525,0.575,0.575,0.635,0.635,0.735};
    double Q2_cor[Nbin]={4.2,5.0,5.5,6.3,6.0,7.0,6.5,7.8,7.1,8.5,7.6,9.1,8.2,9.8,9.8};    
#else
    double x_cor[7]={0.250,0.325,0.375,0.425,0.475,0.525,0.575};
    double Q2_cor[7]={2.0,2.5,3.0,3.5,4.0,4.5,5.0}; 
#endif
    for(int k = 0; k < Nbin; k++){
        TMarker marker;
        marker.SetMarkerStyle(20);
        marker.SetMarkerColor(kRed);
        marker.DrawMarker(x_cor[k],Q2_cor[k]);
        TText *label = new TText(x_cor[k],Q2_cor[k],Form("%.02f",AbeamErr[k]));
        //TText *label = new TText(x_cor[k],Q2_cor[k],Form("%.02f",thatrate[k]/1000.));
        label->SetTextColor(kBlack);
        label->SetTextSize(0.03);
        label->Draw();
    }
    
    //this is the rate for different Q2 and x bin
    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    gStyle->SetPaintTextFormat("4.2f");
    tmpRate->SetMarkerColor(2);
    tmpRate->SetMarkerSize(1.8);
    tmpRate->Draw("colztext");
   
    
    
}
