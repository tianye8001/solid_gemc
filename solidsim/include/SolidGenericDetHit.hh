#ifndef SOLIDGENERICDETHIT_HH
#define SOLIDGENERICDETHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "SolidTrack.hh"

class SolidGenericDetHit : public G4VHit {
    public:
	SolidGenericDetHit();
	SolidGenericDetHit(const SolidGenericDetHit &);
	SolidGenericDetHit(SolidTrack, double, double);

	~SolidGenericDetHit();

	void SetTrack(SolidTrack tr){ fTr = tr; }
	SolidTrack GetTrack(){ return fTr; }
	void SetTime(double t){ fTime = t;}
	double GetTime(){ return fTime; }
	void SetEdep(double e){ fEdep = e;}
	double GetEdep(){ return fEdep; }

	const SolidGenericDetHit& operator=(const SolidGenericDetHit &);

	inline void *operator new(size_t);
	inline void operator delete(void *aHit);
	void *operator new(size_t,void*p){return p;}
#ifndef G4NOT_ISO_DELETES
	void operator delete(void *,void*){}
#endif


    private:
	SolidTrack fTr;
	double     fTime;
	double     fEdep;
};

typedef G4THitsCollection<SolidGenericDetHit> SolidGenericDetHitsCollection;

extern G4Allocator<SolidGenericDetHit> SolidGenericDetHitAllocator;

inline void* SolidGenericDetHit::operator new(size_t) {
    void *aHit;
    aHit = (void *) SolidGenericDetHitAllocator.MallocSingle();
    return aHit;
}

inline void SolidGenericDetHit::operator delete(void *aHit) {
    SolidGenericDetHitAllocator.FreeSingle((SolidGenericDetHit*) aHit);
}

#endif//SOLIDGENERICDETHIT_HH
