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
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.102,0.610,0.968,0.977,0.992,1.000,1.000,0.986,0.993,1.000,},{ 0.000,0.000,0.000,0.000,0.003,0.009,0.006,0.146,0.779,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,},{ 0.001,0.000,0.002,0.002,0.051,0.572,0.959,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.002,0.003,0.335,0.950,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.948,0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.080,0.332,0.526,0.707,0.749,0.832,0.877,0.876,0.926,0.935,0.943,0.953,0.964,0.963,0.963,0.968,0.961,0.967,0.966,0.963}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.102,0.612,0.961,0.977,0.992,1.000,1.000,0.986,0.993,1.000,1.000,},{ 0.000,0.000,0.000,0.003,0.009,0.006,0.146,0.779,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,1.000,},{ 0.000,0.002,0.002,0.051,0.572,0.959,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.004,0.334,0.950,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.994,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,},{ 0.332,0.526,0.707,0.749,0.833,0.877,0.876,0.926,0.935,0.943,0.953,0.963,0.963,0.964,0.968,0.961,0.967,0.966,0.963,0.963}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.024,0.032,0.048,0.035,0.139,0.133,0.145,0.193},{ 0.000,0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.012,0.014,0.033,0.093,0.102,0.155,0.134,0.210,0.215,0.272,0.252,0.266},{ 0.000,0.000,0.001,0.000,0.000,0.013,0.046,0.062,0.155,0.181,0.207,0.217,0.245,0.266,0.328,0.366,0.347,0.346,0.369,0.453},{ 0.002,0.005,0.037,0.094,0.154,0.232,0.292,0.335,0.356,0.400,0.387,0.445,0.431,0.433,0.474,0.458,0.504,0.510,0.511,0.475},{ 0.333,0.385,0.429,0.485,0.515,0.544,0.537,0.559,0.560,0.564,0.566,0.558,0.558,0.560,0.571,0.571,0.580,0.563,0.568,0.581}
};

double forward_electron_trigger_pi_high_eff[6][20]= { 
{ 0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.024,0.032,0.048,0.035,0.139,0.133,0.145,0.193,0.193,},{ 0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.012,0.014,0.033,0.093,0.102,0.155,0.134,0.210,0.215,0.273,0.252,0.265,0.289,},{ 0.000,0.001,0.000,0.000,0.013,0.046,0.062,0.155,0.181,0.205,0.219,0.245,0.266,0.328,0.366,0.345,0.347,0.368,0.453,0.391,},{ 0.005,0.037,0.094,0.154,0.230,0.293,0.333,0.356,0.400,0.387,0.445,0.431,0.431,0.473,0.459,0.505,0.511,0.510,0.476,0.481,},{ 0.385,0.429,0.485,0.514,0.544,0.538,0.558,0.560,0.563,0.566,0.559,0.558,0.560,0.570,0.571,0.580,0.563,0.568,0.580,0.580}
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
		
