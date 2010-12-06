#ifndef SolidOutput_hh
#define SolidOutput_hh

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

class SolidOutput{
    public:
	SolidOutput();
	~SolidOutput();
	void CreateOutputFile();
    private:
};

#endif//SolidOutput_hh
