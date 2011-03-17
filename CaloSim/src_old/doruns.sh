#!/bin/bash

# HN=$(hostname -s)

# echo $HN

nice -n 19 bin/Linux-g++/CaloSim mac/$1.mac /scratch/charm/rmcnabb/$1_${HN}_$2A.root >& /scratch/charm/rmcnabb/$1_${HN}_$2A.log &

# sleep 2

#nice -n 19 bin/Linux-g++/CaloSim mac/$1.mac /scratch/local/rmcnabb/$1_${HN}_$2B.root >& /scratch/local/rmcnabb/$1_${HN}_$2B.log &

#sleep 2

#nice -n 19 bin/Linux-g++/CaloSim mac/$1.mac /scratch/local/rmcnabb/$1_${HN}_$2C.root >& /scratch/local/rmcnabb/$1_${HN}_$2C.log &

#sleep 2

#nice -n 19 bin/Linux-g++/CaloSim mac/$1.mac /scratch/local/rmcnabb/$1_${HN}_$2D.root >& /scratch/local/rmcnabb/$1_${HN}_$2D.log &






