void plotphase(){
  TFile *file = new TFile("convert_pip_p.root");
  TTree *T = (TTree*)(file->Get("h9500"));
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",800,1200);
  c1->SetFillColor(10);
  c1->Divide(2,3);
  TCut cut1 = "q2>1.&&wp>1.6&&w>2.3";
  c1->cd(1);
  TH2F *h1 = new TH2F("h1","h1",100,0.03,0.5,100,0.5,4.5);
  T->Project("h1","q2:x",cut1);
  h1->Draw("CONT");
  h1->SetTitle("");
 
  
}
