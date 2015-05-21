//this version of the code is based on Zhiwen's new pim simulation
//momentum range: LA(>1GeV), FA(>1GeV)
#include "SOLGEM.h"
#include "THaSoleGEMSim.h"
#include "THaSolenoid.h"
#include "THaGemHit.h"
#include "THaGemTrack.h"
#include <iostream>

using namespace std;

ClassImp(SOLGEM)

#define MC_PREFIX "sol."

SOLGEM::SOLGEM( const char* name, const char* desc, THaApparatus* app )
  : THaTrackingDetector(name,desc,app){
  for (Int_t i=0;i!=5;i++){
    hit[i] = new TClonesArray("THaGemHit", 0);
    goodhit[i] = new TClonesArray("THaGemHit", 0);
    fnhit[i]=0;
    fngoodhit[i]=0;
  }
  fTracks = new TClonesArray("THaGemTrack",0);
  fntrack = 0;
  fGoodTracks = new TClonesArray("THaGemTrack",0);
  fngoodtrack = 0;
  //-------------add for EC, using THaGemHit class for now---------------//
  EC_hit = new TClonesArray("THaGemHit", 0);
  nEChit = 0;
  DefineVariables();
}

SOLGEM::~SOLGEM()
{
  Clear();
  delete fTracks;
  delete fGoodTracks;
  /////////////////////
  //delete hit_plane1;
  for (Int_t i=0;i!=5;i++){
    delete hit[i];
    delete goodhit[i];
  }
  //------------add for EC-----------------//
  delete EC_hit;
  //--------------------------------------//
  DefineVariables( THaAnalysisObject::kDelete );
}

void SOLGEM::Clear( Option_t* opt )
{
  for (Int_t i=0;i!=5;i++){
    hit[i]->Delete();
    fnhit[i]=0;
    goodhit[i]->Delete();
    fngoodhit[i]=0;
  }
  //------------add for EC----------//
  EC_hit->Delete();
  nEChit = 0;
  //--------------------------------//
  for (Int_t i=0;i!=fntrack;i++){
    ((THaGemTrack*)(fTracks->At(i)))->Clear();
  }
  
  for (Int_t i=0;i!=fngoodtrack;i++){
    ((THaGemTrack*)(fGoodTracks->At(i)))->Clear();
  }

  fTracks->Delete();
  fntrack = 0;
  fGoodTracks->Delete();
  fngoodtrack = 0;
}

Int_t SOLGEM::DefineVariables( THaAnalysisObject::EMode mode )
{
  const char* const here = "SOLGEM::DefineVariables";
  if( mode == THaAnalysisObject::kDefine && fIsSetup ) 
    return THaAnalysisObject::kOK;
  fIsSetup = ( mode == THaAnalysisObject::kDefine );

  RVarDef vars[] = {
    {"track.n", "Number of tracks", "Get_ngoodtrack()"},
    {"track.charge","charge","fGoodTracks.THaGemTrack.Get_Charge()"},
    {"track.flag","angle flag","fGoodTracks.THaGemTrack.Get_Angleflag()"},
    {"track.Rvalue","R value","fGoodTracks.THaGemTrack.Get_Rvalue()"},
    {"track.Chi2", "Chi square of the fit of the track", "fGoodTracks.THaGemTrack.Get_Chi2()"},
    {"track.Vertex", "reconstructed vertex z postion of the track", "fGoodTracks.THaGemTrack.Get_Vertex()"},
    {"track.Theta", "reconstructed polar angle", "fGoodTracks.THaGemTrack.Get_Theta()"},
    {"track.nhit","number of hits","fGoodTracks.THaGemTrack.Get_nhit()"},
    {"track.Thetamin","minimal estimate for the theta angle of the track","fGoodTracks.THaGemTrack.Get_Thetamin()"},
    {"track.Thetamax","maximal estimate for the theta angle of the track","fGoodTracks.THaGemTrack.Get_Thetamax()"},
    {"track.Mommin","minimal estimate for the momentum of the track","fGoodTracks.THaGemTrack.Get_Mommin()"},
    {"track.Mommax","maximal estimate for the momentum of the track","fGoodTracks.THaGemTrack.Get_Mommax()"},
    {"track.hit1_x","hit 1 x information","fGoodTracks.THaGemTrack.Get_hit1_x()"},
    {"track.hit2_x","hit 2 x information","fGoodTracks.THaGemTrack.Get_hit2_x()"},
    {"track.hit3_x","hit 3 x information","fGoodTracks.THaGemTrack.Get_hit3_x()"},
    {"track.hit4_x","hit 4 x information","fGoodTracks.THaGemTrack.Get_hit4_x()"},
    {"track.hit5_x","hit 5 x information","fGoodTracks.THaGemTrack.Get_hit5_x()"},
    {"track.hit1_y","hit 1 y information","fGoodTracks.THaGemTrack.Get_hit1_y()"},
    {"track.hit2_y","hit 2 y information","fGoodTracks.THaGemTrack.Get_hit2_y()"},
    {"track.hit3_y","hit 3 y information","fGoodTracks.THaGemTrack.Get_hit3_y()"},
    {"track.hit4_y","hit 4 y information","fGoodTracks.THaGemTrack.Get_hit4_y()"},
    {"track.hit5_y","hit 5 y information","fGoodTracks.THaGemTrack.Get_hit5_y()"},
    {"track.hit1_z","hit 1 z information","fGoodTracks.THaGemTrack.Get_hit1_z()"},
    {"track.hit2_z","hit 2 z information","fGoodTracks.THaGemTrack.Get_hit2_z()"},
    {"track.hit3_z","hit 3 z information","fGoodTracks.THaGemTrack.Get_hit3_z()"},
    {"track.hit4_z","hit 4 z information","fGoodTracks.THaGemTrack.Get_hit4_z()"},
    {"track.hit5_z","hit 5 z information","fGoodTracks.THaGemTrack.Get_hit5_z()"},
    {"track.hit1_r","hit 1 r information","fGoodTracks.THaGemTrack.Get_hit1_r()"},
    {"track.hit2_r","hit 2 r information","fGoodTracks.THaGemTrack.Get_hit2_r()"},
    {"track.hit3_r","hit 3 r information","fGoodTracks.THaGemTrack.Get_hit3_r()"},
    {"track.hit4_r","hit 4 r information","fGoodTracks.THaGemTrack.Get_hit4_r()"},
    {"track.hit5_r","hit 5 r information","fGoodTracks.THaGemTrack.Get_hit5_r()"},
    {"track.hit1_phi","hit 1 phi information","fGoodTracks.THaGemTrack.Get_hit1_phi()"},
    {"track.hit2_phi","hit 2 phi information","fGoodTracks.THaGemTrack.Get_hit2_phi()"},
    {"track.hit3_phi","hit 3 phi information","fGoodTracks.THaGemTrack.Get_hit3_phi()"},
    {"track.hit4_phi","hit 4 phi information","fGoodTracks.THaGemTrack.Get_hit4_phi()"},
    {"track.hit5_phi","hit 5 phi information","fGoodTracks.THaGemTrack.Get_hit5_phi()"},
    {"track.hit1_layer","hit 1 layer information","fGoodTracks.THaGemTrack.Get_hit1_layer()"},
    {"track.hit2_layer","hit 2 layer information","fGoodTracks.THaGemTrack.Get_hit2_layer()"},
    {"track.hit3_layer","hit 3 layer information","fGoodTracks.THaGemTrack.Get_hit3_layer()"},
    {"track.hit4_layer","hit 4 layer information","fGoodTracks.THaGemTrack.Get_hit4_layer()"},
    {"track.hit5_layer","hit 5 layer information","fGoodTracks.THaGemTrack.Get_hit5_layer()"},
    {"track.hit1_qu","hit 1 qu information","fGoodTracks.THaGemTrack.Get_hit1_qu()"},
    {"track.hit2_qu","hit 2 qu information","fGoodTracks.THaGemTrack.Get_hit2_qu()"},
    {"track.hit3_qu","hit 3 qu information","fGoodTracks.THaGemTrack.Get_hit3_qu()"},
    {"track.hit4_qu","hit 4 qu information","fGoodTracks.THaGemTrack.Get_hit4_qu()"},
    {"track.hit5_qu","hit 5 qu information","fGoodTracks.THaGemTrack.Get_hit5_qu()"},
    {"track.hit1_qv","hit 1 qv information","fGoodTracks.THaGemTrack.Get_hit1_qv()"},
    {"track.hit2_qv","hit 2 qv information","fGoodTracks.THaGemTrack.Get_hit2_qv()"},
    {"track.hit3_qv","hit 3 qv information","fGoodTracks.THaGemTrack.Get_hit3_qv()"},
    {"track.hit4_qv","hit 4 qv information","fGoodTracks.THaGemTrack.Get_hit4_qv()"},
    {"track.hit5_qv","hit 5 qv information","fGoodTracks.THaGemTrack.Get_hit5_qv()"},
    {"track.hit1_TrueHit","hit 1 true hit information","fGoodTracks.THaGemTrack.Get_hit1_TrueHit()"},
    {"track.hit2_TrueHit","hit 2 true hit information","fGoodTracks.THaGemTrack.Get_hit2_TrueHit()"},
    {"track.hit3_TrueHit","hit 3 true hit information","fGoodTracks.THaGemTrack.Get_hit3_TrueHit()"},
    {"track.hit4_TrueHit","hit 4 true hit information","fGoodTracks.THaGemTrack.Get_hit4_TrueHit()"},
    {"track.hit5_TrueHit","hit 5 true hit information","fGoodTracks.THaGemTrack.Get_hit5_TrueHit()"},
    {0}
  };

  Int_t ret = 
    THaAnalysisObject::DefineVarsFromList( vars, 
					   THaAnalysisObject::kRVarDef, 
					   mode, "", this, MC_PREFIX, here );

  return ret;
}


THaAnalysisObject::EStatus SOLGEM::Init( const TDatime& date )
{
  return fStatus = kOK;
}


Int_t SOLGEM::Decode( const THaEvData& evdata )
{
  Clear();
  THaSoleSimEvent* simEvent = (THaSoleSimEvent*)(((THaSolenoid*)GetApparatus())->GetSimEvent());
  //-------------------------add for EC-------------------------//
  TIter nextECHit(&simEvent->EChits);
  while(THaSoleSimHit *hit_ec = static_cast<THaSoleSimHit*>( nextECHit() ))
    {
      new ((*EC_hit)[nEChit++]) THaGemHit();
      //cout<<hit_laec->x<<" "<<hit_laec->z<<endl;
      //add qu and qv here
      ((THaGemHit*)EC_hit->Last())->Set_content(hit_ec->x, hit_ec->y, hit_ec->z, hit_ec->phi, hit_ec->r, hit_ec->qu, hit_ec->qv, hit_ec->ex, hit_ec->ey, hit_ec->TrueHit);
    }

  //------------------------------------------------------------//
  for (Int_t i=0;i!=5;i++){
    TIter nextHit(&simEvent->gemrealhits[i]);
    while( THaSoleSimHit *hit1 = static_cast<THaSoleSimHit*>( nextHit() )) {
      new ((*hit[i])[fnhit[i]++]) THaGemHit();
      //add qu and qv here
      //cout<<hit1->ex<<endl;
      ((THaGemHit*)hit[i]->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r, hit1->qu, hit1->qv, hit1->ex, hit1->ey, hit1->TrueHit);
      ((THaGemHit*)hit[i]->Last())->Calculate_layer();

      //////////////////////////////////////
      /*Int_t tempnhit = fnhit[i]-1;
      if (i==0)
	{
	  new ((*hit_plane1)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane1->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane1->Last())->Calculate_layer();
	}
      else if (i==1)
	{
	  new ((*hit_plane2)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane2->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane2->Last())->Calculate_layer(); 
	}
      else if (i==2)
	{
	  new ((*hit_plane3)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane3->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane3->Last())->Calculate_layer(); 
	}
      else if (i==3)
	{
	  new ((*hit_plane4)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane4->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane4->Last())->Calculate_layer();
	}
      else if (i==4)
	{
	  new ((*hit_plane5)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane5->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane5->Last())->Calculate_layer();
	}
      else if (i==5)
	{
	   new ((*hit_plane6)[tempnhit]) THaGemHit();
	  ((THaGemHit*)hit_plane6->Last())->Set_content(hit1->x,hit1->y,hit1->z,hit1->phi,hit1->r);
	  ((THaGemHit*)hit_plane6->Last())->Calculate_layer();
	  }*/
	}
  }
  


  return 0;
}
//(check the candidate tracks from the function FindTrack(), a condidate track
//need to has at least three hits, three of them can determine a circle, its
//center and radius.)
Int_t SOLGEM::CoarseTrack(TClonesArray& tracks){
  //(finding candidate tracks according to the 11 track patterns 5 for Large
  //angle events and 6 for forward angle events
  FindTrack(1,0);
  FindTrack(1,1);
  FindTrack(1,2);
  FindTrack(1,3);
  FindTrack(1,4);
  FindTrack(1,5);

  //cout << fntrack << endl;
  if (fntrack > 50000)
  {
    for (Int_t i=0; i!=fTracks->GetLast()+1; i++)
	{
	  THaGemTrack *thistrack = (THaGemTrack*)(fTracks->At(i));
	 thistrack->SetBad(1);
	}
	  //fTracks->Clear();
	  cout<<"too many candidate tracks from the first step, skip this event: "<<fntrack<<endl;
  
    return 0;
    	
  }
  else
  {

  /*cout<<" total number of tracks: "<<fntrack<<endl;
  for (Int_t i=0; i!=fTracks->GetLast()+1; i++)
    {
      THaGemTrack *thistrack = (THaGemTrack*)(fTracks->At(i));
      cout<<"number of hits on this track: "<<thistrack->Get_nhit()<<endl;
      for (Int_t j=0; j!=thistrack->Get_nhit(); j++)
        {
          THaGemHit *thishit = (THaGemHit*)(thistrack->Get_hits()->At(j));
          cout<<thishit->Get_x()<<endl;
          cout<<thishit->Get_layer()<<endl;
        }
	}*/
 

  //(Rmom is the radius of the circle and Rc is the distance between the center
  //of the circle to the beam line)
  //Int_t nmom;
  Int_t c_count = 0;
  Double_t par[4];
  Double_t temp_chi2, temp_vertexz, temp_vertexr;
  //Float_t Rmom[20]={0},Xc[20]={0},Yc[20]={0},Rc[20]={0};
  for (Int_t i=0;i!=fTracks->GetLast()+1;i++){
     THaGemTrack *thistrack = (THaGemTrack*)(fTracks->At(i));
     if (thistrack->Get_Angleflag()==1 && thistrack->Get_nhit()==4){
       c_count = Check_Q_Asym(thistrack);
       if (c_count<3)
	 {
	   thistrack->SetBad(1);
	   continue;
	 }
       else
	 {
	   thistrack->SetBad(0);
	 }
       FitTrack(thistrack, par, 4, &temp_chi2);
       Vertex_Reconstruction(par, 4, &temp_vertexz, &temp_vertexr);
       if (temp_vertexz<0.35 && temp_vertexz>-0.15 && temp_vertexr< 0.2)
	 {
	   thistrack->SetBad(0);
	   thistrack->Set_Chi2(temp_chi2);
	   thistrack->Set_Vertex(temp_vertexz);
	   thistrack->Set_Theta(Polar_Angle_Reconstruction(par, 4));
	 }
       else
	 {
	   thistrack->SetBad(1);
	 }
       /*THaGemHit *hit1 = (THaGemHit*)(thistrack->Get_hits()->At(0));
       THaGemHit *hit2 = (THaGemHit*)(thistrack->Get_hits()->At(1));
       THaGemHit *hit3 = (THaGemHit*)(thistrack->Get_hits()->At(2));
       THaGemHit *hit4 = (THaGemHit*)(thistrack->Get_hits()->At(3));
        Int_t flag = 0;
	Float_t recon_theta=-1000;
	Float_t recon_vertex=-1000;
       //--------------add for EC-----------------//
        if (hit1->Get_layer()==1 && hit2->Get_layer()==3 && hit3->Get_layer()==4 && hit4->Get_layer()==5)
	  {
	    recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.3153);
	    recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
	    recon_vertex = recon_vertex*0.964069-157.786;
	  }
	else if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==4 && hit4->Get_layer()==5)
	  {
	    recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.3227);
	    recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
	    recon_vertex = recon_vertex*0.971302-156.344;
	  }
	else if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==3 && hit4->Get_layer()==5)
	  {
	    recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.3048);
	    recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
	    recon_vertex = recon_vertex*0.969658-156.629; 
	  }
	else if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==3 && hit4->Get_layer()==4)
	  {
	    recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.2927);
	    recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
	    recon_vertex = recon_vertex*0.964888-157.549; 
	  }
	else
	  {
	    recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.4128);
	    recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
	    recon_vertex = recon_vertex*0.926-136.745; 
	  }
	if (recon_vertex<-380. || recon_vertex>-320.)
	  {
	    flag = 0;
	  }
	else
	  {
	    flag = 1;
	  }
	  
       //----------------------------------------//
       //flag = 1;
       if (flag == 1)
	 {
	   nmom  = 0;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit2->Get_x(),hit2->Get_y(),hit3->Get_x(),hit3->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit2->Get_x(),hit2->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit3->Get_x(),hit3->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit2->Get_x(),hit2->Get_y(),hit3->Get_x(),hit3->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   
	   //1234
	   if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==3 && hit4->Get_layer()==4){
	     //123
	     if ( Rmom[0]-(-2.91876+1.0063*Rc[0])< 5. && Rmom[0]-(-2.91876+1.0063*Rc[0])>-5.){
	     }else{
	       flag = 0;
	     }
	     //124
	     if ( Rmom[1]-(-2.73123+1.00584*Rc[1])< 5 && Rmom[1]-(-2.73123+1.00584*Rc[1])>-5.){
	     }else{
	       flag = 0;
	     }
	     //134
	     if ( Rmom[2]-(-2.55778+1.00541*Rc[2])< 5 && Rmom[2]-(-2.55778+1.00541*Rc[2])>-5){
	     }else{
	       flag = 0;
	     }
	     //234
	     if (Rmom[3]-(-2.40568+1.00505*Rc[3])<5. && Rmom[3]-(-2.40568+1.00505*Rc[3])>-5.){
	     }else{
	       flag = 0;
	     }
	     //cross-check
	     if (sqrt((Xc[3]-Xc[2])*(Xc[3]-Xc[2])+(Yc[3]-Yc[2])*(Yc[3]-Yc[2]))<45.*sqrt(2) && Rmom[3]-Rmom[2]-(-0.0511964+1.01637*(Rc[3]-Rc[2]))<2. && Rmom[3]-Rmom[2]-(0.0118574+1.01723*(Rc[3]-Rc[2]))>-1.5){
	     }else{
	       flag = 0;
	     }
	   }
	   
	   //1235
	   if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==3 && hit4->Get_layer()==5){
	     //123
	     if ( Rmom[0]-(-2.91876+1.0063*Rc[0])< 5.&& Rmom[0]-(-2.91876+1.0063*Rc[0])>-5){
	     }else{
	       flag = 0;
	     }
	     //125
	     if ( Rmom[1]-(-2.40645+1.00509*Rc[1])< 5.&& Rmom[1]-(-2.40645+1.00509*Rc[1])>-5){
	     }else{
	       flag = 0;
	     }
	     //135
	     if ( Rmom[2]-(-2.09502+1.00439*Rc[2])<5 && Rmom[2]-(-2.09502+1.00439*Rc[2])>-5){
	     }else{
	       flag = 0;
	     }
	     //235
	     if ( Rmom[3]-(-1.82887+1.00382*Rc[3])< 5&& Rmom[3]-(-1.82887+1.00382*Rc[3])>-5){
	     }else{
	       flag = 0;
	     }
	     if (sqrt((Xc[3]-Xc[2])*(Xc[3]-Xc[2])+(Yc[3]-Yc[2])*(Yc[3]-Yc[2]))<30.*sqrt(2) && Rmom[3]-Rmom[2]-(0.0877964+1.01622*(Rc[3]-Rc[2]))<2. && Rmom[3]-Rmom[2]-(0.0877964+1.01622*(Rc[3]-Rc[2]))>-1){
	     }else{
	       flag = 0;
	     }
	   }
	   
	   //1245
	   if (hit1->Get_layer()==1 && hit2->Get_layer()==2 && hit3->Get_layer()==4 && hit4->Get_layer()==5){
	     //124
	     if ( Rmom[0]-(-2.73123+1.00584*Rc[0])< 5&& Rmom[0]-(-2.73123+1.00584*Rc[0])>-5){
	     }else{
	       flag = 0;
	     }
	     //125
	     if ( Rmom[1]-(-2.40645+1.00509*Rc[1])< 5&& Rmom[1]-(-2.40645+1.00509*Rc[1])>-5){
	     }else{
	       flag = 0;
	     }
	     //145
	     if ( Rmom[2]-(-1.46881+1.00309*Rc[2])<5 && Rmom[2]-(-1.46881+1.00309*Rc[2])>-5){
	     }else{
	       flag = 0;
	     }
	     //245
	     if ( Rmom[3]-(-1.04429+1.00222*Rc[3])<5 && Rmom[3]-(-1.04429+1.00222*Rc[3])>-5){
	     }else{
	       flag = 0;
	     }
	     if (sqrt((Xc[3]-Xc[2])*(Xc[3]-Xc[2])+(Yc[3]-Yc[2])*(Yc[3]-Yc[2]))<20.*sqrt(2) && Rmom[3]-Rmom[2]-(0.244245+0.981558*(Rc[3]-Rc[2]))< 2&& Rmom[3]-Rmom[2]-(0.244245+0.981558*(Rc[3]-Rc[2]))>-1){
	     }else{
	       flag = 0;
	     }
	   }
	   
	   
	   //1345
	   if (hit1->Get_layer()==1 && hit2->Get_layer()==3 && hit3->Get_layer()==4 && hit4->Get_layer()==5){
	     //134
	     if ( Rmom[0]-(-2.55778+1.00541*Rc[0])< 5&& Rmom[0]-(-2.55778+1.00541*Rc[0])>-5){
	     }else{
	       flag = 0;
	     }
	     //135
	     if ( Rmom[1]-(-2.09502+1.00439*Rc[1])<5 && Rmom[1]-(-2.09502+1.00439*Rc[1])>-5){
	     }else{
	       flag = 0;
	     }
	     //145
	     if ( Rmom[2]-(-1.46881+1.00309*Rc[2])<5 && Rmom[2]-(-1.46881+1.00309*Rc[2])>-5){
	     }else{
	       flag = 0;
	     }
	     //345
	     if ( Rmom[3]-(-0.168279+1.00048*Rc[3])<5 && Rmom[3]-(-0.168279+1.00048*Rc[3])>-5){
	     }else{
	       flag = 0;
	     }
	     if (sqrt((Xc[2]-Xc[1])*(Xc[2]-Xc[1])+(Yc[2]-Yc[1])*(Yc[2]-Yc[1]))<45.*sqrt(2) && Rmom[2]-Rmom[1]-(0.47069+0.980583*(Rc[2]-Rc[1]))< 2 && Rmom[2]-Rmom[1]-(0.47069+0.980583*(Rc[2]-Rc[1]))>-1){
	     }else{
	       flag = 0;
	     }
	   }
	   
	   //2345
	   if (hit1->Get_layer()==2 && hit2->Get_layer()==3 && hit3->Get_layer()==4 && hit4->Get_layer()==5){
	     //234
	     if ( Rmom[0]-(-2.40568+1.00505*Rc[0])<5 && Rmom[0]-(-2.40568+1.00505*Rc[0])>-5){
	     }else{
	       flag = 0;
	     }
	     //235
	     if ( Rmom[1]-(-1.82887+1.00382*Rc[1])< 5&& Rmom[1]-(-1.82887+1.00382*Rc[1])>-5){
	     }else{
	       flag = 0;
	     }
	     //245
	     if ( Rmom[2]-(-1.04429+1.00222*Rc[2])<5 && Rmom[2]-(-1.04429+1.00222*Rc[2])>-5){
	     }else{
	       flag = 0;
	     }
	     //345
	     if ( Rmom[3]-(-0.168279+1.00048*Rc[3])<5 && Rmom[3]-(-0.168279+1.00048*Rc[3])>-5){
	     }else{
	       flag = 0;
	     }
	     if (sqrt((Xc[2]-Xc[1])*(Xc[2]-Xc[1])+(Yc[2]-Yc[1])*(Yc[2]-Yc[1]))<60.*sqrt(2) && Rmom[2]-Rmom[1]-(0.504674+0.98735*(Rc[2]-Rc[1]))<2.5 && Rmom[2]-Rmom[1]-(0.504674+0.98735*(Rc[2]-Rc[1]))>-1.5){
	     }else{
	       flag = 0;
	     }
	   }
	 }      
       
       
       if (flag==1){
	 thistrack->SetBad(0);
	 thistrack->Set_Rvalue((sqrt((Xc[1]-Xc[0])*(Xc[1]-Xc[0])+(Yc[1]-Yc[0])*(Yc[1]-Yc[0]))+sqrt((Xc[2]-Xc[1])*(Xc[2]-Xc[1])+(Yc[2]-Yc[1])*(Yc[2]-Yc[1]))+sqrt((Xc[3]-Xc[2])*(Xc[3]-Xc[2])+(Yc[3]-Yc[2])*(Yc[3]-Yc[2]))+sqrt((Xc[3]-Xc[0])*(Xc[3]-Xc[0])+(Yc[3]-Yc[0])*(Yc[3]-Yc[0])))/4.);
       }else{
	 thistrack->SetBad(1);
       }*/
     }else if (thistrack->Get_Angleflag()==1 && thistrack->Get_nhit()==5){
       c_count = Check_Q_Asym(thistrack);
       if (c_count<3)
	 {
	   thistrack->SetBad(1);
	   continue;
	 }
       else
	 {
	   thistrack->SetBad(0);
	 }
       FitTrack(thistrack, par, 4, &temp_chi2);
       Vertex_Reconstruction(par, 4, &temp_vertexz, &temp_vertexr);
       //cout<<temp_chi2<<endl;
       if (temp_vertexz<0.35 && temp_vertexz>-0.15 && temp_vertexr< 0.02)
	 {
	   thistrack->SetBad(0);
	   thistrack->Set_Chi2(temp_chi2);
	   thistrack->Set_Vertex(temp_vertexz);
	   thistrack->Set_Theta(Polar_Angle_Reconstruction(par, 4));
	 }
       else
	 {
	   thistrack->SetBad(1);
	 }
       /*THaGemHit *hit1 = (THaGemHit*)(thistrack->Get_hits()->At(0));
       THaGemHit *hit2 = (THaGemHit*)(thistrack->Get_hits()->At(1));
       THaGemHit *hit3 = (THaGemHit*)(thistrack->Get_hits()->At(2));
       THaGemHit *hit4 = (THaGemHit*)(thistrack->Get_hits()->At(3));
       THaGemHit *hit5 = (THaGemHit*)(thistrack->Get_hits()->At(4));
       Int_t flag = 0;
       //--------------add for EC-----------------//
       Float_t recon_theta = ((thistrack->Get_Thetamin()+thistrack->Get_Thetamax())/2. - 0.322);
       Float_t recon_vertex = -sqrt(pow(hit1->Get_x(),2)+pow(hit1->Get_y(),2))/tan(recon_theta/180.*3.1415926);
       recon_vertex = recon_vertex*0.973038-155.997;
       if (recon_vertex<-380. || recon_vertex>-320.)
	 {
	   flag = 0;
	 }
       else
	 {
	   flag = 1;
	 }
       //----------------------------------------//
       //flag = 1;
       if (flag == 1)
	 {
	   nmom  = 0;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit2->Get_x(),hit2->Get_y(),hit3->Get_x(),hit3->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit2->Get_x(),hit2->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit3->Get_x(),hit3->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit2->Get_x(),hit2->Get_y(),hit3->Get_x(),hit3->Get_y(),hit4->Get_x(),hit4->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit2->Get_x(),hit2->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit3->Get_x(),hit3->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit2->Get_x(),hit2->Get_y(),hit3->Get_x(),hit3->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit1->Get_x(),hit1->Get_y(),hit4->Get_x(),hit4->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit2->Get_x(),hit2->Get_y(),hit4->Get_x(),hit4->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   calculate(hit3->Get_x(),hit3->Get_y(),hit4->Get_x(),hit4->Get_y(),hit5->Get_x(),hit5->Get_y(),&Rmom[nmom],&Xc[nmom],&Yc[nmom]);
	   Rc[nmom] = sqrt(Xc[nmom]*Xc[nmom]+Yc[nmom]*Yc[nmom]);
	   nmom++;
	   
	   
	   //123
	   if ( Rmom[0]-(-2.91876+1.0063*Rc[0])< 5&& Rmom[0]-(-2.91876+1.0063*Rc[0])>-5){
	   }else{
	     flag = 0;
	   }
	   //124
	   if ( Rmom[1]-(-2.73123+1.00584*Rc[1])< 5&& Rmom[1]-(-2.73123+1.00584*Rc[1])>-5){
	   }else{
	     flag = 0;
	   }
	   //134
	   if ( Rmom[2]-(-2.55778+1.00541*Rc[2])< 5&& Rmom[2]-(-2.55778+1.00541*Rc[2])>-5){
	   }else{
	     flag = 0;
	   }
	   //234
	   if ( Rmom[3]-(-2.40568+1.00505*Rc[3])<5 && Rmom[3]-(-2.40568+1.00505*Rc[3])>-5){
	   }else{
	     flag = 0;
	   }
	   //125
	   if ( Rmom[4]-(-2.40645+1.00509*Rc[4])< 5&& Rmom[4]-(-2.40645+1.00509*Rc[4])>-5){
	   }else{
	     flag = 0;
	   }
	   //135
	   if ( Rmom[5]-(-2.09502+1.00439*Rc[5])<5 && Rmom[5]-(-2.09502+1.00439*Rc[5])>-5){
	   }else{
	     flag = 0;
	   }
	   //235
	   if ( Rmom[6]-(-1.82887+1.00382*Rc[6])< 5&& Rmom[6]-(-1.82887+1.00382*Rc[6])>-5){
	   }else{
	     flag = 0;
	   }
	   //145
	   if ( Rmom[7]-(-1.46881+1.00309*Rc[7])<5 && Rmom[7]-(-1.46881+1.00309*Rc[7])>-5){
	   }else{
	     flag = 0;
	   }
	   //245
	   if ( Rmom[8]-(-1.04429+1.00222*Rc[8])<5 && Rmom[8]-(-1.04429+1.00222*Rc[8])>-5){
	   }else{
	     flag = 0;
	   }
	   //345
	   if ( Rmom[9]-(-0.168279+1.00048*Rc[9])<5 && Rmom[9]-(-0.168279+1.00048*Rc[9])>-5){
	   }else{
	     flag = 0;
	   }
	   //cross-check
	   if (sqrt((Xc[8]-Xc[7])*(Xc[8]-Xc[7])+(Yc[8]-Yc[7])*(Yc[8]-Yc[7]))<20.*sqrt(2) && Rmom[8]-Rmom[7]-(0.244245+0.981558*(Rc[8]-Rc[7]))<2 && Rmom[8]-Rmom[7]-(0.244245+0.981558*(Rc[8]-Rc[7]))>-1){
	   }else{
	     flag = 0;
	   }
	   
	   if (sqrt((Xc[6]-Xc[5])*(Xc[6]-Xc[5])+(Yc[6]-Yc[5])*(Yc[6]-Yc[5]))<30.*sqrt(2)&& Rmom[6]-Rmom[5]-(0.0877964+1.01622*(Rc[6]-Rc[5]))<2 && Rmom[6]-Rmom[5]-(0.0877964+1.01622*(Rc[6]-Rc[5]))>-1){
	   }else{
	     flag = 0;
	   }
	 }
       if (flag==1){
	 thistrack->SetBad(0);
	 thistrack->Set_Rvalue((sqrt((Xc[1]-Xc[0])*(Xc[1]-Xc[0])+(Yc[1]-Yc[0])*(Yc[1]-Yc[0]))
				+sqrt((Xc[2]-Xc[1])*(Xc[2]-Xc[1])+(Yc[2]-Yc[1])*(Yc[2]-Yc[1]))
				+sqrt((Xc[3]-Xc[2])*(Xc[3]-Xc[2])+(Yc[3]-Yc[2])*(Yc[3]-Yc[2]))
				+sqrt((Xc[4]-Xc[3])*(Xc[4]-Xc[3])+(Yc[4]-Yc[3])*(Yc[4]-Yc[3]))
				+sqrt((Xc[5]-Xc[4])*(Xc[5]-Xc[4])+(Yc[5]-Yc[4])*(Yc[5]-Yc[4]))
				+sqrt((Xc[6]-Xc[5])*(Xc[6]-Xc[5])+(Yc[6]-Yc[5])*(Yc[6]-Yc[5]))
				+sqrt((Xc[7]-Xc[6])*(Xc[7]-Xc[6])+(Yc[7]-Yc[6])*(Yc[7]-Yc[6]))
				+sqrt((Xc[8]-Xc[7])*(Xc[8]-Xc[7])+(Yc[8]-Yc[7])*(Yc[8]-Yc[7]))
				+sqrt((Xc[9]-Xc[8])*(Xc[9]-Xc[8])+(Yc[9]-Yc[8])*(Yc[9]-Yc[8]))
				+sqrt((Xc[0]-Xc[9])*(Xc[0]-Xc[9])+(Yc[0]-Yc[9])*(Yc[0]-Yc[9]))
				)/10.);
       }else{
	 thistrack->SetBad(1);
       }*/

     }
  }
  fTracks->Sort();
 

  return 0;
  }
}
//(calculate the coordiante of the center of the circle and its radius by using
//three points, however, this method fails if two points are the same, or if
//all of them are colinear)
void SOLGEM::calculate(Double_t x1,Double_t y1,Double_t x2,Double_t y2,Double_t x3,Double_t y3, Double_t* R,Double_t* Xc, Double_t* Yc){
  if (y1!=y2&& (x1-x2)*(y2-y3)!=(x2-x3)*(y1-y2)){
    *Xc = ((y2-y3)*(x1*x1-x2*x2+y1*y1-y2*y2)/2.-(y1-y2)*(x2*x2-x3*x3+y2*y2-y3*y3)/2.)/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
    *Yc = ((x1*x1-x2*x2+y1*y1-y2*y2)/2.-(*Xc)*(x1-x2))/(y1-y2);
    *R = sqrt((*Xc-x1)*(*Xc-x1)+(*Yc-y1)*(*Yc-y1));
    // cout << *R << "\t";
  }else if (y2!=y3&&(x2-x3)*(y3-y1)!=(x3-x1)*(y2-y3)){
    *Xc = ((y3-y1)*(x2*x2-x3*x3+y2*y2-y3*y3)/2.-(y2-y3)*(x3*x3-x1*x1+y3*y3-y1*y1)/2.)/((x2-x3)*(y3-y1)-(x3-x1)*(y2-y3));
    *Yc = ((x2*x2-x3*x3+y2*y2-y3*y3)/2.-(*Xc)*(x2-x3))/(y2-y3);
    *R = sqrt((*Xc-x2)*(*Xc-x2)+(*Yc-y2)*(*Yc-y2));
   //  cout << *R << "\t";
  }else if (y3!=y1&&(x3-x1)*(y1-y2)!=(x1-x2)*(y3-y1)){
    *Xc = ((y1-y2)*(x3*x3-x1*x1+y3*y3-y1*y1)/2.-(y3-y1)*(x1*x1-x2*x2+y1*y1-y2*y2)/2.)/((x3-x1)*(y1-y2)-(x1-x2)*(y3-y1));
    *Yc = ((x3*x3-x1*x1+y3*y3-y1*y1)/2.-(*Xc)*(x3-x1))/(y3-y1);
    *R = sqrt((*Xc-x3)*(*Xc-x3)+(*Yc-y3)*(*Yc-y3));
    // cout << *R << "\t";
  }else{
    *Xc = 0;
    *Yc = 0;
    *R = 0;
  }
  // cout << endl;
}

//(select tracks that pass the function CoarseTrack(). This function also take
// care another problem. In CoarseTrack(), we force the program to look
//for tracks according to the 11 track pattern
// many of them can actually come from the same track.
//for example, if a track is found in the 1234 pattern
// it will be very likely
//that part of the track will be found in the 123, 234, 134, 124 patterns)
Int_t SOLGEM::FineTrack(TClonesArray& tracks){
  for (Int_t i=0;i!=fTracks->GetLast()+1;i++){
    THaGemTrack *thistrack = (THaGemTrack*)(fTracks->At(i));
    if (thistrack->GetBad()==0){
      Int_t flag = 0;
      /*for (Int_t k=0; k!=fngoodtrack; k++)
	{
	  Int_t checkpoint = 0;
	  THaGemTrack *tmptrack = (THaGemTrack*)(fGoodTracks->At(k));
	  for (Int_t n=0; n!=tmptrack->Get_nhit();n++)
	    {
	     for (Int_t j=0;j!=thistrack->Get_nhit();j++)
	       {
		 THaGemHit *thishit = (THaGemHit*)(thistrack->Get_hits()->At(j));
		 THaGemHit *tmphit = (THaGemHit*)(tmptrack->Get_hits()->At(n));
		 if ((thishit->Get_x()==tmphit->Get_x())&&(thishit->Get_y()==tmphit->Get_y())&&(thishit->Get_layer()==tmphit->Get_layer()))
		  {
		    checkpoint = checkpoint + 1;
		  }
	       } 
	    }
	  if (checkpoint == thistrack->Get_nhit())
	    {
	      flag = 1;
	      break;
	    }
	}*/
      //(this part may not be perfect since the flag will be 1 as long as one 
      //of the hits are the same)
      for (Int_t j=0;j!=thistrack->Get_nhit();j++){
	THaGemHit *thishit = (THaGemHit*)(thistrack->Get_hits()->At(j));
	Int_t layer = thishit->Get_layer();
	for (Int_t k=0;k!=fngoodhit[layer];k++){
	  if ((thishit->Get_x() == ((THaGemHit*)(goodhit[layer]->At(k)))->Get_x()) && (thishit->Get_y() == ((THaGemHit*)(goodhit[layer]->At(k)))->Get_y())){
	    flag = 1;
	  }
       	}
      }
      if (flag == 0){
	THaGemTrack *newtrack = new ((*fGoodTracks)[fngoodtrack++]) THaGemTrack();
	newtrack->SetBad(0);
	newtrack->Set_Angleflag(thistrack->Get_Angleflag());
	newtrack->Set_Charge(thistrack->Get_Charge());
	//newtrack->Set_Rvalue(thistrack->Get_Rvalue());
	//newtrack->Set_Mommin(thistrack->Get_Mommin());
	//newtrack->Set_Mommax(thistrack->Get_Mommax());
	newtrack->Set_Vertex(thistrack->Get_Vertex());
	newtrack->Set_Chi2(thistrack->Get_Chi2());
	newtrack->Set_Thetamin(thistrack->Get_Thetamin());
	newtrack->Set_Thetamax(thistrack->Get_Thetamax());
	newtrack->Set_Theta(thistrack->Get_Theta());
	for (Int_t j=0;j!=thistrack->Get_nhit();j++){
	  THaGemHit *thishit = (THaGemHit*)(thistrack->Get_hits()->At(j));
	  Int_t layer = thishit->Get_layer();
	  new ((*goodhit[layer])[fngoodhit[layer]++]) THaGemHit();
	  //add qu and qv here
	  ((THaGemHit*)goodhit[layer]->Last())->Set_content(thishit->Get_x(),thishit->Get_y(),thishit->Get_z(),thishit->Get_phi(),thishit->Get_r(), thishit->Get_qu(), thishit->Get_qv(), thishit->Get_ex(), thishit->Get_ey(), thishit->Get_TrueHit());
	  newtrack->AddHit(thishit);
	}
      }
    }
  }

  

  
  

  return 0;
}

void SOLGEM::FindTrack(Int_t angleflag, Int_t type){

  Double_t philimit[4][2];
  Double_t deltar[4][2];
  Double_t dr;
  Int_t layer_array[5],nlayer=0;
  Int_t Is_Seed = 1;
  //reverse the layer_array for backward tracking 02/27/2015
  if (angleflag ==1 && type ==0){
    //small angle 1->2->3->4->5
    layer_array[0] = 4;layer_array[1] = 3;layer_array[2] = 2;layer_array[3] = 1;layer_array[4]=0; nlayer=5;
    philimit[3][0]=-0.015; philimit[3][1]=0.015; philimit[2][0]=-0.003;philimit[2][1]=0.003;
    philimit[1][0]=-0.08; philimit[1][1]=0.08; philimit[0][0]=-0.008; philimit[0][1]=0.008;
    deltar[3][0]=0.09; deltar[3][1]=0.25; deltar[2][0]=0.01; deltar[2][1]=0.04;
    deltar[1][0]=0.38; deltar[1][1]=0.98; deltar[0][0]=0.02;deltar[0][1]=0.08;
  }else if (angleflag ==1 && type ==1){
    //small angle 1->3->4->5
    layer_array[0] = 4;layer_array[1] = 3;layer_array[2] = 2;layer_array[3] = 0;nlayer=4;
    philimit[2][0]=-0.02; philimit[2][1]=0.02; philimit[1][0]=-0.08;philimit[1][1]=0.08;
    philimit[0][0]=-0.008; philimit[0][1]=0.008; philimit[3][0]=0; philimit[3][1]=0; 
    deltar[2][0]=0.1; deltar[2][1]=0.28; deltar[1][0]=0.38; deltar[1][1]=0.98;
    deltar[0][0]=0.02; deltar[0][1]=0.08; deltar[3][0]=0.;deltar[3][1]=100.;
  }else if (angleflag ==1 && type ==2){
    //small angle 1->2->4->5
    layer_array[0] = 4;layer_array[1] = 3;layer_array[2] = 1;layer_array[3] = 0;nlayer=4;
    philimit[2][0]=-0.015; philimit[2][1]=0.015; philimit[1][0]=-0.08;philimit[1][1]=0.08;
    philimit[0][0]=-0.008; philimit[0][1]=0.008; philimit[3][0]=0; philimit[3][1]=0;
    deltar[2][0]=0.09; deltar[2][1]=0.25; deltar[1][0]=0.4; deltar[1][1]=1.01;
    deltar[0][0]=0.02; deltar[0][1]=0.08; deltar[3][0]=0.;deltar[3][1]=100.;
  }else if (angleflag ==1 && type ==3){
    //small angle 1->2->3->5
    layer_array[0] = 4;layer_array[1] = 2;layer_array[2] = 1;layer_array[3] = 0;nlayer=4;
    philimit[2][0]=-0.015; philimit[2][1]=0.015; philimit[1][0]=-0.003;philimit[1][1]=0.003;
    philimit[0][0]=-0.08; philimit[0][1]=0.08; philimit[3][0]=0; philimit[3][1]=0;
    deltar[2][0]=0.09; deltar[2][1]=0.25; deltar[1][0]=0.01; deltar[1][1]=0.04;
    deltar[0][0]=0.41; deltar[0][1]=1.05; deltar[3][0]=0.;deltar[3][1]=100.;
  }else if (angleflag ==1 && type ==4){
    //small angle 1->2->3->4
    layer_array[0] = 3;layer_array[1] = 2;layer_array[2] = 1;layer_array[3] = 0;nlayer=4;
    philimit[2][0]=-0.015; philimit[2][1]=0.015; philimit[1][0]=-0.003;philimit[1][1]=0.003;
    philimit[0][0]=-0.08; philimit[0][1]=0.08; philimit[3][0]=0; philimit[3][1]=0;
    deltar[2][0]=0.09; deltar[2][1]=0.25; deltar[1][0]=0.01; deltar[1][1]=0.04;
    deltar[0][0]=0.38; deltar[0][1]=0.98; deltar[3][0]=0.;deltar[3][1]=100.;
  }else if (angleflag ==1 && type ==5){
    //small angle 2->3->4->5
    layer_array[0] = 4;layer_array[1] = 3;layer_array[2] = 2;layer_array[3] = 1;nlayer=4;
    philimit[2][0]=-0.003; philimit[2][1]=0.003; philimit[1][0]=-0.08;philimit[1][1]=0.08;
    philimit[0][0]=-0.008; philimit[0][1]=0.008; philimit[3][0]=0; philimit[3][1]=0;
    deltar[2][0]=0.01; deltar[2][1]=0.04; deltar[1][0]=0.38; deltar[1][1]=0.98;
    deltar[0][0]=0.02; deltar[0][1]=0.08; deltar[3][0]=0.;deltar[3][1]=100.;
  }else{
   //small angle 1->2->3->4->5
    layer_array[0] = 4;layer_array[1] = 3;layer_array[2] = 2;layer_array[3] = 1;layer_array[4]=0; nlayer=5;
    philimit[3][0]=-0.015; philimit[3][1]=0.015; philimit[2][0]=-0.003;philimit[2][1]=0.003;
    philimit[1][0]=-0.08; philimit[1][1]=0.08; philimit[0][0]=-0.008; philimit[0][1]=0.008;
    deltar[3][0]=0.09; deltar[3][1]=0.25; deltar[2][0]=0.01; deltar[2][1]=0.04;
    deltar[1][0]=0.38; deltar[1][1]=0.98; deltar[0][0]=0.02;deltar[0][1]=0.08;
  }
  
  //----------------------------------------------------------------//
  // first layer
  //(most of my modifications for speeding up the program are here
  for (Int_t layer1 = 0; layer1!=hit[layer_array[0]]->GetLast()+1;layer1++){
    THaGemHit *hit1 = (THaGemHit*)hit[layer_array[0]]->At(layer1);
    //for large angle check the hit with EC
    //cout<<"layer 1"<<endl;
    Is_Seed = 1;
    if (angleflag ==1 )
      {
	 for (Int_t ec_count=0; ec_count<EC_hit->GetLast()+1; ec_count++)
	   {
	     THaGemHit *echit = (THaGemHit*)EC_hit->At(ec_count);
	     echit->Set_tmpphi(hit1->Get_phi());
	     dr = echit->Get_r() - hit1->Get_r();
	     if (hit1->Get_layer()==4 && (echit->Get_tmpphi()<0.04 && echit->Get_tmpphi()>-0.04) && (dr < 0.08 && dr > -0.02))
	       {
		 Is_Seed = 1;
	       }
	     else if (hit1->Get_layer()==3 && (echit->Get_tmpphi()<0.04 && echit->Get_tmpphi()>-0.04) && (dr < 0.15 && dr > 0.))
	       {
		 Is_Seed = 1;
	       }
	     else
	       {
		 Is_Seed = 0;
	       }
	   }
      }
    if (Is_Seed == 0) continue;
    THaGemTrack *newtrack = new ((*fTracks)[fntrack++]) THaGemTrack();
    
    //second layer
    for (Int_t layer2 = 0; layer2!=hit[layer_array[1]]->GetLast()+1;layer2++){
      THaGemHit *hit2 = (THaGemHit*)hit[layer_array[1]]->At(layer2);
      //cout<<"layer 2"<<endl;
      hit2->Set_tmpphi(hit1->Get_phi());
      //crude check
      //Float_t mom_min = 0.6,mom_max = 11; 
      Int_t charge = -1;
      //theta goes from 18 to 41 deg, this is actually tan(theta)
      Double_t theta_min,theta_max;

      //Float_t mom_min_save[4],mom_max_save[4];
      Double_t theta_min_save[4],theta_max_save[4];

      theta_min = 0.32492;
      theta_max = 0.86929;
      //based on the hit on the first GEM tracker, give the first estimate for the polar angle of the track
      Range_in_theta(hit1->Get_r(),layer_array[0],hit1->Get_r(),layer_array[0],&theta_min,&theta_max,angleflag); 
      //mom_min_save[0] = mom_min;
      //mom_max_save[0] = mom_max;
      theta_min_save[0] = theta_min;
      theta_max_save[0] = theta_max;
      dr = hit1->Get_r()-hit2->Get_r();
      if(dr<deltar[0][1] && dr>deltar[0][0] && ((hit2->Get_tmpphi() >philimit[0][0]&& hit2->Get_tmpphi() <philimit[0][1]))
	 && Predict_r(hit2->Get_r(), layer_array[1], hit1->Get_r(), layer_array[0], theta_min_save[0], theta_max_save[0])
	 && Range_in_theta(hit2->Get_r(),layer_array[1],hit1->Get_r(),layer_array[0],&theta_min,&theta_max,angleflag)
	 ){
	// third layer
	for (Int_t layer3 = 0; layer3!=hit[layer_array[2]]->GetLast()+1;layer3++){
	  THaGemHit *hit3 = (THaGemHit*)hit[layer_array[2]]->At(layer3);
	  //cout<<"layer 3"<<endl;
	  hit3->Set_tmpphi(hit2->Get_phi());
	  //mom_min_save[1] = mom_min;
	  //mom_max_save[1] = mom_max;
	  theta_min_save[1] = theta_min;
	  theta_max_save[1] = theta_max;
	  dr = hit2->Get_r()-hit3->Get_r();
	  if(dr>deltar[1][0] && dr<deltar[1][1] && ((hit3->Get_tmpphi() >philimit[1][0]&& hit3->Get_tmpphi() <philimit[1][1] && charge==-1))
	     && Predict_r(hit3->Get_r(), layer_array[2], hit2->Get_r(), layer_array[1], theta_min_save[1], theta_max_save[1]) 
	     && Range_in_theta(hit3->Get_r(),layer_array[2],hit2->Get_r(),layer_array[1],&theta_min,&theta_max,angleflag)
	    ) {
	    // check r range
	    if (nlayer>3){
	      // fourth layer
	      for (Int_t layer4 = 0; layer4!=hit[layer_array[3]]->GetLast()+1;layer4++){
		THaGemHit *hit4 = (THaGemHit*)hit[layer_array[3]]->At(layer4);
		//cout<<"layer 4"<<endl;
		hit4->Set_tmpphi(hit3->Get_phi());
		//mom_min_save[2] = mom_min;
		//mom_max_save[2] = mom_max;
		theta_min_save[2] = theta_min;
		theta_max_save[2] = theta_max;
		dr = hit3->Get_r()-hit4->Get_r();
		if(dr>deltar[2][0] && dr<deltar[2][1] && ((hit4->Get_tmpphi() >philimit[2][0]&& hit4->Get_tmpphi() <philimit[2][1] && charge==-1))
		   && Predict_r(hit4->Get_r(), layer_array[3], hit3->Get_r(), layer_array[2], theta_min_save[2], theta_max_save[2])
		   && Range_in_theta(hit4->Get_r(),layer_array[3],hit3->Get_r(),layer_array[2],&theta_min,&theta_max,angleflag)
		  ){
		  if (nlayer>4){
		    
		    // fifth layer
		    for (Int_t layer5 = 0; layer5!=hit[layer_array[4]]->GetLast()+1;layer5++){
		      THaGemHit *hit5 = (THaGemHit*)hit[layer_array[4]]->At(layer5);
		      //cout<<"layer 5"<<endl;
		      hit5->Set_tmpphi(hit4->Get_phi());
		      //mom_min_save[3] = mom_min;
		      //mom_max_save[3] = mom_max;
		      theta_min_save[3] = theta_min;
		      theta_max_save[3] = theta_max;
		      dr = hit4->Get_r() - hit5->Get_r();
		      if(dr>deltar[3][0] && dr<deltar[3][1] && ((hit5->Get_tmpphi() >philimit[3][0]&& hit5->Get_tmpphi() <philimit[3][1] && charge==-1))
			 && Predict_r(hit5->Get_r(), layer_array[4], hit4->Get_r(), layer_array[3], theta_min_save[3], theta_max_save[3])
			 && Range_in_theta(hit5->Get_r(),layer_array[4],hit4->Get_r(),layer_array[3],&theta_min,&theta_max,angleflag)
			 ){
			newtrack->AddHit(hit5);
			newtrack->AddHit(hit4);
			newtrack->AddHit(hit3);
			newtrack->AddHit(hit2);
			newtrack->AddHit(hit1);
			newtrack->Set_Charge(charge);
			newtrack->Set_Angleflag(angleflag);
			//newtrack->Set_Mommin(mom_min);
			//newtrack->Set_Mommax(mom_max);
			newtrack->Set_Thetamin(theta_min);
			newtrack->Set_Thetamax(theta_max);
			newtrack = new ((*fTracks)[fntrack++]) THaGemTrack();
			newtrack->Clear();
		      }else{
			//newtrack->Clear();
			//mom_min = mom_min_save[3];
			//mom_max = mom_max_save[3];
			theta_min = theta_min_save[3];
			theta_max = theta_max_save[3];
		      }
		    }
		  }else{
		    if (nlayer==4){
		      newtrack->AddHit(hit4);
		      newtrack->AddHit(hit3);
		      newtrack->AddHit(hit2);
		      newtrack->AddHit(hit1);
		      newtrack->Set_Charge(charge);
		      newtrack->Set_Angleflag(angleflag);
		      //newtrack->Set_Mommin(mom_min);
		      //newtrack->Set_Mommax(mom_max);
		      newtrack->Set_Thetamin(theta_min);
		      newtrack->Set_Thetamax(theta_max);
		      newtrack = new ((*fTracks)[fntrack++]) THaGemTrack();
		      newtrack->Clear();
		    }
		  }
		}else{
		  //mom_min = mom_min_save[2];
		  //mom_max = mom_max_save[2];
		  theta_min = theta_min_save[2];
		  theta_max = theta_max_save[2];
		}
	      }
	    }else{
	      if (nlayer==3){
		newtrack->AddHit(hit3);
		newtrack->AddHit(hit2);
		newtrack->AddHit(hit1);
		//newtrack->Set_Mommin(mom_min);
		//newtrack->Set_Mommax(mom_max);
		newtrack->Set_Thetamin(theta_min);
		newtrack->Set_Thetamax(theta_max);
		newtrack->Set_Charge(charge);
		newtrack->Set_Angleflag(angleflag);
		newtrack = new ((*fTracks)[fntrack++]) THaGemTrack();
		newtrack->Clear();
	      }
	    }
	  }else{
	    //mom_min = mom_min_save[1];
	    //mom_max = mom_max_save[1];
	    theta_min = theta_min_save[1];
	    theta_max = theta_max_save[1];
	  }
	}
      }else{
	//mom_min = mom_min_save[0];
	//mom_max = mom_max_save[0];
	theta_min = theta_min_save[0];
	theta_max = theta_max_save[0];
      }
    }
    newtrack->Clear();
    fTracks->Remove(newtrack);
    fntrack--;
    }
}
//(if delta phi is given, then this function can give a range for the momentum
//of the track. All the parameters in this function can be obtained by using
//SIDIS MC events. Basically, by ploting the momentum at vertex vs delta phi, 
// and fit the distribution with hyperbola)
Int_t SOLGEM::Find_mom_range(Int_t layer1, Double_t phi0, Int_t layer2, Double_t phi1, Double_t* mom_min,Double_t* mom_max,Int_t angleflag){
  Double_t phi2 = phi1-phi0;
  if (phi2<0)
    {
      phi2 = phi2 + 2.*3.1415926;
    }
  if (layer1==0&&layer2==1&&angleflag==0){
    Double_t par[6]={0.0440898,-8.06093e-05,-0.0015,0.0015, 0.2, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==0&&layer2==2&&angleflag==0){
    Double_t par[6]={0.106043,-0.000438188,-0.0032,0.0025, 0.18, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==1&&layer2==2&&angleflag==0){
    Double_t par[6]={0.0623398,-0.000411282,-0.0015,0.0015, 0.2, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==1&&layer2==3&&angleflag==0){
    Double_t par[6]={0.170711,-0.000504328,-0.004,0.0025, 0.15, -0.15};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==2&&layer2==3&&angleflag==0){
    Double_t par[6]={0.108599,-0.000124535,-0.002,0.002, 0.15, -0.15};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==1&&layer2==2&&angleflag==1){
    Double_t par[6]={0.0584916,-0.000214691,-0.0025,0.0025, 0.15, -0.05};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==1&&layer2==3&&angleflag==1){
    Double_t par[6]={0.154429,0.000758276,-0.004,0.0035, 0.1, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==2&&layer2==3&&angleflag==1){
    Double_t par[6]={0.106729,-0.00077419,-0.0025,0.002, 0.15, -0.05};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==2&&layer2==4&&angleflag==1){
    Double_t par[6]={0.253405,0.000254186,-0.0045,0.0035, 0.1, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==3&&layer2==4&&angleflag==1){
    Double_t par[6]={0.154123,-0.000253987,-0.003,0.003, 0.1, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==3&&layer2==5&&angleflag==1){
    Double_t par[6]={0.336808,4.76587e-05,-0.005,0.004, 0.1, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }else if(layer1==4&&layer2==5&&angleflag==1){
    Double_t par[6]={0.183853,-0.000229635,-0.0025,0.002, 0.1, -0.1};
    Double_t tempmin,tempmax;
    tempmin = par[0]/(phi2-par[1]-par[2])-par[4];
    tempmax = par[0]/(phi2-par[1]-par[3])-par[5];
    if (tempmin>*mom_min) *mom_min = tempmin;
    if (tempmax<*mom_max) *mom_max = tempmax;
  }
  if (*mom_min<=*mom_max){
    return 1;
  }else{
    //cout<<layer1<<" "<<layer2<<" "<<phi2<<endl;
    //cout<<*mom_min<<" "<<*mom_max<<endl;
    return 0;
  }

}

Int_t SOLGEM::Range_in_theta(Double_t r1, Int_t layer1, Double_t r2, Int_t layer2,Double_t* theta_min,Double_t* theta_max, Int_t angleflag){
 
  Double_t tempmin,tempmax;
 if (layer1==0 && layer2==1&&angleflag==1){
    Double_t par[4]={9.20089e-5, 3.57085, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3]; 
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==0 && layer2==2&&angleflag==1){
    Double_t par[4]={2.97216e-5, 3.07678, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3]; 
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==1 && layer2==2&&angleflag==1){
    Double_t par[4]={0.00208527, 22.1342, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3]; 
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==1 && layer2==3&&angleflag==1){
    Double_t par[4]={-0.000379827, 0.830618, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3];
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==2 && layer2==3&&angleflag==1){
    Double_t par[4]={-0.000370071, 0.862829, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3];
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==2 && layer2==4&&angleflag==1){
    Double_t par[4]={-0.000376543, 0.800717, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3];
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
  }else if (layer1==3 && layer2==4&&angleflag==1){
    Double_t par[4]={-0.000244691, 11.108, 0.05, -0.05};
    tempmax = par[0]+par[1]*(r2-r1)+par[2];
    tempmin = par[0]+par[1]*(r2-r1)+par[3];
    if (tempmin>*theta_min) *theta_min = tempmin;
    if (tempmax<*theta_max) *theta_max = tempmax;
 }else if (layer1 == 3 && layer2 == 3 && angleflag == 1){
   Double_t par[4] = {-0.00335374, 0.340128, 0.06, -0.06};
   tempmax = par[0]+par[1]*(r1)+par[2];
   tempmin = par[0]+par[1]*(r1)+par[3];
   if (tempmin>*theta_min) *theta_min = tempmin;
   if (tempmax<*theta_max) *theta_max = tempmax;
 }else if (layer1 == 4 && layer2 == 4 && angleflag == 1){
   Double_t par[4] = {-0.0037668, 0.330351, 0.06, -0.06};
   tempmax = par[0]+par[1]*(r1)+par[2];
   tempmin = par[0]+par[1]*(r1)+par[3];
   if (tempmin>*theta_min) *theta_min = tempmin;
   if (tempmax<*theta_max) *theta_max = tempmax;

 }
  
  if (*theta_min<=*theta_max){
    return 1;
  }else{
    return 0;
  }
}

void SOLGEM::FitTrack(THaGemTrack* thistrack, Double_t par[], Int_t npar, Double_t* Chi2)
{
   assert (npar == 4 && "parameters should always be 4 for straight line track in 3D");
  Double_t sum_x[5] = {0};
  Double_t sum_y[5] = {0};
  Double_t temp_z[5], temp_xcoor[5], temp_excoor[5], temp_ycoor[5], temp_eycoor[5];
  for (Int_t i=0; i<thistrack->Get_nhit(); ++i)
    {
      //fill the matrix for the x coordinate
      temp_excoor[i] = thistrack->Get_hit_info(i,8);
      temp_z[i] = thistrack->Get_hit_info(i,2);
      temp_xcoor[i] = thistrack->Get_hit_info(i,0);
      sum_x[0] = sum_x[0] + 1./(temp_excoor[i]*temp_excoor[i]);
      sum_x[1] = sum_x[1] + temp_z[i]/(temp_excoor[i]*temp_excoor[i]);
      sum_x[2] = sum_x[2] + temp_z[i]*temp_z[i]/(temp_excoor[i]*temp_excoor[i]);
      sum_x[3] = sum_x[3] + temp_xcoor[i]/(temp_excoor[i]*temp_excoor[i]);
      sum_x[4] = sum_x[4] + temp_xcoor[i]*temp_z[i]/(temp_excoor[i]*temp_excoor[i]);
      //do the same for the y coordinate
      temp_eycoor[i] = thistrack->Get_hit_info(i,9);
      temp_ycoor[i] = thistrack->Get_hit_info(i,1);
      sum_y[0] = sum_y[0] + 1./(temp_eycoor[i]*temp_eycoor[i]);
      sum_y[1] = sum_y[1] + temp_z[i]/(temp_eycoor[i]*temp_eycoor[i]);
      sum_y[2] = sum_y[2] + temp_z[i]*temp_z[i]/(temp_eycoor[i]*temp_eycoor[i]);
      sum_y[3] = sum_y[3] + temp_ycoor[i]/(temp_eycoor[i]*temp_eycoor[i]);
      sum_y[4] = sum_y[4] + temp_ycoor[i]*temp_z[i]/(temp_eycoor[i]*temp_eycoor[i]);
    }
  Double_t coef[2];
  coef[0] =  1./(sum_x[0]*sum_x[2] - sum_x[1]*sum_x[1]);
  coef[1] =  1./(sum_y[0]*sum_y[2] - sum_y[1]*sum_y[1]);
  par[0] = coef[0]*(sum_x[2]*sum_x[3] - sum_x[1]*sum_x[4]); //fit parameter a for x 
  par[1] = coef[0]*(sum_x[0]*sum_x[4] - sum_x[1]*sum_x[3]); //fit parameter b for x
  par[2] = coef[1]*(sum_y[2]*sum_y[3] - sum_y[1]*sum_y[4]); //fit parameter a for y 
  par[3] = coef[1]*(sum_y[0]*sum_y[4] - sum_y[1]*sum_y[3]); //fit parameter b for y


  *Chi2 = 0;
  for (Int_t i=0; i<thistrack->Get_nhit(); ++i)
    {
      *Chi2 = *Chi2 + pow((temp_xcoor[i] - (par[0] + par[1]*temp_z[i]))/temp_excoor[i] ,2);
      *Chi2 = *Chi2 + pow((temp_ycoor[i] - (par[2] + par[3]*temp_z[i]))/temp_eycoor[i] ,2);
    }
}


void SOLGEM::Vertex_Reconstruction(Double_t par[], Int_t npar, Double_t* vertexz, Double_t* vertexr)
{
   assert (npar == 4 && "parameters should always be 4 for straight line track in 3D");
   *vertexz = (par[0]*par[1] + par[2]*par[3])/( - (par[1]*par[1] + par[3]*par[3]));
   *vertexr = sqrt(pow((par[0] + par[1]*(*vertexz)),2) + pow((par[2] + par[3]*(*vertexz)),2));
   *vertexz = *vertexz + 1.572;
}

Double_t SOLGEM::Polar_Angle_Reconstruction(Double_t par[], Int_t npar)
{
  assert (npar == 4 && "parameters should always be 4 for straight line track in 3D");
  return acos(1./sqrt(1+par[1]*par[1]+par[3]*par[3]))*180./3.1415926;
}

Int_t SOLGEM::Check_Q_Asym(THaGemTrack* thistrack)
{
  Int_t q_count = 0;
  Double_t qu, qv;
  for (Int_t i=0; i<thistrack->Get_nhit(); ++i)
    {
      qu = thistrack->Get_hit_info(i,6);
      qv = thistrack->Get_hit_info(i,7);
      if (fabs((qu-qv)/(qu+qv))<0.2)
	{
	  ++q_count;
	}
    }
  return q_count;
}



Int_t SOLGEM::Predict_r(Double_t r1, Int_t layer1, Double_t r2, Int_t layer2, Double_t theta_min, Double_t theta_max)
{
  Double_t r_max, r_min;
  Double_t Z_POS[6] = {0, 0.28, 0.325, 1.485, 1.575, 1.62809};
  if (layer1==0 && layer2==1){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) + 0.005;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) - 0.005;
  }else if (layer1==0 && layer2==2){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]);
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]); 
  }else if (layer1==1 && layer2==2){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) + 0.005;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) - 0.005; 
  }else if (layer1==1 && layer2==3){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) -0.015;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) +0.015; 
  }else if (layer1==2 && layer2==3){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) -0.01;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) +0.01; 
  }else if (layer1==2 && layer2==4){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) +0.01;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) -0.01; 
  }else if (layer1==3 && layer2==4){
    r_max = r2-theta_min*fabs(Z_POS[layer2] - Z_POS[layer1]) +0.01;
    r_min = r2-theta_max*fabs(Z_POS[layer2] - Z_POS[layer1]) -0.01;
  }else{
    r_max = 0;
    r_min = 0;
  }
    if (r1<r_max && r1>r_min)
      {
	return 1;
      }
    else
      {
	//cout<<"fail at: "<<layer1<<" "<<layer2<<endl;
	return 0;
      }
}

