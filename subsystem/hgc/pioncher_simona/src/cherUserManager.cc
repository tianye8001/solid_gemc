#include "cherUserManager.hh"
#include <fstream>
#include <iomanip>
#include "G4Track.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherUserManager* cherUserManager::fUserManager = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherUserManager::cherUserManager()
{
	if(fUserManager)
	{
		G4Exception("cherUserManager constructed twice.");
	}
	fUserManager = this;
	SPMhits = WChits = PMThits = 0;

	vector<double> photonenergy_mirror;
	vector<double> photonenergy_PMT;
	vector<double> photonenergy_WC;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherUserManager::~cherUserManager()
{
	fUserManager = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherUserManager* cherUserManager::GetUserManager()
{
	return fUserManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherUserManager::SetHit(G4int nhit, G4int type)
{
  if(type == 1)  // Spherical Mirror 1
    SPMhits = nhit;
  else if(type == 2) // PMT
    PMThits = nhit;
  else if(type == 3) // WC
    WChits = nhit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherUserManager::AddHit(G4Track* aTrack, G4int type)
{

  if(type == 1)
    {    SPMhits ++;
      //      G4cout << "hit and energy: " << SPMhits << " " << aTrack->GetKineticEnergy()/eV << G4endl;

      photonenergy_mirror.push_back(aTrack->GetKineticEnergy()/eV);

    }
  else if(type == 2)
    {    PMThits ++;
      //      G4cout << "hit and energy: " << PMThits << " " << aTrack->GetKineticEnergy()/eV << G4endl;  
      photonenergy_PMT.push_back(aTrack->GetKineticEnergy()/eV);
      
    }

  else if(type == 3)
    {    WChits ++;
      //      G4cout << "hit and energy: " << PMThits << " " << aTrack->GetKineticEnergy()/eV << G4endl;  
      photonenergy_WC.push_back(aTrack->GetKineticEnergy()/eV);
      
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int cherUserManager::GetHit(G4int type)
{
  G4int hits = 0;
  if(type == 1)
    hits = SPMhits;
  else if(type == 2)
    hits = PMThits;
  else if(type == 3)
    hits = WChits;
  return hits;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherUserManager::SaveToFile()
{

  //  ofstream theOutResult("output_perfectmirror_11.5deg_3gev.dat");
  ofstream theOutResult("crap_mirror.dat");
  
  theOutResult.precision(4);
  
  for (int i = 0; i < photonenergy_mirror.size(); i++)
    {
      
      /*      G4cout << "does this work ????????????: " << i << " " 
	      << photonenergy_mirror[i] << G4endl; */
      theOutResult << setw(10) << SPMhits << " " 
		   << setw(10) << photonenergy_mirror[i] << G4endl;
    }
  theOutResult.close();    

  //  ofstream theOutpmtResult("output_pmt_11.5deg_3gev.dat");
  ofstream theOutpmtResult("crap_pmt.dat");
  
  theOutpmtResult.precision(4);
  
  for (int i = 0; i < photonenergy_PMT.size(); i++)
    {
      
      /*      G4cout << "does this work ????????????: " << i << " " 
	      << photonenergy_PMT[i] << G4endl; */
      theOutpmtResult << setw(10) << PMThits << " " 
		      << setw(10) << photonenergy_PMT[i] << G4endl;
    }
  theOutpmtResult.close();    

  ofstream theOutwcResult("crap_wc.dat");
  
  theOutwcResult.precision(4);
  
  for (int i = 0; i < photonenergy_WC.size(); i++)
    {
      
      /*      G4cout << "does this work ????????????: " << i << " " 
	      << photonenergy_PMT[i] << G4endl; */
      theOutwcResult << setw(10) << WChits << " " 
		     << setw(10) << photonenergy_WC[i] << G4endl;
    }
  theOutwcResult.close();    
  
  
}

