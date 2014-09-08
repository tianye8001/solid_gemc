#! /bin/tcsh

# CaloSim mac/RunTest.mac script/electron_BaBar.track.root

gogeant4
cd CaloSim

cp -vf CaloSim script/electron_BaBar.track.${1}.exe

CaloSim mac/${1}.mac script/electron_BaBar.track.${1}.root |& tee script/electron_BaBar.track.${1}.log

