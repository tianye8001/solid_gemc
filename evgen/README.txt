== PVDIS event generator ==========================================================================

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


 root2lund : This Program translate the output from eicRate in LUND format and Filter the scattered electron angles
 Usage: root2lund -o outputfile -i inputfile [-th_min theta_min] [-th_max theta_max] [-ph_min phi_min] [-ph_max phi_max] [-l 1-0] [-g 1-0]
     -o outputfile     : output file name (example pluto.lund)  
     -i inputfile      : input file name (example pluto.root)  
     -h help, print this message 
   [optional] 
     -th_min theta_min : specify theta minimum for scattered electron 
     -th_max theta_max : specify theta maximum for scattered electron 
     -ph_min phi_min   : specify phi minimum for scattered electron 
     -ph_max phi_max   : specify phi maximum for scattered electron 
     -l 1-0            : specify format input file ( lund-> 1 (just angle filtering); root->0 (default) )
     -g 2-1-0          : specify if particle in output is a geantino ( geantino-> 1 ; charged geantino-> 2 ; normal->0 (default) )
 --- 

== SIDIS event generator ==========================================================================
tested on ifarm64

1. get lhapdf and compile
http://www.hepforge.org/archive/lhapdf/lhapdf-5.8.5.tar.gz
./configure --prefix=/home/zwzhao/apps/Linux_CentOS5.3-x86_64-gcc4.1.2/lhapdf CC=/usr/bin/gcc CXX=/usr/bin/g++ FC=/usr/bin/gfortran
make
make install
setenv LHAPDF /home/zwzhao/apps/Linux_CentOS5.3-x86_64-gcc4.1.2/lhapdf/lib
setenv LD_LIBRARY_PATH ${LHAPDF}/lib:${LD_LIBRARY_PATH}
download http://www.hepforge.org/archive/lhapdf/pdfsets/5.8.5/cteq6m.LHpdf and put it at $LHAPDF/share/lhapdf

2. compile collider
cd collider
source  /apps/root/PRO/setroot_CUE
make
run "./collider" to see all running options
