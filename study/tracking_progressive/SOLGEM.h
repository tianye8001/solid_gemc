#ifndef ROOT_SOLGEM
#define ROOT_SOLGEM

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// TreeSearch::MWDC                                                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "THaTrackingDetector.h"
#include "TClonesArray.h"
#include "THaDetMap.h"
#include "TMatrixDSym.h"
#include "THaGemHit.h"
#include "THaGemTrack.h"
#include <vector>
#include <utility>
#include <set>
#include <list>
#include <cassert>

using std::vector;

class SOLGEM : public THaTrackingDetector {
  public:
    SOLGEM( const char* name, const char* description = "", 
	  THaApparatus* app = 0 );
    virtual ~SOLGEM();

    virtual void    Clear( Option_t* opt="" );
    virtual Int_t   Decode( const THaEvData& );
    virtual EStatus Init( const TDatime& date );
    virtual Int_t   CoarseTrack( TClonesArray& tracks ); 
    virtual Int_t   FineTrack( TClonesArray& tracks ); 
    void FindTrack(Int_t angleflag, Int_t type);

    //see if the next hit is in the range of r
    Int_t Range_in_theta(Double_t r1, Int_t layer1, Double_t r2, Int_t layer2,Double_t* theta_min,Double_t* theta_max,Int_t angleflag);
    // see if the next hit is in the range of phi with input of momentum
    /* Int_t Range_in_phi(Double_t phi1,Int_t layer1, Double_t phi2, Int_t layer2, Double_t mom_min,Double_t mom_max,Int_t angleflag); */
/*     // Get the momentum range from the current hit and previous momentum range */
    Int_t Find_mom_range(Int_t layer1, Double_t phi0, Int_t layer2, Double_t phi1, Double_t* mom_min,Double_t* mom_max,Int_t angleflag);
    Int_t DefineVariables(THaAnalysisObject::EMode mode = 
			  THaAnalysisObject::kDefine);
    Int_t Get_ntrack(){return fntrack;};
    Int_t Get_ngoodtrack(){return fngoodtrack;};

    /*     virtual Int_t   DefineVariables( EMode mode = kDefine ); */
/*     virtual void    Print(const Option_t* opt) const; */
    void calculate(Double_t,Double_t,Double_t,Double_t,Double_t,Double_t,Double_t*,Double_t*,Double_t*);
    void FitTrack(THaGemTrack*, Double_t*, Int_t, Double_t*);
    void Vertex_Reconstruction(Double_t*, Int_t, Double_t*, Double_t*);
    Double_t Polar_Angle_Reconstruction(Double_t*, Int_t);
    Int_t Check_Q_Asym(THaGemTrack*);
    Int_t Predict_r(Double_t, Int_t, Double_t, Int_t, Double_t, Double_t);

 protected:
    TClonesArray* hit[5];
    Int_t fnhit[5];
    TClonesArray* fTracks;
    Int_t fntrack;

    TClonesArray *goodhit[5]; 
    Int_t fngoodhit[5];
    TClonesArray* fGoodTracks; 
    Int_t fngoodtrack;

    //-----------add for EC---------//
    TClonesArray* EC_hit;
    Int_t nEChit;
    //------------------------------//

    /////////////////////
    /*TClonesArray* hit_plane1;
    TClonesArray* hit_plane2;
    TClonesArray* hit_plane3;
    TClonesArray* hit_plane4;
    TClonesArray* hit_plane5;
    TClonesArray* hit_plane6;*/
    ClassDef(SOLGEM,0) 
};

#endif
