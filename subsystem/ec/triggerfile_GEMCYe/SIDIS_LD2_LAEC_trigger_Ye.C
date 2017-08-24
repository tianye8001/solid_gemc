
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
  Double_t trig_ele_eff[4][20] = { { 0.014,0.016,0.024,0.340,0.904,0.988,0.994,0.996,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,0.999,1.000},{ 0.013,0.012,0.023,0.287,0.891,0.992,0.993,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.017,0.016,0.018,0.170,0.672,0.888,0.927,0.953,0.959,0.964,0.973,0.974,0.972,0.974,0.981,0.979,0.980,0.983,0.986,0.988},{ 0.014,0.016,0.021,0.256,0.781,0.912,0.935,0.945,0.953,0.954,0.962,0.962,0.962,0.967,0.967,0.964,0.967,0.966,0.970,0.974,}}; 
  if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetElectronTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_ele_eff_err[4][20] = { { 0.002,0.002,0.003,0.009,0.006,0.002,0.001,0.001,0.001,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.001,0.000},{ 0.003,0.002,0.003,0.010,0.007,0.002,0.002,0.001,0.001,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000},{ 0.003,0.003,0.003,0.008,0.010,0.007,0.005,0.004,0.004,0.004,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.002,0.002},{ 0.001,0.001,0.002,0.005,0.005,0.003,0.003,0.003,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_ele_eff_err[rad_index][mom_index];
  else
    return 0;  
};

Double_t GetPionTriggerEffi(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff[4][20] = { { 0.015,0.016,0.014,0.023,0.058,0.096,0.164,0.211,0.275,0.285,0.335,0.349,0.367,0.393,0.397,0.432,0.428,0.427,0.448,0.454},{ 0.013,0.012,0.011,0.027,0.064,0.106,0.164,0.221,0.280,0.301,0.332,0.341,0.374,0.386,0.405,0.415,0.444,0.445,0.454,0.462},{ 0.015,0.015,0.013,0.019,0.034,0.057,0.087,0.128,0.170,0.194,0.210,0.216,0.233,0.272,0.273,0.294,0.302,0.323,0.329,0.357},{ 0.014,0.014,0.013,0.021,0.048,0.082,0.128,0.173,0.223,0.241,0.274,0.280,0.305,0.326,0.335,0.358,0.367,0.371,0.387,0.398}};  
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff[rad_index][mom_index];
  else
    return 0;
};

Double_t GetPionTriggerEffiError(Int_t rad_index, Int_t mom_index){
  Double_t trig_pi_eff_err[7][20] = { { 0.002,0.002,0.002,0.003,0.005,0.006,0.007,0.008,0.009,0.009,0.009,0.009,0.009,0.009,0.010,0.010,0.010,0.010,0.010,0.010},{ 0.003,0.002,0.002,0.004,0.006,0.007,0.008,0.010,0.010,0.010,0.011,0.011,0.011,0.011,0.011,0.011,0.012,0.011,0.011,0.011},{ 0.003,0.003,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.008,0.008,0.008,0.009,0.009,0.009,0.010,0.009,0.010,0.010,0.010},{ 0.001,0.001,0.001,0.002,0.002,0.003,0.004,0.004,0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005}};
  if (rad_index!= -1 && mom_index!=-1)
    return trig_pi_eff_err[rad_index][mom_index];
  else
    return 0;
};
