loop()
{

  Double_t t=0;
  Double_t energy=0;
  Double_t y=0;
  Double_t eactual=0; // actual energy deposited in calo
  Double_t escale=17.58; // 1/fractio of E in scintillator
  Double_t yactual=0;

 
  TH1D *ntime=new TH1D("ntime", "events vs. time", 3000, 0., 447600.);
  TH1D *ewtime=new TH1D("ewtime", "energy-weighted vs. time", 3000, 0., 447600.);
  TH1D *eactualtime=new TH1D("eactualtime", "deposited energy-weighted vs. time", 3000, 0., 447600.);

  eactualtime->Sumw2();
  eactualtime->SetName("eactualtime");
  eactualtime->GetXaxis()->SetTitle("Time [ns]");
  eactualtime->GetYaxis()->SetTitle("Desposited Energy Scaled");

  ntime->Sumw2();
  ntime->SetName("ntime");
  ntime->GetXaxis()->SetTitle("Time [ns]");
  ntime->GetYaxis()->SetTitle("Counts");
  ewtime->Sumw2();
  ewtime->SetName("ewtime");
  ewtime->GetXaxis()->SetTitle("Time [ns]");
  ewtime->GetYaxis()->SetTitle("Energy-weighted Counts");
  
  outfile = new TFile("output1.root","RECREATE");

  ntime->SetDirectory(outfile);
  ewtime->SetDirectory(outfile);
  eactualtime->SetDirectory(outfile);
  
//; loop starts here -----------------------------------

  f1=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle1.root");
  TTree *h1=(TTree *)f1->Get("h1");

  TLeaf *elet = h1->GetLeaf("Elet");
  TLeaf *enr1 = h1->GetLeaf("Enr1");
  TLeaf *ef11 = h1->GetLeaf("Ef11");
  TLeaf *ef21 = h1->GetLeaf("Ef21");
  TLeaf *ef31 = h1->GetLeaf("Ef31");
  TLeaf *ef41 = h1->GetLeaf("Ef41");
  TLeaf *xhit = h1->GetLeaf("Xpc1");

  Int_t nevent = h1->GetEntries();
  for(Int_t i=0; i<nevent; i++)
  {

    h1->GetEntry(i);

    t=elet->GetValue();
    energy=enr1->GetValue();
    y=energy/3.1;
    
    eactual=ef11->GetValue();
    eactual=eactual+ef21->GetValue();
    eactual=eactual+ef31->GetValue();
    eactual=eactual+ef41->GetValue();
    eactual = eactual * escale; // makes scale up to 3.1 GeV
    yactual=eactual/3.1; // 
    eactualtime->Fill(t,yactual);

    if(energy>1.8)
    {
      ntime->Fill(t);
    }
    if(energy>0.2)
    {
      ewtime->Fill(t, y);
    }
  }
    outfile->Write();
    return();
//; ---
  f2=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle2.root");
  TTree *h1=(TTree *)f2->Get("h1");

  TLeaf *elet = h1->GetLeaf("Elet");
  TLeaf *enr1 = h1->GetLeaf("Enr1");
  TLeaf *ef11 = h1->GetLeaf("Ef11");
  TLeaf *ef21 = h1->GetLeaf("Ef21");
  TLeaf *ef31 = h1->GetLeaf("Ef31");
  TLeaf *ef41 = h1->GetLeaf("Ef41");

  Int_t nevent = h1->GetEntries();
  for(Int_t i=0; i<nevent; i++)
  {

    h1->GetEntry(i);

    t=elet->GetValue();
    energy=enr1->GetValue();
    y=energy/3.1;

    eactual=ef11->GetValue();
    eactual=eactual+ef21->GetValue();
    eactual=eactual+ef31->GetValue();
    eactual=eactual+ef41->GetValue();
    eactual = eactual * escale; // makes scale up to 3.1 GeV
    yactual=eactual/3.1; // 
    eactualtime->Fill(t,yactual);


    if(energy>1.8)
    {
      ntime->Fill(t);
    }
    if(energy>0.2)
    {
      ewtime->Fill(t, y);
    }
  } 

  
  f3=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle3.root");
  TTree *h1=(TTree *)f3->Get("h1");

  TLeaf *elet = h1->GetLeaf("Elet");
  TLeaf *enr1 = h1->GetLeaf("Enr1");
  TLeaf *ef11 = h1->GetLeaf("Ef11");
  TLeaf *ef21 = h1->GetLeaf("Ef21");
  TLeaf *ef31 = h1->GetLeaf("Ef31");
  TLeaf *ef41 = h1->GetLeaf("Ef41");

  Int_t nevent = h1->GetEntries();
  for(Int_t i=0; i<nevent; i++)
  {

    h1->GetEntry(i);

    t=elet->GetValue();
    energy=enr1->GetValue();
    y=energy/3.1;

    eactual=ef11->GetValue();
    eactual=eactual+ef21->GetValue();
    eactual=eactual+ef31->GetValue();
    eactual=eactual+ef41->GetValue();
    eactual = eactual * escale; // makes scale up to 3.1 GeV
    yactual=eactual/3.1; // 
    eactualtime->Fill(t,yactual);


    if(energy>1.8)
    {
      ntime->Fill(t);
    }
    if(energy>0.2)
    {
      ewtime->Fill(t, y);
    }
  } 

   
  f4=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle4.root");
  TTree *h1=(TTree *)f4->Get("h1");

  TLeaf *elet = h1->GetLeaf("Elet");
  TLeaf *enr1 = h1->GetLeaf("Enr1");
  TLeaf *ef11 = h1->GetLeaf("Ef11");
  TLeaf *ef21 = h1->GetLeaf("Ef21");
  TLeaf *ef31 = h1->GetLeaf("Ef31");
  TLeaf *ef41 = h1->GetLeaf("Ef41");

  Int_t nevent = h1->GetEntries();
  for(Int_t i=0; i<nevent; i++)
  {

    h1->GetEntry(i);

    t=elet->GetValue();
    energy=enr1->GetValue();
    y=energy/3.1;

    eactual=ef11->GetValue();
    eactual=eactual+ef21->GetValue();
    eactual=eactual+ef31->GetValue();
    eactual=eactual+ef41->GetValue();
    eactual = eactual * escale; // makes scale up to 3.1 GeV
    yactual=eactual/3.1; // 
    eactualtime->Fill(t,yactual);


    if(energy>1.8)
    {
      ntime->Fill(t);
    }
    if(energy>0.2)
    {
      ewtime->Fill(t, y);
    }
  } 
  
  f5=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle5.root");
  TTree *h1=(TTree *)f5->Get("h1");

  TLeaf *elet = h1->GetLeaf("Elet");
  TLeaf *enr1 = h1->GetLeaf("Enr1");
  TLeaf *ef11 = h1->GetLeaf("Ef11");
  TLeaf *ef21 = h1->GetLeaf("Ef21");
  TLeaf *ef31 = h1->GetLeaf("Ef31");
  TLeaf *ef41 = h1->GetLeaf("Ef41");

  Int_t nevent = h1->GetEntries();
  for(Int_t i=0; i<nevent; i++)
  {

    h1->GetEntry(i);

    t=elet->GetValue();
    energy=enr1->GetValue();
    y=energy/3.1;

    eactual=ef11->GetValue();
    eactual=eactual+ef21->GetValue();
    eactual=eactual+ef31->GetValue();
    eactual=eactual+ef41->GetValue();
    eactual = eactual * escale; // makes scale up to 3.1 GeV
    yactual=eactual/3.1; // 
    eactualtime->Fill(t,yactual);


    if(energy>1.8)
    {
      ntime->Fill(t);
    }
    if(energy>0.2)
    {
      ewtime->Fill(t, y);
    }
  }   
   outfile->Write();
} 
