#ifndef SolidData_hh
#define SolidData_hh

#include "G4String.hh"
#include <vector>

class SolidDatum;
class SolidOutput;

/*!
 * SolidData
 *
 * Generic class describing data to be written
 * to output in a ROOT tree
 *
 */
class SolidData {
    public:
	SolidData(const G4String &n);
        virtual ~SolidData(){ClearData();}

	const char   *GetDataName() { return fName.data();}
	const char   *GetBranchName() { return fBranchName.data();}
	unsigned int  GetNdata(){ return fData.size(); }

	std::vector<SolidDatum *>GetData() { return fData; }
	SolidDatum* GetDatum(unsigned int i) { return fData[i]; }

	void SetName(const G4String &n){ fName = n; }
	unsigned int AddDatum(SolidDatum *d){fData.push_back(d); 
	                                     return fData.size(); }

	const char *GetClassName(){ return "SolidData";}

	int  ResetData();
	int  ClearData();
	int  RegisterData();

    private:
	G4String  fName;
	G4String  fBranchName;
	std::vector<SolidDatum *> fData;

	SolidOutput *fOutput;
};
#endif//SolidData_hh

