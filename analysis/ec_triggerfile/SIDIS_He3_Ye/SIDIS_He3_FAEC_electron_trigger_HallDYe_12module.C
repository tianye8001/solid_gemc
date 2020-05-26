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
{ 0.000,0.004,0.000,0.000,0.000,0.008,0.000,0.008,0.008,0.007,0.142,0.642,0.976,0.977,0.992,1.000,1.000,0.986,0.993,1.000},{ 0.000,0.000,0.000,0.003,0.003,0.003,0.009,0.156,0.776,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000},{ 0.004,0.003,0.000,0.006,0.061,0.614,0.961,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.005,0.010,0.358,0.955,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.864,0.993,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.005,0.010,0.358,0.955,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000}
};

double forward_electron_trigger_e_high_eff[6][20]={ 

{ 0.004,0.000,0.000,0.000,0.008,0.000,0.008,0.008,0.007,0.142,0.645,0.969,0.977,0.992,1.000,1.000,0.986,0.993,1.000,1.000},{ 0.000,0.000,0.003,0.003,0.003,0.009,0.156,0.776,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,1.000},{ 0.003,0.000,0.006,0.061,0.614,0.961,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.011,0.357,0.955,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.993,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.011,0.357,0.955,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000}

};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.002,0.002,0.000,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.020,0.018,0.035,0.027,0.096,0.104,0.117,0.150},{ 0.000,0.000,0.002,0.003,0.000,0.006,0.003,0.000,0.009,0.017,0.036,0.103,0.114,0.155,0.138,0.206,0.223,0.275,0.256,0.269},{ 0.002,0.000,0.001,0.002,0.010,0.016,0.049,0.070,0.155,0.183,0.207,0.223,0.255,0.270,0.333,0.372,0.341,0.348,0.369,0.451},{ 0.004,0.005,0.037,0.102,0.160,0.238,0.292,0.337,0.361,0.397,0.388,0.451,0.438,0.438,0.476,0.458,0.509,0.514,0.510,0.478},{ 0.175,0.312,0.386,0.455,0.490,0.525,0.518,0.541,0.544,0.551,0.555,0.553,0.543,0.553,0.561,0.562,0.574,0.558,0.561,0.570},{ 0.004,0.005,0.037,0.102,0.160,0.238,0.292,0.337,0.361,0.397,0.388,0.451,0.438,0.438,0.476,0.458,0.509,0.514,0.510,0.478}
};

double forward_electron_trigger_pi_high_eff[6][20]= {
{ 0.002,0.000,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.007,0.020,0.018,0.035,0.027,0.096,0.104,0.117,0.150,0.158},{ 0.000,0.002,0.003,0.000,0.006,0.003,0.000,0.009,0.017,0.036,0.103,0.114,0.155,0.137,0.206,0.223,0.276,0.256,0.268,0.296},{ 0.000,0.001,0.002,0.010,0.016,0.050,0.070,0.155,0.183,0.205,0.225,0.255,0.270,0.333,0.372,0.340,0.349,0.368,0.451,0.391},{ 0.005,0.037,0.102,0.160,0.237,0.293,0.336,0.362,0.398,0.388,0.451,0.438,0.436,0.476,0.459,0.510,0.515,0.509,0.479,0.483},{ 0.313,0.385,0.456,0.489,0.526,0.519,0.540,0.545,0.550,0.555,0.553,0.542,0.553,0.561,0.561,0.574,0.559,0.562,0.569,0.575},{ 0.005,0.037,0.102,0.160,0.237,0.293,0.336,0.362,0.398,0.388,0.451,0.438,0.436,0.476,0.459,0.510,0.515,0.509,0.479,0.483}
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
		
