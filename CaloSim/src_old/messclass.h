//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 19 16:35:44 2010 by ROOT version 5.18/00
// from TTree ntuple/ROOT Ntuple for G4 data
// found on file: out.root
//////////////////////////////////////////////////////////

#ifndef messclass_h
#define messclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class messclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         evtIndex;
   Float_t         vtxE;
   Float_t         initX;
   Float_t         initY;
   Float_t         initZ;
   Float_t         caloX;
   Float_t         caloY;
   Float_t         caloZ;
   Float_t         initPX;
   Float_t         initPY;
   Float_t         initPZ;
   Float_t         caloEdep;
   Float_t         fiberEdep;
   Float_t         glueEdep;
   Float_t         WEdep;
   Float_t         b000;
   Float_t         b001;
   Float_t         b002;
   Float_t         b003;
   Float_t         b004;
   Float_t         b005;
   Float_t         b006;
   Float_t         b007;
   Float_t         b008;
   Float_t         b009;
   Float_t         b010;
   Float_t         b011;
   Float_t         b012;
   Float_t         b013;
   Float_t         b014;
   Float_t         b015;
   Float_t         b016;
   Float_t         b017;
   Float_t         b018;
   Float_t         b019;
   Float_t         b020;
   Float_t         b021;
   Float_t         b022;
   Float_t         b023;
   Float_t         b024;
   Float_t         b025;
   Float_t         v00;
   Float_t         v01;
   Float_t         v02;
   Float_t         v03;
   Float_t         v04;
   Float_t         v05;
   Float_t         v06;
   Float_t         v07;
   Float_t         v08;
   Float_t         v09;
   Float_t         v10;
   Float_t         v11;
   Float_t         v12;
   Float_t         v13;
   Float_t         v14;
   Float_t         h00;
   Float_t         h01;
   Float_t         h02;
   Float_t         h03;
   Float_t         h04;
   Float_t         h05;
   Float_t         h06;
   Float_t         h07;
   Float_t         h08;
   Float_t         h09;
   Float_t         h10;
   Float_t         h11;
   Float_t         h12;
   Float_t         h13;
   Float_t         h14;
   Float_t         totalEdep;
   Float_t         diffX;
   Float_t         diffY;
   Float_t         diffZ;
   Float_t         startOut;

   // List of branches
   TBranch        *b_evtIndex;   //!
   TBranch        *b_vtxE;   //!
   TBranch        *b_initX;   //!
   TBranch        *b_initY;   //!
   TBranch        *b_initZ;   //!
   TBranch        *b_caloX;   //!
   TBranch        *b_caloY;   //!
   TBranch        *b_caloZ;   //!
   TBranch        *b_initPX;   //!
   TBranch        *b_initPY;   //!
   TBranch        *b_initPZ;   //!
   TBranch        *b_caloEdep;   //!
   TBranch        *b_fiberEdep;   //!
   TBranch        *b_glueEdep;   //!
   TBranch        *b_WEdep;   //!
   TBranch        *b_b000;   //!
   TBranch        *b_b001;   //!
   TBranch        *b_b002;   //!
   TBranch        *b_b003;   //!
   TBranch        *b_b004;   //!
   TBranch        *b_b005;   //!
   TBranch        *b_b006;   //!
   TBranch        *b_b007;   //!
   TBranch        *b_b008;   //!
   TBranch        *b_b009;   //!
   TBranch        *b_b010;   //!
   TBranch        *b_b011;   //!
   TBranch        *b_b012;   //!
   TBranch        *b_b013;   //!
   TBranch        *b_b014;   //!
   TBranch        *b_b015;   //!
   TBranch        *b_b016;   //!
   TBranch        *b_b017;   //!
   TBranch        *b_b018;   //!
   TBranch        *b_b019;   //!
   TBranch        *b_b020;   //!
   TBranch        *b_b021;   //!
   TBranch        *b_b022;   //!
   TBranch        *b_b023;   //!
   TBranch        *b_b024;   //!
   TBranch        *b_b025;   //!
   TBranch        *b_v00;   //!
   TBranch        *b_v01;   //!
   TBranch        *b_v02;   //!
   TBranch        *b_v03;   //!
   TBranch        *b_v04;   //!
   TBranch        *b_v05;   //!
   TBranch        *b_v06;   //!
   TBranch        *b_v07;   //!
   TBranch        *b_v08;   //!
   TBranch        *b_v09;   //!
   TBranch        *b_v10;   //!
   TBranch        *b_v11;   //!
   TBranch        *b_v12;   //!
   TBranch        *b_v13;   //!
   TBranch        *b_v14;   //!
   TBranch        *b_h00;   //!
   TBranch        *b_h01;   //!
   TBranch        *b_h02;   //!
   TBranch        *b_h03;   //!
   TBranch        *b_h04;   //!
   TBranch        *b_h05;   //!
   TBranch        *b_h06;   //!
   TBranch        *b_h07;   //!
   TBranch        *b_h08;   //!
   TBranch        *b_h09;   //!
   TBranch        *b_h10;   //!
   TBranch        *b_h11;   //!
   TBranch        *b_h12;   //!
   TBranch        *b_h13;   //!
   TBranch        *b_h14;   //!
   TBranch        *b_totalEdep;   //!
   TBranch        *b_diffX;   //!
   TBranch        *b_diffY;   //!
   TBranch        *b_diffZ;   //!
   TBranch        *b_startOut;   //!

   messclass(TTree *tree=0);
   virtual ~messclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef messclass_cxx
messclass::messclass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("out.root");
      if (!f) {
         f = new TFile("out.root");
      }
      tree = (TTree*)gDirectory->Get("ntuple");

   }
   Init(tree);
}

messclass::~messclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t messclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t messclass::LoadTree(Long64_t entry)
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

void messclass::Init(TTree *tree)
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

   fChain->SetBranchAddress("evtIndex", &evtIndex, &b_evtIndex);
   fChain->SetBranchAddress("vtxE", &vtxE, &b_vtxE);
   fChain->SetBranchAddress("initX", &initX, &b_initX);
   fChain->SetBranchAddress("initY", &initY, &b_initY);
   fChain->SetBranchAddress("initZ", &initZ, &b_initZ);
   fChain->SetBranchAddress("caloX", &caloX, &b_caloX);
   fChain->SetBranchAddress("caloY", &caloY, &b_caloY);
   fChain->SetBranchAddress("caloZ", &caloZ, &b_caloZ);
   fChain->SetBranchAddress("initPX", &initPX, &b_initPX);
   fChain->SetBranchAddress("initPY", &initPY, &b_initPY);
   fChain->SetBranchAddress("initPZ", &initPZ, &b_initPZ);
   fChain->SetBranchAddress("caloEdep", &caloEdep, &b_caloEdep);
   fChain->SetBranchAddress("fiberEdep", &fiberEdep, &b_fiberEdep);
   fChain->SetBranchAddress("glueEdep", &glueEdep, &b_glueEdep);
   fChain->SetBranchAddress("WEdep", &WEdep, &b_WEdep);
   fChain->SetBranchAddress("b000", &b000, &b_b000);
   fChain->SetBranchAddress("b001", &b001, &b_b001);
   fChain->SetBranchAddress("b002", &b002, &b_b002);
   fChain->SetBranchAddress("b003", &b003, &b_b003);
   fChain->SetBranchAddress("b004", &b004, &b_b004);
   fChain->SetBranchAddress("b005", &b005, &b_b005);
   fChain->SetBranchAddress("b006", &b006, &b_b006);
   fChain->SetBranchAddress("b007", &b007, &b_b007);
   fChain->SetBranchAddress("b008", &b008, &b_b008);
   fChain->SetBranchAddress("b009", &b009, &b_b009);
   fChain->SetBranchAddress("b010", &b010, &b_b010);
   fChain->SetBranchAddress("b011", &b011, &b_b011);
   fChain->SetBranchAddress("b012", &b012, &b_b012);
   fChain->SetBranchAddress("b013", &b013, &b_b013);
   fChain->SetBranchAddress("b014", &b014, &b_b014);
   fChain->SetBranchAddress("b015", &b015, &b_b015);
   fChain->SetBranchAddress("b016", &b016, &b_b016);
   fChain->SetBranchAddress("b017", &b017, &b_b017);
   fChain->SetBranchAddress("b018", &b018, &b_b018);
   fChain->SetBranchAddress("b019", &b019, &b_b019);
   fChain->SetBranchAddress("b020", &b020, &b_b020);
   fChain->SetBranchAddress("b021", &b021, &b_b021);
   fChain->SetBranchAddress("b022", &b022, &b_b022);
   fChain->SetBranchAddress("b023", &b023, &b_b023);
   fChain->SetBranchAddress("b024", &b024, &b_b024);
   fChain->SetBranchAddress("b025", &b025, &b_b025);
   fChain->SetBranchAddress("v00", &v00, &b_v00);
   fChain->SetBranchAddress("v01", &v01, &b_v01);
   fChain->SetBranchAddress("v02", &v02, &b_v02);
   fChain->SetBranchAddress("v03", &v03, &b_v03);
   fChain->SetBranchAddress("v04", &v04, &b_v04);
   fChain->SetBranchAddress("v05", &v05, &b_v05);
   fChain->SetBranchAddress("v06", &v06, &b_v06);
   fChain->SetBranchAddress("v07", &v07, &b_v07);
   fChain->SetBranchAddress("v08", &v08, &b_v08);
   fChain->SetBranchAddress("v09", &v09, &b_v09);
   fChain->SetBranchAddress("v10", &v10, &b_v10);
   fChain->SetBranchAddress("v11", &v11, &b_v11);
   fChain->SetBranchAddress("v12", &v12, &b_v12);
   fChain->SetBranchAddress("v13", &v13, &b_v13);
   fChain->SetBranchAddress("v14", &v14, &b_v14);
   fChain->SetBranchAddress("h00", &h00, &b_h00);
   fChain->SetBranchAddress("h01", &h01, &b_h01);
   fChain->SetBranchAddress("h02", &h02, &b_h02);
   fChain->SetBranchAddress("h03", &h03, &b_h03);
   fChain->SetBranchAddress("h04", &h04, &b_h04);
   fChain->SetBranchAddress("h05", &h05, &b_h05);
   fChain->SetBranchAddress("h06", &h06, &b_h06);
   fChain->SetBranchAddress("h07", &h07, &b_h07);
   fChain->SetBranchAddress("h08", &h08, &b_h08);
   fChain->SetBranchAddress("h09", &h09, &b_h09);
   fChain->SetBranchAddress("h10", &h10, &b_h10);
   fChain->SetBranchAddress("h11", &h11, &b_h11);
   fChain->SetBranchAddress("h12", &h12, &b_h12);
   fChain->SetBranchAddress("h13", &h13, &b_h13);
   fChain->SetBranchAddress("h14", &h14, &b_h14);
   fChain->SetBranchAddress("totalEdep", &totalEdep, &b_totalEdep);
   fChain->SetBranchAddress("diffX", &diffX, &b_diffX);
   fChain->SetBranchAddress("diffY", &diffY, &b_diffY);
   fChain->SetBranchAddress("diffZ", &diffZ, &b_diffZ);
   fChain->SetBranchAddress("startOut", &startOut, &b_startOut);
   Notify();
}

Bool_t messclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void messclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t messclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef messclass_cxx
