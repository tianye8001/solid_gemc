#include "THaSolenoid.h"
#include "SOLGEM.h"

ClassImp(THaSolenoid)

THaSolenoid::THaSolenoid( const char* name, const char* description ) 
:   THaSpectrometer( name, description )
{
  AddDetector(new SOLGEM("gem","GEM detectors"));
} 

THaSolenoid::~THaSolenoid()
{
  
}
 
  Int_t THaSolenoid::FindVertices( TClonesArray& /* tracks */ )
{
  // Reconstruct target coordinates for all tracks found.

  // TODO

  return 0;
}

//_____________________________________________________________________________
Int_t THaSolenoid::TrackCalc()
{
  // Additioal track calculations

  // TODO

  return 0;
}
