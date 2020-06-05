// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC e trigger cut on Q2=1 curve on slide 5
// FAEC e trigger cut R edge 90,105,115,130,150,200,230 cm
// FAEC e trigger cut P value 5,4,3,2,1,2 GeV
// LAEC e trigger cut P>3GeV on slide 3

double large_electron_trigger_low_R[3]={90,105,115};
double large_electron_trigger_high_R[3]={105,115,150};

double large_electron_trigger_low_P[20]={1.575,	1.725,	1.875,	2.025,	2.175,	2.325,	2.475,	2.625,	2.775,	2.925,	3.075,	3.225,	3.375,	3.525,	3.675,	3.825,	3.975,	4.125,	4.275, 4.425};
double large_electron_trigger_high_P[20]={1.725,1.875,	2.025,	2.175,	2.325,	2.475,	2.625,	2.775,	2.925,	3.075,	3.225,	3.375,	3.525,	3.675,	3.825,	3.975,	4.125,	4.275,	4.425, 4.575};

double large_electron_trigger_e_low_eff[3][20]= { 
{ 0.006,0.001,0.012,0.007,0.021,0.076,0.318,0.624,0.855,0.938,0.977,0.981,0.990,0.995,0.989,0.991,0.995,0.999,0.997,0.996},{ 0.007,0.000,0.004,0.013,0.009,0.056,0.258,0.598,0.843,0.944,0.986,0.980,0.986,0.991,0.997,0.996,0.995,0.995,0.995,0.996},{ 0.001,0.002,0.003,0.009,0.032,0.138,0.344,0.553,0.703,0.763,0.816,0.838,0.858,0.870,0.888,0.897,0.910,0.907,0.914,0.939}
};

/*double large_electron_trigger_e_low_eff[3][20]= {
{ 0.006,0.001,0.012,0.007,0.021,0.076,0.318,0.624,0.855,0.938,0.977,0.981,0.990,0.995,0.989,0.991,0.995,0.999,0.997,0.996},{ 0.007,0.000,0.004,0.013,0.009,0.056,0.258,0.598,0.843,0.944,0.986,0.980,0.986,0.991,0.997,0.996,0.995,0.995,0.995,0.996},{ 0.007,0.000,0.004,0.013,0.009,0.056,0.258,0.598,0.843,0.944,0.986,0.980,0.986,0.991,0.997,0.996,0.995,0.995,0.995,0.996}};*/



double large_electron_trigger_e_high_eff[3][20]={ 
{ 0.001,0.013,0.007,0.022,0.083,0.341,0.639,0.862,0.939,0.979,0.980,0.991,0.994,0.990,0.991,0.995,0.999,0.996,0.997,0.998},{ 0.000,0.004,0.013,0.011,0.058,0.276,0.611,0.850,0.950,0.988,0.980,0.984,0.992,0.997,0.996,0.995,0.995,0.994,0.997,1.000},{ 0.002,0.003,0.009,0.033,0.154,0.355,0.562,0.703,0.764,0.822,0.834,0.860,0.872,0.894,0.894,0.909,0.912,0.911,0.945,0.925}
};

/*double large_electron_trigger_e_high_eff[3][20]={
{ 0.001,0.013,0.007,0.022,0.083,0.341,0.639,0.862,0.939,0.979,0.980,0.991,0.994,0.990,0.991,0.995,0.999,0.996,0.997,0.998},{ 0.000,0.004,0.013,0.011,0.058,0.276,0.611,0.850,0.950,0.988,0.980,0.984,0.992,0.997,0.996,0.995,0.995,0.994,0.997,1.000},{ 0.000,0.004,0.013,0.011,0.058,0.276,0.611,0.850,0.950,0.988,0.980,0.984,0.992,0.997,0.996,0.995,0.995,0.994,0.997,1.000}};*/

double large_electron_trigger_pi_low_eff[3][20]={ 
{ 0.003,0.001,0.000,0.002,0.005,0.010,0.015,0.016,0.021,0.034,0.057,0.070,0.104,0.096,0.152,0.174,0.200,0.225,0.184,0.217},{ 0.000,0.001,0.001,0.001,0.003,0.001,0.010,0.016,0.029,0.050,0.061,0.076,0.085,0.109,0.132,0.175,0.190,0.201,0.231,0.230},{ 0.002,0.000,0.000,0.002,0.003,0.007,0.011,0.012,0.016,0.033,0.026,0.052,0.052,0.070,0.075,0.100,0.122,0.121,0.125,0.142}
};

/*double large_electron_trigger_pi_low_eff[3][20]={
{ 0.003,0.001,0.000,0.002,0.005,0.010,0.015,0.016,0.021,0.034,0.057,0.070,0.104,0.096,0.152,0.174,0.200,0.225,0.184,0.217},{ 0.000,0.001,0.001,0.001,0.003,0.001,0.010,0.016,0.029,0.050,0.061,0.076,0.085,0.109,0.132,0.175,0.190,0.201,0.231,0.230},{ 0.000,0.001,0.001,0.001,0.003,0.001,0.010,0.016,0.029,0.050,0.061,0.076,0.085,0.109,0.132,0.175,0.190,0.201,0.231,0.230}};*/


double large_electron_trigger_pi_high_eff[3][20]=  { 
{ 0.001,0.000,0.002,0.004,0.011,0.016,0.016,0.022,0.033,0.060,0.073,0.099,0.096,0.160,0.176,0.196,0.226,0.187,0.214,0.226},{ 0.001,0.001,0.001,0.003,0.001,0.010,0.020,0.029,0.049,0.060,0.076,0.091,0.108,0.133,0.175,0.190,0.198,0.242,0.224,0.244},{ 0.000,0.001,0.001,0.004,0.007,0.011,0.013,0.016,0.034,0.027,0.051,0.053,0.073,0.078,0.100,0.121,0.122,0.125,0.140,0.145},
};

/*double large_electron_trigger_pi_high_eff[3][20]=  {
{ 0.001,0.000,0.002,0.004,0.011,0.016,0.016,0.022,0.033,0.060,0.073,0.099,0.096,0.160,0.176,0.196,0.226,0.187,0.214,0.226},{ 0.001,0.001,0.001,0.003,0.001,0.010,0.020,0.029,0.049,0.060,0.076,0.091,0.108,0.133,0.175,0.190,0.198,0.242,0.224,0.244},{ 0.001,0.001,0.001,0.003,0.001,0.010,0.020,0.029,0.049,0.060,0.076,0.091,0.108,0.133,0.175,0.190,0.198,0.242,0.224,0.244}};*/


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
			
			for(int Pj=0;Pj<=19;Pj++){
				if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=large_electron_trigger_high_P[19]){
				P_index=19;
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
			
			for(int Pj=0;Pj<=19;Pj++){
				if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=large_electron_trigger_high_P[19]){
				P_index=19;
			}
		
			//now get R_index and P_index

			//e_eff=0.5*(large_electron_trigger_pi_low_eff[R_index][P_index]+large_electron_trigger_pi_high_eff[R_index][P_index] );
			 e_eff=(large_electron_trigger_pi_high_eff[R_index][P_index] - large_electron_trigger_pi_low_eff[R_index][P_index]  )/( large_electron_trigger_high_P[P_index] -  large_electron_trigger_low_P[P_index]) * (hit_E- large_electron_trigger_low_P[P_index]) + large_electron_trigger_pi_low_eff[R_index][P_index] ;
		
		}
	}
	return e_eff;
}
		
