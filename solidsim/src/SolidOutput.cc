/**
 SolidOutput

 Output class for solid

 Here we create and fill trees
*/

#include "SolidOutput.hh"
#include "SolidData.hh"
#include "SolidDatum.hh"

#include "TFile.h"
#include "TTree.h"

#include <stdlib.h>

int SolidOutput::__SolidOutputInit = 0; 
SolidOutput *SolidOutput::__SolidOutputPtr = NULL;

SolidOutput::SolidOutput(){
    const char *fname = "SolidOutput()";
    if( __SolidOutputInit ){
	fprintf(stderr, "%s::%s  Already instantiated\n",
		GetClassName(), fname);
	exit(1);
    } else {
	__SolidOutputPtr = this;
	__SolidOutputInit = true;
    }

    // Default output file name
    fOutputFileName = "output.root";

    fFile = NULL;

    fTree = new TTree("T", "SoLID Simluation Output");

    if(!fTree){
	fprintf(stderr, "%s::%s  Something went wrong making the tree\n",
		GetClassName(), fname);
	exit(1);
    }
}

SolidOutput::~SolidOutput(){
    __SolidOutputInit = 0;
}

SolidOutput *SolidOutput::GetInstance(){
    if( __SolidOutputInit ){
	return __SolidOutputPtr;
    } else {
	return NULL;
    }
}

/*!
   Create output ROOT file and tree with
   empty branches
*/
int SolidOutput::CreateOutputFile(){
    const char *fname = "CreateOutputFile()";

    fFile = new TFile(fOutputFileName, "RECREATE");

    if(fFile->IsZombie()){
	fprintf(stderr, "%s::%s  Could not create output file %s\
		(is zombie)\n",
		GetClassName(), fname, fOutputFileName.data());
	exit(1);
    }
    fFile->cd();

    return 0;
}

int SolidOutput::CloseOutputFile(){
    fFile->cd();
    fTree->Write("T", TObject::kOverwrite);
    fFile->Close();
    
    // Safe?
    fTree->ResetBranchAddresses();

    delete fTree;
    fTree = 0;
    delete fFile;
    fFile = 0;

    return 0;
}

int SolidOutput::FillTree(){
    const char *fname = "FillTree";
    if( !fTree ){
	fprintf(stderr, "%s::%s  Tree does not exist (set to NULL)\n",
		GetClassName(), fname);
	return -1;
    }

    int ret = fTree->Fill();

    if( ret < 0 ){
	fprintf(stderr, "%s::%s  Write error occured\n",
		GetClassName(), fname);
	return -1;
    }

    return 0;
}
