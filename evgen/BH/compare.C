{
  gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const int n=4;

char *name[n]={"BHinterNO","BHinter","Compton","QED"};

TFile *file[n];

// file[0]=new TFile("zwzhao_4fold_BHinterference.root");
// file[1]=new TFile("zwzhao_4fold_Compton.root");
// file[2]=new TFile("zwzhao_4fold_QEDdiagrams.root");

TH1F *h[n];

TCanvas *c = new TCanvas("c","c",1000,800);
TText *label;
for (Int_t i=0;i<n;i++) {
  file[i]=new TFile(Form("4fold_%s.root",name[i]));  
  h[i]=(TH1F*) file[i]->Get("hlepIM");
//   hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
//   hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
//   hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
 h[i]->SetLineColor(i+1); 
 h[i]->SetMaximum(1.5e-5); 
 cout << i << endl;
 if (i==0) h[i]->Draw();
 else h[i]->Draw("same");
 
label = new TText(0.5,8e-6+i*2e-6,name[i]);
label->SetTextColor(i+1);
label->SetTextSize(0.05);
label->Draw();
 
}

/*
TH2F *h=(TH2F*) h1->Clone();
h->Divide(h1,h2);

TCanvas *c_acceptance_eDIS_1D = new TCanvas("acceptance_eDIS_1D","acceptance_eDIS_1D",1800,900);
c_acceptance_eDIS_1D->Divide(2,2);
c_acceptance_eDIS_1D->cd(1);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_P[i]->SetMinimum(0);
hacceptance_P[i]->SetMaximum(0.6);
hacceptance_P[i]->SetLineColor(i+1);
if (i==0) hacceptance_P[i]->Draw();
else hacceptance_P[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(2);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_Theta[i]->SetMinimum(0);
hacceptance_Theta[i]->SetMaximum(0.1);
hacceptance_Theta[i]->SetLineColor(i+1);
if (i==0) hacceptance_Theta[i]->Draw();
else hacceptance_Theta[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(3);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_x[i]->SetMinimum(0);
hacceptance_x[i]->SetMaximum(0.6);
hacceptance_x[i]->SetLineColor(i+1);
if (i==0) hacceptance_x[i]->Draw();
else hacceptance_x[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(4);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_Q2[i]->SetMinimum(0);
hacceptance_Q2[i]->SetMaximum(0.6);
hacceptance_Q2[i]->SetLineColor(i+1);
if (i==0) hacceptance_Q2[i]->Draw();
else hacceptance_Q2[i]->Draw("same");
}*/

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