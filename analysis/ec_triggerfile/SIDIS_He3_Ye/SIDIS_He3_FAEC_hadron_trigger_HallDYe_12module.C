// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC MIP trigger cut on 200MeV curve on slide 14

double forward_hadron_trigger_low_P[29]={0.0265,	0.0595,	0.0925,	0.1255,	0.1585,	0.1915,	0.2245,	0.2575,	0.2905,	0.3235,	0.3565,	0.3895,	0.4225,	0.4555,	0.4885,	0.5215,	0.5545,	0.5875,	0.6205,	0.6535,	0.6865,	0.7195,	0.7525,	0.7855,	0.8185,	0.8515,	0.8845,	0.9175,	0.9505};

double forward_hadron_trigger_high_P[29]={0.0595,	0.0925,	0.1255,	0.1585,	0.1915,	0.2245,	0.2575,	0.2905,	0.3235,	0.3565,	0.3895,	0.4225,	0.4555,	0.4885,	0.5215,	0.5545,	0.5875,	0.6205,	0.6535,	0.6865,	0.7195,	0.7525,	0.7855,	0.8185,	0.8515,	0.8845,	0.9175,	0.9505,	0.9835};


//electron efficiency
//double forward_hadron_trigger_e_low_eff[29]={0,	0,	0,	0,	0.00831313,	0.0833676,	0.369744,	0.774367,	0.933252,	0.988943,	0.998504,	1,	0.999131,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0.998233,	1,	1,	1,	1};

//double forward_hadron_trigger_e_high_eff[29]={0,	0,	0,	0.00831313,	0.0833676,	0.369744,	0.774367,	0.933252,	0.988943,	0.998504,	1,	0.999131,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0.998233,	1,	1,	1,	1,	1};

double forward_hadron_trigger_e_low_eff[29]={0.020,0.024,0.027,0.054,0.098,0.190,0.359,0.582,0.745,0.869,0.939,0.975,0.991,0.994,0.998,0.998,0.999,1.000,1.000,1.000,0.999,1.000,0.999,1.000,1.000,1.000,1.000,1.000,1.000};
double forward_hadron_trigger_e_high_eff[29]={0.024,0.027,0.054,0.098,0.190,0.359,0.582,0.745,0.869,0.939,0.975,0.991,0.994,0.998,0.998,0.999,1.000,1.000,1.000,0.999,1.000,0.999,1.000,1.000,1.000,1.000,1.000,1.000,1.000};



double forward_hadron_trigger_gamma_low_eff[29]={0.033,0.030,0.045,0.078,0.188,0.348,0.582,0.734,0.856,0.932,0.961,0.991,0.990,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000};
double forward_hadron_trigger_gamma_high_eff[29]={0.030,0.045,0.078,0.188,0.348,0.582,0.734,0.856,0.932,0.961,0.991,0.990,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000};




double forward_hadron_trigger_pion_low_eff[29]={0.022,0.081,0.230,0.594,0.728,0.777,0.810,0.856,0.888,0.876,0.883,0.923,0.924,0.927,0.926,0.939,0.937,0.945,0.948,0.943,0.946,0.966,0.953,0.953,0.958,0.966,0.973,0.965,0.967};
double forward_hadron_trigger_pion_high_eff[29]={0.081,0.230,0.594,0.728,0.777,0.810,0.856,0.888,0.876,0.883,0.923,0.924,0.927,0.926,0.939,0.937,0.945,0.948,0.943,0.946,0.966,0.953,0.953,0.958,0.966,0.973,0.965,0.967,0.973};



double forward_hadron_trigger_proton_low_eff[29]={0.021,0.021,0.018,0.041,0.254,0.762,0.860,0.878,0.912,0.916,0.919,0.923,0.927,0.943,0.934,0.928,0.954,0.943,0.950,0.953,0.954,0.959,0.956,0.958,0.963,0.966,0.966,0.972,0.973};
double forward_hadron_trigger_proton_high_eff[29]={0.021,0.018,0.041,0.254,0.762,0.860,0.878,0.912,0.916,0.919,0.923,0.927,0.943,0.934,0.928,0.954,0.943,0.950,0.953,0.954,0.959,0.956,0.958,0.963,0.966,0.966,0.972,0.973,0.971};

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

