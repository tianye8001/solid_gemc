# $Id: GNUmakefile,v 1.1 2006/05/11 03:00:08 kmura Exp $
# $Name: geant4-09-02 $
# ===========================================================
#   Makefile for building Geant4Py modules
# ===========================================================

# python module name
MODULE := pysolid

CPPVERBOSE := 1

G4PY_INSTALL := $(G4INSTALL)/environments/g4py

# get ROOT libraries and headers

ROOT_INCDIR := $(shell root-config --incdir)
ROOT_LIBDIR := $(shell root-config --libdir)
ROOT_LIBFLG := $(shell root-config --libs)

include $(G4PY_INSTALL)/config/config.gmk
include $(G4PY_INSTALL)/config/g4py.gmk
include $(G4PY_INSTALL)/config/module.gmk

# Need object files from sources
# FIXME  Adding ROOT_LIBFLG is a kludge
objects  += $(patsubst ../src/%.cc, %.o, $(wildcard ../src/*cc)) $(ROOT_LIBFLG) --no-undefined

# Need this to build wrapper C code
CXXFLAGS += -I../include 
