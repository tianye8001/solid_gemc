#include "THaGemTrack.h"
ClassImp(THaGemTrack);
using namespace std;

THaGemTrack :: THaGemTrack() : nhit(0){
  fHits = new TClonesArray("THaGemHit",0);
}

THaGemTrack::~THaGemTrack() {
  Clear();
  delete fHits;
}

void THaGemTrack::Clear(const Option_t* opt){
  fHits->Delete();
  nhit = 0;
  charge = 0;
  angleflag = -1;
}

void THaGemTrack::AddHit(THaGemHit *rhs){
 
  THaGemHit *hit =new ((*fHits)[nhit++]) THaGemHit();
  //added qu and qv here
  hit->Set_content(rhs->Get_x(),rhs->Get_y(),rhs->Get_z(),rhs->Get_phi(),rhs->Get_r(), rhs->Get_qu(), rhs->Get_qv(), rhs->Get_ex(), rhs->Get_ey(), rhs->Get_TrueHit());
  hit->Calculate_layer();
}

Int_t THaGemTrack::Compare(const TObject* obj) const {
  const THaGemTrack* rhs = dynamic_cast<const THaGemTrack*>(obj);
  assert( rhs );
  /*if (angleflag < rhs->Get_Angleflag()){
    return -1;
  }else if (angleflag > rhs->Get_Angleflag()){
    return 1;
  }else{
    if (charge < rhs->Get_Charge()){
      return -1;
    }else if (charge > rhs->Get_Charge()){
      return 1;
    }else{
      if (nhit < rhs->Get_nhit()){
	return 1;
      }else if (nhit > rhs->Get_nhit()){
	return -1;
      }else{
	if (Chi2 > rhs->Get_Chi2()){
	  return 1;
	}else{
	  return -1;
	}
      }
    }
  }*/
	if (nhit < rhs->Get_nhit())
	{
	  return 1;
	}
	else if (nhit > rhs->Get_nhit())
	{
	  return -1;
	}
	else
	{
	  if (Chi2 < rhs->Get_Chi2())
	   {
	      return -1;
	   }
	  else
	   {
   	      return 1;
	   }
	
	}
}

Double_t THaGemTrack::Get_hit_info(Int_t i, Int_t j){
  THaGemHit *thishit;
  if (i<nhit){
    thishit =  (THaGemHit*)(fHits->At(i));
  }else{
    thishit = (THaGemHit*)(fHits->At(i%nhit));
  }
  //---------added j=6 and j=7 cases for qu and qv info------//
  if (j==0){
    return thishit->Get_x();
  }else if (j==1){
    return thishit->Get_y();
  }else if (j==2){
    return thishit->Get_z();
  }else if (j==3){
    return thishit->Get_r();
  }else if (j==4){
    return thishit->Get_phi();
  }else if (j==5){
    return (Float_t)thishit->Get_layer();
  }else if (j==6){
    return thishit->Get_qu();
  }else if (j==7){
    return thishit->Get_qv();
  }else if (j==8){
    return thishit->Get_ex();
  }else if (j==9){
    return thishit->Get_ey();
  }else if (j==10){
    return thishit->Get_TrueHit();
  }else{
    return 0;
  }


  
  //----------------------------------------------------------//
}
