#ifndef THaSoleGEMSim_
#define THaSoleGEMSim_

#include "TList.h"
#include "TVector3.h"
#include "TString.h"
#include <cassert>

class THaSoleSimTrack : public TObject {
 public:
  THaSoleSimTrack() {}
  Float_t mom,theta,phi,vertex;
  Double_t x[6],y[6],z[6];
  Double_t ex[6], ey[6];
  Double_t qu[6], qv[6];
  Int_t flag;

  Double_t Get1X(){return x[0];};
  Double_t Get2X(){return x[1];};
  Double_t Get3X(){return x[2];};
  Double_t Get4X(){return x[3];};
  Double_t Get5X(){return x[4];};
  Double_t Get6X(){return x[5];};

  Double_t Get1Y(){return y[0];};
  Double_t Get2Y(){return y[1];};
  Double_t Get3Y(){return y[2];};
  Double_t Get4Y(){return y[3];};
  Double_t Get5Y(){return y[4];};
  Double_t Get6Y(){return y[5];};
  
  Double_t Get1Z(){return z[0];};
  Double_t Get2Z(){return z[1];};
  Double_t Get3Z(){return z[2];};
  Double_t Get4Z(){return z[3];};
  Double_t Get5Z(){return z[4];};
  Double_t Get6Z(){return z[5];};

  Double_t Get1EX(){return ex[0];};
  Double_t Get2EX(){return ex[1];};
  Double_t Get3EX(){return ex[2];};
  Double_t Get4EX(){return ex[3];};
  Double_t Get5EX(){return ex[4];};
  Double_t Get6EX(){return ex[5];};

  Double_t Get1EY(){return ey[0];};
  Double_t Get2EY(){return ey[1];};
  Double_t Get3EY(){return ey[2];};
  Double_t Get4EY(){return ey[3];};
  Double_t Get5EY(){return ey[4];};
  Double_t Get6EY(){return ey[5];};

  Double_t Get1QU(){return qu[0];};
  Double_t Get2QU(){return qu[1];};
  Double_t Get3QU(){return qu[2];};
  Double_t Get4QU(){return qu[3];};
  Double_t Get5QU(){return qu[4];};
  Double_t Get6QU(){return qu[5];};

  Double_t Get1QV(){return qv[0];};
  Double_t Get2QV(){return qv[1];};
  Double_t Get3QV(){return qv[2];};
  Double_t Get4QV(){return qv[3];};
  Double_t Get5QV(){return qv[4];};
  Double_t Get6QV(){return qv[5];};


  
  Float_t Getflag(){return flag;};
  virtual void Print(const Option_t* opt = "") const;
  ClassDef(THaSoleSimTrack,0)
};


class THaSoleSimHit : public TObject {
 public: 
 THaSoleSimHit() {};
 
 THaSoleSimHit(THaSoleSimHit *rhs);
 THaSoleSimHit* operator = (THaSoleSimHit* rhs);

  Double_t x;
  Double_t y;
  Double_t z;
  Double_t r;
  Double_t phi;
  Int_t region;
  Int_t totalregion;
  Double_t qu;
  Double_t qv;
  Double_t ex;
  Double_t ey;
  Int_t TrueHit;

  Int_t Compare( const TObject* obj ) const;
  Bool_t IsSortable () const { return kTRUE; }
  
  inline void calregion(Int_t value){
    region = Int_t(phi/3.1415926*value/2.);
    if (region == value){
      region = 0;
    }
    totalregion = value;
  }

  virtual void Print(const Option_t* opt = "") const;
  ClassDef(THaSoleSimHit,0)
};

 inline Int_t THaSoleSimHit::Compare(const TObject* obj) const {
   const THaSoleSimHit* rhs = dynamic_cast<const THaSoleSimHit*>(obj);
    assert( rhs );
    if( phi  < rhs->phi )  {
      return  -1;
    }else{
      return 1;
    }
}

class THaSoleSimEvent : public TObject {
  public:
  THaSoleSimEvent();
  virtual ~THaSoleSimEvent();
  
  Int_t event_num;
  TList gemhits[5];
  TList gemrealhits[5];
  TList tracks;
  TList EChits;

  virtual void Clear (const Option_t* opt = "");
  ClassDef(THaSoleSimEvent,0)
};


#endif
