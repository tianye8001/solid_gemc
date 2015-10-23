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

void plot_parameter()
{
gROOT->Reset();
gStyle->SetPalette(1);
// gStyle->SetOptStat(0);
gStyle->SetOptStat(111111);

const double DEG=180./3.1415926;

const int n=41;

double PhotonEnergy[n]={
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
6.19921
};  // in ev
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

double Wavelength[n];
for(int i=0;i<41;i++){
Wavelength[i]=1.24/PhotonEnergy[i]*1e3; // in nm
QE_H12700_03[i]=QE_H12700_03[i]*100;
QE_H8500_03[i]=QE_H8500_03[i]*100;
}

TGraph *g_QE_H12700_03_E=new TGraph(n,PhotonEnergy,QE_H12700_03);
g_QE_H12700_03_E->SetTitle(";E(eV);QE(%)");
g_QE_H12700_03_E->SetName("H12700_03");
TGraph *g_QE_H12700_03_WL=new TGraph(n,Wavelength,QE_H12700_03);
g_QE_H12700_03_WL->SetTitle(";wavelength(nm);QE(%)");
g_QE_H12700_03_WL->SetName("H12700_03");

TGraph *g_QE_H8500_03_E=new TGraph(n,PhotonEnergy,QE_H8500_03);
g_QE_H8500_03_E->SetTitle(";E(eV);QE(%)");
g_QE_H8500_03_E->SetName("QE_H8500_03");
TGraph *g_QE_H8500_03_WL=new TGraph(n,Wavelength,QE_H8500_03);
g_QE_H8500_03_WL->SetTitle(";wavelength(nm);QE(%)");
g_QE_H8500_03_WL->SetName("QE_H8500_03");

TLegend* leg_QE_E = new TLegend(0.8, 0.8, .95, .95);
leg_QE_E->AddEntry(g_QE_H12700_03_E,g_QE_H12700_03_E->GetName());
leg_QE_E->AddEntry(g_QE_H8500_03_E,g_QE_H8500_03_E->GetName());

TLegend* leg_QE_WL = new TLegend(0.8, 0.8, .95, .95);
leg_QE_WL->AddEntry(g_QE_H12700_03_WL,g_QE_H12700_03_WL->GetName());
leg_QE_WL->AddEntry(g_QE_H8500_03_WL,g_QE_H8500_03_WL->GetName());

TCanvas *c_QE = new TCanvas("QE","QE",1600,800);
c_QE->Divide(2,1);
c_QE->cd(1);
// gPad->SetLogy(1);
gPad->SetGrid(1);
g_QE_H12700_03_E->SetMarkerColor(kBlue);
g_QE_H12700_03_E->Draw("AC*");
g_QE_H12700_03_E->SetMaximum(35);
g_QE_H12700_03_E->SetMinimum(0);
g_QE_H12700_03_E->GetXaxis()->SetRangeUser(2,7);
g_QE_H8500_03_E->SetMarkerColor(kRed);
g_QE_H8500_03_E->Draw("C*");
leg_QE_E->Draw();
c_QE->cd(2);
// gPad->SetLogy(1);
gPad->SetGrid(1);
g_QE_H12700_03_WL->SetMarkerColor(kBlue);
g_QE_H12700_03_WL->Draw("AC*");
g_QE_H12700_03_WL->SetMaximum(35);
g_QE_H12700_03_WL->SetMinimum(0);
g_QE_H12700_03_WL->GetXaxis()->SetRangeUser(200,800);
g_QE_H8500_03_WL->SetMarkerColor(kRed);
g_QE_H8500_03_WL->Draw("C*");
leg_QE_WL->Draw();

double reflectivity[n] = {
0.8678125, 0.8651562, 0.8639063, 0.8637500,
0.8640625, 0.8645313, 0.8643750, 0.8656250,
0.8653125, 0.8650000, 0.8648437, 0.8638281, 
0.8635156, 0.8631250, 0.8621875, 0.8617188,
0.8613281, 0.8610156, 0.8610938, 0.8616016,
0.8623047, 0.8637500, 0.8655859, 0.8673828,
0.8700586, 0.8741992, 0.8781055, 0.8825195,
0.8876172, 0.8937207, 0.8981836, 0.9027441,
0.9078369, 0.9102002, 0.9093164, 0.9061743,
0.9004223, 0.8915210, 0.8599536, 0.8208313,
0.7625024
};

TGraph *g_reflectivity_E=new TGraph(n,PhotonEnergy,reflectivity);
g_reflectivity_E->SetTitle(";E(eV);reflectivity");
TGraph *g_reflectivity_WL=new TGraph(n,Wavelength,reflectivity);
g_reflectivity_WL->SetTitle(";wavelength(nm);reflectivity");
 
TCanvas *c_reflectivity = new TCanvas("reflectivity","reflectivity",1600,800);
c_reflectivity->Divide(2,1);
c_reflectivity->cd(1);
g_reflectivity_E->Draw("AC*");
g_reflectivity_E->SetMaximum(1);
g_reflectivity_E->SetMinimum(0.5);
g_reflectivity_E->GetXaxis()->SetRangeUser(2,7);
c_reflectivity->cd(2);
g_reflectivity_WL->Draw("AC*");
g_reflectivity_WL->SetMaximum(1);
g_reflectivity_WL->SetMinimum(0.5);
g_reflectivity_WL->GetXaxis()->SetRangeUser(200,800);

double RefractiveIndex_C4F8O[n] = {
1.00205, 1.00205, 1.00205, 1.00206,
1.00206, 1.00206, 1.00206, 1.00206,
1.00206, 1.00206, 1.00206, 1.00207,
1.00207, 1.00207, 1.00207, 1.00207,
1.00207, 1.00208, 1.00208, 1.00208,
1.00209, 1.00209, 1.00209, 1.0021,
1.00211, 1.00211, 1.00212, 1.00213,
1.00214, 1.00215, 1.00216, 1.00217,
1.00219, 1.0022, 1.00222, 1.00223,
1.00224, 1.00225, 1.00228, 1.00231,
1.00234
}; //at 1.5atm

TGraph *g_RefractiveIndex_C4F8O_E=new TGraph(n,PhotonEnergy,RefractiveIndex_C4F8O);
g_RefractiveIndex_C4F8O_E->SetTitle(";E(eV);RefractiveIndex_C4F8O");
TGraph *g_RefractiveIndex_C4F8O_WL=new TGraph(n,Wavelength,RefractiveIndex_C4F8O);
g_RefractiveIndex_C4F8O_WL->SetTitle(";wavelength(nm);RefractiveIndex_C4F8O");
 
TCanvas *c_RefractiveIndex = new TCanvas("RefractiveIndex","RefractiveIndex",1600,800);
c_RefractiveIndex->Divide(2,1);
c_RefractiveIndex->cd(1);
g_RefractiveIndex_C4F8O_E->Draw("AC*");
g_RefractiveIndex_C4F8O_E->SetMaximum(1.003);
g_RefractiveIndex_C4F8O_E->SetMinimum(1.001);
g_RefractiveIndex_C4F8O_E->GetXaxis()->SetRangeUser(2,7);
c_RefractiveIndex->cd(2);
g_RefractiveIndex_C4F8O_WL->Draw("AC*");
g_RefractiveIndex_C4F8O_WL->SetMaximum(1.003);
g_RefractiveIndex_C4F8O_WL->SetMinimum(1.001);
g_RefractiveIndex_C4F8O_WL->GetXaxis()->SetRangeUser(200,800);

double abs_length_C4F8O[n] = {
87.7642, 87.7642, 87.7642, 87.7642, 
87.7642, 87.7642, 87.7642, 87.7642, 
87.7642, 87.7642, 87.7642, 87.7642, 
87.7642, 87.7642, 87.616, 90.6032, 
93.7711, 102.171, 106.728, 113.497, 
119.095, 123.247, 122.872, 119.913, 
113.597, 104.84, 98.9037, 94.5673, 
91.9657, 90.7634, 90.408, 89.8311, 
87.4725, 83.3764, 73.8737, 67.4882, 
60.427, 53.2042, 39.2524, 30.5066, 
23.3447
}; //in m


TGraph *g_abs_length_C4F8O_E=new TGraph(n,PhotonEnergy,abs_length_C4F8O);
g_abs_length_C4F8O_E->SetTitle(";E(eV);abs_length_C4F8O (m)");
TGraph *g_abs_length_C4F8O_WL=new TGraph(n,Wavelength,abs_length_C4F8O);
g_abs_length_C4F8O_WL->SetTitle(";wavelength(nm);abs_length_C4F8O (m)");
 

TCanvas *c_abs_length = new TCanvas("abs_length","abs_length",1600,800);
c_abs_length->Divide(2,1);
c_abs_length->cd(1);
g_abs_length_C4F8O_E->Draw("AC*");
g_abs_length_C4F8O_E->SetMaximum(150);
g_abs_length_C4F8O_E->SetMinimum(0);
g_abs_length_C4F8O_E->GetXaxis()->SetRangeUser(2,7);
c_abs_length->cd(2);
g_abs_length_C4F8O_WL->Draw("AC*");
g_abs_length_C4F8O_WL->SetMaximum(150);
g_abs_length_C4F8O_WL->SetMinimum(0);
g_abs_length_C4F8O_WL->GetXaxis()->SetRangeUser(200,800);


}