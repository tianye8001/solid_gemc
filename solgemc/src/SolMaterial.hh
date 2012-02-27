#ifndef __SOLMATERAL_HH
#define __SOLMATERAL_HH

#include <map>

void AddSolGEMCMaterial( map<string, G4Material *> &mmap ){
    G4double density, z, a;
    G4int    nel;

    G4Element* C  = new G4Element("Carbon",    "C",  z=6,  a=   12.01*g/mole);
    G4Element* F  = new G4Element("Fluorine",  "F",  z=9,  a= 18.9984*g/mole);

    G4Material *C4F10 = new G4Material("C4F10", density=0.00973*g/cm3, nel=2);
    C4F10->AddElement(C ,   4);
    C4F10->AddElement(F ,  10);

    mmap["C4F10"]       = C4F10;

    return;
}

#endif//__SOLMATERAL_HH
