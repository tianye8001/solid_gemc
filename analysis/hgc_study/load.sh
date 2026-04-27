#!/bin/tcsh
# uname -a | cat > out.log
# more /etc/redhat-release | cat >> out.log
# lscpu | cat >> out.log
# lsmem | cat >> out.log
# pwd | cat >> out.log

#setenv location /scigroup/cvmfs/halla/solid/soft
setenv location /cvmfs/oasis.opensciencegrid.org/jlab/halla/solid/soft/

#run generator
# apptainer exec -B /group,/u,/w,/cache,/volatile,/lustre -B $location/solidevgen_tag1:/evgen  $location/container/jeffersonlab_solidevgen_tag1_latest.sif ./evgen.sh commit0acacfe_20230908

# run solid_gemc
apptainer exec -B ${PWD}:/mywork -B /group,/u,/w,/cache,/volatile,/lustre -B /group/solid/solid_github/JeffersonLab/solid_gemc:/solid_gemc -B $location/field:/field $location/container/jeffersonlab_jlabce_tag2.5_digest:sha256:9b9a9ec8c793035d5bfe6651150b54ac298f5ad17dca490a8039c530d0302008_20220413_s3.9.5.sif ./run.sh

