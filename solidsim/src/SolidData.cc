#include "SolidData.hh" 
#include "SolidDatum.hh" 
#include "SolidOutput.hh"

SolidData::SolidData(const G4String &n) : fName(n) {
    const char *fname = "SolidData()";

    fOutput = SolidOutput::GetInstance();
    if( !fOutput ){
	fprintf(stderr, "%s::%s  Warning: SolidOutput manager not found\n",
	       GetClassName(), fname);
    }
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
