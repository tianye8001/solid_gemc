/* 
 * this script is to get the SIDIS trigger efficiency on EC for "electron trigger"
 *
 * trigger curve we use Jin's curve
 *
 * forward angle is radial cut, large angle is a single cut 
 *
 *
 * Written by Yuxiang Zhao (yxzhao@jlab.org)
 * 2016-2-19
*/


double Get_SIDIS_trigger_efficiency_EC(TString det_ID,TString pid,double hit_R, double hit_Mom, bool Is_debug){
	//det_ID="large", "forward"
	//pid="electron", "gamma", "pion", "proton"
	//hit_R: r value for the hit, in cm  
	//hit_Mom: momentum of the hit  
	
	// value to be returned!!!
	double trigger_efficiency=0;

	
	//---file name for electrons and pions
	// forward
	TString electron_forward_file_name[6]
	={ "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root"
					};
	
	TString pion_forward_file_name[6]
	={ "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",
	   "./SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root"
	};
	
	//large
	TString electron_large_file_name="./SIDIS_He3_201311/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunElectron_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root";
	TString pion_large_file_name="./SIDIS_He3_201311/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunPion_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root";

	//--check R range
	int out_of_R_range_flag=0;
	TFile *trigger_file;
	TString trigger_file_name;
	
	if(det_ID=="forward"){
		const int num_R_seg=7;
		double R_segmentation[num_R_seg]={90,105,115,130,150,200,230}; // R segmentation in cut in the forward angle EC
		int file_ID=1000;
		for(int i=0;i<num_R_seg-1;i++){
			if(hit_R>R_segmentation[i] && hit_R<=R_segmentation[i+1]){
				file_ID=i;
			}
		}
		
		//take care of out-of-range events
		if(hit_R<R_segmentation[0]){
			out_of_R_range_flag=1;    //out of range
		}
		if(hit_R>R_segmentation[num_R_seg-1]){
			out_of_R_range_flag=1;
		}
	
		if(file_ID>=0 && file_ID<num_R_seg-1){ //in forward EC range
			if(pid=="electron" || pid=="gamma"){
				trigger_file_name=electron_forward_file_name[file_ID];
			}else if(pid=="pion" || pid=="proton"){
				trigger_file_name=pion_forward_file_name[file_ID];
			}else{
				cout<<"we only did electron, gamma, pion, proton study for forward EC!"<<endl;
				return 1;
			}
		}
	}else if(det_ID=="large"){
		//need to take care of out-of-R-range events here...
		if(hit_R<80.0 || hit_R>140.0){
			out_of_R_range_flag=1;
		}
		
		//straight single cut
		if(pid=="electron" || pid=="gamma"){
			trigger_file_name=electron_large_file_name;
		}else if(pid=="pion" || pid=="proton"){
			trigger_file_name=pion_large_file_name;
		}else{
			cout<<"we only did electron, gamma, pion, proton study for large angle EC!"<<endl;
			return 1;
		}
	}else{
		cout<<"we only accept det_ID= forward or large !!!"<<endl;
		return 1;
	} // now get the corresponding file_name due to hit_R, det_ID, pid

	if(out_of_R_range_flag!=1){
		trigger_file=new TFile(trigger_file_name);
		TGraphErrors *trigger_curve=(TGraphErrors*) trigger_file->Get("Graph");
	
		const int points_num=21;       //number of points in trigger curve
		double momentum_grid[points_num]={0};
		double efficiency_grid[points_num]={0};
	
		for(int j=0;j<points_num;j++){
			momentum_grid[j]=trigger_curve->GetX()[j];
       		        efficiency_grid[j]=trigger_curve->GetY()[j];
       	       		cout<<"debug:   "<<momentum_grid[j]<<"  "<<efficiency_grid[j]<<endl;
	       	}
		
		for(int k=0; k<points_num-1; k++){
       	         	if(hit_Mom>momentum_grid[k] && hit_Mom<=momentum_grid[k+1]){
				 double eff_low=efficiency_grid[k];
       	                	 double eff_high=efficiency_grid[k+1];
       	              		 double x_low=momentum_grid[k];
       	               	         double x_high=momentum_grid[k+1];
	
       	                         trigger_efficiency=(eff_high-eff_low)/(x_high-x_low)*(hit_Mom-x_low) + eff_low;
       	                }
         	 }
		
		//take care of out-of-range events
		if(hit_Mom<momentum_grid[0]){
			trigger_efficiency=0;
		}
		
		if(hit_Mom>=momentum_grid[points_num-1]){
			trigger_efficiency=efficiency_grid[points_num-1];
		}
	
		
		//deal with proton
		if(pid=="proton")trigger_efficiency=1.0/2.0*trigger_efficiency;   //use pion curve then divided by 2
	}else{
		trigger_efficiency=0;
	}


	cout<<"#####################################################################"<<endl;
	cout<<"your input is: hit_R= "<<hit_R<<"        det_ID= "<<det_ID<<"      hit_Mom= "<<hit_Mom<<"      pid= "<<pid<<endl;
	cout<<"Final trigger efficiency is : "<<trigger_efficiency<<endl;
	cout<<"#######################################################################"<<endl;
	
	return trigger_efficiency;
}
