********************************
*  SIDIS Cross Section Model   *
*  -- Zhihong Ye, 06/10/2014   *
********************************

Note:
1, This model is extracted fro Xin Qian's SIDIS generator "collider.C" 
   which is included as a reference.
2, The XS model is coded in "SIDIS.h". 
  1) A generator is given in "GetSIDIS.C" 
  2) A simpler example of using the model is given in "example.C"
3, LHAPDF is needed to be installed. Unpar "lhapdf.5.8.8.tar.gz", 
   and follow the instruction to install it. Specify the path in "SIDIS.h" or
define ${LHAPDF}=/your_path/
4, The output files include both the ROOT format files and LUND format files,
   where, four root files will generated:
    *_1_0.root, Q2=<10, pt<=1 
    *_2_0.root, Q2=<10, pt>1
    *_3_0.root, Q2>10,  pt<=1.
    *_4_0.root, Q2>10,  pt>1.
    For SoLID config, chain the first two root files.
    The LUND format file save all events in one files.
5, A older version of the model wrotten in FORTRAN is also given in "sidis_fortran/", as a reference.
6, I held no responsiability to this code but you are welcome to discuss questions with me :->
