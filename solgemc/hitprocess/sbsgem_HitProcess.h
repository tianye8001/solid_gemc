#ifndef sbsgem_HITPROCESS_H
#define sbsgem_HITPROCESS_H 1

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "MPHBaseClass.h"

class SolPrimaryGeneratorAction;

// %%%%%%%%%%%%%%%%
// Class definition
// %%%%%%%%%%%%%%%%
class sbsgem_HitProcess : public MPHBaseClass {
    public:
	 sbsgem_HitProcess();
	~sbsgem_HitProcess(){}
	PH_output ProcessHit(MHit*, gemc_opts);                                            ///< Method to process the hit
	vector<identifier> ProcessID(vector<identifier>, G4Step*, detector, gemc_opts) ;   ///< Method to calculate new identifier
	static MPHBaseClass *createHitClass() {return new sbsgem_HitProcess;}

	SolPrimaryGeneratorAction *fPMG;
	SolPrimaryGeneratorAction *GetPMG();
};

#endif
