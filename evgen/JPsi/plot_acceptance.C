void plot_acceptance()
{
    gStyle->SetOptStat(0);
TFile *file1 = new TFile("accep.root");
TH2F *hf1 = (TH2F*)file1->Get("h2");
TH2F *hl1 = (TH2F*)file1->Get("h3"); 

TFile *file2 = new TFile("/home/zwzhao/solid/solid_svn/solid/solid_gemc/analysistool/acceptance/CLEO_JPsi_test/acceptance_solid_CLEO_JPsi_negative_target360_output.root");    
TH2F *hf2 = (TH2F*)file2->Get("acceptance_forwardangle");
TH2F *hl2 = (TH2F*)file2->Get("acceptance_largeangle");
    
TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1400,800);
c_acceptance->Divide(2,2);
c_acceptance->cd(1);
hf1->SetNameTitle("hf1","geant3 acceptance at forwardangle;theta (degree);P (GeV)");
hf1->Draw("colz");
c_acceptance->cd(2);
hl1->SetNameTitle("hl1","geant3 acceptance at largeangle;theta (degree);P (GeV)");
hl1->Draw("colz");
c_acceptance->cd(3);
hf2->SetNameTitle("hf2","geant4 acceptance at forwardangle;theta (degree);P (GeV)");
hf2->SetAxisRange(0,30,"X");
hf2->SetAxisRange(0,8,"Y");
hf2->Draw("colz");
c_acceptance->cd(4);
hl2->SetNameTitle("hl2","geant4 acceptance at largeangle;theta (degree);P (GeV)");
hl2->SetAxisRange(0,30,"X");
hl2->SetAxisRange(0,8,"Y");
hl2->Draw("colz");

TCanvas *c_acceptance_theta = new TCanvas("acceptance_theta","acceptance_theta",1400,800);
c_acceptance_theta->Divide(2,2);
c_acceptance_theta->cd(1);
hf1->ProjectionX();
hf1_px->Draw();
c_acceptance_theta->cd(2);
hl1->ProjectionX();
hl1_px->Draw();
c_acceptance_theta->cd(3);
hf2->ProjectionX();
hf2_px->Draw();
// hf2->SetAxisRange(0,30,"X");
// hf2->SetAxisRange(0,8,"Y");
c_acceptance_theta->cd(4);
// hl2->SetAxisRange(0,30,"X");
// hl2->SetAxisRange(0,8,"Y");
hl2->ProjectionX();
hl2_px->Draw();

}