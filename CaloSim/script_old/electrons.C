electrons(){


  FILE *outfile;
  outfile=fopen("/data/npluser2/nschroed/g2electrons/wiggle5.dat", "w");

  
  f=new TFile("/data/npluser/rmcnabb/lowegeant/precess/wiggle5.root");
  

  TNtuple *nt = (TNtuple *)f->Get("h1");
  
  Int_t nent = nt->GetEntries();

  printf("%d\n\n", nent);

  for(Int_t i=0; i<nent; i++){
    nt->GetEntry(i);

    Int_t cid = nt->GetLeaf("Cid1")->GetValue();

    if(cid!=0){
      Double_t X=nt->GetLeaf("Xpc1")->GetValue();
      Double_t Y=nt->GetLeaf("Ypc1")->GetValue();
      Double_t Z=nt->GetLeaf("Zpc1")->GetValue();
      Double_t XP=nt->GetLeaf("Xmo1")->GetValue();
      Double_t YP=nt->GetLeaf("Ymo1")->GetValue();
      Double_t ZP=nt->GetLeaf("Zmo1")->GetValue();
      Double_t E=nt->GetLeaf("Enr1")->GetValue();

      fprintf(outfile, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n", X, Y, Z, XP, YP, ZP, E);

    }
  }

    fclose(outfile);


}
