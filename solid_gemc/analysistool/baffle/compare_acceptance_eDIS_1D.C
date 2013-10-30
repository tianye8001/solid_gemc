{
  gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(111111);

const int n=6;

TFile *file[n];
file[0]=new TFile("baffleCLEOv8_eDIS_babarbafflemore1_block_output.root");
file[1]=new TFile("baffleCLEOv8_eDIS_0.35x3.5deg_output.root");
file[2]=new TFile("baffleCLEOv8_eDIS_0.35x3.5degblock_output.root");
file[3]=new TFile("baffleCLEOv8_eDIS_0.35x3.5deglast_output.root");
file[4]=new TFile("baffleCLEOv8_eDIS_0.55x5deg_output.root");
file[5]=new TFile("baffleCLEOv8_eDIS_0.55x5degblock_output.root");
// file[5]=new TFile("test_output.root");

int style[n]={1,2,1,3,2,1};
int color[n]={1,2,2,2,4,4};

TH1F *hacceptance_x[n],*hacceptance_P[n],*hacceptance_Theta[n],*hacceptance_Q2[n];
for (Int_t i=0;i<n;i++) {
  hacceptance_x[i]=(TH1F*) file[i]->Get("acceptance_x");
  hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
  hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
  hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
}

// TCanvas *c = new TCanvas("c","c",1000,1200);
// c->Divide(1,2);
// c->cd(1);
// gPad->SetLogz(1);
// h1->Draw();
// c->cd(2);
// gPad->SetLogz(1);
// h2->Draw("colz text");
// 
// TH2F *h=(TH2F*) h1->Clone();
// h->Divide(h1,h2);

TCanvas *c_acceptance_eDIS_1D = new TCanvas("acceptance_eDIS_1D_compare","acceptance_eDIS_1D_compare",1800,900);
c_acceptance_eDIS_1D->Divide(2,2);
c_acceptance_eDIS_1D->cd(1);
gPad->SetGrid();
char *title[n]={"BaBar more1 block","0.35x 3.5deg","0.35x 3.5deg block","0.35x 3.5deg last","0.55x 5deg","0.55x 5deg block"};
leg_hist = new TLegend(0.6,0.6,0.9,0.9);
//   leg_hist->SetHeader("Some histograms");
for (Int_t i=0;i<n;i++) {
// hacceptance_P[i]->SetMinimum(0);
// hacceptance_P[i]->SetMaximum(0.6);
hacceptance_P[i]->SetLineStyle(style[i]);
hacceptance_P[i]->SetLineColor(color[i]);
if (i==0) hacceptance_P[i]->Draw();
else hacceptance_P[i]->Draw("same");

  leg_hist->AddEntry(hacceptance_P[i],title[i],"l"); 
}
  leg_hist->Draw();
  
c_acceptance_eDIS_1D->cd(2);
gPad->SetGrid();
for (Int_t i=0;i<n;i++) {
// hacceptance_Theta[i]->SetMinimum(0);
// hacceptance_Theta[i]->SetMaximum(0.1);
hacceptance_Theta[i]->SetLineStyle(style[i]);
hacceptance_Theta[i]->SetLineColor(color[i]);
if (i==0) hacceptance_Theta[i]->Draw();
else hacceptance_Theta[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(3);
gPad->SetGrid();
for (Int_t i=0;i<n;i++) {
// hacceptance_x[i]->SetMinimum(0);
// hacceptance_x[i]->SetMaximum(0.6);
hacceptance_x[i]->SetLineStyle(style[i]);
hacceptance_x[i]->SetLineColor(color[i]);
if (i==0) hacceptance_x[i]->Draw();
else hacceptance_x[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(4);
gPad->SetGrid();
for (Int_t i=0;i<n;i++) {
// hacceptance_Q2[i]->SetMinimum(0);
// hacceptance_Q2[i]->SetMaximum(0.6);
hacceptance_Q2[i]->SetLineStyle(style[i]);
hacceptance_Q2[i]->SetLineColor(color[i]);
if (i==0) hacceptance_Q2[i]->Draw();
else hacceptance_Q2[i]->Draw("same");
}

// // gPad->SetLogz(1);
// gPad->SetGrid();
// h1->SetMarkerColor(kBlack);
// h1->SetMarkerStyle(6);
// h1->Draw();
// h2->SetMarkerColor(kRed);
// h2->SetMarkerStyle(6);
// h2->Draw("same");
// h3->SetMarkerColor(kBlue);
// h3->SetMarkerStyle(6);
// h3->Draw("same");
// 
// // h1->SetTitle("hits behind 11th baffle (black(-),red(0),blue(+)) ;x (cm);y (cm)");
// h1->SetTitle("hits before FAEC (black(-),red(0),blue(+)) ;x (cm);y (cm)");

// h->Scale(1e-3);
// h->SetAxisRange(20,44,"X");
// h->SetAxisRange(0,7,"Y");
// h->SetAxisRange(5,35,"X");
// h->SetAxisRange(0,11,"Y");
// h->SetTitle("#pi^{-}/e- ;#theta (deg);P (GeV)");
// h->SetTitle("#pi^{-}/K^{-} ;#theta (deg);P (GeV)");
// h->SetTitle("#pi^{+}/K^{+} ;#theta (deg);P (GeV)");
// h->Draw("colz text");

}