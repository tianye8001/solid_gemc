// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: CaloSimDetectorHit.hh,v 1.7 2004/03/25 16:47:29 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#ifndef CaloSimDetectorHit_h
#define CaloSimDetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4Step.hh"

#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CaloSimDetectorHit : public G4VHit
{
public:

  CaloSimDetectorHit();
  ~CaloSimDetectorHit();
  CaloSimDetectorHit(const CaloSimDetectorHit&);
  const CaloSimDetectorHit& operator=(const CaloSimDetectorHit&);
  int operator==(const CaloSimDetectorHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void Draw();
  void Print();
  void PrintToFile(std::ofstream *ptrToFile);

private:
  G4int         TrackNumber;
  G4int         BlockHit;
  G4int         LayerHit;
  G4int         FiberHit;
  G4int         SHorizHit;
  G4int         SVertHit;
  G4int         ParticleType;
  G4double      Edep;
  G4double      Edep_Ionizing;
  G4ThreeVector ParticleMomentum;
  G4double      ParticleEnergy;
  G4double      LocalTime;
  G4double      GlobalTime;
  G4ThreeVector HitPosition;
  G4ThreeVector VertexPosition;
  G4double      VertexTime;
  G4ThreeVector VertexMomentum;
  G4double      VertexEnergy;
  G4int         DecayVolID;
  G4String      DecayVolumeName;
  G4String      HitVolumeName;
  G4String      CreatorProcessName;
  G4String      StepProcessName;

public:
  inline void SetTrackNumber (G4int track)  { TrackNumber = track; };
  inline void SetBlock(G4int block)   { BlockHit = block; };  
  inline void SetLayer(G4int layer)   { LayerHit = layer; };  
  inline void SetFiber(G4int fiber)   { FiberHit = fiber; }; 
  inline void SetSVert(G4int sv) { SVertHit = sv; };
  inline void SetSHoriz(G4int sh) { SHorizHit = sh; };
  inline void SetParticleType(G4int id) {ParticleType = id;};
  inline void SetEdep        (G4double ed)  { Edep = ed; };
  inline void SetEdepIonizing        (G4double ed)  { Edep_Ionizing = ed; };
  inline void SetParticleMom(G4ThreeVector pxpypz) {ParticleMomentum = pxpypz;};
  inline void SetParticleEnergy (G4double pE)   { ParticleEnergy = pE; };
  inline void SetLocalTime     (G4double time) { LocalTime = time; };
  inline void SetGlobalTime    (G4double time) { GlobalTime = time; };
  inline void SetHitPosition (G4ThreeVector xyz){ HitPosition = xyz; };
  inline void SetVertexPos(G4ThreeVector xyz){VertexPosition = xyz;};
  inline void SetVertexTime(G4double t){VertexTime = t;}
  inline void SetVertexMom(G4ThreeVector pxpypz) {VertexMomentum = pxpypz;};
  inline void SetVertexEnergy (G4double pE)   { VertexEnergy = pE; };
  void SetDecayVolID(G4Step* thisStep);
  void SetDecayVolID(G4String thisVolumeName);
  inline void SetHitVol(G4String s){HitVolumeName=s;}
  inline void SetStepProcName(G4String name){StepProcessName=name;}
  inline void SetCreatorProcName(G4String name){CreatorProcessName=name;}
  G4int GetTrackNumber()  { return TrackNumber; };
  G4int GetBlock(){ return BlockHit;};  
  G4int GetLayer(){ return LayerHit;};  
  G4int GetFiber(){ return FiberHit;};
  G4int GetSVert(){ return SVertHit;};
  G4int GetSHoriz(){ return SHorizHit;};
  G4int GetParticleType() { return ParticleType; };
  G4double GetEdep()      { return Edep; };      
  G4double GetEdepIonizing()      { return Edep_Ionizing; };
  G4ThreeVector GetParticleMom() { return ParticleMomentum; };
  G4double GetParticleEnergy()   { return ParticleEnergy; };
  inline G4double GetLocalTime()          { return LocalTime; };
  inline G4double GetGlobalTime()          { return GlobalTime; };
  G4ThreeVector GetHitPosition() { return HitPosition; };
  inline  G4ThreeVector GetVertexPos() { return VertexPosition;}
  inline G4double GetVertexTime() {return VertexTime;}
  G4ThreeVector GetVertexMom() { return VertexMomentum; };
  G4double GetVertexEnergy()   { return VertexEnergy; };
  G4int GetDecayVolID() { return DecayVolID;}
  G4String GetHitVolName(){return HitVolumeName;}
  inline G4String GetStepProcName() {return StepProcessName;}
  inline G4String GetCreatorProcName() {return CreatorProcessName;}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

typedef G4THitsCollection<CaloSimDetectorHit> CaloSimHitsCollection;

extern G4Allocator<CaloSimDetectorHit> CaloSimDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

inline void* CaloSimDetectorHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) CaloSimDetectorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

inline void CaloSimDetectorHit::operator delete(void *aHit)
{
  CaloSimDetectorHitAllocator.FreeSingle((CaloSimDetectorHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#endif


