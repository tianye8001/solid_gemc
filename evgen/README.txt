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