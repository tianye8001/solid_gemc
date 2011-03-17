neighbor(){
  TFile *_file0 = TFile::Open("1e5_3by3.root");     

  ///*
  ntuple->Draw("(bEdep165+bEdep166+bEdep167+bEdep145+bEdep146+bEdep147+bEdep125+bEdep126+bEdep127+bEdep171+bEdep172+bEdep173+bEdep151+bEdep152+bEdep153+bEdep131+bEdep132+bEdep133+bEdep228+bEdep229+bEdep230+bEdep208+bEdep209+bEdep210+bEdep188+bEdep189+bEdep190+bEdep108+bEdep109+bEdep110+bEdep088+bEdep089+bEdep090+bEdep068+bEdep069+bEdep070+bEdep105+bEdep106+bEdep107+bEdep085+bEdep086+bEdep087+bEdep065+bEdep066+bEdep067+bEdep225+bEdep226+bEdep227+bEdep205+bEdep206+bEdep207+bEdep185+bEdep186+bEdep187+bEdep111+bEdep112+bEdep113+bEdep091+bEdep092+bEdep093+bEdep071+bEdep072+bEdep073+bEdep231+bEdep232+bEdep233+bEdep211+bEdep212+bEdep213+bEdep191+bEdep192+bEdep193)>>ring1","","");
  ring1->SetLineColor(2);

ntuple->Draw("bEdep005+bEdep006+bEdep007+bEdep008+bEdep009+bEdep010+bEdep011+bEdep012+bEdep013+bEdep024+bEdep025+bEdep026+bEdep027+bEdep028+bEdep029+bEdep030+bEdep031+bEdep032+bEdep033+bEdep034+bEdep035+bEdep043+bEdep044+bEdep045+bEdep046+bEdep047+bEdep048+bEdep049+bEdep050+bEdep051+bEdep052+bEdep053+bEdep054+bEdep055+bEdep063+bEdep064+bEdep074+bEdep075+bEdep076+bEdep102+bEdep103+bEdep104+bEdep114+bEdep115+bEdep116+bEdep122+bEdep123+bEdep124+bEdep134+bEdep135+bEdep136+bEdep142+bEdep143+bEdep144+bEdep154+bEdep155+bEdep156+bEdep162+bEdep163+bEdep164+bEdep174+bEdep175+bEdep176+bEdep182+bEdep183+bEdep184++bEdep194+bEdep195+bEdep196bEdep202+bEdep203+bEdep204+bEdep214+bEdep215+bEdep216+bEdep223+bEdep224+bEdep234+bEdep235+bEdep236+bEdep243+bEdep244+bEdep245+bEdep246+bEdep247+bEdep248+bEdep249+bEdep250+bEdep251+bEdep252+bEdep253+bEdep254+bEdep255+bEdep262+bEdep264+bEdep265+bEdep266+bEdep267+bEdep268+bEdep269+bEdep270+bEdep271+bEdep272+bEdep273+bEdep274+bEdep275+bEdep285+bEdep286+bEdep287+bEdep288+bEdep289+bEdep290+bEdep291+bEdep292+bEdep293>>ring2");
  ring2->SetLineColor(6); 





  ntuple->Draw("(bEdep149+bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130)>>center","","");
  center->SetLineColor(4);
  ntuple->Draw("fiberEdep>>all_blocks");
  Double_t m1;
  m1 = all_blocks->GetXaxis()->GetXmax();
  TH1F *all = new TH1F("all","all",200,0,m1);
  all->GetXaxis()->SetTitle("Energy Reconstruction (GeV)");
  all->SetTitle("Energy Reconstruction by Algorithm, 3x3 Beam Spot, 2 GeV electrons");
  all->SetLineColor(1);
  ntuple->Draw("fiberEdep>>all");
  all->Draw();
  ring1->Draw("same");


  center->Draw("same");
  


  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(all,"all blocks","l");
  leg->AddEntry(ring1,"nearest neighbors","l");
  leg->AddEntry(ring2,"next nearest neighbors","l");
  leg->AddEntry(center,"center","l");
  leg->Draw();

//*/
  ////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
  /*
  TFile *_file0 = TFile::Open("1e5_1by1.root");     
  ntuple->Draw("(bEdep150+bEdep148+bEdep129+bEdep169+bEdep170+bEdep168+bEdep128+bEdep130)>>ring1","","");
  ntuple->Draw("(bEdep107+bEdep108+bEdep109+bEdep110+bEdep111+bEdep187+bEdep188+bEdep189+bEdep190+bEdep191+bEdep167+bEdep171+bEdep147+bEdep151+bEdep127+bEdep131)>>ring2","","");
  ring2->SetLineColor(6);
  ring1->SetLineColor(2);
  ntuple->Draw("(bEdep149)>>center","","");
  center->SetLineColor(4);
  ntuple->Draw("fiberEdep>>all_blocks");
  Double_t m1;
  m1 = all_blocks->GetXaxis()->GetXmax();
  TH1F *all = new TH1F("all","all",200,0,m1);
  all->GetXaxis()->SetTitle("Energy Reconstruction (GeV)");
  all->SetTitle("Energy Reconstruction by Algorithm, 1x1 Beam Spot, 2 GeV electrons");
  all->SetLineColor(1);
  ntuple->Draw("fiberEdep>>all");
  all->Draw();
   
  
  ring1->Draw("same");
  ring2->Draw("same");
  
  center->Draw("same");

    leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(all,"all blocks","l");
  leg->AddEntry(ring1,"nearest neighbors","l");
  leg->AddEntry(ring2,"next nearest neighbors","l");
  leg->AddEntry(center,"center","l");
  leg->Draw();

  */


}
