#include "SolidFieldManager.hh"
#include "SolidFieldMap.hh"

#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include <stdlib.h>

int SolidFieldManager::__SolidFieldManagerInit = 0;
SolidFieldManager *SolidFieldManager::__SolidFieldManagerPtr = NULL;


SolidFieldManager::SolidFieldManager(){
    fFieldMaps.clear();

    const char *fname = "SolidFieldManager()";
    if( __SolidFieldManagerInit ){
	fprintf(stderr, "%s::%s  Already instantiated\n",
		GetClassName(), fname);
	exit(1);
    } else {
	__SolidFieldManagerPtr = this;
	__SolidFieldManagerInit = 1;
    }


    return;
}

SolidFieldManager::~SolidFieldManager(){
    __SolidFieldManagerInit = 0;
}

SolidFieldManager *SolidFieldManager::GetInstance(){
    if( __SolidFieldManagerInit ){
	return __SolidFieldManagerPtr;
    } else {
	return NULL;
    }
}


/*! 
  Take fields to be included to this
  simulation which were added to fFieldMaps
  and add them

  Return number of fields added
  return -1 on fail
  */
int SolidFieldManager::ProcessFieldMaps(){

    const char *thisfunc = "ProcessFieldMaps";
    int i, ret;
    int nfield = fFieldMaps.size();

    SolidFieldMap *field = NULL;

    G4FieldManager *gfmgr =
	G4TransportationManager::GetTransportationManager()
	->GetFieldManager();

    G4LogicalVolume *lvol;
    G4FieldManager *lfmgr;

    for( i = 0; i < nfield; i++ ){
	field = fFieldMaps[i];
	if( !field ){
	    //Field map is NULL

	    fprintf(stderr, "%s::%s  Field map at %d is null\n",
		    GetClassName(), thisfunc, i );
	    return -1;
	}

	// Add field.  If logical volume is NULL
	// we set it to the full world

	lvol = field->GetLogicalVolume();
	if( lvol ){
	    lfmgr = new G4FieldManager(field);
	    lvol->SetFieldManager(lfmgr, true);
	} else {
	    gfmgr->SetDetectorField(field);
	    gfmgr->CreateChordFinder(field);
	}

	ret = field->AddField();
	if( ret == 1 ){
	    // Adding field failed for some reason
	    fprintf(stderr, "%s::%s  Field map at %d (%s) failed\n",
		    GetClassName(), thisfunc, i, field->GetName());
	    return -1;
	}
    }

    return nfield;
}

