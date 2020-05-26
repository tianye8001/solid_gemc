// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC e trigger cut on Q2=1 curve on slide 5
// FAEC e trigger cut R edge 90,105,115,130,150,200,230 cm
// FAEC e trigger cut P value 5,4,3,2,1,2 GeV
// LAEC e trigger cut P>3GeV on slide 3

double forward_electron_trigger_low_R[6]={90,105,115,130,150,200};
double forward_electron_trigger_high_R[6]={105,115,130,150,200,270};


double forward_electron_trigger_low_P[20]={0.833333,	1.16667,	1.5,	1.83333,	2.16667,	2.5,	2.83333,	3.16667,	3.5,	3.83333,	4.16667,	4.5,	4.83333,	5.16667,	5.5,	5.83333,	6.16667,	6.5,	6.83333,    7.16667};

double forward_electron_trigger_high_P[20]={1.16667,	1.5,	1.83333,	2.16667,	2.5,	2.83333,	3.16667,	3.5,	3.83333,	4.16667,	4.5,	4.83333,	5.16667,	5.5,	5.83333,	6.16667,	6.5,	6.83333,    7.16667,	7.5};

double forward_electron_trigger_e_low_eff[6][20]={  { 0.000,0.000,0.000,0.006,0.000,0.000,0.000,0.008,0.008,0.000,0.110,0.602,0.968,0.969,0.992,1.000,1.000,0.986,0.993,1.000,},{ 0.002,0.004,0.000,0.003,0.000,0.006,0.009,0.152,0.769,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,},{ 0.002,0.000,0.005,0.003,0.039,0.589,0.961,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.000,0.003,0.342,0.948,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.963,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.082,0.333,0.528,0.707,0.747,0.834,0.878,0.877,0.926,0.935,0.943,0.953,0.964,0.963,0.963,0.968,0.961,0.967,0.966,0.963,}
};

double forward_electron_trigger_e_high_eff[6][20]={  { 0.000,0.000,0.006,0.000,0.000,0.000,0.008,0.008,0.000,0.110,0.603,0.961,0.969,0.992,1.000,1.000,0.986,0.993,1.000,1.000,},{ 0.004,0.000,0.003,0.000,0.006,0.009,0.152,0.769,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,1.000,},{ 0.000,0.005,0.003,0.039,0.589,0.961,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.003,0.341,0.948,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.333,0.528,0.707,0.747,0.834,0.878,0.877,0.926,0.935,0.943,0.953,0.963,0.963,0.964,0.968,0.961,0.967,0.966,0.963,0.963,}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.024,0.019,0.048,0.035,0.139,0.133,0.138,0.193,},{ 0.000,0.000,0.002,0.000,0.006,0.000,0.000,0.003,0.006,0.020,0.030,0.093,0.105,0.151,0.134,0.203,0.215,0.269,0.262,0.263,},{ 0.001,0.000,0.000,0.005,0.002,0.013,0.046,0.066,0.155,0.183,0.207,0.217,0.246,0.268,0.328,0.370,0.343,0.348,0.371,0.451,},{ 0.001,0.005,0.040,0.100,0.152,0.234,0.289,0.335,0.356,0.397,0.388,0.447,0.433,0.432,0.475,0.458,0.504,0.510,0.506,0.475,},{ 0.370,0.409,0.457,0.509,0.531,0.555,0.549,0.569,0.565,0.573,0.575,0.567,0.564,0.566,0.574,0.575,0.585,0.567,0.573,0.582,}
};

double forward_electron_trigger_pi_high_eff[6][20]= { 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.024,0.019,0.048,0.035,0.139,0.133,0.138,0.193,0.193,},{ 0.000,0.002,0.000,0.006,0.000,0.000,0.003,0.006,0.020,0.030,0.093,0.105,0.152,0.134,0.203,0.215,0.270,0.262,0.262,0.289,},{ 0.000,0.000,0.005,0.002,0.013,0.046,0.066,0.155,0.183,0.205,0.219,0.246,0.268,0.328,0.370,0.342,0.349,0.370,0.451,0.389,},{ 0.005,0.040,0.100,0.152,0.233,0.291,0.333,0.356,0.398,0.388,0.447,0.434,0.430,0.474,0.459,0.505,0.511,0.505,0.476,0.481,},{ 0.409,0.457,0.509,0.530,0.555,0.550,0.568,0.566,0.573,0.575,0.567,0.563,0.567,0.574,0.575,0.585,0.567,0.573,0.581,0.585,}
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
		
