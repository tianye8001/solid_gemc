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
solid_gemc solid_SIDIS_gem.gcard -BEAM_P="e-,1*GeV,20*deg,0*deg" -SPREAD_P="0*GeV,0*deg,0*deg" -BEAM_V="(0,0,-350)cm" -SPREAD_V="(0.0,0)cm" -OUTPUT=evio,gem_sidis_he3_commit2fef2c2.evio -N=1e5

#convert evio to root
#which  evio2root
evio2root -INPUTF=gem_sidis_he3_commit2fef2c2.evio -B="solid_SIDIS_gem" -R="flux" 

