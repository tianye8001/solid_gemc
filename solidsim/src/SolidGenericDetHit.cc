#include "SolidGenericDetHit.hh"

G4Allocator<SolidGenericDetHit> SolidGenericDetHitAllocator;

SolidGenericDetHit::SolidGenericDetHit(){
}

SolidGenericDetHit::SolidGenericDetHit(SolidTrack tr, double t, double edep):
    fTr(tr), fTime(t), fEdep(edep) {
}

SolidGenericDetHit::~SolidGenericDetHit(){
}

SolidGenericDetHit::SolidGenericDetHit(const SolidGenericDetHit &right)
    :G4VHit(){
	fTr   = right.fTr;
	fTime = right.fTime;
	fEdep = right.fEdep;
	return;
}

const SolidGenericDetHit& 
    SolidGenericDetHit::operator=(const SolidGenericDetHit &right)
{
	fTr   = right.fTr;
	fTime = right.fTime;
	fEdep = right.fEdep;
	return *this;
}
