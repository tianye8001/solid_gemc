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
{ 0.000,0.000,0.000,0.006,0.000,0.000,0.000,0.008,0.017,0.065,0.583,0.935,0.984,0.992,0.992,1.000,1.000,0.986,0.993,1.000,},{ 0.004,0.004,0.000,0.003,0.000,0.009,0.032,0.543,0.956,0.997,0.991,0.997,0.997,0.994,0.997,0.997,0.994,1.000,0.997,1.000,},{ 0.004,0.001,0.005,0.011,0.218,0.856,0.987,0.994,1.000,0.996,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.002,0.020,0.589,0.990,0.993,0.999,1.000,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.923,0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.153,0.337,0.584,0.718,0.772,0.868,0.883,0.907,0.940,0.939,0.957,0.963,0.964,0.963,0.963,0.968,0.962,0.967,0.966,0.963}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.000,0.000,0.006,0.000,0.000,0.000,0.008,0.017,0.065,0.583,0.934,0.984,0.992,0.992,1.000,1.000,0.986,0.993,1.000,1.000,},{ 0.004,0.000,0.003,0.000,0.009,0.032,0.543,0.956,0.997,0.991,0.997,0.997,0.994,0.997,0.997,0.994,1.000,0.997,1.000,1.000,},{ 0.001,0.005,0.011,0.218,0.856,0.987,0.994,1.000,0.996,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.020,0.588,0.990,0.993,0.999,1.000,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.337,0.584,0.717,0.772,0.868,0.883,0.907,0.940,0.939,0.957,0.963,0.964,0.963,0.964,0.968,0.962,0.967,0.966,0.963,0.963}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.015,0.014,0.056,0.044,0.072,0.056,0.172,0.172,0.186,0.215,},{ 0.000,0.000,0.002,0.000,0.006,0.000,0.000,0.006,0.032,0.027,0.057,0.133,0.145,0.194,0.169,0.230,0.240,0.306,0.282,0.294,},{ 0.001,0.000,0.000,0.006,0.012,0.029,0.072,0.100,0.187,0.222,0.248,0.249,0.272,0.297,0.366,0.395,0.360,0.378,0.386,0.461,},{ 0.001,0.009,0.065,0.126,0.206,0.282,0.331,0.357,0.379,0.414,0.418,0.463,0.452,0.452,0.485,0.479,0.517,0.526,0.516,0.485,},{ 0.285,0.360,0.411,0.469,0.503,0.536,0.534,0.552,0.554,0.560,0.560,0.554,0.554,0.557,0.565,0.567,0.578,0.560,0.567,0.576,}
};

double forward_electron_trigger_pi_high_eff[6][20]= { 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.008,0.015,0.014,0.056,0.044,0.072,0.056,0.172,0.172,0.186,0.215,0.221,},{ 0.000,0.002,0.000,0.006,0.000,0.000,0.006,0.032,0.027,0.057,0.133,0.145,0.195,0.168,0.230,0.240,0.307,0.282,0.293,0.318,},{ 0.000,0.000,0.006,0.012,0.029,0.072,0.100,0.187,0.222,0.246,0.251,0.272,0.297,0.366,0.395,0.359,0.379,0.386,0.461,0.407,},{ 0.009,0.064,0.126,0.206,0.281,0.333,0.356,0.379,0.414,0.418,0.463,0.453,0.450,0.484,0.480,0.518,0.527,0.515,0.486,0.489,},{ 0.361,0.410,0.469,0.503,0.536,0.535,0.551,0.555,0.560,0.560,0.554,0.553,0.558,0.565,0.567,0.578,0.561,0.567,0.575,0.579}
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
		
