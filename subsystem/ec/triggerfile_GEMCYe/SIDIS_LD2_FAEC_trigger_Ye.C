
//Ye Tian Aug. 18,2017 created this function for GEMC SIDIS configuration, the code is based on Rakitha's method.  
//The EM, HallDhadrons, HallDhadrons_winup, and HallDhadrons_windown are the backgrounds considered in this study. 

//Radial binning is 5 see trig_low_R and trig_high_R
//momentum binning is 20 see P_low and P_high

//Routines GetPionTriggerEffi and GetElectronTriggerEffi would return the trigger efficiency when radius index and momentum index (bin index) are passed to them
//The last radius index in the trig_pi_eff and trig_ele_eff gives the trigger efficiency for all radius average

//Use routines GetRadiusIndex and GetMomentumIndex to get the bin index for radius and momentum
//The radius is at the front face of the EC
Double_t trig_low_R[5]={90.0 ,105.0 ,115.0 ,130.0,150.0};
Double_t trig_high_R[5]={105.0 ,115.0 ,130.0 ,150.0,200.0};
Double_t P_low[20] = {0.0}; //momentum in GeV
Double_t P_high[20] = {0.0}; 
//momentum bin from 1GeV~8GeV, bins size 0.35GeV
for(int p_bin=0;p_bin<20;p_bin++){
P_low[p_bin]=1+p_bin*0.35; 
P_high[p_bin]=1.35+p_bin*0.35;
}

Int_t GetRadiusIndex(Double_t radius){
  Int_t Ri=-1;
  for (Int_t i =0; i<5;i++){
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
  Double_t trig_ele_eff[5][20] = { { 0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.008,0.007,0.096,0.632,0.969,0.970,0.993,1.000,0.993,0.987,1.000,1.000,1.000},{ 0.002,0.000,0.000,0.005,0.000,0.000,0.092,0.674,0.978,0.991,0.994,0.997,0.994,0.997,0.989,0.994,0.997,1.000,1.000,1.000},{ 0.002,0.000,0.002,0.012,0.415,0.932,0.989,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.002,0.090,0.812,0.990,0.997,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.946,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000}};
 if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetElectronTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_ele_eff_err[5][20] = { { 0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.008,0.007,0.025,0.042,0.015,0.015,0.007,0.000,0.007,0.009,0.000,0.000,0.000},{ 0.002,0.000,0.000,0.004,0.000,0.000,0.016,0.026,0.008,0.005,0.004,0.003,0.004,0.003,0.006,0.004,0.003,0.000,0.000,0.000},{ 0.002,0.000,0.002,0.004,0.021,0.011,0.004,0.000,0.003,0.002,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000},{ 0.001,0.009,0.012,0.003,0.002,0.001,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000},{ 0.007,0.001,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff_err[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetPionTriggerEffi(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff[5][20] = { { 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.015,0.007,0.016,0.024,0.046,0.055,0.158,0.112,0.198,0.152,0.173},{ 0.000,0.004,0.002,0.000,0.000,0.000,0.000,0.008,0.017,0.040,0.095,0.119,0.145,0.137,0.228,0.241,0.235,0.269,0.277,0.328},{ 0.001,0.000,0.000,0.005,0.008,0.044,0.053,0.140,0.174,0.210,0.214,0.254,0.279,0.346,0.354,0.323,0.365,0.426,0.402,0.397},{ 0.001,0.024,0.067,0.140,0.213,0.284,0.335,0.348,0.395,0.395,0.452,0.426,0.439,0.463,0.480,0.496,0.519,0.472,0.502,0.497},{ 0.291,0.340,0.432,0.473,0.515,0.525,0.542,0.535,0.551,0.554,0.552,0.535,0.555,0.557,0.562,0.578,0.540,0.573,0.572,0.579}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff[rad_index][mom_index];
  else
    return 0;
};

Double_t GetPionTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff_err[5][20] = { { 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.010,0.007,0.011,0.012,0.018,0.019,0.033,0.026,0.031,0.031,0.032},{ 0.000,0.003,0.002,0.000,0.000,0.000,0.000,0.005,0.007,0.010,0.017,0.017,0.020,0.019,0.023,0.022,0.023,0.025,0.024,0.026},{ 0.001,0.000,0.000,0.003,0.004,0.009,0.010,0.015,0.017,0.018,0.018,0.018,0.020,0.021,0.020,0.020,0.021,0.022,0.021,0.021},{ 0.001,0.005,0.008,0.012,0.014,0.015,0.017,0.017,0.017,0.017,0.018,0.018,0.017,0.017,0.018,0.018,0.017,0.017,0.018,0.017},{ 0.014,0.012,0.011,0.011,0.011,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010,0.010}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff_err[rad_index][mom_index];
  else
    return 0;
};
