/*
 SolidOutput

 Output class for solid
 */

#include "SolidOutput.hh"

#include "TFile.h"
#include "TTree.h"

SolidOutput::SolidOutput(){
}

SolidOutput::~SolidOutput(){
}

void SolidOutput::CreateOutputFile(){
    // A test that ROOT is properly working
    // with this installation

    TFile *f = new TFile("output.root", "RECREATE");

    TTree *T = new TTree("T", "SoLID Simluation Output");

    T->SetName("T");

    f->Write("T", TObject::kOverwrite);
    f->Close();
}
