void plot_crosssection(){
TCanvas *c_crossection = new TCanvas("crossection","crossection",1000,800);
gPad->SetLogy();
TH1F *h=new TH1F("JPsi","JPsi elastic crosssection;E_{#gamma} (GeV);#sigma (nb)",100,7.5,22);
h->SetMaximum(1e2);
h->SetMinimum(1e-4);
h->Draw();
TF1 *f1 = new TF1("f1","fun_2g(x)",8,22);
f1->Draw("same");
TF1 *f2 = new TF1("f2","fun_3g(x)",8,22);
f2->SetLineStyle(2);
f2->Draw("same");

TCanvas *c_decay = new TCanvas("decay","decay",1000,800);
// TF1 *f3=new TF1("f","3./4./3.1415926*(0.5 + 0.5*cos(x/180*3.1415926)*cos(x/180*3.1415926))",0,180);
TF1 *f3=new TF1("f","3./2.*(1 - cos(x)*cos(x))",0,3.1415926);
// cout << "integral " << f3->Integral(0,3.1415926) << endl;
f3->Draw();
}

// Double_t fun_2g(Double_t x, Double_t){
Double_t fun_2g(Double_t x){
  x=sqrt((x+0.938)*(x+0.938)-x*x);   //convert from E_gamma to W  
  Double_t N2g = 7.5671e3;
  Double_t v = 1./16/3.1415926;
  Double_t R = 1;
  Double_t M = 3.097;
  Double_t xp = (2*0.938*M+M*M)/(x*x-0.938*0.938);
//   Double_t t=0.1;  
  Double_t t=-1*t0lim(0,0.938, M, 0.938, x*x);
//   cout << t << endl;
  Double_t ff = exp(-1.13 * t);

  Double_t result = N2g*v/R/R/M/M*pow(1-xp,2)*ff;
  
  result = result / 1.13;    //total crossection is differential crossection at t=0 and divide by slope
  cout << result << endl;  
  return result;
}

// Double_t fun_3g(Double_t x, Double_t){
Double_t fun_3g(Double_t x){
  x=sqrt((x+0.938)*(x+0.938)-x*x);  //convert from E_gamma to W
  Double_t N3g = 2.894e3;
  Double_t v = 1./16/3.1415926;
  Double_t R = 1;
  Double_t M = 3.097; 
  Double_t xp = (2*0.938*M+M*M)/(x*x-0.938*0.938);
  Double_t t=0.1;    
//   Double_t t=-1*t0lim(0,0.938, M, 0.938, x*x);  
  Double_t ff = exp(-1.13 * t);

  Double_t result = N3g*v/R/R/R/R/M/M/M/M*pow(1-xp,0)*ff;
  
  result = result / 1.13; //total crossection is differential crossection at t=0 and divide by slope
  
  return result;
}

Float_t t0lim(Float_t m1, Float_t m2,Float_t m3, Float_t m4,Float_t s)
{
  Float_t t1,t2,t3,t4;
  
  if (m1>=0){
     t1 = (m1*m1 - m3*m3 - m2*m2 + m4*m4)/(2*sqrt(s));
     t2 = (s + m1*m1 - m2*m2)/(2*sqrt(s));    //E1cm
    //if (t2 < 0.) {return 1.;}
    t2 = sqrt(t2*t2 - m1*m1);                        //p1cm
     t3 = (s + m3*m3 - m4*m4)/(2*sqrt(s));    //E3cm
    //if (t3 < 0.) {return 1.;}
    t3 = sqrt(t3*t3 - m3*m3);                        //p3cm
    t4 = t2 - t3;                            //p1cm-p3cm
  }else{
     t1 = (-m1*m1 - m3*m3 - m2*m2 + m4*m4)/(2*sqrt(s));
     t2 = (s - m1*m1 - m2*m2)/(2*sqrt(s));    //E1cm
    //if (t2 < 0.) {return 1.;}
    t2 = sqrt(t2*t2 + m1*m1);                        //p1cm
     t3 = (s + m3*m3 - m4*m4)/(2*sqrt(s));    //E3cm
    //if (t3 < 0.) {return 1.;}
    t3 = sqrt(t3*t3 - m3*m3);                        //p3cm
     t4 = t2 - t3;                            //p1cm-p3cm
  }
  return  t1*t1 - t4*t4;
}
