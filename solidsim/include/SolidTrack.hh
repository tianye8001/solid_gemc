#ifndef SOLIDTRACK_HH
#define SOLIDTRACK_HH

#include "G4ThreeVector.hh"

class SolidTrack {
    public:
	SolidTrack();
	SolidTrack(G4ThreeVector, double,
	       	   G4ThreeVector, int, G4String);
	SolidTrack(double, double, double, double,
	       	   double, double, double, int, G4String);
       SolidTrack(const SolidTrack &);
       ~SolidTrack();
       const SolidTrack& operator=(const SolidTrack &);

       void Print();

       G4ThreeVector GetPos(){ return fPos; }
       G4ThreeVector GetP(){ return fP; }
       double GetAbsP(){ return sqrt(fP*fP); }
       double GetE(){ return fE;}
       int GetID(){ return fID;}
       G4String GetPartType(){ return fPartType;}

       double GetMass(){ return sqrt(fE*fE - fP*fP);}

    private:
       G4ThreeVector fPos;
       G4ThreeVector fP;
       double   fE;
       int      fID;
       G4String fPartType;
};

#endif//SOLIDTRACK_HH

