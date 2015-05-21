// This class is used to collect hit information
//

#ifndef cherUserManager_h
#define cherUserManager_h 1
#include "G4Track.hh"
#include <vector>
#include "globals.hh"
#include <map>

using namespace std;

class cherUserManager
{
public:
  cherUserManager();
  ~cherUserManager();
  static cherUserManager* GetUserManager();
  void SetHit(G4int, G4int);
  //  void AddHit(G4Track*, G4int, G4ThreeVector, G4ThreeVector, G4double);
  void AddHit(G4Track*, G4int);
  //  void AddHit(G4Track*, G4int, G4ThreeVector);
  G4int GetHit(G4int);
  void SaveToFile();
  
private:
  static cherUserManager* fUserManager;
  G4int SPMhits;
  G4int SPM2hits;
  G4int PMThits;
  G4int WChits;
  vector<double> photonenergy_mirror;
  vector<double> photonenergy_mirror2;
  vector<double> photonenergy_PMT;

  vector<double> photonpositionx_PMT;
  vector<double> photonpositiony_PMT;
  vector<double> photonpositionz_PMT;

  vector<double> photonpositionxl_PMT;
  vector<double> photonpositionyl_PMT;
  vector<double> photonpositionzl_PMT;

  /*  vector<double> photonpositioniz_PMT;
  vector<double> photonpositioniy_PMT;
  vector<double> photonpositionix_PMT;
  vector<double> photonpositionfz_PMT;
  vector<double> photonpositionfy_PMT;
  vector<double> photonpositionfx_PMT;
  vector<double> photondistance_PMT; */

  vector<double> photonenergy_WC;
};

#endif
