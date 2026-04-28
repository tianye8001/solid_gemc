#!/bin/tcsh
# uname -a | cat > out.log
# more /etc/redhat-release | cat >> out.log
# lscpu | cat >> out.log
# lsmem | cat >> out.log
# pwd | cat >> out.log

#setenv location_soft /scigroup/cvmfs/halla/solid/soft
setenv location_soft /cvmfs/oasis.opensciencegrid.org/jlab/halla/solid/soft/

setenv location_solid_gemc $1

#run generator
# apptainer exec -B /group,/u,/w,/cache,/volatile,/lustre -B $location/solidevgen_tag1:/evgen  $location/container/jeffersonlab_solidevgen_tag1_latest.sif ./evgen.sh commit0acacfe_20230908

# run solid_gemc
apptainer exec -B /group,/u,/w,/cache,/volatile,/lustre -B $location_solid_gemc:/solid_gemc -B $location_soft/field:/field $location_soft/container/jeffersonlab_jlabce_tag2.5_digest:sha256:9b9a9ec8c793035d5bfe6651150b54ac298f5ad17dca490a8039c530d0302008_20220413_s3.9.5.sif ./run.sh

