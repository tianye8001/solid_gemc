#! /bin/tcsh

# CaloSim mac/RunTest.mac script/electron_BaBar.track.root

gogeant4
cd CaloSimShashlik


set workdir = "script/LowEBgd_Shashlyk/run${1}";

mkdir -p $workdir
cp -vf include/Config.h $workdir/Config.h
cp -vf CaloSimShashlik $workdir/CaloSimShashlik.exe
cp -vf  mac/LowEBgd.mac $workdir/LowEBgd.mac.orig
rsync -avL  CaloSim* GNUmakefile include mac src  $workdir/source/

cd $workdir/
echo "/random/setSeeds ${1} ${1}" > LowEBgd.mac
cat LowEBgd.mac.orig >> LowEBgd.mac
pwd

echo start at `date` > out.log
nice nice CaloSimShashlik.exe LowEBgd.mac |& tee -a out.log
echo end at `date` >> out.log

pwd
ls -l


