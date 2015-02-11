void TriggerSummary(TString phi = "high")
{

	const char
	        * base =
	                "script/Lead2X0PbBlock_Hex.1.PVDIS_Run%s_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_%s_R%.0f_%s.root";

	static const int n = 5;
	double Rs[] =
	{
	//			247,
	        230, 180, 150, 120, 113,

	        0 }; //cm
	double Trigs[] =
	{
	//			1.5 ,
	        1.5, 2.0, 2.5, 3.5, 3.8,

	        0 }; // GeV
	const char * suffix[] =
	{
	//			"TrigSH1.1",
	        "TrigSH1.1", "TrigSH1.6", "TrigSH2.0", "TrigSH2.8", "TrigSH3.0",

	        NULL };

	const int markers[] =
	{ 24, 25, 20, 21, 22, 23 };
	const Color_t colors[] =
	//	{ kOrange + 9, kRed, kMagenta, kBlue, kAzure + 3 };
	        {
	        //			kOrange + 9,
	                kRed, kMagenta, kBlue, kAzure + 3, kGreen + 4 };

	TCanvas *c1 = new TCanvas("TriggerSummary" + phi, "TriggerSummary" + phi,
	        1800, 1000);
	c1->Divide(2, 1);
	int idx = 1;

	const char * Parts[] =
	{ "Electron", "Pion" };
	const double y_offsets[] =
	{ .1, .4 };

	for ( int npart = 0; npart < 2; npart++ )
	{

		const char * Part = Parts[npart];

		c1->cd(idx++);
		c1->Update();

		TH1 * f = gPad -> DrawFrame(1, -.1, 6, 1.1);
		f -> SetTitle(Part);
		f -> SetTitle(Part);
		f -> SetXTitle("Momentum (GeV/c)");
		f -> SetYTitle("Trigger Efficiency");

		TLine * l = new TLine(1, 0, 6, 0);
		l -> SetLineColor(kBlack);
		l->Draw();

		TLine * l = new TLine(1, 1, 6, 1);
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

		TLegend * leg = new TLegend(.43, .15 + y_offsets[npart], .95,
		        .47 + y_offsets[npart]);

		for ( int i = 0; i < n; i++ )
		{
			TString f_name = Form(base, Part, phi.Data(), Rs[i], suffix[i]);
			cout << "TriggerSummary - Loading " << f_name << endl;

			TFile * file = new TFile(f_name);
			assert(file);

			TGraphErrors * ge = (TGraphErrors *) file->GetObjectChecked(
			        "Graph", "TGraphErrors");
			assert(ge);
			ge
			        = (TGraphErrors *) (ge->Clone(
			                Form("Graph_%s_Eklog_R_%s_R%.0f", Part, phi.Data(),
			                        Rs[i])));
			assert(ge);

			ge->SetLineColor(colors[i]);
			ge->SetMarkerColor(colors[i]);
			ge->SetMarkerStyle(markers[i]);

			ge -> SetLineWidth(2);
			ge -> SetMarkerSize(2);

			ge -> Draw("pl");

			leg -> AddEntry(ge,
			        Form("R=%.0f cm, Trig = %.1f GeV", Rs[i], Trigs[i]), "lep");
		}
		//
		//		if (npart == 1)
		leg -> Draw();
	}

	TString save_name = Form(base, "ALL", phi.Data(), 0, "ALL", "ALL")
	        + TString(c1->GetName());
	cout << "Save to " << save_name << endl;

	SaveCanvas(c1, save_name, kTRUE);
}