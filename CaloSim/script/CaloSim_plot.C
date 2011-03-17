void CaloSim_plot(char *part){
// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1111);
gStyle->SetOptFit(11111111);

TCanvas *c_Hit = new TCanvas("Hit","Hit",1000,1000);
c_Hit->Divide(3,5);

TCanvas *c_Edep = new TCanvas("Edep","Edep",1000,1000);
c_Edep->Divide(3,5);

char outputfilename[100];
// sprintf(outputfilename,"CaloSim_%s_1mm_1e4.root",part);
sprintf(outputfilename,"CaloSim_%s.root",part);
TFile *outputfile=new TFile(outputfilename, "recreate");

TH1F *hshowerPosX=new TH1F("showerPosX","shower Pos X (mm)",5,1.25,3.75);
TH1F *hshowerPosY=new TH1F("showerPosY","shower Pos Y (mm)",5,1.25,3.75);
TH1F *hshowerPosZ=new TH1F("showerPosZ","shower Pos Z (mm)",5,1.25,3.75);

TH1F *hshowerSizeX=new TH1F("showerSizeX","shower Size X (mm)",5,1.25,3.75);
TH1F *hshowerSizeY=new TH1F("showerSizeY","shower Size Y (mm)",5,1.25,3.75);
TH1F *hshowerSizeZ=new TH1F("showerSizeZ","shower Size Z (mm)",5,1.25,3.75);

TH1F *hresolution=new TH1F("resolution","#sigmaE/E (%)",5,1.25,3.75);
TH1F *hratio=new TH1F("ratio","Edep(fiber)/Edep(absorber) (%)",5,1.25,3.75);
TH1F *hloss=new TH1F("loss","1-Edep(calo)/E(beam) (%)",5,1.25,3.75);
  
char *E[5]={"1.5","2.0","2.5","3.0","3.5"};
for(int k=0;k<5;k++){
  char filename[80];
//   sprintf (filename, "CaloSim_%s_1mm_%sGeV_1e4.root",part,E[k]);
  sprintf (filename, "myoutput_%s_%sGeV.root",part,E[k]);  
  cout << filename << endl;
  TFile *file=new TFile(filename);

  // TCanvas *c_EvsFiber = new TCanvas("EvsFiber","EvsFiber",900,900);
  // TH2D *hEvsFiber = (TH2D*) file->Get("EvsFiber");
  // hEvsFiber->Draw("colz");

  char *hstname[3]={"Hit_XY","Hit_XZ","Hit_YZ"};
  for (int i=0;i<3;i++){
    c_Hit->cd(k*3+i+1);
    TH2F *h2 = (TH2F*) file->Get(hstname[i]);
    h2->Draw("colz");    
//     h2->Rebin2D(2,2);
    gPad->SetLogz(1);
    if (i==0){
      hshowerPosX->SetBinContent(k+1,h2->GetMean(1));
      hshowerPosX->SetBinError(k+1,h2->GetMeanError(1));
      hshowerSizeX->SetBinContent(k+1,h2->GetRMS(1));
      hshowerSizeX->SetBinError(k+1,h2->GetRMSError(1));
      
      hshowerPosY->SetBinContent(k+1,h2->GetMean(2));
      hshowerPosY->SetBinError(k+1,h2->GetMeanError(2));
      hshowerSizeY->SetBinContent(k+1,h2->GetRMS(2));
      hshowerSizeY->SetBinError(k+1,h2->GetRMSError(2));  
    }
    if(i==1){
      hshowerPosZ->SetBinContent(k+1,h2->GetMean(2));
      hshowerPosZ->SetBinError(k+1,h2->GetMeanError(2));
      hshowerSizeZ->SetBinContent(k+1,h2->GetRMS(2));
      hshowerSizeZ->SetBinError(k+1,h2->GetRMSError(2));   
    }
  }

  char bankname[100];
  sprintf(bankname,"ntuple");
  TTree *T = (TTree*) file->Get(bankname);

  const int n=3;
  char *bname[n]={"fiberEdep","ratioEdep","caloEdep"
  // "WEdep",
  // "diffX"
  // "glueEdep"
  // "startOut",
  // "diffX","diffY","diffZ",
  //"caloX","caloY","caloZ"
  };
  
 
  char content[100];
  char condition[100];
  char histname[100];
  for (int i=0;i<n;i++){
    c_Edep->cd(k*3+i+1);
    sprintf(histname,"htemp_%i",k*3+i);  
    sprintf(content,"%s>>%s",bname[i],histname);  
    sprintf(condition,"");
    T->Draw(content,condition,"");
//      gROOT->GetListOfFunctions()->FindObject("stats")
//       TH1F *h1=(TH1F*) gRootDir->GetListOfFunctions()->FindObject("htemp");
    TH1F *htemp = (TH1F*)gDirectory->FindObject(histname);
//     cout << htemp->GetRMS() << " " << htemp->GetMean() << endl;          

      double Mean=htemp->GetMean(),RMS=htemp->GetRMS();
      double MeanError=htemp->GetMeanError(),RMSError=htemp->GetRMSError();
      TF1 *fun=new TF1("fun","gaus(0)",0,100);
      fun->SetParameters(1,Mean,RMS);
      
    if (i==0) {
      htemp->Fit(fun,"","",Mean-3*RMS,Mean+3*RMS);
      double resolution=fabs(fun->GetParameter(2)/fun->GetParameter(1));
      double resolutionError=sqrt((fun->GetParError(2)/fun->GetParameter(2))**2+(fun->GetParError(1)/fun->GetParameter(1))**2)*resolution;      
//       double resolution=RMS/Mean;
//       double resolutionError=sqrt((RMSError/RMS)**2+(MeanError/Mean)**2)*resolution;
//       cout << resolution << " " << resolutionError << endl;
      
      hresolution->SetBinContent(k+1,resolution*100);
      hresolution->SetBinError(k+1,resolutionError*100);

//       TPaveText *pt1 = new TPaveText(0.6,0.7,0.8,0.8,"brNDC");
//       pt1->SetFillColor(kRed);
//       pt1->SetTextAlign(12);    
//       char text[100];
//       sprintf(text,"%f",resolution);
//       pt1->AddText(text);
//       pt1->Draw();
    }
    
    if (i==1) {
//       htemp->Fit(fun,"","",Mean-3*RMS,Mean+3*RMS);
//       hratio->SetBinContent(k+1,fabs(fun->GetParameter(1))*100);
//       hratio->SetBinError(k+1,fun->GetParameter(2)*100);
      hratio->SetBinContent(k+1,Mean*100);
      hratio->SetBinError(k+1,RMS*100);      
    }
    
    if (i==2) {
      hloss->SetBinContent(k+1,(1-Mean/atof(E[k]))*100);
      hloss->SetBinError(k+1,RMS/atof(E[k])*100);
    }
    
  }

}

  TCanvas *c_result = new TCanvas("result","result",900,900);
  c_result->Divide(3,3);
  c_result->cd(1);
  hshowerPosX->Draw("E1");
  c_result->cd(2);
  hshowerPosY->Draw("E1");
  c_result->cd(3);
  hshowerPosZ->Draw("E1");
  c_result->cd(4);
  hshowerSizeX->Draw("E1");
  c_result->cd(5);
  hshowerSizeY->Draw("E1");
  c_result->cd(6);
  hshowerSizeZ->Draw("E1");    
  c_result->cd(7);  
  hresolution->Draw("E1");
  c_result->cd(8);  
  hratio->Draw("E1");
  c_result->cd(9);  
  hloss->Draw("E1");
  
outputfile->Write();
outputfile->Flush();

char picname[100];
sprintf(picname,"Hit_%s.png",part);
c_Hit->SaveAs(picname);
sprintf(picname,"Edep_%s.png",part);
c_Edep->SaveAs(picname);

}
