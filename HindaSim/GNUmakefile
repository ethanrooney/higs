# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:42 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------



name := HindaSim
G4TARGET := $(name)
G4EXLIB := true
INCLUDES+=$PWD/src

#ifndef G4INSTALL
G4INSTALL := /home/ethan/geant/geant4-10.6.2
#endif

.PHONY: all
all: rootcint lib bin

#include $(G4INSTALL)/config/architecture.gmk

G4NOHIST := true
#CPPFLAGS += $(shell root-config --cflags)
LDFLAGS  += $(shell root-config --glibs)
#LDFLAGS  += -lXMLIO
CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
#EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --libs)
LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs)

rootcint: 
	@echo "----- Making Dictionaries -----"
#	rootcint -f $(PWD)/src/EventDict.cc -c $(PWD)/include/Event.hh $(PWD)/include/EventLinkDef.h
#	rm src/*Dict.*

include $(G4INSTALL)/config/binmake.gmk

#%Dict.cc: %.hh 
#	@echo "- - - - Making Dictionaries - - - "
#	@$(ROOTSYS)/bin/rootcint -f $@ -c $(INCLUDES) $< $(<:.h=LinkDef.h)
