Edited by Ye Tian on 4/26/2021 (tianye@jlab.org)
==============Edit and recompile EC geometry files===================
Go to the geometry directory, and edit the corresponding goemetry EC segment txt file
ec_segmented_FTBFtest --------FTBF beam test configuration (FTBF_beam_test_configuration.png)
ec_segmented_1module ---------SoLID ECAL reduced 1 module configuration  
../../geometry/ec_segmented_moved/ ---------The whole SoLID ECAL modules configuration
1)solid_PVDIS_ec_forwardangle_geometry.pl----------------adding or reducing modules 

2)solid_PVDIS_ec_forwardangle__parameters_Original.txt-------module material parameters and coordinates  

3)After modifying any *.txt file, it needs to be recompiled by 
   ./solid_PVDIS_ec_forwardangle.pl config_solid_PVDIS_ec_forwardangle.dat 

==============run GEMC with EC only configuration===================

Go to the submit directory, and run GEMC with *.sh file 
for example
./ifarm_beamtest_e6_newbank.sh
The output.root file structer is listed in solid_ec_bank.pl and solid_ec_ps_bank.pl

=============analyze output.root file==============================
Go to the analysis direcotry
root -l  'analysis_beamtest_2021_ps.C+("../submit/output.root",6000)'

=============Edit/recompile hitprocess.C ====================================
Go to your local hitprocess directory 
change the WLS attenuation factor 
cd $GEMC_VERSION
run "scons OPT=1"

