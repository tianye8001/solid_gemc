#include "SolidGenericDet.hh"
#include "SolidData.hh"
#include "SolidDatum.hh"
#include "SolidSDMan.hh"
#include "SolidGenericDetMessenger.hh"

#include "TObjString.h"


SolidGenericDet::SolidGenericDet(G4String name) :
    G4VSensitiveDetector(name), SolidData(name.data()) 
{
    const char *fname = "SolidGenericDet()";

    // Initialize tree variables

    foNhit  = new SolidDatum(this, kInt,    "hit.n");
    foEdep  = new SolidDatum(this, kDouble, "hit.Edep");
    foTime  = new SolidDatum(this, kDouble, "hit.time");
    foTrX   = new SolidDatum(this, kDouble, "hit.x");
    foTrY   = new SolidDatum(this, kDouble, "hit.y");
    foTrZ   = new SolidDatum(this, kDouble, "hit.z");
    foTrE   = new SolidDatum(this, kDouble, "hit.E");
    foTrP   = new SolidDatum(this, kDouble, "hit.p");
    foTrPx  = new SolidDatum(this, kDouble, "hit.px");
    foTrPy  = new SolidDatum(this, kDouble, "hit.py");
    foTrPz  = new SolidDatum(this, kDouble, "hit.pz");

    foTrID  = new SolidDatum(this, kInt,    "hit.ID");

    foFADCa = new SolidDatum(this, kDouble, "fadc_a");
    foFADCt = new SolidDatum(this, kDouble, "fadc_t");
    foADC   = new SolidDatum(this, kDouble, "adc");
    foTDC   = new SolidDatum(this, kDouble, "tdc");

    foPname = new SolidDatum(this, kString, "hit.tr.pname");
    
    // First hits of a track with a particular ID
    fofNhit  = new SolidDatum(this, kInt,    "fhit.n");
    fofTrX   = new SolidDatum(this, kDouble, "fhit.x");
    fofTrY   = new SolidDatum(this, kDouble, "fhit.y");
    fofTrZ   = new SolidDatum(this, kDouble, "fhit.z");
    fofTrE   = new SolidDatum(this, kDouble, "fhit.E");
    fofTrP   = new SolidDatum(this, kDouble, "fhit.p");
    fofTrPx  = new SolidDatum(this, kDouble, "fhit.px");
    fofTrPy  = new SolidDatum(this, kDouble, "fhit.py");
    fofTrPz  = new SolidDatum(this, kDouble, "fhit.pz");
    fofTrID  = new SolidDatum(this, kInt,    "fhit.ID");
    fofTime  = new SolidDatum(this, kDouble, "fhit.time");
    fofPname = new SolidDatum(this, kString, "fhit.pname");

    RegisterData();

    /////////////////////////////

    SolidSDMan *sdman = SolidSDMan::GetInstance();

    if( !sdman ){
	fprintf(stderr, "%s::%s  Warning: Could not find Solid SD Manager\n",
		GetClassName(), fname);
    } else {
	sdman->Register(this);
    }

    // Default response parameters for detector

    fGate_start = 0.0*ns;
    fGate_stop  = 40.0*ns;
    fFADC_tRes  = 0.100*ns;
    fTDC_thresh = 0.0*MeV;
    fTDC_deadtime = 5.0*ns;

    // Messenger to control detector parameters
    new SolidGenericDetMessenger(this);
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
    double partE      = aStep->GetTrack()->GetTotalEnergy();
    int    partID     = aStep->GetTrack()->GetTrackID();
    G4String partName = aStep->GetTrack()->GetDefinition()->GetParticleName();
    G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector p   = aStep->GetPreStepPoint()->GetMomentum();

    SolidTrack tr( pos, partE, p, partID, partName );

    SolidGenericDetHit* hit =
	new SolidGenericDetHit(tr, time/ns, edep/MeV);

    fHits->insert(hit);

    return true;
}

void SolidGenericDet::EndOfEvent(G4HCofThisEvent*){
    const char *fname = "EndOfEvent";

    int i;
    foNhit->Fill(fHits->entries());


    // Copy hits into arrays
    foTime->Resize(fHits->entries());
    foEdep->Resize(fHits->entries());

    foTrX->Resize(fHits->entries());
    foTrY->Resize(fHits->entries());
    foTrZ->Resize(fHits->entries());
    foTrE->Resize(fHits->entries());
    foTrP->Resize(fHits->entries());
    foTrPx->Resize(fHits->entries());
    foTrPy->Resize(fHits->entries());
    foTrPz->Resize(fHits->entries());
    foTrID->Resize(fHits->entries());

    // Make sure we have enough memory for the
    // first hit arrays.
    // this is kinda lazy, since it's a huge
    // over estimation of what we actually need
    fofTime->Resize(fHits->entries());
    fofTrX->Resize(fHits->entries());
    fofTrY->Resize(fHits->entries());
    fofTrZ->Resize(fHits->entries());
    fofTrE->Resize(fHits->entries());
    fofTrP->Resize(fHits->entries());
    fofTrPx->Resize(fHits->entries());
    fofTrPy->Resize(fHits->entries());
    fofTrPz->Resize(fHits->entries());
    fofTrID->Resize(fHits->entries());

    SolidGenericDetHit *hit;
    SolidTrack tr;

    int bin;
    int nbin = GetNFADC();
    double *fadcvals = new double[nbin];
    double *fadctime = new double[nbin];
    double scale;

    double Edepsum = 0.0;

    // Initialize
    for( i = 0; i < nbin; i++ ){
	fadcvals[i] = 0.0;
	scale = ((double) i)/nbin;
	fadctime[i] = (fGate_stop-fGate_start)*scale + fGate_start;
    }

    unsigned int idx;

    std::vector <int>idvec;
    std::vector <double>timevec;

    for( i = 0; i < fHits->entries(); i++ ){
	// Hit-by-hit information
	hit = (*fHits)[i];
	tr  = hit->GetTrack();

	foTime->Fill(hit->GetEdep()/MeV,i);
	foEdep->Fill(hit->GetTime()/ns,i);

	foTrX->Fill(tr.GetPos().x()/m, i);
	foTrY->Fill(tr.GetPos().y()/m, i);
	foTrZ->Fill(tr.GetPos().z()/m, i);
	foTrE->Fill(tr.GetE()/MeV, i);
	foTrP->Fill(tr.GetAbsP()/MeV, i);

	foTrPx->Fill(tr.GetP().x()/MeV, i);
	foTrPy->Fill(tr.GetP().y()/MeV, i);
	foTrPz->Fill(tr.GetP().z()/MeV, i);

	foTrID->Fill(tr.GetID(), i);

	foPname->Push(tr.GetPartType().data());

	// Determine if this is a unique track
	// Only do this analysis if it's meaningful
	// as it is time consuming
	if( FirstHitsAreActive() ){
	    idx = 0;
	    while( idx < idvec.size() && tr.GetID() != idvec[idx] ){
		idx++;
	    }

	    // Didn't find this ID
	    // This is the first time we've seen this
	    // Add it to the list
	    if( idx == idvec.size() ){
		idvec.push_back(tr.GetID());
		timevec.push_back(hit->GetTime());

		// Fill with values
		fofTime->Fill(hit->GetTime()/ns, idx);
		fofTrX->Fill(tr.GetPos().x()/m, idx);
		fofTrY->Fill(tr.GetPos().y()/m, idx);
		fofTrZ->Fill(tr.GetPos().z()/m, idx);
		fofTrE->Fill(tr.GetE()/MeV, idx);
		fofTrP->Fill(tr.GetAbsP()/MeV, idx);
		fofTrPx->Fill(tr.GetP().x()/MeV, idx);
		fofTrPy->Fill(tr.GetP().y()/MeV, idx);
		fofTrPz->Fill(tr.GetP().z()/MeV, idx);
		fofTrID->Fill(tr.GetID(), idx);
		fofPname->Push(tr.GetPartType().data());
	    } else {
		if( timevec[idx] > hit->GetTime() ){
		    fprintf(stderr, "%s::%s Warning:  Hits with same ID processed\n out of time order.  ID %d was seen at %f ns and now has a hit at %f ns\n",
			    GetClassName(), fname, tr.GetID(), timevec[idx], hit->GetTime()/ns);
		}
	    }
	}

	// Build FADC histograms

	// -1 here is if we are outside our
	// gate
	bin = GetFADCbin(hit->GetTime());
	if( bin != -1 ){
	    fadcvals[bin] += hit->GetEdep();
	}
	fofNhit->Fill((int) idvec.size());

	// Refix array size
	// to what it actually is
	fofTime->Resize(idvec.size());
	fofTrX->Resize(idvec.size());
	fofTrY->Resize(idvec.size());
	fofTrZ->Resize(idvec.size());
	fofTrE->Resize(idvec.size());
	fofTrP->Resize(idvec.size());
	fofTrPx->Resize(idvec.size());
	fofTrPy->Resize(idvec.size());
	fofTrPz->Resize(idvec.size());
	fofTrID->Resize(idvec.size());
    }

    foFADCt->Fill(nbin, fadctime);
    foFADCa->Fill(nbin, fadcvals);

    // Get ADC sum and TDC hits

    double lasthit = -1e9;
    int ntdc = 0;

    for( i = 0; i < nbin; i++ ){
	// Test if we are above the TDC threshold
	// and we are past the last hit to simulate
	// deadtime
	if( fadcvals[i] > fTDC_thresh 
		&& (fadctime[i]-lasthit)>fTDC_deadtime ){
	    foTDC->Fill(fadctime[i], ntdc++);
	    lasthit = fadctime[i];
	}
	// Total sum of energy deposition
	Edepsum += fadcvals[i];
    }

    foADC->Fill(Edepsum);

    delete fadcvals;
    delete fadctime;

    return;
}

void SolidGenericDet::clear(){
    ResetData();
    return;
}

int SolidGenericDet::GetFADCbin(double t){
    if( t < fGate_start || fGate_stop < t ){ return -1; }

    double scale = (t - fGate_start);

    double fbin = scale/fFADC_tRes;

    return (int) floor(fbin);
}


bool SolidGenericDet::FirstHitsAreActive(){
    // If any of the first hit variables are
    // active return true
    if( fofNhit->IsActive() ) return true;
    if( fofTime->IsActive() ) return true;
    if( fofTrX->IsActive() ) return true;
    if( fofTrY->IsActive() ) return true;
    if( fofTrZ->IsActive() ) return true;
    if( fofTrE->IsActive() ) return true;
    if( fofTrP->IsActive() ) return true;
    if( fofTrPx->IsActive() ) return true;
    if( fofTrPy->IsActive() ) return true;
    if( fofTrPz->IsActive() ) return true;
    if( fofTrID->IsActive() ) return true;
    if( fofPname->IsActive() ) return true;

    return false;
}
