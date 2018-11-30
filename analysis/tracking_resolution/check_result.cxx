using namespace std;

void check_result()
{
  //gROOT->ProcessLine(".x collimator_cut.cxx");
  const Double_t theta_min = 6.;
  const Double_t theta_max = 17.;
  const Double_t mom_min = 0.;
  const Double_t mom_max = 12.;
  const Double_t vertex_min = -375.;
  const Double_t vertex_max = -325.;
  const Double_t mom_cut = 0.;
  const Double_t deg2rad = 3.1415926/180.;
  //char cut[100] = "MC_mom>0.";
  //TFile *f2 = new TFile("SIDIS_LA_2Dplot.root", "RECREATE");
  //TFile *f1 = new TFile("../SIDIS_LA_electron_process_noise_20000_newGEM.root");
  TFile *f1 = new TFile("../p-2.t000.root");
  TTree *t1 = (TTree*)f1->Get("Reconvertex");
  //TFile *f2 = new TFile("SIDIS_LA_2Dplot.root", "RECREATE");
  TCanvas *c1 = new TCanvas("c1", "c1", 1500, 1000);
  //c1->SetLeftMargin(0.25);
  c1->Divide(4,3);
  gStyle->SetOptStat(111111);
  gStyle->SetTitleFontSize(0.09); 
  //gStyle->SetStat(kFALSE); 
  TH2D *p[12];
  p[0] = new TH2D("p0", "polar angle", 200, mom_min, mom_max, 200, -10, 10);
  p[1] = new TH2D("p1", "", 200, theta_min, theta_max, 200, -10, 10);
  p[2] = new TH2D("p2", "vertex z", 200, mom_min, mom_max, 200, -10, 10);
  p[3] = new TH2D("p3", "", 200, theta_min, theta_max, 200, -10, 10);
  p[4] = new TH2D("p4", "azimuthal angle", 200, mom_min, mom_max, 200, -20, 20);
  p[5] = new TH2D("p5", "", 200, theta_min, theta_max, 200, -20, 20);
  p[6] = new TH2D("p6", "momentum", 200, mom_min, mom_max, 200, -20, 20);
  p[7] = new TH2D("p7", "", 200, theta_min, theta_max, 200, -20, 20);
  p[8] = new TH2D("p8", "polar angle", 200, vertex_min, vertex_max, 200, -10, 10);
  p[9] = new TH2D("p9", "vertex z", 200, vertex_min, vertex_max, 200, -10, 10);
  p[10] = new TH2D("p10", "azimuthal angle", 200, vertex_min, vertex_max, 200, -20, 20);
  p[11] = new TH2D("p11", "momentum", 200, vertex_min, vertex_max, 200, -20, 20); 

  TH1D *h[4];
  h[0] = new TH1D("h0", "", 100, -10, 10);
  h[1] = new TH1D("h1", "", 100, -10, 10);
  h[2] = new TH1D("h2", "", 100, -20, 20);
  h[3] = new TH1D("h3", "", 100, -20, 20); 

  p[0]->GetXaxis()->SetTitle("MC momentum (GeV/c)");
  p[0]->GetYaxis()->SetTitle("#Delta#theta (mrad)");
  p[2]->GetXaxis()->SetTitle("MC momentum (GeV/c)");
  p[2]->GetYaxis()->SetTitle("#Deltavertex z (cm)");
  p[4]->GetXaxis()->SetTitle("MC momentum (GeV/c)");
  p[4]->GetYaxis()->SetTitle("#Delta#phi (mrad)");
  p[6]->GetXaxis()->SetTitle("MC momentum (GeV/c)");
  p[6]->GetYaxis()->SetTitle("#Deltap/p (%)");


  p[1]->GetXaxis()->SetTitle("MC #theta (deg)");
  p[1]->GetYaxis()->SetTitle("#Delta#theta (mrad)");
  p[3]->GetXaxis()->SetTitle("MC #theta (deg)");
  p[3]->GetYaxis()->SetTitle("#Deltavertex z (cm)");
  p[5]->GetXaxis()->SetTitle("MC #theta (deg)");
  p[5]->GetYaxis()->SetTitle("#Delta#phi (mrad)");
  p[7]->GetXaxis()->SetTitle("MC #theta (deg)");
  p[7]->GetYaxis()->SetTitle("#Deltap/p (%)");

  p[8]->GetXaxis()->SetTitle("MC vertex z (cm)");
  p[8]->GetYaxis()->SetTitle("#Delta#theta (mrad)");
  p[9]->GetXaxis()->SetTitle("MC vertex z (cm)");
  p[9]->GetYaxis()->SetTitle("#Deltavertex z (cm)");
  p[10]->GetXaxis()->SetTitle("MC vertex z (cm)");
  p[10]->GetYaxis()->SetTitle("#Delta#phi (mrad)");
  p[11]->GetXaxis()->SetTitle("MC vertex z (cm)");
  p[11]->GetYaxis()->SetTitle("#Deltap/p (%)");
 
  h[0]->GetXaxis()->SetTitle("#Delta#theta (mrad)");
  h[1]->GetXaxis()->SetTitle("#Deltaz (cm)");
  h[2]->GetXaxis()->SetTitle("#Delta#phi (mrad)");
  h[3]->GetXaxis()->SetTitle("#Deltap/p (%)");
  for (Int_t i=0; i<12; i++)
  {
    p[i]->GetXaxis()->SetTitleSize(0.06);
    p[i]->GetYaxis()->SetTitleSize(0.06);
    p[i]->GetXaxis()->SetLabelSize(0.06);
    p[i]->GetYaxis()->SetLabelSize(0.06);
  }

   for (Int_t i=0; i<4; i++)
  {
    h[i]->GetXaxis()->SetTitleSize(0.06);
    h[i]->GetYaxis()->SetTitleSize(0.06);
    h[i]->GetXaxis()->SetLabelSize(0.06);
    h[i]->GetYaxis()->SetLabelSize(0.06);
  }

  /*p[0]->GetXaxis()->SetTitleSize(0.05);
  p[0]->GetYaxis()->SetTitleSize(0.05);
  p[2]->GetXaxis()->SetTitleSize(0.05);
  p[2]->GetYaxis()->SetTitleSize(0.05);
  p[4]->GetXaxis()->SetTitleSize(0.05);
  p[4]->GetYaxis()->SetTitleSize(0.05);
  p[6]->GetXaxis()->SetTitleSize(0.05);
  p[6]->GetYaxis()->SetTitleSize(0.05);

  p[0]->GetXaxis()->SetLabelSize(0.05);
  p[0]->GetYaxis()->SetLabelSize(0.05);
  p[2]->GetXaxis()->SetLabelSize(0.05);
  p[2]->GetYaxis()->SetLabelSize(0.05);
  p[4]->GetXaxis()->SetLabelSize(0.05);
  p[4]->GetYaxis()->SetLabelSize(0.05);
  p[6]->GetXaxis()->SetLabelSize(0.05);
  p[6]->GetYaxis()->SetLabelSize(0.05);


  p[1]->GetXaxis()->SetTitleSize(0.04);
  p[1]->GetYaxis()->SetTitleSize(0.04);
  p[3]->GetXaxis()->SetTitleSize(0.04);
  p[3]->GetYaxis()->SetTitleSize(0.04);
  p[5]->GetXaxis()->SetTitleSize(0.04);
  p[5]->GetYaxis()->SetTitleSize(0.04);
  p[7]->GetXaxis()->SetTitleSize(0.04);
  p[7]->GetYaxis()->SetTitleSize(0.04);*/

   TCut cut = "";

  t1->Project("p0", "(1000*(MC_theta - Recon_theta)*3.1415926/180.):MC_mom", cut);
  t1->Project("p1", "(1000*(MC_theta - Recon_theta)*3.1415926/180.):MC_theta", cut);
  t1->Project("p2", "((MC_vertexz - Recon_vertexz)):MC_mom", cut);
  t1->Project("p3", "((MC_vertexz - Recon_vertexz)):MC_theta", cut);
  t1->Project("p4", "(1000*(MC_phi - Recon_phi)*3.1415926/180.):MC_mom", cut);
  t1->Project("p5", "(1000*(MC_phi - Recon_phi)*3.1415926/180.):MC_theta", cut);
  t1->Project("p6", "(100*(MC_mom - Recon_mom)/MC_mom):MC_mom", cut);
  t1->Project("p7", "(100*(MC_mom - Recon_mom)/MC_mom):MC_theta", cut);
  t1->Project("p8", "(1000*(MC_theta - Recon_theta)*3.1415926/180.):MC_vertexz", cut);
  t1->Project("p9", "((MC_vertexz - Recon_vertexz)):MC_vertexz", cut);
  t1->Project("p10", "(1000*(MC_phi - Recon_phi)*3.1415926/180.):MC_vertexz", cut);
  t1->Project("p11", "(100*(MC_mom - Recon_mom)/MC_mom):MC_vertexz", cut);
  t1->Project("h0", "(1000*(MC_theta - Recon_theta)*3.1415926/180.)", cut);
  t1->Project("h1",  "((MC_vertexz - Recon_vertexz))", cut);
  t1->Project("h2", "(1000*(MC_phi - Recon_phi)*3.1415926/180.)", cut);
  t1->Project("h3", "100*((MC_mom - Recon_mom)/MC_mom)", cut);
  //for (Int_t i=0; i<8; i++)
    //{
      //c1->cd(i+1);
      //p[i]->Draw("colz");
    //}


c1->cd(1);
 TPad *pad1 = c1->cd(1);
 pad1->SetBottomMargin(0.15);
 pad1->SetLeftMargin(0.15);
p[0]->Draw("colz");
c1->cd(2);
 TPad *pad2 = c1->cd(2);
 pad2->SetBottomMargin(0.15);
 pad2->SetLeftMargin(0.15);
p[2]->Draw("colz");
c1->cd(3);
 TPad *pad3 = c1->cd(3);
 pad3->SetBottomMargin(0.15);
 pad3->SetLeftMargin(0.15);
p[4]->Draw("colz");
c1->cd(4);
 TPad *pad4 = c1->cd(4);
 pad4->SetBottomMargin(0.15);
 pad4->SetLeftMargin(0.15);
p[6]->Draw("colz");

c1->cd(5);
 TPad *pad5 = c1->cd(5);
 pad5->SetBottomMargin(0.15);
 pad5->SetLeftMargin(0.15);
p[1]->Draw("colz");
c1->cd(6);
 TPad *pad6 = c1->cd(6);
 pad6->SetBottomMargin(0.15);
 pad6->SetLeftMargin(0.15);
p[3]->Draw("colz");
c1->cd(7);
 TPad *pad7 = c1->cd(7);
 pad7->SetBottomMargin(0.15);
 pad7->SetLeftMargin(0.15);
p[5]->Draw("colz");
c1->cd(8);
 TPad *pad8 = c1->cd(8);
 pad8->SetBottomMargin(0.15);
 pad8->SetLeftMargin(0.15);
p[7]->Draw("colz");

/*c1->cd(9);
p[8]->Draw("colz");
c1->cd(10);
p[9]->Draw("colz");
c1->cd(11);
p[10]->Draw("colz");
c1->cd(12);
p[11]->Draw("colz");*/


 char text[100];
 c1->cd(9);
 TPad *pad9 = c1->cd(9);
 pad9->SetBottomMargin(0.15);
 pad9->SetLeftMargin(0.15);
 h[0]->Fit("gaus");
 TF1 *fit0 = h[0]->GetFunction("gaus");
 Double_t e0 = fit0->GetParameter(2);
 TLatex Tl0; Tl0.SetTextFont(43); Tl0.SetTextSize(30);
 sprintf(text, "#color[2]{#splitline{#sigma=%.2f}{(mrad)}}", e0);
 Tl0.DrawLatex(-9, 0.8*h[0]->GetMaximum(), text); 
c1->cd(10);
 TPad *pad10 = c1->cd(10);
 pad10->SetBottomMargin(0.15);
 pad10->SetLeftMargin(0.15);
 h[1]->Fit("gaus");
 TF1 *fit1 = h[1]->GetFunction("gaus");
 Double_t e1 = fit1->GetParameter(2);
 TLatex Tl1; Tl1.SetTextFont(43); Tl1.SetTextSize(30);
 sprintf(text, "#color[2]{#splitline{#sigma=%.2f}{(cm)}}", e1);
 Tl1.DrawLatex(-9, 0.8*h[1]->GetMaximum(), text);
 c1->cd(11);
 TPad *pad11 = c1->cd(11);
 pad11->SetBottomMargin(0.15);
 pad11->SetLeftMargin(0.15);
 h[2]->Fit("gaus");
 TF1 *fit2 = h[2]->GetFunction("gaus");
 Double_t e2 = fit2->GetParameter(2);
 TLatex Tl2; Tl2.SetTextFont(43); Tl2.SetTextSize(30);
 sprintf(text, "#color[2]{#splitline{#sigma=%.2f}{(mrad)}}", e2);
 Tl2.DrawLatex(-18, 0.8*h[2]->GetMaximum(), text);
 c1->cd(12);
 TPad *pad12 = c1->cd(12);
 pad12->SetBottomMargin(0.15);
 pad12->SetLeftMargin(0.15);
 h[3]->Fit("gaus");
 TF1 *fit3 = h[3]->GetFunction("gaus");
 Double_t e3 = fit3->GetParameter(2);
 TLatex Tl3; Tl3.SetTextFont(43); Tl3.SetTextSize(30);
sprintf(text, "#color[2]{#splitline{#sigma=%.2f}{(%)}}", e3); 
 Tl3.DrawLatex(-18, 0.8*h[3]->GetMaximum(), text);
//TFile *f2 = new TFile("SIDIS_FA_2Dplot.root", "RECREATE");
//for (Int_t i=0; i<8; i++)
//	{
//	   p[i]->Write();
//	}
//f2->Write();
//f2->Close();

}
