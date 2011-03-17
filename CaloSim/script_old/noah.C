#define noah_cxx
#include "noah.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void noah::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L noah.C
//      Root > noah t
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
      calo->GetZaxis()->SetRangeUser(0,2000);
      calo->GetXaxis()->SetTitle("Xpos (cm)");
      calo->GetYaxis()->SetTitle("Ypos (cm)");
      gStyle->SetPalette(1,0);
   Long64_t nentries = fChain->GetEntriesFast();
   cout<<nentries<<endl;
   Double_t val;
   Long64_t ent = 2054;
   cout<<"give me entry  number"<<endl;
   cin>>ent;

   Long64_t nbytes = 0, nb = 0;

     cout<<"HERE"<<endl;
   for (Long64_t jentry=ent; jentry<ent+1;jentry++) {
     cout<<"HERE"<<endl;
     cout<<jentry<<endl;
      Long64_t ientry = LoadTree(jentry);
      cout<<ientry<<endl;
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
    
      gROOT->ProcessLineFast("val = t.ADC_1E");
      calo->Fill(1.5,1.5,val);
      gROOT->ProcessLineFast("val = t.ADC_1W");
      calo->Fill(4.5,1.5,val);
      gROOT->ProcessLineFast("val = t.ADC_2E");
      calo->Fill(7.5,1.5,val);
      gROOT->ProcessLineFast("val = t.ADC_2W");
      calo->Fill(10.5,1.5,val);
      gROOT->ProcessLineFast("val = t.ADC_3E");
      calo->Fill(13.5,1.5,val);


      gROOT->ProcessLineFast("val = t.ADC_3W");
      calo->Fill(1.5,4.5,val);
      gROOT->ProcessLineFast("val = t.ADC_4E");
      calo->Fill(4.5,4.5,val);
      gROOT->ProcessLineFast("val = t.ADC_4W");
      calo->Fill(7.5,4.5,val);
      gROOT->ProcessLineFast("val = t.ADC_5E");
      calo->Fill(10.5,4.5,val);
      gROOT->ProcessLineFast("val = t.ADC_5W");
      calo->Fill(13.5,4.5,val);


      gROOT->ProcessLineFast("val = t.ADC_6E");
      calo->Fill(1.5,7.5,val);
      gROOT->ProcessLineFast("val = t.ADC_6W");
      calo->Fill(4.5,7.5,val);
      gROOT->ProcessLineFast("val = t.ADC_7E");
      calo->Fill(7.5,7.5,val);
      gROOT->ProcessLineFast("val = t.ADC_7W");
      calo->Fill(10.5,7.5,val);
      gROOT->ProcessLineFast("val = t.ADC_8E");
      calo->Fill(13.5,7.5,val);


      gROOT->ProcessLineFast("val = t.ADC_8W");
      calo->Fill(1.5,10.5,val);
      gROOT->ProcessLineFast("val = t.ADC_9E");
      calo->Fill(7.5,10.5,val);
      gROOT->ProcessLineFast("val = t.ADC_9W");
      calo->Fill(10.5,10.5,val);      
      gROOT->ProcessLineFast("val = t.ADC_10E");
      calo->Fill(13.5,10.5,val);


      gROOT->ProcessLineFast("val = t.ADC_10W");
      calo->Fill(1.5,13.5,val);
      gROOT->ProcessLineFast("val = t.ADC_11E");
      calo->Fill(4.5,13.5,val);
      gROOT->ProcessLineFast("val = t.ADC_11W");
      calo->Fill(7.5,13.5,val);
      gROOT->ProcessLineFast("val = t.ADC_12E");
      calo->Fill(10.5,13.5,val);
      gROOT->ProcessLineFast("val = t.ADC_12W");
      calo->Fill(13.5,13.5,val);      

           
      calo->Draw("colz");
      
      
   }
}
