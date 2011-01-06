# --------------------------------------------------------------
# GNUmakefile for SolidSim module.  Seamus Riordan Dec 3, 2010
# --------------------------------------------------------------

name := SolidSim
G4TARGET := $(name)
G4EXLIB := true
G4NO_OPTIMISE := 1

ifndef G4INSTALL
  G4INSTALL = ../../../
endif

# get ROOT libraries and headers

ROOT_INCDIR := $(shell root-config --incdir)
ROOT_LIBDIR := $(shell root-config --libdir)
ROOT_LIBFLG := $(shell root-config --libs)

PY_INCFLG   := $(shell ./config/getpyconfig.pl --includes)
PY_LIBFLG   := $(shell ./config/getpyconfig.pl --libs)

include $(G4INSTALL)/config/architecture.gmk

.PHONY: all
 
all: lib bin

include config/binmake.gmk

# include ROOT flags in compilation
INCFLAGS += -I$(ROOT_INCDIR) $(PY_INCFLG)
LDFLAGS  += -L$(ROOT_LIBDIR) $(ROOT_LIBFLG) $(PY_LIBFLG) -lboost_python
CXXFLAGS += -g

