== inclusive event generator ======================================================

tested on ifarm1102 with CentOS6.2 x64 on 2013/07/31 by Zhiwen Zhao

FAST HOWTO COMPILE THIS GENERATOR

1) first you need a working version of cteq C interface library 
   orginal at http://desy.de/~znagy/hep-programs/cteq-pdf/
   local copy in evgen/cteq-pdf-1.0.4/

cd cteq-pdf-1.0.4/
./configure
make
make install

by default is going to write the desired library in /home/${user}/lib

2) The Generator itself (by Seamus Riordan)
Lorenzo Zana added the possibility to specify the input file and output file
Modified the random number generator to TRandom2 class (chosen for period and speed, see http://root.cern.ch/root/html/TRandom.html). The seed now is randomly generated too, so that different parallel simulation could point to the same input file (easier for scripting and parallel processing)

setup env (do this before compilation and running the code)

setenv LD_LIBRARY_PATH /home/${USER}/lib
setenv LIBRARY_PATH /home/${USER}/lib
source /apps/root/5.34.01/setroot_CUE
 
(root must have been built with OpenGL enabled. Note that the scripts supplied for installing GEMC build root with OpenGL disabled.)

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

refer to the content of input files under output dir for input options.

Besides root tree output, it can produce text output files at the same time which can be used as direct input for later detector simulation. There are two type of text files
1. lund format for vanilla GEMC to use as input which has NO rate information 
2. solund format for solgemc use as input which has rate information.

The output root tree structure is described in output/README

If you have root tree output, but no lund/solund output. No need to rerun eicRate, just do the conversion with root_to_lund below

3) Changing output from root format to lund format

cd root_to_lund/
make

ENVIRONMENT VARIABLES FOR COMPILING (example in bash):
If you are using root 5.28 like me seems you need to put some extra environment for your compiler for the "include" 
LD_LIBRARY_PATH=/home/${USER}/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
LIBRARY_PATH=/home/${USER}/lib:${ROOTSYS}/lib:$LIBRARY_PATH; export LIBRARY_PATH
C_INCLUDE_PATH=/home/${USER}/include:${ROOTSYS}/include:$C_INCLUDE_PATH; export C_INCLUDE_PATH
CPLUS_INCLUDE_PATH=/home/${USER}/include:${ROOTSYS}/include:$CPLUS_INCLUDE_PATH; export CPLUS_INCLUDE_PATH

(csh example)
setenv LD_LIBRARY_PATH ${ROOTSYS}/lib:/home/${USER}/lib:${LD_LIBRARY_PATH}
setenv CPLUS_INCLUDE_PATH /home/${USER}/include:${ROOTSYS}/include 
setenv LIBRARY_PATH /home/${USER}/lib:${ROOTSYS}/lib


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
tested on ifarm1101

1. get lhapdf and compile
mkdir lhapdf
wget http://www.hepforge.org/archive/lhapdf/lhapdf-5.8.5.tar.gz
tar zxf lhapdf-5.8.5.tar.gz
cd lhapdf-5.8.5
./configure --prefix=/PathOflhapdf CC=/usr/bin/gcc CXX=/usr/bin/g++ FC=/usr/bin/gfortran
make
make install
cd ../share/lhapdf
wget http://www.hepforge.org/archive/lhapdf/pdfsets/5.8.5/cteq6m.LHpdf

2. compile and run "collider"
cd collider
setenv ROOTSYS /apps/root/5.28-00c-64bit
setenv PATH ${ROOTSYS}/bin:${PATH}
setenv LD_LIBRARY_PATH ${ROOTSYS}/lib
#setenv LD_LIBRARY_PATH ${ROOTSYS}/lib:${LD_LIBRARY_PATH}
setenv LHAPDF /PathOflhapdf
setenv LD_LIBRARY_PATH ${LHAPDF}/lib:${LD_LIBRARY_PATH}
make
run "./collider" to see all running options

3. analysis result
mkdir analysis   (parallel with rootfiles generated from collider code)

copy generate_weight.C generate_plot.C into the analysis directory
also copy acceptance rootfile into analysis directory

root[] .x generate_weight.C
---->this will add two branches weight_hp, weight_hm in each file, they are xs in nbar for each event.

phase space in this script should be changed to be the same as that in collider.C code

root[] .x generate_plot.C("pion",1,0)

flag is explained in the code.

== inclusive rate calculation used for SIDIS proposal ==============================================

cd single_rate and type make

you use choose option 1 to use scattering e- mommentum and theta as variables
./main target(0 hydrogen,1 deuteron) Lumi(1e33 Hz/cm2) beam(GeV) option(1) bin mom_min(GeV) mom_max(GeV) theta_min(deg) theta_max(deg)

or you choose option 2 to use Q2 and x as variables  
./main target(0 hydrogen,1 deuteron) Lumi(1e33 Hz/cm2) beam(GeV) option(2) bin x_min x_max Q2_min(GeV2) Q2_max(GeV2)
this is not a complete feature. actuall cross section is all calculated in mom,theta bin, so a x,Q2 square bin will define ranges for mom,theta, then calculate in the coverted mom,theta bin square bin. But the actual coversion should be a quare, it only falls within the suqare, so it will be overestimate.

the parameter "bin" can be 1 or n.
If it's 1, the code only calculates rate at 1 point, the central of momentum and angle range.
If it's n, the code calculates n*n points within momentum and angle range and sum to get total rate

calc_rate.C calls on main to generate a rate plot

The code is based on some previous code, refer to 
"Software for estimating (e,e'), (e,pion) cross sections (10/22/2000) source code     instruction(html)"
at http://hallaweb.jlab.org/physics/experiments/he3/A1n/

== JPsi (decay to electron and position) generator ================================================

see readme in JPsi

== Bethe-heitler electron and position production used by TCS ====================================

see readme in genTCS

