#define myclass_cxx
#include "myclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void myclass::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L myclass.C
//      Root > myclass t
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
   //TString a = "t.bEdep";
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


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      inner=0;
      ring1=0;
      ring2=0;
   
      
      


/*
for(Int_t i=0;i<300;i++){

sprintf(word,"%03.0f",i);
num=word;


if(((i-2)%20<15&&i>1&&i<297)&&(!((i-5)%20<9&&i>64&&i<234))){
e = c2+a+num+";";
gROOT->ProcessLineFast(e);
} else 	if(((i-5)%20<9&&i>64&&i<234)&&(!((i-8)%20<3&&i>127&&i<171))){
e = c1+a+num+";";
gROOT->ProcessLineFast(e);
} else 	if((i-8)%20<3&&i>127&&i<171){
e = ci+a+num+";";
gROOT->ProcessLineFast(e);

}




}


*/



      ring2+=(t.bEdep002+t.bEdep003+t.bEdep004+t.bEdep005+t.bEdep006+t.bEdep007+t.bEdep008+t.bEdep009+t.bEdep010+t.bEdep011+t.bEdep012+t.bEdep013+t.bEdep014+t.bEdep015+t.bEdep016+t.bEdep022+t.bEdep023+t.bEdep024+t.bEdep025+t.bEdep026+t.bEdep027+t.bEdep028+t.bEdep029+t.bEdep030+t.bEdep031+t.bEdep032+t.bEdep033+t.bEdep034+t.bEdep035+t.bEdep036+t.bEdep042+t.bEdep043+t.bEdep044+t.bEdep045+t.bEdep046+t.bEdep047+t.bEdep048+t.bEdep049+t.bEdep050+t.bEdep051+t.bEdep052+t.bEdep053+t.bEdep054+t.bEdep055+t.bEdep056);

      ring2+=(t.bEdep062+t.bEdep063+t.bEdep064+t.bEdep074+t.bEdep075+t.bEdep076+t.bEdep082+t.bEdep083+t.bEdep084+t.bEdep094+t.bEdep095+t.bEdep096+t.bEdep102+t.bEdep103+t.bEdep104+t.bEdep114+t.bEdep115+t.bEdep116+t.bEdep122+t.bEdep123+t.bEdep124+t.bEdep134+t.bEdep135+t.bEdep136+t.bEdep142+t.bEdep143+t.bEdep144+t.bEdep154+t.bEdep155+t.bEdep156+t.bEdep162+t.bEdep163+t.bEdep164+t.bEdep174+t.bEdep175+t.bEdep176+t.bEdep182+t.bEdep183+t.bEdep184+t.bEdep194+t.bEdep195+t.bEdep196+t.bEdep202+t.bEdep203+t.bEdep204+t.bEdep214+t.bEdep215+t.bEdep216+t.bEdep222+t.bEdep223+t.bEdep224+t.bEdep234+t.bEdep235+t.bEdep236);

      ring2+=(t.bEdep242+t.bEdep243+t.bEdep244+t.bEdep245+t.bEdep246+t.bEdep247+t.bEdep248+t.bEdep249+t.bEdep250+t.bEdep251+t.bEdep252+t.bEdep253+t.bEdep254+t.bEdep255+t.bEdep256+t.bEdep262+t.bEdep263+t.bEdep264+t.bEdep265+t.bEdep266+t.bEdep267+t.bEdep268+t.bEdep269+t.bEdep270+t.bEdep271+t.bEdep272+t.bEdep273+t.bEdep274+t.bEdep275+t.bEdep276+t.bEdep282+t.bEdep283+t.bEdep284+t.bEdep285+t.bEdep286+t.bEdep287+t.bEdep288+t.bEdep289+t.bEdep290+t.bEdep291+t.bEdep292+t.bEdep293+t.bEdep294+t.bEdep295+t.bEdep296);


      ring1+=(t.bEdep165+t.bEdep166+t.bEdep167+t.bEdep145+t.bEdep146+t.bEdep147+t.bEdep125+t.bEdep126+t.bEdep127+t.bEdep171+t.bEdep172+t.bEdep173+t.bEdep151+t.bEdep152+t.bEdep153+t.bEdep131+t.bEdep132+t.bEdep133+t.bEdep228+t.bEdep229+t.bEdep230+t.bEdep208+t.bEdep209+t.bEdep210+t.bEdep188+t.bEdep189+t.bEdep190+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep088+t.bEdep089+t.bEdep090+t.bEdep068+t.bEdep069+t.bEdep070+t.bEdep105+t.bEdep106+t.bEdep107+t.bEdep085+t.bEdep086+t.bEdep087+t.bEdep065+t.bEdep066+t.bEdep067);

      ring1+=(t.bEdep225+t.bEdep226+t.bEdep227+t.bEdep205+t.bEdep206+t.bEdep207+t.bEdep185+t.bEdep186+t.bEdep187+t.bEdep111+t.bEdep112+t.bEdep113+t.bEdep091+t.bEdep092+t.bEdep093+t.bEdep071+t.bEdep072+t.bEdep073+t.bEdep231+t.bEdep232+t.bEdep233+t.bEdep211+t.bEdep212+t.bEdep213+t.bEdep191+t.bEdep192+t.bEdep193);

      inner+=(t.bEdep149+t.bEdep150+t.bEdep148+t.bEdep129+t.bEdep169+t.bEdep170+t.bEdep168+t.bEdep128+t.bEdep130);


      
      xnum1 = (t.bEdep149+t.bEdep150+t.bEdep148+t.bEdep129+t.bEdep169+t.bEdep170+t.bEdep168+t.bEdep128+t.bEdep130+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep088+t.bEdep089+t.bEdep090+t.bEdep068+t.bEdep069+t.bEdep070+t.bEdep228+t.bEdep229+t.bEdep230+t.bEdep208+t.bEdep209+t.bEdep210+t.bEdep188+t.bEdep189+t.bEdep190)*0+(t.bEdep165+t.bEdep166+t.bEdep167+t.bEdep145+t.bEdep146+t.bEdep147+t.bEdep125+t.bEdep126+t.bEdep127+t.bEdep225+t.bEdep226+t.bEdep227+t.bEdep205+t.bEdep206+t.bEdep207+t.bEdep185+t.bEdep186+t.bEdep187+t.bEdep105+t.bEdep106+t.bEdep107+t.bEdep085+t.bEdep086+t.bEdep087+t.bEdep065+t.bEdep066+t.bEdep067)*-1+(t.bEdep171+t.bEdep172+t.bEdep173+t.bEdep151+t.bEdep152+t.bEdep153+t.bEdep131+t.bEdep132+t.bEdep133+t.bEdep111+t.bEdep112+t.bEdep113+t.bEdep091+t.bEdep092+t.bEdep093+t.bEdep071+t.bEdep072+t.bEdep073+t.bEdep231+t.bEdep232+t.bEdep233+t.bEdep211+t.bEdep212+t.bEdep213+t.bEdep191+t.bEdep192+t.bEdep193)*1;


      xnum2 = 
(t.bEdep008+t.bEdep009+t.bEdep010+t.bEdep028+t.bEdep029+t.bEdep030+t.bEdep048+t.bEdep049+t.bEdep050+t.bEdep248+t.bEdep249+t.bEdep250+t.bEdep268+t.bEdep269+t.bEdep270+t.bEdep288+t.bEdep289+t.bEdep290)*0+
(t.bEdep011+t.bEdep012+t.bEdep013+t.bEdep031+t.bEdep032+t.bEdep033+t.bEdep051+t.bEdep052+t.bEdep053+t.bEdep251+t.bEdep252+t.bEdep253+t.bEdep271+t.bEdep272+t.bEdep273+t.bEdep291+t.bEdep292+t.bEdep293)*1+
(t.bEdep005+t.bEdep006+t.bEdep007+t.bEdep025+t.bEdep026+t.bEdep027+t.bEdep045+t.bEdep046+t.bEdep047+t.bEdep245+t.bEdep246+t.bEdep247+t.bEdep265+t.bEdep266+t.bEdep267+t.bEdep285+t.bEdep286+t.bEdep287)*-1;

      xnum2 +=(t.bEdep014+t.bEdep015+t.bEdep016+t.bEdep034+t.bEdep035+t.bEdep036+t.bEdep054+t.bEdep055+t.bEdep056+t.bEdep074+t.bEdep075+t.bEdep076+t.bEdep094+t.bEdep095+t.bEdep096+t.bEdep114+t.bEdep115+t.bEdep116+t.bEdep134+t.bEdep135+t.bEdep136+t.bEdep154+t.bEdep155+t.bEdep156+t.bEdep174+t.bEdep175+t.bEdep176+t.bEdep194+t.bEdep195+t.bEdep196+t.bEdep214+t.bEdep215+t.bEdep216+t.bEdep234+t.bEdep235+t.bEdep236+t.bEdep254+t.bEdep255+t.bEdep256+t.bEdep274+t.bEdep275+t.bEdep276+t.bEdep294+t.bEdep295+t.bEdep296)*2+(t.bEdep002+t.bEdep003+t.bEdep004+t.bEdep022+t.bEdep023+t.bEdep024+t.bEdep042+t.bEdep043+t.bEdep044+t.bEdep062+t.bEdep063+t.bEdep064+t.bEdep082+t.bEdep083+t.bEdep084+t.bEdep102+t.bEdep103+t.bEdep104+t.bEdep122+t.bEdep123+t.bEdep124+t.bEdep142+t.bEdep143+t.bEdep144+t.bEdep162+t.bEdep163+t.bEdep164+t.bEdep182+t.bEdep183+t.bEdep184+t.bEdep202+t.bEdep203+t.bEdep204+t.bEdep222+t.bEdep223+t.bEdep224+t.bEdep242+t.bEdep243+t.bEdep244+t.bEdep262+t.bEdep263+t.bEdep264+t.bEdep282+t.bEdep283+t.bEdep284)*-2;





      ynum1 = (t.bEdep149+t.bEdep150+t.bEdep148+t.bEdep129+t.bEdep169+t.bEdep170+t.bEdep168+t.bEdep128+t.bEdep130+t.bEdep165+t.bEdep166+t.bEdep167+t.bEdep145+t.bEdep146+t.bEdep147+t.bEdep125+t.bEdep126+t.bEdep127+t.bEdep171+t.bEdep172+t.bEdep173+t.bEdep151+t.bEdep152+t.bEdep153+t.bEdep131+t.bEdep132+t.bEdep133)*0+(t.bEdep105+t.bEdep106+t.bEdep107+t.bEdep085+t.bEdep086+t.bEdep087+t.bEdep065+t.bEdep066+t.bEdep067+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep088+t.bEdep089+t.bEdep090+t.bEdep068+t.bEdep069+t.bEdep070+t.bEdep111+t.bEdep112+t.bEdep113+t.bEdep091+t.bEdep092+t.bEdep093+t.bEdep071+t.bEdep072+t.bEdep073)*-1+(t.bEdep225+t.bEdep226+t.bEdep227+t.bEdep205+t.bEdep206+t.bEdep207+t.bEdep185+t.bEdep186+t.bEdep187+t.bEdep228+t.bEdep229+t.bEdep230+t.bEdep208+t.bEdep209+t.bEdep210+t.bEdep188+t.bEdep189+t.bEdep190+t.bEdep231+t.bEdep232+t.bEdep233+t.bEdep211+t.bEdep212+t.bEdep213+t.bEdep191+t.bEdep192+t.bEdep193)*1;

      ynum2 = (t.bEdep122+t.bEdep123+t.bEdep124+t.bEdep134+t.bEdep135+t.bEdep136+t.bEdep142+t.bEdep143+t.bEdep144+t.bEdep154+t.bEdep155+t.bEdep156+t.bEdep162+t.bEdep163+t.bEdep164+t.bEdep174+t.bEdep175+t.bEdep176)*0+(t.bEdep062+t.bEdep063+t.bEdep064+t.bEdep074+t.bEdep075+t.bEdep076+t.bEdep082+t.bEdep083+t.bEdep084+t.bEdep094+t.bEdep095+t.bEdep096+t.bEdep102+t.bEdep103+t.bEdep104+t.bEdep114+t.bEdep115+t.bEdep116)*-1+(t.bEdep182+t.bEdep183+t.bEdep184+t.bEdep194+t.bEdep195+t.bEdep196+t.bEdep202+t.bEdep203+t.bEdep204+t.bEdep214+t.bEdep215+t.bEdep216+t.bEdep222+t.bEdep223+t.bEdep224+t.bEdep234+t.bEdep235+t.bEdep236)*1;

      ynum2+= (t.bEdep002+t.bEdep003+t.bEdep004+t.bEdep005+t.bEdep006+t.bEdep007+t.bEdep008+t.bEdep009+t.bEdep010+t.bEdep011+t.bEdep012+t.bEdep013+t.bEdep014+t.bEdep015+t.bEdep016+t.bEdep022+t.bEdep023+t.bEdep024+t.bEdep025+t.bEdep026+t.bEdep027+t.bEdep028+t.bEdep029+t.bEdep030+t.bEdep031+t.bEdep032+t.bEdep033+t.bEdep034+t.bEdep035+t.bEdep036+t.bEdep042+t.bEdep043+t.bEdep044+t.bEdep045+t.bEdep046+t.bEdep047+t.bEdep048+t.bEdep049+t.bEdep050+t.bEdep051+t.bEdep052+t.bEdep053+t.bEdep054+t.bEdep055+t.bEdep056)*-2+(t.bEdep242+t.bEdep243+t.bEdep244+t.bEdep245+t.bEdep246+t.bEdep247+t.bEdep248+t.bEdep249+t.bEdep250+t.bEdep251+t.bEdep252+t.bEdep253+t.bEdep254+t.bEdep255+t.bEdep256+t.bEdep262+t.bEdep263+t.bEdep264+t.bEdep265+t.bEdep266+t.bEdep267+t.bEdep268+t.bEdep269+t.bEdep270+t.bEdep271+t.bEdep272+t.bEdep273+t.bEdep274+t.bEdep275+t.bEdep276+t.bEdep282+t.bEdep283+t.bEdep284+t.bEdep285+t.bEdep286+t.bEdep287+t.bEdep288+t.bEdep289+t.bEdep290+t.bEdep291+t.bEdep292+t.bEdep293+t.bEdep294+t.bEdep295+t.bEdep296)*2;





/*
  
    
      xnum1 = (t.bEdep169+t.bEdep149+t.bEdep129)*0+(t.bEdep128+t.bEdep148+t.bEdep168)*-1+(t.bEdep130+t.bEdep150+t.bEdep170)*1;
      xnum2 = (t.bEdep189+t.bEdep109)*0+(t.bEdep190+t.bEdep110)*1+(t.bEdep188+t.bEdep108)*-1+(t.bEdep107+t.bEdep127+t.bEdep147+t.bEdep187+t.bEdep167)*-2+(t.bEdep111+t.bEdep131+t.bEdep151+t.bEdep171+t.bEdep191)*2;
      ynum1 = (t.bEdep148+t.bEdep149+t.bEdep150)*0+(t.bEdep128+t.bEdep129+t.bEdep130)*-1+(t.bEdep168+t.bEdep169+t.bEdep170)*1;
      ynum2 = (t.bEdep147+t.bEdep151)*0+(t.bEdep127+t.bEdep131)*-1+(t.bEdep167+t.bEdep171)*1+(t.bEdep107+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep111)*-2+(t.bEdep187+t.bEdep188+t.bEdep189+t.bEdep190+t.bEdep191)*2;



      

	//+t.bEdep+t.bEdep+t.bEdep+t.bEdep+t.bEdep+
      
      
         
      
      inner+=t.bEdep149;
      ring1+=(t.bEdep150+t.bEdep148+t.bEdep129+t.bEdep169+t.bEdep170+t.bEdep168+t.bEdep128+t.bEdep130);
      ring2+=(t.bEdep107+t.bEdep108+t.bEdep109+t.bEdep110+t.bEdep111+t.bEdep187+t.bEdep188+t.bEdep189+t.bEdep190+t.bEdep191+t.bEdep167+t.bEdep171+t.bEdep147+t.bEdep151+t.bEdep127+t.bEdep131);
      
      
*/














      den1 = inner+ring1;
      den2 = den1+ring2;

      xpos1 = xnum1/den1;
      xpos2 = (xnum1+xnum2)/den2;
      ypos1 = ynum1/den1;
      ypos2 = (ynum1+ynum2)/den2;
      xd1=xpos1-t.initX-0.5;
      xd2=xpos2-t.initX-0.5;
      yd1=ypos1-t.initY;
      yd2=ypos2-t.initY;



      if(jentry%1000==0)
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
}

