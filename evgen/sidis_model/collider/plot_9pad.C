#include "plot3.C"
//#include "plot_data.C"
// #include "plot_cal3.C"

void plot_9pad(Int_t target_flag = 1,Int_t particle_flag=1){
  gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.1,"Y");
  gStyle->SetTitleSize(0.15,"Y");
  gStyle->SetTitleOffset(0.7,"Y");
  gStyle->SetTitleOffset(0.8,"X");
  gStyle->SetLabelSize(0.1,"X");
  gStyle->SetTitleSize(0.15,"X"); 
  //gStyle->SetPadBorderMode(0);


  TCanvas *c1 = new TCanvas("c1","c1",900,900);
  c1->SetFillColor(10);
  Double_t XW  = 0.3;          // Pad Width
  Int_t    Nx = 3;            // Number of pads along X
  Double_t Xm = (1-(Nx*XW))/2; // X Margin
  Double_t Xdw = (XW*0.07);
  Double_t YW  = 0.3;          // Pad Width
  Int_t    Ny = 3;            // Number of pads along Y
  Double_t Ym = (1-(Ny*YW))/2; // Y Margin
  Double_t Ydw = (YW*0.07);
  
  TPad *p[10];
  p[1] = new TPad("p1", "p1", Xm, Ym+2*YW-Ydw, Xm+XW+Xdw, Ym+3*YW, 0, 0, 0);
  p[1]->SetLeftMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[1]->SetRightMargin(0);
  p[1]->SetTopMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[1]->SetBottomMargin(0);
  p[1]->Draw();

  p[2] = new TPad("p2", "p2", Xm+XW+Xdw, Ym+2*YW-Ydw, Xm+2*XW-Xdw, Ym+3*YW, 0, 0, 0);
  p[2]->SetLeftMargin(0);
  p[2]->SetRightMargin(0);
  p[2]->SetTopMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[2]->SetBottomMargin(0);
  p[2]->Draw();

  p[3] = new TPad("p3", "p3", Xm+2*XW-Xdw, Ym+2*YW-Ydw, Xm+3*XW, Ym+3*YW, 0, 0, 0);
  p[3]->SetLeftMargin(0);
  p[3]->SetRightMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[3]->SetTopMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[3]->SetBottomMargin(0);
  p[3]->Draw();

  p[4] = new TPad("p4", "p4", Xm, Ym+YW+Ydw, Xm+XW+Xdw, Ym+2*YW-Ydw, 0, 0, 0);
  p[4]->SetLeftMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[4]->SetRightMargin(0);
  p[4]->SetTopMargin(0);
  p[4]->SetBottomMargin(0);
  p[4]->Draw();
  
  p[5] = new TPad("p5", "p5", Xm+XW+Xdw, Ym+YW+Ydw, Xm+2*XW-Xdw, Ym+2*YW-Ydw, 0, 0, 0);
  p[5]->SetLeftMargin(0);
  p[5]->SetRightMargin(0);
  p[5]->SetTopMargin(0);
  p[5]->SetBottomMargin(0);
  p[5]->Draw();
  
  p[6] = new TPad("p6", "p6", Xm+2*XW-Xdw, Ym+YW+Ydw, Xm+3*XW, Ym+2*YW-Ydw, 0, 0, 0);
  p[6]->SetLeftMargin(0);
  p[6]->SetRightMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[6]->SetTopMargin(0);
  p[6]->SetBottomMargin(0);
  p[6]->Draw();
  
  p[7] = new TPad("p7", "p7", Xm, Ym, Xm+XW+Xdw, Ym+YW+Ydw, 0, 0, 0);
  p[7]->SetLeftMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[7]->SetRightMargin(0);
  p[7]->SetTopMargin(0);
  p[7]->SetBottomMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[7]->Draw();
  
  p[8] = new TPad("p8", "p8", Xm+XW+Xdw, Ym, Xm+2*XW-Xdw, Ym+YW+Ydw, 0, 0, 0);
  p[8]->SetLeftMargin(0);
  p[8]->SetRightMargin(0);
  p[8]->SetTopMargin(0);
  p[8]->SetBottomMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[8]->Draw();
  
  p[9] = new TPad("p9", "p9", Xm+2*XW-Xdw, Ym, Xm+3*XW, Ym+YW+Ydw, 0, 0, 0);
  p[9]->SetLeftMargin(0);
  p[9]->SetRightMargin(1-(XW-2*Xdw)/(XW+Xdw));
  p[9]->SetTopMargin(0);
  p[9]->SetBottomMargin(1-(YW-2*Ydw)/(YW+Ydw));
  p[9]->Draw();
    
  Double_t zero_point = 10.;//0.;
  Double_t llimit = -0.12;
  Double_t hlimit = 0.17;
  Double_t scale = 0.01;//25;
  Double_t xllimit = -0.1;
  Double_t xhlimit = 0.7;
  
  //  TLine *l1 = new TLine(-4.3,zero_point,0.,zero_point);
  
  Double_t x[4]= {-3.6,-3.6,0.1,0.1};
  Double_t y[4]= {-0.1,-0.1,2.6.2.6};


  TH2F *h1 = new TH2F("h1","h1",100,xllimit,xhlimit,100,llimit,hlimit);
  h1->SetXTitle("");
  h1->SetYTitle("");
  h1->SetTitle("");
  h1->GetXaxis()->SetNdivisions(506);
  h1->GetYaxis()->SetNdivisions(506);

  h1->GetYaxis()->SetLabelSize(0.01);
  h1->GetXaxis()->SetLabelSize(0.01);
  h1->GetXaxis()->SetAxisColor(10);
  h1->GetXaxis()->SetLabelColor(0);
  h1->GetYaxis()->SetAxisColor(10);
  h1->GetYaxis()->SetLabelColor(0);
      
  TGaxis *gaxis = new TGaxis(xhlimit,llimit,xhlimit,hlimit,llimit/scale+zero_point,hlimit/scale+zero_point,504,"+L"); //y axis right
  gaxis->SetLabelSize(0.1);
  gaxis->SetTitleOffset(0.85);
  gaxis->SetTitleSize(0.1);
  gaxis->SetTitle("Q^{2} (GeV^{2})");
  gaxis->CenterTitle();
  
  TGaxis *gaxis2 = new TGaxis(xllimit,llimit,xhlimit,llimit,xllimit,xhlimit,50510,""); //x axis
  gaxis2->SetNdivisions(506);
  gaxis2->SetLabelSize(0.1);
  gaxis2->SetTitleOffset(1.);
  gaxis2->SetTitleSize(0.1);
  gaxis2->SetTitle("x");
  gaxis2->CenterTitle();
  
  TGaxis *gaxis1 = new TGaxis(xhlimit,llimit,xhlimit,hlimit,llimit/scale+zero_point,hlimit/scale+zero_point,504,"+L"); //y axis right
  gaxis1->SetLabelOffset(1);
  gaxis1->SetLabelSize(0.05);
  gaxis1->SetTickSize(0.03);
  gaxis1->SetGridLength(0);
  gaxis1->SetTitleOffset(1.);
  gaxis1->SetTitleSize(0.);
  gaxis1->SetTitleColor(1);
  gaxis1->SetTitleFont(62);
 
  
  TGaxis *gaxis3 = new TGaxis(xllimit,llimit,xhlimit,llimit,xllimit,xhlimit,50510,""); //x axis
  gaxis3->SetNdivisions(506);
  gaxis3->SetLabelOffset(1);
  gaxis3->SetLabelSize(0.02);
  gaxis3->SetTickSize(0.03);
  gaxis3->SetGridLength(0);
  gaxis3->SetTitleOffset(1.);
  gaxis3->SetTitleSize(0.07);
  gaxis3->SetTitleColor(1);
  gaxis3->SetTitleFont(62);
  //  gaxis3->SetName("axis4");

  TGaxis *axis = new TGaxis(xllimit,llimit,xllimit,hlimit,llimit,hlimit,50510,"");
    if (particle_flag==1){
      axis->SetTitle("Asymmetry #pi^{+}");
	  axis->CenterTitle();
    }else{
      axis->SetTitle("Asymmetry #pi^{-}");
	  axis->CenterTitle();
    }
    axis->SetTitleOffset(1.1);
    axis->SetTitleSize(0.08);
    axis->SetLabelSize(0.08); 
    axis->SetNdivisions(506);

    TGaxis *axis1 = new TGaxis(xllimit,llimit,xllimit,hlimit,llimit,hlimit,50510,"");
    axis1->SetTitle();
    axis1->SetTitleOffset(0.8);
    axis1->SetTitleSize(0.1);
    axis1->SetLabelSize(0.1); 
    axis1->SetLabelOffset(1); 
    axis1->SetNdivisions(506);
  
  Int_t i1,j1;
  for (Int_t i=0;i!=3;i++){
    for (Int_t j=0;j!=3;j++){
	  p[3*i+j+1]->cd();
	  h1->Draw();
      if((i==1&&j==0)||(i==2&&j==1)){axis->Draw();gaxis2->Draw();}
	  else {axis1->Draw();gaxis3->Draw();}

      if(j==2) 	{
	if(i==1) gaxis->Draw();
	else{
	  gaxis1->Draw();
	}
      }
       // l1->Draw("same");
      
      //cout << "label: " << 8*i+j+1 << endl;

      i1 = i*2;
      j1 = j*4;

//      if (i1+1==1&&j1+3==11)
//      {

      

	plot(particle_flag,target_flag,2,1,j1+3,i1+1,1,scale,zero_point);
	plot(particle_flag,target_flag,2,2,j1+3,i1+1,1,scale,zero_point);

	//	if(i==1&&j==1){
	  plot_solid(j1+3,i1+1,8,scale,zero_point);

	  plot_12(particle_flag,1,j1+1,i1+1,9,scale,zero_point);
	  plot_12(particle_flag,2,j1+1,i1+1,9,scale,zero_point);
	  plot_12(particle_flag,3,j1+1,i1+1,9,scale,zero_point);
	  plot_12(particle_flag,4,j1+1,i1+1,9,scale,zero_point);
	  plot_12(particle_flag,5,j1+1,i1+1,9,scale,zero_point);
	  plot_12(particle_flag,6,j1+1,i1+1,9,scale,zero_point);

	  //	}

//	  }

// 	int ncount = 1;
// 	double logx[1] = {2.}, logQ2[1] = {2.};
// 	TGraph *g1 = new TGraphErrors(ncount,logx,logQ2);
// 	g1->SetMarkerStyle(20);
// 	g1->SetMarkerColor(2);

// 	TGraph *g2 = new TGraphErrors(ncount,logx,logQ2);
// 	g2->SetMarkerStyle(22);
// 	g2->SetMarkerColor(1);

// 	TGraph *g3 = new TGraphErrors(ncount,logx,logQ2);
// 	g3->SetMarkerStyle(21);
// 	g3->SetMarkerColor(4);

// 	  if (i==1&&j==1)
//   {
// 	  TLegend *le1 = new TLegend(0.08,0.55,0.4,0.93);
// 	  le1->SetHeader("#sqrt{s} (GeV)");
//   le1->SetLineColor(10);
//   le1->SetTextSize(0.1);
//   le1->SetFillColor(10);
//   le1->SetShadowColor(10);
//   le1->AddEntry(g1,"15","p");
//   le1->AddEntry(g2,"45","p");
//   le1->AddEntry(g3,"140","p");
// //  le1->AddEntry(h10,"HERMES p #pi^{+}","p");
//   le1->Draw("same");
//   }

/*	if(i==1&&j==1){
	  plot_data(zero_point, scale);
	}
*/
    }
  }

  c1->SaveAs("a.eps");
}
