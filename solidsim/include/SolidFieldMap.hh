#ifndef SolidFieldMap_hh
#define SolidFieldMap_hh

#include "G4String.hh"
#include "G4MagneticField.hh"
#include "G4LogicalVolume.hh"

/*!
   SolidFieldMap

   Class for installing generic field maps into
   the simulation.  Subclasses of this are for
   specific field implementations

   This is a purely virtual class and can't be
   instantiated on it's own
*/


class SolidFieldMap : public G4MagneticField {
    public:
	SolidFieldMap(G4String, G4LogicalVolume *v = NULL);
	~SolidFieldMap();

	virtual int AddField(){return 0;}

	virtual const char *GetName(){ return fName.data(); }

	G4LogicalVolume *GetLogicalVolume(){ return fLogVolume; }
    private:
	G4String fName;
	G4LogicalVolume *fLogVolume;
};

#endif//SolidFieldMap_hh
