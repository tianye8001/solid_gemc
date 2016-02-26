/* 
 * this script is to get the SIDIS trigger efficiency on EC for "hadron trigger"
 *
 * trigger curve we use Jin's curve
 *
 * currently only single cut ~200MeV, no R dependence 
 *
 *
 * Written by Yuxiang Zhao (yxzhao@jlab.org)
 * 2016-2-19
 */

#include<iostream>
#include<fstream>
using namespace std;


double Get_SIDIS_MIP_trigger_efficiency_EC(TString pid,double hit_Mom,bool Is_debug){
	//hit_Mom, momentum of the hit
	//pid="electron", "gamma", "pion", "proton"
	// currently no R dependent cut was used for hadron trigger!
	
	// value to be returned!!!
 	double trigger_efficiency=0;

	//file to be used
	TString electron_file_name="./SIDIS_He3_201311/MIPTrigger/Elec.run10xGetEfficiencies__NO_bgd_TrigMIP2.root";
	TString gamma_file_name="./SIDIS_He3_201311/MIPTrigger/Gamma.run10xGetEfficiencies__NO_bgd_TrigMIP2.root";
	TString pion_file_name="./SIDIS_He3_201311/MIPTrigger/Pion.run10xGetEfficiencies__NO_bgd_TrigMIP2.root";
	TString proton_file_name="./SIDIS_He3_201311/MIPTrigger/Proton.run10xGetEfficiencies__NO_bgd_TrigMIP2.root";
	
	TFile *trigger_file;
	if(pid=="electron"){
		trigger_file=new TFile(electron_file_name);
	}else if(pid=="gamma"){
		trigger_file=new TFile(gamma_file_name);
	}else if(pid=="pion"){
		trigger_file=new TFile(pion_file_name);
	}else if(pid=="proton"){
		trigger_file=new TFile(proton_file_name);
	}else{
		cout<<"we only accept electron, gamma, pion, proton as pid input"<<endl;
	}

	TGraphErrors* trigger_curve=(TGraphErrors*) trigger_file->Get("Graph");

	//---------------------------------------
	//get points in the graph
	//--------------------------------------
	const int points_num=30;    //according to points in the curve
	double momentum_grid[points_num]={0};
	double efficiency_grid[points_num]={0};

	for(int j=0;j<points_num;j++){
		momentum_grid[j]=trigger_curve->GetX()[j];
		efficiency_grid[j]=trigger_curve->GetY()[j];
		cout<<"debug:   "<<momentum_grid[j]<<"	"<<efficiency_grid[j]<<endl;
	}

	//--------------------------------------------
	// get efficiency according to pid's momentum
	//--------------------------------------------

	for(int k=0; k<points_num-1; k++){
		if(hit_Mom>momentum_grid[k] && hit_Mom<=momentum_grid[k+1]){
			double eff_low=efficiency_grid[k];
			double eff_high=efficiency_grid[k+1];
			double x_low=momentum_grid[k];
			double x_high=momentum_grid[k+1];

			trigger_efficiency=(eff_high-eff_low)/(x_high-x_low)*(hit_Mom-x_low) + eff_low;
		}
	}

	//deal with out-of-range events
	if(hit_Mom<momentum_grid[0]){
		trigger_efficiency=0;
	}

	if(hit_Mom>momentum_grid[points_num-1]){
		trigger_efficiency=efficiency_grid[points_num-1];
	}

	cout<<"#####################################################################"<<endl;
	cout<<"your input is: 	hit_Mom= "<<hit_Mom<<"	pid= "<<pid<<endl;
	cout<<"Final trigger efficiency is : "<<trigger_efficiency<<endl;
	cout<<"#######################################################################"<<endl;
	
	return trigger_efficiency;

}

