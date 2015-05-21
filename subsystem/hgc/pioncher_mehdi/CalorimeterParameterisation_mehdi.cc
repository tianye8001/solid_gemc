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
// Developer: Chao Peng
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
  G4RotationMatrix* rm = new G4RotationMatrix();
  G4int XIndex = BlockIndex % fNoPMTline;
  G4int YIndex = (BlockIndex - XIndex)/fNoPMTline;
  G4double Xposition=0;
  G4double Yposition=0;
  G4ThreeVector origin = G4ThreeVector(0.,0.,0.);
  G4int thetaindex=0;
  G4double pi=3.141592653589793;
  G4RotationMatrix* R0 = new G4RotationMatrix();
//  G4double thetaz=12.;
 
//  G4double delx=abs(1.-cos(thetaz*pi/180.)+sin(thetaz*pi/180.));
//  G4double dely=abs(1.-cos(thetaz*pi/180.)-sin(thetaz*pi/180.));
  G4double Rblocks=0.;
  G4double DX=0.;
  G4double DY=0.;
  G4double bltheta = 0.;
  G4int Index1=0;
  G4int Index2=0;


  Index1 = BlockIndex/16;
  Index2 = BlockIndex%16;
  thetaindex = Index1;

    if(Index2==0||Index2==3||Index2==12||Index2==15)
      {
        Rblocks = 1.5*sqrt(2.)*fsizeX;
        if(Index2 == 0) bltheta = 315.;
        if(Index2 == 3) bltheta = 45.;    
        if(Index2 == 15) bltheta = 135.; 
        if(Index2 == 12) bltheta = 225.;
        DX = Rblocks*sin((bltheta+12.*(double)(Index1+1))/180.*pi);
        DY = Rblocks*cos((bltheta+12.*(double)(Index1+1))/180.*pi);
      }
    if(Index2==1||Index2==2||Index2==4||Index2==7||Index2==8||Index2==11||Index2==13||Index2==14)
      {
        Rblocks = sqrt(0.5*fsizeX*0.5*fsizeX + 1.5*fsizeX*1.5*fsizeX);
        if(Index2 == 1) bltheta = 360. - asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 2) bltheta = asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 7) bltheta = 90. - asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 11) bltheta = 90. + asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 14) bltheta = 180. - asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 13) bltheta = 180. + asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 8) bltheta = 270. - asin(0.5*fsizeX/Rblocks)*180./pi;
        if(Index2 == 4) bltheta = 270. + asin(0.5*fsizeX/Rblocks)*180./pi;
        DX = Rblocks*sin((bltheta+12.*(double)(Index1+1))/180.*pi);
        DY = Rblocks*cos((bltheta+12.*(double)(Index1+1))/180.*pi);
      }

    if(Index2==5||Index2==6||Index2==9||Index2==10)
      {
        Rblocks = 0.5*sqrt(2.)*fsizeX;
        if(Index2 == 5) bltheta = 315.;
        if(Index2 == 6) bltheta = 45.;    
        if(Index2 == 10) bltheta = 135.; 
        if(Index2 == 9) bltheta = 225.;
        DX = Rblocks*sin((bltheta+12.*(double)(Index1+1))/180.*pi);
        DY = Rblocks*cos((bltheta+12.*(double)(Index1+1))/180.*pi);

      }

  
//     G4cout << Index1 << G4endl;
     Xposition = 239.7*sin(12.*(Index1+1)*pi/180.) + DX;
     Yposition = 239.7*cos(12.*(Index1+1)*pi/180.) + DY;

/*
     Xposition = 239.7*sin(12.*(BlockIndex+1)*pi/180.);
     //Calculate Y position
     Yposition = 239.7*cos(12.*(BlockIndex+1)*pi/180.);
*/


rm=R0;

//     rm->rotateX(-cos((12.*(thetaindex+1))/180.*pi)*44.*degree);
//     rm->rotateY(sin((12.*(thetaindex+1))/180.*pi)*44.*degree);

//     rm->rotateX(*44.*degree);
     rm->rotateY(44.*degree);

     rm->rotateZ(12.*(thetaindex+1)*degree);

     origin= G4ThreeVector(Xposition*cm, Yposition*cm, 0.*cm); 
     physVol->SetTranslation(origin);
     physVol->SetRotation(rm);


/*
if (BlockIndex <=15){
     rm->rotateX(-cos((12.*(BlockIndex+1))/180.*3.14159265)*44.*degree);
     rm->rotateY(sin((12.*(BlockIndex+1))/180.*3.14159265)*44.*degree);
     rm->rotateZ(-12.*(BlockIndex+1)*degree);

     origin= G4ThreeVector(Xposition*cm, Yposition*cm, 0.*cm); 
     physVol->SetTranslation(origin);
     physVol->SetRotation(rm);
}

if (BlockIndex >15){
          rm->rotateX(-cos((12.*(BlockIndex+1))/180.*3.14159265)*44.*degree);
     rm->rotateY(sin((12.*(BlockIndex+1))/180.*3.14159265)*44.*degree);


     rm->rotateZ(12.*(BlockIndex+1)*degree);

     origin= G4ThreeVector(Xposition*cm, Yposition*cm, 0.*cm); 
     physVol->SetTranslation(origin);
     physVol->SetRotation(rm);
//
}
*/

/*
if (thetaindex >14){
 //    rm->rotateX(-cos((12.*(thetaindex+1))/180.*pi)*44.*degree);
 //    rm->rotateY(sin((12.*(thetaindex+1))/180.*pi)*44.*degree);
     rm->rotateZ(12.*(thetaindex+1)*degree);

     origin= G4ThreeVector(Xposition*cm, Yposition*cm, 0.*cm); 
     physVol->SetTranslation(origin);
     physVol->SetRotation(rm);

//
}
*/

/*
if (thetaindex == 1){
theta =-44*deg;}
else if (thetaindex == 8){theta =20*deg;}
else if (thetaindex == 15){theta =20*deg;}
else if (thetaindex == 22){theta =20*deg;}


rm->rotateX(theta);
*/

//     rm->rotateY(45.*degree);
//     physVol->SetRotation(0);
     
 // }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void CalorimeterParameterisation::ComputeDimensions
(G4Box& CalBlock, const G4int copyNo, const G4VPhysicalVolume*) const
{
  //
  //For further improvement
  //
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
