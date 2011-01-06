#ifndef __SOLIDSIMPLEFIELD_HH
#define __SOLIDSIMPLEFIELD_HH

#include "SolidFieldMap.hh"
#include "G4String.hh"

class G4LogicalVolume;

/*!  SolidSimpleField
 *
 *  This is just a test on how to put a field into 
 *  the world
 */

class SolidSimpleField : public SolidFieldMap {
    public:
	SolidSimpleField( G4String name, G4LogicalVolume *l );
	~SolidSimpleField();

	void GetFieldValue(const G4double Point[4], G4double *Bfield ) const;
    private:
};

#endif//__SOLIDSIMPLEFIELD_HH
