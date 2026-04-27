# HGC simulation setup

Here is HGC simulation setup using "solid_gemc" which is the SoLID simulation program based on GEMC

## the setup

The setup gives a complete definition of the detector.

detector definition are in text files.
It include geometry and sensitivity,material,mirror,hit,bank definition.
The perl scripts is used to produce these text files.
The parameter text file has all external parameters and it can be editted by hand.

After setting up env, a perl script will call other perl scripts and use parameter file to produce all other text files by running command below
./solid_SIDIS_hgc.pl config_solid_SIDIS_hgc.dat

The hit definition, bank definitions and corresponding hit processing routine "solid_hgc" of "solid_gemc" have to match to produce meaningful result.
Any change in hit definition and bank definition, you need to modify the source code "solid_hgc" accordingly and recompile "solid_gemc" by following instruction there

## log

optics designed by Bo Yu and Zhiwen Zhao in 2018
