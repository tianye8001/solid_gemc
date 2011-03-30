void resolution(){
  TFile *file = new TFile("./optics_0p2mm.root");
  TTree *T = file->Get("T");
  
  TString temp,temp1;
  TF1 *f1 = new TF1("m1","gaus");
  TH1F **h1 = new TH1F*[20];
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(5,4);
  Double_t par[5];
  for (Int_t i=0;i!=20;i++){
    c1->cd(i+1);
    Float_t mom_min = 0.5*(i+0.1);
    Float_t mom_max = mom_min+0.5;
    temp.Form("h1_%d",i);
    //momentum
    // h1[i] = new TH1F(temp,temp,100,-0.2,0.2);
//     temp1.Form("p_e>%f&&p_e<%f",mom_min,mom_max);
//     T->Project(temp,"(recon_p-p_e)/p_e",temp1);
//     h1[i]->Draw();
//     h1[i]->Fit(f1,"Q","",-0.1,0.1);
    
// //polar angle
//     h1[i] = new TH1F(temp,temp,100,-0.3,0.3);
//     temp1.Form("p_e>%f&&p_e<%f",mom_min,mom_max);
//     T->Project(temp,"theta_e-recon_theta1",temp1);
//     h1[i]->Draw(); 
//     if (i<4){
//       h1[i]->Fit(f1,"Q","",-0.2,0.2);
//     }else{
//       h1[i]->Fit(f1,"Q","",-0.1,0.1);
//     }
//     f1->GetParameters(par);

    // //azimuthal angle
//     h1[i] = new TH1F(temp,temp,100,-2.0,2.0);
//     temp1.Form("p_e>%f&&p_e<%f",mom_min,mom_max);
//     T->Project(temp,"phi_e-recon_phi",temp1);
//     h1[i]->Draw(); 
//       if (i<4){
//       h1[i]->Fit(f1,"Q","",-1.8,1.8);
//       }else{
// 	h1[i]->Fit(f1,"Q","",1.,1.);
//       }
//       f1->GetParameters(par);

    //vertex z
    h1[i] = new TH1F(temp,temp,100,-20,20);
    temp1.Form("p_e>%f&&p_e<%f",mom_min,mom_max);
    T->Project(temp,"vertexz-recon_vertexz",temp1);
    h1[i]->Draw(); 
    if (i<5){
      h1[i]->Fit(f1,"Q","",-15.,15.);
    }else{
      h1[i]->Fit(f1,"Q","",-5.,5.);
    }
    f1->GetParameters(par);
    
    cout << (mom_min+mom_max)/2. << "\t" << par[2] << endl;
  }
}
