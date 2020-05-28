// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC e trigger cut on Q2=1 curve on slide 5
// FAEC e trigger cut R edge 90,105,115,130,150,200,230 cm
// FAEC e trigger cut P value 5,4,3,2,1,2 GeV
// LAEC e trigger cut P>3GeV on slide 3

double forward_electron_trigger_low_R[6]={90,105,115,130,150,200};
double forward_electron_trigger_high_R[6]={105,115,130,150,200,270};


double forward_electron_trigger_low_P[20]={0.833333,	1.16667,	1.5,	1.83333,	2.16667,	2.5,	2.83333,	3.16667,	3.5,	3.83333,	4.16667,	4.5,	4.83333,	5.16667,	5.5,	5.83333,	6.16667,	6.5,	6.83333,    7.16667};

double forward_electron_trigger_high_P[20]={1.16667,	1.5,	1.83333,	2.16667,	2.5,	2.83333,	3.16667,	3.5,	3.83333,	4.16667,	4.5,	4.83333,	5.16667,	5.5,	5.83333,	6.16667,	6.5,	6.83333,    7.16667,	7.5};

double forward_electron_trigger_e_low_eff[6][20]={ 
 { 0.000,0.005,0.000,0.000,0.000,0.033,0.048,0.033,0.051,0.029,0.108,0.598,0.880,0.874,0.944,0.935,0.893,0.892,0.902,0.943,},{ 0.000,0.000,0.000,0.023,0.039,0.043,0.027,0.161,0.787,0.956,0.976,0.990,0.994,0.994,1.000,0.987,0.987,1.000,0.997,1.000,},{ 0.000,0.004,0.003,0.011,0.058,0.594,0.964,0.994,0.993,0.990,0.993,0.994,1.000,1.000,0.998,1.000,1.000,0.998,1.000,1.000,},{ 0.002,0.014,0.348,0.952,0.992,0.995,0.993,0.996,0.997,0.997,1.000,0.999,0.996,0.999,1.000,0.999,0.997,1.000,0.999,1.000,},{ 0.863,0.992,0.995,0.996,0.998,0.999,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,0.999,1.000,1.000,1.000,},{ 0.142,0.339,0.528,0.712,0.753,0.839,0.880,0.879,0.927,0.933,0.942,0.952,0.960,0.959,0.961,0.965,0.958,0.964,0.962,0.961,}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.005,0.000,0.000,0.000,0.033,0.048,0.033,0.051,0.029,0.108,0.600,0.874,0.874,0.943,0.935,0.893,0.892,0.902,0.943,0.949,},{ 0.000,0.000,0.023,0.039,0.043,0.027,0.161,0.787,0.956,0.976,0.990,0.994,0.994,1.000,0.987,0.987,1.000,0.997,1.000,1.000,},{ 0.004,0.003,0.011,0.058,0.594,0.964,0.994,0.993,0.990,0.993,0.994,1.000,1.000,0.998,1.000,1.000,0.998,1.000,1.000,0.998,},{ 0.014,0.347,0.952,0.992,0.995,0.993,0.996,0.997,0.997,1.000,0.999,0.996,0.999,1.000,0.999,0.997,1.000,0.999,1.000,0.999,},{ 0.992,0.995,0.996,0.998,0.999,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,0.999,1.000,1.000,1.000,1.000,},{ 0.339,0.528,0.711,0.753,0.839,0.880,0.879,0.927,0.933,0.942,0.952,0.960,0.959,0.962,0.965,0.958,0.964,0.962,0.961,0.961,}

};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.022,0.026,0.027,0.070,0.030,0.117,0.114,0.128,0.209,},{ 0.002,0.003,0.000,0.000,0.003,0.000,0.003,0.006,0.024,0.032,0.047,0.106,0.116,0.182,0.140,0.210,0.229,0.302,0.271,0.282,},{ 0.000,0.002,0.000,0.000,0.005,0.020,0.058,0.080,0.175,0.206,0.242,0.237,0.269,0.278,0.352,0.378,0.352,0.347,0.372,0.459,},{ 0.003,0.005,0.055,0.105,0.180,0.254,0.320,0.351,0.368,0.409,0.398,0.448,0.442,0.443,0.473,0.461,0.515,0.520,0.512,0.478,},{ 0.267,0.345,0.408,0.453,0.499,0.534,0.529,0.550,0.552,0.556,0.556,0.553,0.547,0.551,0.566,0.566,0.573,0.557,0.563,0.572,},{ 0.028,0.124,0.188,0.243,0.304,0.346,0.364,0.384,0.400,0.417,0.414,0.430,0.428,0.436,0.459,0.462,0.472,0.472,0.478,0.487,}

};

double forward_electron_trigger_pi_high_eff[6][20]= {
 { 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.022,0.026,0.027,0.070,0.030,0.117,0.114,0.128,0.209,0.194,},{ 0.003,0.000,0.000,0.003,0.000,0.003,0.006,0.024,0.032,0.047,0.106,0.116,0.183,0.139,0.210,0.229,0.303,0.271,0.281,0.312,},{ 0.002,0.000,0.000,0.005,0.020,0.058,0.080,0.175,0.206,0.239,0.238,0.269,0.278,0.352,0.378,0.351,0.348,0.373,0.458,0.398,},{ 0.005,0.055,0.106,0.180,0.253,0.321,0.349,0.368,0.409,0.398,0.448,0.443,0.442,0.472,0.462,0.515,0.521,0.511,0.479,0.481,},{ 0.346,0.407,0.453,0.499,0.534,0.530,0.550,0.552,0.556,0.556,0.554,0.546,0.552,0.566,0.566,0.573,0.558,0.564,0.571,0.578,},{ 0.123,0.188,0.243,0.304,0.346,0.364,0.383,0.400,0.417,0.414,0.431,0.428,0.436,0.458,0.462,0.472,0.472,0.478,0.486,0.489,}
};




double get_forward_electron_trigger_e_eff(double hit_R, double hit_E){
	double e_eff=0; //return value

	int R_index=-1;
	int P_index=-1;
	
	if(hit_R<forward_electron_trigger_low_R[0] || hit_R>forward_electron_trigger_high_R[5]){
		e_eff=0;
	}else{
		//get R_index
		for(int Ri=0;Ri<6;Ri++){
			if(hit_R>=forward_electron_trigger_low_R[Ri] && hit_R<forward_electron_trigger_high_R[Ri]){
				R_index=Ri;
			}
		}
		//cout<<" R index: "<<R_index<<endl;

		if(hit_E<forward_electron_trigger_low_P[0]){
			e_eff=0;
		}else{
			//get P index
			
			for(int Pj=0;Pj<=19;Pj++){
				if(hit_E>=forward_electron_trigger_low_P[Pj] && hit_E<forward_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=forward_electron_trigger_high_P[19]){
				P_index=19;
			}

			//cout<<" P index: "<<P_index<<endl;
		
			//now get R_index and P_index

			//e_eff=0.5*(forward_electron_trigger_e_low_eff[R_index][P_index]+forward_electron_trigger_e_high_eff[R_index][P_index] );
			 e_eff=(forward_electron_trigger_e_high_eff[R_index][P_index] - forward_electron_trigger_e_low_eff[R_index][P_index]  )/( forward_electron_trigger_high_P[P_index] -  forward_electron_trigger_low_P[P_index]) * (hit_E- forward_electron_trigger_low_P[P_index]) + forward_electron_trigger_e_low_eff[R_index][P_index] ;
		
		}
	}
	return e_eff;
}
		
double get_forward_electron_trigger_pi_eff(double hit_R, double hit_E){
	double e_eff=0; //return value

	int R_index=-1;
	int P_index=-1;
	if(hit_R<forward_electron_trigger_low_R[0] || hit_R>forward_electron_trigger_high_R[5]){
		e_eff=0;
	}else{
		//get R_index
		for(int Ri=0;Ri<6;Ri++){
			if(hit_R>=forward_electron_trigger_low_R[Ri] && hit_R<forward_electron_trigger_high_R[Ri]){
				R_index=Ri;
			}
		}

		if(hit_E<forward_electron_trigger_low_P[0]){
			e_eff=0;
		}else{
			//get P index
			
			for(int Pj=0;Pj<=19;Pj++){
				if(hit_E>=forward_electron_trigger_low_P[Pj] && hit_E<forward_electron_trigger_high_P[Pj]){
					P_index=Pj;
				}
			}

			if(hit_E>=forward_electron_trigger_high_P[19]){
				P_index=19;
			}
		
			//now get R_index and P_index

			//e_eff=0.5*(forward_electron_trigger_pi_low_eff[R_index][P_index]+forward_electron_trigger_pi_high_eff[R_index][P_index] );
			 e_eff=(forward_electron_trigger_pi_high_eff[R_index][P_index] - forward_electron_trigger_pi_low_eff[R_index][P_index]  )/( forward_electron_trigger_high_P[P_index] -  forward_electron_trigger_low_P[P_index]) * (hit_E- forward_electron_trigger_low_P[P_index]) + forward_electron_trigger_pi_low_eff[R_index][P_index] ;
		
		}
	}
	return e_eff;
}
		
