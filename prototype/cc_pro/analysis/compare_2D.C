{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
// gStyle->SetPadRightMargin(0.32);


// char input_dir[100]="/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass8/farm_solid_SIDIS_He3_moved_inter";
// char input_dir[200]="/work/halla/solid/sim/solid_gemc/SIDIS_He3_JLAB_VERSION_1.3/pass8";
char input_dir[200]="/work/halla/solid/sim/solid_gemc/cc_pro_JLAB_VERSION_1.3";

const int m=2;
char* input_filename[m]={

"cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_new_output.root",
"cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_new_output.root",
// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_weighted_eDIS_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pimWiser_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_CO2_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_dirty_normalized_pi0Wiser_C4F8_filenum100_1e7_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_1.957e10_CO2_skim_output.root",
// "cc_pro_SIDIS_He3_BeamOnTarget_1.871e10_C4F8_skim_output.root",
  
}; 
// int pid[m]={5,1,5,1};
// char *hst[m]={"hit_hgc_2D","hit_hgc_2D"};
// char *hst[m]={"gen_ThetaP","gen_ThetaP"};
char *hst[m]={"hit_vz_0","hit_vz_1"};
int color[m]={
1,2,
// 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,29,
};
int style[m]={
1,1,
};
float scale[m]={
1,1
};
// char *hst[m]={
// "npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2",
// "npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2","npe_hgc_mom_2",
// };
// double ymin=1e0,ymax=1e5;
// double xmin=-380,xmax=-310;
// char *hst[m]={"fluxR","fluxR","fluxR","fluxR"};
double ymin=1,ymax=2e4;
// double ymin=1,ymax=4e3;
double xmin=0,xmax=200;
// int hit_id[m]={8,8,8,8};
// char *title[m]={"HGC signal Np.e.;MaPMT;MaPMT","HGC signal Np.e.;pixel;pixel"};
// char *title[m]={"HGC background Np.e.;MaPMT;MaPMT","HGC background Np.e.;pixel;pixel"};
// TCanvas *c = new TCanvas("compare_2D","compare_2D",1700,800);
// c->Divide(2,1);		
TCanvas *c[2];
c[0]= new TCanvas("compare_2D_1","compare_2D_1",1000,800);
c[1]= new TCanvas("compare_2D_2","compare_2D_2",1000,800);
// TCanvas *cc = new TCanvas("compare_2D_proj","compare_2D_proj",1200,800);
// cc->Divide(2,1);
///option
bool Is_R=true,Is_Phi=false;
bool Is_log=false;
// bool Is_log=true;
bool Is_cut=false;


TFile *input[m];
TH1F *h[m];
// TH2F *h[m];
TH1D *h_p[m];
for(int i=0;i<m;i++){
  input[i]=new TFile(Form("%s/%s",input_dir,input_filename[i]));
  if (input[i]->IsZombie()) {
    cout << "Error opening ratefile " << input_filename[i] << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename[i] << endl;
  
  char hstname[100];
//   sprintf(hstname,"%s_%i_%i",hst[i],hit_id[i],pid[i]);    
  sprintf(hstname,"%s",hst[i]);
//   sprintf(hstname,"%s","hit_momloss_7");
//   sprintf(hstname,"%s","npe_hgc_mom_9");  
//   sprintf(hstname,"%s","npe_hgc");  
//   sprintf(hstname,"%s","hit_mom_7");
//   sprintf(hstname,"%s","pattern_hgc");    
  cout << hstname << endl;
//   h2[i]=(TH2F*) input[i]->Get(hstname);
  h1[i]=(TH1F*) input[i]->Get(hstname);  

//   if (Is_cut) {
//     for(int j=0;j<h[i]->GetXaxis()->FindBin(cut[i]);j++)  h[i]->SetBinContent(j+1,0);
//   }
  
//   c->cd(i+1);
  c[i]->cd(1);  
//   gPad->SetLogz();
//   gPad->SetLogy();
//   h[i]->SetLineWidth(3);  
//   h[i]->SetLineColor(i);  
//   h[i]->SetLineStyle(1);  
//   h[i]->SetLineColor(color[i]);  
//   h[i]->SetLineStyle(style[i]);
//   h[i]->Scale(scale[i]);  
//   h[i]->SetMinimum(0);
//   h[i]->SetMaximum(1);
//   h[i]->SetAxisRange(xmin,xmax);  
//   h[i]->SetTitle(title[i]);
//   h[i]->GetXaxis()->CenterTitle();
      h[i]->Draw();

//   h[i]->Draw("colz");

//   h_p[i]=h[i]->ProjectionX();
//   cc->cd(i+1);    
//     h_p[i]->Scale(scale[i]);
//   h_p[i]->SetMinimum(0);
//   h_p[i]->SetMaximum(1);
//     h_p[i]->Draw();

//     if (i==0 || i==2) cc->cd(1);
//     if (i==1 || i==3) cc->cd(2);        
  
//   else if (i!=7 && i!=8 && i!=9 && i!=15 && i!=16 && i!=17 && i!=25 && i!=26 && i!=27 && i!=33 && i!=34 && i!=35) h[i]->Draw("same");
  
//   if (i==10 || i==11 || i==16 || i==17) h[i]->Draw("same");
  
//   if (i==0) h[i]->Draw();
//   else if (i<m/2)h[i]->Draw("same");

//   if (i==m/2) h[i]->Draw();
//   else if (i>m/2) h[i]->Draw("same");
//     cout << "event_all " << h[i]->GetEntries() << endl;
    
//     input[i].Close(); 
}

// TH1F *heff_pi=new TH1F("heff_pi",";window;", m/2, 0, m/2);
// TH1F *heff_k=new TH1F("heff_k",";window;", m/2, 0, m/2);
// TH1F *hacc_pi=new TH1F("hacc_pi",";window;", m/2, 0, m/2);
// TH1F *hacc_k=new TH1F("hacc_k",";window;", m/2, 0, m/2);
// double eff_pi[m/2],eff_k[m/2];
// 
// // TLegend* leg = new TLegend(0.80, 0.99-0.3*m, 0.99, 0.99);
// TLegend* leg = new TLegend(0.75, 0.97-0.05*m/2, 0.99, 0.99);
// for(int i=0;i<2;i++){
//   if (i!=7 && i!=8 && i!=9 && i!=15 && i!=16 && i!=17 && i!=25 && i!=26 && i!=27 && i!=33 && i!=34 && i!=35) {}
//   else continue;
// //   double eff=h[i]->Integral(2,100)/h[i]->GetEntries();
// //       double eff=h[i]->Integral(20,100);
// //       leg->AddEntry(h[i],Form("%s \t %.f",label[i],eff),"l");
//   
//   double event_sel=h[i]->Integral(h[i]->FindBin(5),h[i]->GetNbinsX()+1)/scale[i];
//   cout << "event_all " << h[i]->GetEntries() << " event_non_0 " << h[i]->Integral(2,201)/scale[i] << " event_sel " << event_sel<< endl;    
//   double eff;
//   if (i<m/2) {
//     //bin 2 is npe=1, 101 is overflow bin
//     eff=event_sel/h[i]->GetEntries();    
// //      eff=h[i]->Integral(2,201)/scale[i];
//     eff_pi[i]=eff; 
//     heff_pi->Fill(i,eff);
//     hacc_pi->Fill(i,float(h[i]->GetEntries())/h[0]->GetEntries());
//     leg->AddEntry(h[i],Form("%s \t %.03f",label[i],eff),"l");
//   }
//   else {
//     eff=event_sel/h[i]->GetEntries();        
//     eff_k[i-m/2]=eff; 
//     heff_k->Fill(i-m/2,1-eff);
// //     heff_k->Fill(i-m/2,eff);    
//     hacc_k->Fill(i-m/2,float(h[i]->GetEntries())/h[m/2]->GetEntries());
//     leg->AddEntry(h[i],Form("%s \t %.03f",label[i],1-eff),"l");
//   }
// }		
// leg->Draw();
// c->SaveAs("hgc_npe.png");
// 
// TCanvas *c_eff = new TCanvas("eff","eff",1000,800);
// // heff_pi->SetMinimum(0.9);
// heff_pi->SetMinimum(0.5);
// heff_pi->SetMaximum(1);
// heff_pi->SetLineColor(1);
// heff_pi->Draw();
// heff_k->SetLineColor(2);
// heff_k->Draw("same");
// 
// TLegend* leg1 = new TLegend(0.75, 0.95-0.05*2, 0.95, 0.99);
// leg1->AddEntry(heff_pi,"pion","l");
// leg1->AddEntry(heff_k,"kaon","l");
// leg1->Draw();
// c_eff->SaveAs("hgc_eff.png");
// 
// TCanvas *c_acc = new TCanvas("acc","acc",1000,800);
// hacc_pi->SetMinimum(0.5);
// hacc_pi->SetMaximum(1);
// hacc_pi->SetLineColor(1);
// hacc_pi->Draw();
// hacc_k->SetLineColor(2);
// hacc_k->Draw("same");
// 
// TLegend* leg2 = new TLegend(0.75, 0.95-0.05*2, 0.95, 0.99);
// leg2->AddEntry(hacc_pi,"pion","l");
// leg2->AddEntry(hacc_k,"kaon","l");
// leg2->Draw();
// c_acc->SaveAs("hgc_acc.png");
// 
// 
// // double x[8]={0,0.2,0.5,1,2,5,10,50,100};
// // TGraph* gr_k = new TGraph(8,x,eff_k);
// // TGraph* gr_pi_d = new TGraph(8,x,eff_pi);
// // gr->Draw("AC*");

}