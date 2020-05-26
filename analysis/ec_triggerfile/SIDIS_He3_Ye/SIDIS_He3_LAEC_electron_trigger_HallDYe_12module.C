// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC e trigger cut on Q2=1 curve on slide 5
// FAEC e trigger cut R edge 90,105,115,130,150,200,230 cm
// FAEC e trigger cut P value 5,4,3,2,1,2 GeV
// LAEC e trigger cut P>3GeV on slide 3

double large_electron_trigger_low_R[3]={80,105,115};
double large_electron_trigger_high_R[3]={105,115,140};

double large_electron_trigger_low_P[24]={1.575,	1.725,	1.875,	2.025,	2.175,	2.325,	2.475,	2.625,	2.775,	2.925,	3.075,	3.225,	3.375,	3.525,	3.675,	3.825,	3.975,	4.125,	4.275, 4.425,4.575,4.725,4.875,5.025};
double large_electron_trigger_high_P[24]={1.725,1.875,	2.025,	2.175,	2.325,	2.475,	2.625,	2.775,	2.925,	3.075,	3.225,	3.375,	3.525,	3.675,	3.825,	3.975,	4.125,	4.275,	4.425, 4.575,4.725,4.875,5.025,5.175};

/*double large_electron_trigger_e_low_eff[3][20]= { 
{ 0.006,0.001,0.012,0.007,0.021,0.076,0.318,0.624,0.855,0.938,0.977,0.981,0.990,0.995,0.989,0.991,0.995,0.999,0.997,0.996},{ 0.007,0.000,0.004,0.013,0.009,0.056,0.258,0.598,0.843,0.944,0.986,0.980,0.986,0.991,0.997,0.996,0.995,0.995,0.995,0.996},{ 0.001,0.002,0.003,0.009,0.032,0.138,0.344,0.553,0.703,0.763,0.816,0.838,0.858,0.870,0.888,0.897,0.910,0.907,0.914,0.939}
};*/

double large_electron_trigger_e_low_eff[3][24]= {
{ 0.010,0.017,0.016,0.018,0.036,0.118,0.402,0.684,0.881,0.947,0.979,0.980,0.992,0.997,0.990,0.993,0.996,1.000,0.998,0.999,0.999,1.000,1.000,0.999},{ 0.008,0.012,0.011,0.011,0.027,0.085,0.308,0.662,0.863,0.958,0.988,0.984,0.983,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000},{ 0.008,0.012,0.011,0.011,0.027,0.085,0.308,0.662,0.863,0.958,0.988,0.984,0.983,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000}
};
/*double large_electron_trigger_e_high_eff[3][20]={ 
{ 0.001,0.013,0.007,0.022,0.083,0.341,0.639,0.862,0.939,0.979,0.980,0.991,0.994,0.990,0.991,0.995,0.999,0.996,0.997,0.998},{ 0.000,0.004,0.013,0.011,0.058,0.276,0.611,0.850,0.950,0.988,0.980,0.984,0.992,0.997,0.996,0.995,0.995,0.994,0.997,1.000},{ 0.002,0.003,0.009,0.033,0.154,0.355,0.562,0.703,0.764,0.822,0.834,0.860,0.872,0.894,0.894,0.909,0.912,0.911,0.945,0.925}
};*/

double large_electron_trigger_e_high_eff[3][24]={
{ 0.014,0.017,0.019,0.038,0.121,0.421,0.696,0.882,0.949,0.983,0.980,0.992,0.996,0.990,0.993,0.996,1.000,0.998,0.999,0.999,1.000,1.000,0.999,1.000},{ 0.011,0.011,0.012,0.030,0.084,0.323,0.680,0.868,0.961,0.987,0.984,0.984,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000,1.000},{ 0.011,0.011,0.012,0.030,0.084,0.323,0.680,0.868,0.961,0.987,0.984,0.984,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000,1.000}
};
/*double large_electron_trigger_pi_low_eff[3][20]={ 
{ 0.003,0.001,0.000,0.002,0.005,0.010,0.015,0.016,0.021,0.034,0.057,0.070,0.104,0.096,0.152,0.174,0.200,0.225,0.184,0.217},{ 0.000,0.001,0.001,0.001,0.003,0.001,0.010,0.016,0.029,0.050,0.061,0.076,0.085,0.109,0.132,0.175,0.190,0.201,0.231,0.230},{ 0.002,0.000,0.000,0.002,0.003,0.007,0.011,0.012,0.016,0.033,0.026,0.052,0.052,0.070,0.075,0.100,0.122,0.121,0.125,0.142}
};*/

double large_electron_trigger_pi_low_eff[3][24]={

{ 0.004,0.005,0.003,0.004,0.007,0.012,0.017,0.018,0.029,0.039,0.058,0.067,0.096,0.096,0.138,0.163,0.168,0.191,0.168,0.200,0.212,0.238,0.259,0.240},{ 0.004,0.007,0.001,0.006,0.001,0.004,0.015,0.024,0.033,0.048,0.061,0.087,0.098,0.104,0.148,0.177,0.197,0.200,0.249,0.226,0.261,0.256,0.303,0.276},{ 0.004,0.007,0.001,0.006,0.001,0.004,0.015,0.024,0.033,0.048,0.061,0.087,0.098,0.104,0.148,0.177,0.197,0.200,0.249,0.226,0.261,0.256,0.303,0.276}
};
/*double large_electron_trigger_pi_high_eff[3][20]=  { 
{ 0.001,0.000,0.002,0.004,0.011,0.016,0.016,0.022,0.033,0.060,0.073,0.099,0.096,0.160,0.176,0.196,0.226,0.187,0.214,0.226},{ 0.001,0.001,0.001,0.003,0.001,0.010,0.020,0.029,0.049,0.060,0.076,0.091,0.108,0.133,0.175,0.190,0.198,0.242,0.224,0.244},{ 0.000,0.001,0.001,0.004,0.007,0.011,0.013,0.016,0.034,0.027,0.051,0.053,0.073,0.078,0.100,0.121,0.122,0.125,0.140,0.145},
};*/

double large_electron_trigger_pi_high_eff[3][24]=  {
{ 0.005,0.003,0.004,0.007,0.013,0.017,0.018,0.032,0.039,0.058,0.069,0.094,0.098,0.139,0.164,0.168,0.188,0.171,0.204,0.211,0.239,0.259,0.246,0.259},{ 0.006,0.001,0.006,0.001,0.004,0.017,0.023,0.034,0.049,0.062,0.085,0.102,0.102,0.151,0.180,0.195,0.201,0.243,0.236,0.259,0.263,0.298,0.282,0.273},{ 0.006,0.001,0.006,0.001,0.004,0.017,0.023,0.034,0.049,0.062,0.085,0.102,0.102,0.151,0.180,0.195,0.201,0.243,0.236,0.259,0.263,0.298,0.282,0.273}

};
double get_large_electron_trigger_e_eff(double hit_R, double hit_E){
	double e_eff=0; //return value

	int R_index=-1;
	int P_index=-1;
	
	if(hit_R<large_electron_trigger_low_R[0] || hit_R>large_electron_trigger_high_R[2]){
		e_eff=0;
	}else{
		//get R_index
		for(int Ri=0;Ri<3;Ri++){
			if(hit_R>=large_electron_trigger_low_R[Ri] && hit_R<large_electron_trigger_high_R[Ri]){
				R_index=Ri;
			}
		}
		//cout<<" R index: "<<R_index<<endl;

		if(hit_E<large_electron_trigger_low_P[0]){
			e_eff=0;
		}else{
			//get P index
			
			for(int Pj=0;Pj<=23;Pj++){
				if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=large_electron_trigger_high_P[23]){
				P_index=23;
			}

			//cout<<" P index: "<<P_index<<endl;
		
			//now get R_index and P_index

			//e_eff=0.5*(large_electron_trigger_e_low_eff[R_index][P_index]+large_electron_trigger_e_high_eff[R_index][P_index] );
			 e_eff=(large_electron_trigger_e_high_eff[R_index][P_index] - large_electron_trigger_e_low_eff[R_index][P_index]  )/( large_electron_trigger_high_P[P_index] -  large_electron_trigger_low_P[P_index]) * (hit_E- large_electron_trigger_low_P[P_index]) + large_electron_trigger_e_low_eff[R_index][P_index] ;
		
		}
	}
	return e_eff;
}
		
double get_large_electron_trigger_pi_eff(double hit_R, double hit_E){
	double e_eff=0; //return value

	int R_index=-1;
	int P_index=-1;
	if(hit_R<large_electron_trigger_low_R[0] || hit_R>large_electron_trigger_high_R[2]){
		e_eff=0;
	}else{
		//get R_index
		for(int Ri=0;Ri<3;Ri++){
			if(hit_R>=large_electron_trigger_low_R[Ri] && hit_R<large_electron_trigger_high_R[Ri]){
				R_index=Ri;
			}
		}

		if(hit_E<large_electron_trigger_low_P[0]){
			e_eff=0;
		}else{
			//get P index
			
			for(int Pj=0;Pj<=23;Pj++){
				if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=large_electron_trigger_high_P[23]){
				P_index=23;
			}
		
			//now get R_index and P_index

			//e_eff=0.5*(large_electron_trigger_pi_low_eff[R_index][P_index]+large_electron_trigger_pi_high_eff[R_index][P_index] );
			 e_eff=(large_electron_trigger_pi_high_eff[R_index][P_index] - large_electron_trigger_pi_low_eff[R_index][P_index]  )/( large_electron_trigger_high_P[P_index] -  large_electron_trigger_low_P[P_index]) * (hit_E- large_electron_trigger_low_P[P_index]) + large_electron_trigger_pi_low_eff[R_index][P_index] ;
		
		}
	}
	return e_eff;
}
		
