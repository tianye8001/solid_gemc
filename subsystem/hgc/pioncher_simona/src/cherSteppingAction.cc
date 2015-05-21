#include "cherSteppingAction.hh"
#include "cherUserManager.hh"
#include "G4Track.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherSteppingAction::cherSteppingAction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherSteppingAction::~cherSteppingAction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cherSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	// Get Pointers
	//
	cherUserManager* userManager = cherUserManager::GetUserManager();
	G4Track* theTrack = aStep->GetTrack();
	G4int theTrackID = theTrack->GetTrackID();
	// Only count for secondary optical photon
	//
	if( theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && theTrack->GetParentID() > 0 )
	  //	if( theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
	{

		// Find Boundary Process
		//
		G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
		G4OpBoundaryProcessStatus boundaryStatus = Undefined;
		G4OpBoundaryProcess* boundary = NULL;
		if( !boundary )
		{
			G4ProcessManager* pm = theTrack->GetDefinition()->GetProcessManager();
			G4int nprocesses = pm->GetProcessListLength();
			G4ProcessVector* pv = pm->GetProcessList();
			boundary=(G4OpBoundaryProcess*)(*pv)[0];
			for ( G4int i=0; i<nprocesses; i++ )
			{
				if( (*pv)[i]->GetProcessName()=="OpBoundary" )
				  {
				    boundary=(G4OpBoundaryProcess*)(*pv)[i];
				    break;
				  }
			}
		}
		if( thePostPoint->GetStepStatus() == fGeomBoundary )
		  {
		    if( boundary )
		      {
			boundaryStatus = boundary->GetStatus();
		      }
		    switch( boundaryStatus )
		      {
		      case SpikeReflection: //mirror or cone
			{
			  if(theTrack->GetNextVolume()->GetLogicalVolume()->GetName() == "Mirror_1")
			    {
			      static G4int MirPreTrackID = -1;
			      //			      if(MirPreTrackID != theTrackID || theTrack->GetParentID()==0 )
			      if(MirPreTrackID != theTrackID)
				{
				  userManager->AddHit(theTrack,1);
				  MirPreTrackID = theTrackID;
				  G4cout << "photon energy is:::::::::::::::::::::::::::::::::::::::::::::::::::: " 
					 << theTrack->GetKineticEnergy()/eV << " " << "and the trackID is: " <<MirPreTrackID << G4endl;
				}
			    }
			  else if (theTrack->GetNextVolume()->GetLogicalVolume()->GetName() == "winston_cone")
			    {
			      static G4int WcPreTrackID = -1;
			      if(WcPreTrackID != theTrackID)
				{
				  userManager->AddHit(theTrack,3);
				  WcPreTrackID = theTrackID;
				  G4cout << "photon energy is:::::::::::::::::::::::::::::::::::::::::::::::::::: " 
					 << theTrack->GetKineticEnergy()/eV << " " << "and the trackID is: " <<WcPreTrackID << G4endl;
				}			      
			    }
			  break;
			}
		      case Detection:
			{
			  static G4int PMTPreTrackID = -1;
			  if( PMTPreTrackID != theTrackID)
			    {
			      if(theTrack->GetNextVolume()->GetLogicalVolume()->GetName() == "Observer")
				{
				  userManager->AddHit(theTrack,2);
				  PMTPreTrackID = theTrackID;
				}
			    }
			  break;
			}
		      default:
			break;
		      }
		  }
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
