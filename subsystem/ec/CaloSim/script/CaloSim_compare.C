void CaloSim_compare(){
// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1111);

const int m=4;
char *part[m]={"W_NoField","W_YesField","Fe_NoField","Fe_YesField"};
char *partname[m]={"W_NoField (Solid)","W_YesField (Empty)","Fe_NoField (Solid)","Fe_YesField (Empty)"};

const int m=2;
// char *part[m]={"Tungsten","Iron"};
// char *partname[m]={"W_NoField (Solid)","Fe_NoField (Solid)"};
char *part[m]={"Tungsten_NoField","Tungsten_YesField"};
char *partname[m]={"W_NoField (Solid)","W_YesField (Solid)"};
const int n=9;
char *hstname[n]={
"showerPosX","showerPosY","showerPosZ",
"showerSizeX","showerSizeY","showerSizeZ",
"resolution","ratio","loss"
};

TFile *file[m];
for(int k=0;k<m;k++){
      char filename[80];
//     sprintf (filename, "CaloSim_%s_1mm_1e4.root",part[k]);
    sprintf (filename, "CaloSim_%s.root",part[k]);      
    cout << filename << endl;
    file[k]=new TFile(filename);
}

TCanvas *c_result=new TCanvas("result","result",2000,0,900,900);
// c_result->Divide(3,3);   
// for(int i=0;i<n;i++){
  for(int i=6;i<7;i++){
  c_result->cd(i+1);

    for(int k=0;k<m;k++){
    TH1F *h1 = (TH1F*) file[k]->Get(hstname[i]);
    int color=k/2+1;
    h1->SetFillColor(color); 
    h1->SetLineColor(color);
    h1->SetMarkerColor(color);
    h1->SetMarkerStyle(k/2+20+(k%2)*4);
    h1->SetMarkerSize(1);
    if(k==0) h1->Draw("E1");
    else h1->Draw("E1 same");
    if (i==0) {h1->SetMaximum(30);h1->SetMinimum(0);}
    if (i==1) {h1->SetMaximum(0.1);h1->SetMinimum(-0.1);}
    if (i==2) {h1->SetMaximum(0);h1->SetMinimum(-200);}    
    if (i==3) {h1->SetMaximum(100);h1->SetMinimum(0);}       
    if (i==4) {h1->SetMaximum(100);h1->SetMinimum(0);}   
    if (i==5) {h1->SetMaximum(100);h1->SetMinimum(0);}
    if (i==6) {h1->SetMaximum(10);h1->SetMinimum(3);}   
    if (i==7) {h1->SetMaximum(0.02);h1->SetMinimum(0);}   
    if (i==8) {h1->SetMaximum(10);h1->SetMinimum(0);}      
  }

  //add text
  if (i==6){
  TPaveText *pt = new TPaveText(0.65,0.7,0.98,0.98,"brNDC");
  pt->SetFillColor(17);
  pt->SetTextAlign(12);
  pt->Draw();
  // int color[6]={kOrange,kGreen,kViolet,kRed,kBlue,kBlack};
  // int marker[6]={20,23,21,29,29,22};
  for(int k=0;k<m;k++){
  TText *text=pt->AddText(partname[k]);
  text->SetTextColor(k/2+1);
  text->SetTextSize(0.035);
  // TMarker *m = new TMarker(3, 8-(8-7)/4-k*(8-7)/4, k+24);
  // m->SetMarkerColor(k+1);
  // m->SetMarkerSize(2);
  // m->Draw();
  }
  }
  
}

// c_result->SaveAs("result.png");

// TCanvas *c_ec_SciFi_resolution=new TCanvas("ec_SciFi_resolution","ec_SciFi_resolution",2000,0,900,900);
// for(int i=0;i<n;i++){
//   c_result->cd(i+1);

}