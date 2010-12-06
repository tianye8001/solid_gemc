#include "SolidFieldManager.hh"
#include "SolidFieldMap.hh"

SolidFieldManager::SolidFieldManager(){
    fFieldMaps.clear();
   
    return;
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

    for( i = 0; i < nfield; i++ ){
	field = fFieldMaps[i];
	if( !field ){
	    //Field map is NULL

	    fprintf(stderr, "%s::%s  Field map at %d is null\n",
		    GetClassName(), thisfunc, i );
	    return -1;
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

