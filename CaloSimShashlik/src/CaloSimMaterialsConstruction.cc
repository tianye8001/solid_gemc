#include "CaloSimDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Element.hh"

// This function is a private member of class CaloSimDetectorConstruction
void CaloSimDetectorConstruction::buildMaterials()
{
	G4double a, z, density;
	G4String name, symbol;
	G4double temperature, pressure;
	//
	// Elements
	G4double aH = 1.00794 * g / mole;
	elH = new G4Element("Hydrogen", symbol = "H", 1, aH);
	G4double aC = 12.0107 * g / mole;
	elC = new G4Element("Carbon", symbol = "C", 6, aC);
	G4double aN = 14.01 * g / mole;
	elN = new G4Element("Nitrogen", symbol = "N", 7, aN);
	G4double aO = 16.00 * g / mole;
	elO = new G4Element("Oxygen", symbol = "O", 8, aO);
	G4double aF = 18.9984032 * g / mole;
	elF = new G4Element("Flourine", symbol = "F", 9, aF);
	G4double aSi = 28.0855 * g / mole;
	elSi = new G4Element("Silicon", symbol = "Si", 14, aSi);
	G4double aS = 32.066 * g / mole;
	elS = new G4Element("Sulfur", symbol = "S", 16, aS);
	G4double aCl = 35.4527 * g / mole;
	elCl = new G4Element("Chlorine", symbol = "Cl", 17, aCl);
	G4double aCr = 51.9961 * g / mole;
	elCr = new G4Element("Chromium", symbol = "Cr", 24, aCr);
	G4double aMn = 54.938049 * g / mole;
	elMn = new G4Element("Manganese", symbol = "Mn", 25, aMn);
	G4double aFe = 55.845 * g / mole;
	elFe = new G4Element("Iron", symbol = "Fe", 26, aFe);
	G4double aCo = 58.933 * g / mole;
	elCo = new G4Element("Cobalt", symbol = "Co", 27, aCo);
	G4double aNi = 58.6934 * g / mole;
	elNi = new G4Element("Nickel", symbol = "Ni", 28, aNi);
	G4double aW = 183.84 * g / mole;
	elW = new G4Element("Tungsten", symbol = "W", 74, aW);
	G4double aPb = 207.19 * g / mole;
	elPb = new G4Element("Lead", symbol = "Pb", 82, aPb);
	G4double aSn = 118.710 * g / mole;
	elSn = new G4Element("Tin", symbol = "Sn", 50, aSn);
	G4double aCu = 63.546 * g / mole;
	elCu = new G4Element("Copper", symbol = "Cu", 29, aCu);

	//
	// Bulk Solids
	//

	//Aluminum
	z = 13.0;
	a = 26.98 * g / mole;
	density = 2.7 * g / cm3;
	Aluminum = new G4Material("Aluminum", z, a, density);

	//BC404 Scintillator
	density = 1.032 * g / cm3;
	BC404 = new G4Material("BC404", density, 2);
	G4double HCRatioBC404 = 1.100;
	G4double HWeightBC404 = HCRatioBC404 * aH / (HCRatioBC404 * aH + aC);
	BC404->AddElement(elH, HWeightBC404);
	BC404->AddElement(elC, 1 - HWeightBC404);

	//BC408 Scintillator
	density = 1.032 * g / cm3;
	BC408 = new G4Material("BC408", density, 2);
	G4double HCRatioBC408 = 1.104;
	G4double HWeightBC408 = HCRatioBC408 * aH / (HCRatioBC408 * aH + aC);
	BC408->AddElement(elH, HWeightBC408);
	BC408->AddElement(elC, 1 - HWeightBC408);

	//Iron
	z = 26.0;
	a = 55.845 * g / mole;
	density = 7.874 * g / cm3;
	Iron = new G4Material("Iron", z, a, density);

	//Lead
	z = 82.0;
	a = 207.19 * g / mole;
	density = 11.35 * g / cm3;
	Lead = new G4Material("Lead", z, a, density);

	//Copper
	z = 82.0;
	a = 207.19 * g / mole;
	density = 11.35 * g / cm3;
	Lead = new G4Material("Lead", z, a, density);

	//Test material with Pb and H mix
	LeadH = new G4Material("LeadH", density, 2);
	LeadH->AddElement(elH, .1);
	LeadH->AddElement(elPb, 1 - .1);


	//Mylar
	density = 1.39 * g / cm3;
	Mylar = new G4Material("Mylar", density, 3);
	Mylar->AddElement(elC, 5);
	Mylar->AddElement(elH, 4);
	Mylar->AddElement(elO, 2);

	//Stainless Steel
	density = 7.9 * g / cm3;
	SSteel = new G4Material("SSteel", density, 5, kStateSolid);
	SSteel->AddElement(elCr, .19);
	SSteel->AddElement(elFe, .6875);
	SSteel->AddElement(elMn, .02);
	SSteel->AddElement(elNi, .0925);
	SSteel->AddElement(elSi, .01);

	//Sulfur
	z = 16.0;
	a = 32.006 * g / mole;
	//   density = 2.06860*g/cm3;
	density = 1.58 * g / cm3; //this is target made and spec'd by Bernhard
	Sulfur = new G4Material("Sulfur", z, a, density);

	//Tin
	z = 50.0;
	a = 118.710 * g / mole;
	density = 7.310 * g / cm3;
	Tin = new G4Material("Tin", z, a, density);

	//Tungsten
	z = 74.0;
	a = 183.84 * g / mole;
	density = 19.250 * g / cm3;
	Tungsten = new G4Material("Tungsten", z, a, density);

	//Tungsten
	z = 29.0;
	a = 63.546 * g / mole;
	density = 	8.96 * g / cm3;
	Copper = new G4Material("Copper", z, a, density);

	//
	// Gases
	//

	//Air
	density = 1.2931 * mg / cm3;
	Air = new G4Material("Air", density, 2);
	Air->AddElement(elN, .7);
	Air->AddElement(elO, .3);

	Ar = new G4Material("ArgonGas", z = 18., a = 39.95 * g / mole, density
	        = 1.782 * mg / cm3);

	//Vacuum (Galactic)
	density = 1.e-25 * g / cm3;
	pressure = 1.e-25 * atmosphere;
	temperature = pressure / (density * k_Boltzmann);

	//Vacuum (beam)
	//   density     = 1.e-7*mg/cm3;
	//   pressure    = 2.e-2*atmosphere;
	//   temperature = pressure/(density*k_Boltzmann);
	Vacuum = new G4Material("Vacuum", density, 1, kStateGas, temperature,
	        pressure);
	Vacuum->AddMaterial(Air, 1.);

	//  G4double a, z, density;      //z=mean number of protons;
	//
	G4int ncomponents, natoms;
	G4double fractionmass;

	O = new G4Element("Oxygen", symbol = "O", z = 8., a = 16.00 * g / mole);
	Si = new G4Element("Silicon", symbol = "Si", z = 14., a = 28.09 * g / mole);
	Pb = new G4Element("Lead", symbol = "Pb", z = 82., a = 207.19 * g / mole);

	SiO2 = new G4Material("quartz", density = 2.200 * g / cm3, ncomponents = 2);
	SiO2->AddElement(Si, natoms = 1);
	SiO2->AddElement(O, natoms = 2);

	// lead glass
	PbGl = new G4Material("Lead Glass", density = 3.85 * g / cm3, ncomponents
	        = 2);
	PbGl->AddElement(Pb, fractionmass = 0.5316);
	PbGl->AddMaterial(SiO2, fractionmass = 0.4684);

}
