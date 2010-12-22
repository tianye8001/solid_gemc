#ifndef SOLIDSDMAN_HH
#define SOLIDSDMAN_HH

#include <vector>
#include <G4VSensitiveDetector.hh>

/*!  
 * This is a static class that's a workaround
 * since the SDM is not included in the
 * present python bindings.  All detectors
 * will statically add themselves to this
 * at their initialziation
*/

class SolidSDMan {
    public:
	SolidSDMan();
       ~SolidSDMan();

       void Register(G4VSensitiveDetector *d){ printf("Registering\n"); fDet.push_back(d);}

       unsigned int GetNdet(){ return fDet.size();}
       G4VSensitiveDetector *GetDet(int i){ return fDet[i]; }

       static SolidSDMan *GetInstance();

       const char *GetClassName(){return "SolidSDMan";}

       void Clear();
    private:
       std::vector<G4VSensitiveDetector *> fDet;

       static int __SolidSDManInit;
       static SolidSDMan *__SolidSDManPtr;

};

#endif//SOLIDSDMAN_HH
