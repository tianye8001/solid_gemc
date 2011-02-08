FC=gfortran
CC=g++
CXX=g++
FFLAGS=
CCFLAGS=-fPIC -g -Wall
EXEC=root2lund

all: $(EXEC)

root2lund : roottolund.o
	$(CC) $^  -L/usr/lib/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lz -pthread -lm -ldl -rdynamic -o $@ 

roottolund.o : roottolund.C
	$(CC)  -c $(CCFLAGS) $< -o $@



#####################################

clean :
	-rm -f *.o $(EXEC)
