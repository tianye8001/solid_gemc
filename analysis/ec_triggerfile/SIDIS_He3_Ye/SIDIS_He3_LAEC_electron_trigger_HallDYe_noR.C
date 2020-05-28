// refer to http://hallaweb.jlab.org/12GeV/SoLID/download/sim/talk/solid_SIDIS_background_zwzhao_20131118.pdf
// FAEC e trigger cut on Q2=1 curve on slide 5
// FAEC e trigger cut R edge 90,105,115,130,150,200,230 cm
// FAEC e trigger cut P value 5,4,3,2,1,2 GeV
// LAEC e trigger cut P>3GeV on slide 3/

//large angle electron trigger curve has only 20 points

double R_min=80.0;   
double R_max=140.0;


double large_electron_trigger_low_P[24]={1.575, 1.725,  1.875,  2.025,  2.175,  2.325,  2.475,  2.625,  2.775,  2.925,  3.075,  3.225,  3.375,  3.525,  3.675,  3.825,  3.975,  4.125,  4.275, 4.425,4.575,4.725,4.875,5.025};
double large_electron_trigger_high_P[24]={1.725,1.875,  2.025,  2.175,  2.325,  2.475,  2.625,  2.775,  2.925,  3.075,  3.225,  3.375,  3.525,  3.675,  3.825,  3.975,  4.125,  4.275,  4.425, 4.575,4.725,4.875,5.025,5.175};

double large_electron_trigger_e_low_eff[24]= { 0.002,0.006,0.006,0.004,0.019,0.057,0.275,0.632,0.854,0.953,0.988,0.983,0.983,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000};

double large_electron_trigger_e_high_eff[24]={0.006,0.006,0.005,0.019,0.059,0.290,0.649,0.861,0.956,0.986,0.984,0.984,0.995,0.997,0.998,0.996,0.996,0.999,0.999,1.000,1.000,1.000,1.000,1.000};

double large_electron_trigger_pi_low_eff[24]={0.000,0.000,0.001,0.001,0.000,0.001,0.010,0.022,0.031,0.047,0.056,0.079,0.097,0.100,0.142,0.172,0.193,0.194,0.245,0.222,0.257,0.253,0.298,0.272};

double large_electron_trigger_pi_high_eff[24]={0.000,0.001,0.001,0.000,0.001,0.011,0.022,0.031,0.048,0.057,0.077,0.101,0.098,0.146,0.175,0.190,0.196,0.239,0.232,0.256,0.260,0.293,0.278,0.269};

double get_large_electron_trigger_e_eff(double hit_R, double hit_E){
	
	double e_eff=0;

	if(hit_R<R_min || hit_R>R_max){
		e_eff=0;
	}else{
		int P_index=-1;

	    if(hit_E<large_electron_trigger_low_P[0]){
		e_eff=0;
	    }else{		
		for(int Pj=0;Pj<24;Pj++){
			if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
				P_index=Pj;
			}
		}

		if(hit_E>=large_electron_trigger_high_P[23]){
			P_index=23;
		}
		
		//(eff_high-eff_low)/(x_high-x_low)*(hit_E-x_low) + eff_low
		e_eff=(large_electron_trigger_e_high_eff[P_index] - large_electron_trigger_e_low_eff[P_index]  )/( large_electron_trigger_high_P[P_index] -  large_electron_trigger_low_P[P_index]) * (hit_E- large_electron_trigger_low_P[P_index]) + large_electron_trigger_e_low_eff[P_index] ;

		//e_eff=0.5*(large_electron_trigger_e_low_eff[P_index]+large_electron_trigger_e_high_eff[P_index]);
	    }
	}

	return e_eff;
}

double get_large_electron_trigger_pi_eff(double hit_R, double hit_E){
	
	double e_eff=0;

	if(hit_R<R_min || hit_R>R_max){
		e_eff=0;
	}else{
		int P_index=-1;
	    if(hit_E<large_electron_trigger_low_P[0]){
		e_eff=0;
	    }else{	
		for(int Pj=0;Pj<24;Pj++){
			if(hit_E>=large_electron_trigger_low_P[Pj] && hit_E<large_electron_trigger_high_P[Pj]){
				P_index=Pj;
			}
		}

		if(hit_E>=large_electron_trigger_high_P[23]){
			P_index=23;
		}
		//
		 e_eff=(large_electron_trigger_pi_high_eff[P_index] - large_electron_trigger_pi_low_eff[P_index]  )/( large_electron_trigger_high_P[P_index] -  large_electron_trigger_low_P[P_index]) * (hit_E- large_electron_trigger_low_P[P_index]) + large_electron_trigger_pi_low_eff[P_index] ;

		//e_eff=0.5*(large_electron_trigger_pi_low_eff[P_index]+large_electron_trigger_pi_high_eff[P_index]);
	    }
	}

	return e_eff;
}
