#ifndef SolidDetectorConstruction_H
#define SolidDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"

#include <vector>


class G4VPhysicalVolume;
class G4LogicalVolume;
class SolidDetectorMessenger;

class SolidFieldManager;

/*!
  SolidDetectorConstruction

  User defined detector construction class

  Utilizes:
	SolidGeoParser
	SolidFieldManager

  to handle solid, material, detector, and magnetic field
  descriptions.  Nothing about the experiments should be
  hard coded.
  
*/

class SolidDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
	SolidDetectorConstruction();
	~SolidDetectorConstruction();

	G4VPhysicalVolume* Construct();  
	const char *GetClassName(){ return "SolidDetectorConstruction";}

    private:
	SolidDetectorMessenger *fDetectorMessenger;

	SolidFieldManager *fFieldMan;
};
#endif
