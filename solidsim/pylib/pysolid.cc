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
#include <G4LogicalVolume.hh>
#include <SolidGenericDet.hh>
#include <SolidData.hh>
#include <SolidSimpleField.hh>
#include <SolidFieldMap.hh>

BOOST_PYTHON_MODULE(pysolid) {
    class_<SolidGenericDet, bases<G4VSensitiveDetector> >("SolidGenericDet", init<const G4String&>() );
    class_<SolidSimpleField, bases<G4MagneticField> >("SolidSimpleField", init<G4String,G4LogicalVolume *>() );
//    class_<SolidData>("SolidGenericDet", init<const G4String&>() )
//    ;
}
