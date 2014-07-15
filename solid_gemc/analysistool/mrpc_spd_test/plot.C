{
ifstream infile("root_1mm.out");
ifstream infile5("root_5mm.out");

TString rootfile[30];
double E[30],E_Err[30], R[30], R_Err[30];
double E5[30],E_Err5[30], R5[30], R_Err5[30];

int N = 0;
while(!(infile.eof())){
  infile  >> E[N] >> R[N] >> R_Err[N]>> rootfile[N] ;
  infile5 >>E5[N] >> R5[N]>> R_Err5[N]>>rootfile[N] ;
  E_Err[N] = 0.0;
  E_Err5[N] = 0.0;
  N++;
}
	TCanvas *c1 = new TCanvas("c1","c1", 800,600);
	gStyle->SetOptStat(0);
	TH2F *h2 = new TH2F("h2","Photon Respond Rate in SPD (1mm->Red, 5mm->Blue)", 1500, 5*1e-5, 12.5, 1000, 0.005, 5.5); //X->Z position, Y->Hit Count
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
	TGraphErrors *gr5 = new TGraphErrors(N, E5, R5, E_Err5, R_Err5);
	gr5->SetMarkerStyle(20);
	gr5->SetMarkerSize(1.3);
	gr5->SetMarkerColor(4);
	gr5->SetLineColor(2);
	gr5->Draw("p");

    


}
