void acceptance(string input_filename)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const double DEG=180./3.1415926;

bool Is_PVDIS=false,Is_SIDIS_3he=false,Is_SIDIS_proton=false,Is_JPsi=false;
if (input_filename.find("PVDIS",0) != string::npos) Is_PVDIS=true;
else if (input_filename.find("SIDIS_3he",0) != string::npos) Is_SIDIS_3he=true;
else if (input_filename.find("SIDIS_proton",0) != string::npos) s_SIDIS_proton=true;
else if (input_filename.find("JPsi",0) != string::npos) Is_JPsi=true;
else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}

char output_filename[80];
sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.rfind(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

TH2F *hacceptance_forwardangle,*hacceptance_largeangle,*hacceptance_overall;

const int n=2;

TH2F *hgen=new TH2F("gen","gen",100,0,50,110,0,11);
TH2F *hgen_vertexZ=new TH2F("gen_vertexZ","gen_vertexZ",350,15,40,50,-15,35);
TH2F *hgen_vertexR=new TH2F("gen_vertexR","gen_vertexR",350,15,40,50,0,0.5);

TH1F *hflux_mom[n],*hflux_theta[n];
TH2F *hflux[n],*hflux_vertexZ[n],*hflux_vertexR[n];
TH1F *hacceptance_mom[n],*hacceptance_theta[n];
TH2F *hacceptance[n];
TH2F *hhit_rz[n],*hhit_xy[n];
for(int i=0;i<n;i++){
     char hstname[100];  
   sprintf(hstname,"flux_mom_%i",i);
   hflux_mom[i]=new TH1F(hstname,hstname,110,0,11);
   sprintf(hstname,"flux_theta_%i",i);
   hflux_theta[i]=new TH1F(hstname,hstname,100,0,50); 
   sprintf(hstname,"flux_%i",i);
   hflux[i]=new TH2F(hstname,hstname,100,0,50,110,0,11);   
   hflux[i]->SetTitle("particles detected by EC;vertex angle (deg);P (GeV)");
   sprintf(hstname,"flux_vertexZ_%i",i);
   hflux_vertexZ[i]=new TH2F(hstname,hstname,350,15,40,50,-15,35);
   hflux_vertexZ[i]->SetTitle("particles detected by EC;vertex angle (deg);vertex Z (cm)");   
   sprintf(hstname,"flux_vertexR_%i",i);
   hflux_vertexR[i]=new TH2F(hstname,hstname,350,15,40,50,0,0.5);
   hflux_vertexR[i]->SetTitle("particles detected by EC;vertex angle (deg);vertex R (cm)");      
  
   sprintf(hstname,"acceptance_mom_%i",i);
   hacceptance_mom[i]=new TH1F(hstname,hstname,110,0,11);
   sprintf(hstname,"acceptance_theta_%i",i);
   hacceptance_theta[i]=new TH1F(hstname,hstname,100,0,50); 
   sprintf(hstname,"acceptance_%i",i);
   hacceptance[i]=new TH2F(hstname,hstname,100,0,50,110,0,11);   
   
   sprintf(hstname,"hit_rz_%i",i);
   hhit_rz[i]=new TH2F(hstname,hstname,1000,-400,600,300,0,300);  
   sprintf(hstname,"hit_xy_%i",i);
   hhit_xy[i]=new TH2F(hstname,hstname,600,-300,300,600,-300,300);     
}

const int Nplate=6;
TH2F *hbaffleplate[Nplate];
for (int i=0;i<Nplate;i++){
  hbaffleplate[i]=new TH2F(Form("baffleplate_%i", i),Form("baffleplate_%i", i),300,-150,150,300,-150,150);
}

  TFile *file=new TFile(input_filename.c_str());
    if (file->IsZombie()) {
       cout << "Error opening file" << input_filename << endl;
       continue;
//        exit(-1);
    }
    else cout << "open file " << input_filename << endl;

TTree *Tgen = (TTree*) file->Get("genT");
Int_t gen_evn,gen_ngen;
Int_t gen_id_array[1000];
Int_t *gen_id=gen_id_array;
Float_t gen_px_array[1000],gen_py_array[1000],gen_pz_array[1000],gen_p_array[1000],gen_phi_array[1000],gen_theta_array[1000],gen_vx_array[1000],gen_vy_array[1000],gen_vz_array[1000];
Float_t *gen_px=gen_px_array,*gen_py=gen_py_array,*gen_pz=gen_pz_array,*gen_p=gen_p_array,*gen_phi=gen_phi_array,*gen_theta=gen_theta_array,*gen_vx=gen_vx_array,*gen_vy=gen_vy_array,*gen_vz=gen_vz_array;
Tgen->SetBranchAddress("evn",&gen_evn);
Tgen->SetBranchAddress("ngen",&gen_ngen);
Tgen->SetBranchAddress("id",gen_id);
Tgen->SetBranchAddress("px",gen_px);
Tgen->SetBranchAddress("py",gen_py);
Tgen->SetBranchAddress("pz",gen_pz);
Tgen->SetBranchAddress("p",gen_p);
Tgen->SetBranchAddress("phi",gen_phi);
Tgen->SetBranchAddress("theta",gen_theta);
Tgen->SetBranchAddress("vx",gen_vx);
Tgen->SetBranchAddress("vy",gen_vy);
Tgen->SetBranchAddress("vz",gen_vz);

TTree *Tflux = (TTree*) file->Get("fluxT");
Int_t flux_evn,flux_nfluxhit;
Int_t flux_ID_array[1000],*flux_pid_array[1000],*flux_mpid_array[1000];
Int_t *flux_ID=flux_ID_array,*flux_pid=flux_pid_array,*flux_mpid=flux_mpid_array;
Float_t flux_Edep_array[1000],flux_E_array[1000],flux_x_array[1000],flux_y_array[1000],flux_z_array[1000],flux_lx_array[1000],flux_ly_array[1000],flux_lz_array[1000],flux_t_array[1000],flux_px_array[1000],flux_py_array[1000],flux_pz_array[1000],flux_vx_array[1000],flux_vy_array[1000],flux_vz_array[1000],flux_mvx_array[1000],flux_mvy_array[1000],flux_mvz_array[1000];
Float_t *flux_Edep=flux_Edep_array,*flux_E=flux_E_array,*flux_x=flux_x_array,*flux_y=flux_y_array,*flux_z=flux_z_array,*flux_lx=flux_lx_array,*flux_ly=flux_ly_array,*flux_lz=flux_lz_array,*flux_t=flux_t_array,*flux_px=flux_px_array,*flux_py=flux_py_array,*flux_pz=flux_pz_array,*flux_vx=flux_vx_array,*flux_vy=flux_vy_array,*flux_vz=flux_vz_array,*flux_mvx=flux_mvx_array,*flux_mvy=flux_mvy_array,*flux_mvz=flux_mvz_array;
Tflux->SetBranchAddress("evn",&flux_evn);
Tflux->SetBranchAddress("nfluxhit",&flux_nfluxhit);
Tflux->SetBranchAddress("ID",flux_ID);
Tflux->SetBranchAddress("Edep",flux_Edep);
Tflux->SetBranchAddress("E",flux_E);
Tflux->SetBranchAddress("x",flux_x);
Tflux->SetBranchAddress("y",flux_y);
Tflux->SetBranchAddress("z",flux_z);
Tflux->SetBranchAddress("lx",flux_lx);
Tflux->SetBranchAddress("ly",flux_ly);
Tflux->SetBranchAddress("lz",flux_lz);
Tflux->SetBranchAddress("t",flux_t);
Tflux->SetBranchAddress("pid",flux_pid);
Tflux->SetBranchAddress("mpid",flux_mpid);
Tflux->SetBranchAddress("px",flux_px);
Tflux->SetBranchAddress("py",flux_py);
Tflux->SetBranchAddress("pz",flux_pz);
Tflux->SetBranchAddress("vx",flux_vx);
Tflux->SetBranchAddress("vy",flux_vy);
Tflux->SetBranchAddress("vz",flux_vz);
Tflux->SetBranchAddress("mvx",flux_mvx);
Tflux->SetBranchAddress("mvy",flux_mvy);
Tflux->SetBranchAddress("mvz",flux_mvz);

// Int_t nevent = (Int_t)Tgen->GetEntries();
Int_t nevent = (Int_t)Tflux->GetEntries();
Int_t nselected = 0;
cout << nevent << endl;

///radius cut standard as particles can travel 30cm in Z before leave calorimeter
///SIDIS largeangle EC outerradius is at 140cm
double rout_cut_FA,rin_cut_FA,rout_cut_LA,rin_cut_LA;
if (Is_PVDIS){
  rout_cut_FA = 250;  //target at 10,ec front at 320 back at 370 with angle 36
  rin_cut_FA = 0;  //as the detector edge
  cout << " PVDIS rcut " << rin_cut_FA << " " << rout_cut_FA <<  endl;
}
else if (Is_SIDIS_3he){
  rout_cut_FA=220;     //target at -350,ec front at 405 with angle 15
  rin_cut_FA=0;   //cut at the actual edge 
  rout_cut_LA=126.3;   //target at -350,ec front at -65 with angle 23.9
  rin_cut_LA=80;   //cut at the actual edge
  cout << " SIDIS_3he rcut " << rin_cut_FA << " " << rout_cut_FA << " " << rout_cut_LA << " " << rout_cut_LA <<  endl;
}
else if (Is_SIDIS_proton){
  rout_cut_FA=220;     //target at -350,ec front at 405 with angle 15
  rin_cut_FA=0;   //cut at the actual edge  
  rout_cut_LA=126.3; //target at -350,ec front at -65 with angle 23.9
  rin_cut_LA=80;   //cut at the actual edge
  cout << " SIDIS_proton rcut " << rin_cut_FA << " " << rout_cut_FA << " " << rout_cut_LA << " " << rout_cut_LA <<  endl;
}
else if (Is_JPsi){
    rout_cut_FA=220;     //target at -350,ec front at 405 with angle 15
    rin_cut_FA=0;   	//cut at the actual edge
  
//   rout_cut_LA=127.1;   //target at -360,ec front at -65 with angle 23.3    
//   rout_cut_LA=126.3;   //target at -350,ec front at -65 with angle 23.9
//   rout_cut_LA=125.9;   //target at -340,ec front at -65 with angle 24.6
//   rout_cut_LA=125.3;   //target at -330,ec front at -65 with angle 25.3    
//   rout_cut_LA=124.9;   //target at -320,ec front at -65 with angle 26.1
//   rout_cut_LA=124.3;   //target at -310,ec front at -65 with angle 26.9
//      rout_cut_LA=124.0;   //target at -305,ec front at -65 with angle 27.3
     rout_cut_LA=123.9;   //target at -300,ec front at -65 with angle 27.8
//      rout_cut_LA=123.8;   //target at -295,ec front at -65 with angle 28.3
//   rout_cut_LA=123.2;   //target at -290,ec front at -65 with angle 28.7
//      rout_cut_LA=122.6;   //target at -280,ec front at -65 with angle 29.7
//      rout_cut_LA=121.7;   //target at -270,ec front at -65 with angle 30.7
//   rout_cut_LA=120.1;   //target at -250,ec front at -65 with angle 33.0
  rin_cut_LA=80;   //cut at the actual edge  
  cout << " JPsi rcut " << rin_cut_FA << " " << rout_cut_FA << " " << rout_cut_LA << " " << rout_cut_LA <<  endl;
}
else {cout << "not PVDIS or SIDIS or JPsi " << endl; return;}

   
for (Int_t i=0;i<nevent;i++) {
  
//   cout << i << "\r";
//   cout << i << "\n";
  double theta=0,mom=0;  
  Tgen->GetEntry(i);  
  for (Int_t j=0;j<gen_ngen;j++) {
//       cout <<  gen_evn << " " << gen_ngen << " " << *(gen_id+j) << " " << *(gen_px+j) << " " << *(gen_py+j) << " " << *(gen_pz+j) << " " << *(gen_p+j) <<endl;
      theta=*(gen_theta+j);
      mom=*(gen_p+j)/1e3;
      hgen->Fill(theta,mom);
      hgen_vertexZ->Fill(theta,*(gen_vz+j));
      hgen_vertexR->Fill(theta,sqrt(*(gen_vx+j)**2+*(gen_vy+j)**2));      
  }  
  
//   int counter[n]={0,0,0,0,0,0,0,0,0,0};
    Tflux->GetEntry(i);    
    for (Int_t j=0;j<flux_nfluxhit;j++) {
//       cout << j << endl;
//       cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
    
    int detector_ID=*(flux_ID+j)/1000000;
    int subdetector_ID=(*(flux_ID+j)%1000000)/100000;
    int subsubdetector_ID=((*(flux_ID+j)%1000000)%100000)/10000;
//     cout << Detector_ID << " " << SubDetector_ID << " "  << channel_ID << endl;
    
    if (detector_ID==0) hbaffleplate[subdetector_ID-1]->Fill(*(flux_x+j)/10,*(flux_y+j)/10);

    int hit_id=-1;
    if (*(flux_ID+j)==3110000) hit_id=0;
    if (*(flux_ID+j)==3210000) hit_id=1;    
    if (hit_id==-1) continue;  //skip other subsubdetector
    
//     if(mom > 1.4) continue;
             
//       double theta=atan((sqrt((*(flux_x+j))**2+(*(flux_y+j))**2)/(*(flux_z+j)-*gen_vz)))*DEG;

       double r=sqrt(*(flux_x+j)**2+*(flux_y+j)**2);
       hhit_rz[hit_id]->Fill(*(flux_z+j)/10,r/10);
       hhit_xy[hit_id]->Fill(*(flux_x+j)/10,*(flux_y+j)/10);       
       if ((detector_ID==3 && subdetector_ID==2) && (r/10 < rin_cut_LA || rout_cut_LA < r/10)) continue;
       if ((detector_ID==3 && subdetector_ID==1) && (r/10 < rin_cut_FA || rout_cut_FA < r/10)) continue;       
       
	hflux[hit_id]->Fill(theta,mom);
        hflux_vertexZ[hit_id]->Fill(theta,*(flux_vz+j)/10);
        hflux_vertexR[hit_id]->Fill(theta,sqrt(*(flux_vx+j)**2+*(flux_vy+j)**2)/10);       
       
       
//        if (hit_id==7 && theta >17) cout << *(flux_vz+j)/10 << " " << r/10 << " " << theta << " " << mom << endl;
//       cout << *(flux_vz+j)/10 <<  " " << r << endl;
// 	counter[hit_id]++;       
    }    
//     for(int k=0;k<n;k++){
//       if (counter[hit_id] > 1) cout << counter[hit_id] << " " << hit_id << endl;
//       counter[hit_id]=0;
//     }
    
}
file->Close();

if (Is_PVDIS){ 
  double planeZ[6]={40,68,96,124,152,180};
  double Rin[6]={2.11, 12.86, 23.61, 34.36, 45.10, 55.85};
  double Rout[6]={39.60, 59.94, 80.28, 100.63, 120.97, 141.31};
TCanvas *c_baffleplate = new TCanvas("baffleplate","baffleplate",1350,900);
c_baffleplate->Divide(3,2);
for (int i=0;i<Nplate;i++){
  c_baffleplate->cd(i+1);      
  hbaffleplate[i]->Draw("colz");  
  TArc *c_in=new TArc(0,0,Rin[i]);
  c_in->SetLineColor(kBlack);
  c_in->SetFillStyle(0);  
  c_in->Draw();
  TArc *c_out=new TArc(0,0,Rout[i]);
  c_out->SetLineColor(kBlack);
  c_out->SetFillStyle(0);    
  c_out->Draw();
}
c_baffleplate->SaveAs("baffleplate.png");
}

for(int i=0;i<n;i++) {
  hacceptance[i]->Divide(hflux[i],hgen);  
  hacceptance_mom[i]=(TH1F)hacceptance[i]->ProjectionY();
  hacceptance_theta[i]=(TH1F)hacceptance[i]->ProjectionX();
}


TCanvas *c_acc = new TCanvas("acc","acc",1200,800);
c_acc->Divide(3,2);
c_acc->cd(1);
hacceptance[0]->Draw("colz");
c_acc->cd(2);
hacceptance_mom[0]->Draw();
c_acc->cd(3);
hacceptance_theta[0]->Draw();
c_acc->cd(4);
hacceptance[1]->Draw("colz");
c_acc->cd(5);
hacceptance_mom[1]->Draw();
c_acc->cd(6);
hacceptance_theta[1]->Draw();
c_acc->SaveAs("acc.png");

TCanvas *c_gen = new TCanvas("gen","gen",1200,600);
c_gen->Divide(3,1);
c_gen->cd(1);
hgen->Draw("colz");
c_gen->cd(2);
hgen_vertexZ->Draw("colz");
c_gen->cd(3);
hgen_vertexR->Draw("colz");

TCanvas *c_flux = new TCanvas("flux","flux",1200,600);
c_flux->Divide(3,2);
c_flux->cd(1);
hflux[0]->Draw("colz");
c_flux->cd(2);
hflux_vertexZ[0]->Draw("colz");
c_flux->cd(3);
hflux_vertexR[0]->Draw("colz");
c_flux->cd(4);
hflux[1]->Draw("colz");
c_flux->cd(5);
hflux_vertexZ[1]->Draw("colz");
c_flux->cd(6);
hflux_vertexR[1]->Draw("colz");
c_flux->SaveAs("flux.png");

TCanvas *c_hit_rz = new TCanvas("hit_rz","hit_rz",1800,800);
c_hit_rz->Divide(2,1);
for(int k=0;k<n;k++){
c_hit_rz->cd(k+1);
gPad->SetLogz(1);
hhit_rz[k]->Draw("colz");
}

TCanvas *c_hit_xy = new TCanvas("hit_xy","hit_xy",1800,800);
c_hit_xy->Divide(2,1);
for(int k=0;k<n;k++){
c_hit_xy->cd(k+1);
gPad->SetLogz(1);
hhit_xy[k]->Draw("colz");
}
c_hit_xy->SaveAs("hit_xy.png");

// TCanvas *c_acceptance_all_gem = new TCanvas("acceptance_gem","acceptance_gem",1800,800);
// c_acceptance_all_gem->Divide(2,3);
// for(int k=0;k<6;k++){
// c_acceptance_all_gem->cd(k+1);
// hacceptance[k]->Draw("colz");
// char hsttitle[80];
// sprintf(hsttitle,"acceptance at GEM plane %i;theta (degree);P (GeV)",k+1);
// hacceptance[k]->SetTitle(hsttitle);
// }
// c_acceptance_all_gem->SaveAs("acceptance_gem.png");

// TCanvas *c_acceptance_all_gem_1D = new TCanvas("acceptance_gem_1D","acceptance_gem_1D",1800,800);
// c_acceptance_all_gem_1D->Divide(2,6);
// for(int k=0;k<6;k++){
// c_acceptance_all_gem_1D->cd(k+1);
// hacceptance_mom[k]->Draw();
// c_acceptance_all_gem_1D->cd(6+k+1);
// hacceptance_theta[k]->Draw();
// }

hacceptance_forwardangle=(TH2F*) hacceptance[0]->Clone("acceptance_forwardangle");
hacceptance_forwardangle->SetNameTitle("acceptance_forwardangle","acceptance at forwardangle;theta (degree);P (GeV)");
hacceptance_largeangle=(TH2F*) hacceptance[1]->Clone("acceptance_largeangle");
hacceptance_largeangle->SetNameTitle("acceptance_largeangle","acceptance at largeangle;theta (degree);P (GeV)");
hacceptance_overall=(TH2F*) hacceptance_largeangle->Clone();
hacceptance_overall->Add(hacceptance_forwardangle);
hacceptance_overall->SetNameTitle("acceptance","acceptance;theta (degree);P (GeV)");

// gStyle->SetOptStat(0);

if (Is_PVDIS){ 
TCanvas *c_acceptance_all = new TCanvas("acceptance_all","acceptance_all",800,600);
// c_acceptance_all->Divide(1,3);
// c_acceptance_all->cd(1);
// gPad->SetLogy(1);  
hacceptance_overall->Draw("colz");
c_acceptance_all->SaveAs("acceptance_all.png");
}
else{
TCanvas *c_acceptance_all = new TCanvas("acceptance_all","acceptance_all",500,900);
c_acceptance_all->Divide(1,3);
c_acceptance_all->cd(1);
gPad->SetLogy();
gPad->SetGrid();
hacceptance_forwardangle->Draw("colz");
c_acceptance_all->cd(2);
gPad->SetLogy();
gPad->SetGrid();
hacceptance_largeangle->Draw("colz");
c_acceptance_all->cd(3);
gPad->SetLogy();
gPad->SetGrid();
hacceptance_overall->Draw("colz");
c_acceptance_all->SaveAs("acceptance_all.png");
}

hacceptance_forwardangle->SetDirectory(outputfile);
hacceptance_largeangle->SetDirectory(outputfile);
hacceptance_overall->SetDirectory(outputfile);

outputfile->Write();
outputfile->Flush();

}
