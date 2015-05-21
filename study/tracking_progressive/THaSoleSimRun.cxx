#include "THaSoleSimRun.h"

#include "TFile.h"
#include "TTree.h"
#include "TError.h"
#include "TRandom.h"
#include <cstdio>
#include <evio.h>
#include "math.h"

using namespace std;

THaSoleSimRun::THaSoleSimRun(const char* filename, const char* description) :
  THaRunBase(description),rootFileName(filename), rootFile(0),tree(0),event(0),nentries(0), entry(0)
{
  if (rootFileName.IsNull())
    rootFileName = "sole_tracks.root";
}

THaSoleSimRun::THaSoleSimRun(const THaSoleSimRun &run)
  : THaRunBase(run), nentries(0),entry(0)
{
  rootFileName = run.rootFileName;
  rootFile = NULL;
  tree = NULL;
  event = NULL;
}



THaSoleSimRun& THaSoleSimRun::operator=(const THaRunBase& rhs)
{
  if (this != &rhs){
    THaRunBase::operator=(rhs);
    if (rhs.InheritsFrom("THaSoleSimRun"))
      rootFileName = static_cast<const THaSoleSimRun&>(rhs).rootFileName;
    rootFile = NULL;
    tree = NULL;
    event = NULL;
  }
  return *this;
}

Int_t THaSoleSimRun::Init()
{
  fDate.Set(2003,4,15,12,0,0);
  fAssumeDate = kTRUE;
  fDataSet |= kDate;
  return THaRunBase::Init();
}

Int_t THaSoleSimRun::Open()
{
  event = new THaSoleSimEvent();
  
  curr = gDirectory;
  rootFile = new TFile(rootFileName, "READ", "SoleDC Tracks");
  

  if (!rootFile || rootFile->IsZombie()){
    if (rootFile->IsOpen()) Close();
    return -1;
  }
  
  tree = static_cast<TTree*>(rootFile->Get("T"));
  if (!tree) {
    Error( "THaVDCSimRun:Open", 
	   "Tree 'tree' does not exist in the input file. Have a nice day." );
    return -2;
  }
  
  nentries = static_cast<Int_t>(tree->GetEntries());
  entry = 0;

  tree->SetBranchAddress("Ndata.c1",&nhit[0]);
  tree->SetBranchAddress("Ndata.c2",&nhit[1]);
  tree->SetBranchAddress("Ndata.c3",&nhit[2]);
  tree->SetBranchAddress("Ndata.c4",&nhit[3]);
  tree->SetBranchAddress("Ndata.c5",&nhit[4]);
  tree->SetBranchAddress("Ndata.c6",&nhit[5]);
  
  tree->SetBranchAddress("c1.flag",&flag[0][0]);
  tree->SetBranchAddress("c2.flag",&flag[1][0]);
  tree->SetBranchAddress("c3.flag",&flag[2][0]);
  tree->SetBranchAddress("c4.flag",&flag[3][0]);
  tree->SetBranchAddress("c5.flag",&flag[4][0]);
  tree->SetBranchAddress("c6.flag",&flag[5][0]);
  
  tree->SetBranchAddress("c1.x",&x[0][0]);
  tree->SetBranchAddress("c2.x",&x[1][0]);
  tree->SetBranchAddress("c3.x",&x[2][0]);
  tree->SetBranchAddress("c4.x",&x[3][0]);
  tree->SetBranchAddress("c5.x",&x[4][0]);
  tree->SetBranchAddress("c6.x",&x[5][0]);
  
  tree->SetBranchAddress("c1.y",&y[0][0]);
  tree->SetBranchAddress("c2.y",&y[1][0]);
  tree->SetBranchAddress("c3.y",&y[2][0]);
  tree->SetBranchAddress("c4.y",&y[3][0]);
  tree->SetBranchAddress("c5.y",&y[4][0]);
  tree->SetBranchAddress("c6.y",&y[5][0]);
  
  tree->SetBranchAddress("c1.z",&z[0][0]);
  tree->SetBranchAddress("c2.z",&z[1][0]);
  tree->SetBranchAddress("c3.z",&z[2][0]);
  tree->SetBranchAddress("c4.z",&z[3][0]);
  tree->SetBranchAddress("c5.z",&z[4][0]);
  tree->SetBranchAddress("c6.z",&z[5][0]);
  
  tree->SetBranchAddress("chamberx",&chamber_pos[0][0]);
  tree->SetBranchAddress("chambery",&chamber_pos[1][0]);
  tree->SetBranchAddress("chamberz",&chamber_pos[2][0]);
  tree->SetBranchAddress("chamberex",&chamber_res[0][0]);
  tree->SetBranchAddress("chamberey",&chamber_res[1][0]);
  tree->SetBranchAddress("chamberqu",&chamber_qu[0]);
  tree->SetBranchAddress("chamberqv",&chamber_qv[0]);
  
  tree->SetBranchAddress("Nsignal", &Nsignal);
  tree->SetBranchAddress("mom",&mom);
  tree->SetBranchAddress("theta",&theta);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("vertex",&vertex);

  tree->SetBranchAddress("c1.qu", &qu[0][0]);
  tree->SetBranchAddress("c2.qu", &qu[1][0]);
  tree->SetBranchAddress("c3.qu", &qu[2][0]);
  tree->SetBranchAddress("c4.qu", &qu[3][0]);
  tree->SetBranchAddress("c5.qu", &qu[4][0]);
  tree->SetBranchAddress("c6.qu", &qu[5][0]);

  tree->SetBranchAddress("c1.qv", &qv[0][0]);
  tree->SetBranchAddress("c2.qv", &qv[1][0]);
  tree->SetBranchAddress("c3.qv", &qv[2][0]);
  tree->SetBranchAddress("c4.qv", &qv[3][0]);
  tree->SetBranchAddress("c5.qv", &qv[4][0]);
  tree->SetBranchAddress("c6.qv", &qv[5][0]);

  tree->SetBranchAddress("c1.ex", &ex[0][0]);
  tree->SetBranchAddress("c2.ex", &ex[1][0]);
  tree->SetBranchAddress("c3.ex", &ex[2][0]);
  tree->SetBranchAddress("c4.ex", &ex[3][0]);
  tree->SetBranchAddress("c5.ex", &ex[4][0]);
  tree->SetBranchAddress("c6.ex", &ex[5][0]);

  tree->SetBranchAddress("c1.ey", &ey[0][0]);
  tree->SetBranchAddress("c2.ey", &ey[1][0]);
  tree->SetBranchAddress("c3.ey", &ey[2][0]);
  tree->SetBranchAddress("c4.ey", &ey[3][0]);
  tree->SetBranchAddress("c5.ey", &ey[4][0]);
  tree->SetBranchAddress("c6.ey", &ey[5][0]);

  tree->SetBranchAddress("c1.TrueHit", &TrueHit[0][0]);
  tree->SetBranchAddress("c2.TrueHit", &TrueHit[1][0]);
  tree->SetBranchAddress("c3.TrueHit", &TrueHit[2][0]);
  tree->SetBranchAddress("c4.TrueHit", &TrueHit[3][0]);
  tree->SetBranchAddress("c5.TrueHit", &TrueHit[4][0]);
  tree->SetBranchAddress("c6.TrueHit", &TrueHit[5][0]);


  
  curr->cd();
  fOpened = kTRUE;
  return 0;
}

Int_t THaSoleSimRun::ReadEvent() {
  Int_t ret;
  if (!IsOpen()) {
    ret = Open();
    if (ret) return ret;
  }
  
  
  ret = tree->GetEntry(entry++);
  event->event_num = entry;
  
  event->Clear();
  //make an upate for the THaSoleSimTrack
  THaSoleSimTrack *qtrack = new THaSoleSimTrack();
  qtrack->mom = mom;
  qtrack->theta = theta;
  qtrack->phi = phi;
  qtrack->vertex = vertex;
  for (Int_t i=0;i!=6;i++){
    qtrack->x[i] = chamber_pos[0][i];
    qtrack->y[i] = chamber_pos[1][i];
    qtrack->z[i] = chamber_pos[2][i];
    qtrack->ex[i] = chamber_res[0][i];
    qtrack->ey[i] = chamber_res[1][i];
    qtrack->qu[i] = chamber_qu[i];
    qtrack->qv[i] = chamber_qv[i];
  }
      if (qtrack->z[0]!=0&&qtrack->z[1]!=0&&qtrack->z[2]!=0&&qtrack->z[3]!=0&&qtrack->z[4]!=0&&qtrack->z[5]!=0){
	qtrack->flag=1;
      }else{
	qtrack->flag=0;
      }
      event->tracks.Add(qtrack);
    
  Float_t qregion[6]={36,28,27,24,22};

  //----------add EC hits here-----------//
  for (Int_t i=0; i<nhit[5]; i++)
    {
      if (fabs(flag[5][i]-1)<1e-3)
	{
	  THaSoleSimHit *qechit = new THaSoleSimHit();
	  qechit->x = x[5][i];
	  qechit->y = y[5][i];
	  qechit->z = z[5][i];
	  qechit->ex = ex[5][i];
	  qechit->ey = ey[5][i];
	  qechit->qu = qu[5][i];
	  qechit->qv = qv[5][i];
	  qechit->r = sqrt(x[5][i]*x[5][i]+y[5][i]*y[5][i]);
	  qechit->TrueHit = TrueHit[5][i];
	//cout<<qechit->x<<" "<<qechit->z<<" "<<nhit[6]<<endl;
	  /*if (x[5][i]==0){
	    if (y[5][i]>0.){
	      qechit->phi = 3.1415926/2.;
	    }else{
	      qechit->phi = 3.1415926/2.*3.;
	    }
	  }else if (x[5][i]>0.){
	    if (y[5][i]>0.){
	      qechit->phi = atan(y[5][i]/x[5][i]);
	    }else{
	      qechit->phi = 2.*3.1415926 + atan(y[5][i]/x[5][i]);
	    }
	  }else{
	    if (y[5][i]>0.){
	      qechit->phi = 3.1415926 + atan(y[5][i]/x[5][i]);
	    }else{
	      qechit->phi = 3.1415926 + atan(y[5][i]/x[5][i]);
	    }
	  }*/
	qechit->phi = atan2(y[5][i], x[5][i]);
	  //modify TSolSimEvent
	  (event->EChits).Add(qechit);
	}
    }

  //------------------------------------//
  for (Int_t j=0;j!=5;j++){
    //cout<<nhit[j]<<endl;
    for (Int_t i=0;i!=nhit[j];i++){
      if (fabs(flag[j][i]-1)<1e-3){
	THaSoleSimHit *qgemhit = new THaSoleSimHit();
	qgemhit->x = x[j][i];
	qgemhit->y = y[j][i];
	qgemhit->z = z[j][i];
	qgemhit->ex = ex[j][i];
	qgemhit->ey = ey[j][i];
	qgemhit->r = sqrt(x[j][i]*x[j][i]+y[j][i]*y[j][i]);
	qgemhit->qu = qu[j][i];
	qgemhit->qv = qv[j][i];
	qgemhit->TrueHit = TrueHit[j][i];
	/*if (x[j][i]==0){
	  if (y[j][i]>0.){
	    qgemhit->phi = 3.1415926/2.;
	  }else{
	    qgemhit->phi = 3.1415926/2.*3.;
	  }
	}else if (x[j][i]>0.){
	  if (y[j][i]>0.){
	    qgemhit->phi = atan(y[j][i]/x[j][i]);
	  }else{
	    qgemhit->phi = 2.*3.1415926 + atan(y[j][i]/x[j][i]);
	  }
	}else{
	  if (y[j][i]>0.){
	    qgemhit->phi = 3.1415926 + atan(y[j][i]/x[j][i]);
	  }else{
	    qgemhit->phi = 3.1415926 + atan(y[j][i]/x[j][i]);
	  }
	}*/
	qgemhit->phi = atan2(y[j][i], x[j][i]);
	qgemhit->calregion(qregion[j]);
	(event->gemrealhits[j]).Add(qgemhit);
      }
    }
    //

    /* event->gemhits[j].Sort();
    TIter nextHit(&event->gemhits[j]);
    Int_t pre_region = -1;
    Int_t count = 0,new_count;

    Float_t suppression = 4.;
    Float_t rmin[6] = {50,28,31.5,39,50,64};
    Float_t rmax[6] = {80,93,107.5,135,98,122};
    
    Float_t tempx[100],tempy[100],tempz[100];
    Float_t new_tempx[100],new_tempy[100],new_tempz[100];

    while( THaSoleSimHit *hit = 
	   static_cast<THaSoleSimHit*>( nextHit() )) {
      if (hit->region != pre_region ){
	calculate_hit(pre_region,qregion[j],rmin[j],rmax[j],suppression,count,tempx,tempy,tempz,&new_count,new_tempx,new_tempy,new_tempz);
	for (Int_t i=0;i!=new_count;i++){
	  THaSoleSimHit *qgemhit1 = new THaSoleSimHit();
	  qgemhit1->x = new_tempx[i];
	  qgemhit1->y = new_tempy[i];
	  qgemhit1->z = new_tempz[i];
	  qgemhit1->r = sqrt(new_tempx[i]*new_tempx[i] + new_tempy[i]*new_tempy[i]);
	  if (new_tempx[i] == 0){
	    if (new_tempy[i]>0.){
	      qgemhit1->phi = 3.1415926/2.;
	    }else{
	      qgemhit1->phi = 3.1415926/2.*3.;
	    }
	  }else if (new_tempx[i]>0.){
	    if (new_tempy[i]>0.){
	      qgemhit1->phi = atan(new_tempy[i]/new_tempx[i]);
	    }else{
	      qgemhit1->phi = 2.*3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	    }
	  }else{
	    if (new_tempy[i]>0.){
	      qgemhit1->phi = 3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	    }else{
	      qgemhit1->phi = 3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	    }
	  }
	  qgemhit1->calregion(qregion[j]);
	  (event->gemrealhits[j]).Add(qgemhit1);
	}
	
	// clear current list
	count = 0;
	tempx[count] = hit->x;
	tempy[count] = hit->y;
	tempz[count] = hit->z;
	count ++;
      }else{
	tempx[count] = hit->x;
	tempy[count] = hit->y;
	tempz[count] = hit->z;
	count ++;
      }
      pre_region = hit->region;
    }
    
    calculate_hit(pre_region,qregion[j],rmin[j],rmax[j],suppression,count,tempx,tempy,tempz,&new_count,new_tempx,new_tempy,new_tempz);
    

    for (Int_t i=0;i!=new_count;i++){
      THaSoleSimHit *qgemhit1 = new THaSoleSimHit();
      qgemhit1->x = new_tempx[i];
      qgemhit1->y = new_tempy[i];
      qgemhit1->z = new_tempz[i];
      qgemhit1->r = sqrt(new_tempx[i]*new_tempx[i] + new_tempy[i]*new_tempy[i]);
      if (new_tempx[i] == 0){
	if (new_tempy[i]>0.){
	  qgemhit1->phi = 3.1415926/2.;
	}else{
	  qgemhit1->phi = 3.1415926/2.*3.;
	}
      }else if (new_tempx[i]>0.){
	if (new_tempy[i]>0.){
	  qgemhit1->phi = atan(new_tempy[i]/new_tempx[i]);
	}else{
	  qgemhit1->phi = 2.*3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	}
      }else{
	if (new_tempy[i]>0.){
	  qgemhit1->phi = 3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	}else{
	  qgemhit1->phi = 3.1415926 + atan(new_tempy[i]/new_tempx[i]);
	}
      }
      qgemhit1->calregion(qregion[j]);
      (event->gemrealhits[j]).Add(qgemhit1);
      }*/
    
  }
  
  if( ret > 0 )
    return S_SUCCESS;
  else if ( ret == 0 )
    return EOF;
  return -128;  // CODA_ERR
}

Int_t THaSoleSimRun::Close() {
  if (rootFile) {
    rootFile->Close();
    delete rootFile;
    rootFile = 0;
  }
  fOpened = kFALSE;
  return 0;
}

const Int_t *THaSoleSimRun::GetEvBuffer() const {
  if (!IsOpen()) return NULL;
  return reinterpret_cast<Int_t*>(event);
}

THaSoleSimRun::~THaSoleSimRun() {
  delete event;
  if (IsOpen())
    Close();
}

void THaSoleSimRun::calculate_hit(Int_t region,Int_t totalregion, Float_t rmin, Float_t rmax, Float_t suppression, Int_t count, Float_t* x, Float_t* y, Float_t* z, Int_t* new_count, Float_t*new_x, Float_t* new_y, Float_t* new_z){
  //cout<<totalregion<<endl;
  Float_t kmin = tan(region*3.1415926*2./totalregion     +  0.0001);
  Float_t kmax = tan((region+1)*3.1416926*2./totalregion -  0.0001);

  (*new_count) = 0;
  for (Int_t i=0;i!=count;i++){
    // add current x;
    *(new_x+ (*new_count) ) = *(x+i);
    *(new_y+ (*new_count) ) = *(y+i);
    *(new_z+ (*new_count) ) = *(z+i);
    (*new_count) ++;
    for (Int_t j = 0; j < i; j++){
      Float_t x1,y1,z1,r1,phi1,x2,y2,z2,r2,phi2,temp;
      x1 = (kmax* *(x+i) - kmin* *(x+j)+ *(y+j) - *(y+i))/(kmax-kmin);
      y1 = kmax*(x1- *(x+i)) + *(y+i);
      r1 = sqrt(x1*x1+y1*y1);
      
      if (x1 == 0){
	if (y1>0.){
	  phi1 = 3.1415926/2.;
	}else{
	  phi1 = 3.1415926/2.*3.;
	}
      }else if (x1>0.){
	if (y1>0.){
	  phi1 = atan(y1/x1);
	}else{
	  phi1 = 2.*3.1415926 + atan(y1/x1);
	}
      }else{
	if (y1>0.){
	  phi1 = 3.1415926 + atan(y1/x1);
	}else{
	  phi1 = 3.1415926 + atan(y1/x1);
	}
      }

      x2 = (kmin* *(x+i) - kmax* *(x+j)+ *(y+j) - *(y+i))/(kmin-kmax);
      y2 = kmin*(x1- *(x+i)) + *(y+i);
      r2 = sqrt(x2*x2+y2*y2);
      if (x2 == 0){
	if (y2>0.){
	  phi2 = 3.1415926/2.;
	}else{
	  phi2 = 3.1415926/2.*3.;
	}
      }else if (x2>0.){
	if (y2>0.){
	  phi2 = atan(y1/x1);
	}else{
	  phi2 = 2.*3.1415926 + atan(y2/x2);
	}
      }else{
	if (y2>0.){
	  phi2 = 3.1415926 + atan(y2/x2);
	}else{
	  phi2 = 3.1415926 + atan(y2/x2);
	}
      }
      z1 = *(z+i);
      z2 = *(z+i);

      if ( r1 >= rmin && r1 < rmax && phi1 >= region*3.1415926*2./totalregion 
	   && phi1 <= (region+1)*3.1415926*2./totalregion ){
	     temp = gRandom->Uniform(0.,1.);
	     if (temp < 1./suppression){
	      //  if (z1 == 231)
// 		 cout << r1 << "\t" << z1 << "\t" << phi1 << endl;
	       *(new_x+(*new_count)) = x1;
	       *(new_y+(*new_count)) = y1;
	       *(new_z+(*new_count)) = z1;
	       (*new_count) ++;
	     }
	   }
      
	   if(r2 >= rmin && r2 < rmax && phi2 >= region*3.1415926*2/totalregion 
	   && phi2 <= (region+1)*3.1415926*2/totalregion ){
		temp = gRandom->Uniform(0.,1.);
		if (temp < 1./suppression){
		  // if (z2==231)
// 		    cout << r2 << "\t" << z2 << "\t" << phi2 << endl;
		  *(new_x+(*new_count)) = x2;
		  *(new_y+(*new_count)) = y2;
		  *(new_z+(*new_count)) = z2;
		  (*new_count) ++;
		}
	      }
      
    }
  }
  
}


//-----------------------------------------------------------------------------
ClassImp(THaSoleSimRun)
