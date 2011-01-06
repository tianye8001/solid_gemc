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

#include <stack>

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

    fOutListDefined = false;

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
	fprintf(stderr, "%s::%s  Could not create output file %s (is zombie)\n",
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

unsigned int SolidOutput::SetOutputList( G4String f ){
    const char *fname = "SetOutputList";

    fOutputListName = f;
    
    // Read in active branch list
    FILE *file = fopen(fOutputListName.data(), "r");

    if( !file ){
	fprintf(stderr, "%s::%s Error opening file %s: ",
		GetClassName(), fname, fOutputListName.data());
	perror(NULL);
	exit(1);
    }

    fOutListDefined = true;

    size_t nchar = 255;
    char *buf = new char[nchar];

    while( getline(&buf, &nchar, file) > 0 ){
	TrimWhiteAndComments(buf);
	if( strlen(buf) ){
	    fActiveBranches.push_back(G4String(buf));
	}
    }

    return fActiveBranches.size();
}

bool SolidOutput::IsActiveBranch(G4String bname){
    if( !fOutListDefined ){
	return true;
    }

    unsigned int i = 0;
    // Test this branchname against everything
    // in our active branches list
    while( i < fActiveBranches.size() &&
	    !IsMatch(fActiveBranches[i],bname) 
	 ){
	i++;
    }

    if( i != fActiveBranches.size() ){
	// We found a match in fActiveBranches
	return true;
    }
    return false;
}

/*
 * SolidOutput::IsMatch
 * Test bstr against astr to see if it matches.  astr
 * can have wildcards * and ?
 */
bool SolidOutput::IsMatch(G4String gastr, G4String gbstr ){
    bool debug = false;

    int aidx, bidx;

    const char *astr = gastr.data();
    const char *bstr = gbstr.data();

    int alen = strlen(astr);
    int blen = strlen(bstr);

    aidx = 0;
    bidx = 0;

    if( debug )
    printf("Comparing %s to %s\n", bstr, astr );

    bool isglob = false;
    int  gaidx  = -1;
    int  gbidx  = -1;

    // Find the last non * char of astr

    int lastreal = alen-1;
    while( astr[lastreal] == '*' ){
	lastreal--;
    }
    lastreal++;

    while(aidx < alen && bidx < blen){
	if( debug )
	printf("a[%d] = %c   b[%d] = %c\n", aidx, astr[aidx], bidx, bstr[bidx]);
	switch(astr[aidx]){
	    case '*':
		aidx++;
		while(     astr[aidx] == '*' 
			&& astr[aidx] == '?'
		        && aidx < alen       ){
		    aidx++;
		}
		// Star at end matches everything
		if( aidx == alen ){ 
		    if( debug )
		    printf("Wild terminated astr, good to go\n");
		    return true; 
		}
		isglob = true;
		gaidx  = aidx - 1;

		if( debug )
		printf("scanning bstr for %c\n", astr[aidx]);
		while(astr[aidx] != bstr[bidx] && bidx < blen){
		    if( debug )
		    printf("b[%d] = %c... next\n", bidx, bstr[bidx]);
		    bidx++;
		}
		// If we got to the end without
		// finding the next char in astr 
		// we didn't match
		if(bidx==blen){ 
		    if( debug )
		    printf("Hit end of bstr without matching %c, bad match\n", astr[aidx] );
		    return false;
		}
		// If we have to come back to this glob,
		// we'll start checking b one char beyond
		gbidx  = bidx+1;
		break;
    	    case '?':
		// Automatic match
		aidx++;
		bidx++;
		break;
    	    default:
		if( astr[aidx] != bstr[bidx] ){
		    // Go back and treat this
		    // like a glob if we have one
		    if( isglob ){
			aidx = gaidx;
			bidx = gbidx;
			if( debug )
			printf("Backtracking to last glob\n");
			break;
		    }
		    if(debug)
		    printf("Failed match, not in glob\n");
		    return false;
		}
		printf("a %d->%d   b %d->%d\n", aidx, aidx+1, bidx, bidx+1);
		aidx++;
		bidx++;
		break;
	}
    }

    // We have to be at the end of bstr
    // otherwise we have run out of comparisons
    // to do with astr, which is not a match
    if(debug)
    printf("%d == %d?  %d >= %d?\n", bidx, blen, aidx, lastreal );
    if( bidx == blen && aidx >= lastreal){
	if(debug) printf("True!\n");  
	return true; 
    }
    if(debug)
    printf("Nope...\n");
    return false;
}

/*! SolidOutput::TrimWhiteAndComments
 * Trims out whitespace and newlines
 * Comments are defined by # marks, so
 * we terminate at the first sign of those
 */
void SolidOutput::TrimWhiteAndComments(char *str){
    int len = strlen(str);
    int idx;
    for( idx = 0; idx < len && str[idx] != '#'; idx++ ){}
    // Add null to new place
    str[idx] = 0;
    // Get new length
    len = strlen(str);

    char *tmp = new char[len];
    strcpy(tmp,str);

    int cpyidx = 0;
    
    // len+1 to catch the terminator at the end
    for( idx = 0; idx < len+1; idx++ ){
	// Only copy things that aren't
	// whitespace
	if(   tmp[idx] != ' ' 
	   && tmp[idx] != '\n'
	   && tmp[idx] != '\t' ){
	    str[cpyidx] = tmp[idx];
	    cpyidx++;
	}
    }

    delete tmp;
    return;
}
