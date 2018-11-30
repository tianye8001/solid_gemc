# solid_gemc

overview
--------
This repository is for [SoLID](https://hallaweb.jlab.org/12GeV/SoLID) simulation based on [GEMC](https://gemc.jlab.org).

It includes all codes of defining and running simulation, digitizing and analyzing results.

It is a part of [solid_release](https://github.com/JeffersonLab/solid_release) which has prerequisites included

code structure
--------
* "geometry", detector definition
* "field" field definition
* "script" example script to run simulation
* "digitization" code to digitize simulation output 
* "analysis" code to analyze results and do some studies
* "source" source code of solid_gemc which add solid specific hit process routine and load gemc as library
* "mod" some modification of original gemc code to fit solid need

devel rule and how to contribute
--------
* Use "master" branch as devel version and github release as production version
* most small development will be done by "fork->modify->submit pull request" mode.
* some major collaborative development can be done with "branch->modify->submit pull request" mode as needed 

main log
--------
Converting SoLID svn to github by Zhiwen Zhao 2018/11/30, details in [log_svn2git](https://github.com/JeffersonLab/solid_gemc/blob/master/log_svn2git)
