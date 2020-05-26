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
{ 0.000,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.014,0.254,0.714,0.908,0.954,0.957,0.967,0.977,0.972,0.980},{ 0.002,0.000,0.000,0.000,0.000,0.009,0.003,0.053,0.489,0.929,0.990,0.994,0.993,0.997,0.994,0.997,0.990,0.990,0.997,0.997},{ 0.000,0.001,0.000,0.003,0.017,0.413,0.918,0.986,0.998,0.996,0.998,1.000,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.001,0.004,0.245,0.901,0.992,0.998,0.999,0.997,0.999,0.999,1.000,0.999,1.000,0.999,1.000,1.000,1.000,0.999,0.997,1.000},{ 0.577,0.987,0.996,0.999,0.998,0.998,0.998,0.999,0.999,0.999,0.998,0.998,0.999,0.999,1.000,0.998,0.999,0.998,1.000,0.999},
{ 0.001,0.004,0.245,0.901,0.992,0.998,0.999,0.997,0.999,0.999,1.000,0.999,1.000,0.999,1.000,1.000,1.000,0.999,0.997,1.000}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.016,0.286,0.729,0.910,0.952,0.960,0.967,0.975,0.976,0.978,0.982},{ 0.000,0.000,0.000,0.000,0.009,0.006,0.053,0.533,0.934,0.990,0.994,0.993,0.997,0.994,0.997,0.987,0.994,0.997,0.997,1.000},{ 0.001,0.000,0.003,0.020,0.460,0.921,0.988,0.998,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.005,0.282,0.919,0.992,0.998,0.999,0.997,0.999,0.999,1.000,0.999,1.000,0.999,1.000,1.000,1.000,0.997,0.999,1.000,1.000},{ 0.991,0.996,0.999,0.998,0.998,0.998,0.999,0.999,0.998,0.999,0.998,0.999,1.000,1.000,0.999,0.999,0.998,1.000,0.999,1.000},
{ 0.005,0.282,0.919,0.992,0.998,0.999,0.997,0.999,0.999,1.000,0.999,1.000,0.999,1.000,1.000,1.000,0.997,0.999,1.000,1.000}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.002,0.010,0.016,0.016,0.040,0.031,0.100,0.096,0.107},{ 0.000,0.000,0.002,0.000,0.000,0.003,0.000,0.003,0.003,0.010,0.019,0.053,0.132,0.102,0.152,0.136,0.228,0.219,0.262,0.277},{ 0.000,0.003,0.002,0.000,0.005,0.006,0.033,0.054,0.119,0.155,0.201,0.209,0.231,0.240,0.320,0.328,0.345,0.350,0.349,0.373},{ 0.002,0.006,0.036,0.078,0.155,0.215,0.282,0.310,0.353,0.358,0.399,0.429,0.425,0.447,0.430,0.468,0.480,0.494,0.518,0.503},{ 0.163,0.305,0.370,0.446,0.473,0.518,0.523,0.541,0.534,0.544,0.557,0.539,0.550,0.544,0.559,0.560,0.562,0.572,0.550,0.564},
{ 0.002,0.006,0.036,0.078,0.155,0.215,0.282,0.310,0.353,0.358,0.399,0.429,0.425,0.447,0.430,0.468,0.480,0.494,0.518,0.503}
};

double forward_electron_trigger_pi_high_eff[6][20]= { 
{ 0.000,0.000,0.003,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.002,0.010,0.015,0.019,0.037,0.038,0.094,0.106,0.102,0.159},{ 0.003,0.000,0.000,0.000,0.003,0.000,0.003,0.003,0.010,0.019,0.059,0.128,0.106,0.159,0.130,0.227,0.234,0.248,0.286,0.267},{ 0.003,0.002,0.000,0.005,0.006,0.038,0.053,0.126,0.156,0.199,0.222,0.230,0.236,0.322,0.330,0.348,0.339,0.351,0.386,0.446},{ 0.005,0.037,0.086,0.153,0.219,0.284,0.313,0.364,0.352,0.395,0.432,0.418,0.451,0.436,0.468,0.480,0.495,0.521,0.495,0.483},{ 0.308,0.373,0.444,0.481,0.519,0.522,0.540,0.537,0.545,0.558,0.539,0.548,0.544,0.557,0.566,0.560,0.569,0.552,0.565,0.566},
{ 0.005,0.037,0.086,0.153,0.219,0.284,0.313,0.364,0.352,0.395,0.432,0.418,0.451,0.436,0.468,0.480,0.495,0.521,0.495,0.483}
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
		
