#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TMath.h"
#include "TSystem.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "snprintf.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

void Print_Usage();
void Parse_Args(int *argc, char **argv);

extern TSystem *gSystem;


//////////////////////////////////////////////////////////////
// Options Globals
//////////////////////////////////////////////////////////////
char  outfilename[128];
char  infilename[100];


int main (int argc, char **argv) {

  if(argc < 5){
    Print_Usage();
    exit(1);
  }
  
  Parse_Args( &argc, argv );

  double weight;
  double theta;
  double phi;
  double Ef;
  double x;
  double W;
  double y;
  double crs;
  double f1;
  double f2;
  double f1gz;
  double f3gz;
  double g1gz;
  double g5gz;
  double Q2;
  double eta_gZ;
  double rate;
  double pdf[6];
  double Dpdf[5];
  
  double Abeam;
  double Y;
  
  double A_L;
  double Y_L;
  double eta_L;
  
  double A_T;
  double Y_T;
  double eta_T;

  TChain input_chain("T");
  input_chain.Add(infilename);

  input_chain.SetBranchAddress("weight",&weight);
  input_chain.SetBranchAddress("theta",&theta);
  input_chain.SetBranchAddress("phi",&phi);
  input_chain.SetBranchAddress("Ef",&Ef);
  input_chain.SetBranchAddress("x",&x);
  input_chain.SetBranchAddress("W",&W);
  input_chain.SetBranchAddress("y",&y);
  input_chain.SetBranchAddress("crs",&crs);
  input_chain.SetBranchAddress("f1",&f1);
  input_chain.SetBranchAddress("f2",&f2);
  input_chain.SetBranchAddress("f1gz",&f1gz);
  input_chain.SetBranchAddress("f3gz",&f3gz);
  input_chain.SetBranchAddress("g1gz",&g1gz);
  input_chain.SetBranchAddress("g5gz",&g5gz);
  input_chain.SetBranchAddress("Q2",&Q2);
  input_chain.SetBranchAddress("eta_gZ",&eta_gZ);
  input_chain.SetBranchAddress("rate",&rate);
  input_chain.SetBranchAddress("pdf",&pdf);
  input_chain.SetBranchAddress("Dpdf",&Dpdf);
  
  input_chain.SetBranchAddress("Abeam",&Abeam);
  input_chain.SetBranchAddress("Y",&Y);
  
  input_chain.SetBranchAddress("A_L",&A_L);
  input_chain.SetBranchAddress("Y_L",&Y_L);
  input_chain.SetBranchAddress("eta_L",&eta_L);
  
  input_chain.SetBranchAddress("A_T",&A_T);
  input_chain.SetBranchAddress("Y_T",&Y_T);
  input_chain.SetBranchAddress("eta_T",&eta_T);  

  Int_t nentries = (Int_t)input_chain.GetEntries();


  // Variables used for determine the lund output

  double nu; // energy of the Gamma*
  double MASS_p = 0.938; // mass proton in GeV 
  double px,py,pz ;
  double vx,vy,vz ;
  
  
  ofstream OUT (outfilename);
  for (int i=0; i<nentries ; i++) {
    input_chain.GetEntry(i);
    if(i % 100000 == 0 ){
      printf("Analyzed %09d events of total %09d \n",i,nentries);
     }

    if (x>0)   nu = Q2 / (2 * MASS_p * x) ;
    else nu = 0;

    px = Ef * sin(theta) * cos(phi);
    py = Ef * sin(theta)* sin(phi);
    pz = Ef * cos(theta);

    vx = 0.0;
    vy = 0.0;
    vz = 0.0;

      

    OUT << "1" << " \t " << "2"  << " \t " << "1"  << " \t " << "0"  << " \t " << "0" << x << " \t " << y  << " \t " << W  << " \t " << Q2  << " \t " << nu << endl;
    OUT << " \t " << "1" << " \t " << "-1" << " \t " << "1" << " \t " << "11" << " \t " << "0" << " \t " << "0" << " \t " << px << " \t " << py << " \t " << pz << " \t " << Ef << " \t " << "0.00051 " << " \t " << vx  << " \t " << vy << " \t " << vz << endl; 

  }

  OUT.close();


}




//***********************************************************************************
//  Parse arguments 
//***********************************************************************************
void Parse_Args(int *argc, char **argv){
  // Read and parse all the options, leaving only input files in the
  // argv array.
  // This version, all options flags are globals.
#define REMOVE_ONE {(*argc)--;for(j=i;j<(*argc);j++)argv[j]=argv[j+1];i--;}
#define I_PLUS_PLUS if((i+1)<(*argc)){i++;}else{break;}
  int  i,j;


  for( i=1; i<(*argc); i++ )  
    {
      if( argv[i][0] == '-' ) {
	if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"-outfile")==0)
	  {
	    I_PLUS_PLUS;
	    strcpy(outfilename,argv[i]);
	    REMOVE_ONE;
	  }
	else if(strcmp(argv[i],"-i")==0 || strcmp(argv[i],"-infile")==0)
	  {
	    I_PLUS_PLUS;
	    strcpy(infilename,argv[i]);
	    REMOVE_ONE;
	  }
	else if(strcmp(argv[i],"-help")==0||strcmp(argv[i],"-h")==0)  
	  {
	    Print_Usage();
	    exit(1);
	  }
	else
	  {
	    fprintf(stderr,"\nI did not understand the option : %s\n",argv[i]);
	    Print_Usage();
	    exit(1);
	  }
	/* KILL the option from list */
	REMOVE_ONE;
      }
    }
}

//***********************************************************************************
//  Print Usage 
//***********************************************************************************

void Print_Usage() {
  cout << " root2lund : This Program translate the output from eicRate in LUND format \n";  
  cout << " Usage: root2lund -o outputfile -i inputfile \n";  
  cout << "     -o outputfile   - output file name (example pluto.lund)  \n";  
  cout << "     -i inputfile   - input file name (example pluto.root)  \n";  
  cout << "     -h help, print this message \n";
  cout << " --- \n\n";
}
