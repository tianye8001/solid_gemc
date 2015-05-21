#ifndef ROOT_THaGemTrack_
#define ROOT_THaGemTrack_

#include "TMath.h"
#include "TClonesArray.h"
#include "THaGemHit.h"
#include <cassert>

class THaGemTrack : public TObject {
 public:
  THaGemTrack();
  virtual ~THaGemTrack();

  virtual void Clear (const Option_t* opt = "");
  void AddHit(THaGemHit *rhs);
  

  Double_t Get_hit1_x(){return Get_hit_info(0,0);};
  Double_t Get_hit2_x(){return Get_hit_info(1,0);};
  Double_t Get_hit3_x(){return Get_hit_info(2,0);};
  Double_t Get_hit4_x(){return Get_hit_info(3,0);};
  Double_t Get_hit5_x(){return Get_hit_info(4,0);};
  
  Double_t Get_hit1_y(){return Get_hit_info(0,1);};
  Double_t Get_hit2_y(){return Get_hit_info(1,1);};
  Double_t Get_hit3_y(){return Get_hit_info(2,1);};
  Double_t Get_hit4_y(){return Get_hit_info(3,1);};
  Double_t Get_hit5_y(){return Get_hit_info(4,1);};

  Double_t Get_hit1_z(){return Get_hit_info(0,2);};
  Double_t Get_hit2_z(){return Get_hit_info(1,2);};
  Double_t Get_hit3_z(){return Get_hit_info(2,2);};
  Double_t Get_hit4_z(){return Get_hit_info(3,2);};
  Double_t Get_hit5_z(){return Get_hit_info(4,2);};

  Double_t Get_hit1_r(){return Get_hit_info(0,3);};
  Double_t Get_hit2_r(){return Get_hit_info(1,3);};
  Double_t Get_hit3_r(){return Get_hit_info(2,3);};
  Double_t Get_hit4_r(){return Get_hit_info(3,3);};
  Double_t Get_hit5_r(){return Get_hit_info(4,3);};

  Double_t Get_hit1_phi(){return Get_hit_info(0,4);};
  Double_t Get_hit2_phi(){return Get_hit_info(1,4);};
  Double_t Get_hit3_phi(){return Get_hit_info(2,4);};
  Double_t Get_hit4_phi(){return Get_hit_info(3,4);};
  Double_t Get_hit5_phi(){return Get_hit_info(4,4);};

  Double_t Get_hit1_layer(){return Get_hit_info(0,5);};
  Double_t Get_hit2_layer(){return Get_hit_info(1,5);};
  Double_t Get_hit3_layer(){return Get_hit_info(2,5);};
  Double_t Get_hit4_layer(){return Get_hit_info(3,5);};
  Double_t Get_hit5_layer(){return Get_hit_info(4,5);};
  //-----------added for qu charge asymmetry---------------//
  Double_t Get_hit1_qu(){return Get_hit_info(0,6);};
  Double_t Get_hit2_qu(){return Get_hit_info(1,6);};
  Double_t Get_hit3_qu(){return Get_hit_info(2,6);};
  Double_t Get_hit4_qu(){return Get_hit_info(3,6);};
  Double_t Get_hit5_qu(){return Get_hit_info(4,6);};

  Double_t Get_hit1_qv(){return Get_hit_info(0,7);};
  Double_t Get_hit2_qv(){return Get_hit_info(1,7);};
  Double_t Get_hit3_qv(){return Get_hit_info(2,7);};
  Double_t Get_hit4_qv(){return Get_hit_info(3,7);};
  Double_t Get_hit5_qv(){return Get_hit_info(4,7);};

  Double_t Get_hit1_ex(){return Get_hit_info(0,8);};
  Double_t Get_hit2_ex(){return Get_hit_info(1,8);};
  Double_t Get_hit3_ex(){return Get_hit_info(2,8);};
  Double_t Get_hit4_ex(){return Get_hit_info(3,8);};
  Double_t Get_hit5_ex(){return Get_hit_info(4,8);};

  Double_t Get_hit1_ey(){return Get_hit_info(0,9);};
  Double_t Get_hit2_ey(){return Get_hit_info(1,9);};
  Double_t Get_hit3_ey(){return Get_hit_info(2,9);};
  Double_t Get_hit4_ey(){return Get_hit_info(3,9);};
  Double_t Get_hit5_ey(){return Get_hit_info(4,9);};

  Int_t Get_hit1_TrueHit(){return Get_hit_info(0,10);};
  Int_t Get_hit2_TrueHit(){return Get_hit_info(1,10);};	
  Int_t Get_hit3_TrueHit(){return Get_hit_info(2,10);};
  Int_t Get_hit4_TrueHit(){return Get_hit_info(3,10);};
  Int_t Get_hit5_TrueHit(){return Get_hit_info(4,10);};
  //-------------------------------------------------------//


  Int_t Get_nhit() const {return nhit;};
  void Set_Charge(Int_t value) {charge = value;};
  Int_t Get_Charge() const {return charge;};
  void Set_Angleflag(Int_t value){angleflag = value;};
  Int_t Get_Angleflag() const {return angleflag;};
  TClonesArray* Get_hits(){return fHits;};
  Double_t Get_hit_info(Int_t i,Int_t j);

  void Set_Mommin(Double_t min){ mom_min=min;};
  void Set_Mommax(Double_t max){ mom_max=max;};
  Double_t Get_Mommin(){return mom_min;};
  Double_t Get_Mommax(){return mom_max;};

  void Set_Thetamin(Double_t min){ theta_min=min;};
  void Set_Thetamax(Double_t max){ theta_max=max;};
  void Set_Theta(Double_t value){theta=value;};
  Double_t Get_Thetamin(){return theta_min;};
  Double_t Get_Thetamax(){return theta_max;};
  Double_t Get_Theta(){return theta;};
  
  Int_t GetBad(){return flag_bad;};
  void SetBad(Int_t value){flag_bad = value;};

  void Set_Rvalue(Double_t value){Rvalue = value;};
  Double_t Get_Rvalue()const {return Rvalue;};

  void Set_Chi2(Double_t value){Chi2 = value;};
  Double_t Get_Chi2()const {return Chi2;};

  void Set_Vertex(Double_t value){Recon_vertex = value;};
  Double_t Get_Vertex()const {return Recon_vertex;};
  
  Int_t Compare( const TObject* obj ) const;
  Bool_t IsSortable () const { return kTRUE; }
 protected:
  Int_t nhit;
  Int_t charge;
  Int_t angleflag;
  Int_t flag_bad;
  

  Double_t Rvalue;
  Double_t mom_min;
  Double_t mom_max;
  Double_t theta_min;
  Double_t theta_max;
  Double_t theta;
  Double_t Chi2;
  Double_t Recon_vertex;
  TClonesArray *fHits;
  ClassDef(THaGemTrack,0)
};


#endif
