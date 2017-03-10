/*
 * this script is to get electron or pion efficiency using EC (ps+sh),
 * the input is hitting R, hitting phi range, hitting energy, particle you need to get efficiency (electron or pion)
 *
 * The trigger curve we use Jin's trigger curve
 *
 *
 * Written by Yuxiang Zhao (yxzhao@jlab.org) 
 * 2016-2-19
*/

#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>
#include <TString.h>
#include <TGraphErrors.h>

using namespace std;

// refer to slide 3 of http://hallaweb.jlab.org/12GeV/SoLID/download/baffle/talk/solid_baffle_zwzhao_20130910.pdf
// EC trigger cut near x=0.35 curve
// EC trigger cut R edge 110,116,124,165,205,265 cm
// EC trigger cut P value 3.8,3.5,2.5,2.0,1.5 GeV

	//trigger curve using different baffle
	//---this is for more1 block
	TFile* file_high_phi=new TFile("PVDIS_LD2_201309/baffle_babarbafflemore1_block/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_high_R0_ALL.rootTriggerSummaryhigh.root");
	TFile* file_low_phi=new TFile("PVDIS_LD2_201309/baffle_babarbafflemore1_block/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_low_R0_ALL.rootTriggerSummarylow.root");
	
	// in each file, 5 graphes for electron,5 for pion
	const int graph_num=5;    // corresponding to the graph numbers
	TString electron_graph_name_high_phi[5]={"Graph_Electron_Eklog_R_high_R113",
						 "Graph_Electron_Eklog_R_high_R120",
						 "Graph_Electron_Eklog_R_high_R150",
						 "Graph_Electron_Eklog_R_high_R180",
						 "Graph_Electron_Eklog_R_high_R230"
						 };
	TString pion_graph_name_high_phi[5]={"Graph_Pion_Eklog_R_high_R113",
				             "Graph_Pion_Eklog_R_high_R120",
  				             "Graph_Pion_Eklog_R_high_R150",
				             "Graph_Pion_Eklog_R_high_R180",
	                                     "Graph_Pion_Eklog_R_high_R230"
				             };
	
	TString electron_graph_name_low_phi[5]={"Graph_Electron_Eklog_R_low_R113",
	               				"Graph_Electron_Eklog_R_low_R120",
			             		"Graph_Electron_Eklog_R_low_R150",
					        "Graph_Electron_Eklog_R_low_R180",
						"Graph_Electron_Eklog_R_low_R230"
						};
	TString pion_graph_name_low_phi[5]={"Graph_Pion_Eklog_R_low_R113",
					    "Graph_Pion_Eklog_R_low_R120",
                                            "Graph_Pion_Eklog_R_low_R150",
                                            "Graph_Pion_Eklog_R_low_R180",
                                            "Graph_Pion_Eklog_R_low_R230"
                                            };

	double R_segmentation[6]={110,116,124,165,205,265}; //this is for 113,120,150,180,230 curves, got it from zhiwen(zwzhao@jlab.org)

double Get_PVDIS_trigger_efficiency_EC(TString phi_range,TString pid,double hit_R, double hit_Mom, bool Is_debug=false){
	//to test:  in root [1] .x Get_PVDIS_trigger_efficiency_EC.C("high", "electron",235, 3)
	// phi_range= "high" or "low" 
	// pid="electron",  "pion", "gamma", "proton"
	// hit_R= 110->265, out of this range, trigger efficiency is set to be zero  
	// hit_Mom : this is momentum of the particle  
	// note: gamma trigger efficiency = electron,  proton trigger efficiency =1/2 pion trigger efficiency
	
	// value to be returned!!!
	double trigger_efficiency=0;
	


	//----check which curve to pick up according to the input information
	
	//---------------------------
	//check R range
	//--------------------------
	int graph_ID=1000;
	for(int i=0;i<graph_num;i++){
		if( hit_R>R_segmentation[i] && hit_R<=R_segmentation[i+1] ){
			graph_ID=i;
		}
	}
	
	//take care of out-of-range events
	if(hit_R<R_segmentation[0])trigger_efficiency=0;
	if(hit_R>R_segmentation[graph_num])trigger_efficiency=0;

	if(graph_ID>=0 && graph_ID<graph_num){  //R is in EC range
		//------------------------
		// get graph
		//-----------------------
		TGraphErrors* trigger_curve;
	
		if(phi_range=="high"){
			if(pid=="electron" || pid=="gamma"){  //gamma trigger efficiency = electron
				trigger_curve=(TGraphErrors*) file_high_phi->Get(electron_graph_name_high_phi[graph_ID]);
			}else if(pid=="pion" || pid=="proton"){  //proton= 1/2 pion efficiency
				trigger_curve=(TGraphErrors*) file_high_phi->Get(pion_graph_name_high_phi[graph_ID]);
			}else{
				cout<<"you should sign pid to electron (gamma) or pion (proton), now redirecting your pid to electron in default!!!"<<endl;
				trigger_curve=(TGraphErrors*) file_high_phi->Get(electron_graph_name_high_phi[graph_ID]);
			}
		}else if(phi_range=="low"){
			if(pid=="electron" || pid=="gamma"){
				trigger_curve=(TGraphErrors*) file_low_phi->Get(electron_graph_name_low_phi[graph_ID]);
			}else if(pid=="pion" || pid=="proton"){
				trigger_curve=(TGraphErrors*) file_low_phi->Get(pion_graph_name_low_phi[graph_ID]);
			}else{
				cout<<"you should sign pid to electron or pion, now redirecting your pid to electron in default!!!"<<endl;
				trigger_curve=(TGraphErrors*) file_low_phi->Get(electron_graph_name_low_phi[graph_ID]);
			}
		}
	
	
		//---------------------------------------
		//get points in the graph
		//--------------------------------------
		const int points_num=25;    //according to points in the curve
		double momentum_grid[points_num]={0};
		double efficiency_grid[points_num]={0};
	
		for(int j=0;j<points_num;j++){
			momentum_grid[j]=trigger_curve->GetX()[j];
			efficiency_grid[j]=trigger_curve->GetY()[j];
			if (Is_debug) cout<<"debug:   "<<momentum_grid[j]<<"	"<<efficiency_grid[j]<<endl;
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
		
		//take care of out-of-range events
		if(hit_Mom<momentum_grid[0]){
			if(hit_Mom<0.5){
				trigger_efficiency=0;
			}else{
				trigger_efficiency = efficiency_grid[0]/2.0;
			}
		}
		
		if(hit_Mom>momentum_grid[points_num-1])trigger_efficiency = efficiency_grid[points_num-1];
	} //end trigger efficiency calculation with R in EC range
	
	if(pid=="proton")trigger_efficiency=1.0/2.0*trigger_efficiency;   //use pion curve then divided by 2 
	
	if (Is_debug) {
	cout<<"#####################################################################"<<endl;
	cout<<"your input is: hit_R= "<<hit_R<<"	phi_range= "<<phi_range<<"	hit_Mom= "<<hit_Mom<<"	pid= "<<pid<<endl;
	cout<<"Final trigger efficiency is : "<<trigger_efficiency<<endl;
	cout<<"#######################################################################"<<endl;
	}
	
	return trigger_efficiency;

}

