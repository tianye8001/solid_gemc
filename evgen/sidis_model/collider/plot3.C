void plot(Int_t particle_flag,Int_t target_fag,Int_t energy_flag, Int_t Q2_flag, Int_t z_flag, Int_t pt_flag,Int_t color,Double_t scale, 
	Double_t zero_point){

//   gStyle->SetTextSize(0.07);
  TString filename;
  filename.Form("../results/%d_%d_%d_%d_%d_%d.dat", particle_flag, target_fag, energy_flag,  Q2_flag,  z_flag,  pt_flag);
  ifstream infile(filename);
  Int_t count1,count2;
  Double_t Q2[5000],x[5000],z[5000],pt[5000],y[5000],asy[5000],coverage[5000],coef[3][5000];
  Double_t Q2[5000],x[5000];
  infile >> count1 >> count2;
  //cout <<"start " << filename << endl;
  //cout << count1 << "\t" << count2 << endl;
//   cout << z_flag << "\t" << pt_flag << endl;
  Double_t temp;
  Int_t ncount=0;


	if(energy_flag==2&&Q2_flag==2&&z_flag==11&&pt_flag==1) cout << "here!" << endl;
  
  
  for (Int_t i=0;i!=count1;i++){


    for (Int_t j=0;j!=count2;j++){
      infile >> temp >> temp >> Q2[ncount] >> x[ncount] >> z[ncount] >> y[ncount] >> pt[ncount] >> asy[ncount] >> 
		  coverage[ncount] >> coef[0][ncount] >> coef[1][ncount] >> coef[2][ncount];
      if (asy[ncount]>0.&&asy[ncount]<0.05&&coverage[ncount]>6.28/15.&&(coef[0][ncount]+coef[1][ncount]+coef[2][ncount])/3.<3.){ //&&asy[ncount]<0.05
 
// 	asy[ncount] *= (coef[0][ncount]+coef[1][ncount]+coef[2][ncount])/3.; 
	asy[ncount] *= coef[0][ncount]; 
	Q2[ncount] = (Q2[ncount]-zero_point)*scale;
	//	x[ncount] = pow(10,x[ncount]);

	ncount ++;
      }
    }

  }


  TGraphErrors *g1 = new TGraphErrors(ncount,x,Q2,0,asy);
  if(energy_flag==2&&Q2_flag==2&&z_flag==11&&pt_flag==1) cout << ncount << " " << count1 << " " << count2 << endl;
//   }
  if(energy_flag==2&&Q2_flag==2&&z_flag==11&&pt_flag==1) {
	  g1->Draw("*");
	  cout << "draw here" << endl;
  }
  else g1->Draw("*same");
  g1->SetMarkerColor(color);
  if(energy_flag==1||energy_flag==5) g1->SetMarkerStyle(22);
  else if(energy_flag==2) g1->SetMarkerStyle(20);
  else if(energy_flag==4) g1->SetMarkerStyle(21);
  g1->SetMarkerSize(0.6);
  g1->SetLineColor(color);
  infile.close();
  
  TLatex *t1 = new TLatex();
  t1->SetNDC();
  if((pt_flag-1)*0.2!=0.4)t1->SetTextSize(0.04);
  else t1->SetTextSize(0.04*0.321/0.258);
  
  TString titlename;
  if (z_flag==3){
    titlename.Form("#scale[2.0]{%2.1f < P_{hT} < %2.1f}",(pt_flag-1)*0.2,(pt_flag-1)*0.2+0.2);
    if((pt_flag-1)*0.2==0)t1->DrawLatex(0.3,0.6,titlename);
	else if((pt_flag-1)*0.2==0.4)t1->DrawLatex(0.3,0.8,titlename);
	else t1->DrawLatex(0.3,0.85,titlename);
  }
  if (pt_flag==1){
    titlename.Form("#scale[2.0]{%3.2f < z < %3.2f}",(z_flag-3)*0.05+0.3,(z_flag-2)*0.05+0.3);
	if((z_flag-3)*0.05+0.3==0.3)t1->DrawLatex(0.3,0.7,titlename);
	else if((z_flag-3)*0.05+0.3==0.5)t1->DrawLatex(0.1,0.65,titlename);
	else t1->DrawLatex(0.08,0.65,titlename);
  }

}

void plot_solid(Int_t z_flag, Int_t pt_flag,Int_t color,Double_t scale, Double_t zero_point){

  TString filename;
  filename = "new_solid_kine.dat";
  ifstream infile3(filename);

  const int SIZE = 500;
  int count = 0;

  Double_t x[500],z[500],pt[500],q2[500];
  Double_t siv_err[SIZE], coll_err[SIZE], pret_err[SIZE];
  Double_t Astat[SIZE], x[SIZE], logq2[SIZE];

  //Set pt bins
  Double_t ptmin,ptmax;
  if (pt_flag==1){
    ptmin = 0.; ptmax = 0.2;
  }else if (pt_flag==2){
    ptmin = 0.2; ptmax = 0.4;
  }else if (pt_flag==3){
    ptmin = 0.4; ptmax = 0.6;
  }else if (pt_flag==4){
    ptmin = 0.6; ptmax = 0.8;
  }else if (pt_flag==5){
    ptmin = 0.8; ptmax = 1.0;
  }
  
  //Set z bins
  Double_t zmin,zmax;
  if (z_flag==3){
    zmin = 0.3; zmax = 0.35;
  }else if (z_flag==5){
    zmin = 0.4; zmax = 0.45;
  }else if (z_flag==7){
    zmin = 0.5; zmax = 0.55;
  }else if (z_flag==9){
    zmin = 0.6; zmax = 0.65;
  }else if (z_flag==11){
    zmin = 0.7; zmax = 0.75;
  }

  while(!infile3.eof()){
    infile3 >> x[count] >> z[count] >> pt[count] >> q2[count] >> siv_err[count] >> coll_err[count] >> pret_err[count];

    if(siv_err[count]>0. && pt[count] >= ptmin && pt[count] <= ptmax && z[count] >= zmin && z[count] <= zmax){
    
      //Average over errors and plot them according to log scale for x and q2


      Astat[count] = siv_err[count];
      //      x[count] = log(x[count])/log(10.);
      q2[count] = (q2[count]-zero_point)*scale;
      
      count++;
      
    }
  }
  TGraphErrors *g1 = new TGraphErrors(count,x,q2,0,Astat);
  
  //  g1->Draw();
  g1->SetMarkerColor(color);
  g1->SetMarkerStyle(24);
  g1->SetMarkerSize(0.4);
  g1->SetLineColor(color);
  g1->Draw("P");
  infile3.close();

  

}


void plot_12(Int_t particle_flag,Int_t Q2_flag, Int_t z_flag, Int_t pt_flag, Int_t color, Double_t scale, Double_t zero_point){
  cout << "3He!"<<endl;
  //only have 3He
  TString filename;
  filename.Form("./12gev_3he_results/result_%d_%d_%d.dat",particle_flag,Q2_flag,z_flag);
  ifstream infile2(filename);
  
  Double_t temp;
  Double_t x[500],z[500],pt[500],q2[500],w[500],wp[500],logx[500],logq2[500];
  Double_t sob[500],Astat[500],Astat3[500],rate[2][500],dilute[500];
  Double_t event[500];
  Double_t coverage[500],sivers[500],collins[500],prez[500];
  Int_t count = 0;

  Double_t ptmin,ptmax;
  if (pt_flag==1){
    ptmin = 0.; ptmax = 0.2;
  }else if (pt_flag==2){
    ptmin = 0.2; ptmax = 0.4;
  }else if (pt_flag==3){
    ptmin = 0.4; ptmax = 0.6;
  }else if (pt_flag==4){
    ptmin = 0.6; ptmax = 0.8;
  }else if (pt_flag==5){
    ptmin = 0.8; ptmax = 1.0;
  }
  
  while(!infile2.eof()){
    infile2 >> temp >> temp >> temp;
    infile2 >> x[count] >> z[count] >> pt[count] >> q2[count] >> w[count] >> wp[count];
    infile2 >> Astat[count] >> rate[0][count] >> rate[1][count] >> Astat3[count];
    infile2 >> sob[count] >> dilute[count] >> event[count];
    infile2 >> coverage[count] >> sivers[count] >> collins[count] >> prez[count];
    Astat[count] = Astat[count]*sivers[count];

//     cout << x[count] << " " << pt[count] << " " << pt[count] << endl;
//     cout << ptmin << " " << ptmax << endl;

    if (Astat[count]<5e-2 && pt[count] >= ptmin && pt[count] <= ptmax){ //Astat[count]<5e-2 &&
//       Astat[count] = Astat[count]*scale;
//       logx[count] = log(x[count])/log(10.);
//       logq2[count] = log(q2[count])/log(10.);
      q2[count] = (q2[count]-zero_point)*scale;

//       x[count] += 0.02;

//       cout << q2[count] << " " << x[count] << endl;
      count++;
    }
    if (temp==0) break;
  }

  
  TGraphErrors *g1 = new TGraphErrors(count,x,q2,0,Astat);
  g1->Draw("*same");
  g1->SetMarkerColor(color);
  g1->SetMarkerStyle(26);
  g1->SetMarkerSize(0.4);
  g1->SetLineColor(color);
  infile2.close();
		 


}
