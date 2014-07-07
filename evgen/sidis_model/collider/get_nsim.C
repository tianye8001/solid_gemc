#include <TROOT.h>
#include "TApplication.h"
#include "Rtypes.h"
#include "math.h"
#include "iostream.h"
#include "fstream.h"
#include "TFile.h"
#include "TString.h"
#include "TChain.h"



int main(Int_t argc, char *argv[]){
  if (argc != 4) {
    cout << "usage: ./skim filename filenum" << endl;
    return 0;
  }else{
    TString prefix = "./old_rootfiles/";
    TString filename = argv[1];
    Int_t filenum = atoi(argv[2]);
    Float_t ele_energy = atof(argv[3]);

    TChain *T = new TChain("T","T");
    TString posfix;
    posfix.Form("_%d.root",filenum);
    filename = prefix + filename + posfix;
    T->AddFile(filename);
    
    Double_t nsim;
    T->SetBranchAddress("nsim",&nsim);

    Double_t nsimulated;
    
    T->GetEntry(T->GetEntries()-1);
    
    // take into account the simulated acceptance etc
    Double_t ele_accep = (1-cos(150./180.*3.1415926))*2*3.1415926*(ele_energy*3.-0.7);
     Double_t had_accep = (1+1)*2*3.1415926*(10.-0.7);

//     Double_t had_accep = (1+1)*2*3.1415926*(40.-0.1);
    Double_t luminosity = 20; // 20 x 10^{33} nucleons/cm^2/s
    Double_t time = 100; // days
    // nevents = dxs (nbar) * L (nucleons/cm^2/s) * T(days) 
    // days = 86400s;
    // nbar = 10-9 barn = 10^-9 * 10^-28 m^2 = 10^-9 * 10^-28 *10^4 cm^2 = 10^-33 cm^2
    // so 2e34 * 10-33 * 86400 *100 = 1.728e8
    
    Double_t norm_factor = luminosity * 86400 * time * ele_accep * had_accep;
    
//     Int_t ncount = 0;
//     T->GetEntry(0);
//     Double_t nsim_save;
//     Double_t temp;
//     nsim_save = nsim;


//     for (Int_t i=0;i!=T->GetEntries();i++){
//       T->GetEntry(i);
      
      
//       if (fabs(nsim-nsim_save) > 1.e9){
// 	ncount ++;
//       }

//       nsim_save = nsim;
//     }
    
    
//     if (ncount > 0.){
//       nsimulated = (ncount*2. - 1.) * 2147483647. + nsim + 2147483647.;
//     }else{
//       nsimulated = nsim;
//     }

    nsimulated = nsim;
    
    cout << norm_factor << "\t" << nsimulated << endl;
  }
}
