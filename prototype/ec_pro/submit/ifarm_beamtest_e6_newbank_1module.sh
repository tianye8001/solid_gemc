#!/bin/tcsh -f
#source /group/clas/builds/environment.csh
setenv LD_LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
setenv LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
source /group/solid/solid_github/JeffersonLab/solid_gemc/set_solid 1.3 /group/solid/apps/jlab_root /group/solid/solid_github/JeffersonLab/solid_gemc
#in batch
solid_gemc solid_PVDIS_EC_1module_newbank.gcard -BEAM_P="e-,6.0*GeV,0*deg,0*deg" -SPREAD_P="0*GeV,0*deg,0*deg" -BEAM_V="(-39.704,-120.984,10)cm" -SPREAD_V="(6.0, 0)cm" -N=1e2 -OUTPUT="evio,output.evio" -PRINT_EVENT=1 -USE_GUI=0
#convert evio file in standalone simulation to root file
evio2root -INPUTF=output.evio -B="/group/solid/solid_github/JeffersonLab/solid_gemc/geometry/ec_segmented_moved/solid_PVDIS_ec_forwardangle"

