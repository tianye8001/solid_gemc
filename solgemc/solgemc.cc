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
#include "detector_factory.h"
#include "gemc_MainGui.h"
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
#include "string_utilities.h"
#include "utils.h"

/////////////////////////
/// <b> Main Program </b>
/////////////////////////
///  -# Sets the gemc_opts\n
///  -# Starts QT application if USE_GUI=1
///  -# Starts the CLHEP random engine
///  -# Instantiates the Geant4 Run Manager
///  -# Builds detector map object from database
///  -# Builds Processes Routines Map
///  -# Builds Materials Map
///  -# Builds G4 Physical Volumes
///  -# Initialize Physics List
///  -# Initialize Generator
///  -# Initialize Event Action
///  -# Initialize G4Qt User Interface if USE_GUI>0
///  -# Initialize Visualization Manager if USE_GUI>0


// get_pid is useful only on the farm to set the seed
// can set to zero in Windows environment
// ideally we'd want __get_pid();
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
	double use_gui = gemcOpt.args["USE_GUI"].arg;
	
	// Initializing QT application
	QApplication gemc_gui( argc, argv, (bool) use_gui );

	// Initializing gemc splash class
	// This class will log initialization messages
	// This class will show a splashscreen if use_gui is non zero
	gui_splash gemc_splash(use_gui, gemcOpt.args["QTSTYLE"].args, gemcOpt.args["LOG_MSG"].args + " Init: >> " );
	gemc_splash.message(gemcOpt.args["LOG_MSG"].args + " Initializing GEant4 MonteCarlo");

	
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

	
	// random seed initialization
	CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
	G4int seed;
	
	if(gemcOpt.args["RANDOM"].args=="TIME")
	{
		gemc_splash.message(" Initializing CLHEP Random Engine from local time " \
		                   + stringify((double) time(NULL)) \
											 + ", cpu clock "        \
											 + stringify((double) clock())    \
											 + " and process id "    \
											 + stringify(getpid()) + ".");
		seed = (G4int) ( (double) time(NULL)- (double) clock()-getpid() );
	}
	else
	{
		seed = atoi(gemcOpt.args["RANDOM"].args.c_str());
		gemc_splash.message(" Initializing CLHEP Random Engine from user defined seed.");
	}
	CLHEP::HepRandom::setTheSeed(seed);
	gemc_splash.message(" Seed initialized to: " + stringify(seed));
		
	// Construct the default G4 run manager
	gemc_splash.message(" Instantiating Run Manager...");	
	G4RunManager *runManager = new G4RunManager;
	
	// Initializing run_condition class
	gemc_splash.message(" Instantiating Run Conditions...");	
	runConditions runConds(gemcOpt);

  // GEMC Detector Map
	gemc_splash.message(" Retrieving gemc Detector Map...");
	// Initializing Detector Factory
	map<string, detectorFactoryMap> dFactory = registerDetectorFactory();
	cout << check_factory_existance(dFactory, runConds) << endl;
	// Building detector with factory
	map<string, detector> hallMap = build_detector(dFactory, gemcOpt, runConds);

	  
	// Initialize Materials Map Factory
	gemc_splash.message(" Material factory selected: " + gemcOpt.args["MATERIALSDB"].args);
  map<string, materialFactory> materialFactoriesMap = registerMaterialFactories();
  materials *materialSelectedFactory = getMaterialFactory(&materialFactoriesMap, gemcOpt.args["MATERIALSDB"].args);
	map<string, G4Material*> mats = materialSelectedFactory->initMaterials(runConds, gemcOpt);
	AddSolGEMCMaterial(mats);

  // Initialize Parameters Map Factory
	gemc_splash.message(" Parameter factory selected: " + gemcOpt.args["PARAMETERSDB"].args);
  map<string, parameterFactory> parameterFactoriesMap = registerParameterFactories();
  parameters *parameterSelectedFactory = getParameterFactory(&parameterFactoriesMap, gemcOpt.args["PARAMETERSDB"].args);
	map<string, double> gParameters = parameterSelectedFactory->initParameters(runConds, gemcOpt);
  	
 // Creating the sim_condition map to save to the output
	gemc_splash.message(" Writing simulation parameters in the output...");
	
	// filling gcard option content
  map<string, string> sim_condition = gemcOpt.getOptMap();
  
	// adding detectors 
	MergeMaps(sim_condition, runConds.getDetectorConditionsMap());
	
	// adding parameters 
	MergeMaps(sim_condition, getParMap(gParameters));

  // Process Hit Map
	gemc_splash.message(" Building gemc Process Hit Factory...");
	map<string, MPHB_Factory> MProcessHit_Map = HitProcess_Map(gemcOpt.args["HIT_PROCESS_LIST"].args);
	AddSoLIDHP(MProcessHit_Map);
	
	// Bank Map
	gemc_splash.message(" Retrieving gemc Banks Map...");
	map<string, MBank> MBank_Map = read_banks(gemcOpt, MProcessHit_Map);
		
	///< magnetic Field Map
	gemc_splash.message(" Retrieving gemc Magnetic Fields Map...");
	map<string, MagneticField> FieldMap = get_magnetic_Fields(gemcOpt);
  
	// Build the detector
	gemc_splash.message(" Building Detector...");
	MDetectorConstruction* ExpHall = new MDetectorConstruction(gemcOpt);
	ExpHall->hallMap  = &hallMap;
	ExpHall->mats     = &mats;
	ExpHall->FieldMap = &FieldMap;
	runManager->SetUserInitialization(ExpHall);
	
  
	///< Physics List
	string phys_list = gemcOpt.args["USE_PHYSICSL"].args  ;
	gemc_splash.message(" Initializing Physics List " + phys_list + "...");

	G4VUserPhysicsList* physics = NULL;
	G4VModularPhysicsList* phys = NULL;
	G4PhysListFactory factory;
	
	if(phys_list == "gemc")
	{
		physics = new MPhysicsList(gemcOpt);
		runManager->SetUserInitialization(physics);
	}
	else if(phys_list == "noint" )
	{
	       physics = new SolidNoPhysicsList(gemcOpt);
	       runManager->SetUserInitialization(physics);
	}
	else {
		if(factory.IsReferencePhysList(phys_list))
				phys = factory.GetReferencePhysList(phys_list);

		if(!phys) phys = factory.ReferencePhysList();
			
		runManager->SetUserInitialization(phys);
	}

	// need to use flags for both these here
	// physics->SetDefaultCutValue(0.1*mm);
	
	// Setting Max step for all the simulation. This is historically needed to limit 
	// the step in magnetic field in vacuum
	double max_step = gemcOpt.args["MAX_FIELD_STEP"].arg;
	if(max_step != 0)
		G4TransportationManager::GetTransportationManager()->GetPropagatorInField()->SetLargestAcceptableStep(max_step);
	
	// Generator
	gemc_splash.message(" Initializing Primary Generator Action...");

	 // parse output file format
	int commaplace = gemcOpt.args["INPUT_GEN_FILE"].args.find_first_of(',');
	string fform = gemcOpt.args["INPUT_GEN_FILE"].args.substr(0,commaplace);

	G4VUserPrimaryGeneratorAction* gen_action;
	MPrimaryGeneratorAction* dummy_action = new MPrimaryGeneratorAction(&gemcOpt);

	if( fform == "SOLLUND" ){
	    gen_action = new SolPrimaryGeneratorAction(&gemcOpt);
	} else {
	    gen_action = new MPrimaryGeneratorAction(&gemcOpt);
	}

	runManager->SetUserAction(gen_action);
  
	// Event Action
	gemc_splash.message(" Initializing Event Action...");
	MEventAction* event_action = new MEventAction(gemcOpt, gParameters);
	event_action->SetEvtNumber((int) gemcOpt.args["EVN"].arg);     ///< Sets event number from OPTION
	runManager->SetUserAction(event_action);
	
  
	// Stepping Action
	gemc_splash.message(" Initializing Stepping Action...");
	MSteppingAction* SteppingAction = new MSteppingAction(gemcOpt);
	runManager->SetUserAction(SteppingAction);
	
	///< User Interface manager
	gemc_splash.message(" Initializing User Interface...");
  G4UIsession *session = NULL;
	if(use_gui) 
    session = new G4UIQt(argc,argv);
		
	///< Vis Manager
  G4VisManager *visManager = NULL;
  if(use_gui)
  {
    visManager = new G4VisExecutive;
    visManager->Initialize();
	}
  
	// Initialize G4 kernel
	gemc_splash.message(" Initializing Run Manager...\n");
	runManager->Initialize();

  // Getting UI manager, restoring G4Out to cout
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->SetCoutDestination(NULL);

	// Output File: registering output type, output process factory,
	// sensitive detectors into Event Action
	gemc_splash.message(" Initializing Output Action...");
	MOutputs MOutput(gemcOpt);
	map<string, MOutput_Factory> MProcessOutput_Map = Output_Map();

	// saving simulation condition in the output file
  if(MOutput.outType != "no")
  {
		MOutputBaseClass *ProcessOutput  = GetMOutputClass(&MProcessOutput_Map, MOutput.outType);
		ProcessOutput->SaveSimConditions(&MOutput, sim_condition);
		delete ProcessOutput;
	}
  
	event_action->MOut            = &MOutput;
	event_action->Out             = &MProcessOutput_Map;
	event_action->MProcessHit_Map = &MProcessHit_Map;
	event_action->SeDe_Map        = ExpHall->SeDe_Map;
	event_action->MBank_Map       = &MBank_Map;
	event_action->gen_action      = dummy_action;
	
	///< passing output process factory to sensitive detectors
	map<string, MSensitiveDetector*>::iterator it;
	for(it = ExpHall->SeDe_Map.begin(); it != ExpHall->SeDe_Map.end(); it++)
		it->second->MProcessHit_Map = &MProcessHit_Map;
	

	gemc_splash.message(" Executing initial directives...\n");
	vector<string> init_commands = init_dmesg(gemcOpt);
	for(unsigned int i=0; i<init_commands.size(); i++)
		UImanager->ApplyCommand(init_commands[i].c_str());
	string exec_macro = "/control/execute " + gemcOpt.args["EXEC_MACRO"].args;

	// Write out GDML
	G4GDMLParser parser;
	G4VPhysicalVolume* pWorld =
	    G4TransportationManager::GetTransportationManager()->
	    GetNavigatorForTracking()->GetWorldVolume();
	// Make sure file does not exist first.  if it does
	// remove it so we can overwrite it
	unlink("solgemc.gdml");
	parser.Write("solgemc.gdml", pWorld);

	
	if(use_gui)
	{
		gemc_splash.message("Starting GUI...");
		gemc_gui.processEvents();
		
		gemcMainWidget gemcW(runManager, visManager, &gemcOpt, ExpHall->SeDe_Map);
		gemcW.hallMap  = &hallMap;
    gemcW.SeDe_Map = ExpHall->SeDe_Map;
		gemcW.mats     = &mats;
		
		gemcW.setWindowTitle( "solgemc" );
		
		gemcW.show();
		
		// splash can finish once gemcW is up
		gemc_splash.splash->finish(&gemcW);

		gemc_splash.message(" Executing initial visual directives...\n");
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








