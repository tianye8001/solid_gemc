#ifndef SOLIDHP_HH
#define SOLIDHP_HH

#include "MPHBaseClass.h"
#include "HitProcess_MapRegister.h"

#include "trace_HitProcess.h"

/*  This function allows us to add in our own hit processors
 *  for SoLID
 */

void AddSoLIDHP( map<string, MPHB_Factory> &hpmap ){
    hpmap["TRACE"]  = &trace_HitProcess::createHitClass;
    return;
}

#endif//SOLIDHP_HH
