#include <iostream> 
#include <fstream>
#include <cmath> 
#include "math.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMinuit.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TArc.h"
#include "TString.h"
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TString.h"


#include "Get_PVDIS_trigger_efficiency_EC.C"

using namespace std;

/* some numbers to be hard coded
 *
 * make sure they are correct while using this script
 *
 */

const double filenum=500; //file numbers while running GEMC in order to be correct for normalization
const int loop_time=5;   //electron to be 1, pion to be many times to take advantage of statistics, pion has low efficiency on EC
const double PEthresh=2; //lgc pe shreshold for each pmt
const double PMTthresh=2; //lgc pmt shreshold, at least 2pmts are fired in each sector
const double DEG=180./3.1415926;   //rad to degree
const int with_background_on_lgc=0;     //0: no background on lgc, 1: yes background on lgc


//void Get_PVDIS_lgc_singles(){
int main(){
	
	//--- root file, output of GEMC
	// electron
	//TString file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_dirty_normalized_eDIS_filenum100_1e6.root";
 	//---pim hall D
	//TString file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_dirty_normalized_pimHallD_filenum600_6e6.root";
	
	//pim wiser
	TString file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_dirty_normalized_pimWiser_filenum500_5e6.root";
	
	
	//---pip hall D
	//TString file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_dirty_normalized_pipHallD_filenum600_6e6.root";
	//---pi0 hall D
	//TString file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_dirty_normalized_pi0HallD_filenum600_6e6.root";
	
	//---EM background
	//TString background_file_name="./PVDIS_DATA/background_solid_PVDIS_LD2_EM_0.98e8_skim225433.root";
	//---EM background
	TString background_file_name="./PVDIS_new_DATA/background_solid_PVDIS_LD2_EM_4.98e8_skim960975.root";
	
	double prob_get_background_entry=960975/4.98e8;
	double num_of_events_running=4.98e8;
	int total_30ns_background=9375000;   // 9.375 million
	
	TFile *file=new TFile(file_name);
	TFile *background_file=new TFile(background_file_name);


	//-------------------------
	//   get trees in the real data file
	//-------------------------
	
	//---header tree
	TTree *tree_header = (TTree*) file->Get("header");
	vector <double> *evn=0,*evn_type=0;
	vector <double> *beamPol=0;
	vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
	tree_header->SetBranchAddress("evn",&evn);      // event number 
	tree_header->SetBranchAddress("evn_type",&evn_type);  // evn_type==-1 for simulated events
	tree_header->SetBranchAddress("beamPol",&beamPol);   //beam polarization
	tree_header->SetBranchAddress("var1",&var1);     // W+ rate
	tree_header->SetBranchAddress("var2",&var2);     // W- rate
	tree_header->SetBranchAddress("var3",&var3);     // target pol
	tree_header->SetBranchAddress("var4",&var4);     //x
	tree_header->SetBranchAddress("var5",&var5);     //y
	tree_header->SetBranchAddress("var6",&var6);     //w
	tree_header->SetBranchAddress("var7",&var7);     //Q2
	tree_header->SetBranchAddress("var8",&var8);     //rate, Hz, should check the input file of the simulation

	//---generated tree
	//particle generated with certain momentum at certain vertex
	TTree *tree_generated = (TTree*) file->Get("generated");
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID 
	tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	tree_generated->SetBranchAddress("py",&gen_py);
	tree_generated->SetBranchAddress("pz",&gen_pz);
	tree_generated->SetBranchAddress("vx",&gen_vx);    //vertex of the generated particle at target
	tree_generated->SetBranchAddress("vy",&gen_vy);
	tree_generated->SetBranchAddress("vz",&gen_vz);

	//--- flux
	//the real deal output from the GEMC simulation
	TTree *tree_flux = (TTree*) file->Get("flux");
	vector<double> *flux_id=0,*flux_hitn=0;
	vector<double> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	tree_flux->SetBranchAddress("hitn",&flux_hitn);     // hit number
	tree_flux->SetBranchAddress("id",&flux_id);         //hitting detector ID
	tree_flux->SetBranchAddress("pid",&flux_pid);       //pid
	tree_flux->SetBranchAddress("mpid",&flux_mpid);     // mother pid
	tree_flux->SetBranchAddress("tid",&flux_tid);       // track id
	tree_flux->SetBranchAddress("mtid",&flux_mtid);     // mother track id
	tree_flux->SetBranchAddress("otid",&flux_otid);     // original track id
	tree_flux->SetBranchAddress("trackE",&flux_trackE);  // track energy of 1st step,  track here is G4 track
	tree_flux->SetBranchAddress("totEdep",&flux_totEdep); // totEdep in all steps, track here is G4 track
	tree_flux->SetBranchAddress("avg_x",&flux_avg_x);     //average x, weighted by energy deposition in each step
	tree_flux->SetBranchAddress("avg_y",&flux_avg_y);     //average y
	tree_flux->SetBranchAddress("avg_z",&flux_avg_z);     //average z
	tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);   // local average x 
	tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);   // local average y
	tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);   // local average z
	tree_flux->SetBranchAddress("px",&flux_px);          // px of 1st step
	tree_flux->SetBranchAddress("py",&flux_py);          // py of 1st step
	tree_flux->SetBranchAddress("pz",&flux_pz);          // pz of 1st step
	tree_flux->SetBranchAddress("vx",&flux_vx);          // x coordinate of 1st step
	tree_flux->SetBranchAddress("vy",&flux_vy);          // y coordinate of 1st step
	tree_flux->SetBranchAddress("vz",&flux_vz);          // z coordinate of 1st step
	tree_flux->SetBranchAddress("mvx",&flux_mvx);        // mother
	tree_flux->SetBranchAddress("mvy",&flux_mvy);
	tree_flux->SetBranchAddress("mvz",&flux_mvz);
	tree_flux->SetBranchAddress("avg_t",&flux_avg_t);     //average time stamp

	//---lgc
	//information recorded by lgc
	TTree* tree_lgc= (TTree*) file->Get("solid_lgc");
	vector<double> *lgc_hitn=0;
	vector<double> *lgc_sector=0, *lgc_pmt=0, *lgc_pixel=0, *lgc_n_p_e=0;
	vector<double> *lgc_avg_t=0;
	tree_lgc->SetBranchAddress("hitn", &lgc_hitn);
	tree_lgc->SetBranchAddress("sector", &lgc_sector);   //1->30
	tree_lgc->SetBranchAddress("pmt", &lgc_pmt);  //1->9
	tree_lgc->SetBranchAddress("pixel", &lgc_pixel);  //no idea what is this
	tree_lgc->SetBranchAddress("nphe", &lgc_n_p_e);  //number of p.e for a specific hit
	tree_lgc->SetBranchAddress("avg_t", &lgc_avg_t);  //no idea what is this
	
	//--- background lgc
	//information recorded by lgc
	TTree* background_tree_lgc= (TTree*) background_file->Get("solid_lgc");
	vector<double> *background_lgc_hitn=0;
	vector<double> *background_lgc_sector=0, *background_lgc_pmt=0, *background_lgc_pixel=0, *background_lgc_n_p_e=0;
	vector<double> *background_lgc_avg_t=0;
	background_tree_lgc->SetBranchAddress("hitn", &background_lgc_hitn);
	background_tree_lgc->SetBranchAddress("sector", &background_lgc_sector);   //1->30
	background_tree_lgc->SetBranchAddress("pmt", &background_lgc_pmt);  //1->9
	background_tree_lgc->SetBranchAddress("pixel", &background_lgc_pixel);  //no idea what is this
	background_tree_lgc->SetBranchAddress("nphe", &background_lgc_n_p_e);  //number of p.e for a specific hit
	background_tree_lgc->SetBranchAddress("avg_t", &background_lgc_avg_t);  //no idea what is this



	long int N_events = (long int)tree_header->GetEntries();
	//debug
	//N_events=10000;
	cout << "total number of events : " << N_events << endl;


// prepare for outputs
// define histograms, output txt files etc...
	TH1F *h_flux_EC=new TH1F("h_flux_EC","trigger rate on EC", 60, 0, 300);
	TH1F *h_flux_EC_lgc=new TH1F("h_flux_EC_lgc","trigger rate EC & lgc", 60, 0, 300);
	TH1F *h_flux_EC_no_lgc=new TH1F("h_flux_EC_no_lgc","rates fire EC but not lgc", 60, 0, 300);
	
	TH1F *h_n_trigger_sectors=new TH1F("h_n_trigger_sectors","number of triggered sectors",30,0,30);

	TRandom3 rand;
	rand.SetSeed(0);

	//----------------------------
	//      loop trees
	//---------------------------
	for(int loop_id=1;loop_id<=loop_time;loop_id++){
		cout<<"loop.....  "<<loop_id<<endl;
	
	for(long int i=0;i<N_events;i++){
			//cout<<i<<endl;
		
		//---
		//---header tree
		//---
		tree_header->GetEntry(i);
		double rate=var8->at(0);
		rate=rate/filenum/loop_time;     ///---warning, should make sure filenum is right
		double x=var4->at(0);
		double Q2=var7->at(0);
		double y=var5->at(0);
		//cout<<"header tree: "<<rate<<endl;
		

		//---
		//---generated tree
		//---
		tree_generated->GetEntry(i);
		int n_gen=gen_pid->size();
		//cout<<"generated : "<<n_gen<<endl;
		

		
		//---	
		//---flux tree
		//---
		tree_flux->GetEntry(i);
		int n_hits=flux_hitn->size();
		//cout<<n_hits<<endl;
		///////////////////////////////////////////////////////////////////////////////////////
		//       do trigger
		////////////////////////////////////////////////////////////////////////////////////////
		double hit_R;
		TString phi_range;
		double hit_momen;
		TString pid;
		double hit_phi;
		
		int pass_EC=0;
		
		for(int j=0;j<n_hits;j++){ //loop hits in flux to get a hit on EC
			if( fabs(flux_id->at(j) - 3110000)<0.01 ){ //  hit at EC
				//cout<<"hit at EC"<<endl;
				
				hit_R=sqrt(flux_avg_x->at(j)*flux_avg_x->at(j) + flux_avg_y->at(j)*flux_avg_y->at(j));
				hit_R=hit_R/10.0;  //convert mm to cm
				

				hit_momen=sqrt(flux_px->at(j)*flux_px->at(j) + flux_py->at(j)*flux_py->at(j) + flux_pz->at(j)*flux_pz->at(j));
				hit_momen=hit_momen/1000.0;  //covert MeV to GeV
			


				TVector3 hit_vector(flux_avg_x->at(j), flux_avg_y->at(j), flux_avg_z->at(j));
				
				hit_phi=hit_vector.Phi()*DEG;
				
				if(hit_phi - (int(hit_phi/12.0)*12) < 6){
					phi_range="high";
				}else{
					phi_range="low";
				}

				double EC_efficiency=0;
				if(   fabs( fabs(flux_pid->at(j)) - 11 )<0.1    ){
					pid="electron";
					EC_efficiency=Get_PVDIS_trigger_efficiency_EC(hit_R, phi_range, hit_momen, pid);
				}else if(  fabs( fabs(flux_pid->at(j)) - 211 )<0.1 ){
					pid="pion";
					EC_efficiency=Get_PVDIS_trigger_efficiency_EC(hit_R, phi_range, hit_momen, pid);
				}else if(  fabs( fabs(flux_pid->at(j)) - 22 )<0.1 ){
					pid="gamma";
					EC_efficiency=Get_PVDIS_trigger_efficiency_EC(hit_R, phi_range, hit_momen, pid);
				}else if( fabs( fabs(flux_pid->at(j)) - 2212 )<0.1  ){
					pid="proton";
					EC_efficiency=Get_PVDIS_trigger_efficiency_EC(hit_R, phi_range, hit_momen, pid);
				}else{
					EC_efficiency=0;
				}

				double test_num=rand.Uniform(0,1);
				if(test_num<=EC_efficiency){
					pass_EC=1;
					//cout<<"passed"<<endl;
				}else{
					pass_EC=0;
				}
				
			} //end if hit at EC, go to next hit
			
			if(pass_EC){ // This event passes EC trigger already, no need to loop hit anymore
				break;   //stop looping hits for EC
			}
		}// end hit loop for EC


		

		
		//---lgc trigger
		tree_lgc->GetEntry(i);

		int pass_lgc=0;
		
		int sectorhits[30][9]={{0}};
		int ntrigsecs =0;
		int ntrigpmts =0;

		//cout<<"hit number in lgc: "<<lgc_hitn->size()<<endl;
		// for each event on lgc
		if(!lgc_hitn->size()){
			pass_lgc=0;
		}else{
			
			// loop over data tree
			for(int k = 0; k < lgc_hitn->size(); k++){
				if(lgc_n_p_e->at(k)){
					sectorhits[int(lgc_sector->at(k)-1)][int(lgc_pmt->at(k)-1)] += lgc_n_p_e->at(k);
				}
			}  //end loop hits on lgc for data tree
		
			
	
			
			if(with_background_on_lgc){	
			
			//add in 30ns background
			//int background_counter=0;
			for(int i_background=0; i_background<total_30ns_background; i_background++){
				double test_background=rand.Uniform(0,1);
				if(test_background<prob_get_background_entry){   //need to have an entry
					
					background_tree_lgc->GetEntry(long(test_background*num_of_events_running));  //randomly get a background event in background file
					
					if(!background_lgc_hitn->size()){
						//do nothing
					}else{
						for(int k_background=0; k_background< background_lgc_hitn->size(); k_background++){
							if(background_lgc_n_p_e->at(k_background)){
								sectorhits[int(background_lgc_sector->at(k_background)-1)][int(background_lgc_pmt->at(k_background)-1)] +=background_lgc_n_p_e->at(k_background);
							}
						}
					}
				}
			}
			//finish adding in background
			
			}

			
			
			
			
			
			for(int l = 0; l < 30; l++){
				ntrigpmts = 0;
				for(int m = 0; m < 9; m++){
					if(sectorhits[l][m] >= PEthresh) ntrigpmts++;
				}
				if(ntrigpmts >= PMTthresh) ntrigsecs++;
			}
	
			if(ntrigsecs){
				pass_lgc=1;
				//cout<<"passed lgc"<<endl;
			}else{
				pass_lgc=0;
			}
		}


		//---
		//---fill histograms based on trigger flag
		//---
		// only EC
		if(pass_EC){
			h_flux_EC->Fill(hit_R, rate);
		}
		// EC and LGC
		if(pass_EC && pass_lgc){
			h_flux_EC_lgc->Fill(hit_R, rate);
		}
		// EC but no LGC
		if(pass_EC && !pass_lgc){
			h_flux_EC_no_lgc->Fill(hit_R,rate);
		}
		


	} //end event loop
	
	} //end loop time


	TCanvas *can=new TCanvas("can","can");
	can->cd();
	h_flux_EC_lgc->Draw();
	cout<<"EC&lgc trigger rate:"<<h_flux_EC_lgc->Integral(1,60)<<endl;

	//do outputs

	ofstream OUTPUT_rate;
	OUTPUT_rate.open("EC_and_lgc_both.txt");
	if(!OUTPUT_rate){
		cout<<"can't open output file"<<endl;
		return 1;
	}

	OUTPUT_rate<<" only EC: "<<h_flux_EC->Integral(1,60)<<endl;
	OUTPUT_rate<<"EC&lgc both fired:"<<h_flux_EC_lgc->Integral(1,60)<<endl;
	OUTPUT_rate<<"EC but no lgc fired:"<<h_flux_EC_no_lgc->Integral(1,60)<<endl;


	TFile *output_file=new TFile("EC_and_lgc_both.root","RECREATE");
	h_flux_EC->SetDirectory(output_file);
	h_flux_EC_lgc->SetDirectory(output_file);
	h_flux_EC_no_lgc->SetDirectory(output_file);
	output_file->Write();


}

	

