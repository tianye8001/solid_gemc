{  
// double d=266;    //(315-65)/cos(20/180*3.1415926)=266cm   TCS LA
// double d=741;       //(315+415)/cos(10/180*3.1415926)=741cm  TCS FA
// double d=786;       //(350+430)/cos(7/180*3.1415926)=786cm  SIDIS FA
double d=6.70;       //(350+306)/cos(12/180*3.1415926)=670cm  SIDIS FA before HGC

  
const double M_pi=0.140,M_k=0.494,M_p=0.938;
double l_pi=2.6e-8,l_k=1.24e-8;
double c=3e8;

for(int p=1;p<11;p++){

TLorentzVector pi(0,0,p,sqrt(p*p+M_pi*M_pi));

TF1 *fpi=new TF1("fpi","1-exp(-x/([0]*[1]*[2]*[3]))",0,10);
fpi->SetParameters(pi.Beta(),pi.Gamma(),l_pi,c);
cout << fpi->Eval(d) << ",";
fpi->SetMaximum(1);
fpi->SetMinimum(1e-3);
fpi->SetTitle("charged pion/kaon from 1 to 10 GeV;flight path (m);decay rate");
fpi->SetLineColor(kBlack);
fpi->SetLineStyle(1);
if (p==1) fpi->Draw();
else fpi->Draw("same");

}
cout << endl;

for(int p=1;p<11;p++){  
TLorentzVector k(0,0,p,sqrt(p*p+M_k*M_k));
TF1 *fk=new TF1("fk","1-exp(-x/([0]*[1]*[2]*[3]))",0,10);
fk->SetParameters(k.Beta(),k.Gamma(),l_k,c);
cout << fk->Eval(d) << ",";
fk->SetMaximum(1);
fk->SetMinimum(1e-3);
fk->SetTitle("charged pion/kaon from 1 to 10 GeV;flight path (m);decay rate");
fk->SetLineColor(kRed);
fk->SetLineStyle(1);
fk->Draw("same");
}
cout << endl;

gPad->SetLogy();

/*TF1 *line=new TF1("line","5",0,12);
// TF1 *line=new TF1("line","0.08",0,10);
line->SetLineColor(kRed);
line->Draw("same");

TF1 *line1=new TF1("line1","0.4",0,12);
// TF1 *line=new TF1("line","0.08",0,10);
line1->SetLineColor(kRed);
line1->Draw("same");				


//       TLine *lh;
//       TLatex  t;
//       t.SetTextAlign(32);
//       t.SetTextSize(0.07);   
//       lh = new TLine(3,0.9,3.4,0.9);
//       lh->SetLineStyle(1);
//       t.DrawLatex(4.8,0.9,"#Delta t (p-#pi)");
//       lh->Draw();
//       lh = new TLine(3,0.8,3.4,0.8);
//       lh->SetLineStyle(9);
//       t.DrawLatex(4.8,0.8,"#Delta t (p-K)");
//       lh->Draw();      
//       lh = new TLine(3,0.7,3.4,0.7);
//       lh->SetLineStyle(7);
//       t.DrawLatex(4.8,0.7,"#Delta t (K-#pi)");
//       lh->Draw(); 
      
// draw the legend
   TLegend *legend=new TLegend(0.65,0.65,0.88,0.85);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(ppi,"#Delta t (p-#pi)","l");
   legend->AddEntry(pk,"#Delta t (p-K)","l");
   legend->AddEntry(kpi,"#Delta t (K-#pi)","l");
   legend->Draw();    */ 
      
}