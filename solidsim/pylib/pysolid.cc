#include <boost/python.hpp>

using namespace boost::python;

/*!
  Include exposed classes for the python interface

Example:
#include <G4VSensitiveDetector.hh>
#include <SolidGenericDet.hh>

BOOST_PYTHON_MODULE(pysolid) {
    class_<SolidGenericDet, bases<G4VSensitiveDetector> >("SolidGenericDet", init<const G4String&>() )
    ;
}

*/ 


#include <G4VSensitiveDetector.hh>
#include <SolidGenericDet.hh>
#include <SolidData.hh>

BOOST_PYTHON_MODULE(pysolid) {
    class_<SolidGenericDet, bases<G4VSensitiveDetector> >("SolidGenericDet", init<const G4String&>() )
    ;
//    class_<SolidData>("SolidGenericDet", init<const G4String&>() )
//    ;
}
