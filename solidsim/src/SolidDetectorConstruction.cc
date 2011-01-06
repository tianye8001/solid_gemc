/*
*/

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "SolidDetectorMessenger.hh"
#include "SolidDetectorConstruction.hh"

#include "SolidFieldMap.hh"
#include "SolidFieldManager.hh"
#include "SolidSDMan.hh"

#include <Python.h>
#include <boost/python/extract.hpp>

/////////////////////////////////////////////////////////////////////////////
SolidDetectorConstruction::SolidDetectorConstruction() {
  fDetectorMessenger = new SolidDetectorMessenger(this);
  fFieldMan = new SolidFieldManager();

  // Default geometry file
  fGeoFile = "defaultgeo";

  // Initialize Python interpreter
  // There is no return value, there is a 
  // fatal error if it fails
  Py_Initialize();
}

/////////////////////////////////////////////////////////////////////////////
SolidDetectorConstruction::~SolidDetectorConstruction() { 
  delete fDetectorMessenger;
}

/*!
    SolidDetectorConstruction::Construct

    This constructs our geometry.  It presently uses a
    Python interpeter to set up the geometry (forgoing
    necessary recompilations and getting the features
    of Python available)

    returns a G4VPhysicalVolume which is our world
*/
G4VPhysicalVolume* SolidDetectorConstruction::Construct() {  
    const char *thisfunc = "Construct";

    // Initialize our SD manager
    SolidSDMan *sdman = new SolidSDMan();

    // Python function name
    const char *constfname = "Construct"; 

    char mutfname[255]; // Intermedate object to pass 
                        // in non-const functions
    strcpy(mutfname, constfname);

    /*!
      	This is where our Python interpeter gets read in.
	It's important that we don't Py_DECREF pModule
	too much or the module itself will go out of scope 
	and wreck even our global variables
    */

    // Set up to read from file in fGeoFile
    PyObject *pName   = PyString_FromString(fGeoFile.data());
    PyObject *pModule = PyImport_Import(pName);

    if( pModule == NULL ){
	fprintf(stderr, "%s::%s Loading module %s failed\n", 
		GetClassName(), thisfunc, fGeoFile.data()); 
	fprintf(stderr, "Make sure it is in your $PYTHONPATH and that\n");
	fprintf(stderr, "you can run it with 'python %s.py'\n", 
		fGeoFile.data());
	exit(1);
    }

    PyObject *pValue, *pArgs, *pFunc;
    G4PVPlacement *world = NULL;

    // Get the construct function from the file
    pFunc = PyObject_GetAttrString(pModule, mutfname);

    if (pFunc && PyCallable_Check(pFunc)) {
	// Call function and get return value
	pValue = PyObject_CallObject(pFunc, pArgs = PyTuple_New(0));
	// Didn't return something valid
	if( !pValue ){
	    fprintf(stderr, "%s::%s Python function %s::%s\
		    failed (returned NULL)\n",
		    GetClassName(), thisfunc, fGeoFile.data(), constfname);
	    exit(1);
	}
	// Extract our world volume from the return value
	world = boost::python::extract<G4PVPlacement *>(pValue);
	if( !world ){
	    // Couldn't cast
	    // Didn't get back what we expected...
	    fprintf(stderr, "%s::%s G4PVPlacement extraction\
		    from interpreter failed\nPython %s::%s did\
		    not return a G4PVPlacement\n",
		    GetClassName(), thisfunc, fGeoFile.data(),constfname);
	    exit(1);
	}
    } else {
	// The function wasn't able to be called from the module
	// This seems to usually happen if there's some error 
	// if you try to run the thing
	if( !pFunc ){
	    fprintf(stderr, "%s::%s Python function %s::%s was not found\n",
		    GetClassName(), thisfunc, fGeoFile.data(),constfname);
	    fprintf(stderr, "Make sure you can run 'python %s.py'\n", 
		    fGeoFile.data());
	} else {
	    fprintf(stderr, "%s::%s Python object %s::%s is not a\
		    callable function\n",
		    GetClassName(), thisfunc, fGeoFile.data(),constfname);
	}
	exit(1);
    }

    // We set the fields to logical volumes
    // in the interpreter, but the field manager
    // sets everything up in terms of the chord finder, etc
    // since the Python bindings seem to be of limited
    // functionality
    
    int ret = fFieldMan->ProcessFieldMaps();

    if( ret == -1 ){
	fprintf(stderr, "%s::%s Adding fields has failed\n",
		GetClassName(), thisfunc );
	// Something is wrong.  Let's die here before running
	// further
	exit(1);
	return NULL;
    }

    // Add the SD detectors to the manager
    G4SDManager* g4sdman = G4SDManager::GetSDMpointer();
    g4sdman->SetVerboseLevel(1000);

    unsigned int i;
    for( i = 0; i < sdman->GetNdet(); i++ ){
	g4sdman->AddNewDetector(sdman->GetDet(i));
    }

    sdman->Clear();

    return world;
}
