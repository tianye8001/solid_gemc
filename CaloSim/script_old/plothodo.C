plothodo(){
  gStyle->SetPalette(1,0);
  
  Double_t m;

  TH2F *calo = new TH2F("hodo","calo energy dep",15,0,15,15,0,15);

  f1=new TFile("out.root");
  
  TH1F *h = new TH1F("h","h",200,0,0.2);

  TString a = "v";
  TString z = ">>h";
  TString b;
  TString num;
  Double_t n;
  Double_t x;
  Double_t y;
  char word[3];
  //n=2;
  
  for(Int_t i = 0; i<15;i++){
    n=i;
    sprintf(word,"%02.0f",n);
    num=word;
    //cout<<num<<endl;
    //cout<<z<<endl;
    b=a+num+z;
    //cout<<b<<endl;
    
    x=i%15+0.5;
    y=(i-i%15)/15+0.5;
    
    ntuple->Draw(b);
    m=h->GetMean();
    
    calo->Fill(x,y,m);
  }
  calo->Draw("colz");

  

}
