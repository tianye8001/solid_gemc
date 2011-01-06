#include "SolidFieldMap.hh"
#include "SolidFieldManager.hh"
#include "G4LogicalVolume.hh"

// Register with the field manager
SolidFieldMap::SolidFieldMap(G4String name, G4LogicalVolume *v ):
    fName(name), fLogVolume(v) 
{
    SolidFieldManager *fieldman = SolidFieldManager::GetInstance();
    fieldman->AddField(this);
}

SolidFieldMap::~SolidFieldMap(){
    //FIXME:  Unregister from fieldman?
}
