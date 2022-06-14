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
#include "TFile.h"
#include "TMarker.h"

//if your input file is obtained after hadd
//then set this to false
const bool SplitFiles = false;

void fileReducer(string inputFileName)
{
    double rout_cut_FA=270,rin_cut_FA=110,rout_cut_LA=0,rin_cut_LA=0;
    unsigned int numberOfFile = 0;
    
    vector<string> input_sim_file;
    if (!SplitFiles){
//         input_sim_file.push_back("/lustre19/expphy/volatile/halla/solid/tianye/container/eAll_commited4fe_rod_6mm_4.4/eAll_commited4fe_rod_6mm_4.4_100files_1e6.root");
        input_sim_file.push_back(inputFileName.c_str());

        
        string sToFind = "files_";
        std::size_t found = input_sim_file[0].find(sToFind);
        if (found==std::string::npos){
            cout<<"input file name "<<input_sim_file[0]<<" does not satisfy the name format."<<endl;
            exit(0);
        }
        std::size_t start = 0;
        
        for (std::size_t i  = found; i >= 0; i--){
            if (input_sim_file[0][i] == '_') {
                start = i;
                break;
            }
        }
        
        numberOfFile = stoi(input_sim_file[0].substr(start+1, found - start - 1));
        cout<<"number of files: "<<numberOfFile<<", make sure this is correct."<<endl;
        
    }
    else{
        for (int i=0; i<200; i++){
	        input_sim_file.push_back(Form("/volatile/halla/solid/xiongw/PVDIS_6.6GeV/out.%d.root", i+1));
        }
        numberOfFile = input_sim_file.size();
        cout<<"number of files: "<<numberOfFile<<endl;
    }
    

//     TFile* outFile = new TFile("output_PVDIS_fileReducer_4.4GeV_eAll.root", "RECREATE");
    TFile* outFile = new TFile("output_reduced.root", "RECREATE");
    TTree* outTree = new TTree("T", "T");
    double Ei = 0.;
    double Q2 = 0;
    double W = 0;
    double x = 0;
    double y = 0;
    double Abeam = 0;
    double px_gen = 0;
    double py_gen = 0;
    double pz_gen = 0;
    double vx_gen = 0;
    double vy_gen = 0;
    double vz_gen = 0;
    double rate = 0;
    double rateRad = 0;
    double ecR = 0;
    double ecP = 0;
    
    outTree->Branch("Ei",       &Ei,           "Ei/D"      ); //initial beam energy
    outTree->Branch("Q2",       &Q2,           "Q2/D"      ); 
    outTree->Branch("W",        &W,            "W/D"       );
    outTree->Branch("x",        &x,            "x/D"       );
    outTree->Branch("y",        &y,            "y/D"       );
    outTree->Branch("Abeam",    &Abeam,        "Abeam/D"   ); //PV asymmetry
    
    outTree->Branch("vx",       &vx_gen,       "vx/D"      );
    outTree->Branch("vy",       &vy_gen,       "vy/D"      );
    outTree->Branch("vz",       &vz_gen,       "vz/D"      );
    outTree->Branch("px",       &px_gen,       "px/D"      );
    outTree->Branch("py",       &py_gen,       "py/D"      );
    outTree->Branch("pz",       &pz_gen,       "pz/D"      );
    outTree->Branch("rate",     &rate,         "rate/D"    ); //rate without pre-vertex radiation
    outTree->Branch("rateRad",  &rateRad,      "rateRad/D" ); //rate with pre-vertex radiation
    
    outTree->Branch("ecR",      &ecR,          "ecR/D"     ); //r position of hit on EC virtual plane
    outTree->Branch("ecP",      &ecP,          "ecP/D"     ); //momentum of the particle on EC virtual plane
   
    TH2D* hist = new TH2D("hist", "hist", 200, 0 ,1, 200, 0, 20);
    TH2D* hist1 = new TH2D("hist1", "hist1", 200, 0 ,50, 200, 0, 12);
 
    for (unsigned int ifile = 0; ifile < input_sim_file.size(); ifile++){
        cout<<"analyzing file "<<ifile<<endl;
        
        TFile *file=new TFile(input_sim_file[ifile].c_str(), "READ");
	    TTree *tree_header = 0;
	    vector <int> *evn=0,*evn_type=0;
        vector <double> *beamPol=0;
        vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0, *var9=0, *var10 = 0;
        
        tree_header = (TTree*) file->Get("userHeader");
        tree_header->SetBranchAddress("userVar001",&var1);     //1
        tree_header->SetBranchAddress("userVar012",&var2);     //x
        tree_header->SetBranchAddress("userVar013",&var3);     //y
        tree_header->SetBranchAddress("userVar014",&var4);     //W
        tree_header->SetBranchAddress("userVar015",&var5);     //Q2
        tree_header->SetBranchAddress("userVar006",&var6);     //rate
        tree_header->SetBranchAddress("userVar007",&var7);     //rate_rad
        tree_header->SetBranchAddress("userVar008",&var8);     //Wmrate
        tree_header->SetBranchAddress("userVar009",&var9);     //Abeam
        tree_header->SetBranchAddress("userVar011",&var10);    //Ei
        
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
	    
	    TTree *tree_flux = (TTree*) file->Get("flux");
	    vector<int> *flux_id=0,*flux_hitn=0;
	    vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	    vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,
	    *flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	    
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
	    
	    long int N_events = (long int)tree_header->GetEntries();
        cout << "output has entry " << tree_header->GetEntries() << endl;
        
        for(long int entry=0;entry<N_events-1; entry++){
            tree_header->GetEntry(entry);
            tree_generated->GetEntry(entry);
            tree_flux->GetEntry(entry);
            
            //cout<<entry<<" "<<var6->size()<<" "<<gen_pid->size()<<endl;

            if (var6->size() != 1)    continue;
            if (gen_pid->size() != 1) continue;
            
            x=var2->at(0);	
	        y=var3->at(0);
	        W=var4->at(0);		
	        Q2=var5->at(0);
	        rate = var6->at(0)/numberOfFile;
		    rateRad = var7->at(0)/numberOfFile;
            Abeam = var9->at(0);
            Ei = var10->at(0);
		    
		px_gen=gen_px->at(0)/1000.;
	        py_gen=gen_py->at(0)/1000.;
	        pz_gen=gen_pz->at(0)/1000.;
	        vx_gen=gen_vx->at(0);
	        vy_gen=gen_vy->at(0);
	        vz_gen=gen_vz->at(0);
            double mom = sqrt(px_gen*px_gen + py_gen*py_gen + pz_gen*pz_gen);
            double theta = acos(pz_gen / mom) * 180. / TMath::Pi();

            hist->Fill(x, Q2);
            hist1->Fill(theta, mom/1000.);
            bool writeFlag = false;
            ecP = -1.;
            ecR = -1.;
            for (UInt_t j=0;j<flux_hitn->size();j++) {

                int detector_ID=flux_id->at(j)/1000000;
                int subdetector_ID=(flux_id->at(j)%1000000)/100000;
                int subsubdetector_ID=((flux_id->at(j)%1000000)%100000)/10000;		  
                int component_ID=flux_id->at(j)%10000;      
	  
                double hit_r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/1e1; //mm to cm
                double hit_p=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j))/1e3;  //MeV to GeV

                int hit_id=-1;
                if (detector_ID==1 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=0;
                if (detector_ID==1 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=1;	  
                if (detector_ID==1 && subdetector_ID == 3 && subsubdetector_ID == 1) hit_id=2;	  
                if (detector_ID==1 && subdetector_ID == 4 && subsubdetector_ID == 1) hit_id=3;	  
                if (detector_ID==1 && subdetector_ID == 5 && subsubdetector_ID == 1) hit_id=4;	  
                if (detector_ID==1 && subdetector_ID == 6 && subsubdetector_ID == 1) hit_id=5;	        
                if (detector_ID==2 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=6;
                if (detector_ID==2 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=7;	              
                if (detector_ID==5 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=8;
                if (detector_ID==5 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=9;	                          
                if (detector_ID==3 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=10;
                if (detector_ID==3 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=11;

                if (detector_ID==4 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=12;  

                if (detector_ID==6 && subdetector_ID == 1 && subsubdetector_ID == 1) hit_id=13;
                if (detector_ID==6 && subdetector_ID == 2 && subsubdetector_ID == 1) hit_id=14;  
                
                if(hit_id==10){   //FAEC 
                    if (hit_r<rin_cut_FA || hit_r>rout_cut_FA) continue;

                    if(TMath::Nint(flux_tid->at(j))==1) {
                        ecR = hit_r;
                        ecP = hit_p;
                        writeFlag = true;
                    }
                }
                	
            }
            //writeFlag = true;
            if (writeFlag) outTree->Fill();
        }
    }

    //TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    //hist1->Draw();
    outFile->cd();
    outTree->Write();
    outFile->Close();
}
