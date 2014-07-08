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
#include "./solenoid_lib/sole_inter.h"
#include "TMatrix.h"
#include "TMatrixD.h"

#define PI 3.14159265
const int N=3;

void getcoef(Double_t,Double_t*,Double_t*);
void get_results1(Int_t,Int_t,Int_t,Int_t,Int_t,Int_t);

int main(Int_t argc, char *argv[]){
  if (argc != 7) {
    cout << "usage:  target_flag energy_flag particle_flag Q2_flag pt_flag z_flag" << endl;
    return 0;
  }else{
 
    Int_t target_flag= atoi(argv[1]);
    Int_t energy_flag= atoi(argv[2]);
    Int_t particle_flag= atoi(argv[3]);
    Int_t Q2_flag= atoi(argv[4]);
    Int_t pt_flag= atoi(argv[5]);
    Int_t z_flag= atoi(argv[6]);
    
    get_results1( target_flag, energy_flag, particle_flag, Q2_flag, pt_flag, z_flag);
  }

  // gSystem->Load("libSole.so");
//   gSystem->Load("/home/xqian/root/root/lib/libMatrix.so");
  
}
 
void get_results1(Int_t target_flag,Int_t energy_flag,Int_t particle_flag,Int_t Q2_flag,Int_t pt_flag,Int_t z_flag){
  // Int_t target_flag; //  1 for proton; 2 for deuteron; 3 for 3he
//   Int_t energy_flag; // 1 for 11+60  ; 2 for 3 + 20; 3; 4; 5 for 5x100
//   Int_t Q2_flag; // 1 for Q2_flag <=10; 2 for Q2_flag>10;
//   Int_t pt_flag; // 1-15
//   Int_t z_flag; // 1-12
//   Int_t particle_flag;

  TString filename,log_filename,data_filename;
  TString log_prefix,data_prefix;
  TString header,posfix;
  
  ofstream outfile;
  // loop throug the target_flag
  // for (particle_flag = 1; particle_flag<=2; particle_flag ++ ){
  if (particle_flag==1){
    log_prefix = "./database_p/";
    data_prefix = "./out_rootfiles_p/";
  }else{
    log_prefix = "./database_m/";
    data_prefix = "./out_rootfiles_m/";
  }    
  //  for (target_flag = 1; target_flag <=3; target_flag ++){
  //       for (energy_flag = 1; energy_flag<=2; energy_flag ++ ){
  if (target_flag==1){
    if (energy_flag ==1){
      header = "Collider_p_pip_3_20_";
    }else if (energy_flag ==2){
      header = "Collider_p_pip_3_12_";
    }
  }	

  if (pt_flag>=6){
    posfix.Form("%d_%d_%d.root",(Q2_flag-1)*2+2,z_flag,pt_flag);
  }else{
    posfix.Form("%d_%d_%d.root",(Q2_flag-1)*2+1,z_flag,pt_flag);
  }
  log_filename = log_prefix + header + posfix;
  data_filename = data_prefix + header + posfix;
  
  Int_t ncount[2];
  Double_t counter[2][5000],Q2[5000],x[5000],z[5000],y[5000],pt[5000],nevent[5000];
  ifstream infile(log_filename);
  TFile file(data_filename);
  TH1F *h1;
  infile >> ncount[0] >> ncount[1];
  filename.Form("./results/%d_%d_%d_%d_%d_%d.dat",particle_flag,target_flag,energy_flag,Q2_flag,z_flag,pt_flag);
  outfile.open(filename);


  Double_t x1[360],weight[360];
  Double_t angle[4];
  Double_t coef[3];
  Double_t coverage;

  outfile << ncount[0] << "\t" << ncount[1] << endl;
  for (Int_t i=0;i!=ncount[0];i++){
    for (Int_t j=0;j!=ncount[1];j++){
      infile >> counter[0][i*ncount[1]+j] >> counter[1][i*ncount[1]+j] >> Q2[i*ncount[1]+j] >> x[i*ncount[1]+j] >> z[i*ncount[1]+j] >> y[i*ncount[1]+j] >> pt[i*ncount[1]+j] >> nevent[i*ncount[1]+j];

      if(nevent[i*ncount[1]+j]<1) continue;

      h1 = (TH1F*)file.Get(Form("h_%d_%d",i,j));

      for (Int_t k=0;k!=360;k++){
	x1[k] = h1->GetBinContent(k+1);
      }
      sole_inter sole;
      sole.init(360,x1);
      sole.connect();
      sole.get_new(x1);
      sole.get_limit(angle);
      for (Int_t k=0;k!=360;k++){
	weight[k] = sole.get_accep(k+0.5);
      }
      coverage = (angle[1]-angle[0]+angle[3]-angle[2])*PI/180.;
      getcoef(coverage,coef,weight);

      // cout << i << "\t" << j << "\t" << coef[0] << endl;
      

      if (nevent[i*ncount[1]+j]>0.){
	outfile << counter[0][i*ncount[1]+j] << " \t" << counter[1][i*ncount[1]+j] << " \t" << Q2[i*ncount[1]+j] << " \t" << x[i*ncount[1]+j] << " \t" << z[i*ncount[1]+j] << " \t" << y[i*ncount[1]+j] << " \t" << pt[i*ncount[1]+j] << " \t" << 1./sqrt(nevent[i*ncount[1]+j]) << " \t" << coverage << " \t" << coef[0] << " \t" << coef[1] << " \t" << coef[2] << endl;
      }else{
	outfile << counter[0][i*ncount[1]+j] << " \t" << counter[1][i*ncount[1]+j] << " \t" << Q2[i*ncount[1]+j] << " \t" << x[i*ncount[1]+j] << " \t" << z[i*ncount[1]+j] << " \t" << y[i*ncount[1]+j] << " \t" << pt[i*ncount[1]+j] << " \t" << 0. << " \t" << coverage << " \t" << coef[0] << " \t" << coef[1] << " \t" << coef[2] << endl;
      }
    }
  }
  infile.close();
  outfile.close();
  file.Close();

  
}



void getcoef(Double_t angle, Double_t* coef, Double_t* acpt){
//x->phi y->phih 3 terms,w/ acpt
  Double_t a_matrix[N*N]={};
  Double_t x,y;
  for(Int_t i=0;i<180;i++){
    x = PI*(i+0.5)/180.; //phi

    for(Int_t j=0;j<360;j++){
      y = PI*(j+0.5)/180.; //phi_h
      a_matrix[0] += (sin(x)*sin(x))*PI/180.*PI/180.*acpt[j];
      a_matrix[1] += (sin(x)*sin(2*y-x))*PI/180.*PI/180.*acpt[j];
      a_matrix[2] += (sin(x)*sin(2*y+x))*PI/180.*PI/180.*acpt[j];

      a_matrix[N+1] += (sin(2*y-x)*sin(2*y-x))*PI/180.*PI/180.*acpt[j];
      a_matrix[N+2] += (sin(2*y-x)*sin(2*y+x))*PI/180.*PI/180.*acpt[j];

      a_matrix[2*N+2] += (sin(2*y+x)*sin(2*y+x))*PI/180.*PI/180.*acpt[j];
    }
  }
      a_matrix[N] = a_matrix[1];
      a_matrix[2*N] = a_matrix[2];
      a_matrix[2*N+1] = a_matrix[N+2];
//       cout << "\t Initialize a_matrix done!" << endl;

  TMatrixD a(N,N,a_matrix);
  TMatrixD asav = a;
  a.Invert();
//   cout << "\t Initialize a invert done!" << endl;

  Double_t qx[N]={};
  for(Int_t i=0;i<180;i++){
    x = PI*(i+0.5)/180.; //phi
    for(Int_t j=0;j<360;j++){
      y = PI*(j+0.5)/180.; //phi_h
      for(Int_t k=0;k<N;k++){
	qx[k] += (pow((a(k,0)*sin(x)+a(k,1)*sin(2*y-x)+a(k,2)*sin(2*y+x)),2))*PI/180.*PI/180.*acpt[j];
      }
    }
  }
  for(Int_t i=0;i<N;i++){
    qx[i] *= PI*angle;
    coef[i] = sqrt(qx[i]/2);
  }

return;
}
