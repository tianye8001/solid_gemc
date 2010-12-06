#ifndef SolidData_hh
#define SolidData_hh

#include "TROOT.h"
#include "TString.h"

enum datatype_t {kInt, kDouble, kFloat, kIntArray, kDoubleArray, kFloatArray};

/** Data description struct */
struct datadesc_t {
    char branchname[255];///< Branchname to be put in tree
    datatype_t type;     ///< Data type to be stored
    void *ptr;           ///< Pointer to data
    UInt_t *size;        ///< Pointer to size of data (only relevant for Array)
};

/**
 * SolidData
 *
 * Generic class describing data to be written
 * to output in a ROOT tree
 *
 */
class SolidData {
    public:
	 SolidData(const char *n){ fName = n; fData = NULL; fNdata = 0; }
        ~SolidData();

	const char  *GetName() { return fName.Data();}
	int          GetNData(){ return fNdata; }
	datadesc_t **GetData() { return fData; }

	void SetName(const char *n){ fName = n; }
	int  SetData(datadesc_t *);

    private:
	TString      fName;
	int          fNdata;
	datadesc_t **fData;

	int  ClearData();
};
#endif//SolidData_hh

