#define messclass_cxx
#include "messclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void messclass::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L messclass.C
//      Root > messclass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

   //   nentries = 1000;
   Long64_t nbytes = 0, nb = 0;
   //TString a = "t.b";
   Double_t xpos1, xnum1, xpos2, xnum2, den1, den2;
   Double_t xd1,xd2,yd1,yd2;
   Double_t ypos1, ynum1, ypos2, ynum2;
   TString ci = "inner+=";
   TString c1 = "ring1+=";
   TString c2 = "ring2+=";
   //   TString d = "<<endl;";
   TString e;
   //   Double_t etotal=0;
   char word[3];
   TString num;
      Double_t inner=0;
      Double_t ring1=0;
      Double_t ring2=0;
   TH1F *hi = new TH1F("hi","hi",150,0,0.15);
   hi->SetLineColor(2);
   TH1F *h1 = new TH1F("h1","h1",150,0,0.15);
   h1->SetLineColor(4);
   TH1F *h2 = new TH1F("h2","h2",150,0,0.15);

   TH1F *hxp1 = new TH1F("hxp1","hxp1",100,-2,2);
   TH1F *hxp2 = new TH1F("hxp2","hxp2",100,-2,2);
   TH1F *hyp1 = new TH1F("hyp1","hyp1",100,-2,2);
   TH1F *hyp2 = new TH1F("hyp2","hyp2",100,-2,2);
   TH1F *hx = new TH1F("hx","hx",100,-2,2);
   TH1F *hy = new TH1F("hy","hy",100,-2,2);


   TH1F *hxd1 = new TH1F("hxd1","hxd1",100,-2,2);
   TH1F *hxd2 = new TH1F("hxd2","hxd2",100,-2,2);
   TH1F *hyd1 = new TH1F("hyd1","hyd1",100,-2,2);
   TH1F *hyd2 = new TH1F("hyd2","hyd2",100,-2,2);

     
     TH2F *calo = new TH2F("calo","calo energy dep",5,0,15,5,0,15);
     TH2F *pos = new TH2F("pos","init pos",5,0,15,5,0,15);
     Int_t starter=1;
     
   //   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   for (Long64_t jentry=starter; jentry<starter+5;jentry++) {  
     cout<<"jentry is "<<jentry<<endl;
     Long64_t ientry = LoadTree(jentry);
     cout<<ientry<<endl;
     if (ientry < 0) break;
     cout<<"here"<<endl;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     inner=0;
     ring1=0;
     ring2=0;
     
     
     
     gStyle->SetPalette(1,0);
     
     
     
          
     
     TString a = "t.b";
     TString b;
     TString num;
     Double_t n;
     Double_t x;
     Double_t y;
     Double_t xpos;
     Double_t ypos;
     Double_t val;
     char word[3];
     //n=2;
     
     for(Int_t i = 0; i<25;i++){
       n=i;
       sprintf(word,"%03.0f",n);
       num=word;
       //cout<<num<<endl;
       //cout<<z<<endl;
       b=a+num;
       //cout<<b<<endl;
       
       x=3*(i%5)+1.5;
       y=3*((i-i%5)/5)+1.5;
       //cout<<"val is "<<val<<endl;
       gROOT->ProcessLineFast("val = "+b);
       //cout<<val<<endl;
       calo->Fill(x,y,val);
     }
     xpos = t.caloX+7.5;
     ypos = t.caloY+7.5;
     //cout<<"initX = "<<xpos<<", initY = "<<ypos<<endl;
     pos->Fill(xpos,ypos);
     cout<<"messX = "<<xpos<<", messY = "<<ypos<<endl;
     
         
   }
        calo->Draw("colz");
     pos->SetMarkerStyle(2);
     pos->SetMarkerColor(10);
     pos->Draw("same");
   ////////////////////////////3x3//////////////////////      
   /*

      ring2+=(t.b002+t.b003+t.b004+t.b005+t.b006+t.b007+t.b008+t.b009+t.b010+t.b011+t.b012+t.b013+t.b014+t.b015+t.b016+t.b022+t.b023+t.b024+t.b025+t.b026+t.b027+t.b028+t.b029+t.b030+t.b031+t.b032+t.b033+t.b034+t.b035+t.b036+t.b042+t.b043+t.b044+t.b045+t.b046+t.b047+t.b048+t.b049+t.b050+t.b051+t.b052+t.b053+t.b054+t.b055+t.b056);

      ring2+=(t.b062+t.b063+t.b064+t.b074+t.b075+t.b076+t.b082+t.b083+t.b084+t.b094+t.b095+t.b096+t.b102+t.b103+t.b104+t.b114+t.b115+t.b116+t.b122+t.b123+t.b124+t.b134+t.b135+t.b136+t.b142+t.b143+t.b144+t.b154+t.b155+t.b156+t.b162+t.b163+t.b164+t.b174+t.b175+t.b176+t.b182+t.b183+t.b184+t.b194+t.b195+t.b196+t.b202+t.b203+t.b204+t.b214+t.b215+t.b216+t.b222+t.b223+t.b224+t.b234+t.b235+t.b236);

      ring2+=(t.b242+t.b243+t.b244+t.b245+t.b246+t.b247+t.b248+t.b249+t.b250+t.b251+t.b252+t.b253+t.b254+t.b255+t.b256+t.b262+t.b263+t.b264+t.b265+t.b266+t.b267+t.b268+t.b269+t.b270+t.b271+t.b272+t.b273+t.b274+t.b275+t.b276+t.b282+t.b283+t.b284+t.b285+t.b286+t.b287+t.b288+t.b289+t.b290+t.b291+t.b292+t.b293+t.b294+t.b295+t.b296);


      ring1+=(t.b165+t.b166+t.b167+t.b145+t.b146+t.b147+t.b125+t.b126+t.b127+t.b171+t.b172+t.b173+t.b151+t.b152+t.b153+t.b131+t.b132+t.b133+t.b228+t.b229+t.b230+t.b208+t.b209+t.b210+t.b188+t.b189+t.b190+t.b108+t.b109+t.b110+t.b088+t.b089+t.b090+t.b068+t.b069+t.b070+t.b105+t.b106+t.b107+t.b085+t.b086+t.b087+t.b065+t.b066+t.b067);

      ring1+=(t.b225+t.b226+t.b227+t.b205+t.b206+t.b207+t.b185+t.b186+t.b187+t.b111+t.b112+t.b113+t.b091+t.b092+t.b093+t.b071+t.b072+t.b073+t.b231+t.b232+t.b233+t.b211+t.b212+t.b213+t.b191+t.b192+t.b193);

      inner+=(t.b149+t.b150+t.b148+t.b129+t.b169+t.b170+t.b168+t.b128+t.b130);


      
      xnum1 = (t.b149+t.b150+t.b148+t.b129+t.b169+t.b170+t.b168+t.b128+t.b130+t.b108+t.b109+t.b110+t.b088+t.b089+t.b090+t.b068+t.b069+t.b070+t.b228+t.b229+t.b230+t.b208+t.b209+t.b210+t.b188+t.b189+t.b190)*0+(t.b165+t.b166+t.b167+t.b145+t.b146+t.b147+t.b125+t.b126+t.b127+t.b225+t.b226+t.b227+t.b205+t.b206+t.b207+t.b185+t.b186+t.b187+t.b105+t.b106+t.b107+t.b085+t.b086+t.b087+t.b065+t.b066+t.b067)*-1+(t.b171+t.b172+t.b173+t.b151+t.b152+t.b153+t.b131+t.b132+t.b133+t.b111+t.b112+t.b113+t.b091+t.b092+t.b093+t.b071+t.b072+t.b073+t.b231+t.b232+t.b233+t.b211+t.b212+t.b213+t.b191+t.b192+t.b193)*1;






      xnum2 = (t.b008+t.b009+t.b010+t.b028+t.b029+t.b030+t.b048+t.b049+t.b050+t.b248+t.b249+t.b250+t.b268+t.b269+t.b270+t.b288+t.b289+t.b290)*0+(t.b011+t.b012+t.b013+t.b031+t.b032+t.b033+t.b051+t.b052+t.b053+t.b251+t.b252+t.b253+t.b271+t.b272+t.b273+t.b291+t.b292+t.b293)*1+(t.b005+t.b006+t.b007+t.b025+t.b026+t.b027+t.b045+t.b046+t.b047+t.b245+t.b246+t.b247+t.b265+t.b266+t.b267+t.b285+t.b286+t.b287)*-1;
      xnum2 +=(t.b014+t.b015+t.b016+t.b034+t.b035+t.b036+t.b054+t.b055+t.b056+t.b074+t.b075+t.b076+t.b094+t.b095+t.b096+t.b114+t.b115+t.b116+t.b134+t.b135+t.b136+t.b154+t.b155+t.b156+t.b174+t.b175+t.b176+t.b194+t.b195+t.b196+t.b214+t.b215+t.b216+t.b234+t.b235+t.b236+t.b254+t.b255+t.b256+t.b274+t.b275+t.b276+t.b294+t.b295+t.b296)*2+(t.b002+t.b003+t.b004+t.b022+t.b023+t.b024+t.b042+t.b043+t.b044+t.b062+t.b063+t.b064+t.b082+t.b083+t.b084+t.b102+t.b103+t.b104+t.b122+t.b123+t.b124+t.b142+t.b143+t.b144+t.b162+t.b163+t.b164+t.b182+t.b183+t.b184+t.b202+t.b203+t.b204+t.b222+t.b223+t.b224+t.b242+t.b243+t.b244+t.b262+t.b263+t.b264+t.b282+t.b283+t.b284)*-2;







      ynum1 = (t.b149+t.b150+t.b148+t.b129+t.b169+t.b170+t.b168+t.b128+t.b130+t.b165+t.b166+t.b167+t.b145+t.b146+t.b147+t.b125+t.b126+t.b127+t.b171+t.b172+t.b173+t.b151+t.b152+t.b153+t.b131+t.b132+t.b133)*0+(t.b105+t.b106+t.b107+t.b085+t.b086+t.b087+t.b065+t.b066+t.b067+t.b108+t.b109+t.b110+t.b088+t.b089+t.b090+t.b068+t.b069+t.b070+t.b111+t.b112+t.b113+t.b091+t.b092+t.b093+t.b071+t.b072+t.b073)*-1+(t.b225+t.b226+t.b227+t.b205+t.b206+t.b207+t.b185+t.b186+t.b187+t.b228+t.b229+t.b230+t.b208+t.b209+t.b210+t.b188+t.b189+t.b190+t.b231+t.b232+t.b233+t.b211+t.b212+t.b213+t.b191+t.b192+t.b193)*1;


      ynum2 = (t.b122+t.b123+t.b124+t.b134+t.b135+t.b136+t.b142+t.b143+t.b144+t.b154+t.b155+t.b156+t.b162+t.b163+t.b164+t.b174+t.b175+t.b176)*0+(t.b062+t.b063+t.b064+t.b074+t.b075+t.b076+t.b082+t.b083+t.b084+t.b094+t.b095+t.b096+t.b102+t.b103+t.b104+t.b114+t.b115+t.b116)*-1+(t.b182+t.b183+t.b184+t.b194+t.b195+t.b196+t.b202+t.b203+t.b204+t.b214+t.b215+t.b216+t.b222+t.b223+t.b224+t.b234+t.b235+t.b236)*1;


      ynum2+= (t.b002+t.b003+t.b004+t.b005+t.b006+t.b007+t.b008+t.b009+t.b010+t.b011+t.b012+t.b013+t.b014+t.b015+t.b016+t.b022+t.b023+t.b024+t.b025+t.b026+t.b027+t.b028+t.b029+t.b030+t.b031+t.b032+t.b033+t.b034+t.b035+t.b036+t.b042+t.b043+t.b044+t.b045+t.b046+t.b047+t.b048+t.b049+t.b050+t.b051+t.b052+t.b053+t.b054+t.b055+t.b056)*-2+(t.b242+t.b243+t.b244+t.b245+t.b246+t.b247+t.b248+t.b249+t.b250+t.b251+t.b252+t.b253+t.b254+t.b255+t.b256+t.b262+t.b263+t.b264+t.b265+t.b266+t.b267+t.b268+t.b269+t.b270+t.b271+t.b272+t.b273+t.b274+t.b275+t.b276+t.b282+t.b283+t.b284+t.b285+t.b286+t.b287+t.b288+t.b289+t.b290+t.b291+t.b292+t.b293+t.b294+t.b295+t.b296)*2;



*/

	//////////2x2/////////////
  /*
      xnum1 = (t.bEdep149+t.bEdep150+t.bEdep169+t.bEdep170+t.bEdep109+t.bEdep110+t.bEdep129+t.bEdep130+t.bEdep189+t.bEdep190+t.bEdep209+t.bEdep210)*0+(t.bEdep127+t.bEdep128+t.bEdep107+t.bEdep108+t.bEdep147+t.bEdep148+t.bEdep167+t.bEdep168+t.bEdep187+t.bEdep188+t.bEdep207+t.bEdep208)*-1+(t.bEdep111+t.bEdep112+t.bEdep131+t.bEdep132+t.bEdep151+t.bEdep152+t.bEdep171+t.bEdep172+t.bEdep191+t.bEdep192+t.bEdep211+t.bEdep212)*1;

      xnum2 = (t.bEdep069+t.bEdep070+t.bEdep089+t.bEdep090+t.bEdep229+t.bEdep230+t.bEdep249+t.bEdep250)*0+(t.bEdep071+t.bEdep072+t.bEdep091+t.bEdep092+t.bEdep231+t.bEdep232+t.bEdep251+t.bEdep252)*1+(t.bEdep067+t.bEdep068+t.bEdep087+t.bEdep088+t.bEdep227+t.bEdep228+t.bEdep247+t.bEdep248)*-1+(t.bEdep065+t.bEdep066+t.bEdep085+t.bEdep086+t.bEdep105+t.bEdep106+t.bEdep125+t.bEdep126+t.bEdep145+t.bEdep146+t.bEdep165+t.bEdep166+t.bEdep185+t.bEdep186+t.bEdep205+t.bEdep206+t.bEdep225+t.bEdep226+t.bEdep245+t.bEdep246)*-2+(t.bEdep073+t.bEdep074+t.bEdep093+t.bEdep094+t.bEdep113+t.bEdep114+t.bEdep133+t.bEdep134+t.bEdep153+t.bEdep154+t.bEdep173+t.bEdep174+t.bEdep193+t.bEdep194+t.bEdep213+t.bEdep214+t.bEdep233+t.bEdep234+t.bEdep253+t.bEdep254)*2;

      ynum1 = (t.bEdep149+t.bEdep150+t.bEdep169+t.bEdep170+t.bEdep147+t.bEdep148+t.bEdep167+t.bEdep168+t.bEdep151+t.bEdep152+t.bEdep171+t.bEdep172)*0+(t.bEdep127+t.bEdep128+t.bEdep107+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep129+t.bEdep130+t.bEdep111+t.bEdep112+t.bEdep131+t.bEdep132)*-1+(t.bEdep187+t.bEdep188+t.bEdep207+t.bEdep208+t.bEdep189+t.bEdep190+t.bEdep209+t.bEdep210+t.bEdep191+t.bEdep192+t.bEdep211+t.bEdep212)*1; 
     ynum2 = (t.bEdep145+t.bEdep146+t.bEdep165+t.bEdep166+t.bEdep153+t.bEdep154+t.bEdep173+t.bEdep174)*0+(t.bEdep105+t.bEdep106+t.bEdep125+t.bEdep126+t.bEdep113+t.bEdep114+t.bEdep133+t.bEdep134)*-1+(t.bEdep185+t.bEdep186+t.bEdep205+t.bEdep206+t.bEdep193+t.bEdep194+t.bEdep213+t.bEdep214)*1+(t.bEdep065+t.bEdep066+t.bEdep085+t.bEdep086+t.bEdep067+t.bEdep068+t.bEdep087+t.bEdep088+t.bEdep069+t.bEdep070+t.bEdep089+t.bEdep090+t.bEdep071+t.bEdep072+t.bEdep091+t.bEdep092+t.bEdep073+t.bEdep074+t.bEdep093+t.bEdep094)*-2+(t.bEdep225+t.bEdep226+t.bEdep245+t.bEdep246+t.bEdep233+t.bEdep234+t.bEdep253+t.bEdep254+t.bEdep227+t.bEdep228+t.bEdep247+t.bEdep248+t.bEdep229+t.bEdep230+t.bEdep249+t.bEdep250+t.bEdep231+t.bEdep232+t.bEdep251+t.bEdep252)*2;

	//+t.bEdep+t.bEdep+t.bEdep+t.bEdep+t.bEdep+
      
      
         
      
      inner+=(t.bEdep149+t.bEdep150+t.bEdep169+t.bEdep170);
      ring1+=(t.bEdep127+t.bEdep128+t.bEdep107+t.bEdep108+t.bEdep147+t.bEdep148+t.bEdep167+t.bEdep168+t.bEdep187+t.bEdep188+t.bEdep207+t.bEdep208+t.bEdep109+t.bEdep110+t.bEdep129+t.bEdep130+t.bEdep189+t.bEdep190+t.bEdep209+t.bEdep210+t.bEdep111+t.bEdep112+t.bEdep131+t.bEdep132+t.bEdep151+t.bEdep152+t.bEdep171+t.bEdep172+t.bEdep191+t.bEdep192+t.bEdep211+t.bEdep212);
      ring2+=(t.bEdep065+t.bEdep066+t.bEdep085+t.bEdep086+t.bEdep105+t.bEdep106+t.bEdep125+t.bEdep126+t.bEdep145+t.bEdep146+t.bEdep165+t.bEdep166+t.bEdep185+t.bEdep186+t.bEdep205+t.bEdep206+t.bEdep225+t.bEdep226+t.bEdep245+t.bEdep246+t.bEdep073+t.bEdep074+t.bEdep093+t.bEdep094+t.bEdep113+t.bEdep114+t.bEdep133+t.bEdep134+t.bEdep153+t.bEdep154+t.bEdep173+t.bEdep174+t.bEdep193+t.bEdep194+t.bEdep213+t.bEdep214+t.bEdep233+t.bEdep234+t.bEdep253+t.bEdep254+t.bEdep067+t.bEdep068+t.bEdep087+t.bEdep088+t.bEdep227+t.bEdep228+t.bEdep247+t.bEdep248+t.bEdep069+t.bEdep070+t.bEdep089+t.bEdep090+t.bEdep229+t.bEdep230+t.bEdep249+t.bEdep250+t.bEdep071+t.bEdep072+t.bEdep091+t.bEdep092+t.bEdep231+t.bEdep232+t.bEdep251+t.bEdep252);
      
  */      

      ////////////////////1x1//////////////


      /*
    
      xnum1 = (t.b169+t.b149+t.b129)*0+(t.b128+t.b148+t.b168)*-1+(t.b130+t.b150+t.b170)*1;
      xnum2 = (t.b189+t.b109)*0+(t.b190+t.b110)*1+(t.b188+t.b108)*-1+(t.b107+t.b127+t.b147+t.b187+t.b167)*-2+(t.b111+t.b131+t.b151+t.b171+t.b191)*2;
      ynum1 = (t.b148+t.b149+t.b150)*0+(t.b128+t.b129+t.b130)*-1+(t.b168+t.b169+t.b170)*1;
      ynum2 = (t.b147+t.b151)*0+(t.b127+t.b131)*-1+(t.b167+t.b171)*1+(t.b107+t.b108+t.b109+t.b110+t.b111)*-2+(t.b187+t.b188+t.b189+t.b190+t.b191)*2;



      

	//+t.b+t.b+t.b+t.b+t.b+
      
      
         
      
      inner+=t.b149;
      ring1+=(t.b150+t.b148+t.b129+t.b169+t.b170+t.b168+t.b128+t.b130);
      ring2+=(t.b107+t.b108+t.b109+t.b110+t.b111+t.b187+t.b188+t.b189+t.b190+t.b191+t.b167+t.b171+t.b147+t.b151+t.b127+t.b131);
      
      */





  /*









      den1 = inner+ring1;
      den2 = den1+ring2;

      xpos1 = xnum1/den1;
      xpos2 = (xnum1+xnum2)/den2;
      ypos1 = ynum1/den1;
      ypos2 = (ynum1+ynum2)/den2;
      xd1=xpos1-t.initX;
      xd2=xpos2-t.initX;
      yd1=ypos1-t.initY+0.5;
      yd2=ypos2-t.initY+0.5;



      if(jentry%10==0)
	cout<<"entry "<<jentry<<endl;
      hi->Fill(inner);
      h1->Fill(ring1);
      h2->Fill(ring2);

      hx->Fill(t.initX);
      hy->Fill(t.initY);


      hxp1->Fill(xpos1);
      hxp2->Fill(xpos2);
      hyp1->Fill(ypos1);
      hyp2->Fill(ypos2);

      hxd1->Fill(xd1);
      hxd2->Fill(xd2);
      hyd1->Fill(yd1);
      hyd2->Fill(yd2);


   }

   h2->Draw();
   h1->Draw("same");
   hi->Draw("same");
  */
}

