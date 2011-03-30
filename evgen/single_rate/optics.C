void optics()
{
  
  Float_t x[5],y[5],z[5];
  Float_t mom,theta,phi,vertexz;
  

  TFile *file = new TFile("convert_single.root");
  TTree *T = (TTree*)file->Get("h9500");
  
  T->SetBranchAddress("hit1_x",&x[0]);
  T->SetBranchAddress("hit2_x",&x[1]);
  T->SetBranchAddress("hit3_x",&x[2]);
  T->SetBranchAddress("hit4_x",&x[3]);
  T->SetBranchAddress("hit5_x",&x[4]);
  T->SetBranchAddress("hit1_y",&y[0]);
  T->SetBranchAddress("hit2_y",&y[1]);
  T->SetBranchAddress("hit3_y",&y[2]);
  T->SetBranchAddress("hit4_y",&y[3]);
  T->SetBranchAddress("hit5_y",&y[4]);
  T->SetBranchAddress("hit1_z",&z[0]);
  T->SetBranchAddress("hit2_z",&z[1]);
  T->SetBranchAddress("hit3_z",&z[2]);
  T->SetBranchAddress("hit4_z",&z[3]);
  T->SetBranchAddress("hit5_z",&z[4]);
  T->SetBranchAddress("p_e",&mom);
  T->SetBranchAddress("theta_e",&theta);
  T->SetBranchAddress("phi_e",&phi);
  T->SetBranchAddress("vertexz",&vertexz);
  
  TFile *gile = new TFile("optics.root","RECREATE");
  TTree *t1 = new TTree("T","filter");

  Float_t x0,y0,R,rotangle[3];
  t1->Branch("hit1_x",&x[0],"hit1_x/F");
  t1->Branch("hit2_x",&x[1],"hit2_x/F");
  t1->Branch("hit3_x",&x[2],"hit3_x/F");
  t1->Branch("hit4_x",&x[3],"hit4_x/F");
  t1->Branch("hit5_x",&x[4],"hit5_x/F");
  t1->Branch("hit1_y",&y[0],"hit1_y/F");
  t1->Branch("hit2_y",&y[1],"hit2_y/F");
  t1->Branch("hit3_y",&y[2],"hit3_y/F");
  t1->Branch("hit4_y",&y[3],"hit4_y/F");
  t1->Branch("hit5_y",&y[4],"hit5_y/F");
  t1->Branch("hit1_z",&z[0],"hit1_z/F");
  t1->Branch("hit2_z",&z[1],"hit2_z/F");
  t1->Branch("hit3_z",&z[2],"hit3_z/F");
  t1->Branch("hit4_z",&z[3],"hit4_z/F");
  t1->Branch("hit5_z",&z[4],"hit5_z/F");
  t1->Branch("p_e",&mom,"p_e/F");
  t1->Branch("theta_e",&theta,"theta_e/F");
  t1->Branch("phi_e",&phi,"phi_e/F");
  t1->Branch("vertexz",&vertexz,"vertexz/F");
  t1->Branch("x0",&x0,"x0/F");
  t1->Branch("y0",&y0,"y0/F");
  t1->Branch("R",&R,"R/F");
  // t1->Branch("rotangle1",&rotangle[0],"rotangle1/F");
  //   t1->Branch("rotangle2",&rotangle[1],"rotangle2/F");
  //   t1->Branch("rotangle3",&rotangle[2],"rotangle3/F");
  Float_t recon_p,recon_theta[3],recon_phi,recon_vertexz;
  t1->Branch("recon_p",&recon_p,"recon_p/F");
  t1->Branch("recon_theta",&recon_theta[0],"recon_theta1/F");
  // t1->Branch("recon_theta2",&recon_theta[1],"recon_theta2/F");
  //   t1->Branch("recon_theta3",&recon_theta[2],"recon_theta3/F");
  // Float_t a1,a2,L;
  
  //   t1->Branch("a1",&a1,"a1/F");
  //   t1->Branch("a2",&a2,"a2/F");
  

  t1->Branch("recon_phi",&recon_phi,"recon_phi/F");
  t1->Branch("recon_vertexz",&recon_vertexz,"recon_vertexz/F");
  t1->SetDirectory(gile);


 
  Int_t flag=0;
  Float_t temp1,temp2,temp3,temp4;
  for (Int_t i=1;i!=T->GetEntries();i++){
    T->GetEntry(i);
    
   //  for (Int_t j=0;j!=4;j++){
//       x[j] = x[j] + 0.02*gRandom->Gaus();
//       y[j] = y[j] + 0.02*gRandom->Gaus();
//     }


    if (x[2]!=x[1]&&x[1]!=x[0]&&x[2]!=x[0]){
      temp3 = (x[1]*x[1] + y[1]*y[1]) -(x[0]*x[0] + y[0]*y[0]);
      temp4 = (x[2]*x[2] + y[2]*y[2]) -(x[1]*x[1] + y[1]*y[1]);
      
      temp1 = temp3 * (x[2]-x[1]) - temp4 * (x[1]-x[0]);
      temp2 = 2.*(y[1]-y[0])*(x[2]-x[1])-2.*(y[2]-y[1])*(x[1]-x[0]);
      
      if (temp2!=0.){
	y0 = temp1/temp2;
	x0 = (temp3-2.*(y[1]-y[0])*y0)/2./(x[1]-x[0]);
	R = sqrt((x0-x[0])*(x0-x[0])+(y0-y[0])*(y0-y[0]));  
	flag=1;
      }
    
      // if (flag==1)
      // cout << R/mom/sin(theta/180.*3.1415926) << endl;
      rotangle[0] = 2.*asin(sqrt((x[1]-x[0])*(x[1]-x[0])+(y[1]-y[0])*(y[1]-y[0]))/2./R);
      rotangle[1] = 2.*asin(sqrt((x[2]-x[1])*(x[2]-x[1])+(y[2]-y[1])*(y[2]-y[1]))/2./R);
      rotangle[2] = 2.*asin(sqrt((x[2]-x[0])*(x[2]-x[0])+(y[2]-y[0])*(y[2]-y[0]))/2./R);
      
      
      recon_theta[0] = (atan(R*rotangle[0]/(z[1]-z[0]))/3.1415926*180.+atan(R*rotangle[1]/(z[2]-z[1]))/3.1415926*180.+atan(R*rotangle[2]/(z[2]-z[0]))/3.1415926*180.)/3.;
      if (mom<2.){
	recon_theta[0]-=7.134471-110.749621*mom/10.+621.062337*pow(mom/10.,2)-1199.982860*pow(mom/10.,3)-1.90139e-02;
	//cout << recon_theta[0]-theta << "\t" << 1.70858*exp(-1.66737*mom) << endl;
      }else if (mom>=2.&&mom<5.){
	recon_theta[0]-=0.866207-4.803766*mom/10.+9.700155*pow(mom/10.,2)-6.701193*pow(mom/10.,3)-1.90139e-02;
      }else{
	recon_theta[0]-=0.105870-0.142202*mom/10.+0.067025*pow(mom/10.,2)-1.90139e-02;
      }
      
      recon_p = R/sin(recon_theta[0]/180.*3.1415926)/(211.507352-0.362817*recon_theta[0]+0.075475*pow(recon_theta[0],2));
      if (R<=150.){
	recon_p=recon_p/(2.148768-5.693577*R/100.+11.300216*pow(R/100.,2)-11.088944*pow(R/100.,3)+5.352901*pow(R/100.,4)-1.015195*pow(R/100.,5));
      }
      
      if (phi>180.) phi-=360.;

      if (x0<=0.){
	recon_phi = atan(y0/x0)/3.1415926*180.+90.;
      }else if(x0>0.){
	recon_phi = atan(y0/x0)/3.1415926*180.-90.;
      }
      if (recon_phi>150.&&phi<-100){
	recon_phi=recon_phi-360.;
      }
      
      if (recon_p>5.){
	recon_phi+=7.622193-1.035305*recon_p+0.045715*pow(recon_p,2);
      }else if (recon_p<=5. &&recon_p>2.){
	recon_phi+=21.745970-9.236038*recon_p+1.684827*pow(recon_p,2)-0.112270*pow(recon_p,3);
      }else{
	recon_phi+=56.604832-61.676525*recon_p+28.903270*pow(recon_p,2)-4.955798*pow(recon_p,3);
      }

      if (recon_theta[0]<14.){
	recon_phi+=1.514944-0.122757*recon_theta[0];
      }else{
	recon_phi+=3.798204-0.288034*recon_theta[0];
      }
      
      
      recon_vertexz = 622.988226 -1.009191*sqrt(x[3]**2+y[3]**2)/tan(recon_theta[0]/180.*3.1415926);
      
      if (recon_p>5.){
 	recon_vertexz -= 63.850300 -264.493908*recon_p/10.+430.713846*pow(recon_p/10.,2)-326.026639*pow(recon_p/10.,3)+94.673286*pow(recon_p/10.,4);
      }else if (recon_p<=5. && recon_p>2.){
	recon_vertexz -= 270.804985 - 222.1657780*recon_p + 74.44942853*recon_p*recon_p - 11.56588*pow(recon_p,3) + 0.68687*pow(recon_p,4);

      }else{
  	recon_vertexz -= 1282.426854 - 2414.3316471*recon_p + 1922.8097 *pow(recon_p,2) - 724.607200065*pow(recon_p,3) + 106.0223*pow(recon_p,4);
      }

      recon_vertexz+=-3.231150+1.383760*recon_theta[0]-0.139851*recon_theta[0]*recon_theta[0]+0.003959*pow(recon_theta[0],3)-0.579271+0.047484*recon_theta[0];
      
      
  
      t1->Fill();
      if (i%1000==0) cout << i << "\t" << recon_vertexz << endl;
    }

    
    
  }
  
  //t1->Write();
  gile->Write();
  gile->Close();
  file->Close();
  
}
