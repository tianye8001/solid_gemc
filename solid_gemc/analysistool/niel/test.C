
{
gSystem->Load("niel_fun_cc.so"); 
	
	TNiel niel_proton("niel_proton.txt");
	TNiel niel_electron("niel_electron.txt");
	TNiel niel_pions("niel_pions.txt");
	TNiel niel_neutron("niel_neutron.txt");
	TH1F *hniel_proton=new TH1F("niel_proton","niel_proton",1000,-10,4);
	TH1F *hniel_electron=new TH1F("niel_electron","niel_electron",1000,-10,4);
	TH1F *hniel_pions=new TH1F("niel_pions","niel_pions",1000,-10,4);
	TH1F *hniel_neutron=new TH1F("niel_neutron","niel_neutron",1000,-10,4);

	for(int i=0;i<1000;i++) hniel_proton->SetBinContent(i+1,niel_proton.GetNielFactor(pow(10,(i*(14/1000.)-10))));
	for(int i=0;i<1000;i++) hniel_electron->SetBinContent(i+1,niel_electron.GetNielFactor(pow(10,(i*(14/1000.)-10))));	
	for(int i=0;i<1000;i++) hniel_pions->SetBinContent(i+1,niel_pions.GetNielFactor(pow(10,(i*(14/1000.)-10))));
	for(int i=0;i<1000;i++) hniel_neutron->SetBinContent(i+1,niel_neutron.GetNielFactor(pow(10,(i*(14/1000.)-10))));	

	
	TCanvas *c_niel = new TCanvas("niel","niel",900,900);
	gPad->SetLogy(1);	
	hniel_neutron->SetMinimum(1e-5);
	hniel_neutron->SetMaximum(1e4);	
	hniel_neutron->Draw();		
	hniel_proton->Draw("same");
	hniel_electron->Draw("same");
	hniel_pions->Draw("same");

	
}