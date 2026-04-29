#!/bin/csh -f

source /jlab/2.5/ce/jlab.csh
setenv SoLID_GEMC /solid_gemc
setenv GEMC $SoLID_GEMC/mod/gemc/$GEMC_VERSION
setenv LD_LIBRARY_PATH ${GEMC}:${LD_LIBRARY_PATH}
setenv PATH ${SoLID_GEMC}/source/${GEMC_VERSION}:${PATH}

cd /solid_gemc/analysis/hgc_study

mkdir output

# nevt="1e1"

#cherenkov
# # foreach mom (2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 6.5 7.0 7.5)
# foreach mom (5.0)
# #     solid_gemc cherenkov_batch.gcard -BEAM_P="pi-,$mom*GeV,0*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=txt,output_pim_p$mom\_1e3.txt -N=1 -HIT_VERBOSITY=100
#
# # gemc 2.3
#     solid_gemc cherenkov_batch.gcard -BEAM_P="e-,$mom*GeV,0*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output/cherenkov/cherenkov_C4F8_e_p$mom\_$nevt.evio -N=1e3
#     evio2root -INPUTF=output/cherenkov/cherenkov_C4F8_e_p$mom\_$nevt.evio  -B="cherenkov"
#
# #gemc > 2.8
# #     solid_gemc cherenkov_batch.gcard -BEAM_P="e-,$mom*GeV,0*deg,0*deg" -BEAM_V="(0,0,-350)cm" -OUTPUT=evio,output/cherenkov/cherenkov_C4F8_e_p$mom\_1e3.evio -N=1e3 -RECORD_OPTICALPHOTONS=1
# #     evio2root -INPUTF=output/cherenkov/cherenkov_C4F8_e_p$mom\_1e3.evio  -R="flux" -B="cherenkov"
# end

foreach mom (2.5 7.5)
   foreach theta (8.0 14.5)
    solid_gemc solid_SIDIS_He3_moved_hgc_batch.gcard -BEAM_P="pi-,$mom*GeV,$theta*deg,0*deg" -SPREAD_P="0*GeV,0*deg,180*deg" -BEAM_V="(0,0,-350)cm" -RECORD_OPTICALPHOTONS=1 -OUTPUT=evio,output/output.evio -N=1e3
    evio2root -INPUTF=output/output.evio -R="flux" -B="../../geometry/hgc_moved/solid_SIDIS_hgc"
    rm -f output/output.evio
    mv output/output.root output/hgc_SIDIS_He3_pim_z350_p$mom\_theta$theta\_phi360_1e3.root
   end
end

