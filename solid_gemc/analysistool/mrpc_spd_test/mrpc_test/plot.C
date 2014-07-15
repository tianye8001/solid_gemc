{
ifstream infile("mrpc_gamma_resp.txt");

TString rootfile[30];
double E[30],E_Err[30], R[30], R_Err[30];

int N = 0;
while(!(infile.eof())){
  infile >> rootfile[N] >> E[N] >> R[N] >> R_Err[N];
  E_Err[N] = 0.0;
  N++;
}
	TCanvas *c1 = new TCanvas("c1","c1", 800,600);
	gStyle->SetOptStat(0);
	TH2F *h2 = new TH2F("h2","Photon to Electron Pairs Probability in MRPC", 1500, 5*1e-5, 12.5, 1000, 0.05, 9.); //X->Z position, Y->Hit Count
	h2->SetXTitle("E (GeV)");
	h2->GetXaxis()->CenterTitle(1);
	h2->SetYTitle("Rate");
	h2->GetYaxis()->CenterTitle(1);
	gPad->SetLogx(0);
	h2->Draw();
    gPad->SetLogx(1);
	TGraphErrors *gr = new TGraphErrors(N, E, R, E_Err, R_Err);
	gr->SetMarkerStyle(24);
	gr->SetMarkerSize(1.3);
	gr->SetMarkerColor(2);
	gr->SetLineColor(2);
	gr->Draw("p");



}
