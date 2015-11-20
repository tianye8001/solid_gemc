From the drawing and tables from engineers, we got the EC hexagon module center coordinate in lab frame and save as txt file

EC_map.C script is used to 
1. convert the EC coordinate map into GEMC parameter file
2. get the fired module and its surrounded 6 module ID with hit position hit_x hit_y in cm

the SoLID lab frame
*********************
The solenoid coil central plane and solenoid central line crosses at the origin.
electron beam and solenoid central line are along +z axis
y axis is vertical and +y pointing up relative to the ground
x axis is horizontal and +x pointing left relative to the electron beam
*********************
refer to https://hallaweb.jlab.org/wiki/index.php/Solid_Software#Coordinate_System

Imaging we are riding along the beam and facing EC from front

EC module ID consist of idx,idy,id,sector
idx and idy are given by column and row number of the module
Their values increase from bottom to top for idy, from right to left for idx
idx=0 and idy=0 module is the most bottom right module.
In the script, module center coordinate in lab frame is recorded in x[idy][idx], y[idy][idx]
id is the total id of the module, its value increase by following idx first, then idy
sector is the sector number, it matches baffle for FAEC

for FAEC, the range are
sector: 1-30 
id:1-1748
idy: 1-54 rows
idx direction: 1-46 coll. in maximum row

keyword status is 1 for module existing or 0 for not, this is to ensure PVDIS and SIDIS have same module id

= log ==========

written by Yuxiang Zhao (yxzhao@jlab.org)  2014/08

Update by Zhiwen Zhao  (zwzhao@jlab.org)  2015/11
