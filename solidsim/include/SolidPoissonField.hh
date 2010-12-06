#ifndef SolidPoissonField_hh
#define SolidPoissonField_hh

#include "SolidFieldMap.hh"
#include "TString.h"

/*!
   SolidPoissonField

   Class to read Poisson/Superfish field maps and
   put into our geometry.  The map to be used
   is set by SetFileName(const char*) or passed
   as argument.

   This class is handled by SolidFieldManager

   Seamus Riordan
   Dec 3, 2010
*/

class SolidPoissonField: public SolidFieldMap{
/// FIXME:  I don't know if this needs to have access to 
///   the detector construction class or needs to derive from it
    public:
	 SolidPoissonField(const char *name, const char *file=NULL);
	~SolidPoissonField() {};
	const char *GetClassName(){ return "SolidPoissonField";}

	int AddField();

	void SetFileName(const char *n){ fFileName = n; }

    private:
	TString fFileName;
};

#endif//SolidPoissonField_hh
