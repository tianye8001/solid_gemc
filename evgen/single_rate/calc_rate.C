calc_rate(){
const int xbin=55;
const int Q2bin=20;
// double x_low=0.225,x_high=0.775;
// double Q2_low=3.,Q2_high=12.;
double x_low=0,x_high=11;  /// x is mom now
double Q2_low=0,Q2_high=180; ///Q2 is theta now
double xbinwidth=(x_high-x_low)/xbin;
double Q2binwidth=(Q2_high-Q2_low)/Q2bin;
TH2F *h1=new TH2F("whitlow rate","whitlow rate",xbin,x_low,x_high,Q2bin,Q2_low,Q2_high);
TH2F *h2=new TH2F("qfs rate","qfs rate",xbin,x_low,x_high,Q2bin,Q2_low,Q2_high);
for (int i=0;i<xbin;i++){
  for (int j=0;j<Q2bin;j++){
    char cmd[100];
    double x_min=x_low+xbinwidth*i,x_max=x_low+xbinwidth*(i+1);
    double x=(x_min+x_max)/2.;
    double Q2_min=Q2_low+Q2binwidth*j,Q2_max=Q2_low+Q2binwidth*(j+1);
    double Q2=(Q2_min+Q2_max)/2.;
    if (0.939**2+2*0.939*(11.-x)-4*11.*x*sin(Q2/180.*3.14)**2 > 4.){ /// W>2 to ensure DIS region
      if (4*11.*x*sin(Q2/180.*3.14)**2 > 1.){ /// Q2>1
//     if (Q2_min>(2.**2-0.94**2)/(1/x-1)){ /// W>2 to ensure DIS region    
//       sprintf (cmd,"./main 0 1000. 11. 2 %f %f %f %f",x_min,x_max,Q2_min,Q2_max);
      sprintf (cmd,"./main 0 1000. 11. 1 %f %f %f %f",x_min,x_max,Q2_min,Q2_max);      
      gSystem->Exec(cmd);
      ifstream file1("ele1.dat");
      ifstream file2("ele2.dat");
      string rate_s;
      file1>>rate_s;      file1.close(); cout << "rate1 " << rate_s << endl;
      if (rate_s!="NaN" && atof(rate_s.c_str()) > 0) h1->SetBinContent(i+1,j+1,atof(rate_s.c_str()));
      file2>>rate_s;       file2.close();  cout << "rate2 " << rate_s << endl;    
      if (rate_s!="NaN" && atof(rate_s.c_str()) > 0) h2->SetBinContent(i+1,j+1,atof(rate_s.c_str()));
    }
    }
    
  }
}

double Q2[xbin],rate[xbin];

gStyle->SetOptStat(0);
TCanvas *c_rate = new TCanvas("rate","rate",1200,900);
c_rate->Divide(1,2);
c_rate->cd(1);
h1->SetMarkerSize(2);
h1->SetTitle("whitlow rate;x;Q2");
h1->Rebin2D(5,2);
h1->Draw("TEXT");

for (int i=0;i<xbin;i++){
  Q2[i]=0.;
  rate[i]=0.;
  for (int j=0;j<Q2bin;j++){
  Q2[i] = Q2[i] + (Q2_low+1.*(j+1/2.))*h1->GetBinContent(i+1,j+1);
  rate[i] = rate[i] + h1->GetBinContent(i+1,j+1);
  }
  Q2[i] = Q2[i]/rate[i];  
}
for (int i=0;i<xbin;i++) cout << Q2[i] << ",";
cout << endl;
for (int i=0;i<xbin;i++) cout << rate[i] << ",";
cout << endl;

c_rate->cd(2);
h2->SetMarkerSize(2);
h2->SetTitle("qfs rate;x;Q2");
h2->Draw("TEXT");

for (int i=0;i<xbin;i++){
  Q2[i]=0.;
  rate[i]=0.;
  for (int j=0;j<Q2bin;j++){
  Q2[i] = Q2[i] + (Q2_low+1.*(j+1/2.))*h2->GetBinContent(i+1,j+1);
  rate[i] = rate[i] + h2->GetBinContent(i+1,j+1);
  }
  Q2[i] = Q2[i]/rate[i];  
}
for (int i=0;i<xbin;i++) cout << Q2[i] << ",";
cout << endl;
for (int i=0;i<xbin;i++) cout << rate[i] << ",";
cout << endl;

}