#include "SolidTrack.hh"

SolidTrack::SolidTrack(){
    fPos = G4ThreeVector();
    fP   = G4ThreeVector();
    fE   = -1.0;
    fID  = -1;
    fPartType = "NULL";
}

SolidTrack::SolidTrack(G4ThreeVector pos,
	double partE, G4ThreeVector p,
	int ID, G4String type) :
    fPos(pos), fP(p), fE(partE), fID(ID), fPartType(type)
{
    return;
}

SolidTrack::SolidTrack(double xpos, double ypos, double zpos, 
	double partE, double px, double py, double pz, 
	int ID, G4String type) :
    fE(partE), fID(ID), fPartType(type)
{
    fPos = G4ThreeVector(xpos, ypos, zpos);
    fP   = G4ThreeVector(px, py, pz);
    return;
}

SolidTrack::~SolidTrack(){
}

SolidTrack::SolidTrack(const SolidTrack &right){
    fPos = right.fPos;
    fP   = right.fP;
    fE   = right.fE;
    fID  = right.fID;
    fPartType = right.fPartType;
}


const SolidTrack& SolidTrack::operator=(const SolidTrack &right){
    fPos = right.fPos;
    fP   = right.fP;
    fE   = right.fE;
    fID  = right.fID;
    fPartType = right.fPartType;
    return *this;
}

void SolidTrack::Print(){
    printf("%s \t ID: %8d\n", fPartType.data(), fID);
    printf("pos = (%6.3f, %6.3f, %6.3f) m\n", fPos.X/m, fPos.Y/m, fPos.Z/m);
    printf("p   = (%6.3f, %6.3f, %6.3f) m\n", fP.X/m, fP.Y/m, fP.Z/m);
    printf("E   = %6.1f MeV\n", fE/MeV);
    return;
}
