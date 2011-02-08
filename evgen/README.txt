FAST HOWTO COMPILE THIS GENERATOR

tested on ifarml6 (64 bit)
ifarml6> echo $ROOTSYS
/u/apps/root/PRO/root


1) first you need a working version of cteq C interface library (http://desy.de/~znagy/hep-programs/cteq-pdf/)


cd cteq-pdf-1.0.4/
./configure
make
make install

by default is going to write the desired library in /home/${user}/lib
Remember to add this directory (or the one that you will choose) to your $LD_LIBRARY_PATH and $LIBRARY_PATH

for example:
setenv LD_LIBRARY_PATH /home/zana/lib:${LD_LIBRARY_PATH}
setenv LIBRARY_PATH /home/zana/lib:${LIBRARY_PATH}

2) The Generator itself (thanks Seamus)
I added the possibility to specify the input file and output file
Modified the random number generator to TRandom2 class (chosen for period and speed, see http://root.cern.ch/root/html/TRandom.html). The seed now is randomly generated too, so that different parallel simulation could point to the same input file (easier for scripting and parallel processing)
 
This Makefile has been tested in ifarml6 (64 bit) at Jefferson Lab today 12/03/2010



cd eicRate_20101102/
make

this will create the binary eicRate
one can test it for an example in the "output" directory 
It requires at the moment the file PolQuarkDist_fine.txt in the running directory.

 eicRate : This Program Generates events 
 Usage: eicRate -i inputfile -o outputfile 
     -i (or -input) inputfile    input file name with correct flags (default input.dat)  
     -o (or -output) outputfile output file name with correct flags (default output.root)
     -h (or -help) print this message 



3) Changing output from root format to lund format

cd root_to_lund/
make

ENVIRONMENT VARIABLES FOR COMPILING (example in bash):
If you are using root 5.28 like me seems you need to put some extra environment for your compiler for the "include" 
LD_LIBRARY_PATH=/home/zana/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
LIBRARY_PATH=/home/zana/lib:${ROOTSYS}/lib:$LIBRARY_PATH; export LIBRARY_PATH
C_INCLUDE_PATH=/home/zana/include:${ROOTSYS}/include:$C_INCLUDE_PATH; export C_INCLUDE_PATH
CPLUS_INCLUDE_PATH=/home/zana/include:${ROOTSYS}/include:$CPLUS_INCLUDE_PATH; export CPLUS_INCLUDE_PATH

(csh example)
setenv LD_LIBRARY_PATH ${ROOTSYS}/lib:/home/zana/lib:${LD_LIBRARY_PATH}
setenv CPLUS_INCLUDE_PATH /home/zana/include:${ROOTSYS}/include 
setenv LIBRARY_PATH /home/zana/lib:${ROOTSYS}/lib


root2lund : This Program translate the output from eicRate in LUND format 
Usage: root2lund -o outputfile -i inputfile 
     -o outputfile   - output file name (example pluto.lund)  
     -i inputfile   - input file name (example pluto.root)  
     -h help, print this message 
