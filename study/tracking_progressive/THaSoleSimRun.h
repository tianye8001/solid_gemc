#ifndef THaSoleSimRun_
#define THaSoleSimRun_

#include "THaRunBase.h"
#include "THaSoleGEMSim.h"
#include "TString.h"
#include "TDirectory.h"

class TFile;
class TTree;
class TBranch;

class THaSoleSimRun : public THaRunBase {
 public:
  THaSoleSimRun(const char* filename = "", const char* description = "");
  THaSoleSimRun(const THaSoleSimRun &run);
  virtual ~THaSoleSimRun();
  virtual THaSoleSimRun &operator=(const THaRunBase &rhs);

  Int_t Close();
  Int_t Open();
  const Int_t* GetEvBuffer() const;
  Int_t ReadEvent();
  Int_t Init();
  const char* GetFileName() const {return rootFileName.Data();}
  void SetFileName(const char* name) {rootFileName = name; }
  //  Int_t SetNumOfPlanes(Int_t num) {numberofplanes = num; return num;}
  //Int_t GetNumOfPlanes() const {return numberofplanes; } 

  void calculate_hit(Int_t region,Int_t totalregion, Float_t rmin, Float_t rmax, Float_t suppression, Int_t count, Float_t* x, Float_t* y, Float_t* z, Int_t* new_count, Float_t*new_x, Float_t* new_y, Float_t* new_z);

 protected:
  virtual Int_t ReadDatabase() {return 0;}
  TString rootFileName;
  TFile *rootFile;
  TDirectory *curr;
  TTree *tree;
  THaSoleSimEvent *event;
  //For PVDIS there are 5 GEM trackers and one electromagnetic calorimeter, the first five are for GEM while the last one is EC
  Int_t nhit[6];
  Int_t Nsignal;
  Int_t TrueHit[6][10000];
  Double_t flag[6][10000];
  Double_t x[6][10000];
  Double_t ex[6][10000];
  Double_t y[6][10000];
  Double_t ey[6][10000];
  Double_t z[6][10000];
  Double_t chamber_pos[3][6];
  Double_t chamber_res[2][6];
  Double_t chamber_qu[6];
  Double_t chamber_qv[6];
  Double_t mom,theta,phi,vertex;
  //-------------added for uv charge asymmetry-------------//
  Double_t qu[6][10000];
  Double_t qv[6][10000];
  //-------------------------------------------------------//
  
  Int_t nentries;
  Int_t entry;
  ClassDef(THaSoleSimRun, 0) // Run class for simulated VDC data
    };
#endif
