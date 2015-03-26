{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptFit(11111);
// gStyle->SetPadRightMargin(0.32);

   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

//    c1->SetFillColor(42);
//    c1->SetGrid();

   const Int_t n = 9;
   Double_t E[n]={0.2,0.5,1,1.5,2,3.5,5,8,11};
   Double_t E_error[n]={0,0,0,0,0,0,0,0,0};   
   
   //all value in MeV
   Double_t Mean[n]={4.66728e+01,1.27190e+02,2.59957e+02,3.92702e+02,5.25039e+02,9.21626e+02,1.31626e+03,2.10454e+03,2.89340e+03};
   Double_t Mean_error[n]={2.86274e-01,3.82772e-01,4.79628e-01,5.81373e-01,6.39520e-01,8.01087e-01,8.74600e-01,1.20359e+00,1.41368e+00};
   Double_t Sigma[n]={8.99890e+00,1.19100e+01,1.51065e+01,1.79508e+01,1.97789e+01,2.50124e+01,2.74955e+01,3.66417e+01,4.35832e+01};
   Double_t Sigma_error[n]={2.03032e-01,2.92724e-01,3.34968e-01,4.17188e-01,4.58145e-01,5.96691e-01,6.76271e-01,8.84596e-01,1.05733e+00};
   Double_t res[n];
   Double_t res_error[n];   

   for (Int_t i=0;i<n;i++) {
     res[i]=Sigma[i]/1e3/E[i];
     res_error[i]=Sigma_error[i]/1e3/E[i]; 
//      res_error[i]=sqrt(1000.)/E[i];      
//      printf(" i %i %f %f \n",i,x[i],y[i]);
   }
   gr = new TGraphErrors(n,E,res,E_error,res_error);
//    gr->SetLineColor(2);
//    gr->SetLineWidth(4);
//    gr->SetMarkerColor(4);
   gr->SetMarkerStyle(1);
   gr->SetTitle("EC energy resolution");
   gr->GetXaxis()->SetTitle("E");
   gr->GetYaxis()->SetTitle("#sigma/E");
   gr->Draw("AP");
   
   TF1 *fun = new TF1("fun","sqrt(pow([0]/sqrt(x),2)+pow([1],2))",0,12);
   gr->Fit("fun");
   
   // TCanvas::Update() draws the frame, after which one can change it
//    c1->Update();
//    c1->GetFrame()->SetFillColor(21);
//    c1->GetFrame()->SetBorderSize(12);
//    c1->Modified();
}