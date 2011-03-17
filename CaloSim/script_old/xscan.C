xscan(){
  gStyle->SetPalette(1,0);



  Int_t bsize = 2;
  cout<<"block size?"<<endl;
  cin>>bsize;


  if(bsize==1){

  TFile *_file0 = TFile::Open("1e5_1by1_xscan.root");

  TH1F *a = new TH1F("a","a",200,0,0.16);
  a->GetYaxis()->SetRangeUser(0,10000);


  ntuple->Draw("(b089+b109+b129+b149+b169+b189+b209)-(b090+b110+b130+b150+b170+b190+b210):initX+1>>hdiff");
  hdiff->GetXaxis()->SetTitle("Impact on Target Column (cm)");
  hdiff->GetYaxis()->SetTitle("E Target - E Center (GeV)");
  hdiff->SetTitle("Energy Diff vs. Impact Pos, 1x1 block");
  hdiff->Draw("colz");
  c1->SaveAs("figs/1x1_diff.gif");
  

  ntuple->Draw("(b088+b108+b128+b148+b168+b188+b208):(initX+1)>>hn2");
  hn2->SetTitle("EDep vs. Impact Position, 1 column to left, 1x1cm blocks");
  hn2->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  hn2->GetYaxis()->SetTitle("Energy Dep (GeV)"); 
  hn2->Draw("colz");
  c1->SaveAs("figs/1x1_EvsX_n.gif");


  ntuple->Draw("(b089+b109+b129+b149+b169+b189+b209):(initX+1)>>h02");
  h02->SetTitle("EDep vs. Impact Position, Target column, 1x1cm blocks");
  h02->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h02->GetYaxis()->SetTitle("Energy Dep (GeV)");
  h02->Draw("colz");
  c1->SaveAs("figs/1x1_EvsX_0.gif");

  
  ntuple->Draw("(b090+b110+b130+b150+b170+b190+b210):(initX+1)>>h12");
  h12->SetTitle("EDep vs. Impact Position, 1 column to right, 1x1cm blocks");
  h12->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h12->GetYaxis()->SetTitle("Energy Dep (GeV)");
  h12->Draw("colz");
  c1->SaveAs("figs/1x1_EvsX_1.gif");


  
  ntuple->Draw("(b091+b111+b131+b151+b171+b191+b211):(initX+1)>>h22");
  h22->SetTitle("EDep vs. Impact Position, 2 columns to right, 1x1cm blocks");
  h22->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h22->GetYaxis()->SetTitle("Energy Dep (GeV)");
  h22->Draw("colz");
 c1->SaveAs("figs/1x1_EvsX_2.gif");



  ntuple->Draw("(b088+b108+b128+b148+b168+b188+b208)/fiberEdep:initX+1>>hresn");
  hresn->SetLineColor(2);
  ntuple->Draw("(b089+b109+b129+b149+b169+b189+b209)/fiberEdep:initX+1>>hres0");
  hres0->SetLineColor(1);
  ntuple->Draw("(b090+b110+b130+b150+b170+b190+b210)/fiberEdep:initX+1>>hres1");
  hres1->SetLineColor(3);
  ntuple->Draw("(b091+b111+b131+b151+b171+b191+b211)/fiberEdep:initX+1>>hres2");
  hres2->SetLineColor(4);


  ntuple->Draw("(b088+b108+b128+b148+b168+b188+b208)>>hn");
  hn->SetLineColor(2);
  ntuple->Draw("(b089+b109+b129+b149+b169+b189+b209)>>h0");
  h0->SetLineColor(1);
  ntuple->Draw("(b090+b110+b130+b150+b170+b190+b210)>>h1");
  h1->SetLineColor(3);
  ntuple->Draw("(b091+b111+b131+b151+b171+b191+b211)>>h2");
  h2->SetLineColor(4);
  ntuple->Draw("fiberEdep>>fdep");
  fdep->SetLineColor(6);
  
  a->GetXaxis()->SetTitle("Energy Dep (GeV)");
  a->SetTitle("Energy dep in each column, 1x1 block");
  a->Draw();
  fdep->Draw("same");
  h0->Draw("same");
  hn->Draw("same");
  h1->Draw("same");
  h2->Draw("same");

  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(hn,"1 column to left","l");
  leg->AddEntry(h0,"Target column","l");
  leg->AddEntry(h1,"1 column to right","l");
  leg->AddEntry(h2,"2 columns to right","l");
  leg->AddEntry(fdep,"e in all fibers","l");
  leg->Draw();
  c1->SaveAs("figs/1x1_Edep.gif");

  }
  

  else if(bsize==2){
   
  TFile *_file0 = TFile::Open("1e5_2by2_xscan.root");
  TH1F *a = new TH1F("a","a",200,0,0.16);
  a->GetYaxis()->SetRangeUser(0,10000);
  
  ntuple->Draw("(b109+b110+b129+b130+b149+b150+b169+b170+b189+b190+b209+b210)-(b111+b112+b131+b132+b151+b152+b171+b172+b191+b192+b211+b212):initX+1>>hdiff");
  hdiff->GetXaxis()->SetTitle("Impact on Target Column (cm)");
  hdiff->GetYaxis()->SetTitle("E Target - E Center (GeV)");
  hdiff->SetTitle("Energy Diff vs. Impact Pos, 2x2 block");
  hdiff->Draw("colz");
  c1->SaveAs("figs/2x2_diff.gif");

  ntuple->Draw("(b107+b108+b127+b128+b147+b148+b167+b168+b187+b188+b207+b208):(initX+1)>>hn2");
  hn2->SetTitle("EDep vs. Impact Position, 1 column to left, 2x2cm blocks");
  hn2->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  hn2->GetYaxis()->SetTitle("Energy Dep (GeV)"); 
  hn2->Draw("colz");
  c1->SaveAs("figs/2x2_EvsX_n.gif");
 
  ntuple->Draw("(b109+b110+b129+b130+b149+b150+b169+b170+b189+b190+b209+b210):(initX+1)>>h02");
  h02->SetTitle("EDep vs. Impact Position, Target column, 2x2cm blocks");
  h02->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h02->GetYaxis()->SetTitle("Energy Dep (GeV)");
   h02->Draw("colz");
  c1->SaveAs("figs/2x2_EvsX_0.gif");
 
  
  ntuple->Draw("(b111+b112+b131+b132+b151+b152+b171+b172+b191+b192+b211+b212):(initX+1)>>h12");
  h12->SetTitle("EDep vs. Impact Position, 1 column to right 2x2cm blocks");
  h12->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h12->GetYaxis()->SetTitle("Energy Dep (GeV)");
    h12->Draw("colz");
  c1->SaveAs("figs/2x2_EvsX_1.gif");

  
  ntuple->Draw("(b113+b114+b133+b134+b153+b154+b173+b174+b193+b194+b213+b214):(initX+1)>>h22");
  h22->SetTitle("EDep vs. Impact Position, 2 columns to right 2x2cm blocks");
  h22->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h22->GetYaxis()->SetTitle("Energy Dep (GeV)");
    h22->Draw("colz");
  c1->SaveAs("figs/2x2_EvsX_2.gif");

  ntuple->Draw("(b107+b108+b127+b128+b147+b148+b167+b168+b187+b188+b207+b208)>>hn");
  hn->SetLineColor(2);
  ntuple->Draw("(b109+b110+b129+b130+b149+b150+b169+b170+b189+b190+b209+b210)>>h0");
  h0->SetLineColor(1);
  ntuple->Draw("(b111+b112+b131+b132+b151+b152+b171+b172+b191+b192+b211+b212)>>h1");
  h1->SetLineColor(3);
  ntuple->Draw("(b113+b114+b133+b134+b153+b154+b173+b174+b193+b194+b213+b214)>>h2");
  h2->SetLineColor(4);
  ntuple->Draw("fiberEdep>>fdep");
  fdep->SetLineColor(6);
  
  a->GetXaxis()->SetTitle("Energy Dep (GeV)");
  a->SetTitle("Energy dep in each column, 2x2 block");
  a->Draw();
  fdep->Draw("same");
  h0->Draw("same");
  hn->Draw("same");
  h1->Draw("same");
  h2->Draw("same");


  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(hn,"1 column to left","l");
  leg->AddEntry(h0,"Target column","l");
  leg->AddEntry(h1,"1 column to right","l");
  leg->AddEntry(h2,"2 columns to right","l");
  leg->AddEntry(fdep,"e in all fibers","l");
  leg->Draw();
  c1->SaveAs("figs/2x2_Edep.gif");


  }
  else{
  TFile *_file0 = TFile::Open("1e5_3by3_xscan.root");
  TH1F *a = new TH1F("a","a",200,0,0.16);
  a->GetYaxis()->SetRangeUser(0,10000);


  
  ntuple->Draw("(b068+b069+b070+b088+b089+b090+b108+b109+b110+b128+b129+b130+b148+b149+b150+b168+b169+b170+b188+b189+b190+b208+b209+b210+b228+b229+b230)-(b071+b072+b073+b091+b092+b093+b111+b112+b113+b131+b132+b133+b151+b152+b153+b171+b172+b173+b191+b192+b193+b211+b212+b213+b231+b232+b233):initX+2>>hdiff");
  hdiff->GetXaxis()->SetTitle("Impact on Target Column (cm)");
  hdiff->GetYaxis()->SetTitle("E Target - E Center (GeV)");
  hdiff->SetTitle("Energy Diff vs. Impact Pos, 3x3 block");
  hdiff->Draw("colz");
  c1->SaveAs("figs/3x3_diff.gif");


  ntuple->Draw("(b065+b066+b067+b085+b086+b087+b105+b106+b107+b125+b126+b127+b145+b146+b147+b165+b166+b167+b185+b186+b187+b205+b206+b207+b225+b226+b227):(initX+2)>>hn2");
  hn2->SetTitle("EDep vs. Impact Position, 1 column to left, 3x3cm blocks");
  hn2->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  hn2->GetYaxis()->SetTitle("Energy Dep (GeV)");
  hn2->Draw("colz");
  c1->SaveAs("figs/3x3_EvsX_n.gif");
  
  
  ntuple->Draw("(b068+b069+b070+b088+b089+b090+b108+b109+b110+b128+b129+b130+b148+b149+b150+b168+b169+b170+b188+b189+b190+b208+b209+b210+b228+b229+b230):(initX+2)>>h02");
  h02->SetTitle("EDep vs. Impact Position, Target column, 3x3cm blocks");
  h02->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h02->GetYaxis()->SetTitle("Energy Dep (GeV)");
  h02->Draw("colz");
  c1->SaveAs("figs/3x3_EvsX_0.gif");
  
  ntuple->Draw("(b071+b072+b073+b091+b092+b093+b111+b112+b113+b131+b132+b133+b151+b152+b153+b171+b172+b173+b191+b192+b193+b211+b212+b213+b231+b232+b233):(initX+2)>>h12");
  h12->SetTitle("EDep vs. Impact Position, 1 column to right, 3x3cm blocks");
  h12->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h12->GetYaxis()->SetTitle("Energy Dep (GeV)");
    h12->Draw("colz");
  c1->SaveAs("figs/3x3_EvsX_1.gif");



  ntuple->Draw("(b074+b075+b076+b094+b095+b096+b114+b115+b116+b134+b135+b136+b154+b155+b156+b174+b175+b176+b194+b195+b196+b214+b215+b216+b234+b235+b236):(initX+2)>>h22");
  h22->SetTitle("EDep vs. Impact Position, 2 columns to right, 3x3cm blocks");
  h22->GetXaxis()->SetTitle("Impact Position on target column (cm)");
  h22->GetYaxis()->SetTitle("Energy Dep (GeV)");
    h22->Draw("colz");
  c1->SaveAs("figs/3x3_EvsX_2.gif");
    
  ntuple->Draw("(b065+b066+b067+b085+b086+b087+b105+b106+b107+b125+b126+b127+b145+b146+b147+b165+b166+b167+b185+b186+b187+b205+b206+b207+b225+b226+b227)>>hn");
  hn->SetLineColor(2);
  ntuple->Draw("(b068+b069+b070+b088+b089+b090+b108+b109+b110+b128+b129+b130+b148+b149+b150+b168+b169+b170+b188+b189+b190+b208+b209+b210+b228+b229+b230)>>h0");
  h0->SetLineColor(1);
  ntuple->Draw("(b071+b072+b073+b091+b092+b093+b111+b112+b113+b131+b132+b133+b151+b152+b153+b171+b172+b173+b191+b192+b193+b211+b212+b213+b231+b232+b233)>>h1");
  h1->SetLineColor(3);
  ntuple->Draw("(b074+b075+b076+b094+b095+b096+b114+b115+b116+b134+b135+b136+b154+b155+b156+b174+b175+b176+b194+b195+b196+b214+b215+b216+b234+b235+b236)>>h2");
  h2->SetLineColor(4);
  ntuple->Draw("fiberEdep>>fdep");
  fdep->SetLineColor(6);
  
  a->GetXaxis()->SetTitle("Energy Dep (GeV)");
  a->SetTitle("Energy dep in each column, 3x3 block");
  a->Draw();
  fdep->Draw("same");
  h0->Draw("same");
  hn->Draw("same");
  h1->Draw("same");
  h2->Draw("same");


  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(hn,"1 column to left","l");
  leg->AddEntry(h0,"Target column","l");
  leg->AddEntry(h1,"1 column to right","l");
  leg->AddEntry(h2,"2 columns to right","l");
  leg->AddEntry(fdep,"e in all fibers","l");
  leg->Draw();
  c1->SaveAs("figs/3x3_Edep.gif");


  }
  
}
