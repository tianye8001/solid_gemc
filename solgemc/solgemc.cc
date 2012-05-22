
// %%%%%%%%%%
// G4 headers
// %%%%%%%%%%
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"

#include "G4UIQt.hh"
#include "G4Qt.hh"

// %%%%%%%%%%
// Qt headers
// %%%%%%%%%%
#include <QApplication>
#include <QSplashScreen>

// %%%%%%%%%%%%%
// gemc headers
// %%%%%%%%%%%%%
#include "HitProcess_MapRegister.h"
#include "detector.h"
#include "gemc_MainGui.h"
#include "images/CLAS12_cad.h"
#include "MagneticField.h"
#include "MBankdefs.h"
#include "MDetectorConstruction.h"
#include "MEventAction.h"
#include "MOutputBaseClass.h"
#include "MPHBaseClass.h"
#include "MPhysicsList.h"
#include "MPrimaryGeneratorAction.h"
#include "MSteppingAction.h"
#include "Output_Register.h"
#include "usage.h"
#include "run_conditions.h"
#include "material_factory.h"
#include "parameter_factory.h"


/////////////////////////
/// <b> Main Program </b>
/////////////////////////
///  -# Sets the gemc_opts\n
///  -# Starts QT application if USE_QT=1
///  -# Starts the CLHEP random engine
///  -# Instantiates the Geant4 Run Manager
///  -# Builds detector map object from database
///  -# Builds Processes Routines Map
///  -# Builds Materials Map
///  -# Builds G4 Physical Volumes
///  -# Initialize Physics List
///  -# Initialize Generator
///  -# Initialize Event Action
///  -# Initialize G4Qt User Interface if USE_QT>0
///  -# Initialize Visualization Manager if USE_QT>0


// get_pid is useful only on the farm
// don't need it in Windows environment
// (but, why _getpid is not found?)
#ifdef _MSC_VER
#include <stdio.h>	
#include <process.h>
	//int get_pid(){return __get_pid();}
	int get_pid(){return 0;}
#endif

#include "addopts.h"
#include "solidhp.h"
#include "SolMaterial.hh"
#include "SolidNoPhysicsList.h"
#include "SolPrimaryGeneratorAction.h"

int main( int argc, char **argv )
{
	
	gemc_opts gemcOpt;
	gemcOpt.Set(argc, argv);
	string hd_msg    = gemcOpt.args["LOG_MSG"].args + " Init: >> " ;
	
	cout << endl << hd_msg  << " Geant4 MonteCarlo" << endl;
	double use_qt = gemcOpt.args["USE_QT"].arg;
	
	///< Initializing QT application
	QApplication gemc_gui( argc, argv, (bool) use_qt );
	QPixmap *splash_i = NULL;
	QSplashScreen *splash = NULL;
	

#ifdef Q_OS_MAC
//
// If you are on a Mac, add the gemc.app/Contents/plugins directory to the list of paths
// that are searched for dynamic plugins.
//
	QDir dir(QApplication::applicationDirPath());	
	dir.cdUp();
	dir.cd("PlugIns");
	QApplication::setLibraryPaths(QStringList(dir.absolutePath()));
	
	
//  To print the path that is searched for plugins, uncomment:
//
//	foreach (QString path, gemc_gui.libraryPaths())
//      qDebug() << "Path: " << path << endl;	
#endif

	
	///< Initializing Splash Screen
	if(use_qt)
	{
		splash_i = new QPixmap(CLAS12_cad);
		splash   = new QSplashScreen(*splash_i);
		splash->show();
		gemc_gui.processEvents();
	}
	
	string msg;
	
	///< Initializing the CLHEP Random engine
	msg = " Setting CLHEP Random Engine...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	// CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
	CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
	string RAND = gemcOpt.args["RANDOM"].args;
	G4int seed;
	
	if(RAND=="TIME")
	{
		msg = " Initializing CLHEP Random Engine from time, cpu clock and process id...";
		seed = time(NULL)-clock()-getpid() ;
	}
	else
	{
		seed = atoi(RAND.c_str());
		msg = " Initializing CLHEP Random Engine from user seed...";
	}
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	char seeds[100];
	sprintf(seeds, "%d", seed);
	msg = " Random Seed Initialized to: " ;
	msg.append(seeds);

	CLHEP::HepRandom::setTheSeed(seed);
	
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	
	///< Reading the gcard file
	if(gemcOpt.args["gcard"].args != "no")
	{
		msg = " Opening GCARD file " + gemcOpt.args["gcard"].args + "...";
		if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	}
	run_conditions RunConditions(gemcOpt);
	
	///< Construct the default G4 run manager
	msg = " Instantiating Run Manager...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	G4RunManager *runManager = new G4RunManager;
	
  ///< Detector Map
	msg = " Retrieving gemc Detector Map...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	map<string, detector> Hall_Map = read_detector(gemcOpt, RunConditions);
  
	///< Materials Map
	msg = " Material factory selected: " + gemcOpt.args["MATERIALSDB"].args;
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
  map<string, materialFactory> materialFactoriesMap = registerMaterialFactories();
  materials *materialSelectedFactory = getMaterialFactory(&materialFactoriesMap, gemcOpt.args["MATERIALSDB"].args);
	map<string, G4Material*> mats = materialSelectedFactory->initMaterials(RunConditions, gemcOpt);
	AddSolGEMCMaterial(mats);

  ///< Parameters Map
	msg = " Parameter factory selected: " + gemcOpt.args["PARAMETERSDB"].args;
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
  map<string, parameterFactory> parameterFactoriesMap = registerParameterFactories();
  parameters *parameterSelectedFactory = getParameterFactory(&parameterFactoriesMap, gemcOpt.args["PARAMETERSDB"].args);
	map<string, double> gParameters = parameterSelectedFactory->initParameters(RunConditions, gemcOpt);
  
  ///< Process Hit Map
	msg = " Building gemc Process Hit Factory...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	map<string, MPHB_Factory> MProcessHit_Map = HitProcess_Map(gemcOpt.args["HIT_PROCESS_LIST"].args);
	AddSoLIDHP(MProcessHit_Map);
	
	
	///< Bank Map
	msg = " Retrieving gemc Banks Map...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	map<string, MBank> MBank_Map = read_banks(gemcOpt, MProcessHit_Map);

	///< magnetic Field Map
	msg = " Retrieving gemc Magnetic Fields Map...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	map<string, MagneticField> FieldMap = get_magnetic_Fields(gemcOpt);
	
  
  
	///< Build G4 Physical Volumes: MDetectorConstruction
	MDetectorConstruction* ExpHall = new MDetectorConstruction(gemcOpt);
	ExpHall->Hall_Map = &Hall_Map;
	ExpHall->mats    = &mats;
	ExpHall->FieldMap = &FieldMap;
	runManager->SetUserInitialization(ExpHall);
	
  
	///< Physics List
	string phys_list = gemcOpt.args["USE_PHYSICSL"].args  ;
	msg = " Initializing Physics List " + phys_list + "...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;

	G4VUserPhysicsList* physics = NULL;
	G4VModularPhysicsList* phys = NULL;
	G4PhysListFactory factory;
	
	if(phys_list == "gemc")
	{
		physics = new MPhysicsList(gemcOpt);
		runManager->SetUserInitialization(physics);
	} else if(phys_list == "noint" ) {
	        physics = new SolidNoPhysicsList(gemcOpt);
	        runManager->SetUserInitialization(physics);
	} else {
		if(factory.IsReferencePhysList(phys_list))
				phys = factory.GetReferencePhysList(phys_list);

		if(!phys) phys = factory.ReferencePhysList();
			
		runManager->SetUserInitialization(phys);
	}

	// need to use flags for both these here
	//  	physics->SetDefaultCutValue(0.1*mm);
	
	// Setting Max step for all the simulation. This is historically needed to limit 
	// the step in magnetic field in vacuum
	double max_step = gemcOpt.args["MAX_FIELD_STEP"].arg;
	if(max_step != 0)
		G4TransportationManager::GetTransportationManager()->GetPropagatorInField()->SetLargestAcceptableStep(max_step);
	
	///< Generator
	msg = " Initializing Primary Generator Action...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;

	// parse output file format
	int commaplace = gemcOpt.args["INPUT_GEN_FILE"].args.find_first_of(',');
	string fform = gemcOpt.args["INPUT_GEN_FILE"].args.substr(0,commaplace);

	G4VUserPrimaryGeneratorAction* gen_action;
	MPrimaryGeneratorAction* dummygen_action = new MPrimaryGeneratorAction(&gemcOpt);

	if( fform == "SOLLUND" ){
	    gen_action = new SolPrimaryGeneratorAction(&gemcOpt);
	} else {
	    gen_action = new MPrimaryGeneratorAction(&gemcOpt);
	}
	runManager->SetUserAction(gen_action);
	
  
	///< Event Action
	msg = " Initializing Event Action...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	MEventAction* event_action = new MEventAction(gemcOpt, gParameters);
	event_action->SetEvtNumber((int) gemcOpt.args["EVN"].arg);     ///< Sets event number from OPTION
	runManager->SetUserAction(event_action);
	
  
	///< Stepping Action
	msg = " Initializing Stepping Action...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	MSteppingAction* SteppingAction = new MSteppingAction(gemcOpt);
	runManager->SetUserAction(SteppingAction);
	
	///< User Interface manager
	// need UIQt to see Qt Open GL - have to comment line 136 of visualization/OpenGL/src/G4OpenGLQtViewer.cc
	msg = " Initializing User Interface...";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
  G4UIsession *session = NULL;
	if(use_qt) 
    session = new G4UIQt(argc,argv);
		
	///< Vis Manager
  G4VisManager *visManager = NULL;
  if(use_qt)
  {
    visManager = new G4VisExecutive;
    visManager->Initialize();
	}
  
	///< Initialize G4 kernel
	msg = " Initializing Run Manager...\n";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	runManager->Initialize();

  // Getting UI manager, restoring G4Out to cout
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->SetCoutDestination(NULL);

	///< Output File: registering output type, output process factory,
	///< sensitive detectors into Event Action
	msg = " Initializing Output Action...";
	MOutputs MOutput(gemcOpt);
	
	map<string, MOutput_Factory> MProcessOutput_Map = Output_Map();
	
	event_action->MOut            = &MOutput;
	event_action->Out             = &MProcessOutput_Map;
	event_action->MProcessHit_Map = &MProcessHit_Map;
	event_action->SeDe_Map        = ExpHall->SeDe_Map;
	event_action->MBank_Map       = &MBank_Map;
	event_action->gen_action      = dummygen_action;
	
	///< passing output process factory to sensitive detectors
	map<string, MSensitiveDetector*>::iterator it;
	for(it = ExpHall->SeDe_Map.begin(); it != ExpHall->SeDe_Map.end(); it++)
		it->second->MProcessHit_Map = &MProcessHit_Map;
	

	msg = " Executing initial directives...\n";
	if(use_qt) splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
	vector<string> init_commands = init_dmesg(gemcOpt);
	for(unsigned int i=0; i<init_commands.size(); i++)
		UImanager->ApplyCommand(init_commands[i].c_str());

	string exec_macro = "/control/execute " + gemcOpt.args["EXEC_MACRO"].args;

	
	if(use_qt)
	{
    splash->showMessage("Starting GUI...");
		gemc_gui.processEvents();
		
		gemcMainWidget gemcW(runManager, visManager, &gemcOpt, ExpHall->SeDe_Map);
		gemcW.Hall_Map = &Hall_Map;
		gemcW.SeDe_Map = ExpHall->SeDe_Map;
		gemcW.mats    = &mats;
		
		gemcW.setWindowTitle( "solgemc" );
		
		gemcW.show();
		splash->finish(&gemcW);

		msg = " Executing initial visual directives...\n";
		splash->showMessage(msg.c_str()); gemc_gui.processEvents(); cout << hd_msg << msg << endl;
		vector<string> init_vcommands = init_dvmesg(gemcOpt, visManager);
		for(unsigned int i=0; i<init_vcommands.size(); i++)
		{
			cout << " >> Now executing: " << init_vcommands[i].c_str() << endl;
			UImanager->ApplyCommand(init_vcommands[i].c_str());
		}
		
		if(exec_macro != "/control/execute no") UImanager->ApplyCommand(exec_macro.c_str());
		if(gemcOpt.args["N"].arg>0)
		{
			char command[100];
			sprintf(command, "/run/beamOn %d", (int) gemcOpt.args["N"].arg);
			UImanager->ApplyCommand(command);
		}

		return gemc_gui.exec();
		// deleting the visManager and runManager is now taken care 
		// in the gemc_quit slot
		// since qApp->quit() also calls an exit 
		cout << " >> Exiting gemc qApp." << endl;
		delete visManager;
    if(session != NULL) delete session;
	}
	else
	{
		if(gemcOpt.args["N"].arg>0)
		{
			char command[100];
			sprintf(command, "/run/beamOn %d", (int) gemcOpt.args["N"].arg);
			UImanager->ApplyCommand(command);
		}
		if(exec_macro != "/control/execute no") UImanager->ApplyCommand(exec_macro.c_str());
	}
	
	delete runManager;	
  return 1;
}








