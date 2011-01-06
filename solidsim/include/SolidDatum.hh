#ifndef SOLIDDATUM_HH
#define SOLIDDATUM_HH

#include <G4String.hh>
#include <vector>
#include <string>
#include "types.hh"

class SolidData;
class SolidOutput;
class TBranch;

class SolidDatum {
    public:
	SolidDatum(SolidData *d, vartype_t type, G4String name, int len = 1);

	~SolidDatum();

	void Init();
	int Resize(unsigned int);

	int Fill(unsigned int, void* );

	int Fill(std::vector<double> );
	int Fill(std::vector<int> );
	int Fill(std::vector<std::string> );

	int Fill(int, int l = -1);
	int Fill(double, int l = -1);
	int Fill(std::string);

	void ClearStr(){fStrData.clear(); fLen = 0;}
	int Push(std::string s){fStrData.push_back(s); fLen++; return fLen;}

	void SetOutput(SolidOutput *);
	void UnsetBranch();

	void SetupBranch();
	void SetBranchAddress();

	const char *GetClassName(){return "SolidDatum";}

	bool IsActive(){ return fIsActive; }

    private:
	void *fData;
	std::vector<std::string> fStrData;

	G4String fName;
	G4String fROOTtype;
	unsigned int fLen;
	unsigned int fAllocLen;

	bool fIsActive;

	SolidOutput *fOutput;
	vartype_t fType;

	TBranch *fNbranch, *fDbranch;
};

#endif//SOLIDDATUM_HH
