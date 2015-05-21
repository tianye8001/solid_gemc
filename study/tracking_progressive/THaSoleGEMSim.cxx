#include "THaSoleGEMSim.h"
#include "TSystem.h"
#include "TMath.h"

ClassImp(THaSoleSimTrack);
ClassImp(THaSoleSimHit);
ClassImp(THaSoleSimEvent);

#include <iostream>
#include <cstdio>
using namespace std;

void THaSoleSimTrack::Print (const Option_t* opt ) const
{
  
}

THaSoleSimHit::THaSoleSimHit(THaSoleSimHit *rhs){
  x = rhs->x;
  y = rhs->y;
  z = rhs->z;
  phi = rhs->phi;
  region = rhs->region;
  ex = rhs->ex;
  ey = rhs->ey;
  qu = rhs->qu;
  qv = rhs->qv;
  TrueHit = rhs->TrueHit;
}

THaSoleSimHit* THaSoleSimHit::operator=(THaSoleSimHit* rhs) {
  x = rhs->x;
  y = rhs->y;
  z = rhs->z;
  ex = rhs->ex;
  ey = rhs->ey;
  phi = rhs->phi;
  region = rhs->region;
  TrueHit = rhs->TrueHit;
  //---------added for uv charge asymmetry-----------//
  qu = rhs->qu;
  qv = rhs->qv;
  //-------------------------------------------------//
  return this;
}

void THaSoleSimHit::Print(const Option_t* opt) const
{
  
}


THaSoleSimEvent::THaSoleSimEvent() {
}

THaSoleSimEvent::~THaSoleSimEvent() {
  Clear();
}

void THaSoleSimEvent::Clear(const Option_t* opt)
{
  for (Int_t i=0;i!=5;i++){
    gemhits[i].Delete(opt);
    gemrealhits[i].Delete(opt);
  }
  tracks.Delete(opt);
  //----------add for EC--------//
  EChits.Delete(opt);
  //----------------------------//
}
