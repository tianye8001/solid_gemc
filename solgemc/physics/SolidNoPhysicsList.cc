// %%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%
#include "SolidNoPhysicsList.h"
#include "SolidNoPhysics.h"

SolidNoPhysicsList::SolidNoPhysicsList(gemc_opts Opt):  G4VModularPhysicsList()
{
	gemcOpt = Opt;
	string hd_msg  = gemcOpt.args["LOG_MSG"].args + " Solid Physics List: <<< ";
	double use_opt = gemcOpt.args["OPT_PH"].arg;
//	double   VERB  = gemcOpt.args["PHY_VERBOSITY"].arg ;
  
	// EM Physics
	RegisterPhysics( new SolidNoPhysics());
 
}

SolidNoPhysicsList::~SolidNoPhysicsList(){}

void SolidNoPhysicsList::SetCuts()
{
	double   VERB  = gemcOpt.args["PHY_VERBOSITY"].arg ;
  SetCutsWithDefault();  
  
  if (VERB>2) DumpCutValuesTable();
}




