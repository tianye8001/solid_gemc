#ifndef SolidOutput_hh
#define SolidOutput_hh

#include <vector>
#include <G4String.hh>

/**
 SolidOutput

 This class handles all output into ROOT files
 from the simulation

 It must:
 	Handle generation of ROOT trees and event-by-event filling
	Is responsible for setting up appropriate branches for output
	Handle output and storage of input files
	Handle whatever version storage we have

*/

class SolidData;
class TTree;
class TFile;

class SolidOutput{
    public:
	SolidOutput();
	~SolidOutput();
	int CreateOutputFile();
	int CloseOutputFile();

	static SolidOutput *GetInstance();

	int FillTree();

	const char *GetClassName(){ return "SolidOutput";}

	TTree *GetTree(){ return fTree; }
    private:
	static int __SolidOutputInit;
	static SolidOutput *__SolidOutputPtr;

	G4String fOutputFileName;

	TFile *fFile;
	TTree *fTree;
};

#endif//SolidOutput_hh
