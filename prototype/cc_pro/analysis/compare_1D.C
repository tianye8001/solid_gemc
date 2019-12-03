{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetOptStat(1111111);
// gStyle->SetPadRightMargin(0.32);

// char input_dir[200]="/work/halla/solid/sim/solid_gemc/PVDIS_LD2_JLAB_VERSION_1.3/pass4";
char input_dir[200]="/work/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3";
// char input_dir[200]="/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass8";

const int m=8;
char* input_filename[m]={

// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_1.957e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_1.871e10_C4F8_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_3.999e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_3.999e10_C4F8_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_5.956e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_5.87e10_C4F8_skim_output.root",

"cc_pro_SIDIS_He3_dirty_weighted_eDIS_N2_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_dirty_weighted_eDIS_C4F8_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_dirty_normalized_pimWiser_N2_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_dirty_normalized_pimWiser_C4F8_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_N2_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_C4F8_filenum100_1e7_output.root",
"cc_pro_SIDIS_He3_BeamOnTarget_2e10_N2_skim_output.root",
"cc_pro_SIDIS_He3_BeamOnTarget_1.871e10_C4F8_skim_output.root",

// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_N2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_N2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_N2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_1.957e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_2e10_N2_skim_output.root",


};
// int pid[m]={5,1,5,1};
// char *label[m]={"HGC NO front win","CF_1","Al_1","CF_10","Al_10","HGCwinNO","HGCwinNO_LGCwinbackNO"};
// char *label[m]={"HGC NO front win","CF_1","CF_5","CF_10","Al_1","Al_5","Al_10"};
// char *label[m]={"HGC winNO","HGC winCF 1%","CF_5","CF_10","HGC winAl 1%","Al_5","Al_10"};
// char *label[m]={"HGC winNO Np.e.>0","HGC winNO Np.e.>1","HGC winCF1% Np.e.>0","HGC winCF1% Np.e.>1","HGC winAl1% Np.e.>0","HGC winAl1% Np.e.>1"};
// char *label[m]={"LGC Np.e.>=1","LGC Np.e.>=2","LGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// char *label[m]={"LGC Np.e.>=1","LGC Np.e.>=2","LGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// char *label[m]={"HGC Np.e.>=1","HGC Np.e.>=2","HGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// char *label[m]={,"eDIS (CO2)","eDIS (C4F8)","pimWiser (CO2)","pimWiser (C4F8)","pi0Wiser (CO2)","pi0Wiser (C4F8)","BeamOnTarget (CO2)","BeamOnTarget (C4F8)"};
char *label[m]={,"eDIS (N2)","eDIS (C4F8)","pimWiser (N2)","pimWiser (C4F8)","pi0Wiser (N2)","pi0Wiser (C4F8)","BeamOnTarget (N2)","BeamOnTarget (C4F8)"};
// int MarkerStyle[m]={20,24,26,21,22,23};
// int MarkerStyle[m]={20,26,20,20,20,20,20,20};
int MarkerStyle[m]={20,24,21,25,22,26,23,32};
// int color[m]={1,1,2,2,3,3};
int color[m]={1,1,2,2,3,3,4,4};
int style[m]={1,2,1,2,1,2,1,2};
// char *hst[m]={"hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc"};
// char *title="hit;PMT;N_{p.e.} rate(kHz) = (event rate * N_{p.e.})";
char *hst[m]={"occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc"};
char *title="occupancy;PMT;event rate(kHz)";

int scale[m]={2,2,2,2,2,2,1,1};  //add both windows to double lumi
// double ymin=1e0,ymax=2e3;
// double ymin=30,ymax=240;
// double ymin=0,ymax=4e4;
// double ymin=1,ymax=4e3;
double ymin=1e-3,ymax=2e4;
// double ymin=1e-3,ymax=1e7;
// double xmin=-380,xmax=-310;
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
// double ymin=1e0,ymax=1e7;
// double xmin=0,xmax=60;
// int hit_id[m]={8,8,8,8};

TCanvas *c = new TCanvas("compare_1D","compare_1D",1200,800);
c->Divide(1,1);
///option
bool Is_R=true,Is_Phi=false;
// bool Is_log=false;
bool Is_log=true;
bool Is_cut=false;

TLegend* leg = new TLegend(0.85, 0.98-0.05*m, 0.98, 0.98);
// TLegend* leg = new TLegend(0.75, 0.98-0.05*3, 0.98, 0.98);
TFile *input[m];
TH1F *h[m];
for(int i=0;i<m;i++){  
//   if (i>5) continue;  
  
  input[i]=new TFile(Form("%s/%s",input_dir,input_filename[i]));
  if (input[i]->IsZombie()) {
    cout << "Error opening file " << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
  char hstname[100];
//   sprintf(hstname,"%s_%i_%i",hst[i],hit_id[i],pid[i]);    
  sprintf(hstname,"%s",hst[i]);      
  cout << hstname << endl;
  h[i]=(TH1F*) input[i]->Get(hstname);

  if (Is_cut) {
    for(int j=0;j<h[i]->GetXaxis()->FindBin(cut[i]);j++)  h[i]->SetBinContent(j+1,0);
  }
  
  if(Is_log) gPad->SetLogy();
//   h[i]->SetLineColor(color[i]);
//   h[i]->SetLineWidth(3);  
//   h[i]->SetLineStyle(style[i]);
   h[i]->Scale(scale[i]);    
  h[i]->SetMinimum(ymin);
  h[i]->SetMaximum(ymax);
//   h[i]->SetAxisRange(xmin,xmax);  
  h[i]->SetTitle(title);  
//   if (i==0) h[i]->Draw("C");
//   else h[i]->Draw("C same");

h[i]->SetMarkerStyle(MarkerStyle[i]);
h[i]->SetMarkerSize(2);
h[i]->SetMarkerColor(color[i]);
h[i]->SetLineColor(color[i]);

  if (i==0) h[i]->Draw("P");
  else h[i]->Draw("P same");

  cout << h[i]->Integral() << endl;  
  //   input.Close(); 
  
  leg->AddEntry(h[i], label[i],"p");  
		
}
leg->Draw();

c->SaveAs("compare_1D.png");

}