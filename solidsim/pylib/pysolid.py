from SolidGeant4 import *

#----------------------------------------------------
# include exposed interfaces to the Python
# interpreter
#
# Example:
#class SolidGenericDet(G4VSensitiveDetector):
#    "Generic Solid SD"
#    def __init_(self, sdname):
#	G4VSensitiveDetector.__init__(self, sdname)
# 
#----------------------------------------------------

class SolidGenericDet(G4VSensitiveDetector, SolidData):
    "Generic Solid SD"
    def __init_(self, sdname):
	G4VSensitiveDetector.__init__(self, sdname)
	SolidData.__init__(self, sdname)

class SolidSimpleField(G4MagneticField, SolidSimpleField):
    "Generic Solid SD"
    def __init_(self, sdname, logvol):
	G4MagneticField.__init__(self)
	SolidFieldMap.__init__(self, sdname, logvol)

#class SolidData():
#    "Solid data container"
#    def __init_(self, sdname):
