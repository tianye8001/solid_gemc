#include "SolidDatum.hh"
#include "SolidData.hh"
#include "SolidOutput.hh"

#include <TTree.h>

SolidDatum::SolidDatum(SolidData *d, vartype_t type, G4String name, int len ){
    fName = d->GetName()+G4String(".")+name;
    fLen  = len;
    fOutput = NULL;
    fType = type;

    Init();

    d->AddDatum(this);
}

void SolidDatum::Init(){
    switch( fType ){
	case kInt:
	    fROOTtype = "I";
	    fData = new int[fLen];
	    break;
    	case kDouble:
	    fROOTtype = "D";
	    fData = new double[fLen];
	    break;
    	case kString:
	    fData = NULL;
	default:
	    fROOTtype = "???";
    }


}

SolidDatum::~SolidDatum(){
    UnsetBranch();
}


void SolidDatum::SetOutput(SolidOutput *out){
    // Passing it a new tree resets
    // where we are
    if( fOutput ){
	UnsetBranch();
    }

    if( !out ){
	fOutput = NULL;
	return;
    }

    fOutput = out;
    SetupBranch();
}

void SolidDatum::UnsetBranch(){
    TTree *t;
    
    if( !fOutput ){ return; }    

    t = fOutput->GetTree();
    // Tree may be destroyed by fOutput
    // already... make sure

    if( t ){
	t->ResetBranchAddress(fNbranch);
	t->ResetBranchAddress(fDbranch);
    }
    return;
}

void SolidDatum::SetupBranch(){
    char lname[255], bname[255];

    // Output not set, so meaningless
    if( !fOutput ){ return; }

    // Tree may be destroyed by fOutput
    // already... make sure
    TTree *t = fOutput->GetTree();

    if(t){
	if( fType != kString ){
	    // Data length type
	    sprintf(bname, "Ndata.%s", fName.data());
	    sprintf(lname, "%s/I", bname);
	    fNbranch = t->Branch(bname, &fLen, lname);

	    sprintf(lname, "%s[Ndata.%s]/%s", 
		    fName.data(), fName.data(), fROOTtype.data());
	    fDbranch = t->Branch(fName.data(), fData, lname);
	} else {
	    fNbranch = NULL;
	    fDbranch = t->Branch(fName.data(), &fStrData);
	}
    }

    return;
}

void SolidDatum::SetBranchAddress(){
    // If output not set, this is meaningless
    if( !fOutput ){ return; }

    // Tree may be destroyed by fOutput
    // already... make sure
    TTree *t = fOutput->GetTree();

    if(t){
	t->SetBranchAddress(fName.data(), fData);
    }
}

//////////////////////////////



int SolidDatum::Resize(unsigned int len){
    int ret;
    
    // Strings don't need to be resized
    if( fType == kString ){ return 0; }

    // We already have enough space
    if( fLen >= len ){ return 0; }
    
    ret = len - fLen;

    switch( fType ){
	case kInt:
	    delete   (int *)fData;
	    fData = new int[len];
	    break;
	case kDouble:
	    delete   (double *)fData;
	    fData = new double[len];
	    break;
	default:
	    break;
    }

    fLen = len;

    // Update the branch address
    // in the tree
    SetBranchAddress();

    return ret;
}


int SolidDatum::Fill(unsigned int n, void *d){
    Resize(n);

    unsigned int i;

    switch( fType ){
	case kInt:
	    memcpy(fData, d, sizeof(int)*n);
	    break;
	case kDouble:
	    memcpy(fData, d, sizeof(double)*n);
	    break;
	case kString:
	    for( i = 0; i < n; i++ ){
		fStrData.push_back(((std::string *) d)[i]);
	    }
	    break;
	default:
	    break;
    }

    fLen = n;
    return fLen;
}

int SolidDatum::Fill(std::vector<int> v){
    Resize(v.size());
    unsigned int i;

    for( i = 0; i < v.size(); i++ ){
	((int *)fData)[i] = v[i];
    }

    fLen = v.size();

    return fLen;
}

int SolidDatum::Fill(std::vector<double> v){
    Resize(v.size());
    unsigned int i;

    for( i = 0; i < v.size(); i++ ){
	((double *)fData)[i] = v[i];
    }

    fLen = v.size();

    return fLen;
}

int SolidDatum::Fill(std::vector<std::string> v){
    unsigned int i;

    fStrData.clear();
    for( i = 0; i < v.size(); i++ ){
	fStrData.push_back(v[i]);
    }

    fLen = v.size();

    return fLen;
}

int SolidDatum::Fill(int t, int l){

    if( l < 0 ){
	Resize(1);
	((int *)fData)[0] = t;
	fLen = 1;
    } else {
	((int *)fData)[l] = t;
    }

    return fLen;
}

int SolidDatum::Fill(double t, int l){
    if( l < 0 ){
	Resize(1);
	((double *)fData)[0] = t;
	fLen = 1;
    } else {
	((double *)fData)[l] = t;
    }

    return fLen;
}

int SolidDatum::Fill(std::string t){
    fStrData.clear();
    fStrData.push_back(t);
    fLen = 1;

    return fLen;
}
