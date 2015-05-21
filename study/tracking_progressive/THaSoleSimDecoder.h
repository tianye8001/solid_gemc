#ifndef THaSoleSimDecoder_
#define THaSoleSimDecoder_

#include "THaEvData.h"
#include "TClonesArray.h"
#include "THaAnalysisObject.h"
#include "TList.h"

class THaCrateMap;

class THaSoleSimDecoder : public THaEvData {
 public:
  THaSoleSimDecoder();
  virtual ~THaSoleSimDecoder();
  
  Int_t LoadEvent (const int* evbuffer, THaCrateMap* usermap);
  Int_t GetNTracks(){ return fTracks.GetLast()+1;}
  void Clear(Option_t* opt="");
  Int_t DefineVariables(THaAnalysisObject::EMode mode = 
			  THaAnalysisObject::kDefine);
 protected:
  TList   fTracks;    // Monte Carlo tracks
  
  bool fIsSetup;
  
  ClassDef(THaSoleSimDecoder,0)
};
    
#endif
