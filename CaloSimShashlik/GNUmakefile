# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------
G4LIB_BUILD_SHARED := 
G4WORKDIR := ../

name := CaloSimShashlik
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

CPPFLAGS  += $(shell $(ROOTSYS)/bin/root-config --cflags) -I/usr/include/c++/3.4.6/backward
EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --glibs)
# EXTRA_LINK_DEPENDENCIES := $(HOME)/Xplotter/lib/libXplotter.a

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk
