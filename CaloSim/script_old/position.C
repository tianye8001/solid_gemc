position(){
  TFile *_file0 = TFile::Open("1e5_1by1.root");     

   ntuple->Draw("((bEdep149+bEdep129+bEdep169)*0+(bEdep128+bEdep148+bEdep168)*-1+(bEdep130+bEdep150+bEdep170)*1)/(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130) - (initX+0.5)>>ring1");

   ntuple->Draw("((bEdep149+bEdep129+bEdep169+bEdep189+bEdep109)*0+(bEdep108+bEdep188+bEdep128+bEdep148+bEdep168)*-1+(bEdep190+bEdep110+bEdep130+bEdep150+bEdep170)*1+(bEdep107+bEdep127+bEdep147+bEdep167+bEdep187)*-2+(bEdep191+bEdep171+bEdep151+bEdep131+bEdep111)*2)/(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130+bEdep107+bEdep108+bEdep109+bEdep110+bEdep111+bEdep187+bEdep188+bEdep189+bEdep190+bEdep191+bEdep167+bEdep171+bEdep147+bEdep151+bEdep127+bEdep131) - (initX+0.5)>>ring2");
   ring2->SetLineColor(2);
   ring1->Draw();
   ring2->Draw("same");

}
