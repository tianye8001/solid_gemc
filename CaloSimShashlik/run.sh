#! /bin/tcsh

# CaloSim mac/RunTest.mac $dest_prefix.root

set dest_prefix = "script/PVDIS_Lead2X0PbBlock";
#set dest_prefix = "script/PVDIS_Lead3HalfX0Pb";
#set dest_prefix = "script/PVDIS_Lead3X0Pb";
# set dest_prefix = "script/BackendScint";

gogeant4
cd CaloSimShashlik

#cp -vf exe/${2}/Config.h $dest_prefix.${2}.${1}.Config.h
#cp -vf exe/${2}/CaloSimShashlik $dest_prefix.${2}.${1}.exe

cp -vf include/Config.h $dest_prefix.${2}.${1}.Config.h
cp -vf CaloSimShashlik $dest_prefix.${2}.${1}.exe

cp -vf mac/${1}.mac $dest_prefix.${2}.${1}.mac

date |& tee $dest_prefix.${2}.${1}.log;
nice nice $dest_prefix.${2}.${1}.exe $dest_prefix.${2}.${1}.mac $dest_prefix.${2}.${1}.root \
|& tee -a $dest_prefix.${2}.${1}.log
date  |& tee -a $dest_prefix.${2}.${1}.log;

ls -lh $dest_prefix.${2}.${1}*;
date;

