#!/bin/csh
uname -a | cat > out.log
more /etc/redhat-release | cat >> out.log
lscpu | cat >> out.log
more /proc/meminfo | cat >> out.log

#use official installation on farm and ifarm
setenv LD_LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
setenv LIBRARY_PATH /group/solid/solid_svn/evgen/cteq-pdf-1.0.4/lib
source /group/solid/solid_github/JeffersonLab/solid_gemc/set_solid 1.3 /group/solid/apps/jlab_root /group/solid/solid_github/JeffersonLab/solid_gemc

#run generator
cp /group/solid/solid_svn/evgen/eicRate_20101102/output/PolPdf_Linear.txt ./
cp /group/solid/solid_svn/evgen/eicRate_20101102/output/PolQuarkDist_fine.txt ./
#cp /group/solid/solid_svn/evgen/eicRate_20101102/output/input_solid_SIDIS_He3.dat input.dat
/group/solid/solid_svn/evgen/eicRate_20101102/eicRate -i input.dat -o gen.root -n 1e4 -m 20 | cat >> out.log

#run simulation
solid_gemc solid.gcard -INPUT_GEN_FILE="LUND,gen.lund" -N=1e4 | cat >> out.log

#convert evio to root
#need more option for banks other than flux
evio2root -INPUTF=out.evio -B="/group/solid/solid_github/JeffersonLab/solid_gemc/geometry/ec_segmented/solid_PVDIS_ec_forwardangle   /group/solid/solid_github/JeffersonLab/solid_gemc/geometry/lgc/lg_cherenkov  /group/solid/solid_github/JeffersonLab/solid_gemc/geometry/gem/solid_PVDIS_gem" | cat >> out.log

# cp /group/solid/solid_github/JeffersonLab/solid_gemc/analysis/SoLIDFileReduce.C ./
# root -b -q 'SoLIDFileReduce.C+("PVDIS","out.root")'

# mv -f out.root_skim out.root



