//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 19 20:45:54 2011 by ROOT version 5.29/01
// from TTree fluxT/gemc flux infos tree
// found on file: electron_BaBar.root
//////////////////////////////////////////////////////////

#ifndef GEMC2CaloSim_h
#define GEMC2CaloSim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <fstream>
using namespace std;

class GEMC2CaloSim : public TSelector {

public :
	fstream foutfile;
	TString foutfilename;

	Double_t sumXP;
	Double_t sumYP;
	Double_t sumN;

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           evn;
   Int_t           nfluxhit;
   Int_t           ID[1];   //[nfluxhit]
   Float_t         Edep[1];   //[nfluxhit]
   Float_t         E[1];   //[nfluxhit]
   Float_t         x[1];   //[nfluxhit]
   Float_t         y[1];   //[nfluxhit]
   Float_t         z[1];   //[nfluxhit]
   Float_t         lx[1];   //[nfluxhit]
   Float_t         ly[1];   //[nfluxhit]
   Float_t         lz[1];   //[nfluxhit]
   Float_t         t[1];   //[nfluxhit]
   Int_t           pid[1];   //[nfluxhit]
   Int_t           mpid[1];   //[nfluxhit]
   Float_t         px[1];   //[nfluxhit]
   Float_t         py[1];   //[nfluxhit]
   Float_t         pz[1];   //[nfluxhit]
   Float_t         vx[1];   //[nfluxhit]
   Float_t         vy[1];   //[nfluxhit]
   Float_t         vz[1];   //[nfluxhit]
   Float_t         mvx[1];   //[nfluxhit]
   Float_t         mvy[1];   //[nfluxhit]
   Float_t         mvz[1];   //[nfluxhit]

   // List of branches
   TBranch        *b_evn;   //!
   TBranch        *b_nfluxhit;   //!
   TBranch        *b_ID;   //!
   TBranch        *b_Edep;   //!
   TBranch        *b_E;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_lx;   //!
   TBranch        *b_ly;   //!
   TBranch        *b_lz;   //!
   TBranch        *b_t;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_mpid;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_mvx;   //!
   TBranch        *b_mvy;   //!
   TBranch        *b_mvz;   //!

   GEMC2CaloSim(TString outfilename);
   virtual ~GEMC2CaloSim() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(GEMC2CaloSim,0);
};

#endif

#ifdef GEMC2CaloSim_cxx
void GEMC2CaloSim::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("nfluxhit", &nfluxhit, &b_nfluxhit);
   fChain->SetBranchAddress("ID", ID, &b_ID);
   fChain->SetBranchAddress("Edep", Edep, &b_Edep);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("x", x, &b_x);
   fChain->SetBranchAddress("y", y, &b_y);
   fChain->SetBranchAddress("z", z, &b_z);
   fChain->SetBranchAddress("lx", lx, &b_lx);
   fChain->SetBranchAddress("ly", ly, &b_ly);
   fChain->SetBranchAddress("lz", lz, &b_lz);
   fChain->SetBranchAddress("t", t, &b_t);
   fChain->SetBranchAddress("pid", pid, &b_pid);
   fChain->SetBranchAddress("mpid", mpid, &b_mpid);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("vy", vy, &b_vy);
   fChain->SetBranchAddress("vz", vz, &b_vz);
   fChain->SetBranchAddress("mvx", mvx, &b_mvx);
   fChain->SetBranchAddress("mvy", mvy, &b_mvy);
   fChain->SetBranchAddress("mvz", mvz, &b_mvz);
}

Bool_t GEMC2CaloSim::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef GEMC2CaloSim_cxx
