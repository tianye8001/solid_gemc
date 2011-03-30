void fit(){
  Float_t par[10];
  T->Draw("recon_theta1-theta_e:p_e/10.>>h1","p_e<2.");
  TProfile *fp = (TProfile*)h1->ProfileX();
  // TF1 *f1 = new TF1("m1","pol2",0.5,1.);
  TF1 *f2 = new TF1("m2","pol3",0.07,0.2);
  // fp->Fit(f1,"","",0.5,1.);
//   TF1 *f3 = new TF1("m3","pol3",0.2,0.5);
//   fp->Fit(f3,"","",0.2,0.5);
  fp->Fit(f2,"","",0.07,0.2);
  //fp->GetParameters(par);
  //cout << par[1] << endl;
  TString temp;
  //temp.Form("recon_theta1-theta_e-(9.30697e+00*exp(-2.70353e+01*p_e/10.+5.50657e+01*pow(p_e/10.,2)+-5.28952e+01*pow(p_e/10.,3)+1.92142e+01*pow(p_e/10.,4)))");
  //T->Draw(temp);
 
}
