positiony(){
  TFile *_file0 = TFile::Open("1e5_1by1.root");     

  TH1F *ring1 = new TH1F("ring1","ring1",100,-1,1);
  TH1F *ring2 = new TH1F("ring2","ring2",100,-1,1);
  
   ntuple->Draw("((bEdep149+bEdep149+bEdep150)*0+(bEdep128+bEdep129+bEdep130)*-1+(bEdep168+bEdep169+bEdep170)*1)/(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130) - (initY)>>ring1");

   ntuple->Draw("((bEdep148+bEdep151+bEdep149+bEdep149+bEdep150)*0+(bEdep127+bEdep131+bEdep128+bEdep129+bEdep130)*-1+(bEdep167+bEdep171+bEdep168+bEdep169+bEdep170)*1+(bEdep108+bEdep109+bEdep110+bEdep107+bEdep111)*-2+(bEdep187+bEdep188+bEdep189+bEdep190+bEdep191)*2)/(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130+bEdep107+bEdep108+bEdep109+bEdep110+bEdep111+bEdep187+bEdep188+bEdep189+bEdep190+bEdep191+bEdep167+bEdep171+bEdep147+bEdep151+bEdep127+bEdep131) - (initY)>>ring2");

   //ntuple->Draw("((bEdep149+bEdep129+bEdep169+bEdep189+bEdep109)*0+(bEdep108+bEdep188+bEdep128+bEdep148+bEdep168)*-1+(bEdep190+bEdep110+bEdep130+bEdep150+bEdep170)*1+(bEdep107+bEdep127+bEdep147+bEdep167+bEdep187)*-2+(bEdep191+bEdep171+bEdep151+bEdep131+bEdep111)*2)/(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130+bEdep107+bEdep108+bEdep109+bEdep110+bEdep111+bEdep187+bEdep188+bEdep189+bEdep190+bEdep191+bEdep167+bEdep171+bEdep147+bEdep151+bEdep127+bEdep131) - (initX+0.5)>>ring2");
   ring2->SetLineColor(2);
   ring2->Draw();
   ring1->Draw("same");

}
