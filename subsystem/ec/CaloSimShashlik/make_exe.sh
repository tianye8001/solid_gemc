#! /bin/tcsh -f

# CaloSim mac/RunTest.mac $dest_prefix.root

set dest_prefix = "exe/${1}/";

make -j4

mkdir -vp $dest_prefix
rsync -avL include/Config.h $dest_prefix
rsync -avL CaloSimShashlik $dest_prefix

