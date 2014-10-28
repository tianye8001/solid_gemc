#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

#include <TRandom3.h>

#include "G2PPhys/G2PPhysBase.hh"
#include "G2PPhys/G2PPhysEl/G2PPhysEl.hh"
#include "G2PPhys/G2PPhysPB/G2PPhysPB.hh"
#include "G2PPhys/G2PPhysQFS/G2PPhysQFS.hh"
#include "G2PPhys/G2PPhysWISER/G2PPhysWISER.hh"

using namespace std;

FILE *fp;

ofstream lundfile;

static const double kDEG = 3.14159265358979323846/180.0;

// int main()
// {
//     fp = fopen("result1.dat", "w");

//     double Ei = 0.116;
//     double Ef = 0;

//     double in[35][6] = { {.13135320E+02,.78344187E+01,.40297212E-01,0,0,0 },
//                          {.13159968E+02,.77832346E+01,.61706660E-01,0,0,0 },
//                          {.13230485E+02,.75165900E+01,.44058778E-01,0,0,0 },
//                          {.15472480E+02,.39513019E+01,.29570551E-01,0,0,0 },
//                          {.15512698E+02,.39552531E+01,.29475874E-01,0,0,0 },
//                          {.15560565E+02,.39029073E+01,.31959273E-01,0,0,0 },
//                          {.17021715E+02,.27175101E+01,.13366449E-01,0,0,0 },
//                          {.19642125E+02,.14944415E+01,.74335815E-02,0,0,0 },
//                          {.20250156E+02,.13233122E+01,.64001613E-02,0,0,0 },
//                          {.22352577E+02,.85754887E+00,.68730332E-02,0,0,0 },
//                          {.25583263E+02,.48924053E+00,.24032822E-02,0,0,0 },
//                          {.26341648E+02,.42770711E+00,.28398542E-02,0,0,0 },
//                          {.29926121E+02,.24699361E+00,.11622018E-02,0,0,0 },
//                          {.35092204E+02,.11979300E+00,.62082633E-03,0,0,0 },
//                          {.37906488E+02,.84836670E-01,.39570476E-03,0,0,0 },
//                          {.37952486E+02,.83579816E-01,.53292261E-03,0,0,0 },
//                          {.38002831E+02,.83324312E-01,.39095933E-03,0,0,0 },
//                          {.38341794E+02,.79164717E-01,.36446553E-03,0,0,0 },
//                          {.39916252E+02,.65281937E-01,.31315534E-03,0,0,0 },
//                          {.40558669E+02,.61114390E-01,.46725013E-03,0,0,0 },
//                          {.50108012E+02,.21362139E-01,.11375727E-03,0,0,0 },
//                          {.50884968E+02,.19790091E-01,.99424004E-04,0,0,0 },
//                          {.51831326E+02,.18272053E-01,.10184600E-03,0,0,0 },
//                          {.60978122E+02,.74885376E-02,.35151663E-04,0,0,0 },
//                          {.61138970E+02,.73142993E-02,.53543238E-04,0,0,0 },
//                          {.64738421E+02,.52964709E-02,.24532217E-04,0,0,0 },
//                          {.70359591E+02,.32316590E-02,.16929798E-04,0,0,0 },
//                          {.75225774E+02,.21285685E-02,.10003936E-04,0,0,0 },
//                          {.85008331E+02,.94365709E-03,.70656453E-05,0,0,0 },
//                          {.90417626E+02,.61313860E-03,.47033353E-05,0,0,0 },
//                          {.91461204E+02,.56619221E-03,.30406792E-05,0,0,0 },
//                          {.10858935E+03,.15109455E-03,.12924381E-05,0,0,0 },
//                          {.10985949E+03,.13673025E-03,.99646780E-06,0,0,0 },
//                          {.10997535E+03,.13656998E-03,.86898670E-06,0,0,0 },
//                          {.11331657E+03,.10410941E-03,.10008235E-05,0,0,0 } };

//     G2PPhysBase *pPhys = new G2PPhysEl();
//     pPhys->SetTarget(6,12);
//     double M = 12.0107*0.931494028;
//     pPhys->SetTargetMass(M);
//     pPhys->SetParticle(11);
//     double pars[1] = {1};

//     for (int i = 0; i<35; i++) {
//         double theta = in[i][0]*kDEG;
//         pars[0] = 1;
//         pPhys->SetPars(pars,1);
//         double xs1 = pPhys->GetXS(Ei, Ef, theta);
//         pars[0] = 2;
//         pPhys->SetPars(pars,1);
//         double xs2 = pPhys->GetXS(Ei, Ef, theta);
//         double sth2 = sin(theta/2)*sin(theta/2);
//         Ef = Ei/(1+2*Ei/M*sth2);
//         double q2 = 4*Ei*Ef*sth2;
//         printf("%e\t%e\t%e\t%e\t%e\n", theta/kDEG, q2, in[i][1]*1e4, xs1, xs2);
//         fprintf(fp,"%e\t%e\t%e\t%e\t%e\t%e\n", theta/kDEG, q2, in[i][1]*1e4, in[i][2]*1e4, xs1, xs2);
//     }

//     fclose(fp);

//     fp = fopen("result2.dat", "w");

//     Ei = 0.7472;

//     double in2[16][6] = {
//         { 0.32080000E+02,0.12600000E-05,0.36000001E-07,.932,4.,-.4800 },
//         { 0.34080000E+02,0.11400000E-05,0.36000001E-07,.932,4.,-.4800 },
//         { 0.36080000E+02,0.77500002E-06,0.26000000E-07,.932,4.,-.4800 },
//         { 0.38080000E+02,0.46300000E-06,0.16000000E-07,.932,4.,-.4800 },
//         { 0.40080000E+02,0.26000000E-06,0.90000001E-08,.932,4.,-.4800 },
//         { 0.42080000E+02,0.12700000E-06,0.43000000E-08,.932,4.,-.4800 },
//         { 0.44080000E+02,0.56200000E-07,0.21000000E-08,.932,4.,-1.240 },
//         { 0.46080000E+02,0.23800000E-07,0.80000000E-09,.932,4.,-1.240 },
//         { 0.48080000E+02,0.95100001E-08,0.45000000E-09,.932,4.,-1.240 },
//         { 0.50080000E+02,0.35000000E-08,0.22000000E-09,.932,4.,-1.240 },
//         { 0.52080000E+02,0.10900000E-08,0.12000000E-09,.932,4.,-1.240 },
//         { 0.53080000E+02,0.55000001E-09,0.78000001E-10,.932,4.,-1.240 },
//         { 0.54080000E+02,0.41200000E-09,0.61000001E-10,.932,4.,-1.240 },
//         { 0.56080000E+02,0.72500002E-10,0.19000000E-10,.932,4.,-1.240 },
//         { 0.58080000E+02,0.23000000E-10,0.68000000E-11,.932,4.,-1.240 },
//         { 0.64080000E+02,0.40000000E-11,0.40000000E-11,.932,4.,-1.240 }
//     };

//     for (int i = 0; i<15; i++) {
//         double theta = in2[i][0]*kDEG;
//         pars[0] = 1;
//         pPhys->SetPars(pars,1);
//         double xs1 = pPhys->GetXS(Ei, Ef, theta);
//         pars[0] = 2;
//         pPhys->SetPars(pars,1);
//         double xs2 = pPhys->GetXS(Ei, Ef, theta);
//         double sth2 = sin(theta/2)*sin(theta/2);
//         Ef = Ei/(1+2*Ei/M*sth2);
//         double q2 = 4*Ei*Ef*sth2;
//         printf("%e\t%e\t%e\t%e\t%e\n", theta/kDEG, q2, in2[i][1]*1e4, xs1, xs2);
//         fprintf(fp,"%e\t%e\t%e\t%e\t%e\t%e\n", theta/kDEG, q2, in2[i][1]*1e4, in[i][2]*1e4, xs1, xs2);
//     }

//     fclose(fp);

//     fp = fopen("result3.dat", "w");

//     Ei = 2.253;

//     for (int i = 0; i<=55; i++) {
//         double theta = (4+(i/5.0))*kDEG;
//         pars[0] = 1;
//         pPhys->SetPars(pars,1);
//         double xs1 = pPhys->GetXS(Ei, Ef, theta);
//         pars[0] = 2;
//         pPhys->SetPars(pars,1);
//         double xs2 = pPhys->GetXS(Ei, Ef, theta);
//         double sth2 = sin(theta/2)*sin(theta/2);
//         Ef = Ei/(1+2*Ei/M*sth2);
//         double q2 = 4*Ei*Ef*sth2;
//         printf("%e\t%e\t%e\t%e\n", theta/kDEG, q2, xs1, xs2);
//         fprintf(fp,"%e\t%e\t%e\t%e\n", theta/kDEG, q2, xs1, xs2);
//     }

//     fclose(fp);

//     return 0;
// }

// int main()
// {
//     //double Ei = 11.0;
//     double Ei = 8.8; //GeV
//     double Ef_min = 0.9;
//     double Ef_max = 8.7;
//     double Ef_bin = 0.1;
//     //double Ef_N = (Ef_max-Ef_min)/Ef_bin;
//     double ang_min = 6.6;
//     double ang_max = 12.0;
//     double ang_N = 10.0;
//     double ang_bin = (ang_max-ang_min)/ang_N;
//     double lumi = 1.0e36*1.0e-30;
//     double angacc = 0.057/ang_N;
//     //double angacc = 0.5*kDEG*2*3.14159265358979323846;
//     double momacc = 100; //MeV

//     // //double Ei = 11.0;
//     // double Ei = 8.8; //GeV
//     // double Ef_min = 3.5;
//     // double Ef_max = 8.7;
//     // double Ef_bin = 0.1;
//     // //double Ef_N = (Ef_max-Ef_min)/Ef_bin;
//     // double ang_min = 14.5;
//     // double ang_max = 22.0;
//     // double ang_N = 10.0;
//     // double ang_bin = (ang_max-ang_min)/ang_N;
//     // double lumi = 1.0e36*1.0e-30;
//     // double angacc = 0.2308/ang_N;
//     // //double angacc = 0.5*kDEG*2*3.14159265358979323846;
//     // double momacc = 100; //MeV

//     char filename[300];
//     sprintf(filename, "result_%04.1lf_%04.1lf.dat", Ei, ang_min);
//     fp = fopen(filename, "w");

//     G2PPhysBase *pPhys = new G2PPhysPB();
//     pPhys->SetTarget(2,3);
//     double M = 3.0160293*0.931494028;
//     pPhys->SetTargetMass(M);
//     pPhys->SetParticle(11);

//     double sumrate=0.0;
//     double sumxs=0.0;
//     int N = 0;
//     for (double ang = ang_min+ang_bin/2.0; ang<ang_max; ang+=ang_bin) {
//         double theta = ang*kDEG;
//         for (double Ef = Ef_min+Ef_bin/2.0; Ef<Ef_max; Ef+=Ef_bin) {
//             double xs = pPhys->GetXS(Ei, Ef, theta);
//             double rate = xs*lumi*angacc*momacc;
//             printf("%5.2lf\t%5.2lf\t%5.2lf\t%e\t%e\n", Ei, Ef, theta/kDEG, xs, rate);
//             fprintf(fp, "%5.2lf\t%5.2lf\t%5.2lf\t%e\t%e\n", Ei, Ef, theta/kDEG, xs, rate);
//             sumrate+=rate;
//             sumxs+=xs;
//             N++;
//         }
//     }

//     printf("%e\t%e\n", sumxs/N, sumrate);
//     fprintf(fp, "%e\t%e\n", sumxs/N, sumrate);

//     fclose(fp);

//     return 0;
// }

// int main()
// {
//     double Ei = 5.65;
//     double ang = 45*kDEG;
//     double Pf = 0.55;

//     G2PPhysBase *pPhys = new G2PPhysWISER();
//     double pars[10];
//     pars[0] = 0.027+0.5*(4.*0.0708)/61.28;//+0.0031+0.0124;
//     //pars[0] = 0.027+0.0124;
//     pPhys->SetPars(pars,1);
//     pPhys->SetTarget(1,1);
//     pPhys->SetParticle(-211);

//     double xs = pPhys->GetXS(Ei, Pf, ang);

//     printf("%e\n", xs);
// }

void GenerateGEMCLundFile(G2PPhysBase *pPhys,double beame, double lumi, double nevents);

int main()
{

  G2PPhysBase *pPhys = new G2PPhysEl();
  pPhys->SetParticle(11);
  double Ei = 2.253;
  double Ef = 0.0, M = 0.0;
  
  for (int i = 0; i<=55; i++) {
    double theta = (4+(i/5.0))*kDEG;
    pPhys->SetTarget(1,1);
    M = 1.008*0.931494028;
    pPhys->SetTargetMass(M);
    double xs1 = pPhys->GetXS(Ei, Ef, theta);        
    pPhys->SetTarget(2,4);
    M = 4.002602*0.931494028;
    pPhys->SetTargetMass(M);
    double xs2 = pPhys->GetXS(Ei, Ef, theta);
    pPhys->SetTarget(6,12);
    M = 12.0107*0.931494028;
    pPhys->SetTargetMass(M);
    double xs3 = pPhys->GetXS(Ei, Ef, theta);
    pPhys->SetTarget(7,14);
    M = 14.0030740048*0.931494028;
    pPhys->SetTargetMass(M);
        double xs4 = pPhys->GetXS(Ei, Ef, theta);
        printf("%e\t%e\t%e\t%e\t%e\n", theta/kDEG, xs1, xs2, xs3, xs4);
  }
    
  //To generate GEMC lund file following code is added. Rakitha rakithab@jlab.org - Tue Oct 28 11:08:58 EDT 2014
  
  pPhys = new G2PPhysPB();
  pPhys->SetParticle(11);
  Ei = 2.253;
  Ef = 0.0, M = 0.0;
  double PBarray[2]={0,0};//rad length before and after scattering vertex  
  pPhys->SetPars(PBarray,2);
  
  double Ebeam = 11;//GeV
  
//PVDIS_LD2    
//   pPhys->SetTarget(1,2);
//   M = 1.874; //2.014*0.931494028
//   double lumi = 1.27e39;//cm^-2.s^-1   neuclon lumi
 //SIDIS_He3
//   pPhys->SetTarget(2,3);    
//   M = 2.814;    
//   double lumi = 3e36;//cm^-2.s^-1     neuclon lumi
//SIDIS_He3_window_downstream
  pPhys->SetTarget(17,35);    
  M = 32.866;    
  double lumi = 1.87e36;//cm^-2.s^-1         neuclon lumi
  
  pPhys->SetTargetMass(M); 
  
  GenerateGEMCLundFile(pPhys,Ebeam,lumi,1e6);
      
  return 0;
}

void GenerateGEMCLundFile(G2PPhysBase *pPhys,double beame, double lumi, double nevents){
  //rate=eff_cross_sec in cm^2 * luminosity in cm^-2.s^-1 / nevents
  double M = 0.931494028;//in GeV
  TRandom *r3 = new TRandom3();
  double mom_p = r3->Uniform(0,beame);
  double theta_max = 90 * kDEG ;
  double theta_min = 0 * kDEG ;
  double phi;
  double Q2,w2;
  double x;
  double theta = r3->Uniform(theta_min,theta_max);
  double xs_pbosted =0.;
  double rate;

  double V = (2*3.14159)*(cos(theta_min) - cos(theta_max))*(beame-0)*1000;

  double vx,vy,vz;

  lundfile.open ("trial.lund");

  for (int i=0;i<nevents;i++){
    //vertex
    vx = r3->Uniform(-0.5,0.5);
    vy = r3->Uniform(-0.5,0.5);
//     vz = r3->Uniform(-10,30);//PVDIS_LD2
//     vz = r3->Uniform(-370,330); //SIDIS_He3
//     vz = r3->Uniform(-330.006,-329.994);//SIDIS_He3_downstream
    vz = r3->Uniform(-370.006,-369.994);//SIDIS_He3_upstream    
    phi = r3->Uniform(0,2*3.14159);
    //kinematics
    mom_p = r3->Uniform(0,beame);
    theta = r3->Uniform(theta_min,theta_max);
    Q2=4.*beame*mom_p*pow((sin(abs(theta)/2.)),2); 
    w2=pow(M,2)+2.*M*(beame-mom_p)-Q2;
    x = Q2/(2.0*M*(beame-mom_p));
    //if (Q2<10 && w2<16){
    xs_pbosted = pPhys->GetXS(beame,mom_p,theta)*V;//cross section in units of ub or 1e-30 cm^2 the GetXS return in ub/MeV-sr and V has MeV-sr
    if (!isnan(xs_pbosted)){
//       printf(" %i %3.3f GeV %3.3f deg %3.3e ub %3.3f kHz \n",i,mom_p,theta/kDEG,xs_pbosted,xs_pbosted*1e-30*lumi/nevents/1000);
      rate = xs_pbosted*1e-30*lumi/nevents;
    }else{
//       printf(" %i %3.3f GeV %3.3f deg 0 ub 0 kHz \n",i,mom_p,theta/kDEG);
      rate = 0;
    }

    //write to lund file        
    if (rate > 0.){
    lundfile<<"1" << " \t " << 0 << " \t " << 0 << " \t " << "0"  << " \t " << "0" << " \t " << x << " \t " << (beame-mom_p)  << " \t " << w2  << " \t " << Q2  << " \t " << rate << endl;
    lundfile<< " \t " << "1" << " \t " << -1 << " \t " << "1" << " \t " << pPhys->GetParticle() << " \t " << "0" << " \t " << "0" << " \t " << mom_p*sin(theta)*cos(phi) << " \t "<< mom_p*sin(theta)*sin(phi) << " \t "<< mom_p*cos(theta) << " \t " << mom_p << " \t " << 0.000511 << " \t " << vx  << " \t " << vy << " \t " << vz << endl;
    }
    
    //}else
    //printf(" %i %3.3f GeV %3.3f deg 0 ub 0 kHz \n",i,mom_p,theta/kDEG);
    
  }

  lundfile.close();

};
 
