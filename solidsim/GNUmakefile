# --------------------------------------------------------------
# GNUmakefile for SolidSim module.  Seamus Riordan Dec 3, 2010
# --------------------------------------------------------------

name := SolidSim
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../../
endif

# get ROOT libraries and headers

ROOT_INCDIR := $(shell root-config --incdir)
ROOT_LIBDIR := $(shell root-config --libdir)
ROOT_LIBFLG := $(shell root-config --libs)

include $(G4INSTALL)/config/architecture.gmk

.PHONY: all
 
all: lib bin

include config/binmake.gmk

# include ROOT flags in compilation
INCFLAGS += -I$(ROOT_INCDIR) -I/usr/include/python2.4/
LDFLAGS  += -L$(ROOT_LIBDIR) $(ROOT_LIBFLG) -lpython2.4 -lboost_python
CXXFLAGS += -g

