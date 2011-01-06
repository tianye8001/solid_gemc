#ifndef SOLIDGENERICDET_HH
#define SOLIDGENERICDET_HH

#include "SolidGenericDetHit.hh"
#include "SolidData.hh"

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"

class SolidDatum;
class TObjString;

class SolidGenericDet : public G4VSensitiveDetector, public SolidData {
    public:
	SolidGenericDet(G4String name);
	~SolidGenericDet();

	void Initialize(G4HCofThisEvent*HCE);
	G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	void EndOfEvent(G4HCofThisEvent*HCE);
	void clear();

	const char *GetClassName(){ return "SolidGenericDet";}

	void SetGateStart(double g){ fGate_start = g; }
	void SetGateStop(double g){ fGate_stop  = g; }
	void SetFADCtRes(double r){ fFADC_tRes  = r; }
	void SetTDCThresh(double t){ fTDC_thresh  = t; }
	void SetTDCDeadtime(double dt){ fTDC_deadtime  = dt; }

    private:
	SolidGenericDetHitsCollection *fHits;

	SolidDatum
	    *foEdep, *foTime, *foTrX, *foTrY, *foTrZ,
	    *foTrE,  *foTrP,  *foTrPx, *foTrPy, *foTrPz,
	    *foFADCa, *foFADCt, *foTDC,  *foADC,
	    *foNhit, *foTrID, *foPname;

	SolidDatum
	    *fofTime, *fofTrX, *fofTrY, *fofTrZ,
	    *fofTrE,  *fofTrP,  *fofTrPx, *fofTrPy, *fofTrPz,
	    *fofNhit, *fofTrID, *fofPname;

	int    GetNFADC(){ return ((int)((fGate_stop-fGate_start)/fFADC_tRes));}
	int    GetFADCbin(double t);

	double fGate_start;
	double fGate_stop;
	double fFADC_tRes;
	double fTDC_thresh;
	double fTDC_deadtime;

	bool FirstHitsAreActive();
};

#endif//SOLIDGENERICDET_HH
