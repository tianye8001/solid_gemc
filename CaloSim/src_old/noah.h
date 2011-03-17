//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat May 15 14:27:02 2010 by ROOT version 5.18/00
// from TTree MuLife/MuLife
// found on file: noah.root
//////////////////////////////////////////////////////////

#ifndef noah_h
#define noah_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class noah {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           TDC_fast_2E;
   Int_t           TDC_fast_2W;
   Int_t           TDC_fast_3E;
   Int_t           TDC_fast_3W;
   Int_t           TDC_fast_4E;
   Int_t           TDC_fast_4W;
   Int_t           TDC_fast_Dummy3;
   Int_t           TDC_fast_Dummy4;
   Int_t           SLOW_3;
   Int_t           SLOW_4;
   Int_t           SLOW_5;
   Int_t           SLOW_6;
   Int_t           SLOW_7;
   Int_t           SLOW_8;
   Int_t           SLOW_9;
   Int_t           SLOW_10;
   Int_t           SLOW_11;
   Int_t           SLOW_12;
   Int_t           SLOW_1;
   Int_t           SLOW_2;
   Int_t           SLOW_13;
   Int_t           SLOW_14;
   Int_t           TDCSUM;
   Int_t           STOP_DET;
   Int_t           LAYER_N;
   Int_t           L1_UP;
   Int_t           L1_DOWN;
   Int_t           L2_UP;
   Int_t           L2_DOWN;
   Int_t           L3_UP;
   Int_t           L3_DOWN;
   Int_t           L4_UP;
   Int_t           L4_DOWN;
   Int_t           UP;
   Int_t           DOWN;
   Float_t         Z2;
   Float_t         Z3;
   Float_t         Z4;
   Float_t         Z_23;
   Float_t         Z_24;
   Float_t         Z_all;
   Int_t           ADC_1E;
   Int_t           ADC_1W;
   Int_t           ADC_2E;
   Int_t           ADC_2W;
   Int_t           ADC_3E;
   Int_t           ADC_3W;
   Int_t           ADC_4E;
   Int_t           ADC_4W;
   Int_t           ADC_5E;
   Int_t           ADC_5W;
   Int_t           ADC_6E;
   Int_t           ADC_6W;
   Int_t           ADC_7E;
   Int_t           ADC_7W;
   Int_t           ADC_8E;
   Int_t           ADC_8W;
   Int_t           ADC_9E;
   Int_t           ADC_9W;
   Int_t           ADC_10E;
   Int_t           ADC_10W;
   Int_t           ADC_11E;
   Int_t           ADC_11W;
   Int_t           ADC_12E;
   Int_t           ADC_12W;

   // List of branches
   TBranch        *b_TDC_fast_2E;   //!
   TBranch        *b_TDC_fast_2W;   //!
   TBranch        *b_TDC_fast_3E;   //!
   TBranch        *b_TDC_fast_3W;   //!
   TBranch        *b_TDC_fast_4E;   //!
   TBranch        *b_TDC_fast_4W;   //!
   TBranch        *b_TDC_fast_Dummy3;   //!
   TBranch        *b_TDC_fast_Dummy4;   //!
   TBranch        *b_SLOW_3;   //!
   TBranch        *b_SLOW_4;   //!
   TBranch        *b_SLOW_5;   //!
   TBranch        *b_SLOW_6;   //!
   TBranch        *b_SLOW_7;   //!
   TBranch        *b_SLOW_8;   //!
   TBranch        *b_SLOW_9;   //!
   TBranch        *b_SLOW_10;   //!
   TBranch        *b_SLOW_11;   //!
   TBranch        *b_SLOW_12;   //!
   TBranch        *b_SLOW_1;   //!
   TBranch        *b_SLOW_2;   //!
   TBranch        *b_SLOW_13;   //!
   TBranch        *b_SLOW_14;   //!
   TBranch        *b_TDCSUM;   //!
   TBranch        *b_STOP_DET;   //!
   TBranch        *b_LAYER_N;   //!
   TBranch        *b_L1_UP;   //!
   TBranch        *b_L1_DOWN;   //!
   TBranch        *b_L2_UP;   //!
   TBranch        *b_L2_DOWN;   //!
   TBranch        *b_L3_UP;   //!
   TBranch        *b_L3_DOWN;   //!
   TBranch        *b_L4_UP;   //!
   TBranch        *b_L4_DOWN;   //!
   TBranch        *b_UP;   //!
   TBranch        *b_DOWN;   //!
   TBranch        *b_Z2;   //!
   TBranch        *b_Z3;   //!
   TBranch        *b_Z4;   //!
   TBranch        *b_Z_23;   //!
   TBranch        *b_Z_24;   //!
   TBranch        *b_Z_all;   //!
   TBranch        *b_ADC_1E;   //!
   TBranch        *b_ADC_1W;   //!
   TBranch        *b_ADC_2E;   //!
   TBranch        *b_ADC_2W;   //!
   TBranch        *b_ADC_3E;   //!
   TBranch        *b_ADC_3W;   //!
   TBranch        *b_ADC_4E;   //!
   TBranch        *b_ADC_4W;   //!
   TBranch        *b_ADC_5E;   //!
   TBranch        *b_ADC_5W;   //!
   TBranch        *b_ADC_6E;   //!
   TBranch        *b_ADC_6W;   //!
   TBranch        *b_ADC_7E;   //!
   TBranch        *b_ADC_7W;   //!
   TBranch        *b_ADC_8E;   //!
   TBranch        *b_ADC_8W;   //!
   TBranch        *b_ADC_9E;   //!
   TBranch        *b_ADC_9W;   //!
   TBranch        *b_ADC_10E;   //!
   TBranch        *b_ADC_10W;   //!
   TBranch        *b_ADC_11E;   //!
   TBranch        *b_ADC_11W;   //!
   TBranch        *b_ADC_12E;   //!
   TBranch        *b_ADC_12W;   //!

   noah(TTree *tree=0);
   virtual ~noah();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef noah_cxx
noah::noah(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("noah.root");
      if (!f) {
         f = new TFile("noah.root");
      }
      tree = (TTree*)gDirectory->Get("MuLife");

   }
   Init(tree);
}

noah::~noah()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t noah::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t noah::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void noah::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("TDC_fast_2E", &TDC_fast_2E, &b_TDC_fast_2E);
   fChain->SetBranchAddress("TDC_fast_2W", &TDC_fast_2W, &b_TDC_fast_2W);
   fChain->SetBranchAddress("TDC_fast_3E", &TDC_fast_3E, &b_TDC_fast_3E);
   fChain->SetBranchAddress("TDC_fast_3W", &TDC_fast_3W, &b_TDC_fast_3W);
   fChain->SetBranchAddress("TDC_fast_4E", &TDC_fast_4E, &b_TDC_fast_4E);
   fChain->SetBranchAddress("TDC_fast_4W", &TDC_fast_4W, &b_TDC_fast_4W);
   fChain->SetBranchAddress("TDC_fast_Dummy3", &TDC_fast_Dummy3, &b_TDC_fast_Dummy3);
   fChain->SetBranchAddress("TDC_fast_Dummy4", &TDC_fast_Dummy4, &b_TDC_fast_Dummy4);
   fChain->SetBranchAddress("SLOW_3", &SLOW_3, &b_SLOW_3);
   fChain->SetBranchAddress("SLOW_4", &SLOW_4, &b_SLOW_4);
   fChain->SetBranchAddress("SLOW_5", &SLOW_5, &b_SLOW_5);
   fChain->SetBranchAddress("SLOW_6", &SLOW_6, &b_SLOW_6);
   fChain->SetBranchAddress("SLOW_7", &SLOW_7, &b_SLOW_7);
   fChain->SetBranchAddress("SLOW_8", &SLOW_8, &b_SLOW_8);
   fChain->SetBranchAddress("SLOW_9", &SLOW_9, &b_SLOW_9);
   fChain->SetBranchAddress("SLOW_10", &SLOW_10, &b_SLOW_10);
   fChain->SetBranchAddress("SLOW_11", &SLOW_11, &b_SLOW_11);
   fChain->SetBranchAddress("SLOW_12", &SLOW_12, &b_SLOW_12);
   fChain->SetBranchAddress("SLOW_1", &SLOW_1, &b_SLOW_1);
   fChain->SetBranchAddress("SLOW_2", &SLOW_2, &b_SLOW_2);
   fChain->SetBranchAddress("SLOW_13", &SLOW_13, &b_SLOW_13);
   fChain->SetBranchAddress("SLOW_14", &SLOW_14, &b_SLOW_14);
   fChain->SetBranchAddress("TDCSUM", &TDCSUM, &b_TDCSUM);
   fChain->SetBranchAddress("STOP_DET", &STOP_DET, &b_STOP_DET);
   fChain->SetBranchAddress("LAYER_N", &LAYER_N, &b_LAYER_N);
   fChain->SetBranchAddress("L1_UP", &L1_UP, &b_L1_UP);
   fChain->SetBranchAddress("L1_DOWN", &L1_DOWN, &b_L1_DOWN);
   fChain->SetBranchAddress("L2_UP", &L2_UP, &b_L2_UP);
   fChain->SetBranchAddress("L2_DOWN", &L2_DOWN, &b_L2_DOWN);
   fChain->SetBranchAddress("L3_UP", &L3_UP, &b_L3_UP);
   fChain->SetBranchAddress("L3_DOWN", &L3_DOWN, &b_L3_DOWN);
   fChain->SetBranchAddress("L4_UP", &L4_UP, &b_L4_UP);
   fChain->SetBranchAddress("L4_DOWN", &L4_DOWN, &b_L4_DOWN);
   fChain->SetBranchAddress("UP", &UP, &b_UP);
   fChain->SetBranchAddress("DOWN", &DOWN, &b_DOWN);
   fChain->SetBranchAddress("Z2", &Z2, &b_Z2);
   fChain->SetBranchAddress("Z3", &Z3, &b_Z3);
   fChain->SetBranchAddress("Z4", &Z4, &b_Z4);
   fChain->SetBranchAddress("Z_23", &Z_23, &b_Z_23);
   fChain->SetBranchAddress("Z_24", &Z_24, &b_Z_24);
   fChain->SetBranchAddress("Z_all", &Z_all, &b_Z_all);
   fChain->SetBranchAddress("ADC_1E", &ADC_1E, &b_ADC_1E);
   fChain->SetBranchAddress("ADC_1W", &ADC_1W, &b_ADC_1W);
   fChain->SetBranchAddress("ADC_2E", &ADC_2E, &b_ADC_2E);
   fChain->SetBranchAddress("ADC_2W", &ADC_2W, &b_ADC_2W);
   fChain->SetBranchAddress("ADC_3E", &ADC_3E, &b_ADC_3E);
   fChain->SetBranchAddress("ADC_3W", &ADC_3W, &b_ADC_3W);
   fChain->SetBranchAddress("ADC_4E", &ADC_4E, &b_ADC_4E);
   fChain->SetBranchAddress("ADC_4W", &ADC_4W, &b_ADC_4W);
   fChain->SetBranchAddress("ADC_5E", &ADC_5E, &b_ADC_5E);
   fChain->SetBranchAddress("ADC_5W", &ADC_5W, &b_ADC_5W);
   fChain->SetBranchAddress("ADC_6E", &ADC_6E, &b_ADC_6E);
   fChain->SetBranchAddress("ADC_6W", &ADC_6W, &b_ADC_6W);
   fChain->SetBranchAddress("ADC_7E", &ADC_7E, &b_ADC_7E);
   fChain->SetBranchAddress("ADC_7W", &ADC_7W, &b_ADC_7W);
   fChain->SetBranchAddress("ADC_8E", &ADC_8E, &b_ADC_8E);
   fChain->SetBranchAddress("ADC_8W", &ADC_8W, &b_ADC_8W);
   fChain->SetBranchAddress("ADC_9E", &ADC_9E, &b_ADC_9E);
   fChain->SetBranchAddress("ADC_9W", &ADC_9W, &b_ADC_9W);
   fChain->SetBranchAddress("ADC_10E", &ADC_10E, &b_ADC_10E);
   fChain->SetBranchAddress("ADC_10W", &ADC_10W, &b_ADC_10W);
   fChain->SetBranchAddress("ADC_11E", &ADC_11E, &b_ADC_11E);
   fChain->SetBranchAddress("ADC_11W", &ADC_11W, &b_ADC_11W);
   fChain->SetBranchAddress("ADC_12E", &ADC_12E, &b_ADC_12E);
   fChain->SetBranchAddress("ADC_12W", &ADC_12W, &b_ADC_12W);
   Notify();
}

Bool_t noah::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void noah::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t noah::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef noah_cxx
