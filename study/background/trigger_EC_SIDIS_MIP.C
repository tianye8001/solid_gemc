///use Eklog_R plot and trigger curve to make trigger cut and get trigger rate

void trigger_EC_SIDIS_MIP(char *region)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
gStyle->SetPadRightMargin(0.32);    

int region_index;
if (region=="SIDIS_FA") region_index=0;
// else if (region=="SIDIS_LA") region_index=1;
else if (region=="SIDIS_LA") {cout << "trigger only for FA" << endl; exit(-1);}
else {cout << "need option for FA or LA region" << endl; exit(-1);}

// int det[2]={8,12};  //detecor ID
// double Rmin[2]={90,80};
// double Rmax[2]={230,140};

int det[2]={8,12};  //detecor ID
double Rmin[2]={105,80};
double Rmax[2]={235,140};

// int det[2]={18,12};  //detecor ID
// double Rmin[2]={58,80};
// double Rmax[2]={127,140};

double factor=1.;  //only PVDIS need this factor as 2 because high and low area only takes half of full azimuthal

int rebin_factor=1;

const int m=5;
char* input_filename[m]={
// "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_pim_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_pip_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_pi0_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_p_1e6_output.root"
  
// "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root_Q21",
// "background_solid_CLEO_SIDIS_He3_sum_actual_pi0_1e6_output.root",  
//     "background_solid_CLEO_SIDIS_He3_window_downstream_other_eDIS_1e6_output.root",
  "background_solid_CLEO_SIDIS_He3_window_upstream_other_eDIS_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",  
"background_solid_CLEO_SIDIS_He3_sum_actual_pim_1e6_output.root",
"background_solid_CLEO_SIDIS_He3_sum_actual_pip_1e6_output.root",
"background_solid_CLEO_SIDIS_He3_sum_actual_pi0_1e6_output.root",
"background_solid_CLEO_SIDIS_He3_sum_actual_p_1e6_output.root"

// "background_solid_CLEO_SIDIS_He3_window_upstream_actual_pi0_1e6_output.root",  
// // "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root",
// // "background_solid_CLEO_SIDIS_He3_other_eDIS_1e6_output.root_Q21",
// "background_solid_CLEO_SIDIS_He3_sum_actual_pim_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_pip_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_window_upstream_actual_pi0_1e6_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_p_1e6_output.root"


// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root",
// "background_solid_CLEO_SIDIS_He3_sum_actual_all_output.root"

// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root",
// "background_solid_CLEO_SIDIS_He3_1e8_output.root"

// "a.root","a.root","a.root","a.root","a.root"
};

const int Ntrigline=1,Ntriglinebin=30;

TFile *file_trig_cut[1][Ntrigline][4];

double trig_cut_range_R[Ntrigline+1]={0,300};

///Forward MIP trigger, rough estimate
// file_trig_cut[0][0][0]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_TrigMIP2.root");
// file_trig_cut[0][0][1]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_TrigMIP2.root");
// 
// file_trig_cut[0][1][0]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_TrigMIP2.root");
// file_trig_cut[0][1][1]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_TrigMIP2.root");

///MIP trigger 100% pion eff at 1GeV, 30 points per curve
file_trig_cut[0][0][0]=new TFile("triggerfile/MIPTrigger/Elec.run10xGetEfficiencies__NO_bgd_TrigMIP2.root");
file_trig_cut[0][0][1]=new TFile("triggerfile/MIPTrigger/Pion.run10xGetEfficiencies__NO_bgd_TrigMIP2.root");
file_trig_cut[0][0][2]=new TFile("triggerfile/MIPTrigger/Gamma.run10xGetEfficiencies__NO_bgd_TrigMIP2.root");
file_trig_cut[0][0][3]=new TFile("triggerfile/MIPTrigger/Proton.run10xGetEfficiencies__NO_bgd_TrigMIP2.root");

///MIP trigger 95% pion eff at 1GeV, 60 points per curve
// file_trig_cut[0][0][0]=new TFile("triggerfile/MIPTrigger_95Perc/Elec.run10xGetEfficiencies__NO_bgd_TrigMIP95Perc.root");
// file_trig_cut[0][0][1]=new TFile("triggerfile/MIPTrigger_95Perc/Pion.run10xGetEfficiencies__NO_bgd_TrigMIP95Perc.root");
// file_trig_cut[0][0][2]=new TFile("triggerfile/MIPTrigger_95Perc/Gamma.run10xGetEfficiencies__NO_bgd_TrigMIP95Perc.root");
// file_trig_cut[0][0][3]=new TFile("triggerfile/MIPTrigger_95Perc/Proton.run10xGetEfficiencies__NO_bgd_TrigMIP95Perc.root");


double trig_cut[1][Ntrigline][Ntriglinebin+2][8];
TGraphErrors *gr_trig_cut[1][Ntrigline][4];
for (int j=0;j<1;j++){
for (int i=0;i<Ntrigline;i++){  
  double binwidth;
  for (int l=0;l<4;l++){    
    gr_trig_cut[j][i][l]=(TGraphErrors*) file_trig_cut[j][i][l]->Get("Graph");
    binwidth=gr_trig_cut[j][i][l]->GetX()[1]-gr_trig_cut[j][i][l]->GetX()[0];
    for (int k=0;k<Ntriglinebin;k++){ //set any point with eff <0.01 as 0
      if (gr_trig_cut[j][i][l]->GetY()[k]<0.01) gr_trig_cut[j][i][l]->SetPoint(k,gr_trig_cut[j][i][l]->GetX()[k],0.);
    }    
  }    
trig_cut[j][i][0][0]=trig_cut_range_R[i];
trig_cut[j][i][0][1]=trig_cut_range_R[i+1];
trig_cut[j][i][0][2]=0.;
trig_cut[j][i][0][3]=gr_trig_cut[j][i][0]->GetX()[0]-binwidth/2;
trig_cut[j][i][0][4]=0.;
trig_cut[j][i][0][5]=0.;
trig_cut[j][i][0][6]=0.;
trig_cut[j][i][0][7]=0.;
for (int k=0;k<Ntriglinebin;k++){
trig_cut[j][i][k+1][0]=trig_cut_range_R[i];
trig_cut[j][i][k+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][k+1][2]=gr_trig_cut[j][i][0]->GetX()[k]-binwidth/2;
trig_cut[j][i][k+1][3]=gr_trig_cut[j][i][0]->GetX()[k]+binwidth/2;
trig_cut[j][i][k+1][4]=gr_trig_cut[j][i][0]->GetY()[k];
trig_cut[j][i][k+1][5]=gr_trig_cut[j][i][1]->GetY()[k];
trig_cut[j][i][k+1][6]=gr_trig_cut[j][i][2]->GetY()[k];
trig_cut[j][i][k+1][7]=gr_trig_cut[j][i][3]->GetY()[k];
}
trig_cut[j][i][Ntriglinebin+1][0]=trig_cut_range_R[i];
trig_cut[j][i][Ntriglinebin+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][Ntriglinebin+1][2]=gr_trig_cut[j][i][0]->GetX()[Ntriglinebin-1]+binwidth/2;
trig_cut[j][i][Ntriglinebin+1][3]=11.;
trig_cut[j][i][Ntriglinebin+1][4]=gr_trig_cut[j][i][0]->GetY()[Ntriglinebin-1];
trig_cut[j][i][Ntriglinebin+1][5]=gr_trig_cut[j][i][1]->GetY()[Ntriglinebin-1];
trig_cut[j][i][Ntriglinebin+1][6]=gr_trig_cut[j][i][2]->GetY()[Ntriglinebin-1];
trig_cut[j][i][Ntriglinebin+1][7]=gr_trig_cut[j][i][3]->GetY()[Ntriglinebin-1];
}
}

cout << "here is the trig value" << endl;
for (int j=0;j<1;j++){
for (int i=0;i<Ntrigline;i++){  
  for (int k=0;k<Ntriglinebin+2;k++){
    for (int l=0;l<8;l++){
      cout << trig_cut[j][i][k][l] << "\t\t";
    }
  cout << endl;      
  }
}
}


/*===================================================================
/// Forward Electron Trigger
// Radius(cm)  P Threshold (GeV)
//   90 - 105      5.0    
// 105 - 115      4.0    
// 115 - 130      3.0    
// 130 - 150      2.0    
// 150 - 200      1.0 
// 200 - 230      2.0 
// 6 point cut, right on Q2=1 line and field bend line
double trig_cut_range_R[Ntrigline+1]={0,105,115,130,150,200,300};
// double trig_cut_range_R[Ntrigline+1]={0,63,70,85,100,110,127};

// Radius(cm)  P Threshold (GeV)
//   90 - 105      5.0    
// 105 - 115      4.0    
// 115 - 130      3.0    
// 130 - 150      2.0    
// 150 - 210      1.0 
// 5 point cut, right on Q2=1 line
// double trig_cut_range_R[Ntrigline+1]={0,105,115,130,150,300};


// Radius(cm)  E Threshold (GeV)   Trigger Turn-on curve (pion)
// 90 - 110    4.0                
// 110 - 125   3.0                
// 125 - 145   2.0                
// 145 - 210   1.0                
// double trig_cut_range_R[Ntrigline+1]={0,110,125,145,300};

file_trig_cut[0][0][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root");
file_trig_cut[0][0][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH4.4.root");
file_trig_cut[0][1][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root");
file_trig_cut[0][1][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH3.5.root");
file_trig_cut[0][2][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root");
file_trig_cut[0][2][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH2.6.root");
file_trig_cut[0][3][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root");
file_trig_cut[0][3][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root");
file_trig_cut[0][4][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root");
file_trig_cut[0][4][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_Trig0.9.root");
file_trig_cut[0][5][0]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root");
file_trig_cut[0][5][1]=new TFile("triggerfile/cutRadial_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_BackGround_Oct2013_SIDIS_TrigSH1.6.root");

// file_trig_cut[0][0][0]=new TFile("triggerfile/cut2GeV_NObackground/Lead2X0PbBlock_ZeroSpt_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_TrigSH1.6.root");
// file_trig_cut[0][0][1]=new TFile("triggerfile/cut2GeV_NObackground/Lead2X0PbBlock_ZeroSpt_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_TrigSH1.6.root");
// 
// file_trig_cut[0][1][0]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunElectron_GetEfficiencies_Trig0.9.root");
// file_trig_cut[0][1][1]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Forward_RunPion_GetEfficiencies_Trig0.9.root");

///Large Angle Trigger   has no radial dependence
for (int i=0;i<Ntrigline;i++){
file_trig_cut[1][i][0]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunElectron_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root");
file_trig_cut[1][i][1]=new TFile("triggerfile/cut1GeV_innerbackground/Lead2X0PbBlock_Hex.1.SIDIS_Large_RunPion_GetEfficienciesBackGround_Oct2013_SIDIS_Full_bgd_TrigSH2.0.root");
}

char *gr_trig_cut_ele_name[2][Ntrigline],*gr_trig_cut_pi_name[2][Ntrigline];
for(int j=0;j<2;j++){
  for(int i=0;i<Ntrigline;i++){
    gr_trig_cut_ele_name[j][i]="Graph";
    gr_trig_cut_pi_name[j][i]="Graph";    
  }  
}

double trig_cut[2][Ntrigline][Ntriglinebin+2][6];
TGraphErrors *gr_trig_cut_ele[2][Ntrigline],*gr_trig_cut_pi[2][Ntrigline];
for (int j=0;j<2;j++){
for (int i=0;i<Ntrigline;i++){  
gr_trig_cut_ele[j][i]=(TGraphErrors*) file_trig_cut[j][i][0]->Get(gr_trig_cut_ele_name[j][i]);
gr_trig_cut_pi[j][i]=(TGraphErrors*) file_trig_cut[j][i][1]->Get(gr_trig_cut_pi_name[j][i]);
double binwidth=gr_trig_cut_ele[j][i]->GetX()[1]-gr_trig_cut_ele[j][i]->GetX()[0];
if (j==1) { //add one more point for LA to become 21 points like FA
  gr_trig_cut_ele[j][i]->SetPoint(20,gr_trig_cut_ele[j][i]->GetX()[19]+binwidth,gr_trig_cut_ele[j][i]->GetY()[19]);
  gr_trig_cut_pi[j][i]->SetPoint(20,gr_trig_cut_pi[j][i]->GetX()[19]+binwidth,gr_trig_cut_pi[j][i]->GetY()[19]);    
}
for (int k=0;k<Ntriglinebin;k++){ //set any point with eff <0.01 as 0
  if (gr_trig_cut_ele[j][i]->GetY()[k]<0.01) gr_trig_cut_ele[j][i]->SetPoint(k,gr_trig_cut_ele[j][i]->GetX()[k],0.);
  if (gr_trig_cut_pi[j][i]->GetY()[k]<0.01) gr_trig_cut_pi[j][i]->SetPoint(k,gr_trig_cut_pi[j][i]->GetX()[k],0.);
}
trig_cut[j][i][0][0]=trig_cut_range_R[i];
trig_cut[j][i][0][1]=trig_cut_range_R[i+1];
// trig_cut[j][i][0][2]=0.22;
// trig_cut[j][i][0][3]=gr_trig_cut_ele[j][i]->GetX()[0]-binwidth/2;
// trig_cut[j][i][0][4]=0.8*gr_trig_cut_ele[j][i]->GetY()[0];
// trig_cut[j][i][0][5]=0.8*gr_trig_cut_pi[j][i]->GetY()[0];
trig_cut[j][i][0][2]=0.;
trig_cut[j][i][0][3]=gr_trig_cut_ele[j][i]->GetX()[0]-binwidth/2;
trig_cut[j][i][0][4]=0.;
trig_cut[j][i][0][5]=0.;
cout << j << " " << i << " " << 0 << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[0] << "\t" << gr_trig_cut_ele[j][i]->GetY()[0] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[0] << "\t" << gr_trig_cut_pi[j][i]->GetY()[0] << endl;
for (int k=0;k<Ntriglinebin;k++){
trig_cut[j][i][k+1][0]=trig_cut_range_R[i];
trig_cut[j][i][k+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][k+1][2]=gr_trig_cut_ele[j][i]->GetX()[k]-binwidth/2;
trig_cut[j][i][k+1][3]=gr_trig_cut_ele[j][i]->GetX()[k]+binwidth/2;
trig_cut[j][i][k+1][4]=gr_trig_cut_ele[j][i]->GetY()[k];
trig_cut[j][i][k+1][5]=gr_trig_cut_pi[j][i]->GetY()[k];
cout << j << " " << i << " " << k << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[k] << "\t" << gr_trig_cut_ele[j][i]->GetY()[k] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[k] << "\t" << gr_trig_cut_pi[j][i]->GetY()[k] << endl;
}
trig_cut[j][i][Ntriglinebin+1][0]=trig_cut_range_R[i];
trig_cut[j][i][Ntriglinebin+1][1]=trig_cut_range_R[i+1];
trig_cut[j][i][Ntriglinebin+1][2]=gr_trig_cut_ele[j][i]->GetX()[Ntriglinebin-1]+binwidth/2;
trig_cut[j][i][Ntriglinebin+1][3]=11.;
trig_cut[j][i][Ntriglinebin+1][4]=gr_trig_cut_ele[j][i]->GetY()[Ntriglinebin-1];
trig_cut[j][i][Ntriglinebin+1][5]=gr_trig_cut_pi[j][i]->GetY()[Ntriglinebin-1];
cout << j << " " << i << " " << Ntriglinebin+1 << " " << gr_trig_cut_ele_name[j][i] << "\t" << gr_trig_cut_ele[j][i]->GetX()[Ntriglinebin-1] << "\t" << gr_trig_cut_ele[j][i]->GetY()[Ntriglinebin-1] << "\t" << gr_trig_cut_pi_name[j][i] << "\t" << gr_trig_cut_pi[j][i]->GetX()[Ntriglinebin-1] << "\t" << gr_trig_cut_pi[j][i]->GetY()[Ntriglinebin-1] << endl;
}
}

cout << "here is the trig value" << endl;
for (int j=0;j<2;j++){
for (int i=0;i<Ntrigline;i++){  
  for (int k=0;k<Ntriglinebin+2;k++){
    for (int l=0;l<6;l++){
      cout << trig_cut[j][i][k][l] << "\t\t";
    }
  cout << endl;      
  }
}
}
==================================================*/



int pid[m]={2,6,5,1,4};
char *label[m]={"e(DIS)","#pi^{-}(DIS)","#pi^{+}(DIS)","#gamma(#pi^{0}(DIS))","p(DIS)"};
// char *label[m]={"e(EM)","#pi^{-}(EM)","#pi^{+}(EM)","#gamma(EM)","p(EM)"};
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

TH2F *hEklog_R[n][m],*hEklog_R_trig[n][m];
TH1F *hfluxR[n][m];
TH1F *hfluxR_proj[n][m],*hfluxR_trig[n][m];
for(int i=0;i<m;i++){
  TFile *input=new TFile(input_filename[i]);
  if (input->IsZombie()) {
    cout << "Error opening ratefile" << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
  for(int j=0;j<n;j++){
  char hstname[100];  
  sprintf(hstname,"fluxR_%i_%i",det[region_index],pid[i]);
  cout << hstname << endl;
  hfluxR[j][i]=(TH1F*) input->Get(hstname); 
  c_fluxR_ec->cd(j+1);
  gPad->SetLogy(1);    
  hfluxR[j][i]->SetLineColor(color[i]);
  hfluxR[j][i]->SetMinimum(1e-7);
  hfluxR[j][i]->SetMaximum(1e2); 
  if (i==0) hfluxR[j][i]->Draw();
  else hfluxR[j][i]->Draw("same");    
  

  sprintf(hstname,"%s_%i_%i","Eklog_R",det[region_index],pid[i]);  
  cout << hstname << endl;
  hEklog_R[j][i]=(TH2F*) input->Get(hstname);  
  c_Eklog_R_ec->cd(j*m+i+1);
  gPad->SetLogz(1);
  if (i!=3) hEklog_R[j][i]->SetAxisRange(-3,1.1,"Y");  
  hEklog_R[j][i]->Draw("colz");
  
//   hfluxR_proj[j][i]= (TH1F*) hEklog_R[j][i]->ProjectionX();
  hfluxR_proj[j][i]= (TH1F*) hEklog_R[j][i]->ProjectionX("_px",1,hEklog_R[j][i]->GetNbinsY());  
  hfluxR_proj[j][i]->Scale(1./rebin_factor);  
  hfluxR_proj[j][i]->Rebin(rebin_factor);  
  c_fluxR_ec_proj->cd(j+1);
  gPad->SetLogy(1);      
  hfluxR_proj[j][i]->SetLineColor(color[i]);
  hfluxR_proj[j][i]->SetMinimum(1e-7);
  hfluxR_proj[j][i]->SetMaximum(1e2); 
  hfluxR_proj[j][i]->SetTitle(";R (cm);flux (kHz/mm2)");
  if (i==0) hfluxR_proj[j][i]->Draw();
  else hfluxR_proj[j][i]->Draw("same");    

  sprintf(hstname,"%s_trig_%i_%i","Eklog_R",j,i);      
  hEklog_R_trig[j][i]=(TH2F*) hEklog_R[j][i]->Clone(hstname);
  hEklog_R_trig[j][i]->Reset();
      cout << "bin" << hEklog_R[j][i]->GetNbinsY() << endl;  
  for(int k=1;k<=hEklog_R[j][i]->GetNbinsX();k++){
    for(int l=1;l<=hEklog_R[j][i]->GetNbinsY();l++){  
      double x=hEklog_R[j][i]->GetXaxis()->GetBinCenter(k);
      double y=hEklog_R[j][i]->GetYaxis()->GetBinCenter(l);      
      double Ek=pow(10,y);
//       double mom=sqrt(pow(10,y)*(pow(10,y)+2*mass[i]));  //from Ek to P
//       double mom=pow(10,y);  
      
      double new_value=0.;
// 	if (pow(10,y) > 2) new_value=hEklog_R[j][i]->GetBinContent(k,l);      
// 	else new_value=0;
//       for(int a=0;a<4;a++){      
// 	 for(int b=0;b<10;b++){
      for(int a=0;a<Ntrigline;a++){      
	 for(int b=0;b<Ntriglinebin+2;b++){
// 	    if (trig_cut[region_index][a][b][0] <= x && x < trig_cut[region_index][a][b][1] && trig_cut[region_index][a][b][2] <= mom && mom < trig_cut[region_index][a][b][3]){
// 	      if(i==0 || i==3) { //electron and photon use same cut
// 		new_value=trig_cut[region_index][a][b][4]*hEklog_R[j][i]->GetBinContent(k,l);	
// // 		if (mom>1) new_value=trig_cut[region_index][a][b][4]*hEklog_R[j][i]->GetBinContent(k,l);
// // 		else  new_value=(trig_cut[region_index][a][1][4]-(1-mom)*fabs(trig_cut[region_index][a][3][4]-trig_cut[region_index][a][1][4])/0.5)*hEklog_R[j][i]->GetBinContent(k,l);
// 	      }
// 	      else if (i==1 || i==2 ) { //pip and pim use same cut
// 		new_value=trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);		
// // 		if(mom>1) new_value=trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);
// // 		else  new_value=(trig_cut[region_index][a][1][5]-(1-mom)*fabs(trig_cut[region_index][a][3][5]-trig_cut[region_index][a][1][5])/0.5)*hEklog_R[j][i]->GetBinContent(k,l);
// 	      }		
// // 	      else if (i==1 || i==2 ) {
// // 		if  (mom>2) new_value=trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);
// // 		else new_value=0;
// // 	      }
// 	      else if (i==4) { //proton use half pion trig rate
// 		new_value=0.5*trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);
// // 		new_value=trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);
// 	      }
// 	      else new_value=0.;
// 	    }

	    if (trig_cut[region_index][a][b][0] <= x && x < trig_cut[region_index][a][b][1] && trig_cut[region_index][a][b][2] <= Ek && Ek < trig_cut[region_index][a][b][3]){
	      if(i==0) { //electron cut
		new_value=trig_cut[region_index][a][b][4]*hEklog_R[j][i]->GetBinContent(k,l);
	      }
	      else if (i==1 || i==2 ) { //pip and pim use same cut
		new_value=trig_cut[region_index][a][b][5]*hEklog_R[j][i]->GetBinContent(k,l);		
	      }		
	      else if (i==3) { //gamma cut
		new_value=trig_cut[region_index][a][b][6]*hEklog_R[j][i]->GetBinContent(k,l);
	      }
	      else if (i==4) { //proton cut
		new_value=trig_cut[region_index][a][b][7]*hEklog_R[j][i]->GetBinContent(k,l);
	      }	      
	      else new_value=0.;
	    }
	    
	 }
      }
      hEklog_R_trig[j][i]->SetBinContent(k,l,new_value);
    }
  }
  
  c_Eklog_R_ec_trig->cd(j*m+i+1);
  gPad->SetLogz(1);
  if (i!=3) hEklog_R_trig[j][i]->SetAxisRange(-3,1.1,"Y");    
  hEklog_R_trig[j][i]->Draw("colz"); 

  c_fluxR_ec_proj->cd(j+1);
  gPad->SetLogy(1);  
  hfluxR_trig[j][i]= (TH1F*) hEklog_R_trig[j][i]->ProjectionX();
  hfluxR_trig[j][i]= (TH1F*) hEklog_R_trig[j][i]->ProjectionX("_px",1,hEklog_R_trig[j][i]->GetNbinsY());   // do this to remove underflow and overflow bin content  
  hfluxR_trig[j][i]->Scale(1./rebin_factor);  //change from 1cm to 5cm bin
  hfluxR_trig[j][i]->Rebin(rebin_factor); //change from 1cm to 5cm bin  
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

double rate_total[n][m],rate_total_trig[n][m];
double rate_R[n][m][Ntrigline],rate_R_trig[n][m][Ntrigline];
for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
//     if(i==3 || i>6) continue;     
      int nbins=hfluxR_proj[j][i]->GetNbinsX();
      double binwidth=hfluxR_proj[j][i]->GetBinWidth(1);
//       cout << nbins << " " << binwidth << endl;
      double sum=0,sum_trig=0;
      double sum_R[Ntrigline],sum_R_trig[Ntrigline];
      for (int l=0;l<Ntrigline;l++){sum_R[l]=0;sum_R_trig[l]=0;}
      for(int k=1;k<nbins;k++){
	double r=hfluxR_proj[j][i]->GetBinCenter(k);
	if (r < Rmin[region_index] || Rmax[region_index]< r) continue;
	double thisrate=2*3.1415926*hfluxR_proj[j][i]->GetBinCenter(k)*binwidth*100*hfluxR_proj[j][i]->GetBinContent(k);  // factor 100 is from mm2 to cm2
	double thisrate_trig=2*3.1415926*hfluxR_trig[j][i]->GetBinCenter(k)*binwidth*100*hfluxR_trig[j][i]->GetBinContent(k); // factor 100 is from mm2 to cm2
	sum += thisrate;
	sum_trig += thisrate_trig;
	for (int l=0;l<Ntrigline;l++){
	  if (trig_cut_range_R[l] <= r && r < trig_cut_range_R[l+1]) {
	    sum_R[l] += thisrate;
	    sum_R_trig[l] += thisrate_trig;    
	  }
	}
      }
      rate_total[j][i]=sum/factor;
      rate_total_trig[j][i]=sum_trig/factor;      
      for (int l=0;l<Ntrigline;l++){
	rate_R[j][i][l]= sum_R[l]/factor;
	rate_R_trig[j][i][l]= sum_R_trig[l]/factor;  
      }
   }  
}   

for (int l=0;l<Ntrigline;l++){
  for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
      cout << Form("%.02e",rate_R[j][i][l]) << "\t";
    }
  }  
cout << endl;   
  for(int j=0;j<n;j++){
   for(int i=0;i<m;i++){
      cout << Form("%.02e",rate_R_trig[j][i][l]) << "\t";
    }
  }  
cout << endl;     
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

// char *pic_name[2][3]={
// "Eklog_R_high_ec_lead.png",
// "Eklog_R_high_ec_trig_lead.png",
// "fluxR_high_ec_lead.png",
// 
// "Eklog_R_low_ec_lead.png",
// "Eklog_R_low_ec_trig_lead.png",
// "fluxR_low_ec_lead.png"
// };
char *pic_name[2][3]={
"Eklog_R_FAEC.png",
"Eklog_R_FAEC_trig.png",
"fluxR_FAEC.png",

"Eklog_R_LAEC.png",
"Eklog_R_LAEC_trig.png",
"fluxR_LAEC.png",
};
c_Eklog_R_ec->SaveAs(pic_name[region_index][0]);
c_Eklog_R_ec_trig->SaveAs(pic_name[region_index][1]);
c_fluxR_ec_proj->SaveAs(pic_name[region_index][2]);

}


}
