{
  gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetPadRightMargin(0.32);

//    UInt_t Number = 3;
//    Double_t Red[Number]    = { 1.00, 0.00, 0.00};
//    Double_t Green[Number]  = { 0.00, 1.00, 0.00};
//    Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
//    Double_t Length[Number] = { 0.00, 0.50, 1.00 };
//    Int_t nb=50;
//    TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
//    f2->SetContour(nb);
   
const int m=3;
char* input_filename[m]={
//   "background_solid_PVDIS_LD2_EM_1e8_output.root",
//   "background_solid_PVDIS_LD2_EM_1e8_output.root",
//   "background_solid_PVDIS_LD2_EM_1e8_output.root",

// "background_solid_PVDIS_LD2_dirty_normalized_pi0_filenum100_1e6_output.root",  
//   "background_solid_PVDIS_LD2_EM_1e8_output.root",
  
"hitxy_3sector/background_solid_PVDIS_LD2_clean_weighted_eDIS_filenum1_1e6_output.root",  
// "tmp/background_solid_PVDIS_LD2_clean_weighted_pim_filenum1_1e6_output.root",
"hitxy_3sector/background_solid_PVDIS_LD2_clean_weighted_pi0_filenum1_1e6_output.root",  
"hitxy_3sector/background_solid_PVDIS_LD2_clean_weighted_pip_filenum1_1e6_output.root",

// "background_solid_PVDIS_LD2_clean_weighted_eDIS_filenum1_1e6_output.root",
// // "background_solid_PVDIS_LD2_clean_weighted_pim_filenum1_1e6_output.root",
// "background_solid_PVDIS_LD2_clean_weighted_pi0_filenum1_1e6_output.root",  
// "background_solid_PVDIS_LD2_clean_weighted_pip_filenum1_1e6_output.root",
  
// "background_solid_PVDIS_LD2_clean_normalized_pim_filenum1_1e6_output.root",
// "background_solid_PVDIS_LD2_clean_normalized_pi0_filenum1_1e6_output.root",
// "background_solid_PVDIS_LD2_clean_normalized_pip_filenum1_1e6_output.root",
};
int pid[m]={2,1,5};
// int pid[m]={6,1,5};
char *label[m]={"1","2","3"};
int color[m]={1,2,3};
// int color[m]={1,1,1};
int style[m]={1,1,1};
// char *hst[m]={"vertexZ","vertexZ","vertexZ","vertexZ"};
// double ymin=1e-4,ymax=1e5;
// double xmin=-380,xmax=-310;
// char *hst[m]={"hitZ","hitZ","hitZ","hitZ"};
// double ymin=1e-4,ymax=1e10;
// double xmin=-500,xmax=500;
char *hst[m]={"hitXY","hitXY","hitXY"};
double ymin=0,ymax=70;
double xmin=50,xmax=300;
// int hit_id[m]={18,18,18};
// int hit_id[m]={22,22,22};
// char *title="Before LGCC";
int hit_id[m]={24,24,24};
// int hit_id[m]={8,8,8};
char *title="After LGCC";
TCanvas *c = new TCanvas("compare_2D_photonblock","compare_2D_photonblock",1000,800);
// c->Divide(2,2);
///option
bool Is_R=true,Is_Phi=false;
// bool Is_log=false;
bool Is_log=true;
bool Is_cut=false;

///======================

TFile *input[m];
TH2F *h[m];
for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;
  input[i]=new TFile(input_filename[i]);
  if (input[i]->IsZombie()) {
    cout << "Error opening ratefile " << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
//   c->cd(i+1);
  
  char hstname[100];
  sprintf(hstname,"%s_%i_%i",hst[i],hit_id[i],pid[i]);    
  cout << hstname << endl;
  h[i]=(TH2F*) input[i]->Get(hstname);

  if (Is_cut) {
    for(int j=0;j<h[i]->GetXaxis()->FindBin(cut[i]);j++)  h[i]->SetBinContent(j+1,0);
  }
  
//   if(Is_log) gPad->SetLogz();
  h[i]->SetMarkerColor(color[i]);
//   h[i]->SetFillColor(color[i]);  
//   h[i]->SetMarkerStyle(3);  
//   h[i]->SetLineStyle(style[i]);
//   h[i]->SetMinimum(ymin);
//   h[i]->SetMaximum(ymax);
  h[i]->SetAxisRange(ymin,ymax,"Y");    
  h[i]->SetAxisRange(xmin,xmax,"X");  
  h[i]->SetTitle(title);
  if (i==0) h[i]->Draw("scat=10");
  else h[i]->Draw("same scat=10");
//   if (i==0) h[i]->Draw("col");
//   else h[i]->Draw("same col");  
  
  cout << h[i]->Integral() << endl;
//     input.Close();   
}

TPaveText *pt1 = new TPaveText(0.85,0.95-m*0.05,0.95,0.95,"brNDC");
// TPaveLabel *pt1 = new TPaveLabel(0.7,0.5,0.95,0.95,"a \n b \r sdfhdfghdsfkghdkfghdshgh","brNDC");
pt1->SetFillColor(kWhite);
pt1->SetTextAlign(12);
// pt1->SetTextSize(2);
pt1->Draw();
char *content[m]={"e^{-}","#gamma(#pi^{0})","#pi^{+}"};
for(int i=0;i<m;i++){
TText *text1=pt1->AddText(content[i]);
text1->SetTextColor(color[i]);
text1->SetTextSize(0.035);
}


// TLegend* leg = new TLegend(0.7, 0.9-0.05*m, 0.9, 0.9);
// for(int i=0;i<m;i++){
//   leg->AddEntry(h[i], label[i],"l");  
// }
// leg->Draw();
   
// TLegend* leg = new TLegend(0.7, 0.7, 0.9, 0.9);
// 
//   TFile *input[m];
// TH1F *h[n][m];
// for(int i=0;i<m;i++){
// //     if(i==3 || i>6) continue;
//   input[i]=new TFile(input_filename[i]);
//   if (input[i]->IsZombie()) {
//     cout << "Error opening ratefile " << input_filename[i] << endl;
//     exit(-1);
//   }
//   else cout << "open file " << input_filename[i] << endl;
//   
//   for(int j=0;j<n;j++){
//     char hstname[100];
// //     sprintf(hstname,"%s_%i_%i",hst,hit_id[j],pid[i]);
//     sprintf(hstname,"%s_%i_%i",hst[i],hit_id[j],pid[i]);    
//   cout << hstname << endl;
//   h[j][i]=(TH1F*) input[i]->Get(hstname);
//   c->cd(j+1);
// //   for(int k=1;k<24;k++) {h[j][i]->SetBinContent(k,0);}
//   if(Is_log) gPad->SetLogy();
//   h[j][i]->SetLineColor(color[i]);
//   h[j][i]->SetLineStyle(style[i]);
//   h[j][i]->SetMinimum(ymin);
//   h[j][i]->SetMaximum(ymax);
//   h[j][i]->SetAxisRange(xmin,xmax);  
//   h[j][i]->SetTitle(title[j]);  
//   if (i==0) h[j][i]->Draw();
//   else h[j][i]->Draw("same");
// 
//   leg->AddEntry(h[j][i], label[i],"l");  
//   }
// //   input.Close();
// } 
//    leg->Draw();

// double rate_total[n][m];
// for(int j=0;j<n;j++){
//    for(int i=0;i<m;i++){
// //     if(i==3 || i>6) continue;     
//       int nbins=h[j][i]->GetSize()-2;
//       double binwidth=h[j][i]->GetBinWidth(1);
// //       cout << nbins << " " << binwidth << endl;
//       double sum=0;
// //       for(int k=1;k<29;k++){     
// //       for(int k=29;k<34;k++){       
// //       for(int k=35;k<54;k++){         
//       for(int k=1;k<nbins;k++){      
// 	if (n==1) {
// // 	  if (h[j][i]->GetBinCenter(k) < 110 || 265< h[j][i]->GetBinCenter(k)) continue;	
// 	}
// 	else if (n==2) {
// // 	  if (j==0 && (h[j][i]->GetBinCenter(k) < 98 || 230< h[j][i]->GetBinCenter(k))) continue;
// // 	  if (j==1 && (h[j][i]->GetBinCenter(k) < 83 || 140< h[j][i]->GetBinCenter(k))) continue;
// 	  if (j==1 && (h[j][i]->GetBinCenter(k) < 98 || 230< h[j][i]->GetBinCenter(k))) continue;
// 	}
// 	
// 	if(Is_R) sum += 2*3.1415926*h[j][i]->GetBinCenter(k)*binwidth*100*h[j][i]->GetBinContent(k);
// // 	if(Is_R) sum += h[j][i]->GetBinContent(k);
// 	else if(Is_Phi) sum += binwidth*h[j][i]->GetBinContent(k);
// 	else {cout << "not sure R or Phi" << endl;}
// // 	cout << h[j][i]->GetBinCenter(k) << " " << h[j][i]->GetBinContent(k) << " " << sum << endl;	
//       }
// //       cout << j << "\t" << label[i] << "\t" << sum << endl;
//       rate_total[j][i]=sum;
// //       rate_total[j][i]=sum/1000.;      
//       cout << sum << endl;
//    }  
// }      
// // cout << " overall rate in KHz " << endl;
// 
// gStyle->SetPaintTextFormat("2.0f");
// 
//    
// for(int j=0;j<n;j++){
// c->cd(j+1);
// TPaveText *pt1 = new TPaveText(0.7,0.99-m*0.05,0.99,0.99,"brNDC");
// // TPaveLabel *pt1 = new TPaveLabel(0.7,0.5,0.95,0.95,"a \n b \r sdfhdfghdsfkghdkfghdshgh","brNDC");
// pt1->SetFillColor(17);
// pt1->SetTextAlign(12);
// pt1->Draw();
// for(int i=0;i<m;i++){
// //     if(i==3 || i>6) continue;
// char content[500];
// if(Is_R) sprintf(content,"%s \t\t %.2g %s",label[i],rate_total[j][i],"kHz");
// else if(Is_Phi) sprintf(content,"%s \t\t %.2g",label[i],rate_total[j][i]);
// else {cout << "not sure R or Phi" << endl;}
// TText *text1=pt1->AddText(content);
// text1->SetTextColor(color[i]);
// text1->SetTextSize(0.035);
// }
// }

c->SaveAs("compare_2D.png");

}

/*

for(int k=8;k<16;k++){
  c->cd(k-7);
  gPad->SetLogy(1);  
  for(int l=0;l<m;l++){
//     h[k][l]->SetMinimum(1e-2);
//     h[k][l]->SetMaximum(1e2);    
    h[k][l]->SetLineColor(l+1);
    if (l==0) h[k][l]->Draw();
    else h[k][l]->Draw("same");
  }
}

TH1F *hphoton_geant4=(TH1F*) file_geant4->Get("P_large_6_1");
TH1F *hboth_geant4=(TH1F*) file_geant4->Get("P_large_6_3");
TH1F *hneutron_geant4=(TH1F*) file_geant4->Get("P_large_6_3");
double yymin=1e3,yymax=1e7;

TCanvas *c_compare = new TCanvas("compare","compare",1800,500);
c_compare->Divide(3,1);

c_compare->cd(1);
gPad->SetLogy(1);
gPad->SetLogx(1);
hboth_geant4->SetMinimum(yymin);
hboth_geant4->SetMaximum(yymax);
hboth_geant4->SetLineColor(kBlack);
hboth_geant4->Draw();
hall_geant3->SetLineColor(kRed);
hall_geant3->Draw("same");

c_compare->cd(2);
gPad->SetLogy(1);
gPad->SetLogx(1);
hphoton_geant4->SetMinimum(yymin);
hphoton_geant4->SetMaximum(yymax);
hphoton_geant4->SetLineColor(kBlack);
hphoton_geant4->Draw();
hphoton_geant3->SetLineColor(kRed);
hphoton_geant3->Draw("same");

c_compare->cd(3);
gPad->SetLogy(1);
gPad->SetLogx(1);
// helectron_geant4->SetMinimum(yymin);
// helectron_geant4->SetMaximum(yymax);
helectron_geant4->SetLineColor(kBlack);
// helectron_geant4->Scale(0.7);
helectron_geant4->Draw();
helectron_geant3->SetLineColor(kRed);
helectron_geant3->Draw("same");*/

