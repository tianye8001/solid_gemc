{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetOptStat(1111111);
gStyle->SetPadRightMargin(0.32);

// char input_dir[200]="/volatile/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3/withoutEC";
// char input_dir[200]="/volatile/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3/pass1";

// const int m=8;
// char* input_filename[m]={
// 
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1.957e10_CO2_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1.871e10_C4F8_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_3.999e10_CO2_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_3.999e10_C4F8_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_5.956e10_CO2_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_5.87e10_C4F8_skim_output.root",
// 
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_C4F8_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_2e10_N2_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1.871e10_C4F8_skim_output.root",
// 
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_weighted_eDIS_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_CO2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_N2_filenum100_1e7_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1.957e10_CO2_skim_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_2e10_N2_skim_output.root",
// 
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// // "cc_pro_SIDIS_He3_BeamOnTarget_1e10_skim_CO2_output.root",
// 
// "cc_pro_SIDIS_He3_CO2_BeamOnTarget_1.957e10_skim_output.root",
// // "cc_pro_SIDIS_He3_N2_BeamOnTarget_2e10_skim_output.root",
// 
// "cc_pro_SIDIS_He3_BeamOnTarget_1e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_CO2_dirty_normalized_pi0Wiser_filenum100_1e6_skim_output.root",
// "cc_pro_SIDIS_He3_CO2_dirty_weighted_eDIS_filenum100_1e6_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2_dirty_normalized_pi0Wiser_filenum100_1e6_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2_dirty_weighted_eDIS_filenum100_1e6_skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2_dirty_normalized_pi0Wiser_filenum100_1e6_skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2_dirty_weighted_eDIS_filenum100_1e6_skim_output.root",
// 
// };
// // int pid[m]={5,1,5,1};
// // char *label[m]={"HGC NO front win","CF_1","Al_1","CF_10","Al_10","HGCwinNO","HGCwinNO_LGCwinbackNO"};
// // char *label[m]={"HGC NO front win","CF_1","CF_5","CF_10","Al_1","Al_5","Al_10"};
// // char *label[m]={"HGC winNO","HGC winCF 1%","CF_5","CF_10","HGC winAl 1%","Al_5","Al_10"};
// // char *label[m]={"HGC winNO Np.e.>0","HGC winNO Np.e.>1","HGC winCF1% Np.e.>0","HGC winCF1% Np.e.>1","HGC winAl1% Np.e.>0","HGC winAl1% Np.e.>1"};
// // char *label[m]={"LGC Np.e.>=1","LGC Np.e.>=2","LGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// // char *label[m]={"LGC Np.e.>=1","LGC Np.e.>=2","LGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// // char *label[m]={"HGC Np.e.>=1","HGC Np.e.>=2","HGC Np.e.>=2 & 2X2","CF_10","HGC winAl 1%","Al_5"};
// // char *label[m]={,"eDIS (CO2)","eDIS (C4F8)","pimWiser (CO2)","pimWiser (C4F8)","pi0Wiser (CO2)","pi0Wiser (C4F8)","BeamOnTarget (CO2)","BeamOnTarget (C4F8)"};
// char *label[m]={,"eDIS (N2)","eDIS (C4F8)","pimWiser (N2)","pimWiser (C4F8)","pi0Wiser (N2)","pi0Wiser (C4F8)","BeamOnTarget (N2)","BeamOnTarget (C4F8)"};
// // int MarkerStyle[m]={20,24,26,21,22,23};
// // int MarkerStyle[m]={20,26,20,20,20,20,20,20};
// int MarkerStyle[m]={20,24,21,25,22,26,23,32};
// // int color[m]={1,1,2,2,3,3};
// int color[m]={1,1,2,2,3,3,4,4};
// int style[m]={1,2,1,2,1,2,1,2};
// char *hst[m]={"hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc"};
// char *title="hit;PMT;N_{p.e.} rate(kHz) = (event rate * N_{p.e.})";
// // char *hst[m]={"occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc"};
// // char *title="occupancy;PMT;event rate(kHz)";
// 
// int scale[m]={2,2,2,2,2,2,1,1};  //add both windows to double lumi
// // double ymin=1e0,ymax=2e3;
// // double ymin=30,ymax=240;
// // double ymin=0,ymax=4e4;
// // double ymin=1,ymax=4e3;
// // double ymin=1e-3,ymax=2e4;
// double ymin=1e-3,ymax=1e7;
// // double xmin=-380,xmax=-310;
// // char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
// // double ymin=1e0,ymax=1e7;
// // double xmin=0,xmax=60;
// // int hit_id[m]={8,8,8,8};

// // pass1
// char input_dir[200]="/volatile/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3/pass1";
// const int m=19;
// char* input_filename[m]={
// "cc_pro_SIDIS_He3_Beup_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9.skim_output.root",
// "cc_pro_SIDIS_He3_Alup_CO2LA_dirty_normalized_pi0Wiser_filenum99_0.99e9.skim_output.root",
// "cc_pro_SIDIS_He3_N2up_CO2LA_dirty_normalized_pi0Wiser_filenum97_0.97e9.skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_CO2LA_dirty_normalized_pi0Wiser_filenum99_0.99e9_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2down_CO2LA_dirty_normalized_pi0Wiser_filenum73_0.73e9.skim_output.root",
// "cc_pro_SIDIS_He3_Aldown_CO2LA_dirty_normalized_pi0Wiser_filenum218_2.18e9.skim_output.root",
// "cc_pro_SIDIS_He3_Bedown_CO2LA_dirty_normalized_pi0Wiser_filenum97_0.97e9.skim_output.root",
// 
// "cc_pro_SIDIS_He3_Beup_CO2LA_dirty_weighted_eDIS_filenum61_0.61e9_skim_output.root",
// "cc_pro_SIDIS_He3_Alup_CO2LA_dirty_weighted_eDIS_filenum97_0.97e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2up_CO2LA_dirty_weighted_eDIS_filenum56_0.56e9_skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2down_CO2LA_dirty_weighted_eDIS_filenum98_0.98e9_skim_output.root",
// "cc_pro_SIDIS_He3_Aldown_CO2LA_dirty_weighted_eDIS_filenum99_0.99e9_skim_output.root",
// "cc_pro_SIDIS_He3_Bedown_CO2LA_dirty_weighted_eDIS_filenum63_0.63e9_skim_output.root",
// 
// "cc_pro_SIDIS_He3_CO2LA_BeamOnTarget_14.291e10_skim_output.root",
// };
// // char *label[m]={,"eDIS (CO2)","eDIS (C4F8)","pimWiser (CO2)","pimWiser (C4F8)","pi0Wiser (CO2)","pi0Wiser (C4F8)","BeamOnTarget (CO2)","BeamOnTarget (C4F8)"};
// char *label[m]={"eDIS (Be up)","eDIS (Al up)","eDIS (N2 up)","eDIS (win up)","eDIS (He3)","eDIS (win down)","eDIS (N2 down)","eDIS (Al down)","eDIS (Be down)","pi0Wiser (Be up)","pi0Wiser (Al up)","pi0Wiser (N2 up)","pi0Wiser (win up)","pi0Wiser (He3)","pi0Wiser (win down)","pi0Wiser (N2 down)","pi0Wiser (Al down)","pi0Wiser (Be down)","BeamOnTarget"};
// int MarkerStyle[m]={24,24,24,24,24,24,24,24,24,26,26,26,26,26,26,26,26,26,20};
// int color[m]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1};
// int style[m]={1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1};
// char *hst[m]={"occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc","occ_hgc"};
// // char *hst[m]={"hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc","hit_hgc"};
// double ymin=1e-4,ymax=1e3;
// // char *hst[m]={"pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc","pe_hgc"};
// // char *hst[m]={"npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc"};
// // double ymin=1,ymax=1e6;
// // char *hst[m]={"hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0"};
// // double ymin=1e-10,ymax=1e6;

// pass2
// char input_dir[200]="/volatile/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3/pass2";
// const int m=22;
// char* input_filename[m]={
// "cc_pro_SIDIS_He3_Beup_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Alup_CO2LA_dirty_weighted_eDIS_filenum98_0.98e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2up_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2down_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Aldown_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Bedown_CO2LA_dirty_weighted_eDIS_filenum100_1e9_skim_output.root",
// "cc_pro_C_CO2LA_dirty_weighted_eDIS_filenum96_0.96e9_skim_output.root",
// "cc_pro_C_N2_CO2LA_dirty_weighted_eDIS_filenum92_0.92e9_skim_output.root",
// 
// "cc_pro_SIDIS_He3_Beup_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Alup_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2up_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_winup_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_windown_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_N2down_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Aldown_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_SIDIS_He3_Bedown_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// "cc_pro_C_CO2LA_dirty_normalized_pi0Wiser_filenum119_1.19e9_skim_output.root",
// "cc_pro_C_N2_CO2LA_dirty_normalized_pi0Wiser_filenum100_1e9_skim_output.root",
// 
// };
// // char *label[m]={,"eDIS (CO2)","eDIS (C4F8)","pimWiser (CO2)","pimWiser (C4F8)","pi0Wiser (CO2)","pi0Wiser (C4F8)","BeamOnTarget (CO2)","BeamOnTarget (C4F8)"};
// char *label[m]={"eDIS (Be up)","eDIS (Al up)","eDIS (N2 up)","eDIS (win up)","eDIS (He3)","eDIS (win down)","eDIS (N2 down)","eDIS (Al down)","eDIS (Be down)","eDIS (C)","eDIS (C_N2)","pi0Wiser (Be up)","pi0Wiser (Al up)","pi0Wiser (N2 up)","pi0Wiser (win up)","pi0Wiser (He3)","pi0Wiser (win down)","pi0Wiser (N2 down)","pi0Wiser (Al down)","pi0Wiser (Be down)","pi0Wiser (C)","pi0Wiser (C_N2)"};
// int MarkerStyle[m]={24,24,24,24,24,24,24,24,24,24,24,26,26,26,26,26,26,26,26,26,26,26};
// int color[m]={1,2,3,4,5,6,7,8,9,11,12,1,2,3,4,5,6,7,8,9,11,12};
// int style[m]={1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2};
// // char *hst[m]={"occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3","occ_hgc_3"};
// // char *hst[m]={"hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3","hit_hgc_3"};
// // double ymin=1e-5,ymax=1e3;
// char *hst[m]={"pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3","pe_hgc_3"};
// // char *hst[m]={"npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc","npe_hgc"};
// double ymin=1,ymax=1e6;
// // char *hst[m]={"hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0","hit_E_0"};
// // double ymin=1e-6,ymax=1e6;
// char *title="TCD with CO2 at Large Angle";

char input_dir[200]="/volatile/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3/pass2";
const int m=2;
char* input_filename[m]={
"cc_pro_SIDIS_He3_CO2LA_even_e_central_1e3_output.root",
"cc_pro_SIDIS_He3_CO2LA_even_e_broad_1e5_output.root",
};
char *label[m]={"even e central","even e broad"};
int MarkerStyle[m]={24,26};
int color[m]={1,1};
int style[m]={1,1};
char *hst[m]={"pe_hgc_0","pe_hgc_0"};
// char *hst[m]={"npe_hgc","npe_hgc"};
double ymin=1,ymax=4e4;
double xmin=1,xmax=100;
char *title="TCD with CO2 at Large Angle";

TCanvas *c = new TCanvas("compare_1D","compare_1D",1200,800);
c->Divide(1,1);
///option
bool Is_R=true,Is_Phi=false;
// bool Is_logy=false;
bool Is_logy=true;
bool Is_logx=false;
// bool Is_logx=true;
bool Is_cut=false;

TLegend* leg = new TLegend(0.70, 0.98-0.04*m, 0.98, 0.98);
// TLegend* leg = new TLegend(0.75, 0.98-0.05*3, 0.98, 0.98);
TFile *input[m];
TH1F *h[m];

double total1=0,total2=0;
for(int i=0;i<m;i++){  
//   if (i!=4) continue;  
  
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
  
  if(Is_logy) gPad->SetLogy();
  if(Is_logx) gPad->SetLogx();  
//   h[i]->SetLineColor(color[i]);
//   h[i]->SetLineWidth(3);  
//   h[i]->SetLineStyle(style[i]);
//    h[i]->Scale(scale[i]);    
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

//   if (i==0) h[i]->Draw();
//   else h[i]->Draw("same");

// h[i]->Draw();

  double a=h[i]->Integral();
  if (i== 0 || i== 1 ||   i== 7|| i== 8|| i== 11|| i== 12||   i== 18|| i== 19) {total1 += a;total2 += a;}
  if (i== 2|| i== 3 || i== 4 || i== 5||i== 6||i== 13|| i== 14|| i== 15|| i== 16 ||i== 17) total1 +=a;
  if (i== 9 || i== 10 || i== 20|| i== 21)   total2 +=a;
  
  cout << "GetEntries " << h[i]->GetEntries() << " Integral " << h[i]->Integral() << endl;  
  //   input.Close(); 
  
  leg->AddEntry(h[i], label[i],"p");  
		
}
leg->Draw();

cout << "total1 avg " << total1/16 <<  endl;
cout << "total2 avg " << total2/16 <<  endl;

c->SaveAs("compare_1D.png");

}