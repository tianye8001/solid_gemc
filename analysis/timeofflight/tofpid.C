{  
// double d=266;    //(315-65)/cos(20/180*3.1415926)=266cm   TCS LA
// double d=741;       //(315+415)/cos(10/180*3.1415926)=741cm  TCS FA
double d=786;       //(350+430)/cos(7/180*3.1415926)=786cm  SIDIS FA
//   double d=850;
  
const double M_pi=0.140,M_k=0.494,M_p=0.938;
TF1 *ppi=new TF1("ppi","[2]/30./(x/sqrt(x*x+[0]*[0]))-[2]/30./(x/sqrt(x*x+[1]*[1]))",0,12);
ppi->SetParameters(M_p,M_pi,d);
TF1 *pk=new TF1("kp","[2]/30./(x/sqrt(x*x+[0]*[0]))-[2]/30./(x/sqrt(x*x+[1]*[1]))",0,12);
pk->SetParameters(M_p,M_k,d);
TF1 *kpi=new TF1("kpi","[2]/30./(x/sqrt(x*x+[0]*[0]))-[2]/30./(x/sqrt(x*x+[1]*[1]))",0,12);
kpi->SetParameters(M_k,M_pi,d);
ppi->SetMaximum(7);
ppi->SetMinimum(0);
ppi->SetTitle("TOF PID;Mom (GeV/c);Time Diff (ns)");
ppi->SetLineColor(kBlack);
ppi->SetLineStyle(1);
ppi->Draw();
pk->SetLineColor(kBlack);
pk->SetLineStyle(9);
pk->Draw("same");
kpi->SetLineColor(kBlack);
kpi->SetLineStyle(7);
kpi->Draw("same");

TF1 *line=new TF1("line","5",0,12);
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
   legend->Draw();     
      
}