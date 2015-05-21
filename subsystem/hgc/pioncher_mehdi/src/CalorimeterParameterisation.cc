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
//
// $Id: CalorimeterParameterisation.cc,2012-08-01 $
// GEANT4 tag $Name: geant-4-9-4-patch-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CalorimeterParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterParameterisation::CalorimeterParameterisation(  
        G4int    NoPMT,
        G4int    NoPMTline,
        G4double widthCalor,
        G4ThreeVector CenterPos, 
        G4double sizeX,
        G4double sizeY) 
//        G4ThreeVector CenterPos,          //  center of the first 


{
   fNoPMT =  NoPMT; 
   fNoPMTline =  NoPMTline; 
   fspacingXY = widthCalor;
   fCenterPos = CenterPos;
   fsizeX  =  sizeX;
   fsizeY  =  sizeY;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterParameterisation::~CalorimeterParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  G4int BlockIndex = copyNo;
//  G4cout <<"copynumb="<<BlockIndex<<G4endl;
  G4RotationMatrix* rm = new G4RotationMatrix();
  G4int XIndex = BlockIndex % fNoPMTline;
  G4int YIndex = (BlockIndex - XIndex)/fNoPMTline;
  G4double Xposition=0;
  G4double Yposition=0;
  G4ThreeVector origin = G4ThreeVector(0.,0.,0.);

  Xposition = ((double)XIndex - 1.5)*2.*fsizeX;
  Yposition = (1.5 - (double)YIndex)*2.*fsizeY;
  origin= G4ThreeVector(Xposition*cm, Yposition*cm, 0.*cm);
  physVol->SetTranslation(origin);

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
