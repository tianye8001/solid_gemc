{
  gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetPadRightMargin(0.32);

// const int m=15;
// char* input_filename[m]={
// // "background_solid_CLEO_SIDIS_He3_2e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_2e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_eES_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_pip_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_pim_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_pip_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Kp_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Km_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Ks_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Ks_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Ks_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_Kl_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_p_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_2e8_output.root"
// "background_solid_CLEO_JPsi_LH2_1e8_output.root",
// "background_solid_CLEO_JPsi_LH2_1e8_output.root",
// "background_solid_CLEO_JPsi_LH2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_eES_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_pip_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_pim_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_pip_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Kp_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Km_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Ks_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Ks_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Ks_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_Kl_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_other_p_1e6_output.root",
// "background_solid_CLEO_JPsi_LH2_1e8_output.root"
// };
// int pid[m]={1,2,2,2,5,6,1,7,8,5,6,1,9,4,3};
// char *label[m]={"#gamma(EM)","e(EM)","e(DIS)","e(ES)","#pi^{+}(DIS)","#pi^{-}(DIS)","#gamma(#pi^{0}(DIS))","K^{+}(DIS)","K^{-}(DIS)","#pi^{+}(K^{0}(DIS))","#pi^{-}(K^{0}(DIS))","#gamma(K^{0}(DIS))","K_{l}(DIS)","p(DIS)","neutron"};
// int color[m]={1,2,3,4,5,6,7,8,9,42,32,43,34,45,36};
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR"};
// double min=1e-8,max=1e2;    
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e5;
// ///EC R
// const int n=2;
// int hit_id[n]={8,12};
// char *title[n]={"EC forward angle","EC large angle"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",2000,800);
// c->Divide(n,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=7;
// char* input_filename[m]={
// "../baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// "../baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "../baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_1e7_cutinner2cm_output.root",
// // "background_solid_CLEO_PVDIS_1e6_cutinner4cm_openbeamline_output.root",
// "background_solid_CLEO_PVDIS_1e6_cutinner4cm_output.root",
// "background_solid_CLEO_PVDIS_1e6_cutinner5cm_output.root",
// "background_solid_CLEO_PVDIS_1e6_cutinner5cmcut_output.root",
// "background_solid_CLEO_PVDIS_1e6_cutinner6cm_output.root",
// "background_solid_CLEO_PVDIS_1e6_cutinner6cmcut_output.root",
// // "old/background_solid_CLEO_PVDIS_1e7_cutinner4cm_output.root",
// // "background_solid_CLEO_PVDIS_1e7_cutinner5cm_output.root",
// // "background_solid_CLEO_PVDIS_1e7_cutinner5cm_output.root",
// // "old/background_solid_CLEO_PVDIS_1e7_cutinner6cm_output.root",
// // "background_solid_CLEO_PVDIS_1e7_cutinner6cm_output.root"
// };
// // int pid[m]={1,1,1,1,1,1,1};
// int pid[m]={5,5,5,5,5,5,5};
// // char *label[m]={"#gamma(EM) 2cm old","#gamma(EM) 4cm old","#gamma(EM) 4cm","#gamma(EM) 5cm","#gamma(EM) 6cm"};
// char *label[m]={"#gamma(EM) 2cm old","#gamma(EM) 4cm old","#gamma(EM) 4cm","#gamma(EM) 5cm","#gamma(EM) 5cmcut","#gamma(EM) 6cm","#gamma(EM) 6cmcut"};
// int color[m]={1,2,3,4,5,6,7};
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e1,max=1e7;    
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR"};
// double min=1e-2,max=1e5;  
// // char *hst[m]={"Eklog","Eklog","Eklog","Eklog","Eklog","Eklog","Eklog"};
// // double min=1e4,max=1e9;  
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e5;
// ///EC R
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC forward angle"};
// // int hit_id[n]={18};
// // char *title[n]={"LGCC"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(n,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=15;
// char* input_filename[m]={
// "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_eES_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pim_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_pip_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Kp_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Km_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Ks_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Ks_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Ks_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_Kl_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_other_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_2e8_output.root"
// "background_solid_CLEO_PVDIS_LD2_1e8_output.root"
// };
// int pid[m]={1,2,2,2,5,6,1,7,8,5,6,1,9,4,3};
// // int pid[m]={1,2,1,2,1,2,1,2,8,5,6,1,9,4,3};
// char *label[m]={"#gamma(EM)","e(EM)","e(DIS)","e(ES)","#pi^{+}(DIS)","#pi^{-}(DIS)","#gamma(#pi^{0}(DIS))","K^{+}(DIS)","K^{-}(DIS)","#pi^{+}(K^{0}(DIS))","#pi^{-}(K^{0}(DIS))","#gamma(K^{0}(DIS))","K_{l}(DIS)","p(DIS)","neutron"};
// int color[m]={1,2,3,4,5,6,7,8,9,42,32,43,34,45,36};
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR"};
// double min=1e-8,max=1e3;    
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e6;
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC forward angle"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(n,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=2;
// char* input_filename[m]={
// "baffle_babarbafflemore1/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_babarbafflemore1_block/background_solid_CLEO_PVDIS_LD2_1e8_output.root"
// };
// int pid[m]={1,1};
// char *label[m]={"#gamma(EM) baffle more1","#gamma(EM) baffle more1 block"};
// int color[m]={1,2};
// char *hst[m]={"fluxR","fluxR"};
// double min=1e-8,max=1e3;    
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e6;
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC forward angle"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(n,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=10;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",  
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_real_p_1e6_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_1e8_output.root"
// };
// int pid[m]={1,2,3,4,5,6,7,8,9,10};
// char *label[m]={"#gamma","e","n","p","pi+","pi-","K+","K-","Kl","other"};
// int color[m]={1,2,3,4,5,6,7,8,9,31};
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR","fluxR"};
// double min=1e-8,max=1e3;
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e6;
// // const int n=1;
// // int hit_id[n]={8};
// // char *title[n]={"EC forward angle"};
// // TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// // const int n=2;
// // int hit_id[n]={8,12};
// // char *title[n]={"EC forward angle","EC large angle"};
// // TCanvas *c = new TCanvas("compare_1D","compare_1D",1900,800);
// const int n=2;
// int hit_id[n]={16,17};
// char *title[n]={"MRPC front","MRPC within"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1900,800);
// c->Divide(n,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=2;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_other_pim_notargetcollimator_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_pim_1e6_output.root"
// };
// int pid[m]={1,1};
// char *label[m]={"pim with target collimator","pim  with target collimator"};
// int color[m]={1,2};
// char *hst[m]={"vertexZ","vertexZ"};
// double min=1e-8,max=1e3;    
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e6;
// const int n=2;
// int hit_id[n]={8,12};
// char *title[n]={"EC forward angle","EC large angle"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(1,n);
// ///option
// bool Is_R=true,Is_Phi=false;
// bool Is_log=false;
// // bool Is_log=true;

// const int m=2;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root"
// // "background_solid_CLEO_SIDIS_He3_actual_pip_1e6_output.root"
// // "background_solid_CLEO_SIDIS_He3_notargetcollimator_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_notargetcollimator_1e8_output.root"
// // "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_1e8_output.root"
// };
// int pid[m]={1,2};
// char *label[m]={"EM photon","EM electron"};
// int color[m]={1,2};
// char *hst[m]={"fluxR","fluxR"};
// double min=1e-8,max=1e3;    
// // char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR","EfluxR"};
// // double min=1e-4,max=1e6;
// const int n=2;
// int hit_id[n]={16,8};
// char *title[n]={"before MRPC","after MRPC"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(1,n);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=2;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_notargetcollimator_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root"
// };
// int pid[m]={1,1};
// char *label[m]={"e+#gamma(EM), nobaffle","e+#gamma(EM), baffle"};
// int color[m]={1,2};
// char *hst[m]={"fluxR","fluxR"};
// double min=1e-4,max=1e6;
// const int n=2;
// int hit_id[n]={8,12};
// char *title[n]={"FAEC","LAEC"};
// TCanvas *c = new TCanvas("fluxR","fluxR",1600,900);
// c->Divide(2,n/2);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=5;
// char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root"
// };
// int pid[m]={1,2,5,6,4};
// char *label[m]={"gamma","e","pip","pim","p"};
// int color[m]={1,2,3,4,5};
// char *hst[m]={"EdepR","EdepR","EdepR","EdepR","EdepR"};
// double min=0,max=1e10;
// const int n=2;
// int hit_id[n]={8,12};
// char *title[n]={"FAEC","LAEC"};
// TCanvas *c = new TCanvas("EdepR","EdepR",1600,900);
// c->Divide(2,n/2);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=4;
// char* input_filename[m]={
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "baffle_babarbafflemore1_block/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "baffle_babarbafflemore1_block/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_notargetcollimator_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_notargetcollimator_1e8_output.root",
// // "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// };
// int pid[m]={1,1,2,2};
// char *label[m]={"gamma","gamma","e","e",};
// int color[m]={1,1,2,2};
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
// double min=0,max=1e10;
// // const int n=2;
// // int hit_id[n]={8,12};
// // char *title[n]={"FAEC","LAEC"};
// // TCanvas *c = new TCanvas("fluxR","fluxR",1600,900);
// // c->Divide(2,n/2);
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"FAEC"};
// TCanvas *c = new TCanvas("fluxR","fluxR",1000,900);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=4;
// char* input_filename[m]={
// // "background_solid_CLEO_PVDIS_LD2_nobaffle_noshieldbeamline_2e8_output.root",
// // "background_solid_CLEO_PVDIS_LD2_nobaffle_noshieldbeamline_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_noshieldbeamline_2e8_output.root",
// // "baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_noshieldbeamline_2e8_output.root",
// // "baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// };
// int pid[m]={1,2,1,2};
// // int pid[m]={1,1,1,1};
// char *label[m]={
//   "#gamma(EM) nobaffle","e(EM) nobaffle","#gamma(EM) baffle","e(EM) baffle"
// };
// int color[m]={1,2,3,4};
// ///EC R
// // char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
// // double min=1e-1,max=1e3;  
// char *hst[m]={"EfluxR","EfluxR","EfluxR","EfluxR"};
// double min=1e2,max=2e6;  
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1300,800);
// c->Divide(1,1);
// ///gem R
// // char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
// // double min=1e-2,max=7e1;
// // const int n=4;
// // int hit_id[n]={0,1,2,3};
// // char *title[n]={"gem 1","gem 2","gem 3","gem 4"};
// // TCanvas *c = new TCanvas("compare_1D","compare_1D",1300,800);
// // c->Divide(2,2);
// ///option
// bool Is_R=false,Is_Phi=true;
// // bool Is_log=false;
// bool Is_log=true;

// const int m=13;
// char* input_filename[m]={
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// // "baffle_smallerZ/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root",
// // "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_2e8_output.root"
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",
// "baffle_smallerZ_cutinner/background_solid_CLEO_PVDIS_LD2_1e8_output.root",  
// };
// int pid[m]={2,1,1,1,2,2,2,1,1,1,2,2,2};
// char *label[m]={"e(DIS)","#gamma(EM) nobaffle total","#gamma(EM) nobaffle target","#gamma(EM) nobaffle other","e(EM) nobaffle total","e(EM) nobaffle target","e(EM) nobaffle other","#gamma(EM) baffle total","#gamma(EM) baffle target","#gamma(EM) baffle other","e(EM) baffle total","e(EM) baffle target","e(EM) baffle other"};
// // int pid[m]={2,2,2,1,2,2,2};
// // char *label[m]={"e(DIS) larger Z baffle","e(DIS) smaller Z baffle","#gamma(EM) target","#gamma(EM) other","e(EM) total","e(EM) target","e(EM) other"};
// int color[m]={1,2,3,4,5,6,7,8,9,40,43,46,49};
// ///EC phi
// char *hst[m]={"fluxPhi","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other"};
// double min=1e-2,max=1e7;  
// // char *hst[m]={"EfluxPhi","EfluxPhi","EfluxPhi_target","EfluxPhi_other","EfluxPhi","EfluxPhi_target","EfluxPhi_other","EfluxPhi","EfluxPhi_target","EfluxPhi_other","EfluxPhi","EfluxPhi_target","EfluxPhi_other"};
// // double min=1e1,max=1e7;  
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1300,800);
// c->Divide(1,1);
// ///gem phi
// // char *hst[m]={"fluxPhi","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other","fluxPhi","fluxPhi_target","fluxPhi_other"};
// // double min=1e2,max=1e5;  
// // const int n=4;
// // int hit_id[n]={0,1,2,3};
// // char *title[n]={"gem 1","gem 2","gem 3","gem 4"};
// // TCanvas *c = new TCanvas("compare_1D","compare_1D",1300,800);
// // c->Divide(2,2);
// ///option
// bool Is_R=false,Is_Phi=true;
// // bool Is_log=false;
// bool Is_log=true;


// const int m=3;
// char* input_filename[m]={
// "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root",
// "baffle_largerZ_extrablock/background_solid_CLEO_PVDIS_LD2_other_eDIS_1e6_output.root"
// };
// int pid[m]={2,2,2};
// char *label[m]={"e(DIS) all","e(DIS) target","e(DIS) other"};
// int color[m]={1,2,3};
// const int n=1;
// int hit_id[n]={8};
// // char *title[n]={"gem"};
// char *hst[m]={"fluxPhi","fluxPhi_target","fluxPhi_other"};
// double min=1e-10,max=1e10; 
// // double min=1e2,max=1e8;  
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,900);
// c->Divide(n,1);


// const int m=4;
// char* input_filename[m]={
// "SIDIS_He3_1/old/background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// "SIDIS_He3_1/old/background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// "SIDIS_He3_1/background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// "SIDIS_He3_1/background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root"
// };
// int pid[m]={1,2,1,2};
// char *label[m]={"#gamma(EM) old","e(EM) old","#gamma(EM) new","e(EM) new"};
// int color[m]={1,2,3,4};
// const int n=1;
// int hit_id[n]={8};
// char *title[n]={"EC forward angle"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,900);
// c->Divide(n,1);

// const int m=2;
// char* input_filename[m]={
// "background_solid_CLEO_PVDIS_LD2_nobaffle_2e8_output.root",
// "background_solid_CLEO_PVDIS_LD2_2e8_output.root"
// };
// int pid[m]={0,0};
// char *label[m]={"e+#gamma(EM), nobaffle","e+#gamma(EM), baffle"};
// int color[m]={1,2};
// const int n=4;
// int hit_id[n]={0,1,2,3};
// char *title[n]={"GEM plane 1","GEM plane 2","GEM plane 3","GEM plane 4"};
// TCanvas *c = new TCanvas("fluxR","fluxR",1600,900);
// c->Divide(2,n/2);

// const int m=5;
// char* input_filename[m]={
// "background_solid_PVDIS_LD2_EM_1e8_output.root",
// "background_solid_PVDIS_LD2_EM_1e8_output.root",
// "background_solid_PVDIS_LD2_EM_1e8_output.root",
// "background_solid_PVDIS_LD2_EM_1e8_output.root",
// "background_solid_PVDIS_LD2_EM_1e8_output.root"
// };
// // int pid[m]={0,1,2,3,4};
// // int pid[m]={5,6,7,8,10};
// // int pid[m]={0,0,0,0,0};
// // int pid[m]={1,1,1,1,1};
// int pid[m]={2,2,2,2,2};
// char *label[m]={"GEM 1","GEM 2","GEM 3","GEM 4","GEM 5"};
// int color[m]={1,2,3,4,5};
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR"};
// double min=1e-2,max=1e3;    
// double rmin=0,rmax=300;
// const int n=5;
// // int hit_id[n]={29,29,29,29,29};
// int hit_id[n]={29,31,33,35,37};
// // int hit_id[n]={30,32,34,36,38};
// char *title[n]={"Rate"};
// TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
// c->Divide(1,1);
// ///option
// bool Is_R=true,Is_Phi=false;
// // bool Is_log=false;
// bool Is_log=true;

const int m=6;
char* input_filename[m]={
// "background_solid_SIDIS_He3_EM_1e8_output.root",
// "background_solid_SIDIS_He3_EM_1e8_output.root",
// "background_solid_SIDIS_He3_EM_1e8_output.root",
// "background_solid_SIDIS_He3_EM_1e8_output.root",
// "background_solid_SIDIS_He3_EM_1e8_output.root",
// "background_solid_SIDIS_He3_EM_1e8_output.root"

"background_solid_JPsi_LH2_EM_1e8_output.root",  
"background_solid_JPsi_LH2_EM_1e8_output.root",
"background_solid_JPsi_LH2_EM_1e8_output.root",
"background_solid_JPsi_LH2_EM_1e8_output.root",
"background_solid_JPsi_LH2_EM_1e8_output.root",
"background_solid_JPsi_LH2_EM_1e8_output.root",
};
int pid[m]={0,0,0,0,0,0};
// int pid[m]={1,1,1,1,1,1};
// int pid[m]={2,2,2,2,2,2};
char *label[m]={"GEM 1","GEM 2","GEM 3","GEM 4","GEM 5","GEM 6"};
int color[m]={1,2,3,4,5,6};
char *hst[m]={"fluxR","fluxR","fluxR","fluxR","fluxR","fluxR"};
double min=1e-2,max=1e3;    
double rmin=0,rmax=300;
const int n=6;
int hit_id[n]={29,31,33,35,37,39};
// int hit_id[n]={30,32,34,36,38,40};
char *title[n]={"EM Background"};
TCanvas *c = new TCanvas("compare_1D","compare_1D",1000,800);
c->Divide(1,1);
///option
bool Is_R=true,Is_Phi=false;
// bool Is_log=false;
bool Is_log=true;


///======================
TLegend* leg = new TLegend(0.8, 0.8, 0.9, 0.9);

  TFile *input[m];
TH1F *h[n][m];
for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;
  input[i]=new TFile(input_filename[i]);
  if (input[i]->IsZombie()) {
    cout << "Error opening ratefile " << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
  for(int j=i;j<i+1;j++){
    char hstname[100];
//     sprintf(hstname,"%s_%i_%i",hst,hit_id[j],pid[i]);
    sprintf(hstname,"%s_%i_%i",hst[i],hit_id[j],pid[i]);    
  cout << hstname << endl;
  h[j][i]=(TH1F*) input[i]->Get(hstname);
  c->cd(j+1);
//   for(int k=1;k<24;k++) {h[j][i]->SetBinContent(k,0);}
  if(Is_log) gPad->SetLogy();
  h[j][i]->SetLineColor(color[i]);
//   h[j][i]->SetLineStyle(i%2*7);  
  h[j][i]->SetMinimum(min);
  h[j][i]->SetMaximum(max);
  h[j][i]->SetAxisRange(rmin,rmax);  
  h[j][i]->SetTitle(title[j]);  
  if (i==0) h[j][i]->Draw();
  else h[j][i]->Draw("same");

  leg->AddEntry(h[j][i], label[i],"l");  
  }
//   input.Close();
}

   leg->Draw();

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
c->SaveAs("compare_1D.png");
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

