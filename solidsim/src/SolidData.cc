#include "SolidData.hh"

/**
 * Sets the data to be put into output tree
 * Accepts NULL terminated array as input
 * Handles it's own memory management, so
 * transient structures passed are OK
 *
 * Returns number of data allocated (fNdata)
 * Returns -1 on fail
 */
int SolidData::SetData(datadesc_t darray[]){
    int n = 0;
    ClearData();

    datadesc_t *data = darray;

    while( data ){
	fData[n] = (datadesc_t *) malloc(sizeof(datadesc_t));
	strcpy(fData[n]->branchname, data->branchname);
	fData[n]->type = data->type;
	fData[n]->ptr  = data->ptr;
	fData[n]->size = data->size;
	n++; data++;
    }
    fNdata = n;
    return n;
}

/**
 * Clears data that is set
 * Returns number of data destroyed (fNdata)
 */
int SolidData::ClearData(){
    int i;
    int n = fNdata;

    for( i = 0; i < fNdata; i++ ){
	free(fData[i]);
    }

    fNdata = 0;
    return n;
}
