#include "SolidData.hh" 
#include "SolidDatum.hh" 
#include "SolidOutput.hh"

#include <stdlib.h>

SolidData::SolidData(const G4String &n) : fName(n) {
    const char *fname = "SolidData()";

    const char *name = fName.data();
    int len = strlen(name)-1;

    // Search backwards for slashes and just keep
    // the main detector name
    //
    // This is what will be used in the ROOT tree
    // for the branch names
    while(len>0 && name[len] != '/'){ len--; }
    if( len==0 && name[0] != '/' ){ fBranchName = fName; } else {
	fBranchName = fName(len+1,strlen(name));
    }

    fOutput = SolidOutput::GetInstance();
    if( !fOutput ){
	fprintf(stderr, "%s::%s  Warning: SolidOutput manager not found\n",
	       GetClassName(), fname);
    }
}

int SolidData::ResetData(){
    return fData.size();
}

/**
 * Clears data that is set
 * Returns number of data destroyed
 */
int SolidData::ClearData(){
    int n = fData.size();
    fData.clear();
    return n;
}

/**
 * Make this class available for output
 */
int SolidData::RegisterData(){
    unsigned int i;
    if( !fOutput ) return 0;
    // No error if fOutput is NULL, 
    // we warned at initialization

    for( i = 0; i < fData.size(); i++ ){
	fData[i]->SetOutput(fOutput);
    }

    return fData.size();
}
