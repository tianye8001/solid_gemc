#ifndef ROOT_THaSolenoid
#define ROOT_THaSolenoid

#include "THaSpectrometer.h"
#include "THaSoleSimRun.h"
#include "THaEvData.h"
#include "THaDetector.h"
#include "VarDef.h"
#include "TVector3.h"
#include "TRotation.h"
#include "TMatrixD.h"

class THaSolenoid : public THaSpectrometer {
  public:
	//////////////////////////////////////////////////////////////////
	// Constructor desctructor
	//////////////////////////////////////////////////////////////////
    virtual ~THaSolenoid();
    THaSolenoid( const char* name, const char* description );//constructor
    
    void SetSimEvent(const Int_t* rhs) {sim_event = (THaSoleSimEvent*)rhs;};
    THaSoleSimEvent* GetSimEvent(){return sim_event;};
    
    virtual Int_t   FindVertices( TClonesArray& tracks );
    virtual Int_t   TrackCalc();
    
 protected:
    THaSoleSimEvent *sim_event;
    ClassDef(THaSolenoid,0) //ABC for Hall A BigBite
      };

#endif
