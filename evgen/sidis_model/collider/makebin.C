#include <TROOT.h>
#include "TApplication.h"
#include "Rtypes.h"
#include "math.h"
#include "iostream.h"
#include "fstream.h"
#include "TFile.h"
#include "TString.h"
#include "TChain.h"
#include "TCut.h"
#include "TH1F.h"
#include "TF1.h" 

int main(Int_t argc, char *argv[]){
  if (argc != 12) {
    cout << "usage: $directory $fac1 $fac2 $target_flag $particle_flag $ele_energy $hadron_energy $Q2_flag $z_flag $pt_flag $fudgeok" << endl;
    return 0;
  }else{

    TString prefix = "./skim/skim_rootfiles/";
    
    TString filename = argv[1];
    Double_t factor1 = atof(argv[2]);
    Double_t factor2 = atof(argv[3]);
    Int_t target_flag = atoi(argv[4]);
    Int_t particle_flag = atoi(argv[5]);
    Double_t ele_energy = atof(argv[6]);
    Double_t hadron_energy = atof(argv[7]);
    Int_t Q2_flag = atoi(argv[8]);
    Int_t z_flag = atoi(argv[9]);
    Int_t pt_flag = atoi(argv[10]);
    Int_t fudgeok = atoi(argv[11]);

    Double_t fudge_factor=1.;
        
    TString new_filename;
    new_filename = prefix + filename;
    TChain *T = new TChain("T","T");
    T->AddFile(new_filename);
    
    if (particle_flag==1){
      prefix = "./out_rootfiles_p/";
    }else{ 
      prefix = "./out_rootfiles_m/";
    }
    
    new_filename = prefix + filename;

    TFile *file = new TFile(new_filename,"RECREATE");
    
    if (particle_flag==1){
      prefix = "./database_p/";
    }else{
      prefix = "./database_m/";
    }
    
    new_filename = prefix + filename;
    ofstream outfile(new_filename);

    Float_t q2llimit = 0., q2hlimit = 20.;
    Float_t xllimit = -0.1, xhlimit = 0.7;

    //Q2
    TH1F *h1  =new TH1F("h1","h1",1000,0.,20.);
    //x
    TH1F *h2 = new TH1F("h2","h2",1000,-0.1,0.7);
    //Q2
    TH1F *h1Q2  =new TH1F("h1Q2","h1Q2",1000,0.,20.);
    //x 
    TH1F *h1x = new TH1F("h1x","h1x",1000,-0.1,0.7);
    // z
    TH1F *h1z = new TH1F("h1z","h1z",1000,0.2,0.8);
    // y 
    TH1F *h1y = new TH1F("h1y","h1y",1000,0.,1.);
    // pt
    TH1F *h1pt = new TH1F("h1pt","h1pt",1000.,0.,10.);

    // dilution factor
    TH1F *h1di = new TH1F("h1di","h1di",1000.,0.,10.);
    TH1F *h1phi_h = new TH1F("h1phi_h","h1phi_h",360,0.,360.);
    TH1F *h2phi_h = new TH1F("h2phi_h","h2phi_h",360,0.,360.);
    
    TString cut1,cut2;
    if (particle_flag==1){
      cut1.Form("dxs_hp*%f/%f",factor1,factor2);
    }else{
      cut1.Form("dxs_hm*%f/%f",factor1,factor2);
    }
    
    
    TCut cut(cut1);
    T->Project("h1","Q2",cut);
    h1->SetDirectory(file);
    
    Double_t total_eve = h1->GetSum(); 
    
    Double_t single_bin;
    Double_t dilute_factor,target_factor;
    
    // 100 days, 2e34 /cm^2/s ; the last factor is sqrt(2) for the angular separation
    dilute_factor = 0.5 * 0.7 * 0.7 / 2. ; //50% overall efficiency + 70% polarization  


    TString filename1;
    Int_t count1,count2,n1,n2;
    ifstream infile;


    if(ele_energy == 3){//3x12

      filename1.Form("./results1/1_1_2_%d_%d_%d.dat",Q2_flag,z_flag,pt_flag);
      infile.open(filename1);
      infile >> n1 >> n2;
      infile.close();
      count1 = n1+1;
      count2 = n1*n2/count1;
      if(count1>count2){
	count1 = n1;
	count2 = n2;
      }

      if (target_flag==1){
	//proton 200 days *2 | reduce L to 4e32 from 2e34; /50
	target_factor = 1.;
	dilute_factor *= 2./50.;
      }
    }

    total_eve *= dilute_factor*target_factor*fudge_factor;
    

    TString histoname;
    
    Int_t xbin[5] = {}, Q2bin;
    
    Double_t x_min,x_max,Q2_min,Q2_max,nevent_Q2,nevent_x;


//     Q2bin = sqrt(total_bin/3.);
    Q2bin = count1; //sqrt(total_bin);
    if (Q2bin<1) Q2bin = 1;
    xbin[0] = count2 + 2; //total_bin/Q2bin;
    xbin[1] = count2 - 2;
    xbin[2] = 2;
    if(xbin[1]<1){
      xbin[1] = 1;
      xbin[2] = 1;
    }
    

    outfile << Q2bin << "\t" << xbin[0] << endl;

//     Q2_min = 0.; Q2b_min = 1;Q2b_max = 1;
//     //loop through x and Q2 bin
    for (Int_t i=0;i!=Q2bin;i++){

      Q2_min = (q2hlimit - q2llimit)/Q2bin*i+q2llimit;
      Q2_max = (q2hlimit - q2llimit)/Q2bin*(i+1)+q2llimit;
      
      cut2.Form("(Q2>=%f&&Q2<%f)",Q2_min,Q2_max);
      cut2 = cut1 + "*" + cut2;
      cut = cut2;
      h2->Reset();
      T->Project("h2","x",cut);

      for (Int_t j=0;j!=xbin[i];j++){

	h1di->Reset();
	h1Q2->Reset();
	h1x->Reset();
	h1y->Reset();
	h1z->Reset();
	h1pt->Reset();
	h1phi_h->Reset();
	h1phi_h->Reset();

	x_min = (xhlimit - xllimit)/xbin[i]*j+xllimit;
	x_max = (xhlimit - xllimit)/xbin[i]*(j+1)+xllimit;

	cut2.Form("(Q2>=%f&&Q2<%f&&x>=%f&&x<%f)",Q2_min,Q2_max,x_min,x_max);
	cut2 = cut1 + "*" + cut2;
	cut = cut2;

// 	cout << Q2_min << " " << x_min << endl;
	
	T->Project("h1Q2","Q2",cut);
	T->Project("h1x","x",cut);
	T->Project("h1z","z",cut);
	T->Project("h1y","y",cut);
	T->Project("h1pt","pt",cut);

	if (particle_flag==1){
	  T->Project("h1di","dilute_p",cut);
	}else{
	  T->Project("h1di","dilute_m",cut);
	}
	
	Double_t temp_dilute = h1di->GetMean();
	if (target_flag ==1){
	  outfile << i << " \t" << j << " \t" << h1Q2->GetMean() << " \t" << h1x->GetMean() << " \t" << h1z->GetMean() << " \t" << h1y->GetMean() << " \t" << h1pt->GetMean() << " \t" << h1Q2->GetSum()*dilute_factor*fudge_factor << endl;
	}else if (target_flag == 2 ){
	  // Need to take into account the proton polarization
	  outfile << i << " \t" << j << " \t" << h1Q2->GetMean() << " \t" << h1x->GetMean() << " \t" << h1z->GetMean() << " \t" << h1y->GetMean() << " \t" << h1pt->GetMean() << " \t" << h1Q2->GetSum()*dilute_factor*0.88*0.88/(temp_dilute*temp_dilute*4. + (1 + temp_dilute)*(1+temp_dilute))*fudge_factor << endl;
	}else if (target_flag == 3){
	  outfile << i << " \t" << j << " \t" << h1Q2->GetMean() << " \t" << h1x->GetMean() << " \t" << h1z->GetMean() << " \t" << h1y->GetMean() << " \t" << h1pt->GetMean() << " \t" << h1Q2->GetSum()*dilute_factor*0.865*0.865/((1+2.*temp_dilute)*(1+2.*temp_dilute))*fudge_factor << endl;
	}
	

	histoname.Form("h_%d_%d",i,j);
	TH1F *hhh = (TH1F*)h1phi_h->Clone(histoname);
	
	cut2.Form("(Q2>=%f&&Q2<%f&&x>=%f&&x<%f&&phi_h>0.)",Q2_min,Q2_max,x_min,x_max);
	cut2 = cut1 + "*" + cut2;
	cut = cut2;
	T->Project("h1phi_h","phi_h*180./3.1415926",cut);
	cut2.Form("(Q2>=%f&&Q2<%f&&x>=%f&&x<%f&&phi_h<0.)",Q2_min,Q2_max,x_min,x_max);
	cut2 = cut1 + "*" + cut2;
	cut = cut2;
	T->Project("h2phi_h","phi_h*180./3.1415926+360.",cut);
	
	hhh->Add(h1phi_h);
	hhh->Add(h2phi_h);

	hhh->SetDirectory(file);
	
//   	xb_min = xb_max;
  	x_min = x_max;
      }
      
      
//       Q2b_min = Q2b_max;
      Q2_min = Q2_max;
    }
    


    file->Write();
    file->Close();
    outfile.close();
  }
}
