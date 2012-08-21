void acceptance(string input_filename)
{
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

const double DEG=180./3.1415926;

char output_filename[80];
sprintf(output_filename, "%s_output.root",input_filename.substr(0,input_filename.find(".")).c_str());
TFile *outputfile=new TFile(output_filename, "recreate");

const int n=10;
TH1F *hgen_mom,*hgen_theta;
TH2F *hgen;
TH1F *hacceptance_mom[n],*hacceptance_theta[n];
TH2F *hacceptance[n];
TH2F *hhit[n];

char hstname[100];
sprintf(hstname,"gen_mom");
hgen_mom=new TH1F(hstname,hstname,110,0,11);    
sprintf(hstname,"gen_theta");
hgen_theta=new TH1F(hstname,hstname,200,0,40);    
sprintf(hstname,"gen");
hgen=new TH2F(hstname,hstname,200,0,40,110,0,11);
for(int i=0;i<n;i++){
   sprintf(hstname,"acceptance_mom_%i",i);
   hacceptance_mom[i]=new TH1F(hstname,hstname,110,0,11);
   sprintf(hstname,"acceptance_theta_%i",i);
   hacceptance_theta[i]=new TH1F(hstname,hstname,200,0,40); 
   sprintf(hstname,"acceptance_%i",i);
   hacceptance[i]=new TH2F(hstname,hstname,200,0,40,110,0,11);   
   sprintf(hstname,"hit_%i",i);
   hhit[i]=new TH2F(hstname,hstname,1200,-600,600,500,0,500);  
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

   
for (Int_t i=0;i<nevent;i++) {
  
  double theta=0,mom=0;
  
  Tgen->GetEntry(i);  
  for (Int_t j=0;j<gen_ngen;j++) {
//       cout <<  gen_evn << " " << gen_ngen << " " << *(gen_id+j) << " " << *(gen_px+j) << " " << *(gen_py+j) << " " << *(gen_pz+j) << " " << *(gen_p+j) <<endl;
      theta=*(gen_theta+j);
      mom=*(gen_p+j)/1e3;
      hgen_mom->Fill(mom);
      hgen_theta->Fill(theta);      
      hgen->Fill(theta,mom);
  }  
  
//   int counter[n]={0,0,0,0,0,0,0,0,0,0};
    Tflux->GetEntry(i);    
    for (Int_t j=0;j<flux_nfluxhit;j++) {
//       cout << flux_evn<< " " << flux_nfluxhit << " " << *(flux_ID+j) << " " << *(flux_pid+j) << " " << *(flux_mpid+j) << " " <<  *(flux_Edep+j) << " " << *(flux_E+j) << " " << *(flux_x+j) << " " << *(flux_y+j) << " " << *(flux_z+j) << " " << *(flux_vx+j) << " " << *(flux_vy+j) << " " << *(flux_vz+j)  << " " << *(flux_px+j) << " " << *(flux_py+j) << " " << *(flux_pz+j) << endl;
      
    int Detector_ID=*(flux_ID+j)/1000000;
    int SubDetector_ID=(*(flux_ID+j)%1000000)/100000;
    int channel_ID=(*(flux_ID+j)%1000000)%100000;
//     cout << Detector_ID << " " << SubDetector_ID << " "  << channel_ID << endl;
     
    int hit_id=0;
    if (Detector_ID==1) hit_id=SubDetector_ID-1;
    else if (Detector_ID==3 && SubDetector_ID==2) hit_id=6;
    else if (Detector_ID==3 && SubDetector_ID==1) hit_id=7;    
    else if (Detector_ID==2 && SubDetector_ID==1) hit_id=8;
    else if (Detector_ID==2 && SubDetector_ID==2) hit_id=9;    
    else {
//       cout << "wrong flux_ID " << *(flux_ID+j) << endl; 
      continue;      
    }
    
//       double theta=atan((sqrt((*(flux_x+j))**2+(*(flux_y+j))**2)/(*(flux_z+j)-*gen_vz)))*DEG;

       hacceptance_mom[hit_id]->Fill(mom);
       hacceptance_theta[hit_id]->Fill(theta);       
       hacceptance[hit_id]->Fill(theta,mom);
       double r=sqrt(*(flux_x+j)**2+*(flux_y+j)**2);
       hhit[hit_id]->Fill(*(flux_z+j)/10,r/10);
       
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

TCanvas *c_gen = new TCanvas("gen","gen",600,600);
hgen->Draw("colz");

TCanvas *c_hit = new TCanvas("hit","hit",1800,800);
c_hit->Divide(4,2);
for(int k=0;k<n;k++){
c_hit->cd(k+1);
gPad->SetLogz(1);
hhit[k]->Draw("colz");
}

TCanvas *c_acceptance_gem = new TCanvas("acceptance_gem","acceptance_gem",1800,800);
c_acceptance_gem->Divide(2,3);
for(int k=0;k<6;k++){
c_acceptance_gem->cd(k+1);
hacceptance[k]->Divide(hacceptance[k],hgen);
hacceptance[k]->Scale(100);
hacceptance[k]->Draw("colz");
char hsttitle[80];
sprintf(hsttitle,"acceptance at GEM plane %i;theta (degree);P (GeV)",k+1);
hacceptance[k]->SetTitle(hsttitle);
}

TCanvas *c_acceptance_gem_1D = new TCanvas("acceptance_gem_1D","acceptance_gem_1D",1800,800);
c_acceptance_gem_1D->Divide(2,6);
for(int k=0;k<6;k++){
c_acceptance_gem_1D->cd(k+1);
hacceptance_mom[k]->Divide(hacceptance_mom[k],hgen_mom);
hacceptance_mom[k]->Scale(100);
hacceptance_mom[k]->Draw();
c_acceptance_gem_1D->cd(6+k+1);
hacceptance_theta[k]->Divide(hacceptance_theta[k],hgen_theta);
hacceptance_theta[k]->Scale(100);
hacceptance_theta[k]->Draw();
}

TCanvas *c_acceptance_ec = new TCanvas("acceptance_ec","acceptance_ec",1800,800);
c_acceptance_ec->Divide(2,1);
for(int k=6;k<8;k++){
c_acceptance_ec->cd(k-6+1);
hacceptance[k]->Divide(hacceptance[k],hgen);
hacceptance[k]->Scale(100);
hacceptance[k]->Draw("colz");
char hsttitle[80];
if (k==6) sprintf(hsttitle,"acceptance at EC largeangle;theta (degree);P (GeV)");
if (k==7) sprintf(hsttitle,"acceptance at EC forwardangle;theta (degree);P (GeV)");
hacceptance[k]->SetTitle(hsttitle);
}

TCanvas *c_acceptance_ec_1D = new TCanvas("acceptance_ec_1D","acceptance_ec_1D",1800,800);
c_acceptance_ec_1D->Divide(2,2);
for(int k=6;k<8;k++){
c_acceptance_ec_1D->cd(k-6+1);
hacceptance_mom[k]->Divide(hacceptance_mom[k],hgen_mom);
hacceptance_mom[k]->Scale(100);
hacceptance_mom[k]->Draw();
c_acceptance_ec_1D->cd(2+k-6+1);
hacceptance_theta[k]->Divide(hacceptance_theta[k],hgen_theta);
hacceptance_theta[k]->Scale(100);
hacceptance_theta[k]->Draw();
}

TCanvas *c_acceptance_cc = new TCanvas("acceptance_cc","acceptance_cc",1800,800);
c_acceptance_cc->Divide(2,1);
for(int k=8;k<10;k++){
c_acceptance_cc->cd(k-8+1);
hacceptance[k]->Divide(hacceptance[k],hgen);
hacceptance[k]->Scale(100);
hacceptance[k]->Draw("colz");
char hsttitle[80];
if (k==8) sprintf(hsttitle,"acceptance at CC lightgas;theta (degree);P (GeV)");
if (k==9) sprintf(hsttitle,"acceptance at CC heavygas;theta (degree);P (GeV)");
hacceptance[k]->SetTitle(hsttitle);
}

TCanvas *c_acceptance_cc_1D = new TCanvas("acceptance_cc_1D","acceptance_cc_1D",1800,800);
c_acceptance_cc_1D->Divide(2,2);
for(int k=8;k<10;k++){
c_acceptance_cc_1D->cd(k-8+1);
hacceptance_mom[k]->Divide(hacceptance_mom[k],hgen_mom);
hacceptance_mom[k]->Scale(100);
hacceptance_mom[k]->Draw();
c_acceptance_cc_1D->cd(2+k-8+1);
hacceptance_theta[k]->Divide(hacceptance_theta[k],hgen_theta);
hacceptance_theta[k]->Scale(100);
hacceptance_theta[k]->Draw();
}

outputfile->Write();
outputfile->Flush();

}
