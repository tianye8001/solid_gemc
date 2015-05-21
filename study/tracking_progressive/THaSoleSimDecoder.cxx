#include "THaSoleSimDecoder.h"
#include "THaSoleGEMSim.h"
#include "THaCrateMap.h"
#include "THaBenchmark.h"
#include "VarDef.h"

using namespace std;

#define DEBUG 0
#define MC_PREFIX "MC."

THaSoleSimDecoder::THaSoleSimDecoder()
{
  DefineVariables();
}

THaSoleSimDecoder::~THaSoleSimDecoder() {
  DefineVariables( THaAnalysisObject::kDelete );
}

Int_t THaSoleSimDecoder::DefineVariables( THaAnalysisObject::EMode mode )
{
  const char* const here = "THaSoleSimDecoder::DefineVariables";
  if( mode == THaAnalysisObject::kDefine && fIsSetup ) 
    return THaAnalysisObject::kOK;
  fIsSetup = ( mode == THaAnalysisObject::kDefine );

  RVarDef vars[] = {
    {"mctr.n", "Number of tracks", "GetNTracks()"},
    {"mctr.flag","flag","fTracks.THaSoleSimTrack.Getflag()"},
    {"mctr.mom","momentum","fTracks.THaSoleSimTrack.mom"},
    {"mctr.theta","theta","fTracks.THaSoleSimTrack.theta"},
    {"mctr.phi","phi","fTracks.THaSoleSimTrack.phi"},
    {"mctr.vertex","vertex","fTracks.THaSoleSimTrack.vertex"},
    {"mctr.c1.x","x","fTracks.THaSoleSimTrack.Get1X()"},
    {"mctr.c1.y","y","fTracks.THaSoleSimTrack.Get1Y()"},
    {"mctr.c1.z","z","fTracks.THaSoleSimTrack.Get1Z()"},
    {"mctr.c1.ex","ex","fTracks.THaSoleSimTrack.Get1EX()"},
    {"mctr.c1.ey","ey","fTracks.THaSoleSimTrack.Get1EY()"},
    {"mctr.c1.qu","qu","fTracks.THaSoleSimTrack.Get1QU()"},
    {"mctr.c1.qv","qv","fTracks.THaSoleSimTrack.Get1QV()"},
    {"mctr.c2.x","x","fTracks.THaSoleSimTrack.Get2X()"},
    {"mctr.c2.y","y","fTracks.THaSoleSimTrack.Get2Y()"},
    {"mctr.c2.z","z","fTracks.THaSoleSimTrack.Get2Z()"},
    {"mctr.c2.ex","ex","fTracks.THaSoleSimTrack.Get2EX()"},
    {"mctr.c2.ey","ey","fTracks.THaSoleSimTrack.Get2EY()"},
    {"mctr.c2.qu","qu","fTracks.THaSoleSimTrack.Get2QU()"},
    {"mctr.c2.qv","qv","fTracks.THaSoleSimTrack.Get2QV()"},
    {"mctr.c3.x","x","fTracks.THaSoleSimTrack.Get3X()"},
    {"mctr.c3.y","y","fTracks.THaSoleSimTrack.Get3Y()"},
    {"mctr.c3.z","z","fTracks.THaSoleSimTrack.Get3Z()"},
    {"mctr.c3.ex","ex","fTracks.THaSoleSimTrack.Get3EX()"},
    {"mctr.c3.ey","ey","fTracks.THaSoleSimTrack.Get3EY()"},
    {"mctr.c3.qu","qu","fTracks.THaSoleSimTrack.Get3QU()"},
    {"mctr.c3.qv","qv","fTracks.THaSoleSimTrack.Get3QV()"},
    {"mctr.c4.x","x","fTracks.THaSoleSimTrack.Get4X()"},
    {"mctr.c4.y","y","fTracks.THaSoleSimTrack.Get4Y()"},
    {"mctr.c4.z","z","fTracks.THaSoleSimTrack.Get4Z()"},
    {"mctr.c4.ex","ex","fTracks.THaSoleSimTrack.Get4EX()"},
    {"mctr.c4.ey","ey","fTracks.THaSoleSimTrack.Get4EY()"},
    {"mctr.c4.qu","qu","fTracks.THaSoleSimTrack.Get4QU()"},
    {"mctr.c4.qv","qv","fTracks.THaSoleSimTrack.Get4QV()"},
    {"mctr.c5.x","x","fTracks.THaSoleSimTrack.Get5X()"},
    {"mctr.c5.y","y","fTracks.THaSoleSimTrack.Get5Y()"},
    {"mctr.c5.z","z","fTracks.THaSoleSimTrack.Get5Z()"},
    {"mctr.c5.ex","ex","fTracks.THaSoleSimTrack.Get5EX()"},
    {"mctr.c5.ey","ey","fTracks.THaSoleSimTrack.Get5EY()"},
    {"mctr.c5.qu","qu","fTracks.THaSoleSimTrack.Get5QU()"},
    {"mctr.c5.qv","qv","fTracks.THaSoleSimTrack.Get5QV()"},
    {0}
  };

  Int_t ret = 
    THaAnalysisObject::DefineVarsFromList( vars, 
					   THaAnalysisObject::kRVarDef, 
					   mode, "", this, MC_PREFIX, here );

  return ret;
}

void THaSoleSimDecoder::Clear( Option_t* opt )
{
  // Clear track and plane data

  THaEvData::Clear();

  // Never delete the tracks, only clear the list. The tracks are deleted
  // in THaVDCSimRun::ReadEvent() by the call to event->Clear().
  fTracks.Clear("nodelete");
}

Int_t THaSoleSimDecoder::LoadEvent(const int* evbuffer, THaCrateMap* map) {
  Clear();

  fMap = map;
  buffer = evbuffer;

  THaSoleSimEvent* simEvent = (THaSoleSimEvent*)(evbuffer);

  //  if(DEBUG) PrintOut();
  if (first_decode) {
    // init_cmap();     
    //if (init_slotdata(map) == HED_ERR) return HED_ERR;
    first_decode = false;
  }
  if( fDoBench ) fBench->Begin("clearEvent");
  Clear();

  //  for( int i=0; i<fNSlotClear; i++ )
  //  crateslot[fSlotClear[i]]->clearEvent();
  if( fDoBench ) fBench->Stop("clearEvent");
  
  evscaler = 0;
  event_length = 0;

  event_type = 1;
  event_num = simEvent->event_num;
  recent_event = event_num;
  
  if( fDoBench ) fBench->Begin("physics_decode");

  // for (Int_t i=0;i!=6;i++){
//     TIter nextHit(&simEvent->gemrealhits[i]);
//     while( THaSoleSimHit *hit = 
// 	   static_cast<THaSoleSimHit*>( nextHit() )) {
      
//     }
//   }
  
  TIter nextTrack(&simEvent->tracks);
  while ( THaSoleSimTrack* track = (THaSoleSimTrack*)nextTrack() ) {
    fTracks.Add( track );
  }
  

  if( fDoBench ) fBench->Stop("physics_decode");
  return HED_OK;
  
}

ClassImp(THaSoleSimDecoder)
