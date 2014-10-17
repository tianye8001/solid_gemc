///use Eklog_R plot and trigger curve to make trigger cut and get trigger rate

void trigger_EC_PVDIS(char *region)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
gStyle->SetPadRightMargin(0.32);  

double Rmin=110,Rmax=265; //in cm, range of EC for trigger
  
//   const int m=16;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_3he_2e8_output.root",
// "background_solid_CLEO_SIDIS_3he_2e8_output.root",
// "background_solid_CLEO_SIDIS_3he_other_eDIS_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_eDIS_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_eES_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_eES_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_pip_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_pim_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_pi0_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Kp_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Km_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Ks_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Ks_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Ks_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_Kl_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_other_p_1e6_output.root",
// "background_solid_CLEO_SIDIS_3he_2e8_output.root"
// };
// int pid[m]={1,2,1,2,1,2,5,6,1,7,8,5,6,9,4,3};
// char *label[m]={"e(EM)","#gamma(EM)","e(DIS)","#gamma(DIS)","e(ES)","#gamma(ES)","#pi^{+}(DIS)","#pi^{-}(DIS)","#gamma(#pi^{0}(DIS))","K^{+}(DIS)","K^{-}(DIS)","#pi^{+}(K^{0}(DIS))","K_{l}(DIS)","p(DIS)","n(EM)"};
// int color[m]={1,2,3,4,5,6,7,8,9,41,32,43,34,45,36,47};

// const int m=3;
// char* input_filename[m]={
// // "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// 
// // "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// 
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.20_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pim_nobaffle_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pip_nobaffle_1e6_output.root",
// 
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.20_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// 
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.20_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.55_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.65_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_nocut_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_output.root",
// 
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.20_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.55_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.65_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_nocut_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// 
// };
// int pid[m]={2,6,5};
// // int pid[m]={2,2,2};
// // char *label[m]={"#gamma(EM)","e(EM)","e(DIS)","#pi^{+}(DIS)","#pi^{-}(DIS)","#gamma(#pi^{0}(DIS))"};
// char *label[m]={"e(DIS)","#pi^{-}(DIS)","#pi^{+}(DIS)"};
// int color[m]={1,2,3};

const int m=5;
char* input_filename[m]={
// "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",

// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.20_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pim_nobaffle_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_nobaffle_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_p_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_real_pi0_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_pip_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",

// "background_solid_PVDIS_LD2_EM_1e8_output.root",
"background_solid_PVDIS_LD2_other_eDIS_1e6_output.root",
"background_solid_PVDIS_LD2_actual_pim_1e6_output.root",
"background_solid_PVDIS_LD2_actual_pip_1e6_output.root",
"background_solid_PVDIS_LD2_actual_pi0_1e6_output.root",
"background_solid_PVDIS_LD2_actual_p_1e6_output.root",
  
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",

// "baffle_babarbaffle/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// // "baffle_babarbaffle/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// "baffle_babarbafflemore/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// // "baffle_babarbafflemore/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// "baffle_babarbafflemore1/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// // "baffle_babarbafflemore1/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// "baffle_smallerZ_cutinner4cm/background_solid_CLEO_PVDIS_LD2_1e6_output.root",
// "baffle_smallerZ_cutinner4cm/background_solid_CLEO_PVDIS_LD2_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_test_pim_1e6_output.root",
// "real/background_solid_CLEO_PVDIS_LD2_test_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_test_p_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",


// "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_test_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_test_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_test_pi0_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_test_pim_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.20_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.55_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_W2x0.65_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_nocut_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_nobaffle_1e6_output.root",

// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.20_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.55_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_W2x0.65_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_nocut_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",

};
int pid[m]={2,6,5,1,4};
// int pid[m]={6,6,5,5,1};
// int pid[m]={2,6,5,6,5};
// int pid[m]={2,2,2};
// char *label[m]={"#gamma(EM)","e(EM)","e(DIS)","#pi^{+}(DIS)","#pi^{-}(DIS)","#gamma(#pi^{0}(DIS))"};
char *label[m]={"e(DIS)","#pi^{-}(DIS)","#pi^{+}(DIS)","#gamma(#pi^{0}(DIS))","p(DIS)"};
// double cal[m]={1,155000*1e6/(50e-6/1.6e-19),155000*1e6/(50e-6/1.6e-19),1,27000*1e6/(50e-6/1.6e-19)};
// double cal[m]={1,140000*1e6/(50e-6/1.6e-19),1,140000*1e6/(50e-6/1.6e-19),1};
// 140000*1e6/(50e-6/1.6e-19),26500*1e6/(50e-6/1.6e-19)};
double cal[m]={1,1,1,1,1};
// double cal[m]={1,140000*1e6/(50e-6/1.6e-19),140000*1e6/(50e-6/1.6e-19),140000*1e6/(50e-6/1.6e-19),26500*1e6/(50e-6/1.6e-19)};
// 155285,155587,156813,27000
// pim     pip    pi0    p   

// char *label[m]={"#gamma(EM) BaBar baffle","#gamma(EM) BaBar baffle More","#gamma(EM) BaBar baffle More1","#gamma(EM) CLEO baffle 4cm","#gamma(EM) CLEO baffle 4cm"};
// int pid[m]={1,1,1,1,1};
// double cal[m]={1,1,1,1,1};

double mass[m]={0.0005,0.1396,0.1396,0.,0.938};
int color[m]={1,2,4,6,30};
  
const int n=1;

TCanvas *c_Eklog_R_ec = new TCanvas("Eklog_R_ec","Eklog_R_ec",1800,n*400);
c_Eklog_R_ec->Divide(m,n);

TCanvas *c_Eklog_R_ec_trig = new TCanvas("Eklog_R_ec_trig","Eklog_R_ec_trig",1800,n*400);
c_Eklog_R_ec_trig->Divide(m,n);

TCanvas *c_fluxR_ec = new TCanvas("fluxR_ec","fluxR_ec",n*900,800);
c_fluxR_ec->Divide(n,1);

TCanvas *c_fluxR_ec_proj = new TCanvas("fluxR_ec_proj","fluxR_ec_proj",n*900,800);
c_fluxR_ec_proj->Divide(n,1);

int region_index;
if (region=="high") region_index=0;
else if (region=="low") region_index=1;
else {cout << "need option for high or low region" << endl; exit(-1);}

TFile *file_trig_cut[2];

//trig file more1
// file_trig_cut[0]=new TFile("../triggerfile/PVDIS_LD2_201309/baffle_babarbafflemore1/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Real_Eklog_R_high_R0_ALL.rootTriggerSummaryhigh.root");
// file_trig_cut[1]=new TFile("../triggerfile/PVDIS_LD2_201309/baffle_babarbafflemore1/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Real_Eklog_R_low_R0_ALL.rootTriggerSummarylow.root");

//trig file more1 block
file_trig_cut[0]=new TFile("../triggerfile/PVDIS_LD2_201309/baffle_babarbafflemore1_block/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_high_R0_ALL.rootTriggerSummaryhigh.root");
file_trig_cut[1]=new TFile("../triggerfile/PVDIS_LD2_201309/baffle_babarbafflemore1_block/Lead2X0PbBlock_Hex.1.PVDIS_RunALL_GetEfficiencies_Full_bgd_BackGround_Sept2013_Block_Real_Eklog_R_low_R0_ALL.rootTriggerSummarylow.root");

char *gr_trig_cut_ele_name[2][5]={
"Graph_Electron_Eklog_R_high_R113",
"Graph_Electron_Eklog_R_high_R120",
"Graph_Electron_Eklog_R_high_R150",
"Graph_Electron_Eklog_R_high_R180",
"Graph_Electron_Eklog_R_high_R230",

"Graph_Electron_Eklog_R_low_R113",
"Graph_Electron_Eklog_R_low_R120",
"Graph_Electron_Eklog_R_low_R150",
"Graph_Electron_Eklog_R_low_R180",
"Graph_Electron_Eklog_R_low_R230"
};
char *gr_trig_cut_pi_name[2][5]={
"Graph_Pion_Eklog_R_high_R113",
"Graph_Pion_Eklog_R_high_R120",
"Graph_Pion_Eklog_R_high_R150",
"Graph_Pion_Eklog_R_high_R180",
"Graph_Pion_Eklog_R_high_R230",

"Graph_Pion_Eklog_R_low_R113",
"Graph_Pion_Eklog_R_low_R120",
"Graph_Pion_Eklog_R_low_R150",
"Graph_Pion_Eklog_R_low_R180",
"Graph_Pion_Eklog_R_low_R230"
};

double trig_cut_range_R[6]={110,116,124,165,205,265}; //113,120,150,180,230

double trig_cut[2][5][26][6];
TGraphErrors *gr_trig_cut_ele[2],*gr_trig_cut_pi[2];
for (int j=0;j<2;j++){
for (int i=0;i<5;i++){  
gr_trig_cut_ele[j]=(TGraphErrors*) file_trig_cut[j]->Get(gr_trig_cut_ele_name[j][i]);
gr_trig_cut_pi[j]=(TGraphErrors*) file_trig_cut[j]->Get(gr_trig_cut_pi_name[j][i]);
trig_cut[j][i][0][0]=trig_cut_range_R[i];
trig_cut[j][i][0][1]=trig_cut_range_R[i+1];
trig_cut[j][i][0][2]=0.5;
trig_cut[j][i][0][3]=1.;
// trig_cut[j][i][0][4]=0.5*gr_trig_cut_ele[j]->GetY()[0];   //Method 1, eff(P<1GeV) = 0.5*eff(P=1GeV)
// trig_cut[j][i][0][5]=0.5*gr_trig_cut_pi[j]->GetY()[0];   //Method 1, eff(P<1GeV) = 0.5*eff(P=1GeV)
trig_cut[j][i][0][4]=0.;        //Method 2, eff(P<1GeV) = 0
trig_cut[j][i][0][5]=0.;        //Method 2, eff(P<1GeV) = 0
cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[0] << "\t" << gr_trig_cut_ele[j]->GetY()[0] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[0] << "\t" << gr_trig_cut_pi[j]->GetY()[0] << endl;
for (int k=0;k<25;k++){
trig_cut[j][i][k+1][0]=trig_cut_range_R[i];
trig_cut[j][i][k+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][k+1][2]=1.+k*0.2;
trig_cut[j][i][k+1][3]=1.+(k+1)*0.2;
trig_cut[j][i][k+1][4]=gr_trig_cut_ele[j]->GetY()[k];
trig_cut[j][i][k+1][5]=gr_trig_cut_pi[j]->GetY()[k];
cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[k] << "\t" << gr_trig_cut_ele[j]->GetY()[k] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[k] << "\t" << gr_trig_cut_pi[j]->GetY()[k] << endl;
}
trig_cut[j][i][25][0]=trig_cut_range_R[i];
trig_cut[j][i][25][1]=trig_cut_range_R[i+1];
trig_cut[j][i][25][2]=6.;
trig_cut[j][i][25][3]=11.;
trig_cut[j][i][25][4]=gr_trig_cut_ele[j]->GetY()[24];
trig_cut[j][i][25][5]=gr_trig_cut_pi[j]->GetY()[24];
cout << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j]->GetX()[24] << "\t" << gr_trig_cut_ele[j]->GetY()[24] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j]->GetX()[24] << "\t" << gr_trig_cut_pi[j]->GetY()[24] << endl;
}
}

  
// double trig_cut[4][10][6]={
// // 110,160,0.5,1.0,0.10,0.10,
// // 110,160,1.0,1.3,0.32,0.15,
// // 110,160,1.3,1.7,0.44,0.18,
// // 110,160,1.7,2.0,0.65,0.22,
// // 110,160,2.0,2.3,0.85,0.27,
// // 110,160,2.3,2.7,0.97,0.34,
// // 110,160,2.7,3.0,1.00,0.35,
// // 110,160,3.0,3.3,1.00,0.38,
// // 110,160,3.3,3.6,1.00,0.42,
// // 110,160,3.6,11.,1.00,0.47,
// 
// 110,160,0.5,1.0,0.10,0.02,
// 110,160,1.0,1.3,0.32,0.07,
// 110,160,1.3,1.7,0.44,0.08,
// 110,160,1.7,2.0,0.65,0.09,
// 110,160,2.0,2.3,0.85,0.13,
// 110,160,2.3,2.7,0.97,0.18,
// 110,160,2.7,3.0,1.00,0.19,
// 110,160,3.0,3.3,1.00,0.23,
// 110,160,3.3,3.6,1.00,0.28,
// 110,160,3.6,11.,1.00,0.31,
// 
// 160,205,0.5,1.0,0.01,0.02,
// 160,205,1.0,1.3,0.12,0.06,
// 160,205,1.3,1.7,0.25,0.10,
// 160,205,1.7,2.0,0.35,0.11,
// 160,205,2.0,2.3,0.62,0.13,
// 160,205,2.3,2.7,0.95,0.22,
// 160,205,2.7,3.0,1.00,0.25,
// 160,205,3.0,3.3,1.00,0.28,
// 160,205,3.3,3.6,1.00,0.32,
// 160,205,3.6,11.,1.00,0.38,
// 
// // 160,205,0.5,1.0,0.10,0.10,
// // 160,205,1.0,1.3,0.30,0.17,
// // 160,205,1.3,1.7,0.55,0.22,
// // 160,205,1.7,2.0,0.83,0.26,
// // 160,205,2.0,2.3,0.98,0.35,
// // 160,205,2.3,2.7,1.00,0.42,
// // 160,205,2.7,3.0,1.00,0.44,
// // 160,205,3.0,3.3,1.00,0.43,
// // 160,205,3.3,3.6,1.00,0.50,
// // 160,205,3.6,11.,1.00,0.52,
// 
// 205,235,0.5,1.0,0.05,0.01,
// 205,235,1.0,1.3,0.15,0.05,
// 205,235,1.3,1.7,0.31,0.08,
// 205,235,1.7,2.0,0.70,0.12,
// 205,235,2.0,2.3,0.98,0.18,
// 205,235,2.3,11.,1.00,0.27,
// 205,235,2.7,3.0,1.00,0.28,
// 205,235,3.0,3.3,1.00,0.33,
// 205,235,3.3,3.6,1.00,0.38,
// 205,235,3.6,11.,1.00,0.42,
// 
// 235,265,0.5,1.0,0.00,0.00,
// 235,265,1.0,1.3,0.00,0.00,
// 235,265,1.3,1.7,0.05,0.01,
// 235,265,1.7,2.0,0.50,0.03,
// 235,265,2.0,2.3,0.96,0.10,
// 235,265,2.3,11.,1.00,0.16,
// 235,265,2.7,3.0,1.00,0.22,
// 235,265,3.0,3.3,1.00,0.26,
// 235,265,3.3,3.6,1.00,0.32,
// 235,265,3.6,11.,1.00,0.35
// };


TH2F *hEklog_R[n][m],*hEklog_R_trig[n][m];
TH1F *hfluxR[n][m];
TH1F *hfluxR_proj[n][m],*hfluxR_trig[n][m];
// for(int i=1;i<4;i++){
for(int i=0;i<m;i++){
  TFile *input=new TFile(input_filename[i]);
  if (input->IsZombie()) {
    cout << "Error opening ratefile" << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
  for(int j=0;j<n;j++){
  char hstname[100];
  
  sprintf(hstname,"fluxR_%i_%i",8+j*4,pid[i]);
  cout << hstname << endl;
  hfluxR[j][i]=(TH1F*) input->Get(hstname); 
  hfluxR[j][i]->Scale(cal[i]);        
  c_fluxR_ec->cd(j+1);
  gPad->SetLogy(1);     
  hfluxR[j][i]->SetLineColor(color[i]);
  hfluxR[j][i]->SetMinimum(1e-7);
  hfluxR[j][i]->SetMaximum(1e2); 
  if (i==0) hfluxR[j][i]->Draw();
  else hfluxR[j][i]->Draw("same");    
  
  char *hstname_Eklog_R[2]={"Eklog_R_high","Eklog_R_low"};
  sprintf(hstname,"%s_%i_%i",hstname_Eklog_R[region_index],8+j*4,pid[i]);  
  cout << hstname << endl;
  hEklog_R[j][i]=(TH2F*) input->Get(hstname);  
  hEklog_R[j][i]->Scale(cal[i]);      
  c_Eklog_R_ec->cd(j*m+i+1);
  gPad->SetLogz(1);
//   hEklog_R[j][i]->SetAxisRange(-2,2,"Y");  
  hEklog_R[j][i]->Draw("colz");
  
  hfluxR_proj[j][i]= (TH1F*) hEklog_R[j][i]->ProjectionX();
//   hfluxR_proj[j][i]->Scale(1/5.);  
//   hfluxR_proj[j][i]->Rebin(5);
  c_fluxR_ec_proj->cd(j+1);
  gPad->SetLogy(1);      
  hfluxR_proj[j][i]->SetLineColor(color[i]);
  hfluxR_proj[j][i]->SetMinimum(1e-7);
  hfluxR_proj[j][i]->SetMaximum(1e2); 
  hfluxR_proj[j][i]->SetTitle(";R (cm);flux (kHz/mm2)");
  if (i==0) hfluxR_proj[j][i]->Draw();
  else hfluxR_proj[j][i]->Draw("same");    

  sprintf(hstname,"%s_trig_%i_%i",hstname_Eklog_R[region_index],j,i);      
  hEklog_R_trig[j][i]=(TH2F*) hEklog_R[j][i]->Clone(hstname);   
  for(int k=1;k<hEklog_R_trig[j][i]->GetNbinsX();k++){
    for(int l=1;l<hEklog_R_trig[j][i]->GetNbinsY();l++){    
      double x=hEklog_R_trig[j][i]->GetXaxis()->GetBinCenter(k);
      double y=hEklog_R_trig[j][i]->GetYaxis()->GetBinCenter(l);      
      double mom=sqrt(pow(10,y)*(pow(10,y)+2*mass[i]));  //from Ek to P
      
      double new_value=0.;
// 	if (pow(10,y) > 2) new_value=hEklog_R_trig[j][i]->GetBinContent(k,l);      
// 	else new_value=0;
//       for(int a=0;a<4;a++){      
// 	 for(int b=0;b<10;b++){
      for(int a=0;a<5;a++){      
	 for(int b=0;b<26;b++){
	    if (trig_cut[region_index][a][b][0] <= x && x < trig_cut[region_index][a][b][1] && trig_cut[region_index][a][b][2] <= mom && mom < trig_cut[region_index][a][b][3]){
	      if(i==0 || i==3) {
		new_value=trig_cut[region_index][a][b][4]*hEklog_R_trig[j][i]->GetBinContent(k,l);		
// 		if (mom>1) new_value=trig_cut[region_index][a][b][4]*hEklog_R_trig[j][i]->GetBinContent(k,l);
// 		else  new_value=(trig_cut[region_index][a][1][4]-(1-mom)*fabs(trig_cut[region_index][a][3][4]-trig_cut[region_index][a][1][4])/0.5)*hEklog_R_trig[j][i]->GetBinContent(k,l);
	      }
	      else if (i==1 || i==2 ) {
		new_value=trig_cut[region_index][a][b][5]*hEklog_R_trig[j][i]->GetBinContent(k,l);		
// 		if(mom>1) new_value=trig_cut[region_index][a][b][5]*hEklog_R_trig[j][i]->GetBinContent(k,l);
// 		else  new_value=(trig_cut[region_index][a][1][5]-(1-mom)*fabs(trig_cut[region_index][a][3][5]-trig_cut[region_index][a][1][5])/0.5)*hEklog_R_trig[j][i]->GetBinContent(k,l);
	      }		
// 	      else if (i==1 || i==2 ) {
// 		if  (mom>2) new_value=trig_cut[region_index][a][b][5]*hEklog_R_trig[j][i]->GetBinContent(k,l);
// 		else new_value=0;
// 	      }
	      else if (i==4) new_value=0.5*trig_cut[region_index][a][b][5]*hEklog_R_trig[j][i]->GetBinContent(k,l);
	      else new_value=0.;
	    }
	    
// 	    double mom=pow(10,y); 
// 	    if (mom>=10e-3) new_value=hEklog_R_trig[j][i]->GetBinContent(k,l);
// 	    else new_value=0;
	 }
      }
      hEklog_R_trig[j][i]->SetBinContent(k,l,new_value);
    }
  }
  
  c_Eklog_R_ec_trig->cd(j*m+i+1);
  gPad->SetLogz(1);
//   hEklog_R_trig[j][i]->SetAxisRange(-2,2,"Y");    
  hEklog_R_trig[j][i]->Draw("colz"); 
  
  hfluxR_trig[j][i]= (TH1F*) hEklog_R_trig[j][i]->ProjectionX();
//   hfluxR_trig[j][i]->Scale(1/5.);  
//   hfluxR_trig[j][i]->Rebin(5);
  c_fluxR_ec_proj->cd(j+1);
  gPad->SetLogy(1);
  hfluxR_trig[j][i]->SetLineStyle(7);  
  hfluxR_trig[j][i]->SetLineColor(color[i]);
  hfluxR_trig[j][i]->SetMinimum(1e-7);
  hfluxR_trig[j][i]->SetMaximum(1e2); 
//   if (i==0) hfluxR_trig[j][i]->Draw();
//   else hfluxR_trig[j][i]->Draw("same");  
//   if (i==0) hfluxR_trig[j][i]->Draw();
//   else if (i==1 || i==2) hfluxR_trig[j][i]->Draw("same");     
  hfluxR_trig[j][i]->Draw("same");
  }
//   input.Close();
}

// c_fluxR_ec->cd(1);
// TPaveText *pt1 = new TPaveText(0.8,0.6,0.95,0.9,"brNDC");
// pt1->SetFillColor(19);
// pt1->SetTextAlign(12);
// pt1->Draw();
// for(int i=0;i<m;i++){
// TText *text=pt1->AddText(label[i]);
// text->SetTextColor(color[i]);
// text->SetTextSize(0.024);


double rate_total[n][m],rate_total_trig[n][m];
double rate_R[n][m][5],rate_R_trig[n][m][5];
for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;     
      int nbins=hfluxR_proj[j][i]->GetNbinsX();
      double binwidth=hfluxR_proj[j][i]->GetBinWidth(1);
//       cout << nbins << " " << binwidth << endl;
      double sum=0,sum_trig=0;
      double sum_R[5]={0,0,0,0,0},sum_R_trig[5]={0,0,0,0,0};
      for(int k=1;k<nbins;k++){
	double r=hfluxR_proj[j][i]->GetBinCenter(k);
	if (r < Rmin || Rmax< r) continue;
// 	if (hfluxR_proj[j][i]->GetBinCenter(k) < 60 || 150< hfluxR_proj[j][i]->GetBinCenter(k)) continue;
	double thisrate=2*3.1415926*hfluxR_proj[j][i]->GetBinCenter(k)*binwidth*100*hfluxR_proj[j][i]->GetBinContent(k);
	double thisrate_trig=2*3.1415926*hfluxR_trig[j][i]->GetBinCenter(k)*binwidth*100*hfluxR_trig[j][i]->GetBinContent(k);
	sum += thisrate;
	sum_trig += thisrate_trig;
	for (int l=0;l<5;l++){
	  if (trig_cut_range_R[l] <= r && r < trig_cut_range_R[l+1]) {
	    sum_R[l] += thisrate;
	    sum_R_trig[l] += thisrate_trig;    
	  }
	}
      }
      ///high and low area only takes half of full azimuthal
      rate_total[j][i]=sum/2.;               
      rate_total_trig[j][i]=sum_trig/2.;     
      for (int l=0;l<5;l++){
	rate_R[j][i][l]= sum_R[l]/2.;
	rate_R_trig[j][i][l]= sum_R_trig[l]/2.;  
      }
   }  
}   

for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
    for (int l=0;l<5;l++){
      cout << Form("%.02e",rate_R[j][i][l]) << "\t";
    }
      cout << endl;
   }  
}

for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
    for (int l=0;l<5;l++){
      cout << Form("%.02e",rate_R_trig[j][i][l]) << "\t";
    }
    cout << endl;
   }  
}

// cout << " overall rate in KHz " << endl;

// gStyle->SetPaintTextFormat("2.1f");

for(int j=0;j<n;j++){
c_fluxR_ec_proj->cd(j+1);
{
TPaveText *pt1 = new TPaveText(0.65,0.99-m*0.05,0.99,0.99,"brNDC");
// TPaveLabel *pt1 = new TPaveLabel(0.7,0.5,0.95,0.95,"a \n b \r sdfhdfghdsfkghdkfghdshgh","brNDC");
pt1->SetFillColor(19);
pt1->SetTextAlign(12);
pt1->Draw();
for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;
char content[500];
sprintf(content,"%s \t\t %.3g %s",label[i],rate_total[j][i],"kHz");
TText *text1=pt1->AddText(content);
text1->SetTextColor(color[i]);
text1->SetTextSize(0.035);
}
}
// c_fluxR_ec_trig->cd(j+1);
{
TPaveText *pt1 = new TPaveText(0.65,0.70-m*0.05,0.99,0.70,"brNDC");
// TPaveLabel *pt1 = new TPaveLabel(0.7,0.5,0.95,0.95,"a \n b \r sdfhdfghdsfkghdkfghdshgh","brNDC");
pt1->SetFillColor(19);
pt1->SetTextAlign(12);
pt1->Draw();
for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;
char content[500];
sprintf(content,"%s \t\t %.3g %s",label[i],rate_total_trig[j][i],"kHz");
TText *text1=pt1->AddText(content);
text1->SetTextColor(color[i]);
text1->SetTextSize(0.035);
}
}

char *pic_name[2][3]={
"Eklog_R_high_ec_lead.png",
"Eklog_R_high_ec_trig_lead.png",
"fluxR_high_ec_lead.png",

"Eklog_R_low_ec_lead.png",
"Eklog_R_low_ec_trig_lead.png",
"fluxR_low_ec_lead.png"
};
// c_Eklog_R_ec->SaveAs(pic_name[region_index][0]);
// c_Eklog_R_ec_trig->SaveAs(pic_name[region_index][1]);
// c_fluxR_ec_proj->SaveAs(pic_name[region_index][2]);

}



/*	

for(int k=8;k<16;k++){
  c_fluxR_ec->cd(k-7);
  gPad->SetLogy(1);  
  for(int l=0;l<m;l++){
//     hfluxR[k][l]->SetMinimum(1e-2);
//     hfluxR[k][l]->SetMaximum(1e2);    
    hfluxR[k][l]->SetLineColor(l+1);
    if (l==0) hfluxR[k][l]->Draw();
    else hfluxR[k][l]->Draw("same");
  }
}

TH1F *hphoton_geant4=(TH1F*) file_geant4->Get("P_large_6_1");
TH1F *hboth_geant4=(TH1F*) file_geant4->Get("P_large_6_3");
TH1F *hneutron_geant4=(TH1F*) file_geant4->Get("P_large_6_3");
double ymin=1e3,ymax=1e7;

TCanvas *c_compare = new TCanvas("compare","compare",1800,500);
c_compare->Divide(3,1);

c_compare->cd(1);
gPad->SetLogy(1);
gPad->SetLogx(1);
hboth_geant4->SetMinimum(ymin);
hboth_geant4->SetMaximum(ymax);
hboth_geant4->SetLineColor(kBlack);
hboth_geant4->Draw();
hall_geant3->SetLineColor(kRed);
hall_geant3->Draw("same");

c_compare->cd(2);
gPad->SetLogy(1);
gPad->SetLogx(1);
hphoton_geant4->SetMinimum(ymin);
hphoton_geant4->SetMaximum(ymax);
hphoton_geant4->SetLineColor(kBlack);
hphoton_geant4->Draw();
hphoton_geant3->SetLineColor(kRed);
hphoton_geant3->Draw("same");

c_compare->cd(3);
gPad->SetLogy(1);
gPad->SetLogx(1);
// helectron_geant4->SetMinimum(ymin);
// helectron_geant4->SetMaximum(ymax);
helectron_geant4->SetLineColor(kBlack);
// helectron_geant4->Scale(0.7);
helectron_geant4->Draw();
helectron_geant3->SetLineColor(kRed);
helectron_geant3->Draw("same");*/

}