#ifndef ROOT_THaGemHit_
#define ROOT_THaGemHit_

#include "TMath.h"
#include <cassert>

class THaGemHit : public TObject {
 public:
  THaGemHit(){}
  //added qu1 and qv1 in Set_content
  void Set_content(Double_t x1, Double_t y1, Double_t z1, Double_t phi1, Double_t r1, Double_t qu1, Double_t qv1, Double_t ex1, Double_t ey1, Int_t TrueHit1);
  
  Double_t Get_phi(){ return phi;};
  Double_t Get_x(){ return x;};
  Double_t Get_y(){ return y;};
  Double_t Get_z(){ return z;};
  Double_t Get_r(){ return r;};
  Double_t Get_qu(){return qu;};
  Double_t Get_qv(){return qv;};
  Double_t Get_ex(){return ex;};
  Double_t Get_ey(){return ey;};
  Int_t Get_TrueHit(){return TrueHit;};

  Int_t Get_layer(){return layer;};
  Int_t Get_p_layer(){return p_layer;};
  Int_t Get_p2_layer(){return p2_layer;};
  Int_t Get_n_layer(){return n_layer;};
  Int_t Get_n2_layer(){return n2_layer;};
  
  void Calculate_layer();
  void Set_array(Int_t layer, Int_t flag, Int_t value);
  Int_t Get_array(Int_t layer, Int_t flag);
  
  Double_t Get_tmpphi() const {return tempphi;};
  void Set_tmpphi(Float_t offset);

  Int_t Compare( const TObject* obj ) const;
  Bool_t IsSortable () const { return kTRUE; }

  virtual void Print(const Option_t* opt = "") const{};
 protected:
  Double_t x;  // Hit x
  Double_t y;  // Hit y
  Double_t z;  // Hit z
  Double_t phi; // Hit phi

  Double_t tempphi;

  Double_t r;   // Hit r
  Int_t layer;  //Hit layer
  Int_t p_layer; // the previous layer
  Int_t p2_layer; // the one before the previous layer
  Int_t n_layer; // next layer
  Int_t n2_layer; // the one after the next layer
  Int_t p_array[4],p2_array[4],n_array[4],n2_array[4];
  Double_t qu;
  Double_t qv;
  Double_t ex;
  Double_t ey;
  Int_t TrueHit;

  ClassDef(THaGemHit,0)
};
//set the range of phi to be -PI to PI
inline void THaGemHit::Set_tmpphi(Float_t offset){
  tempphi = phi - offset;
  if (tempphi>3.1415926){
    tempphi = tempphi - 2.*3.1415926;
  }
}

inline Int_t THaGemHit::Compare(const TObject* obj) const {
   const THaGemHit* rhs = dynamic_cast<const THaGemHit*>(obj);
    assert( rhs );
    if (tempphi  < rhs->Get_tmpphi()) {
      return  -1;
    }else{
      return 1;
    }
}

#endif
