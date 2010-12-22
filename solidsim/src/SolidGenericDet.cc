#include "SolidGenericDet.hh"
#include "SolidData.hh"
#include "SolidDatum.hh"
#include "SolidSDMan.hh"

#include "TObjString.h"


SolidGenericDet::SolidGenericDet(G4String name) :
    G4VSensitiveDetector(name), SolidData(name.data()) 
{
    const char *fname = "SolidGenericDet()";

    // Initialize tree variables

    foNhit = new SolidDatum(this, kInt, "hit.n");

    foEdep = new SolidDatum(this, kDouble, "hit.Edep");
    foTime = new SolidDatum(this, kDouble, "hit.time");

    foTrX  = new SolidDatum(this, kDouble, "hit.tr.x");
    foTrY  = new SolidDatum(this, kDouble, "hit.tr.y");
    foTrZ  = new SolidDatum(this, kDouble, "hit.tr.z");
    foTrE  = new SolidDatum(this, kDouble, "hit.tr.E");
    foTrP  = new SolidDatum(this, kDouble, "hit.tr.p");
    foTrPx = new SolidDatum(this, kDouble, "hit.tr.px");
    foTrPy = new SolidDatum(this, kDouble, "hit.tr.py");
    foTrPz = new SolidDatum(this, kDouble, "hit.tr.pz");

    foTrID = new SolidDatum(this, kInt, "hit.tr.ID");

    foFADCa = new SolidDatum(this, kDouble, "fadc_a");
    foFADCt = new SolidDatum(this, kDouble, "fadc_t");
    foADC   = new SolidDatum(this, kDouble, "adc");
    foTDC   = new SolidDatum(this, kDouble, "tdc");

    foPname = new SolidDatum(this, kString, "hit.tr.pname");

    printf("Registering data\n");
    RegisterData();
    printf("Registered\n");

    /////////////////////////////

    SolidSDMan *sdman = SolidSDMan::GetInstance();

    if( !sdman ){
	fprintf(stderr, "%s::%s  Warning: Could not find Solid SD Manager\n",
		GetClassName(), fname);
    } else {
	sdman->Register(this);
    }


    // Default values for detector
    // FIXME:
    // These should be controlled by
    // messenger

    fGate_start = 0.0*ns;
    fGate_stop  = 20.0*ns;
    fFADC_size  = 0.100*ns;
    fTDC_thresh = 1.0*MeV;
    fTDC_deadtime = 5.0*ns;
}

SolidGenericDet::~SolidGenericDet(){
    ClearData();

    // FIXME:  This is awful
    // We need to fix the SD manager destroying
    // the detectors we create in the interpreter
    // in its destructor.  Exiting here (because it's
    // at the very end after we're written output and
    // after the visualization manager dies) to prevent 
    // segfaults.  I'm sooo, sooo sorry about this.
    // - Seamus
    exit(0);

    return;
}

void SolidGenericDet::Initialize(G4HCofThisEvent*) {
    fHits = new SolidGenericDetHitsCollection 
	(SensitiveDetectorName,"GenericHC"); 
}

G4bool SolidGenericDet::ProcessHits(G4Step* aStep, G4TouchableHistory*){

    double edep = aStep->GetTotalEnergyDeposit();
    if( edep<=0.0) return false;


    double time = aStep->GetPreStepPoint()->GetGlobalTime();


    // Track info
    double partE = aStep->GetTrack()->GetTotalEnergy();
    G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector p   = aStep->GetPreStepPoint()->GetMomentum();
    int    partID = aStep->GetTrack()->GetTrackID();
    G4String partName = aStep->GetTrack()->GetDefinition()->GetParticleName();
    //    printf("hit of energy %f MeV by %d\n", edep, partID);

    SolidTrack tr( pos, partE, p, partID, partName);

    SolidGenericDetHit* hit =
	new SolidGenericDetHit(tr, time, edep);

    fHits->insert(hit);

    return true;
}

void SolidGenericDet::EndOfEvent(G4HCofThisEvent*){
    unsigned int i;
    foNhit->Fill(fHits->entries());

    // Copy hits into arrays
    foTrX->Resize(fHits->entries());
    foTrY->Resize(fHits->entries());
    foTrZ->Resize(fHits->entries());
    foTrE->Resize(fHits->entries());
    foTrP->Resize(fHits->entries());
    foTrPx->Resize(fHits->entries());
    foTrPy->Resize(fHits->entries());
    foTrPz->Resize(fHits->entries());
    foTrID->Resize(fHits->entries());

    SolidGenericDetHit *hit;
    SolidTrack tr;

    for( i = 0; i < fHits->entries(); i++ ){
	hit = (*fHits)[i];
	tr  = hit->GetTrack();

	foTrX->Fill(tr.GetPos().X/m, i);
	foTrY->Fill(tr.GetPos().Y/m, i);
	foTrZ->Fill(tr.GetPos().Z/m, i);
	foTrE->Fill(tr.GetE()/MeV, i);
	foTrP->Fill(tr.GetAbsP()/MeV, i);

	foTrPx->Fill(tr.GetP().X/MeV, i);
	foTrPy->Fill(tr.GetP().Y/MeV, i);
	foTrPz->Fill(tr.GetP().Z/MeV, i);

	foTrID->Fill(tr.GetID(), i);

	foPname->Push(tr.GetPartType().data());
    }

    return;
}

void SolidGenericDet::clear(){
    return;
}
