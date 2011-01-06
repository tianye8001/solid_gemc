#include "SolidSimpleField.hh"
#include "G4String.hh"
#include "G4LogicalVolume.hh"

SolidSimpleField::SolidSimpleField(G4String name, G4LogicalVolume *v):
    SolidFieldMap(name,v)
{
    return;
}

SolidSimpleField::~SolidSimpleField(){
}

void SolidSimpleField::GetFieldValue(const G4double [4], G4double *Bfield ) const {
    double tesla = 1e4*gauss;

    Bfield[0] = 0.01*tesla;
    Bfield[1] = 0.01*tesla;
    Bfield[2] = 0.01*tesla;

    return;
}
