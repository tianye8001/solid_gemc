plot(){
  gStyle->SetPalette(1,0);
  
  Double_t m;

  TH2F *calo = new TH2F("calo","calo energy dep, two far spaced events (GeV)",5,0,15,5,0,15);
  calo->GetXaxis()->SetTitle("X dim (cm)");
  calo->GetYaxis()->SetTitle("Y dim (cm)");
  f1=new TFile("near.root");
  
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
  
  for(Int_t i = 0; i<25;i++){
    m=0;
    n=i;

    sprintf(word,"%03.0f",n);
    num=word;
    //cout<<num<<endl;
    //cout<<z<<endl;
    b=a+num+z;
    //cout<<b<<endl;
    
    x=3*(i%5)+1.5;
    y=3*(i-i%5)/5+1.5;
    
    ntuple->Draw(b);
    for(Int_t j = 0; j<=h->GetNbinsX(); j++){ 
      if(h->GetBinContent(j)!=0){
	m+=h->GetBinCenter(j);
	cout<<h->GetBinCenter(j);
	cout<<"j= "<<j<<endl;
      }
    }

    // m=h->GetMean();
    cout<<"m = "<<m<<endl;
    calo->Fill(x,y,m);
  }
  calo->Draw("colz");

  

}
