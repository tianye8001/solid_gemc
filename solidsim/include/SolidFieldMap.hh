#ifndef SolidFieldMap_hh
#define SolidFieldMap_hh

#include "TString.h"

/*!
   SolidFieldMap

   Class for installing generic field maps into
   the simulation.  Subclasses of this are for
   specific field implementations

   This is a purely virtual class and can't be
   instantiated on it's own
*/

class SolidFieldMap{
    public:
	SolidFieldMap(const char *){};
	~SolidFieldMap() {};

	virtual int AddField(){return 0;}

	virtual const char *GetName(){ return fName.Data(); }
    private:
	TString fName;
};

#endif//SolidFieldMap_hh
