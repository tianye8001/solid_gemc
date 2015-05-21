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
// $Id: DetectorConstruction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Sphere.hh"

class G4Tubs;
class G4Box;
class G4Polycone;
class G4Cons;
class G4Sphere;
class G4AssemblyVolume;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class DetectorMessenger;
class G4VPVParameterisation;
class G4IntersectionSolid;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:
     
     void SetAbsorberMaterial (G4String);     
     void SetAbsorberThickness(G4double);     

     void SetTargetMaterial (G4String);     
   
     void SetCellMaterial (G4String);
     
     void SetNeckMaterial (G4String); 
    
     void SetConeMaterial (G4String);    
     void SetTankMaterial (G4String);   
     void SetMirrorMaterial (G4String);  
     void SetShieldMaterial (G4String);  
     void SetThinWindowKMaterial (G4String);  
     void SetThinWindowMMaterial (G4String);  

     void SetCalorSizeXY(G4double);          
     
     void SetMagField(G4double);
     
     G4VPhysicalVolume* Construct();

     void UpdateGeometry();
     void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);

  public:
  
     void PrintCalorParameters(); 
                    
     G4double GetWorldSizeZ()           {return WorldSizeZ;}; 
     G4double GetWorldSizeXY()          {return WorldSizeXY;};
     
     G4double GetCalorThickness()       {return CalorThickness;}; 
     G4double GetCalorSizeXY()          {return CalorSizeXY;};
  
     G4Material* GetAbsorberMaterial()  {return AbsorberMaterial;};
     G4double    GetAbsorberThickness() {return AbsorberThickness;};      
     
     G4Material* GetTargetMaterial()       {return TargetMaterial;};
     G4Material* GetCellMaterial()      {return CellMaterial;};
     G4Material* GetNeckMaterial()      {return NeckMaterial;};
     G4Material* GetConeMaterial()      {return ConeMaterial;};
     G4Material* GetTankMaterial()      {return TankMaterial;};
     G4Material* GetMirrorMaterial()      {return MirrorMaterial;};
     G4Material* GetShieldMaterial()      {return ShieldMaterial;};
     G4Material* GetThinWindowKMaterial()      {return ThinWindowKMaterial;};
     G4Material* GetThinWindowMMaterial()      {return ThinWindowMMaterial;};

     const G4VPhysicalVolume* GetphysiWorld() {return physiWorld;};           
     const G4VPhysicalVolume* GetAbsorber()   {return physiAbsorber[30];};
     const G4VPhysicalVolume* GetCell()        {return physiCell;};


                 
  private:
     
     G4Material*        AbsorberMaterial;
     G4double           AbsorberThickness;
     
     G4Material*        TargetMaterial;
     G4Material*        CellMaterial;
     G4Material*        NeckMaterial; 
    
     G4Material*        ConeMaterial;
     G4Material*        TankMaterial;
     G4Material*        MirrorMaterial; 
     G4Material*        ShieldMaterial; 
     G4Material*        ThinWindowKMaterial; 
     G4Material*        ThinWindowMMaterial; 

     G4double           CalorSizeXY;
     G4double           CalorThickness;
     
     G4Material*        defaultMaterial;
     G4double           WorldSizeXY;
     G4double           WorldSizeZ;
     
     G4Box*             solidWorld;    //pointer to the solid World 
     G4LogicalVolume*   logicWorld;    //pointer to the logical World
     G4VPhysicalVolume* physiWorld;    //pointer to the physical World

     G4Box*             solidNeck;
     G4LogicalVolume*   logicNeck;
     G4VPhysicalVolume* physiNeck;

     G4Polycone*        Tank;
     G4LogicalVolume*   Tank_log;
     G4VPhysicalVolume* Tank_phys;

     G4Cons*            winston_cone;
     G4LogicalVolume*   winston_cone_log;
     G4AssemblyVolume*  winston_cone_Assembly;

     G4Sphere*          Shield;
     G4LogicalVolume*   Shield_log;
     G4AssemblyVolume*  Shield_Assembly;

     G4Polycone*        WindowK;
     G4LogicalVolume*   WindowK_log;
     G4VPhysicalVolume* WindowK_phys;

     G4Polycone*        WindowM;
     G4LogicalVolume*   WindowM_log;
     G4VPhysicalVolume* WindowM_phys;


     G4Box*             PMT;
     G4LogicalVolume*   PMT_log;
     G4AssemblyVolume*  PMT_Assembly;


     G4IntersectionSolid* M1;
     G4LogicalVolume*   M1_log;
     G4AssemblyVolume*  Mirror_Assembly;


     G4Polycone*        solidCell;
     G4LogicalVolume*   logicCell;
     G4VPhysicalVolume* physiCell;

     G4Tubs*            solidTarget;
     G4LogicalVolume*   logicTarget;
     G4VPhysicalVolume* physiTarget;
     
     G4Tubs*            solidWinIn;
     G4LogicalVolume*   logicWinIn;
     G4VPhysicalVolume* physiWinIn;

     G4Tubs*            solidWinOut;
     G4LogicalVolume*   logicWinOut;
     G4VPhysicalVolume* physiWinOut;

     G4Box*             solidCalor;    //pointer to the solid Calor 
     G4LogicalVolume*   logicCalor;    //pointer to the logical Calor
     G4VPhysicalVolume* physiCalor;    //pointer to the physical Calor
       
     G4Box*             solidPMTFrame; //pointer to the solid Absorber
     G4LogicalVolume*   logicPMTFrame[30]; //pointer to the logical Absorber
     G4VPhysicalVolume* physiPMTFrame[30]; //pointer to the physical Absorber

     G4Box*             solidAbsorber; //pointer to the solid Absorber
     G4LogicalVolume*   logicAbsorber[30]; //pointer to the logical Absorber
     G4VPhysicalVolume* physiAbsorber[30]; //pointer to the physical Absorber

    
     G4VPVParameterisation* CalorimeterParameter;
     
     G4UniformMagField* magField;      //pointer to the magnetic field
     
     DetectorMessenger* detectorMessenger;  //pointer to the Messenger
     
     G4Sphere* BuildSPMirror(G4ThreeVector P1, G4ThreeVector P2, G4ThreeVector Direction, G4double Z_mirror, G4double T_mirror, G4ThreeVector& Position, G4double& Ris);

  private:
    
     void DefineMaterials();
  
};


#endif

