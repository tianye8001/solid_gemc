// {
//   const int Ntrigline=5;
// 
//   TFile *file_trig_cut[2][Ntrigline][2];//[Det_ID][Cut_ID][PID], Det_DC: 0->FA, 1->LA, PID:
//   
//   TString Trigger_Dir_Rad="SIDIS_He3_201311/cutRadial_innerbackground/";
//   file_trig_cut[0][0][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][0][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][1][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][1][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][2][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][2][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][3][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][3][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][4][0]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",Trigger_Dir_Rad.Data()));
//   file_trig_cut[0][4][1]=new TFile(Form("%s/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root",Trigger_Dir_Rad.Data()));
//   
//   TGraphErrors *gr_trig_cut_ele[2][Ntrigline],*gr_trig_cut_pi[2][Ntrigline];  
//   for (int j=0;j<2;j++){
// 	  for (int i=0;i<Ntrigline;i++){    
// 		  gr_trig_cut_ele[j][i]=(TGraphErrors*) file_trig_cut[j][i][0]->Get("Graph");
// 		  gr_trig_cut_pi[j][i]=(TGraphErrors*) file_trig_cut[j][i][1]->Get("Graph");
// 	  }
//   }
//   
// 	TCanvas *c1 = new TCanvas("TriggerSummary" + phi, "TriggerSummary" + phi,
// 	        1800, 1000);
// 	c1->Divide(2, 1);
// 	int idx = 1;  
// 			
// }

void plot_SIDIS()
{
// 	const char * base =	                "script/Lead2X0PbBlock_Hex.1.PVDIS_Run%s_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_%s_R%.0f_%s.root";
	const char * base =	                "SIDIS_He3_201311/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_Run%s_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig%s%.1f.root";

	static const int n = 5;
// 	double Rs[] =
// 	{
// 	//			247,
// 	        230, 180, 150, 120, 113,
// 
// 	        0 }; //cm
	
	double Rs[n] = {175,140,123,110,105}; //cm

	        
// 	double Trigs[] =
// 	{
// 	//			1.5 ,
// 	        1.5, 2.0, 2.5, 3.5, 3.8,
// 
// 	        0 }; // GeV
	double Trigs[] = {0.9,1.6,2.6,3.5,4.4}; // GeV
	
	double Trigs_value[n] = {1.,2.,3.,4.,5.}; // GeV		

	const char * par[] = {"Electron","Pion"};

// 	const char * suffix[] =
// 	{
// 	//			"TrigSH1.1",
// 	        "TrigSH1.1", "TrigSH1.6", "TrigSH2.0", "TrigSH2.8", "TrigSH3.0",
// 
// 	        NULL };
	const char * suffix[] =	{"","SH","SH","SH","SH"};

	const int markers[] =
	{ 24, 25, 20, 21, 22, 23 };
	const Color_t colors[] =
	//	{ kOrange + 9, kRed, kMagenta, kBlue, kAzure + 3 };
	        {
	        //			kOrange + 9,
	                kRed, kMagenta, kBlue, kAzure + 3, kGreen + 4 };

// 	TCanvas *c1 = new TCanvas("TriggerSummary" + phi, "TriggerSummary" + phi,1800, 1000);
	TCanvas *c1 = new TCanvas("TriggerSummary", "TriggerSummary",1800, 1000);	
	c1->Divide(2, 1);
	int idx = 1;

	const char * Parts[] =
	{ "Electron", "Pion" };
	const double y_offsets[] =
	{ .1, .6 };

	for ( int npart = 0; npart < 2; npart++ )
	{

		const char * Part = Parts[npart];

		c1->cd(idx++);
		c1->Update();

		TH1 * f = gPad -> DrawFrame(0.5, -.1, 6, 1.1);
		f -> SetTitle(Part);
		f -> SetTitle(Part);
		f -> SetXTitle("Momentum (GeV/c)");
		f -> SetYTitle("Trigger Efficiency");

		TLine * l = new TLine(0.5, 0, 6, 0);
		l -> SetLineColor(kBlack);
		l->Draw();

		TLine * l = new TLine(0.5, 1, 6, 1);
		l -> SetLineColor(kBlack);
		l->Draw();

		//		TLine * l = new TLine(2, 0, 2, 1);
		//		l -> SetLineColor(kBlue);
		//		l -> SetLineWidth(2);
		//		l->SetLineStyle(2);
		//		l->Draw();
		//
		//		TLine * l = new TLine(2.5, 0, 2.5, 1);
		//		l -> SetLineColor(kRed);
		//		l -> SetLineWidth(2);
		//		l->SetLineStyle(2);
		//		l->Draw();

		TLegend * leg = new TLegend(.75, .02 + y_offsets[npart], .95,
		        .35 + y_offsets[npart]);

		for ( int i = 0; i < n; i++ )
		{
// 			TString f_name = Form(base, Part, phi.Data(), Rs[i], suffix[i]);
			TString f_name = Form(base,par[npart],suffix[i],Trigs[i]);		  
			cout << "TriggerSummary - Loading " << f_name << endl;

			TFile * file = new TFile(f_name);
			assert(file);

			TGraphErrors * ge = (TGraphErrors *) file->GetObjectChecked(
			        "Graph", "TGraphErrors");
			assert(ge);
// 			ge = (TGraphErrors *) (ge->Clone(Form("Graph_%s_Eklog_R_%s_R%.0f", Part, phi.Data(),Rs[i])));
// 			ge = (TGraphErrors *) (ge->Clone(Form("Graph_%s_Eklog_R_%s_R%.0f", Part, phi.Data(),Rs[i])));			
// 			assert(ge);

			ge->SetLineColor(colors[i]);
			ge->SetMarkerColor(colors[i]);
			ge->SetMarkerStyle(markers[i]);

			ge -> SetLineWidth(2);
			ge -> SetMarkerSize(2);

			ge -> Draw("pl");

// 			leg -> AddEntry(ge,Form("R=%.0f cm, Trig = %.0f GeV", Rs[i], Trigs_value[i]),"lep");
			leg -> AddEntry(ge,Form("Trig = %.0f GeV", Trigs_value[i]),"lep");			
		}
		//
		//		if (npart == 1)
		leg -> Draw();
	}

// 	TString save_name = Form(base, "ALL", phi.Data(), 0, "ALL", "ALL")
// 	        + TString(c1->GetName());
// 	cout << "Save to " << save_name << endl;

// 	SaveCanvas(c1, save_name, kTRUE);
}
  
