
//Ye Tian Aug. 18,2017 created this function for GEMC SIDIS configuration, the code is based on Rakitha's method.  
//The EM, HallDhadrons, HallDhadrons_winup, and HallDhadrons_windown are the backgrounds considered in this study. 

//Radial binning is 3 see trig_low_R and trig_high_R
//momentum binning is 20 see P_low and P_high

//Routines GetPionTriggerEffi and GetElectronTriggerEffi would return the trigger efficiency when radius index and momentum index (bin index) are passed to them
//The last radius index in the trig_pi_eff and trig_ele_eff gives the trigger efficiency for all radius average

//Use routines GetRadiusIndex and GetMomentumIndex to get the bin index for radius and momentum
//The radius is at the front face of the EC
Double_t trig_low_R[3]={90.0 ,105.0 ,115.0 };
Double_t trig_high_R[3]={105.0 ,115.0 ,130.0};
Double_t P_low[20] = {0.0}; //momentum in GeV
Double_t P_high[20] = {0.0}; 
//momentum bin from 1GeV~8GeV, bins size 0.35GeV
for(int p_bin=0;p_bin<20;p_bin++){
P_low[p_bin]=1+p_bin*0.35; 
P_high[p_bin]=1.35+p_bin*0.35;
}

Int_t GetRadiusIndex(Double_t radius){
  Int_t Ri=-1;
  for (Int_t i =0; i<3;i++){
    if (radius>trig_low_R[i] && radius<=trig_high_R[i]){
      Ri=i;
      break;
    }
  }
  return Ri;
};
Int_t GetMomentumIndex(Double_t mom){
  Int_t Pi=-1;
  for (Int_t i =0; i<20;i++){
    if (mom>P_low[i] && mom<=P_high[i]){
      Pi=i;
      break;
    }
  }
  return Pi;
};


Double_t GetElectronTriggerEffi(Int_t rad_index, Int_t mom_index){
  Double_t trig_ele_eff[3][20] = { { 0.002,0.002,0.006,0.030,0.489,0.928,0.987,0.994,0.996,0.999,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,0.999,1.000},{ 0.001,0.001,0.002,0.022,0.441,0.932,0.985,0.995,0.997,0.999,1.000,1.000,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.001,0.002,0.004,0.074,0.540,0.852,0.916,0.944,0.953,0.961,0.969,0.972,0.970,0.971,0.979,0.977,0.979,0.982,0.984,0.986}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetElectronTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_ele_eff_err[3][20] = { { 0.001,0.001,0.002,0.003,0.009,0.005,0.002,0.001,0.001,0.001,0.001,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.001,0.000,},{ 0.001,0.001,0.001,0.003,0.011,0.006,0.003,0.002,0.001,0.001,0.000,0.000,0.001,0.000,0.000,0.000,0.000,0.000,0.000,0.000},{ 0.001,0.001,0.001,0.005,0.010,0.007,0.006,0.005,0.004,0.004,0.004,0.003,0.004,0.003,0.003,0.003,0.003,0.003,0.003,0.002}}; 
  if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff_err[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetPionTriggerEffi(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff[3][20] = { { 0.000,0.000,0.000,0.002,0.017,0.033,0.087,0.137,0.207,0.211,0.255,0.279,0.311,0.343,0.348,0.391,0.386,0.391,0.402,0.417},{ 0.000,0.000,0.001,0.002,0.015,0.045,0.084,0.128,0.195,0.234,0.268,0.278,0.315,0.342,0.352,0.368,0.397,0.406,0.409,0.433},{ 0.000,0.000,0.000,0.005,0.014,0.036,0.057,0.094,0.144,0.167,0.186,0.194,0.212,0.245,0.250,0.275,0.285,0.302,0.308,0.343}};  
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff[rad_index][mom_index];
  else
    return 0;
};

Double_t GetPionTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff_err[3][20] = { { 0.000,0.000,0.000,0.001,0.003,0.003,0.005,0.007,0.008,0.008,0.008,0.009,0.009,0.009,0.009,0.010,0.009,0.010,0.009,0.010},{ 0.000,0.000,0.001,0.001,0.003,0.005,0.006,0.008,0.009,0.010,0.010,0.010,0.011,0.011,0.011,0.011,0.011,0.011,0.011,0.011},{ 0.000,0.000,0.000,0.002,0.002,0.004,0.005,0.006,0.007,0.008,0.008,0.008,0.008,0.009,0.009,0.009,0.009,0.009,0.010,0.010}}; 
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff_err[rad_index][mom_index];
  else
    return 0;
};
