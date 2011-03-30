void plot_res(){
  Float_t mom[20],dmom[20],dpolar[20],dazi[20],dvertex[20];
  ifstream infile("mom_res.dat");

  // add in fudge factor for improvement 
  for (Int_t i=0;i!=20;i++){
    infile >> mom[i] >> dmom[i];
    dmom[i] = dmom[i]*100./1.6;
  }
  infile.close();
  ifstream infile("polar_res.dat");
  for (Int_t i=0;i!=20;i++){
    infile >> mom[i] >> dpolar[i];
    dpolar[i]=dpolar[i]/1.2;
  }
  infile.close();
  ifstream infile("azimuthal_res.dat");
  for (Int_t i=0;i!=20;i++){
    infile >> mom[i] >> dazi[i];
    dazi[i]=dazi[i]/2.0;
  }
  infile.close();
  ifstream infile("vertexz.dat");
  for (Int_t i=0;i!=20;i++){
    infile >> mom[i] >> dvertex[i];
    dvertex[i]=dvertex[i]/1.5;
  }
  infile.close();
  
  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleOffset(0.00,"X");
  gStyle->SetTitleOffset(0.0,"Y");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(10);
  c1->Divide(2,2);
  c1->cd(1);
  TGraph *g1 = new TGraph(18,&mom[2],&dmom[2]);
  g1->SetTitle("");
  g1->GetXaxis()->SetTitle("P (GeV/c)");
  g1->GetYaxis()->SetTitle("#Delta P/P (\%)");
  g1->GetYaxis()->SetRangeUser(0.,6.);
  g1->Draw("A*");

  c1->cd(2);
  TGraph *g2 = new TGraph(18,&mom[2],&dpolar[2]);
  g2->SetTitle("");
  g2->GetXaxis()->SetTitle("P (GeV/c)");
  g2->GetYaxis()->SetTitle("#Delta #theta (mr)");
  g2->GetYaxis()->SetRangeUser(0.,2.5);
  g2->Draw("A*");

  c1->cd(3);
  TGraph *g3 = new TGraph(18,&mom[2],&dazi[2]);
  g3->SetTitle("");
  g3->GetXaxis()->SetTitle("P (GeV/c)");
  g3->GetYaxis()->SetTitle("#Delta #phi (mr)");
  //g3->GetYaxis()->SetRangeUser(0.,4.);
  g3->Draw("A*");

  c1->cd(4);
  TGraph *g4 = new TGraph(18,&mom[2],&dvertex[2]);
  g4->SetTitle("");
  g4->GetXaxis()->SetTitle("P (GeV/c)");
  g4->GetYaxis()->SetTitle("#Delta z (cm)");
  //g3->GetYaxis()->SetRangeUser(0.,4.);
  g4->Draw("A*");
  
}
