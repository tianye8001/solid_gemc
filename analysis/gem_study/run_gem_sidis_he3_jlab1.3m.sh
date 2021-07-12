#!/bin/csh
source /group/solid/solid_github/JeffersonLab/solid_gemc/set_solid 1.3 /group/solid/apps/jlab_root /group/solid/solid_github/JeffersonLab/solid_gemc

#run simulation
solid_gemc solid_SIDIS_gem.gcard -BEAM_P="e-,1*GeV,20*deg,0*deg" -SPREAD_P="0*GeV,0*deg,0*deg" -BEAM_V="(0,0,-350)cm" -SPREAD_V="(0.0,0)cm" -OUTPUT=evio,gem_sidis_he3_jlab1.3m.evio -N=1e5

#convert evio to root
#need more option for banks other than flux
evio2root -INPUTF=gem_sidis_he3_jlab1.3m.evio -B="solid_SIDIS_gem"
