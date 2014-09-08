// Driver for GEMC2CaloSim
// Direct to call from root
// Jin Huang <jinhuang@jlab.org>
#include "GEMC2CaloSim.h"
//#include "GEMC2CaloSim.C"

void GEMC2CaloSimScript(void)
{


    GEMC2CaloSim * sel = new GEMC2CaloSim("electron_BaBar.track.dat");
//    GEMC2CaloSim * sel = new GEMC2CaloSim("test.track.dat");


	TFile *_file0 = TFile::Open("electron_BaBar.root");
	assert(_file0);
	if(! _file0->IsOpen()) return;

	TTree *T = (TTree*)gDirectory->Get("fluxT");
	assert(T);

//	T->Process(sel,"",20);
	T->Process(sel);
}
