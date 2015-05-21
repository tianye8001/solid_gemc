#include "TSystem.h"
#include "THaGemHit.h"
#include <math.h>
#include <iostream>

ClassImp(THaGemHit);

using namespace std;


//added qu1 and qv1 in Set_content
void THaGemHit::Set_content(Double_t x1, Double_t y1, Double_t z1, Double_t phi1, Double_t r1, Double_t qu1, Double_t qv1, Double_t ex1, Double_t ey1, Int_t TrueHit1){
  x=x1;y=y1;z=z1;r=r1;phi=phi1;qu=qu1;qv=qv1;ex=ex1;ey=ey1;TrueHit=TrueHit1;
}

void THaGemHit::Calculate_layer(){
  if (fabs(z)<1e-3){
    layer = 0;
    p_layer = -1;
    p2_layer = -1;
    n_layer = 1;
    n2_layer = 2;
  }else if (fabs(z-0.28)<1e-3){
    layer = 1;
    p_layer = 0;
    p2_layer = -1;
    n_layer = 2;
    n2_layer = 3;
  }else if (fabs(z-0.325)<1e-3){
    layer = 2;
    p_layer = 1;
    p2_layer = 0;
    n_layer = 3;
    n2_layer = 4;
  }else if (fabs(z-1.485)<1e-3){
    layer = 3;
    p_layer = 2;
    p2_layer = 1;
    n_layer = 4;
    n2_layer = 5;
  }else if (fabs(z-1.575)<1e-3){
    layer = 4;
    p_layer = 3;
    p2_layer = 2;
    n_layer = 5;
    n2_layer = -1;
  }else if (fabs(z-1.62809)<1e-3){
    layer = 5;
    p_layer = 3;
    p2_layer = 2;
    n_layer = 5;
    n2_layer = -1; 
  }
}


void THaGemHit::Set_array(Int_t layer, Int_t flag, Int_t value){
  if (layer == p_layer && flag>=0 && flag<=3){
    p_array[flag] = value;
  }else if (layer == p2_layer && flag>=0 && flag<=3){
    p2_array[flag] = value;
  }else if (layer == n_layer && flag>=0 && flag<=3){
    n_array[flag] = value;
  }else if (layer == n2_layer && flag>=0 && flag<=3){
    n2_array[flag] = value;
  }else{
    cout << "layer Wrong in THaGemHit::Set_array" << endl;
  }
}

Int_t THaGemHit::Get_array(Int_t layer, Int_t flag){
  if (layer == p_layer && flag>=0 && flag<=3){
    return p_array[flag];
  }else if (layer == p2_layer && flag>=0 && flag<=3){
    return p2_array[flag];
  }else if (layer == n_layer && flag>=0 && flag<=3){
    return n_array[flag];
  }else if (layer == n2_layer && flag>=0 && flag<=3){
    return n2_array[flag];
  }else{
    cout << "layer Wrong in THaGemHit::Get_array" << endl;
    return -1;
  }
}
