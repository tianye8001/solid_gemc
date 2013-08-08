#ifndef CaloSimDetectorConstruction_H
#define CaloSimDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class CaloSimSD;

#include "G4String.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4VisAttributes.hh"
#include "Config.h"

class CaloSimDetectorConstruction: public G4VUserDetectorConstruction
{
public:

	CaloSimDetectorConstruction(G4String);
	~CaloSimDetectorConstruction();

	G4VPhysicalVolume* Construct();
//	G4VPhysicalVolume* ConstructShowerOnly();
//	G4VPhysicalVolume* ConstructTotoalShower();
	G4VPhysicalVolume* ConstructShowerShashlik();
	G4VPhysicalVolume* ConstructShowerShashlikLayout(G4String layout_file);
	G4VPhysicalVolume* ConstructShowerShashlikHexagon();

//	G4VPhysicalVolume*
//	ConstructShower(G4VPhysicalVolume* experimentalHall_phys, CaloSimSD* aSD);
//	G4VPhysicalVolume
//	        *
//	        ConstructPreShower(G4VPhysicalVolume* experimentalHall_phys,
//	                CaloSimSD* aSD);

private:

	void buildMaterials();

	// Logical volumes
	//
	G4LogicalVolume* experimentalHall_log;
	G4LogicalVolume* tracker_log;
	G4LogicalVolume* calorimeterBlock_log;
	G4LogicalVolume* calorimeterLayer_log;

	// Physical volumes
	//
	G4VPhysicalVolume* experimentalHall_phys;
	G4VPhysicalVolume* calorimeterLayer_phys;
	G4VPhysicalVolume* calorimeterBlock_phys;
	G4VPhysicalVolume* tracker_phys;

	G4String outputFileName;

	//
	// MATERIALS
	//

	//
	// Elements, defined by Z and atomic mass
	//

	G4Element *elH; // Hydrogen,  atomic no. 1
	G4Element *elC; // Carbon,    atomic no. 6
	G4Element *elN; // Nitrogen,  atomic no. 7
	G4Element *elO; // Oxygen,    atomic no. 8
	G4Element *elF; // Flourine,  atomic no. 9
	G4Element *elSi; // Silicon,   atomic no. 14
	G4Element *elS; // Sulfur,    atomic no. 16
	G4Element *elCl; // Chlorine,  atomic no. 17
	G4Element *elCr; // Chromium,  atomic no. 24
	G4Element *elMn; // Manganese, atomic no. 25
	G4Element *elFe; // Iron,      atomic no. 26
	G4Element *elCo; // Cobalt,    atomic no. 27
	G4Element *elNi; // Nickel,    atomic no. 28
	G4Element *elSn; // Tin,       atomic no. 50
	G4Element *elW; // Tungsten,  atomic no. 74
	G4Element *elPb; //
	G4Element *elAu; // Gold,      atomic no. 79
	G4Element *elCu; // Copper,      atomic no. 29


	//
	// Materials, defined by density, number of
	//            constituent elements, mass ratio, etc.
	// Bulk Solids
	G4Material *Aluminum;
	G4Material *BC404;
	G4Material *BC408;
	G4Material *Iron;
	G4Material *Lead;
	G4Material *LeadH;
	G4Material *Mylar;
	G4Material *SSteel;
	G4Material *Sulfur;
	G4Material *Tin;
	G4Material *Tungsten;
	G4Material *Copper;

	// Gases
	G4Material *Air;
	G4Material *Ar;
	G4Material *Vacuum;

	// Visualization Attributes
	G4VisAttributes *whiteSolid;
	G4VisAttributes *blackSolid;
	G4VisAttributes *redSolid;
	G4VisAttributes *greenSolid;
	G4VisAttributes *blueSolid;
	G4VisAttributes *magentaSolid;
	G4VisAttributes *cyanSolid;
	G4VisAttributes *yellowSolid;
	G4VisAttributes *whiteFrame;
	G4VisAttributes *redFrame;
	G4VisAttributes *greenFrame;
	G4VisAttributes *blueFrame;
	G4VisAttributes *magentaFrame;
	G4VisAttributes *cyanFrame;
	G4VisAttributes *yellowFrame;
	G4VisAttributes *offAtt;
	G4VisAttributes *TargetVisAtt;

	G4Material* PbGl;
	G4Element* O;
	G4Element* Si;
	G4Element* Pb;
	G4Material* SiO2;
};

#endif

