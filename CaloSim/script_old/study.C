wcstudy(){
  gROOT->ProcessLine(".L $HOME/geant4/lightguide/libLG.so");
  gStyle->SetPalette(1,0);
  TString file_name = "a.root";
  TFile* fp = new TFile(file_name,"RECREATE");

  TString root_name = "/data/npluser2/gdamhor2/3x3/parabox/";
  TString path_name;
  Double_t rad;

  Double_t x;
  Double_t y;
  Double_t te;
  Int_t nhits;

  char word[2];
  TString r_s;
  TString hist_name;
  fp->Write();
  fp->Close();

  TH1F *te_rad = new TH1F("te_rad", "TE vs. terminal radius",21,0.25,10.75);
  te_rad->GetXaxis()->SetTitle("terminal radius [mm/sqrt(2)]");
  te_rad->GetYaxis()->SetTitle("Transmission Efficiency");

  sumfile = new TFile("sumhistos.root","RECREATE");
  te_rad->SetDirectory(sumfile);


  //go to 95
  for(Float_t r=5;r<11;r+=5.){
    rad = r;
    sprintf(word,"%02.0f" ,rad);
    r_s=word;
    path_name = root_name+r_s+".root";
    cout<<path_name<<endl;
    
    
    
    f1=new TFile(path_name);

        
    outfile = new TFile(file_name,"UPDATE");
    
        
    hist_name=r_s+"_enddist";
    cout<<hist_name<<endl;
    
    
    
    TH2F *enddist=new TH2F(hist_name, "Hits on terminal end", 200, -20, 20,200,-20,20);
    TTree *tree=(TTree *)f1->Get("tree");
    TBranch *evt = (TBranch *)tree->GetBranch("evt");
    TBranch *fSensTubeHits=tree->GetBranch("fSensTubeHits");
    
    TLeaf *endX = tree->GetLeaf("fSensTubeHits.posX");
    TLeaf *endY = tree->GetLeaf("fSensTubeHits.posY");
    TLeaf *endZ = tree->GetLeaf("fSensTubeHits.posZ");
    TLeaf *Nhits = tree->GetLeaf("fNSensTubeHit");
    
    enddist->SetDirectory(outfile);
    
    //tree->Draw("fSensTubeHits.posX:fSensTubeHits.posY>>enddist","","colz");
    Int_t nentries = tree->GetEntries();
    cout<<nentries<<" tree entries"<<endl;
    nhits=0;
    for(Int_t i=0;i<nentries;i++){
      tree->GetEntry(i);
      nhits+=Nhits->GetValue();
    }
    te=nhits/320000.;
    te_rad->Fill(r/10.,te);
    // = fSensTubeHits->GetEntries();
    cout<<nhits<<endl;
    cout<<nentries<<" tree entries"<<endl;
    //ntotal+=nevent;
    for(Int_t i=0; i<nentries; i++)
      {
	cout<<evt->GetEntries()<<" evt entries"<<endl;
	cout<<fSensTubeHits->GetEntries()<<" fS branch entries"<<endl;
	//tree->Draw("fSensTubeHits.posX>>enddist");
	evt->GetEntry(i);
	for(Int_t j=0; i<fSensTubeHits->GetEntries();i++){
	  fSensTubeHits->GetEntry(i);

	//	fSensTubeHits->GetEntry(i);
	x = endX->GetValue(i);

	y = endY->GetValue(i);
	enddist->Fill(x,y);
	
	/*
	  t=elet->GetValue();
	  energy=enr1->GetValue();
	  zpos=zpc1->GetValue();
	  senergy = energy +sqrt(energy)*gRandom->Gaus(0,sig);
	  if(j==5 && k==10 && energy!= 0.0 && zpos<-7){
	  ediag=senergy/sqrt(energy)-sqrt(energy);
	  etrue->Fill(energy);
	  esmear->Fill(senergy);
	  hdiag->Fill(ediag);
	  }	    
	  if(senergy>cut&&zpos<-7)
	  {
	  ntime->Fill(t);
	  }
	*/
	}
      }
    
    
    
    f1->Close();
    outfile->Write();
    outfile->Close();
    
  }
}
