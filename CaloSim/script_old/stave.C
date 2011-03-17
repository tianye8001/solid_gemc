stave(){


  gStyle->SetPalette(1,0);
  TH1F *h = new TH1F("h","h",21,-0.5,20.5);

  TFile *_file0 = TFile::Open("/data/npluser2/nschroed/1e5_pencil.root");

  TH2F *staves = new TH2F("staves","Hits in a stave per event",21,-0.5,20.5,20,-0.5,19.5);


  TH1F *h = new TH1F("h","h",21,-0.5,20.5);
  h->GetXaxis()->SetTitle("# of Hits");
  h->GetYaxis()->SetTitle("Freq");
  TString v = "v";
  TString hor = "h";
  TString z = ">>h";
  TString b;
  TString c = "figs/stave/";
  TString num;
  Double_t freq;

  char word[2];  
  Double_t n;

  //TCanvas *can = new TCanvas();
  //can->Divide(4,5);




  for(Int_t i=0;i<20;i++){
    //can->cd(i+1);
    n=i;
    sprintf(word,"%02.0f",n);
    num=word;
    b = v+num+z;
    h->SetTitle("Stave "+v+num+", # of hits in an event");
    
    ntuple->Draw(b);
    for(Int_t j=0;j<21;j++){
    freq=h->GetBinContent(j+1);
    //    cout<<"
    staves->Fill(j,i,freq);
    }
    //    c1->SaveAs(c+v+num+".gif");
  
    

  }

  staves->Draw("colz");
  //can->SaveAs("can.gif");

  /*

  for(Int_t i=0;i<15;i++){
    n=i;
    sprintf(word,"%02.0f",n);
    num=word;
    b = hor+num+z;
    h->SetTitle("Stave "+hor+num+", # of hits in an event");
    
    ntuple->Draw(b);
    //c1->SaveAs(c+hor+num+".gif");

  }
  */

}
