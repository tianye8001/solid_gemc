// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC MIP trigger cut on 200MeV curve on slide 14

double forward_hadron_trigger_low_P[29]={0.0265,	0.0595,	0.0925,	0.1255,	0.1585,	0.1915,	0.2245,	0.2575,	0.2905,	0.3235,	0.3565,	0.3895,	0.4225,	0.4555,	0.4885,	0.5215,	0.5545,	0.5875,	0.6205,	0.6535,	0.6865,	0.7195,	0.7525,	0.7855,	0.8185,	0.8515,	0.8845,	0.9175,	0.9505};

double forward_hadron_trigger_high_P[29]={0.0595,	0.0925,	0.1255,	0.1585,	0.1915,	0.2245,	0.2575,	0.2905,	0.3235,	0.3565,	0.3895,	0.4225,	0.4555,	0.4885,	0.5215,	0.5545,	0.5875,	0.6205,	0.6535,	0.6865,	0.7195,	0.7525,	0.7855,	0.8185,	0.8515,	0.8845,	0.9175,	0.9505,	0.9835};


//electron efficiency
//double forward_hadron_trigger_e_low_eff[29]={0,	0,	0,	0,	0.00831313,	0.0833676,	0.369744,	0.774367,	0.933252,	0.988943,	0.998504,	1,	0.999131,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0.998233,	1,	1,	1,	1};

//double forward_hadron_trigger_e_high_eff[29]={0,	0,	0,	0.00831313,	0.0833676,	0.369744,	0.774367,	0.933252,	0.988943,	0.998504,	1,	0.999131,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0.998233,	1,	1,	1,	1,	1};

double forward_hadron_trigger_e_low_eff[29]={0.011,0.012,0.020,0.031,0.067,0.158,0.323,0.547,0.725,0.850,0.927,0.958,0.973,0.974,0.977,0.980,0.983,0.981,0.987,0.986,0.982,0.984,0.979,0.986,0.987,0.988,0.986,0.990,0.984};
double forward_hadron_trigger_e_high_eff[29]={0.012,0.020,0.031,0.067,0.158,0.323,0.547,0.725,0.850,0.927,0.958,0.973,0.974,0.977,0.980,0.983,0.981,0.987,0.986,0.982,0.984,0.979,0.986,0.987,0.988,0.986,0.990,0.984,0.985};


//gamma efficiency
//double forward_hadron_trigger_gamma_low_eff[29]={0,	0,	0.000195771,	0.000525762,	0.0196078,	0.214712,	0.61692,	0.867033,	0.968889,	0.993653,	0.996963,	0.995766,	0.999102,	1,	1,	1,	1,	1,	0.99866,	0.998567,	1,	1,	1,	1,	0.998305,	1,	1,	0.998106,	1};

//double forward_hadron_trigger_gamma_high_eff[29]={0,	0.000195771,	0.000525762,	0.0196078,	0.214712,	0.61692,	0.867033,	0.968889,	0.993653,	0.996963,	0.995766,	0.999102,	1,	1,	1,	1,	1,	0.99866,	0.998567,	1,	1,	1,	1,	0.998305,	1,	1,	0.998106,	1,	1};

double forward_hadron_trigger_gamma_low_eff[29]={0.033,0.010,0.036,0.052,0.186,0.335,0.579,0.744,0.855,0.914,0.958,0.991,0.990,0.997,1.000,0.993,1.000,0.993,1.000,0.997,0.996,1.000,0.997,1.000,1.000,1.000,0.997,1.000,1.000};
double forward_hadron_trigger_gamma_high_eff[29]={0.010,0.036,0.052,0.186,0.335,0.579,0.744,0.855,0.914,0.958,0.991,0.990,0.997,1.000,0.993,1.000,0.993,1.000,0.997,0.996,1.000,0.997,1.000,1.000,1.000,0.997,1.000,1.000,1.000};

//gamma background
//double forward_hadron_trigger_gamma_low_eff[29]={0.011,0.013,0.015,0.031,0.120,0.353,0.554,0.735,0.825,0.919,0.964,0.986,0.998,0.996,1.000,1.000,1.000,0.999,0.997,1.000,1.000,1.000,1.000,0.998,1.000,0.998,1.000,1.000,1.000};
//double forward_hadron_trigger_gamma_high_eff[29]={0.013,0.015,0.031,0.120,0.353,0.554,0.735,0.825,0.919,0.964,0.986,0.998,0.996,1.000,1.000,1.000,0.999,0.997,1.000,1.000,1.000,1.000,0.998,1.000,0.998,1.000,1.000,1.000,1.000};

//pion efficiency
//double forward_hadron_trigger_pion_low_eff[29]={0.0193918,	0.419003,	0.598157,	0.743008,	0.808838,	0.857615,	0.87741,	0.910832,	0.925447,	0.945196,	0.958666,	0.956376,	0.953532,	0.962371,	0.970134,	0.965402,	0.98063,	0.979721,	0.979194,	0.986357,	0.990798,	0.990385,	0.991909,	0.988599,	0.991364,	0.990619,	0.990991,	0.994208,	0.996094};

//double forward_hadron_trigger_pion_high_eff[29]={0.419003,	0.598157,	0.743008,	0.808838,	0.857615,	0.87741,	0.910832,	0.925447,	0.945196,	0.958666,	0.956376,	0.953532,	0.962371,	0.970134,	0.965402,	0.98063,	0.979721,	0.979194,	0.986357,	0.990798,	0.990385,	0.991909,	0.988599,	0.991364,	0.990619,	0.990991,	0.994208,	0.996094,	0.997921};

//double forward_hadron_trigger_pion_low_eff[36]={0.011,0.047,0.162,0.513,0.702,0.749,0.812,0.839,0.872,0.873,0.870,0.923,0.907,0.925,0.928,0.916,0.943,0.939,0.939,0.940,0.948,0.933,0.970,0.945,0.942,0.945,0.980,0.967,0.963,0.956,0.964,0.960,0.954,0.956,0.974,0.964};

//double forward_hadron_trigger_pion_high_eff[36]={0.048,0.172,0.557,0.715,0.765,0.800,0.851,0.885,0.871,0.877,0.916,0.915,0.927,0.917,0.939,0.933,0.936,0.948,0.938,0.946,0.962,0.943,0.953,0.943,0.964,0.969,0.963,0.959,0.969,0.955,0.956,0.957,0.969,0.965,0.960,0.960};


double forward_hadron_trigger_pion_low_eff[29]={0.029,0.077,0.233,0.590,0.723,0.775,0.826,0.859,0.900,0.883,0.876,0.928,0.911,0.933,0.918,0.947,0.929,0.933,0.934,0.941,0.940,0.955,0.947,0.951,0.950,0.957,0.965,0.961,0.958};
//double forward_hadron_trigger_pion_low_eff[29]={0.008,0.053,0.171,0.555,0.713,0.763,0.805,0.852,0.891,0.877,0.882,0.915,0.920,0.929,0.914,0.942,0.934,0.932,0.949,0.937,0.943,0.960,0.936,0.956,0.943,0.967,0.967,0.961,0.956};
double forward_hadron_trigger_pion_high_eff[29]={0.077,0.233,0.590,0.723,0.775,0.826,0.859,0.900,0.883,0.876,0.928,0.911,0.933,0.918,0.947,0.929,0.933,0.934,0.941,0.940,0.955,0.947,0.951,0.950,0.957,0.965,0.961,0.958,0.971};
//double forward_hadron_trigger_pion_high_eff[29]={0.053,0.171,0.555,0.713,0.763,0.805,0.852,0.891,0.877,0.882,0.915,0.920,0.929,0.914,0.942,0.934,0.932,0.949,0.937,0.943,0.960,0.936,0.956,0.943,0.967,0.967,0.961,0.956,0.969};
//pion nobackground
//double forward_hadron_trigger_pion_low_eff[29]={0.000,0.010,0.084,0.426,0.672,0.743,0.781,0.836,0.886,0.867,0.870,0.902,0.910,0.912,0.909,0.935,0.910,0.912,0.935,0.930,0.928,0.954,0.936,0.949,0.933,0.955,0.958,0.951,0.954};
//double forward_hadron_trigger_pion_high_eff[29]={0.010,0.084,0.426,0.672,0.743,0.781,0.836,0.886,0.867,0.870,0.902,0.910,0.912,0.909,0.935,0.910,0.912,0.935,0.930,0.928,0.954,0.936,0.949,0.933,0.955,0.958,0.951,0.954,0.962};


//proton efficiency
//double forward_hadron_trigger_proton_low_eff[29]={0,	0,	0.00153139,	0.0259336,	0.470748,	0.899351,	0.917235,	0.931217,	0.934783,	0.962238,	0.952522,	0.955738,	0.968284,	0.979821,	0.977629,	0.992788,	0.976744,	0.992683,	0.979228,	0.987562,	0.994118,	0.990937,	0.993976,	0.996599,	1,	1,	0.992674,	1,	0.995984};

//double forward_hadron_trigger_proton_high_eff[29]={0,	0.00153139,	0.0259336,	0.470748,	0.899351,	0.917235,	0.931217,	0.934783,	0.962238,	0.952522,	0.955738,	0.968284,	0.979821,	0.977629,	0.992788,	0.976744,	0.992683,	0.979228,	0.987562,	0.994118,	0.990937,	0.993976,	0.996599,	1,	1,	0.992674,	1,	0.995984,	1};
double forward_hadron_trigger_proton_low_eff[29]={0.000,0.017,0.023,0.055,0.241,0.765,0.854,0.884,0.905,0.914,0.917,0.918,0.921,0.939,0.931,0.926,0.946,0.943,0.945,0.953,0.952,0.956,0.954,0.954,0.960,0.964,0.961,0.968,0.967};
double forward_hadron_trigger_proton_high_eff[29]={0.017,0.023,0.055,0.241,0.765,0.854,0.884,0.905,0.914,0.917,0.918,0.921,0.939,0.931,0.926,0.946,0.943,0.945,0.953,0.952,0.956,0.954,0.954,0.960,0.964,0.961,0.968,0.967,0.969};

//calculate electron efficiency
double get_forward_hadron_trigger_e_eff(double hit_E){
	double e_eff=0;
	
	if(hit_E<forward_hadron_trigger_low_P[0]){
		e_eff=0;
	}else{

		int P_index=-1;

		for(int Pi=0; Pi<29; Pi++){

			if(hit_E>=forward_hadron_trigger_low_P[Pi] && hit_E<forward_hadron_trigger_high_P[Pi]){
				P_index=Pi;
			}
	
		}

		if(hit_E>=forward_hadron_trigger_high_P[28]){
			P_index=28;
		}

		e_eff=(forward_hadron_trigger_e_high_eff[P_index] - forward_hadron_trigger_e_low_eff[P_index])/( forward_hadron_trigger_high_P[P_index] - forward_hadron_trigger_low_P[P_index] ) * (hit_E - forward_hadron_trigger_low_P[P_index]) + forward_hadron_trigger_e_low_eff[P_index];
	}

	return e_eff;
}


//calculate gamma efficiency
double get_forward_hadron_trigger_gamma_eff(double hit_E){
	double gamma_eff=0;
	
	if(hit_E<forward_hadron_trigger_low_P[0]){
		gamma_eff=0;
	}else{

		int P_index=-1;

		for(int Pi=0; Pi<29; Pi++){

			if(hit_E>=forward_hadron_trigger_low_P[Pi] && hit_E<forward_hadron_trigger_high_P[Pi]){
				P_index=Pi;
			}
	
		}

		if(hit_E>=forward_hadron_trigger_high_P[28]){
			P_index=28;
		}

		gamma_eff=(forward_hadron_trigger_gamma_high_eff[P_index] - forward_hadron_trigger_gamma_low_eff[P_index])/( forward_hadron_trigger_high_P[P_index] - forward_hadron_trigger_low_P[P_index] ) * (hit_E - forward_hadron_trigger_low_P[P_index]) + forward_hadron_trigger_gamma_low_eff[P_index];
	}

	return gamma_eff;
}


//calculate pion efficiency
double get_forward_hadron_trigger_pion_eff(double hit_E){
	double pion_eff=0;
	
	if(hit_E<forward_hadron_trigger_low_P[0]){
		pion_eff=0;
	}else{

		int P_index=-1;

		for(int Pi=0; Pi<29; Pi++){

			if(hit_E>=forward_hadron_trigger_low_P[Pi] && hit_E<forward_hadron_trigger_high_P[Pi]){
				P_index=Pi;
			}
	
		}

		if(hit_E>=forward_hadron_trigger_high_P[28]){
			P_index=28;
		}

		pion_eff=(forward_hadron_trigger_pion_high_eff[P_index] - forward_hadron_trigger_pion_low_eff[P_index])/( forward_hadron_trigger_high_P[P_index] - forward_hadron_trigger_low_P[P_index] ) * (hit_E - forward_hadron_trigger_low_P[P_index]) + forward_hadron_trigger_pion_low_eff[P_index];
	}

	return pion_eff;
}



//calculate proton efficiency
double get_forward_hadron_trigger_proton_eff(double hit_E){
	double proton_eff=0;
	
	if(hit_E<forward_hadron_trigger_low_P[0]){
		proton_eff=0;
	}else{

		int P_index=-1;

		for(int Pi=0; Pi<29; Pi++){

			if(hit_E>=forward_hadron_trigger_low_P[Pi] && hit_E<forward_hadron_trigger_high_P[Pi]){
				P_index=Pi;
			}
	
		}

		if(hit_E>=forward_hadron_trigger_high_P[28]){
			P_index=28;
		}

		proton_eff=(forward_hadron_trigger_proton_high_eff[P_index] - forward_hadron_trigger_proton_low_eff[P_index])/( forward_hadron_trigger_high_P[P_index] - forward_hadron_trigger_low_P[P_index] ) * (hit_E - forward_hadron_trigger_low_P[P_index]) + forward_hadron_trigger_proton_low_eff[P_index];
	}

	return proton_eff;
}

