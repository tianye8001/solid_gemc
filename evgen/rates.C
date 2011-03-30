void rates(){
  gStyle->SetOptStat(0);
  TFile *file = new TFile("convert_single.root");
  TTree *T = (TTree*)file->Get("h9500");

  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleOffset(1.5,"Y");
  gStyle->SetLabelSize(0.05,"X");
  gStyle->SetTitleSize(0.05,"X");

  TCanvas *c1 = new TCanvas("c1","c1",1200,1200);
  c1->SetFillColor(10);
  c1->Divide(4,4);
  c1->cd(1);
  
  
  TH1F *h1 = new TH1F("h1","h1",100,105,194);
  T->Project("h1","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_e*(hitnum1_8>0.)");
  cout <<"e- at forward angle 11 " <<  h1->GetSum()<< endl;
  h1->Reset();
  T->Project("h1","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_e/(sqrt(hit8_x*hit8_x+hit8_y*hit8_y)/100.)/2./3.1415926/(194-105)*100.*(hitnum1_8>0.)");
  // h1->Draw();
  h1->SetTitle("Electron at forward angle");
  h1->SetXTitle("R radius (cm)");
  h1->SetYTitle("kHz/100cm^{2}");

  

  c1->cd(2);
  TH1F *h2 = new TH1F("h2","h2",100,80,138);  
  T->Project("h2","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_e*(hitnum1_9>0.&&p_e>3.5)");
  cout << "e- at large angle  11 " << h2->GetSum() << endl;
  h2->Reset();
  T->Project("h2","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_e/(sqrt(hit9_x*hit9_x+hit9_y*hit9_y)/100.)/2./3.1415926/(138-80)*100.*(hitnum1_9>0.&&p_e>3.5)");
  // h2->Draw();
  h2->SetTitle("Electron at large angle");
  h2->SetXTitle("R radius (cm)");
  h2->SetYTitle("kHz/100cm^{2}");

  
  c1->cd(3);
  TH1F *h3 = new TH1F("h3","h3",100,105,194);
  T->Project("h3","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_p*(hitnum1_8>0.)");
  cout <<"p at forward angle 11 " <<  h3->GetSum()<< endl;
  h3->Reset();
  T->Project("h3","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_p/(sqrt(hit8_x*hit8_x+hit8_y*hit8_y)/100.)/2./3.1415926/(194-105)*100.*(hitnum1_8>0.)");
  h3->SetLineColor(2);
  h3->Draw();
  h3->SetTitle("Proton at forward angle");
  h3->SetXTitle("R radius (cm)");
  h3->SetYTitle("kHz/100cm^{2}");

  c1->cd(4);
  TH1F *h4 = new TH1F("h4","h4",100,80,138);  
  
  T->Project("h4","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_p*(hitnum1_9>0.&&p_e>3.5)");
  cout << "p at large angle  11 " << h4->GetSum() << endl;
  h4->Reset();
  T->Project("h4","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_p/(sqrt(hit9_x*hit9_x+hit9_y*hit9_y)/100.)/2./3.1415926/(138-80)*100.*(hitnum1_9>0.&&p_e>3.5)");
  h4->SetLineColor(2);
  h4->Draw();
  h4->SetTitle("Proton at large angle");
  h4->SetXTitle("R radius (cm)");
  h4->SetYTitle("kHz/100cm^{2}");
  
  c1->cd(1);
    
  TH1F *h5 = new TH1F("h5","h5",100,105,194);
  T->Project("h5","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_pim*(hitnum1_8>0.)");
  cout <<"e- at forward angle 8.8 " <<  h5->GetSum()<< endl;
  h5->Reset();
  T->Project("h5","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_pim/(sqrt(hit8_x*hit8_x+hit8_y*hit8_y)/100.)/2./3.1415926/(194-105)*100.*(hitnum1_8>0.)");
  h5->Draw();
  h5->SetTitle("Electron at forward angle");
  h5->SetXTitle("R radius (cm)");
  h5->SetYTitle("kHz/100cm^{2}");

  h1->SetLineColor(2);
  h1->Draw("same");

  c1->cd(2);
  TH1F *h6 = new TH1F("h6","h6",100,80,138);  
  T->Project("h6","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_pim*(hitnum1_9>0.&&p_e>3.5)");
  cout << "e- at large angle 8.8  " << h6->GetSum() << endl;
  h6->Reset();
  T->Project("h6","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_pim/(sqrt(hit9_x*hit9_x+hit9_y*hit9_y)/100.)/2./3.1415926/(138-80)*100.*(hitnum1_9>0.&&p_e>3.5)");
  h6->Draw();
  h6->SetTitle("Electron at large angle");
  h6->SetXTitle("R radius (cm)");
  h6->SetYTitle("kHz/100cm^{2}");
  h2->SetLineColor(2);
  h2->Draw("same");
  
  c1->cd(3);
  TH1F *h7 = new TH1F("h7","h7",100,105,194);
  T->Project("h7","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_pip*(hitnum1_8>0.)");
  cout <<"p at forward angle 8.8 " <<  h7->GetSum()<< endl;
  h7->Reset();
  T->Project("h7","sqrt(hit8_x*hit8_x+hit8_y*hit8_y)","sdxs_pip/(sqrt(hit8_x*hit8_x+hit8_y*hit8_y)/100.)/2./3.1415926/(194-105)*100.*(hitnum1_8>0.)");
  h7->SetTitle("Proton at forward angle");
  h7->SetXTitle("R radius (cm)");
  h7->SetYTitle("kHz/100cm^{2}");
  h7->Draw("same");
  
  c1->cd(4);
  TH1F *h8 = new TH1F("h8","h8",100,80,138);  
  T->Project("h8","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_pip*(hitnum1_9>0.&&p_e>3.5)");
  cout << "p at large angle 8.8 " << h8->GetSum() << endl;
  h8->Reset();
  T->Project("h8","sqrt(hit9_x*hit9_x+hit9_y*hit9_y)","sdxs_pip/(sqrt(hit9_x*hit9_x+hit9_y*hit9_y)/100.)/2./3.1415926/(138-80)*100.*(hitnum1_9>0.&&p_e>3.5)");
  h8->SetTitle("Proton at large angle");
  h8->SetXTitle("R radius (cm)");
  h8->SetYTitle("kHz/100cm^{2}");
  h8->Draw("same");
  

  TFile *gile = new TFile("temp.root","RECREATE");
  h1->SetDirectory(gile);
  h2->SetDirectory(gile);
  h3->SetDirectory(gile);
  h4->SetDirectory(gile);
  h5->SetDirectory(gile);
  h6->SetDirectory(gile);
  h7->SetDirectory(gile);
  h8->SetDirectory(gile);
  gile->Write();
  gile->Close();
}
