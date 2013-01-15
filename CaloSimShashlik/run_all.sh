#! /bin/tcsh

# PVDIS
set Server = "ssh mitnig";
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_Run PVDIS_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_Run PVDIS_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_Run PVDIS_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_Run PVDIS_8mm" &

set Server = "ssh poseidon";
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_RunPi PVDIS_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_RunPi PVDIS_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_RunPi PVDIS_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh PVDIS_RunPi PVDIS_8mm" &


# SIDIS_Large
set Server = "ssh northstar";
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_Run SIDIS_Large_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_Run SIDIS_Large_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_Run SIDIS_Large_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_Run SIDIS_Large_8mm" &

xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_RunPi SIDIS_Large_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_RunPi SIDIS_Large_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_RunPi SIDIS_Large_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Large_RunPi SIDIS_Large_8mm" &

# SIDIS_Forward
set Server = "ssh apple";
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_Run SIDIS_Forward_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_Run SIDIS_Forward_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_Run SIDIS_Forward_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_Run SIDIS_Forward_8mm" &

xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_RunPi SIDIS_Forward_4mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_RunPi SIDIS_Forward_5mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_RunPi SIDIS_Forward_6mm" &
xterm -hold  -geometry 80x20 -e $Server "$PWD/run.sh SIDIS_Forward_RunPi SIDIS_Forward_8mm" &

wait;

