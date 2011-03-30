void plot()
{
  TFile *file = new TFile("convert_single.root");
  TCanvas *c1 = new TCanvas("c1","c1",800,400);
  c1->SetFillColor(10);
  gStyle->SetOptStat(0);
  c1->Divide(2,1);
  c1->cd(1);
  TH1F *h1 = new TH1F("h1","h1",100,0,10.);
  TH1F *h2 = new TH1F("h2","h2",100,7.5,28.);
  TH1F *h3 = new TH1F("h3","h3",100,0,10.);
  TH1F *h4 = new TH1F("h4","h4",100,7.5,28.);
  TH1F *h5 = new TH1F("h5","h5",100,0,10.);
  TH1F *h6 = new TH1F("h6","h6",100,0,10.);

  h9500->Project("h1","p_e","1./(200000./(cos(0.122168)-cos(0.453788))*(cos(8./180.*3.1415926)-cos(17./180.*3.1415926))/7.04*6.12)*10.*7.*(hitnum1_8>0.&&p_e<7.0)");
  h9500->Project("h2","theta_e","1./(200000./(cos(0.122168)-cos(0.453788))*(cos(8./180.*3.1415926)-cos(17./180.*3.1415926))/7.04*6.12)*100./(28.-7.5)*9.*(hitnum1_8>0.&&p_e<7.0)");
  h9500->Project("h3","p_e","1./(200000./(cos(0.122168)-cos(0.453788))*(cos(15./180.*3.1415926)-cos(26./180.*3.1415926))/7.04*2.)*10.*2.*(hitnum1_9>0.&&p_e>4.&&p_e<6.)");
  h9500->Project("h4","theta_e","1./(200000./(cos(0.122168)-cos(0.453788))*(cos(15./180.*3.1415926)-cos(26./180.*3.1415926))/7.04*2.)*100./(28.-7.5)*11.*(hitnum1_9>0.&&p_e>4.&&p_e<6.)");
  h9500->Project("h5","p_e","1./(200000./7.04*6.12)*(hitnum1_8>0.&&p_e<7.0)*2.*3.1415926*(cos(0.122168)-cos(0.453788))");
  h9500->Project("h6","p_e","1./(200000./7.04*2.0)*(hitnum1_9>0.&&p_e<6.0&&p_e>4.0)*2.*3.1415926*(cos(0.122168)-cos(0.453788))");
  
  
  h1->Draw();
  h1->SetTitle("Acceptance");
  h1->GetXaxis()->SetTitle("Mom. (GeV/c)");
  h1->GetYaxis()->SetRangeUser(0.,1.);
  h3->Draw("same");
  h3->SetLineColor(2);
  TLegend *l1 = new TLegend(0.2,0.7,0.9,0.9);
  TString temp;
  temp.Form("Forward angle: %2.1f msr x 6.0 GeV/c",h5->GetSum()*1000.);
  l1->AddEntry(h1,temp,"l");
  temp.Form("Large angle: %2.1f msr x 2.0 GeV/c",h6->GetSum()*1000.);
  l1->AddEntry(h3,temp,"l");
  l1->Draw();
  c1->cd(2);
  h2->Draw();
  h2->GetYaxis()->SetRangeUser(0.,1.1);
  h2->SetTitle("Acceptance");
  h2->GetXaxis()->SetTitle("Angle (degree)");
  h4->Draw("same");
  h4->SetLineColor(2);
}
