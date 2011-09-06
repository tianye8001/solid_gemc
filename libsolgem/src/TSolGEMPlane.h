#ifndef __TSOLGEMPLANE_H
#define __TSOLGEMPLANE_H

#include "THaSubDetector.h"

#include "types.h"

class TSolGEMCluster;
class TClonesArray;

class TSolGEMPlane : public THaSubDetector {
    public:
	TSolGEMPlane(const char *name, const char *desc);
	virtual ~TSolGEMPlane() {;}

	TClonesArray *GetClusters() { return fClusters; }

	Int_t Decode( const THaEvData &);
	GEMDir_t GetDirection(){ return fDir; }
	TSolGEMPlane *GetPairedPlane() { return fPairPlane; }

	Int_t    GetNStrips()  const { return fNStrips; }
	Double_t GetPPitch()   const { return fSPitch/fPixelFactor;} // Pixel pitch
	Int_t    GetNPixels()  const { return fNStrips * fPixelFactor; }

	// Following assumes parallel strips, later we may
	// need to generalize this

	Double_t GetSBeg()     const { return fSBeg; }
	Double_t GetSPitch()   const { return fSPitch; }
	Double_t GetSAngle()   const; // Angle (rad) between horizontal axis
                                      // and normal to strips in dir of
	                              // increasing strip position
	Double_t GetSAngleComp() const { return 3.14159/2 - GetSAngle(); }
	Double_t GetPixelLocation (UInt_t i) const { return GetSBeg() + i * GetPPitch();} // Lower left corner of pixel i

    private:
	TClonesArray  *fClusters; // Clusters
	GEMDir_t fDir;		 // Plane orientation
	TSolGEMPlane *fPairPlane; // Paired plane

	Int_t fNStrips;     // Number of strips
	Double_t fSBeg;     // Position of 1st strip (low edge) (m)
                            // i.e. distance to detector origin normal to strip
	Double_t fSPitch;   // Strip pitch (m)
	Int_t fPixelFactor;  // Pixels per strip

    public:
	ClassDef(TSolGEMPlane,1)

};

#endif//__TSOLGEMPLANE_H