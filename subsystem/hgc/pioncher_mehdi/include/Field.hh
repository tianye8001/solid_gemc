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

#ifndef Field_H
#define Field_H 1

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

// C++ headers
#include <sstream>
#include <fstream>
#include <vector>
#include "math.h"

using namespace std;


class Field : public G4MagneticField
{
  double table_start[3];
  double cell_size[3];
  double table_start_target[3];
  double cell_size_target[3];
  
  
public:
  Field();
  ~Field();
  
  void GetFieldValue( const  double Point[3],
		      double *Bfield ) const;
  
private:
  
  // 2D Cylindrical Maps - phi-symmetric, need only transverse and longitudinal (z) component

  vector<vector <G4double> > B2DCylT ;
  vector<vector <G4double> > B2DCylL ;

  vector< vector < vector <G4double> > > B3DCartX ;
  vector< vector < vector <G4double> > > B3DCartY ;
  vector< vector < vector <G4double> > > B3DCartZ ;
  

};

#endif
