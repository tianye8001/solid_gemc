//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
 
#include "Field.hh"
 
Field::Field()
{

  // this is to read the SoLID map

  int TNPOINTS, LNPOINTS;         ///< Number of cells in Transverse, Longitudinal dimensions
  double tlimits[2], llimits[2];  ///< Boundaries in  Transverse, Longitudinal dimensions

  TNPOINTS = 501;
//  TNPOINTS = 401;
  LNPOINTS = 1001;
  
  tlimits[0] = 0.*cm;
  tlimits[1] = 500.*cm;
  llimits[0] = -500.*cm;
//  tlimits[1] = 400.*cm;
//  llimits[0] = -400.*cm;

  llimits[1] = 600.*cm; 

  table_start[0] = tlimits[0];
  table_start[1] = llimits[0];
  cell_size[0]   = (tlimits[1] - tlimits[0])/( TNPOINTS - 1);
  cell_size[1]   = (llimits[1] - llimits[0])/( LNPOINTS - 1);
  
  cout << "how about here???:, SoLID " << TNPOINTS << " " << LNPOINTS << " " 
       << table_start[0] << " " << cell_size[0] << " " << cell_size[1] << endl;

  // end SoLID

  // this is to read NH3 map

  int XNPOINTS, YNPOINTS, ZNPOINTS;          ///< Number of cells in X, Y, Z dimensions (SoLID system)
  double xlimits[2], ylimits[2], zlimits[2]; ///< Boundaries in  X, Y, Z dimensions

  XNPOINTS = 201;
  YNPOINTS = 201;
  ZNPOINTS = 251;

  xlimits[0] = -100.*cm;
  xlimits[1] = 100.*cm;

  ylimits[0] = -100.*cm;
  ylimits[1] = 100.*cm; 

  zlimits[0] = -400.*cm; // limits here: -50 to 200 cm with origin in center of target
  zlimits[1] = -150.*cm; // so this would make -50-350 = -400 to 200-350 = -150 w.r.t. center of SoLID coil

  table_start_target[0] = xlimits[0];
  table_start_target[1] = ylimits[0];
  table_start_target[2] = zlimits[0];

  cell_size_target[0]   = (xlimits[1] - xlimits[0])/( XNPOINTS - 1);
  cell_size_target[1]   = (ylimits[1] - ylimits[0])/( YNPOINTS - 1);
  cell_size_target[2]   = (zlimits[1] - zlimits[0])/( ZNPOINTS - 1);
  
  cout << "how about here???:, TARGET " << XNPOINTS << " " << YNPOINTS << " " 
       << table_start_target[0] << " " << cell_size_target[0] << " " 
       << cell_size_target[1] << endl;  

  // end NH3 target
  
  // ***********************

  // this is SoLID map in phi symetric (around z) cylindrical coord: R,z,Br,Bz
//  const char * filename = "solenoid_BaBar.dat";
  const char * filename = "solenoid_CLEOv8.dat";
  ifstream IN(filename);
  if(!IN)
    {
      cout << " File SoLID could not be opened. Exiting." << endl;
      exit(0);
    }
  
  cout << "file name for SoLID is:::::::: " << filename << endl; 
  
  // this is NH3 map x,y,z coord. in SoLID ref. system; map from Kalyan and Jixie
  const char * filename_target = "solid_targetfield_xyz_short.dat";
  ifstream IN_TARGET(filename_target);
  if(!IN_TARGET)
    {
      cout << " File target could not be opened. Exiting." << endl;
      exit(0);
    }
  
  cout << "file name for target is:::::::: " << filename_target << endl; 
  

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Setting up storage space for tables for SoLID map
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  B2DCylT.resize( TNPOINTS );
  B2DCylL.resize( TNPOINTS );
  
  for(int it=0; it<TNPOINTS; it++)
    {
      B2DCylT[it].resize(LNPOINTS);
      B2DCylL[it].resize(LNPOINTS);
    }
  
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Setting up storage space for tables for target map
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  B3DCartX.resize( XNPOINTS );
  B3DCartY.resize( YNPOINTS );
  B3DCartZ.resize( ZNPOINTS );
  
  for(int ix = 0; ix < XNPOINTS; ix++)
    {
      
      B3DCartX[ix].resize(YNPOINTS);
      B3DCartY[ix].resize(YNPOINTS);
      B3DCartZ[ix].resize(YNPOINTS);
      
      for(int iy = 0; iy < YNPOINTS; iy++){
	
	B3DCartX[ix][iy].resize(ZNPOINTS);
	B3DCartY[ix][iy].resize(ZNPOINTS);
	B3DCartZ[ix][iy].resize(ZNPOINTS);
	
      }
    }

  // now we have empty vectors of the size that's expected by 
  // the SoLID map: B2DCylT[R][z], B2DCylL[R][z]
  // and by the target map: B3DCartX[x][y][z] etc.

  // %%%%%%%%%%%%%
  // Filling table for SoLID
  // %%%%%%%%%%%%%
  double TC, LC;  // coordinates as read from the SoLID map
  double BT, BL;  // transverse and longitudinal magnetic field as read from the SoLID map
  int IT, IL;  	  // indexes of the vector SoLID map
  
  for(int it=0; it<TNPOINTS; it++)
    {
      for(int il=0; il<LNPOINTS; il++)
	{
	  IN >> TC >> LC >> BT >> BL;
	  TC *= cm;
	  LC *= cm;

	  IT = (int) floor( ( TC/cm - table_start[0]/cm + 
				       cell_size[0]/cm/2 ) / ( cell_size[0]/cm ) ) ;
	  IL = (int) floor( ( LC/cm - table_start[1]/cm + 
				       cell_size[1]/cm/2 ) / ( cell_size[1]/cm ) ) ;
	  // don't forget *gauss	  
	  B2DCylT[IT][IL] = BT*gauss;
	  B2DCylL[IT][IL] = BL*gauss;
	  
	}
    }
  IN.close();
  cout << " done!" << endl;
 
  // end filling table with the SoLID map

  // %%%%%%%%%%%%%
  // Filling table for NH3 target
  // %%%%%%%%%%%%%
  double XC, YC, ZC;  // coordinates as read from the NH3 map
  double BX, BY, BZ;  // x,y,z magnetic fields as read from the NH3 map
  int IX, IY, IZ;     // indexes of the vector NH3 map
  
  for(int ix = 0; ix < XNPOINTS; ix++)
    {
      for(int iy = 0; iy < YNPOINTS; iy++)
	{
	  for(int iz = 0; iz < ZNPOINTS; iz++){
	    
	    IN_TARGET >> XC >> YC >> ZC >> BX >> BY >> BZ;

	    XC *= cm;
	    YC *= cm;
	    ZC = (ZC - 350.)* cm;
	    
	    IX = (int) floor( ( XC/cm - table_start_target[0]/cm + 
				cell_size_target[0]/cm/2 ) / ( cell_size_target[0]/cm ) ) ;
	    IY = (int) floor( ( YC/cm - table_start_target[1]/cm + 
				cell_size_target[1]/cm/2 ) / ( cell_size_target[1]/cm ) ) ;
	    IZ = (int) floor( ( ZC/cm - table_start_target[2]/cm + 
				cell_size_target[2]/cm/2 ) / ( cell_size_target[2]/cm ) ) ;

	    // don't forget *tesla as the units are for the target map	  
	    B3DCartX[IX][IY][IZ] = BX*tesla;
	    B3DCartY[IX][IY][IZ] = BY*tesla;
	    B3DCartZ[IX][IY][IZ] = BZ*tesla;

	    /*	    cout << "coord. from targte file: " << XC/cm << " " 
		 << YC/cm << " " << ZC/cm << endl;
	    cout << IX << " " << IY << " " << IZ << endl;

	    cout << "the field at the target as dumped in vectors: " 
		 << B3DCartX[IX][IY][IZ]/tesla << " " 
		 << B3DCartY[IX][IY][IZ]/tesla << "  " 
		 << B3DCartZ[IX][IY][IZ]/tesla << endl;

	    cout << "the field at the target as read from the file: " 
	    << BX << " " << BY << " " << BZ << endl;  */

	  }
	}
    }

  IN_TARGET.close();
  cout << " done with the target map!" << endl;
  
  // end filling table with the target map

}

Field::~Field()
{;}

void Field::GetFieldValue(const double Point[3],double *Bfield) const
{
  
  vector<double> Field[3];
  
  Bfield[0] = Bfield[1] = Bfield[2] = 0*gauss;
  
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // phi symmetric field in cylindrical coordinates
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  if(B2DCylT.size() && B2DCylL.size() && 
     B3DCartX.size() && B3DCartY.size() && B3DCartZ.size())
    
    {
      double psfield[3] = {0,0,0};
      unsigned int IT, IL;
      unsigned int IX, IY, IZ;
      
      double LC;      // longitudinal coordinate of the track in the global coordinate system
      double TC, phi; // transverse and phy polar 2D coordinates: the map is phi-symmetric. phi is angle in respect to x
      double XC, YC, ZC; // carthesian coordinates of particle

      // for SoLID map

      TC              = sqrt(Point[0]*Point[0] + Point[1]*Point[1]);
      G4ThreeVector vpos(Point[0], Point[1], Point[2]);
      phi = vpos.phi();
      LC  = Point[2];

      IT = (unsigned int) floor( ( TC - table_start[0]/mm ) / (cell_size[0]/mm) ) ;
      IL = (unsigned int) floor( ( LC - table_start[1]/mm ) / (cell_size[1]/mm) ) ;
      
      if( fabs( table_start[0]/mm + IT*cell_size[0]/mm - TC) > 
	  fabs( table_start[0]/mm + (IT+1)*cell_size[0]/mm - TC)  ) IT++;
      if( fabs( table_start[1]/mm + IL*cell_size[1]/mm - LC) > 
	  fabs( table_start[1]/mm + (IL+1)*cell_size[1]/mm - LC)  ) IL++;
      
      // end SoLID map
      
      // for target map

      /*      cout << "what are the particle coordinates: " << Point[0]/cm << " " << Point[1]/cm 
	      << " " << Point[2]/cm << endl;  */

      if (Point[2]/cm <= -150. && Point[2]/cm >= -400.){

      XC = Point[0];
      YC = Point[1]; 
      ZC = Point[2];
      
      IX = (unsigned int) floor( ( XC - table_start_target[0]/mm ) / (cell_size_target[0]/mm) ) ;
      IY = (unsigned int) floor( ( YC - table_start_target[1]/mm ) / (cell_size_target[1]/mm) ) ;
      IZ = (unsigned int) floor( ( ZC - table_start_target[2]/mm ) / (cell_size_target[2]/mm) ) ;
      
      if( fabs( table_start_target[0]/mm + IX*cell_size_target[0]/mm - XC) > 
	  fabs( table_start_target[0]/mm + (IX+1)*cell_size_target[0]/mm - XC)  ) IX++;

      if( fabs( table_start_target[1]/mm + IY*cell_size_target[1]/mm - YC) > 
	  fabs( table_start_target[1]/mm + (IY+1)*cell_size_target[1]/mm - YC)  ) IY++;
      
      if( fabs( table_start_target[2]/mm + IZ*cell_size_target[2]/mm - ZC) > 
	  fabs( table_start_target[2]/mm + (IZ+1)*cell_size_target[2]/mm - ZC)  ) IZ++;

      }

      // end target map
      
      // vector sizes are checked on both T and L components
      // (even if only one is enough)

      if(Point[2]/cm <= -150. && Point[2]/cm >= -400.){
	
	if(IX < B3DCartX.size() && IX < B3DCartY.size() && IX < B3DCartZ.size())
	  if(IY < B3DCartX[IX].size() && IY < B3DCartY[IX].size() && IY < B3DCartZ[IX].size()) 
	    if(IZ < B3DCartX[IX][IY].size() && IZ < B3DCartY[IX][IY].size() && IZ < B3DCartZ[IX][IY].size())
	      if(IT < B2DCylT.size() && IT < B2DCylL.size())
		if(IL < B2DCylT[IT].size() && IL < B2DCylL[IT].size()  )
		  {
/////////////////// TARGET FIELD ADDITION ///////////////////////////
		    /*		    psfield[0] = B2DCylT[IT][IL] * cos(phi) + B3DCartX[IX][IY][IZ];
		    psfield[1] = B2DCylT[IT][IL] * sin(phi) + B3DCartY[IX][IY][IZ];
		    psfield[2] = B2DCylL[IT][IL] + B3DCartZ[IX][IY][IZ]; */
/////////////////////////////////////////////////////////////////////
		    psfield[0] = B2DCylT[IT][IL] * cos(phi);
		      psfield[1] = B2DCylT[IT][IL] * sin(phi);
		      psfield[2] = B2DCylL[IT][IL]; 
		    
		    /*		    cout << "here we start sanity checks in the if z=(-400,-150)" << endl;
		    
		    cout << " x =: " << Point[0]/cm << " " << "y =: " << Point[1]/cm 
			 << " " << "z =: " << Point[2]/cm << endl;
		    cout << "Bx total =: " << psfield[0]/gauss << " " 
			 << "By total =: " << psfield[1]/gauss << " " 
			 << "Bz total =: " <<  psfield[2]/gauss << endl;
		    cout << "Bx SoLID =: " << cos(phi)*B2DCylT[IT][IL]/gauss << " " 
			 << "By SoLID =: " << sin(phi)*B2DCylT[IT][IL]/gauss << " " 
			 << "Bz SoLID =: " << B2DCylL[IT][IL]/gauss << endl;
		    cout << "Bx target =: " << B3DCartX[IX][IY][IZ]/gauss << " " 
			 << "By target =: " << B3DCartY[IX][IY][IZ]/gauss << " " 
			 << "Bz target =: " << B3DCartZ[IX][IY][IZ]/gauss << endl;  */

		  }
      }
      
      if(Point[2]/cm > -150.){
	
	if(IT < B2DCylT.size() && IT < B2DCylL.size())
	  if(IL < B2DCylT[IT].size() && IL < B2DCylL[IT].size()  )
	    {
	      psfield[0] = B2DCylT[IT][IL] * cos(phi);
	      psfield[1] = B2DCylT[IT][IL] * sin(phi);
	      psfield[2] = B2DCylL[IT][IL];
	      
	    }      
      }
      for(int i=0; i<3; i++) Field[i].push_back(psfield[i]);
      
    }
  
  // %%%%%%%%%%%%%%%%%%
  // Summing the Fields
  // %%%%%%%%%%%%%%%%%%
  
  for(unsigned int i=0; i<Field[0].size(); i++)
    for(int j=0; j<3; j++)
      Bfield[j] +=  Field[j][i];
  //      Bfield[j] +=  Field[j][i] * 0.;
  
  //  if(Point[2]/cm < 400. && Point[2]/cm > 300.){
  
  /*  cout << " at x, y, z (cm) the Bfield (gauss) is:  " << Point[0]/cm << " " 
       << Point[1]/cm << " " << Point[2]/cm << " " << Bfield[0]/gauss  << " " 
       << Bfield[1]/gauss << " " << Bfield[2]/gauss << endl; */
  //  } 
}

