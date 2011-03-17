#define aclass_cxx
#include "aclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void aclass::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L aclass.C
//      Root > aclass t
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
     TH2F *calo = new TH2F("calo","calo energy dep",5,0,15,5,0,15);
     TH2F *pos = new TH2F("pos","init pos",5,0,15,5,0,15);
     Int_t starter=1;
   Long64_t nentries = fChain->GetEntriesFast();
   cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

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
   
   
   
}
