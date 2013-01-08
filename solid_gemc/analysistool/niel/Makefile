FC=gfortran
CC=g++
CXX=g++
FFLAGS=
CCFLAGS=-fPIC -g -Wall
SHARED=niel_fun_lib.so


all: $(SHARED)



niel_fun_Dict.cxx: niel_fun.h niel_fun_Linkdef.h
	rootcint -f $@ -c $(CCFLAGS) -p $^
 
niel_fun_lib.so: niel_fun_Dict.cxx niel_fun.cc
	g++ -shared -o$@ `root-config --ldflags` $(CCFLAGS) -I$(ROOTSYS)/include $^

#####################################

clean :
	-rm -f niel_fun_Dict.*  $(SHARED)
