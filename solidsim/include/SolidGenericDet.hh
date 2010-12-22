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

    private:
	SolidGenericDetHitsCollection *fHits;

	SolidDatum
	    *foEdep, *foTime, *foTrX, *foTrY, *foTrZ,
	    *foTrE,  *foTrP,  *foTrPx, *foTrPy, *foTrPz,
	    *foFADCa, *foFADCt, *foTDC,  *foADC,
	    *foNhit, *foTrID, *foPname;

	double fGate_start;
	double fGate_stop;
	double fFADC_size;
	double fTDC_thresh;
	double fTDC_deadtime;
};

#endif//SOLIDGENERICDET_HH
