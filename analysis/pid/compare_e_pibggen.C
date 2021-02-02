#include <iomanip>
#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <string>

#include "TTree.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"

using namespace std;

void compare_e_pibggen(string type,string filename_e,string filename_pi){
   gStyle->SetPalette(kBird);
   gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.04,"xyz"); // size of axis values
  gStyle->SetTitleSize(0.04,"xyz");   
  gStyle->SetTitleSize(0.07,"t");    
   gStyle->SetPaintTextFormat("4.1f");   

   char expname[200];
   double xmin,xmax,ymin,ymax;
    double rej_FA_low,rej_FA_high,rej_LA;    
   if (type=="solid_JPsi_LH2") {
     sprintf(expname, "JPsi");     
     xmin=8;xmax=28;ymin=0.5;ymax=7;
     rej_FA_low=1e-4;
     rej_FA_high=5e-3;     
     rej_LA=5e-3;
   }
   else if (type=="solid_SIDIS_He3") {
     sprintf(expname, "3He");
     xmin=8;xmax=24;ymin=1;ymax=7;     
     rej_FA_low=1e-4;
     rej_FA_high=5e-3;     
     rej_LA=5e-3;     
   }
   else if (type=="solid_PVDIS_LD2") {
     sprintf(expname, "LD");
     xmin=22;xmax=35;ymin=1.5;ymax=5;
     rej_FA_low=1e-4;
     rej_FA_high=5e-3;     
   }
   else {
     cout << "unknown type" << endl;
     return;
  }
  
//   cout << xmin << " " << xmax << " " << ymin << " " << ymax << " " << endl;

   //TFile *file_e=new TFile("/work/halla/solid/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/rate_solid_PVDIS_LD2_eDIS_1e6.root");
   // TFile *file_e=new TFile("/work/halla/solid/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/rate_solid_PVDIS_LD2_eDIS_50GeV_1e6.root");
   TFile *file_e=new TFile(filename_e.c_str());
   TTree *T_e = (TTree*) file_e->Get("T");

   TCanvas *c_e = new TCanvas("e","e",1800,1000);
   c_e->cd(1);
//    gPad->SetLogz();
//    T_e->Draw("sqrt(px*px+py*py+pz*pz):theta>>h_e(100,0,5,100,0,20)","rate*(W<3&&x>0.35&&theta/3.1415926*180>22&&theta/3.1415926*180<35)","colz");    
   T_e->Draw("sqrt(px*px+py*py+pz*pz):theta>>h_e(20,5,45,20,0,10)","rate/1e3","text colz");       
   TH2F *h_e = (TH2F*)gPad->GetPrimitive("h_e");
   h_e->SetTitle("e^{-} rate (kHz);#theta (deg);P (GeV/c)");      
//    h_e->GetXaxis()->SetRangeUser(xmin,xmax);
//    h_e->GetYaxis()->SetRangeUser(ymin,ymax);
   c_e->SaveAs(Form("%s_rate_e.pdf",type.c_str()));     
   {
   int bin,binxmin,binymin,binzmin,binxmax,binymax,binzmax;  
   bin=h_e->FindBin(xmin,ymin);  
   h_e->GetBinXYZ(bin,binxmin,binymin,binzmin);   
   bin=h_e->FindBin(xmax,ymax);  
   h_e->GetBinXYZ(bin,binxmax,binymax,binzmax);   
   cout << "e- rate in kHz "<< h_e->Integral(binxmin,binxmax,binymin,binymax) << endl;   
   }   
   
//    T_e->Draw("Q2:W>>h_e(100,0,5,100,0,20)","rate*(W<3&&x>0.35&&theta/3.1415926*180>22&&theta/3.1415926*180<35)","colz"); 
   // T_e->Draw("Q2:W>>h_e(120,0,12,100,0,100)","rate*(W>3&&Q2>1&&Q2>0.2&&theta/3.1415926*180<50)","colz"); 
//    h_e->SetTitle("e^- rate;W(GeV);Q2(GeV^{2})");
   // T_e->Draw("Q2:W>>h_e(120,0,12,100,0,100)","rate*(W>3&&Q2>1&&Q2>0.2&&theta/3.1415926*180<50)","colz"); 
   // h_e->SetTitle("eDIS rate;W(GeV);Q2(GeV^{2})");
   // T_e->Draw("Q2:x>>h_e(100,0,1,100,0,100)","rate*(W>3&&Q2>1&&Q2>0.2&&theta/3.1415926*180<50)","colz"); 
   // h_e->SetTitle("eDIS rate;x;Q2(GeV^{2})");
//    h_e->SetMaximum(1e13);
//    h_e->SetMinimum(1e-3);

   //get pi
   TH2F *h_pi=new TH2F("pi","pi",20,5,45,20,0,10);
   
   int filecount;
    if (type=="solid_JPsi_LH2" || type=="solid_SIDIS_He3" ) filecount=1000;   
    else if (type=="solid_PVDIS_LD2") filecount=1800;   
//     filecount=10;    
    
   for(int i=0; i<filecount;i++){
      string filename_pi_name=Form("%s/LUND/hallD_pion_m_%s_1k_%i.lund",filename_pi.c_str(),expname,i+1);
      ifstream input(filename_pi_name.c_str());
      if (input.good()) {} //cout << "open file " << filename_pi_name << " OK" << "\r";
      else {cout << "can't open the file" << endl; return;}

      // reads and discard the first 13 lines of text
//       char textline[200];
//       for (int k = 0; k<13; k++) input.getline(textline,200);

      double  header[10];
      double  particles[14];

      for (int j = 0; j<1000; j++) {
	      input >> header[0] >> header[1] >> header[2] >> header[3] >> header[4] >> header[5] >> header[6] >> header[7] >> header[8] >> header[9];
	      input >> particles[0] >> particles[1] >> particles[2] >> particles[3] >> particles[4] >> particles[5] >> particles[6] >> particles[7] >> particles[8] >> particles[9] >> particles[10] >> particles[11] >> particles[12] >> particles[13];
	      
// 	      cout << header[9] << " " << particles[6] << " " << particles[7] << " " << particles[8] << endl;
	      double rate=header[9];
	      double px=particles[6],py=particles[7],pz=particles[8];	      
	      double p=sqrt(px*px+py*py+pz*pz);
	      double theta=acos(fabs(pz/p))/3.1416*180;
	      
	      h_pi->Fill(theta,p,rate);
      }
   }
   
   cout << "pi bggen files " << filecount << endl;

   h_pi->Scale(1e-3/filecount);  //in kHz and normalized by filecount
   
   TCanvas *c_pi = new TCanvas("pi","pi",1800,1000);
   c_pi->cd(1);
//    gPad->SetLogz();
   h_pi->SetTitle("#pi^{-} rate (kHz);#theta (deg);P (GeV/c)");      
//    h_pi->GetXaxis()->SetRangeUser(xmin,xmax);   
//    h_pi->GetYaxis()->SetRangeUser(ymin,ymax);     
   h_pi->Draw("text colz");
//    h_pi->SetMaximum(1e13);
//    h_pi->SetMinimum(1e-3);
   c_pi->SaveAs(Form("%s_rate_pi.pdf",type.c_str()));         
   {
   int bin,binxmin,binymin,binzmin,binxmax,binymax,binzmax;  
   bin=h_pi->FindBin(xmin,ymin);  
   h_pi->GetBinXYZ(bin,binxmin,binymin,binzmin);   
   bin=h_pi->FindBin(xmax,ymax);  
   h_pi->GetBinXYZ(bin,binxmax,binymax,binzmax);   
   cout << "pi- rate in kHz "<< h_pi->Integral(binxmin,binxmax,binymin,binymax) << endl;   
   }   

      TCanvas *c_pie = new TCanvas("pie","pie",1800,1000);
      TH2F *h_pie=(TH2F*) h_pi->Clone();      
      h_pie->Divide(h_e);        
      h_pie->SetTitle("#pi^{-}/e^{-} ratio;#theta (deg);P (GeV/c)");      
//       h_pie->GetXaxis()->SetRangeUser(xmin,xmax);   
      h_pie->Draw("text colz");
      c_pie->SaveAs(Form("%s_ratio_pie.pdf",type.c_str())); 
      
   gStyle->SetPaintTextFormat("2.2f");    

      //rejection       
      TCanvas *c_pie_rej = new TCanvas("pie_rej","pie_rej",1800,1000);
      
      TH2F *h_pie_rej=(TH2F*) h_pie->Clone();             
	  for (int i = 1; i<=20; i++) {	
	    for (int j = 1; j<=20; j++) {
	      double x=h_pie_rej->GetXaxis()->GetBinCenter(i);
	      double y=h_pie_rej->GetYaxis()->GetBinCenter(j);	

	      if (type=="solid_JPsi_LH2" || type=="solid_SIDIS_He3" ) {		
		if (x <15) {//FA
		  if (y <4) h_pie_rej->SetBinContent(i,j,h_pie_rej->GetBinContent(i,j)*rej_FA_low);
		  else  h_pie_rej->SetBinContent(i,j,h_pie_rej->GetBinContent(i,j)*rej_FA_high);
		}
		else h_pie_rej->SetBinContent(i,j,h_pie_rej->GetBinContent(i,j)*rej_LA); //LA	      
	      }
	      else if (type=="solid_PVDIS_LD2") {      
		  if (y <4) h_pie_rej->SetBinContent(i,j,h_pie_rej->GetBinContent(i,j)*rej_FA_low);
		  else  h_pie_rej->SetBinContent(i,j,h_pie_rej->GetBinContent(i,j)*rej_FA_high); 
	      }
	      
	    }
	  }
	  
      //clean up
      	  for (int i = 1; i<=20; i++) {	
	    for (int j = 1; j<=20; j++) {
	      double x=h_pie_rej->GetXaxis()->GetBinCenter(i);
	      double y=h_pie_rej->GetYaxis()->GetBinCenter(j);	
	      
	      if (type=="solid_SIDIS_He3" ) {  	      
		if (x==16 && y>6) h_pie_rej->SetBinContent(i,j,0); // cleanup
		if (x==18 && y>5) h_pie_rej->SetBinContent(i,j,0); // cleanup	      
	      }
	      else if (type=="solid_PVDIS_LD2") {
		if (x==24 && y>4.5) h_pie_rej->SetBinContent(i,j,0); // cleanup	      		
	      }
	    }
	  }

      h_pie_rej->Scale(1e2); //percent

      //change text size
      if (type=="solid_JPsi_LH2" || type=="solid_SIDIS_He3" ) h_pie_rej->SetMarkerSize(1);
      else if (type=="solid_PVDIS_LD2") h_pie_rej->SetMarkerSize(2);      

      h_pie_rej->SetTitle("#pi^{-}/e^{-} ratio (\%) after #pi^{-} rejection;#theta (deg);P (GeV/c)");      
      h_pie_rej->GetXaxis()->SetRangeUser(xmin,xmax);   
      h_pie_rej->GetYaxis()->SetRangeUser(ymin,ymax);                       
      h_pie_rej->Draw("text colz");

// lines in P vs theta at 11GeV beam
  TF1 *W_2=new TF1("W_2","(0.938*0.938-4+2*0.938*11)/(2*0.938+4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180);
   W_2->SetLineColor(kOrange);
  TF1 *W_3=new TF1("W_3","(0.938*0.938-9+2*0.938*11)/(2*0.938+4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180);
   W_3->SetLineColor(kOrange);
   W_3->SetLineStyle(2);      
   TF1 *Q2_1=new TF1("Q2_1","1./(4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180); 
   Q2_1->SetLineColor(kRed);
   TF1 *Q2_2=new TF1("Q2_2","2./(4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180); 
   Q2_2->SetLineColor(kRed);
   Q2_2->SetLineStyle(2);         
   TF1 *x_35=new TF1("x_35","(0.35*2*0.938*11)/(0.35*2*0.938+4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180); 
   x_35->SetLineColor(kRed);
   TF1 *x_55=new TF1("x_55","(0.55*2*0.938*11)/(0.55*2*0.938+4*11*sin(x/180.*3.1415926/2)*sin(x/180.*3.1415926/2))",0,180); 
   x_55->SetLineColor(kRed);
   x_55->SetLineStyle(2);
   
  {
   TLegend* leg = new TLegend(0.8, 0.7, 0.9, 0.9);      
   if (type=="solid_SIDIS_He3" ) {
    W_2->Draw("same");
    leg->AddEntry(W_2, "W=2","l");    
    W_3->Draw("same");
    leg->AddEntry(W_3, "W=3","l");    
    Q2_1->Draw("same");
    leg->AddEntry(Q2_1, "Q^{2}=1","l");        
    Q2_2->Draw("same");
    leg->AddEntry(Q2_2, "Q^{2}=2","l");        
    leg->Draw();    
    
    TLine *line_p = new TLine(15,3.5,25,3.5);
    line_p->SetLineWidth(6);
    line_p->SetLineColor(kGreen);        
    line_p->Draw("same");
    TLine *line_theta = new TLine(15,1,15,3.5);    
    line_theta->SetLineWidth(6);
    line_theta->SetLineColor(kGreen);        
    line_theta->Draw("same");    
   }
   else if (type=="solid_PVDIS_LD2") {      
    W_2->Draw("same");
    leg->AddEntry(W_2, "W=2","l");    
    W_3->Draw("same");
    leg->AddEntry(W_3, "W=3","l");    
    x_35->Draw("same");
    leg->AddEntry(x_35, "x=0.35","l");        
    x_55->Draw("same");
    leg->AddEntry(x_55, "x=0.55","l");        
    leg->Draw();    
   }
   }
   
    //physics cut   
      c_pie_rej->SaveAs(Form("%s_ratio_pie_rej.pdf",type.c_str()));
  
   TCanvas *c_pie_rej_cut = new TCanvas("pie_rej_cut","pie_rej_cut",1800,1000);  
    TH2F *h_pie_rej_cut=(TH2F*) h_pie_rej->Clone();              

    for (int i = 1; i<=20; i++) {	
	    for (int j = 1; j<=20; j++) {
	      double x=h_pie_rej_cut->GetXaxis()->GetBinCenter(i);
	      double y=h_pie_rej_cut->GetYaxis()->GetBinCenter(j);	
	      
	      if (type=="solid_SIDIS_He3" ) {  	      
		if (x>15 && y<3.5) h_pie_rej_cut->SetBinContent(i,j,0); // cut LA at 3.5GeV
		if (x<9 && y<3.5) h_pie_rej_cut->SetBinContent(i,j,0); // cut FA Q2=1
		if (x<11 && y<2.5) h_pie_rej_cut->SetBinContent(i,j,0); // cut FA Q2=1
		if (x<13 && y<1.5) h_pie_rej_cut->SetBinContent(i,j,0); // cut FA Q2=1 
	      }
// 	      if (type=="solid_JPsi_LH2" ) {  	      
// 		if (y<2.5) h_pie_rej_cut->SetBinContent(i,j,0); // for decay lepton 
// 	      }
// 	      if (type=="solid_PVDIS_LD2" ) {  	      
// 		if (y<1.5) h_pie_rej_cut->SetBinContent(i,j,0); 
// 	      }
	      
	    }
	  }
   h_pie_rej_cut->Draw("text colz");


   {
   TLegend* leg = new TLegend(0.8, 0.7, 0.9, 0.9);      
   if (type=="solid_SIDIS_He3" ) {
    W_2->Draw("same");
    leg->AddEntry(W_2, "W=2","l");    
    W_3->Draw("same");
    leg->AddEntry(W_3, "W=3","l");    
    Q2_1->Draw("same");
    leg->AddEntry(Q2_1, "Q^{2}=1","l");        
    Q2_2->Draw("same");
    leg->AddEntry(Q2_2, "Q^{2}=2","l");        
    leg->Draw();    

    TLine *line_p = new TLine(15,3.5,25,3.5);    
    line_p->SetLineWidth(6);
    line_p->SetLineColor(kGreen);        
    line_p->Draw("same");
    TLine *line_theta = new TLine(15,1,15,3.5);    
    line_theta->SetLineWidth(6);
    line_theta->SetLineColor(kGreen);        
    line_theta->Draw("same");     
   }
   else if (type=="solid_PVDIS_LD2") {      
    W_2->Draw("same");
    leg->AddEntry(W_2, "W=2","l");    
    W_3->Draw("same");
    leg->AddEntry(W_3, "W=3","l");    
    x_35->Draw("same");
    leg->AddEntry(x_35, "x=0.35","l");        
    x_55->Draw("same");
    leg->AddEntry(x_55, "x=0.55","l");        
    leg->Draw();    
   }
   }
  
    c_pie_rej_cut->SaveAs(Form("%s_ratio_pie_rej_cut.pdf",type.c_str()));
}
