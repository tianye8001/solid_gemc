# solid_gemc

overview
--------
This repository is for [SoLID](https://hallaweb.jlab.org/12GeV/SoLID) simulation based on [GEMC](https://gemc.jlab.org).

It includes all codes of defining and running simulation, digitizing and analyzing results.

It is a part of [solid_release](https://github.com/JeffersonLab/solid_release) which has prerequisites included. 

compile and run
--------
Only support "tcsh" with NO special env variable set, which means clean .login and .cshrc

Before compile or run, set up env by
* "source set_solid" with all default value
* or "source set_solid your_JLAB_VERSION your_JLAB_ROOT your_solid_gemc_location" with your values

To compile
* cd $SoLID_GEMC/source/$GEMC_VERSION/
* scons OPT=1

To run
* cd $SoLID_GEMC/script/
* solid_gemc solid_SIDIS_He3_full.gcard
* solid_gemc solid_SIDIS_NH3_full.gcard
* solid_gemc solid_PVDIS_LD2_full.gcard
* solid_gemc solid_JPsi_LH2_full.gcard

code structure
--------
* "geometry", detector definition
* "field" field definition
* "script" example script to run simulation
* "digitization" code to digitize simulation output 
* "analysis" code to analyze results and do some studies
* "source" source code of solid_gemc which add solid specific hit process routine and load gemc as library
* "mod" some modification of original gemc code to fit solid need

development rule and how to contribute
--------
* Use "master" branch as devel version and github release as production version
* most small development will be done by "fork->modify->submit pull request" mode.
* some major collaborative development can be done with "branch->modify->submit pull request" mode as needed 

To keep the fork in sync, do this on your computer
* git clone https://github.com/[your_github_name]/solid_gemc.git
* git remote add upstream https://github.com/JeffersonLab/solid_gemc.git
* git fetch upstream
* git checkout master
* git merge upstream/master
* git push origin master
