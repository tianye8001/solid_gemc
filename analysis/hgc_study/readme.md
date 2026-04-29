# HGC study

HGC simulation configuration is defined in ../../geometry/hgc_moved/, refer to readme file there

Here is the files and scripts to run HGC simulation and analysis results

It can work as standalone, but also test with other subsystems and full SoLID simulation

The container env setup following instruction at https://github.com/JeffersonLab/solid_release/blob/master/howto.md

## how to run simulation standalone in gui mode
solid_gemc solid_SIDIS_He3_hgc.gcard
solid_gemc solid_SIDIS_He3_moved_hgc.gcard
solid_gemc solid_SIDIS_NH3_hgc.gcard
solid_gemc solid_SIDIS_NH3_moved_hgc.gcard

## how to run simulation standalone in batch mode, convert root file and analyze results

### run simulation standalone in batch mode
solid_gemc solid_SIDIS_He3_hgc_batch.gcard -RECORD_OPTICALPHOTONS=1 -BEAM_P="pi-,5*GeV,10*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output.evio -N=1e3
solid_gemc solid_SIDIS_NH3_hgc_batch.gcard -RECORD_OPTICALPHOTONS=1 -BEAM_P="pi-,5*GeV,10*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output.evio -N=1e3
solid_gemc solid_SIDIS_He3_moved_hgc_batch.gcard -RECORD_OPTICALPHOTONS=1 -BEAM_P="pi-,5*GeV,10*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output.evio -N=1e3
solid_gemc solid_SIDIS_NH3_moved_hgc_batch.gcard -RECORD_OPTICALPHOTONS=1 -BEAM_P="pi-,5*GeV,10*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output.evio -N=1e3

(remove -RECORD_OPTICALPHOTONS=1 for jlab_ce 1.3)

### convert evio file in standalone simulation to root file
evio2root -INPUTF=output.evio -R="flux" -B="../../geometry/hgc/solid_SIDIS_hgc"
evio2root -INPUTF=output.evio -R="flux" -B="../../geometry/hgc_moved/solid_SIDIS_hgc"

(remove -R="flux" for jlab_ce 1.3)

use run option -NO_FIELD="all" to turn off all field at run time.

### how to do it all together

setenv location_solid_gemc where_your_solid_gemc

run "load.sh ${location_solid_gemc}" which will run "run.sh" inside the container

"run.sh" then run batch simulation and produce root files at dir "output"

## how to analyze results

do this outside of the container

module use /group/halla/modulefiles
module load root

alias root 'root -l --web=off'

root -b -q -l 'analysis.C+("output.root","hgc",false,false)'

analysis output will be in output_output.root


