// $Id: CaloSimSD.cc,v 1.38 2004/04/09 19:02:20 asharp Exp $
// GEANT4 tag $Name:  $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "CaloSimSD.hh"
// #include "MulanRunAction.hh"
// #include "MulanPrimaryGeneratorAction.hh"
// #include "MulanEventAction.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsCollection.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4String.hh"
#include "stdio.h"
#include "math.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimSD::CaloSimSD(G4String name, G4String outputFileName = NULL) :
		G4VSensitiveDetector(name)
{
	G4cout << "CaloSimSD instantiating...";
	G4String HCname = name;
	collectionName.insert(HCname = "detectorCollection");

	//  outfile=fopen("tmp.dat", "w");

	G4cout << " done" << G4endl;

	//  G4String outputFileName="test.root";
	rootFile = new TFile(outputFileName, "RECREATE");

	ntuple =
	        new TNtuple("ntuple",
	                "ROOT Ntuple for G4 data",
	                // 		       "evtIndex:vtxE:initX:initY:initZ:caloX:caloY:caloZ:initPX:initPY:initPZ:caloEdep:fiberEdep:glueEdep:WEdep:b01:b02:b03:b04:b05:b06:b07:b08:b09:b10:b11:b12:b13:b14:b15:b16:b17:b18:b19:b20:b21:b22:b23:b24:b25:v01:v02:v03:v04:v05:v06:v07:v08:v09:v10:v11:v12:v13:v14:v15:h01:h02:h03:h04:h05:h06:h07:h08:h09:h10:h11:h12:h13:h14:h15:totalEdep:diffX:diffY:diffZ:startOut");
	                "evtIndex:vtxE:initX:initY:initZ:caloX:caloY:caloZ:initPX:initPY:initPZ:caloEdep:fiberEdep:glueEdep:WEdep:totalEdep:ratioEdep:diffX:diffY:diffZ:startOut:b01:b02:b03:b04:b05:b06:b07:b08:b09:b10:b11:b12:b13:b14:b15:b16:b17:b18:b19:b20:v01:v02:v03:v04:v05:v06:v07:v08:v09:v10:v11:v12:v13:v14:v15:v16:v17:v18:v19:v20:h01:h02:h03:h04:h05:h06:h07:h08:h09:h10:h11:h12:h13:h14:h15:h16:caloEdep_ps:fiberEdep_ps:glueEdep_ps:WEdep_ps:totalEdep_ps:ratioEdep_ps");

	T = new TTree("T", "ROOT Ntuple for G4 data");

	T->Branch("Theta", &myTheta, "Theta/D");

	T->Branch("NBlockHit", &NBlockHit, "NBlockHit/I");
	NBlockHit = nblock;

	T->Branch("NBlockHitLayer", &NBlockHitLayer, "NBlockHitLayer/I");
	NBlockHitLayer = nblock * nScintlayer;

	T->Branch("NHitLayer", &NHitLayer, "NHitLayer/I");
	NHitLayer = nScintlayer;

	T->Branch("blockID", blockID, "blockID[NBlockHit]/I");
	T->Branch("layerID", layerID, "layerID[NHitLayer]/I");

	T->Branch("blockX", blockX, "blockX[NBlockHit]/D");
	T->Branch("blockY", blockY, "blockY[NBlockHit]/D");

	T->Branch("blockWEdep", blockWEdep, "blockWEdep[NBlockHit]/D");
	T->Branch("blockglueEdep", blockglueEdep, "blockglueEdep[NBlockHit]/D");
	T->Branch("blockfiberEdep", blockfiberEdep, "blockfiberEdep[NBlockHit]/D");
	T->Branch("blockfiberEdep_PS", blockfiberEdep_PS,
	        "blockfiberEdep_PS[NBlockHit]/D");

	// disabled to save file size
//	T->Branch("blockglueEdepLayer",blockglueEdepLayer,"blockglueEdepLayer[NBlockHitLayer]/D");
//	T->Branch("blockfiberEdepLayer",blockfiberEdepLayer,"blockfiberEdepLayer[NBlockHitLayer]/D");

	T->Branch("glueEdepLayer", glueEdepLayer, "glueEdepLayer[NHitLayer]/D");
	T->Branch("fiberEdepLayer", fiberEdepLayer, "fiberEdepLayer[NHitLayer]/D");
	T->Branch("fiberEdepIonizingLayer", fiberEdepIonizingLayer,
	        "fiberEdepIonizingLayer[NHitLayer]/D");
	T->Branch("WEdepLayer", WEdepLayer, "WEdepLayer[NHitLayer]/D");

	T->Branch("blockfiberPhotons", blockfiberPhotons,
	        "blockfiberPhotons[NBlockHit]/D");
	T->Branch("fiberPhotonsLayer", fiberPhotonsLayer,
	        "fiberPhotonsLayer[NHitLayer]/D");

//	G4int xbins = 200;
//	G4double xmax = 200.;
//	Int_t ybins = 320;
//	G4double ymax = 160;
//	EvsFiber = new TH2D("EvsFiber", "EvsFiber", xbins, 0, xmax, ybins, 0, ymax);
//	EvsFiber->SetOption("colz");

	hHit_XY = new TH2F("Hit_XY", "Hit_XY", 600, -300, 300, 400, -300, 300);
	hHit_XZ = new TH2F("Hit_XZ", "Hit_XZ", 600, -300, 300, 600, -0,
	        ShashlikBlockDepth);
	hHit_YZ = new TH2F("Hit_YZ", "Hit_YZ", 400, -300, 300, 600, -0,
	        ShashlikBlockDepth);

//	hStep_Layer = new TH2F("hStep_Layer", "Step size in layer", 1000,0,4);
//	hStep_Fiber = new TH2F("hStep_Fiber", "Step size in Fiber", 1000,0,4);

	hHit_XY->SetOption("colz");
	hHit_XZ->SetOption("colz");
	hHit_YZ->SetOption("colz");

	evtIndex = -1;

	for (int i = 0; i < nblock; i++)
	{
		blockX[i] = 0;
		blockY[i] = 0;
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

CaloSimSD::~CaloSimSD()
{

	//printf("\n\n CLOSING \n\n");
	//  fclose(outfile);
	rootFile->Write();
	rootFile->Close();

	//G4cout<<"This is CaloSimSD destructor\n";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimSD::Initialize(G4HCofThisEvent* HCE)
{
	detectorCollection = new CaloSimHitsCollection(SensitiveDetectorName,
	        collectionName[0]);
	static G4int HCID = -1;
	if (HCID < 0)
	{
		HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}
	HCE->AddHitsCollection(HCID, detectorCollection);
	// resetting variables to be used in each step
	badFirstStep = 0;
	evtIndex++; // events counter starts at 0.
	Prim4VecSet = false;

	fEnteredCalo = 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4bool CaloSimSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
	/////////////////////////////////////////////////////////////////////
	// This function is called when a particle takes a step in a       //
	// sensitive volume. It looks up relevant information about the    //
	// particle, its location, what it's doing, etc. and stores it in a//
	// CaloSimHit object (a new instance of it called newHit is  //
	// made each time). This information is recovered later when       //
	// EndOfEvent() is called. If you want to look at the info while   //
	// it's stored in the hit collection (a vector of CaloSimHit //
	// objects compiled for each event), use the methods of the class  //
	// CaloSimHit, like Print().                                 //
	/////////////////////////////////////////////////////////////////////

	if (badFirstStep == 1)
		return false;
	particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();

	parentID = aStep->GetTrack()->GetParentID();
	currentVolume = aStep->GetPreStepPoint()->GetPhysicalVolume();
	volumeName = currentVolume->GetName();
	const G4VProcess* stepProcess =
	        aStep->GetPostStepPoint()->GetProcessDefinedStep();
	G4String stepProcessName = "None";
	if (stepProcess != NULL)
	{
		stepProcessName = stepProcess->GetProcessName();
	}
	const G4VProcess* creatorProcess = aStep->GetTrack()->GetCreatorProcess();
	G4String creatorProcessName = "None";
	if (creatorProcess != NULL)
	{
		creatorProcessName = creatorProcess->GetProcessName();
	}

//	G4cout << "CaloSimSD::ProcessHits - Step print:"<<G4endl;
//
//	G4cout << "\t particleName = \t"<<particleName<<G4endl;
//	G4cout << "\t volumeName = \t"<<volumeName<<G4endl;
//	G4cout << "\t stepProcessName = \t"<<stepProcessName<<G4endl;
//	G4cout << "\t creatorProcessName = \t"<<creatorProcessName<<G4endl;
//	G4cout << "\t step size = \t"<<aStep->GetStepLength()/mm<<" mm"<<G4endl;

	CaloSimDetectorHit* newHit = new CaloSimDetectorHit();
	// these numbers we know right away
	newHit->SetTrackNumber(aStep->GetTrack()->GetTrackID());
	newHit->SetEdep(aStep->GetTotalEnergyDeposit());
	newHit->SetEdepIonizing(
	        aStep->GetTotalEnergyDeposit()
	                - aStep->GetNonIonizingEnergyDeposit());
	newHit->SetParticleMom(aStep->GetPreStepPoint()->GetMomentum());
	newHit->SetHitPosition(aStep->GetPreStepPoint()->GetPosition());
	newHit->SetHitVol(volumeName);
	newHit->SetParticleEnergy(aStep->GetTrack()->GetKineticEnergy());
	newHit->SetVertexPos(aStep->GetTrack()->GetVertexPosition());

//	if (aStep->GetNonIonizingEnergyDeposit())
//	{
//		G4cout<<"--> Found Non-Ionizing hit "<<aStep->GetNonIonizingEnergyDeposit()<<G4endl;
//	}

//	G4cout<<"newHit->GetHitPosition() = "
//			<<newHit->GetHitPosition().x()<<", "
//			<<newHit->GetHitPosition().y()<<", "
//			<<newHit->GetHitPosition().z()
//			<<G4endl;

	// set the names of process used in this step, and
	// process that created the current particle
	newHit->SetStepProcName(stepProcessName);
	if (creatorProcess != NULL)
	{
		G4String *creator = &creatorProcessName;
		newHit->SetCreatorProcName(*creator);
	}
	else
	{
		newHit->SetCreatorProcName(creatorProcessName);
	}

	newHit->SetVertexMom(aStep->GetTrack()->GetVertexMomentumDirection());
	newHit->SetVertexEnergy(aStep->GetTrack()->GetVertexKineticEnergy());

	G4int hitSVert = 0;
	G4int hitSHoriz = 0;
	G4int hitBlock = 0;
	G4int hitLayer = 0;
	G4int hitFiber = 0;
	if (!strcmp(volumeName, "Fiber"))
	{

		hitBlock = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        2);
		hitLayer = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        1);
		hitFiber = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        0);

		assert(hitFiber==0);
		// Shashlik Mod
	}

	if (!strcmp(volumeName, "Layer") or !strcmp(volumeName, "phrej_Scint")
	        or !strcmp(volumeName, "Leading_Scint")
//			or !strcmp(volumeName, "Backend_Scint")
	        )
	{

		hitBlock = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        1);
		hitLayer = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        0);

		//   G4cout<< volumeName << "  LAYER: " << hitLayer << " FIBER: " << hitFiber
		//	<< "  BLOCK: "  << hitBlock << G4endl;

	}

	if (!strcmp(volumeName, "CaloBlock"))
	{

		hitBlock = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        0);

	}

	if (!strcmp(volumeName, "SVert"))
	{
		hitSVert = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        0);

		assert(0);
		// disabled
	}

	if (!strcmp(volumeName, "SHoriz"))
	{
		hitSHoriz = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(
		        0);

		assert(0);
		// disabled
	}

	newHit->SetSVert(hitSVert);
	newHit->SetSHoriz(hitSHoriz);
	newHit->SetBlock(hitBlock);
	newHit->SetLayer(hitLayer);
	newHit->SetFiber(hitFiber);

	// calculate the particle type number
	G4int type = GetParticleType(particleName, parentID);
	newHit->SetParticleType(type);

	detectorCollection->insert(newHit);

	return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void CaloSimSD::EndOfEvent(G4HCofThisEvent* HCE)
{
	////////////////////////////////////////////////////////////////////
	// This function is called when each Event has completed (i.e., a //
	// primary muon is generated and tracked, then all of its daughter//
	// and granddaughter particles are tracked). It sets the event    //
	// number index in the tree, then calls ProcessEventHC() to fill  //
	// other leaves and branches in the tree.                         //
	////////////////////////////////////////////////////////////////////

	// std::cerr<<"End Of Event ..."<<G4endl;

	// evtIndex is incremented in Initialize() fcn. Starts with 0, not 1.
	if (G4double(G4int(evtIndex / 100)) == (evtIndex / 100.))
		G4cout << "Doing ProcessEventHC on event " << evtIndex << G4endl;

	ProcessEventHC(HCE);
}

double CaloSimSD::Theta = 0;

void CaloSimSD::ProcessEventHC(G4HCofThisEvent* hitCollections)
{
	//////////////////////////////////////////////////////////////////////
	// Called from EndOfEvent(). Does the processing on each of the hit //
	// collections for each event. There is 1 hit collection for each   //
	// sensitive detector declared in CaloSimConstruction. Each   //
	// hit collection is a vector of CaloSimHit objects containing//
	// relevant information about the steps of each particle within a   //
	// sensitive volume. Retrieves information from the CaloSimHit//
	// objects and stores into branches/leaves of DataTree.             //
	//////////////////////////////////////////////////////////////////////

	G4double totalEdep = 0;
	G4double fiberEdep = 0;
	G4double fiberEdepIonizing = 0;
	G4double glueEdep = 0;
	G4double WEdep = 0;

	G4double totalEdep_ps = 0;
	G4double fiberEdep_ps = 0;
	G4double glueEdep_ps = 0;
	G4double WEdep_ps = 0;

	// std::cerr<<"Init Process ..."<<G4endl;

	G4double b[nblock + 100] =
	{ 0 };

	G4double h[nblock + 100] =
	{ 0 };
	G4double v[nblock + 100] =
	{ 0 };

	for (int i = 0; i < nblock; i++)
	{
		b[i] = h[i] = v[i] = 0;

		blockWEdep[i] = blockglueEdep[i] = blockfiberEdep[i] =
		        blockfiberEdep_PS[i] = blockfiberPhotons[i] = 0;

		blockID[i] = i;
		for (int j = 0; j < nScintlayer; j++)
		{
			assert(i*nScintlayer + j<NBlockHitLayer);
			blockglueEdepLayer[i * nScintlayer + j] = 0;
			blockfiberEdepLayer[i * nScintlayer + j] = 0;
			blockfiberPhotonsLayer[i * nScintlayer + j] = 0;
		}
	}
	for (int j = 0; j < nScintlayer; j++)
	{
		layerID[j] = j;
		glueEdepLayer[j] = 0;
		fiberEdepLayer[j] = 0;
		fiberEdepIonizingLayer[j] = 0;
		WEdepLayer[j] = 0;
		fiberPhotonsLayer[j] = 0;
	}

	// std::cerr<<"Start Process ..."<<G4endl;

	CaloSimHitsCollection *aHitCollWithinThisEvent;

	// loop over the Hit Collections (1 for each SD in DetConstruction)
	G4int NCollections = hitCollections->GetNumberOfCollections();
	for (G4int n = 0; n < NCollections; n++)
	{
		aHitCollWithinThisEvent =
		        (CaloSimHitsCollection*) hitCollections->GetHC(n);
		G4int EntriesWithinHitColl = aHitCollWithinThisEvent->entries();

		// loop over the hits within the hit collections
		for (G4int ent = 0; ent < EntriesWithinHitColl; ent++)
		{
			//    G4cout<<"Starting entry "<<ent<<" of "<<EntriesWithinHitColl<<G4endl;
//			G4int thisType = (*aHitCollWithinThisEvent)[ent]->GetParticleType();
			G4String thisProcess =
			        (*aHitCollWithinThisEvent)[ent]->GetStepProcName();
			G4String thisVolume =
			        (*aHitCollWithinThisEvent)[ent]->GetHitVolName();
			G4int trackID = (*aHitCollWithinThisEvent)[ent]->GetTrackNumber();

			G4double edep = (*aHitCollWithinThisEvent)[ent]->GetEdep();
			G4double edep_ionizing =
			        (*aHitCollWithinThisEvent)[ent]->GetEdepIonizing();

			G4int block = (*aHitCollWithinThisEvent)[ent]->GetBlock();
			G4int layer = (*aHitCollWithinThisEvent)[ent]->GetLayer();
			assert(block<nblock && block>=0);
			assert(layer<nScintlayer && layer>=0);

			G4ThreeVector hitpos =
			        (*aHitCollWithinThisEvent)[ent]->GetHitPosition();

//			// std::cerr<<"Test Process ..."<<G4endl;

			if (!strcmp(thisVolume, "CaloBlock"))
			{
				WEdep = WEdep + edep;

				blockWEdep[block] += edep;

				G4int Wlayer = floor(
				        (hitpos.z() - (phrej_Scint + leading_Pb + leading_Scint
				                + front_spt_plate)) / layerSep) + 1;
				if (Wlayer < 0)
					Wlayer = 0;

				if (Wlayer < nScintlayer && Wlayer >= 0)
					WEdepLayer[Wlayer] += edep;
				else
					G4cout << "Error Wlayer = " << Wlayer << G4endl;

			}
			if (!strcmp(thisVolume, "Layer"))
			{
				glueEdep = glueEdep + edep;
				totalEdep = totalEdep + edep;

				assert(block<nblock);
				blockglueEdep[block] += edep;

				assert(block*nScintlayer+layer<nblock*nScintlayer);
				blockglueEdepLayer[block * nScintlayer + layer] += edep;

				assert(layer<nScintlayer);
				glueEdepLayer[layer] += edep;

			}
			if (!strcmp(thisVolume, "Fiber")
			        or !strcmp(thisVolume, "phrej_Scint")
			        or !strcmp(thisVolume, "Leading_Scint")
//					or !strcmp(thisVolume, "Backend_Scint")
			        )
			{
				const G4double photon = Edep2Photon(edep, hitpos);

				if (!strcmp(thisVolume, "phrej_Scint"))
					assert(layer == 0);

				if (!strcmp(thisVolume, "Leading_Scint"))
					assert(layer == 1);

//				if (!strcmp(thisVolume, "Backend_Scint"))
//					assert(layer == nScintlayer-1);

				fiberEdep = fiberEdep + edep;
				totalEdep = totalEdep + edep;
				fiberEdepIonizing = fiberEdepIonizing + edep_ionizing;

				assert(block<nblock);

				if (layer == 1)
					blockfiberEdep_PS[block] += edep;
				else if (layer > 1)
					blockfiberEdep[block] += edep;
				blockfiberPhotons[block] += photon;

				assert(block*nScintlayer+layer<nblock*nScintlayer);
				blockfiberEdepLayer[block * nScintlayer + layer] += edep;
				blockfiberPhotonsLayer[block * nScintlayer + layer] += photon;

				assert(layer<nScintlayer);
				fiberEdepLayer[layer] += edep;
				fiberEdepIonizingLayer[layer] += edep_ionizing;
				fiberPhotonsLayer[layer] += photon;

			}
//			// std::cerr<<"Test Process ..."<<G4endl;

			//if(!strcmp(thisVolume,"Fiber") || !strcmp(thisVolume,"Layer")){
//			if (!strcmp(thisVolume, "Fiber"))
//			{ // Use only the fiber energy
//				b[block - 1] = b[block - 1] + edep;

			//G4cout << "block = "  << block << "\n";
			//G4cout << thisVolume << " " << edep << " " << block << "\n";
//			}

			pos = (*aHitCollWithinThisEvent)[ent]->GetHitPosition();
			hHit_XY->Fill(pos.x(), pos.y(), edep);
			hHit_XZ->Fill(pos.x(), pos.z(), edep);
			hHit_YZ->Fill(pos.y(), pos.z(), edep);

			//       totalEdep=totalEdep+edep;

			if (trackID == 1 && !Prim4VecSet)
			{
				vtxPos = (*aHitCollWithinThisEvent)[ent]->GetVertexPos();
				vtxMom = (*aHitCollWithinThisEvent)[ent]->GetVertexMom();

				vtxE = (*aHitCollWithinThisEvent)[ent]->GetVertexEnergy();
				if (vtxE < 1e-10)
					vtxE = 0.0; // truncate very small numbers
				fStartOut = 0;
				if (!strcmp(thisVolume, "expHall"))
					fStartOut = 1;
				Prim4VecSet = true; // flag to say this info recorded once
			}

			/* if(strcmp(thisVolume,"expHall")&&!fEnteredCalo){
			 caloPos = (*aHitCollWithinThisEvent)[ent]->GetVertexPos();
			 }*/

//			if (trackID == 1 && (!strcmp(thisVolume, "CaloBlock") || !strcmp(
//			        thisVolume, "Layer") || !strcmp(thisVolume, "Fiber"))
//			        && fEnteredCalo == 0)
//			{
//
//				//G4cout<<thisVolume<<G4endl;
//				caloPos = (*aHitCollWithinThisEvent)[ent]->GetHitPosition();
//				diffPos = caloPos - vtxPos;
//				fEnteredCalo = 1;
//			}
		} // 		for (G4int ent = 0; ent < EntriesWithinHitColl; ent++)

	}

	// std::cerr<<"Ending Process ..."<<G4endl;

	G4double caloX = caloPos.x();
	G4double caloY = caloPos.y();
	G4double caloZ = caloPos.z();
//	G4cout<<"caloX= "<<caloX/cm+7.5<<"   caloY= "<<caloY/cm+7.5<<"   caloZ= "<<caloZ/cm<<G4endl;

	G4double initX = vtxPos.x();
	G4double initY = vtxPos.y();
	G4double initZ = vtxPos.z();
	G4double initPX = vtxMom.x();
	G4double initPY = vtxMom.y();
	G4double initPZ = vtxMom.z();

	G4double diffX = diffPos.x();
	G4double diffY = diffPos.y();
	G4double diffZ = diffPos.z();

	G4double caloEdep = fiberEdep + glueEdep + WEdep;
	G4double ratioEdep = fiberEdep / WEdep;

	G4double caloEdep_ps = fiberEdep_ps + glueEdep_ps + WEdep_ps;
	G4double ratioEdep_ps = fiberEdep_ps / WEdep_ps;

	// std::cerr<<"ntpars ..."<<G4endl;
	Float_t ntpars[200] =
	{ evtIndex, vtxE / GeV, initX / cm, initY / cm, initZ / cm, caloX / cm,
	        caloY / cm, caloZ / cm, initPX, initPY, initPZ, caloEdep / GeV,
	        fiberEdep / GeV, glueEdep / GeV, WEdep / GeV, totalEdep / GeV,
	        ratioEdep / GeV, diffX / cm, diffY / cm, diffZ / cm, fStartOut, b[0]
	                / GeV, b[1] / GeV, b[2] / GeV, b[3] / GeV, b[4] / GeV, b[5]
	                / GeV, b[6] / GeV, b[7] / GeV, b[8] / GeV, b[9] / GeV, b[10]
	                / GeV, b[11] / GeV, b[12] / GeV, b[13] / GeV, b[14] / GeV,
	        b[15] / GeV, b[16] / GeV, b[17] / GeV, b[18] / GeV, b[19] / GeV,
	        v[0] / GeV, v[1] / GeV, v[2] / GeV, v[3] / GeV, v[4] / GeV, v[5]
	                / GeV, v[6] / GeV, v[7] / GeV, v[8] / GeV, v[9] / GeV, v[10]
	                / GeV, v[11] / GeV, v[12] / GeV, v[13] / GeV, v[14] / GeV,
	        v[15] / GeV, v[16] / GeV, v[17] / GeV, v[18] / GeV, v[19] / GeV,
	        h[0] / GeV, h[1] / GeV, h[2] / GeV, h[3] / GeV, h[4] / GeV, h[5]
	                / GeV, h[6] / GeV, h[7] / GeV, h[8] / GeV, h[9] / GeV, h[10]
	                / GeV, h[11] / GeV, h[12] / GeV, h[13] / GeV, h[14] / GeV,
	        h[15] / GeV, caloEdep_ps / GeV, fiberEdep_ps / GeV, glueEdep_ps
	                / GeV, WEdep_ps / GeV, totalEdep_ps / GeV, ratioEdep_ps
	                / GeV };
	// std::cerr<<"Done ntpars ..."<<G4endl;

	assert(ntuple);
	ntuple->Fill(ntpars);
	// std::cerr<<"Done ntuple ..."<<G4endl;

	assert(NBlockHit<=nblock);
	assert(NBlockHitLayer<=nblock*nScintlayer);
	assert(NHitLayer<=nScintlayer);

	myTheta = Theta;

	// process photon numbers

	for (int i = 0; i < nblock; i++)
	{

		blockfiberPhotons[i] = RndGen.Poisson(blockfiberPhotons[i]);

		for (int j = 0; j < nScintlayer; j++)
		{
			blockfiberPhotonsLayer[i * nScintlayer + j] = RndGen.Poisson(
			        blockfiberPhotonsLayer[i * nScintlayer + j]);
		}
	}
	for (int j = 0; j < nScintlayer; j++)
	{
		fiberPhotonsLayer[j] = RndGen.Poisson(fiberPhotonsLayer[j]);
	}

	assert(T);
	T->Fill();

	// std::cerr<<"Done Process ..."<<G4endl;

	/*
	 fprintf(outfile, "%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t",
	 evtIndex, vtxE/GeV, initX/cm, initY/cm, initZ/cm,
	 initPX, initPY, initPZ,
	 caloEdep/GeV);
	 for(G4int bi=1; bi<=20; bi++){
	 fprintf(outfile, "%f\t", b[bi-1]/GeV);
	 }
	 fprintf(outfile, "\n");
	 */

	G4cout << "Sampling ratio = " << fiberEdep / (fiberEdep + glueEdep + WEdep)
	        << ", " << fiberEdepIonizing / (fiberEdep + glueEdep + WEdep)
	        << " (Ionizing)" << G4endl;
}

G4int CaloSimSD::GetParticleType(G4String particleName, G4int parentID)
{
	if (!strcmp(particleName, "e+") && parentID == 1)
	{
		return 1;
	}
	else if (!strcmp(particleName, "e-"))
	{
		return 2;
	}
	else if (!strcmp(particleName, "gamma"))
	{
		return 3;
	}
	else if (!strcmp(particleName, "mu+") && parentID == 0)
	{
		return 4;
	}
	else if (!strcmp(particleName, "e+") && parentID > 1)
	{
		return 5;
	}
	else
	{
		return 6;
	}
}

