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
{ 0.000,0.004,0.000,0.000,0.000,0.008,0.000,0.008,0.008,0.000,0.126,0.634,0.976,0.977,0.992,1.000,1.000,0.986,0.993,1.000},{ 0.000,0.000,0.000,0.003,0.003,0.003,0.003,0.140,0.766,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000},{ 0.000,0.001,0.000,0.005,0.052,0.608,0.959,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.003,0.009,0.344,0.954,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.861,0.993,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.003,0.009,0.344,0.954,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000}
};

double forward_electron_trigger_e_high_eff[6][20]={ 
{ 0.004,0.000,0.000,0.000,0.008,0.000,0.008,0.008,0.000,0.126,0.636,0.969,0.977,0.992,1.000,1.000,0.986,0.993,1.000,1.000},{ 0.000,0.000,0.003,0.003,0.003,0.003,0.140,0.766,0.975,0.991,0.993,0.997,0.994,0.997,0.991,0.991,1.000,0.997,1.000,1.000},{ 0.001,0.000,0.005,0.052,0.608,0.959,0.994,1.000,0.996,0.998,0.998,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.009,0.344,0.954,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.993,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000},{ 0.009,0.344,0.954,0.992,0.998,0.999,0.997,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000}
};

double forward_electron_trigger_pi_low_eff[6][20]={ 
{ 0.000,0.002,0.000,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.005,0.018,0.016,0.033,0.025,0.096,0.101,0.117,0.150},{ 0.000,0.000,0.002,0.003,0.000,0.003,0.003,0.000,0.006,0.017,0.033,0.097,0.111,0.155,0.138,0.206,0.223,0.275,0.252,0.266},{ 0.002,0.000,0.000,0.002,0.008,0.015,0.048,0.070,0.153,0.181,0.205,0.221,0.254,0.270,0.331,0.370,0.341,0.348,0.369,0.451},{ 0.004,0.003,0.037,0.096,0.159,0.238,0.289,0.336,0.355,0.396,0.387,0.450,0.438,0.438,0.474,0.456,0.509,0.511,0.507,0.478},{ 0.172,0.310,0.383,0.452,0.490,0.525,0.517,0.540,0.544,0.549,0.554,0.552,0.542,0.552,0.561,0.560,0.571,0.558,0.560,0.569},{ 0.004,0.003,0.037,0.096,0.159,0.238,0.289,0.336,0.355,0.396,0.387,0.450,0.438,0.438,0.474,0.456,0.509,0.511,0.507,0.478}
};

double forward_electron_trigger_pi_high_eff[6][20]= {
 { 0.002,0.000,0.002,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.005,0.018,0.016,0.033,0.025,0.096,0.101,0.117,0.150,0.158},{ 0.000,0.002,0.003,0.000,0.003,0.003,0.000,0.006,0.017,0.033,0.097,0.111,0.155,0.137,0.206,0.223,0.276,0.252,0.265,0.292},{ 0.000,0.000,0.002,0.008,0.015,0.048,0.070,0.153,0.181,0.203,0.223,0.254,0.270,0.331,0.370,0.340,0.349,0.368,0.451,0.389},{ 0.003,0.037,0.096,0.159,0.237,0.291,0.335,0.355,0.396,0.387,0.450,0.438,0.436,0.473,0.456,0.510,0.512,0.506,0.479,0.483},{ 0.310,0.383,0.452,0.489,0.525,0.518,0.540,0.544,0.548,0.554,0.552,0.541,0.552,0.560,0.560,0.571,0.559,0.560,0.568,0.575},{ 0.003,0.037,0.096,0.159,0.237,0.291,0.335,0.355,0.396,0.387,0.450,0.438,0.436,0.473,0.456,0.510,0.512,0.506,0.479,0.483} 
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
		
