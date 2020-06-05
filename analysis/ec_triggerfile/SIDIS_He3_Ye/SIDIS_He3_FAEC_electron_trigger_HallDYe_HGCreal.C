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
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.331,0.870,0.984,0.985,0.992,1.000,1.000,0.986,0.993,1.000,},{ 0.000,0.000,0.000,0.000,0.003,0.009,0.012,0.330,0.900,0.991,0.991,0.993,0.997,0.994,0.997,0.994,0.991,1.000,0.997,1.000,},{ 0.002,0.000,0.002,0.002,0.100,0.758,0.981,0.994,1.000,0.996,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.003,0.007,0.459,0.979,0.993,0.999,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.891,0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.147,0.333,0.554,0.713,0.756,0.856,0.880,0.890,0.935,0.936,0.949,0.961,0.964,0.963,0.963,0.968,0.961,0.967,0.966,0.963}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.331,0.868,0.984,0.985,0.992,1.000,1.000,0.986,0.993,1.000,1.000,},{ 0.000,0.000,0.000,0.003,0.009,0.012,0.330,0.900,0.991,0.991,0.993,0.997,0.994,0.997,0.994,0.991,1.000,0.997,1.000,1.000,},{ 0.000,0.002,0.002,0.100,0.758,0.981,0.994,1.000,0.996,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.007,0.458,0.979,0.993,0.999,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.333,0.554,0.713,0.756,0.856,0.880,0.890,0.935,0.936,0.949,0.961,0.964,0.963,0.964,0.968,0.961,0.967,0.966,0.963,0.963,}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.032,0.038,0.064,0.042,0.156,0.148,0.172,0.215,},{ 0.000,0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.018,0.024,0.042,0.123,0.117,0.176,0.156,0.223,0.229,0.294,0.272,0.278,},{ 0.000,0.000,0.001,0.000,0.003,0.016,0.070,0.076,0.171,0.200,0.228,0.235,0.261,0.276,0.341,0.382,0.352,0.350,0.379,0.459,},{ 0.002,0.008,0.054,0.114,0.177,0.260,0.302,0.347,0.367,0.406,0.400,0.459,0.442,0.442,0.477,0.471,0.511,0.517,0.515,0.480,},{ 0.254,0.343,0.397,0.454,0.497,0.527,0.527,0.544,0.549,0.557,0.557,0.551,0.549,0.554,0.566,0.564,0.574,0.559,0.562,0.573,}
};

double forward_electron_trigger_pi_high_eff[6][20]= { 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.032,0.038,0.064,0.042,0.156,0.148,0.172,0.215,0.214,},{ 0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.018,0.024,0.042,0.123,0.117,0.177,0.156,0.223,0.229,0.294,0.272,0.277,0.308,},{ 0.000,0.001,0.000,0.003,0.016,0.070,0.076,0.171,0.201,0.225,0.237,0.261,0.276,0.341,0.382,0.351,0.351,0.378,0.459,0.397,},{ 0.008,0.054,0.114,0.177,0.259,0.303,0.345,0.368,0.407,0.400,0.459,0.442,0.441,0.477,0.472,0.511,0.517,0.514,0.481,0.487,},{ 0.344,0.397,0.454,0.496,0.527,0.528,0.544,0.549,0.557,0.557,0.551,0.548,0.555,0.566,0.564,0.574,0.560,0.562,0.572,0.578,}
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
		
