#!/bin/csh -f

#setup env
source /jlab/devel/ce/jlab.csh
setenv SoLID_GEMC /group/solid/solid_github/JeffersonLab/solid_gemc
setenv LD_LIBRARY_PATH ${GEMC}:${LD_LIBRARY_PATH}
setenv PATH ${SoLID_GEMC}/source/commit2fef2c2:${PATH}
#setenv PATH /group/solid/devel/banks/bin:${PATH}
setenv PATH /group/solid/devel/banks_jlabsolid/bin:${PATH}
#setenv PATH /group/solid/devel/banks_zhaozhiwen/bin:${PATH}
#setenv PATH /group/solid/devel/banks_zwzhao/bin:${PATH}

#run simulation
solid_gemc solid_SIDIS_gem_virtualplane.gcard -BEAM_P="proton,5.5*GeV,15*deg,0*deg" -SPREAD_P="5.5*GeV,15*deg,180*deg" -BEAM_V="(0,0,-315)cm" -SPREAD_V="(0.0,7.5)cm" -OUTPUT=evio,gem_jpsi.evio -N=1e5

#convert evio to root
#which  evio2root
evio2root -INPUTF=gem_jpsi.evio -R="flux" 

