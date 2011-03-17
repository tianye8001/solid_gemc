plot(){
  gStyle->SetPalette(1,0);
  
  Double_t m;

  TH2F *calo = new TH2F("calo","calo energy dep",20,0,20,15,0,15);

  f1=new TFile("1e5_3by3.root");
  
  TH1F *h = new TH1F("h","h",200,0,0.2);

  TString a = "b";
  TString z = ">>h";
  TString b;
  TString num;
  Double_t n;
  Double_t x;
  Double_t y;
  char word[3];
  //n=2;
  
  for(Int_t i = 0; i<300;i++){
    n=i;
    sprintf(word,"%03.0f",n);
    num=word;
    //cout<<num<<endl;
    //cout<<z<<endl;
    b=a+num+z;
    //cout<<b<<endl;
    
    x=i%20+0.5;
    y=(i-i%20)/20+0.5;
    
    ntuple->Draw(b);
    m=h->GetMean();
    
    calo->Fill(x,y,m);
  }
  calo->Draw("colz");

  

}
