loopit(){
  TFile *_file0 = TFile::Open("noah.root");
  gROOT->ProcessLine(".L noah.C");
  gROOT->ProcessLine("noah t");
  t.Loop();



}
