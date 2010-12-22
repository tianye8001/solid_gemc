#include "SolidSDMan.hh"

int SolidSDMan::__SolidSDManInit = 0;
SolidSDMan *SolidSDMan::__SolidSDManPtr = NULL;

SolidSDMan::SolidSDMan(){
    const char *fname = "SolidSDMan()";
    if( __SolidSDManInit ){
	fprintf(stderr, "%s::%s  Already instantiated\n",
		GetClassName(), fname);
	exit(1);
    } else {
	__SolidSDManPtr = this;
	__SolidSDManInit = 1;
    }
}

SolidSDMan::~SolidSDMan(){
    __SolidSDManInit = 0;
    Clear();
}

SolidSDMan *SolidSDMan::GetInstance(){
    if( __SolidSDManInit ){
	return __SolidSDManPtr;
    } else {
	return NULL;
    }
}

void SolidSDMan::Clear(){
    /* empty vector without calling
       destructors*/
    while(fDet.size()){
	fDet.pop_back();
    }
    return;
}
