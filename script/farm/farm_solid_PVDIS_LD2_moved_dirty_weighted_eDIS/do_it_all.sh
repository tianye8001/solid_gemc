#!/bin/csh -f

#use official installation on farm and ifarm
# setenv LD_LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
# setenv LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
# # source /group/solid/solid_github/JeffersonLab/solid_gemc/set_solid 1.3 /group/solid/apps/jlab_root /group/solid/solid_github/JeffersonLab/solid_gemc

# #run generator
# cp /group/solid/solid_svn/evgen/eicRate_20101102/output/PolPdf_Linear.txt ./
# cp /group/solid/solid_svn/evgen/eicRate_20101102/output/PolQuarkDist_fine.txt ./
# #cp /group/solid/solid_svn/evgen/eicRate_20101102/output/input_solid_SIDIS_He3.dat input.dat
# /group/solid/solid_svn/evgen/eicRate_20101102/eicRate -i input.dat -o gen.root -n 1e4 -m 20 | cat >> out.log

source /jlab/devel/ce/jlab.csh
setenv SoLID_GEMC /group/solid/solid_github/JeffersonLab/solid_gemc
setenv LD_LIBRARY_PATH ${GEMC}:${LD_LIBRARY_PATH}
setenv PATH ${SoLID_GEMC}/source/commit2fef2c2:${PATH}
#setenv PATH /group/solid/devel/banks/bin:${PATH}
setenv PATH /group/solid/devel/banks_jlabsolid/bin:${PATH}
# setenv PATH /group/solid/devel/banks/bin:${PATH}
#setenv PATH /group/solid/devel/banks_zwzhao/bin:${PATH}

#run simulation
solid_gemc solid.gcard -INPUT_GEN_FILE="LUND,gen.lund" -N=1e4 | cat >> out.log

# solid_gemc solid.gcard -BEAM_P="e-,11*GeV,25*deg,0*deg" -BEAM_V="(0,0,10)cm" -N=1 

#convert evio to root
#need more option for banks other than flux
which  evio2root
evio2root -INPUTF=out.evio -B="/group/solid/solid_github/JeffersonLab/solid_gemc/geometry/ec_segmented_moved/solid_PVDIS_ec_forwardangle   /group/solid/solid_github/JeffersonLab/solid_gemc/geometry/lgc_moved/lg_cherenkov  /group/solid/solid_github/JeffersonLab/solid_gemc/geometry/gem/solid_PVDIS_gem"  -R="flux" | cat >> out.log

# cp /group/solid/solid_github/JeffersonLab/solid_gemc/analysis/SoLIDFileReduce.C ./
# root -b -q 'SoLIDFileReduce.C+("PVDIS","out.root")'

# mv -f out.root_skim out.root




