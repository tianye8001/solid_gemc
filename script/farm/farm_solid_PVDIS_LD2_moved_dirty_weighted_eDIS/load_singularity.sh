#!/bin/tcsh
uname -a | cat > out.log
more /etc/redhat-release | cat >> out.log
lscpu | cat >> out.log
more /proc/meminfo | cat >> out.log
pwd | cat >> out.log

setenv LD_LIBRARY_PATH /group/solid/apps/evgen/cteq-pdf-1.0.4/lib
setenv LIBRARY_PATH /group/solid/apps/evgen/cteq-pdf-1.0.4/lib
setenv ROOTSYS /group/solid/apps/root/root_v5.34.36.Linux-centos7-x86_64-gcc4.8
setenv PATH ${ROOTSYS}/bin:${PATH}
if (!($?LD_LIBRARY_PATH)) then
  setenv LD_LIBRARY_PATH ${ROOTSYS}/lib
else
  setenv LD_LIBRARY_PATH ${ROOTSYS}/lib:${LD_LIBRARY_PATH}
endif
# which root

#run generator
cp /group/solid/solid_github/JeffersonLab/evgen_inclusive/output/PolPdf_Linear.txt ./
cp /group/solid/solid_github/JeffersonLab/evgen_inclusive/output/PolQuarkDist_fine.txt ./
#cp /group/solid/solid_github/JeffersonLab/evgen_inclusive/output/input_solid_SIDIS_He3.dat input.dat
/group/solid/solid_github/JeffersonLab/evgen_inclusive/eicRate -i input.dat -o gen.root -n 1e4 -m 20 | cat >> out.log

#may need to slurm job
#source /etc/profile.d/modules.csh  

module load singularity/3.5.3
which singularity | cat >> out.log
singularity exec /group/solid/apps/jeffersonlab_jlabce_tagdevel_digestsha256:01eac4333bdd2077233076363983d1898775c6c61e8f5c5b0b9f324c75c4da3c_20200409_s3.5.3.sif ./do_it_all.sh


