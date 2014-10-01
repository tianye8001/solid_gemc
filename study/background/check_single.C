{
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	gStyle->SetPadRightMargin(0.32);

	const int m=2;
	char* input_filename[m]={
		"background_solid_SIDIS_He3_EM_1e8_output.root",
		"background_solid_SIDIS_He3_EM_1e8_output.root"
	};
//	int pid[m]={2,2};
//	char *label[m]={"e (new)","e (old)",};
	int pid[m]={1,2};
	char *label[m]={"g (new)","e (new)"};
	int color[m]={2,4};
	char *hst[m]={"fluxR","fluxR"};
	double min=0,max=1e10;
	const int n=1;
	int hit_id[n]={42};
	char *title[n]={"LASPD"};
	TCanvas *c = new TCanvas("fluxR","fluxR",1000,900);
	///option
	bool Is_R=true,Is_Phi=false;
	bool Is_log=true;


	//======================

	TFile *input[m];
	TH1F *h[n][m];
	for(int i=0;i<m;i++){
		input[i]=new TFile(input_filename[i]);
		if (input[i]->IsZombie()) {
			cout << "Error opening ratefile " << input_filename[i] << endl;
			exit(-1);
		}
		else cout << "open file " << input_filename[i] << endl;

		for(int j=0;j<n;j++){
			char hstname[100];
			sprintf(hstname,"%s_%i_%i",hst[i],hit_id[j],pid[i]);    
			cout << hstname << endl;
			h[j][i]=(TH1F*) input[i]->Get(hstname);
			c->cd(j+1);
			if(Is_log) gPad->SetLogy();
			h[j][i]->SetLineColor(color[i]);
			//h[j][i]->SetLineStyle(i%2*7);  
			h[j][i]->SetLineStyle(1);  
			h[j][i]->SetLineWidth(2);  
			h[j][i]->SetTitle(title[j]);  
			if (i==0) h[j][i]->Draw();
			else h[j][i]->Draw("same");  
		}
	}

	double rate_total[n][m];
	for(int j=0;j<n;j++){
		for(int i=0;i<m;i++){
			int nbins=h[j][i]->GetSize()-2;
			double binwidth=h[j][i]->GetBinWidth(1);
			double sum=0;
			for(int k=1;k<nbins;k++){      
				if (n==1) {
					// 	  if (h[j][i]->GetBinCenter(k) < 110 || 265< h[j][i]->GetBinCenter(k)) continue;	
				}
				else if (n==2) {
					// 	  if (j==0 && (h[j][i]->GetBinCenter(k) < 98 || 230< h[j][i]->GetBinCenter(k))) continue;
					// 	  if (j==1 && (h[j][i]->GetBinCenter(k) < 83 || 140< h[j][i]->GetBinCenter(k))) continue;
					if (j==1 && (h[j][i]->GetBinCenter(k) < 98 || 230< h[j][i]->GetBinCenter(k))) continue;
				}

				if(Is_R) sum += 2*3.1415926*h[j][i]->GetBinCenter(k)*binwidth*100*h[j][i]->GetBinContent(k);
				else if(Is_Phi) sum += binwidth*h[j][i]->GetBinContent(k);
				else {cout << "not sure R or Phi" << endl;}
			}
			rate_total[j][i]=sum;
			cout << sum << endl;
		}  
		}      

		gStyle->SetPaintTextFormat("2.0f");

		for(int j=0;j<n;j++){
			c->cd(j+1);
			TPaveText *pt1 = new TPaveText(0.7,0.99-m*0.05,0.99,0.99,"brNDC");
			pt1->SetFillColor(17);
			pt1->SetTextAlign(12);
			pt1->Draw();
			for(int i=0;i<m;i++){
				char content[500];
				if(Is_R) sprintf(content,"%s \t\t %.2g %s",label[i],rate_total[j][i],"kHz");
				else if(Is_Phi) sprintf(content,"%s \t\t %.2g",label[i],rate_total[j][i]);
				else {cout << "not sure R or Phi" << endl;}
				TText *text1=pt1->AddText(content);
				text1->SetTextColor(color[i]);
				text1->SetTextSize(0.035);
			}
		}
		c->SaveAs(Form("compare_single_%s_%d.png",title[0],hit_id[0]));
		}

