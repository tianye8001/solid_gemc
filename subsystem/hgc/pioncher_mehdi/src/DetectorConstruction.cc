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
// $Id: DetectorConstruction.cc, 2012-08-01 $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "CalorimeterParameterisation.hh"
#include "CalorimeterSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4GeometryManager.hh"
#include "G4SDManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Paraboloid.hh"

#include "G4NistManager.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Torus.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4PVReplica.hh"
#include "G4AssemblyVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4Polycone.hh"
#include "Field.hh"
#include "G4TransportationManager.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:AbsorberMaterial(0),TargetMaterial(0),CellMaterial(0),NeckMaterial(0),defaultMaterial(0),ConeMaterial(0),TankMaterial(0),MirrorMaterial(0),ShieldMaterial(0),ThinWindowKMaterial(0),ThinWindowMMaterial(0),
 solidWorld(0),logicWorld(0),physiWorld(0),
 solidNeck(0),logicNeck(0),physiNeck(0),
 solidCell(0),logicCell(0),physiCell(0),
 solidTarget(0),logicTarget(0),physiTarget(0),
 solidWinIn(0),logicWinIn(0),physiWinIn(0),
 solidWinOut(0),logicWinOut(0),physiWinOut(0),
 solidCalor(0),logicCalor(0),physiCalor(0),
 magField(0)
{
  // default parameter values of the calorimeter
  AbsorberThickness = 180.*mm;
  CalorSizeXY       = 300.*cm;
  WorldSizeXY       = 600.*cm;
  WorldSizeZ        = 600.*cm; 

  // materials
  DefineMaterials();
//  SetAbsorberMaterial("G4_GLASS_PLATE");
  SetAbsorberMaterial("Glass");
  SetTargetMaterial("C4F8O");
  SetCellMaterial("Kapton");
  SetNeckMaterial("Aluminum");
  SetConeMaterial("G4_GLASS_PLATE");
  SetTankMaterial("C4F8O");
  SetMirrorMaterial("G4_GLASS_PLATE");
  SetShieldMaterial("Plombe");
  SetThinWindowKMaterial("kevlar");
  SetThinWindowMMaterial("mylar");
  // create commands for interactive definition of the calorimeter
  detectorMessenger = new DetectorMessenger(this);
}

//....olooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials
 
  G4String symbol;               //a=mass of a mole;
  G4double a, z, density;        //z=mean number of protons;  
  //G4int iz, n;                 //iz=number of protons  in an isotope; 
                                 // n=number of nucleons in an isotope;
  G4NistManager* Nist_man = G4NistManager::Instance();
  G4int ncomponents, natoms;
  G4double fractionmass;

  //
  // define Elements
  //

  G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  G4Element* Pb = new G4Element("elLead"  ,symbol="Pb", z= 82., a= 207.20*g/mole);
  G4Element* W  = new G4Element("Tungsten",symbol="W" , z= 74., a= 183.84*g/mole);
  G4Element* Ar = new G4Element("Argon", symbol="Ar", z= 18., a= 39.95*g/mole);
  G4Element* F = new G4Element("Flourine", "F", z=9 , a=19.00*g/mole);

  //
  // define a material from elements.
  //
  G4Material* PbWO4 =
          new G4Material("PbWO4", density= 8.300*g/cm3, ncomponents=3);
  PbWO4->AddElement(Pb, natoms=1);
  PbWO4->AddElement(W, natoms=1);
  PbWO4->AddElement(O, natoms=4);

  //Torlon4203L
  G4Material* Torlon =
	  new G4Material("Torlon", density= 1.412*g/cm3, ncomponents=5);
  Torlon->AddElement(C, natoms=9);
  Torlon->AddElement(H, natoms=4);
  Torlon->AddElement(N, natoms=2);
  Torlon->AddElement(O, natoms=3);
  Torlon->AddElement(Ar, natoms=1);

  //Hydrogen gas
  density = 10000* 4.192263e-7*g/cm3;
  G4Material* H2 =
	  new G4Material("H2gas", density, ncomponents=1, kStateGas, 25*kelvin, 83.02*pascal);
  H2->AddElement(H, natoms=2);

  G4Material* H2O = 
  new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  // overwrite computed meanExcitationEnergy with ICRU recommended value 
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);

 
  G4Material* Al =
  new G4Material("Aluminum", z= 13., a = 26.98*g/mole, density = 2.70*g/cm3);

  G4Material* Plombe =
  new G4Material("Plombe", density = 11.34*g/cm3, ncomponents=1);
  Plombe->AddElement(Pb, natoms=1);
 //
  // define a material from elements.   case 2: mixture by fractional mass
  //
//  G4Material* Air = 
//  new G4Material("Air"  , density= 1.290*mg/cm3, ncomponents=2);
//  Air->AddElement(N, fractionmass=0.7);
 // Air->AddElement(O, fractionmass=0.3);

  //Kapton
  G4Material* Kapton =
	  new G4Material("Kapton", density= 1.42*g/cm3, ncomponents=4);
  Kapton->AddElement(H, fractionmass= 0.0273);
  Kapton->AddElement(C, fractionmass= 0.7213);
  Kapton->AddElement(N, fractionmass= 0.0765);
  Kapton->AddElement(O, fractionmass= 0.1749);
// Glass
//
  G4Material* Glass2 = Nist_man->FindOrBuildMaterial("G4_GLASS_PLATE");
  G4Material* Glass =	  new G4Material("Glass", density= 1.032*g/cm3, ncomponents=2);
  Glass->AddElement(C,fractionmass= 0.91533);
  Glass->AddElement(H,fractionmass= 0.08467);

  // C4F8O
  
  G4Material* C4F8O = new G4Material("C4F8O", density=13.47255*kg/m3, ncomponents=3, kStateGas,293.*kelvin,1.5*atmosphere); 
  C4F8O->AddElement(C, 4);
  C4F8O->AddElement(F, 8);  
  C4F8O->AddElement(O, 1);

  //mylar 
  G4Material* mylar = new G4Material("mylar",density= 1.397*g/cm3, ncomponents=3);
  mylar -> AddElement(H,0.042);
  mylar -> AddElement(C,0.625);
  mylar -> AddElement(O,0.333);

  //kevlar
  G4Material* kevlar = new G4Material("kevlar",density= 1.44*g/cm3, ncomponents=4);
  kevlar -> AddElement(H,0.04);
  kevlar -> AddElement(C,0.71);
  kevlar -> AddElement(O,0.12);
  kevlar -> AddElement(N,0.13);


// this material will kill every tracks that touch it
G4Material* Kryptonite = new G4Material("Kryptonite", density= 0.00000001*mg/cm3, ncomponents=1);
Kryptonite->AddElement(Ar, 100.*perCent);

// ------------ Generate & Add Material Properties Table ------------
//

  const G4int nEntries = 41;
  
  G4double PhotonEnergy[nEntries] = {2.04358*eV, 2.0664*eV, 2.09046*eV, 2.14023*eV, 
                                     2.16601*eV, 2.20587*eV, 2.23327*eV, 2.26137*eV, 
                                     2.31972*eV, 2.35005*eV, 2.38116*eV, 2.41313*eV, 
                                     2.44598*eV, 2.47968*eV, 2.53081*eV, 2.58354*eV, 
                                     2.6194*eV, 2.69589*eV, 2.73515*eV, 2.79685*eV, 
                                     2.86139*eV, 2.95271*eV, 3.04884*eV, 3.12665*eV, 
                                     3.2393*eV, 3.39218*eV, 3.52508*eV, 3.66893*eV,
                                     3.82396*eV, 3.99949*eV, 4.13281*eV, 4.27679*eV, 
                                     4.48244*eV, 4.65057*eV, 4.89476*eV, 5.02774*eV, 
                                     5.16816*eV, 5.31437*eV, 5.63821*eV, 5.90401*eV, 
                                     6.19921*eV};
  
  // the one to use
  G4double C4F8O_RefractiveIndex[nEntries] = {1.00205, 1.00205, 1.00205, 1.00206,
                                              1.00206, 1.00206, 1.00206, 1.00206,
                                              1.00206, 1.00206, 1.00206, 1.00207,
                                              1.00207, 1.00207, 1.00207, 1.00207,
                                              1.00207, 1.00208, 1.00208, 1.00208,
                                              1.00209, 1.00209, 1.00209, 1.0021,
                                              1.00211, 1.00211, 1.00212, 1.00213,
                                              1.00214, 1.00215, 1.00216, 1.00217,
                                              1.00219, 1.0022, 1.00222, 1.00223,
                                              1.00224, 1.00225, 1.00228, 1.00231,
                                              1.00234};  

 
 G4double Glass_RefractiveIndex[nEntries] = {1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1.};



  G4MaterialPropertiesTable* C4F8O_MPT = new G4MaterialPropertiesTable();
  C4F8O_MPT->AddProperty("RINDEX", PhotonEnergy, C4F8O_RefractiveIndex,nEntries);
  C4F8O->SetMaterialPropertiesTable(C4F8O_MPT); 

  G4MaterialPropertiesTable* Glass_MPT = new G4MaterialPropertiesTable();
  Glass_MPT->AddProperty("RINDEX", PhotonEnergy, Glass_RefractiveIndex,nEntries);
  Glass->SetMaterialPropertiesTable(Glass_MPT); 



 //Air
  G4Material* Air = Nist_man->FindOrBuildMaterial("G4_AIR");
  
 
// Vacuum

  G4Material* Vacuum = new G4Material("Vacuum", density=1.e-5*g/cm3, 1, kStateGas, STP_Temperature, 2.e-2*bar);
  Vacuum->AddMaterial(Air, 1.);
  G4double Vacuum_RefractiveIndex[nEntries] = {1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1., 1., 1., 1., 
                                               1.};

  G4MaterialPropertiesTable* Vacuum_MPT = new G4MaterialPropertiesTable();
  Vacuum_MPT->AddProperty("RINDEX", PhotonEnergy, Vacuum_RefractiveIndex, nEntries);
  Vacuum->SetMaterialPropertiesTable(Vacuum_MPT);

 
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //default materials of the World
  defaultMaterial  = Vacuum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  //     
  // World
  //
  solidWorld = new G4Box("World", WorldSizeXY, WorldSizeXY, WorldSizeZ);				//its name
                                 
            
  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   defaultMaterial,	//its material
                                   "World");		//its name
                                   
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(0., 0. ,0.), //at (0,0,0)
                                 logicWorld,		//its logical volume				 
                                 "World",		//its name
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number


   // Empty translate, rotation and vector
  G4ThreeVector V0 = G4ThreeVector(0.,0.,0.);
  G4RotationMatrix R0 = G4RotationMatrix();
  G4Transform3D T0 = G4Transform3D(R0, V0);


  // position of the target w.r.t. BaBar-Solid's origin (0,0,0) at the center of coil
  G4ThreeVector V0_tg = G4ThreeVector(0.,0.,-350.*cm);
  
  G4RotationMatrix Rm;
  G4RotationMatrix Rc;
  G4RotationMatrix* Rr = new G4RotationMatrix();
  G4Transform3D Tr; 
 // The CF4 Tank
  
  // here we make the tank=sum of two polycones: the z coord. for 
  // the radius is given w.r.t. (0,0,0); numbers are taken from Xin's
  // Geant3 simulation
  
  // this is for the BaBar setup

  G4int nmbRZ = 2 ;
  G4double zis[] = {306.0*cm, 406.0*cm}; 
  G4double rmin[] = {86.0*cm, 98*cm};
  G4double rmax[] = {265.0*cm, 265.0*cm};
  
  G4Polycone* Tank = new G4Polycone("Tank", 0.*degree, 360.*degree, nmbRZ, zis,rmin, rmax);
  
  G4LogicalVolume* Tank_log = new G4LogicalVolume(Tank, TankMaterial, "Tank", 0, 0, 0);

  // therefore place the tank at (0,0,0)
  
  G4VPhysicalVolume* Tank_phys = new G4PVPlacement(Rr, V0, Tank_log, "Tank", logicWorld, true, 0);

  // this is rot angle of WC and PMTs around the x axis
  G4double ang_xrot = 44. * degree;
  G4double image_x = 0. * cm;

//*******************************Winston Cone***********************************************************
  G4double image_y = 239.7 * cm;
  G4double image_z = 325 * cm;

  G4double rmin_w_front_cone = 14.16*cm; 
  G4double rmax_w_front_cone = 14.73*cm; 
  G4double rmin_w_end = 22.04*cm; 
  G4double rmax_w_end = 22.61*cm;
  G4double z_w_half = (19. + 0.1)*cm;

  G4ThreeVector Pos_winston_cone = G4ThreeVector(0.*cm,(image_y-sin(ang_xrot)*z_w_half), (image_z+cos(ang_xrot)*z_w_half));
  G4Cons* winston_cone = new G4Cons("winston_cone", rmin_w_front_cone, rmax_w_front_cone,rmin_w_end, rmax_w_end, z_w_half, 0.*degree, 360.*degree);
  G4LogicalVolume* winston_cone_log = new G4LogicalVolume(winston_cone, ConeMaterial,"winston_cone", 0, 0, 0);

// Winston cone Assembly: place it in the tank

  G4AssemblyVolume* winston_cone_Assembly = new G4AssemblyVolume();
  Rm = R0;
  Rm.rotateZ(0.*degree); // rotate to improve eff.

  Rc = R0;  
  Rc.rotateX(ang_xrot); 
  Rc.rotateZ(0.*degree); 
  
  G4ThreeVector Pos_Tmp_winston_cone;
//  for(G4int i = 1; i<31; i++){
  for(G4int i = 0; i<30; i++){
    Rm.rotateZ(-12.*degree);
    Rc.rotateZ(-12.*degree);
    Pos_Tmp_winston_cone = Pos_winston_cone;
    Tr = G4Transform3D(Rc, Pos_Tmp_winston_cone.transform(Rm));
    winston_cone_Assembly->AddPlacedVolume(winston_cone_log, Tr);
  } 
  winston_cone_Assembly->MakeImprint(Tank_log, T0, 0, false); 
 


//*********PMT Assembly**************


  //  Observer Assembly: place it in the tank
  G4double image_y_obs = 239.7 * cm;
  G4double image_z_obs = 325 * cm;
  G4double PMT_half_lgt = 2.54 * mm;
 G4double rmin_w_front = 10.16*cm; 
 G4double rmax_w_front = 8.19*cm; 


  G4ThreeVector Pos_Img_PMT = G4ThreeVector(image_x, image_y, image_z);

  G4Box* PMT = new G4Box("PMT", rmin_w_front, rmin_w_front, PMT_half_lgt);

  G4ThreeVector Pos_PMT = G4ThreeVector(0.*cm,(sin(ang_xrot)*PMT_half_lgt+image_y_obs), (image_z_obs-(cos(ang_xrot)*PMT_half_lgt)));
  G4LogicalVolume* PMT_log = new G4LogicalVolume(PMT, AbsorberMaterial, "PMT",0, 0, 0);

  G4AssemblyVolume* PMT_Assembly = new G4AssemblyVolume();
  Rm = R0;
  Rm.rotateZ(0.*degree); // rotate Observer to improve eff.

  Rc = R0; // do not rotate 
  Rc.rotateX(ang_xrot); // do not rotate 
  Rc.rotateZ(0.*degree); // do not rotate 
  
  G4ThreeVector Pos_Tmp_PMT;
  for(G4int i = 0; i<30; i++){
//for(G4int i = 6; i<36; i++){
    Rm.rotateZ(12.*degree);
    Rc.rotateZ(12.*degree);
    Pos_Tmp_PMT = Pos_PMT;
    Tr = G4Transform3D(Rc, Pos_Tmp_PMT.transform(Rm));
    //    Tr = G4Transform3D(Rm, Pos_Tmp_Observer.transform(Rm));
    PMT_Assembly->AddPlacedVolume(PMT_log, Tr);
  }
  PMT_Assembly->MakeImprint(Tank_log, T0, 0, false);




//************************Shield******************************************
//G4Box* Shield = new G4Box("Shield", 15*cm, 15*cm, 2*mm);
G4double Shield_half_lgt = 2. * mm;
  G4double image_y_shield = 239.7 * cm;
  G4double image_z_shield = 325 * cm;
G4Sphere* Shield = new G4Sphere("Shield",14.5*cm,20*cm,180*degree,359.99*degree,90*degree,180*degree);
G4ThreeVector Pos_Shield_img = G4ThreeVector(0.0,240.1*cm ,325.4*cm);
G4ThreeVector Pos_Shield = G4ThreeVector(0.*cm,(sin(ang_xrot)*Shield_half_lgt+image_y_shield), (image_z_shield-(cos(ang_xrot)*Shield_half_lgt)));

G4LogicalVolume* Shield_log = new G4LogicalVolume(Shield, ShieldMaterial, "Shield",0, 0, 0);

  G4AssemblyVolume* Shield_Assembly = new G4AssemblyVolume();
  Rm = R0;
  Rm.rotateZ(0.*degree); // rotate Observer to improve eff.

  Rc = R0; // do not rotate 
  Rc.rotateX(ang_xrot); // do not rotate 
  Rc.rotateZ(0.*degree); // do not rotate 
  
  G4ThreeVector Pos_Tmp_Shield;
  for(G4int i = 0; i<30; i++){
//for(G4int i = 6; i<36; i++){
    Rm.rotateZ(12.*degree);
    Rc.rotateZ(12.*degree);

    Rm.rotateZ(0.*degree);
    Rc.rotateZ(0.*degree);

    Pos_Tmp_Shield = Pos_Shield;
    Tr = G4Transform3D(Rc, Pos_Tmp_Shield.transform(Rm));
    Shield_Assembly->AddPlacedVolume(Shield_log, Tr);
  }
  Shield_Assembly->MakeImprint(Tank_log, T0, 0, false);



  //************************Thin Windows******************************************

  G4double zism[] = {305.986*cm, 305.999*cm};
  G4double zisk[] = {305.846*cm, 305.889*cm};
  G4double rminw[] = {86.0*cm, 86*cm};
  G4double rmaxw[] = {185.0*cm, 185.0*cm};
  
  G4Polycone* WindowM = new G4Polycone("WindowM", 0.*degree, 360.*degree, nmbRZ, zism,rminw, rmaxw);
  G4Polycone* WindowK = new G4Polycone("WindowK", 0.*degree, 360.*degree, nmbRZ, zisk,rminw, rmaxw);
  
  G4LogicalVolume* WindowM_log = new G4LogicalVolume(WindowM, ThinWindowMMaterial, "WindowM", 0, 0, 0);
  G4LogicalVolume* WindowK_log = new G4LogicalVolume(WindowK, ThinWindowKMaterial, "WindowK", 0, 0, 0);
 
  
  G4VPhysicalVolume* WindowM_phys = new G4PVPlacement(Rr, V0, WindowM_log, "WindowM", logicWorld, true, 0);
  G4VPhysicalVolume* WindowK_phys = new G4PVPlacement(Rr, V0, WindowK_log, "WindowK", logicWorld, true, 0);




//*******************************Mirror***********************************************************
  
  // define Z_mirror w.r.t. the origin of coordinates: 
  // ~ 21 cm before the tank's back wall 
  
  // thickness of mirror: 5mm
  // central ray will give the radius of the sphere 
  // that goes into building the mirror  

G4ThreeVector Pos_Img_Observer = G4ThreeVector(image_x, image_y, image_z);

//  G4double Z_M1 = 383.*cm;
// shift by 10 cm
    G4double Z_M1 = 388*cm;
// shift by 20 cm
 //   G4double Z_M1 = 403.*cm;
    
    G4double T_M1 = 3.*mm;

  // the polar angular range for the BaBar setup is (8.5, 15.5) deg --> from Xin
  G4ThreeVector central_ray = G4ThreeVector(0., sin(11.5*degree), cos(11.5*degree));
//  G4ThreeVector central_ray = G4ThreeVector(0., sin(12.0*degree), cos(12.0*degree));
  // this will be returned by the BuildSPMirror routine
  G4ThreeVector Pos_M1;
  G4double R;
  G4Sphere* SPM1 = BuildSPMirror(V0_tg, Pos_Img_Observer, central_ray, Z_M1, T_M1,Pos_M1, R);  
  
  // max and min polar angles in SIDIS
  G4double Angle_in = 7.5*degree;
  G4double Angle_out = 15.5*degree; 

  // z dist. between the target and front/back walls of the tank: 350 + 306 & 350 + 396
  // add 15*cm to R_in because the mirror is sticking out
  G4double Z_front = 656.*cm;
//  G4double Z_front = 676.*cm;
//  G4double Z_end = 746.*cm;

// shift by 10 cm
  G4double Z_end = 756.*cm;

// shift by 20 cm
//  G4double Z_end = 766.*cm;

  G4double R_front_in = Z_front*tan(Angle_in);
  G4double R_front_out = Z_front*tan(Angle_out);
  
  G4double R_end_in = Z_end*tan(Angle_in);
  G4double R_end_out = Z_end*tan(Angle_out);

  // make a cone to intersect a sphere
  G4Cons* CM1 = new G4Cons("CM1", R_front_in, R_front_out, R_end_in, R_end_out,
(Z_end-Z_front)/2., (90.-6.)*degree, 12.*degree); 

  G4cout << "rfin is: " << R_front_in/cm << " " << "rfout is: " << R_front_out/cm <<
" " 
         << "rein is: " << R_end_in/cm << " " << "reout is: " << R_end_out/cm << " "
         << "z_half is: " << (Z_end-Z_front)/2./cm << G4endl;

  // this is where the center of the cone should stay w.r.t. (0,0,0)
  // i.e. in the middle of the tank: (306+396)/2=351*cm

//  G4ThreeVector Pos_CM1 = G4ThreeVector(0.,0.,351.*cm);

// For a shit of 10 cm
 G4ThreeVector Pos_CM1 = G4ThreeVector(0.,0.,356.*cm);

// For a shit of 20 cm
// G4ThreeVector Pos_CM1 = G4ThreeVector(0.,0.,361.*cm);

  G4IntersectionSolid* M1 = new G4IntersectionSolid("M1", CM1, SPM1, 0,
Pos_M1-Pos_CM1);
  
  G4LogicalVolume* M1_log = new G4LogicalVolume(M1, MirrorMaterial, "Mirror_1", 0, 0, 0);
  
  G4AssemblyVolume* Mirror_Assembly = new G4AssemblyVolume();
  Rm = R0;
 for(G4int i = 0; i<30; i++){
 // for(G4int i = 6; i<36; i++){
          Rm.rotateZ(12.*degree);
          Tr = G4Transform3D(Rm, Pos_CM1);
          Mirror_Assembly->AddPlacedVolume(M1_log, Tr);
  }
  Mirror_Assembly->MakeImprint(Tank_log, T0, 0, false); 

/*
  static G4bool fieldIsInitialized = false;
  if(!fieldIsInitialized)
    {
      Field* myField = new cherField;
      G4FieldManager* fieldMgr
        = G4TransportationManager::GetTransportationManager()->GetFieldManager();
      fieldMgr->SetDetectorField(myField);
      fieldMgr->CreateChordFinder(myField);
      fieldIsInitialized = true;
    } 
*/


//******************************PMT***********************************************************
/*
  solidCalor = 0;
  logicCalor = 0;
  physiCalor = 0;

  solidCalor = new G4Box("Calorimeter",             //its name
                         CalorSizeXY, CalorSizeXY, 100.*cm);//size
                             
  logicCalor = new G4LogicalVolume(solidCalor,      //its solid
                                   defaultMaterial, //its material
                                   "Calorimeter");  //its name
                                       
  physiCalor = new G4PVPlacement(0,                 //no rotation
                                 G4ThreeVector(0.,0.,325.0*cm),      //at (0,0,0)
                                 logicCalor,        //its logical volume
                                 "Calorimeter",     //its name
                                 logicWorld,        //its mother  volume
                                 false,             //no boolean operation
                                 0);                //copy number

 

 solidPMTFrame = 0;
//  solidAbsorber = 0;
for(int i = 0; i < 30; ++i)
  {
    logicAbsorber[i] = 0;
    physiAbsorber[i] = 0;
    logicPMTFrame[i] = 0;
    physiPMTFrame[i] = 0;
  }

  solidPMTFrame = new G4Box ("PMTArray_Frame", 4.*2.54*cm, 4.*2.54*cm, 10*mm);

  G4ThreeVector ArrayCenterPosition;
for(int i = 0; i < 30; ++i) {
  std::stringstream ss;
  ss << "PMTFrame_" << i;
  G4String FrameName = ss.str();
  ss.clear();

  Rm.rotateZ(-12.*degree);
  Rc.rotateZ(-12.*degree);
  ArrayCenterPosition =  G4ThreeVector( 240.6657*sin(12.*(i+1)*pi/180.)*cm, 240.6657*cos(12.*(i+1)*pi/180.)*cm, 324.*cm);
  Tr = G4Transform3D(Rc, ArrayCenterPosition);

  logicPMTFrame[i] = new G4LogicalVolume(solidPMTFrame, AbsorberMaterial, AbsorberMaterial->GetName());
  physiPMTFrame[i] = new G4PVPlacement(Tr,
                                 logicPMTFrame[i],        //its logical volume
                                 FrameName,     //its name
                                 Tank_log,        //its mother  volume
                                 false,             //no boolean operation
                                 0);                //copy number

}

 
  solidAbsorber = new G4Box ("PMTTube", 2.54*cm, 2.54*cm, 10.*mm);

  CalorimeterParameter = new CalorimeterParameterisation(16,        //NbofPMT
                                                         4,          //NbofPMT line in array
                                                         CalorSizeXY, //Calorimeter Size
                                                         G4ThreeVector(0.*cm, 0.*cm, 0.*cm),
//                                                         G4Transform3D(Rc, Pos_PMT.transform(Rm)),
                                                         2.54,  //dimension x
                                                         2.54); //dimension y
 //                                                      G4ThreeVector(90.*cm, 0.*cm, 0.*cm), //center position     

for(int i = 0; i < 30; ++i) { 

 std::stringstream ss;
  ss << "PMTArray_" << i;
  G4String PMTName = ss.str();
  ss.clear();

  logicAbsorber[i] = new G4LogicalVolume(solidAbsorber, AbsorberMaterial, AbsorberMaterial->GetName());

  physiAbsorber[i] = new G4PVParameterised(PMTName ,
                                         logicAbsorber[i],
                                         logicPMTFrame[i],
                                         kXAxis,
                                         16,                      //NbofPMTs
                                         CalorimeterParameter,
                                         false);
}
*/

 //
  //Sensitive detectors
  //
 
 CalorimeterSD* PMTSD;
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  PMTSD = new CalorimeterSD("PMTARRAY");
//     PMTSD = new CalorimeterSD("aa");
  SDman->AddNewDetector( PMTSD );
  PMT_log->SetSensitiveDetector(PMTSD);


 /*
 CalorimeterSD* ArraySD[30];
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
   
for(int i = 0; i < 30; ++i) {
    std::stringstream ss;
//   ss << "PMTArray_" << i;
   ss << "PMTArray_" << i;
   G4String trackerChamberSDname = ss.str();
   ss.clear();
   ArraySD[i] = new CalorimeterSD(trackerChamberSDname);
   SDman->AddNewDetector( ArraySD[i] );
   logicAbsorber[i]->SetSensitiveDetector(ArraySD[i]);
//   logicPMTFrame[i]->SetSensitiveDetector(ArraySD[i]);

  }
*/

/*
  G4double image_y_obs = 239.7 * cm;
  G4double image_z_obs = 325 * cm;
  G4double PMT_half_lgt = 2.54 * cm;


 CalorimeterParameter = new CalorimeterParameterisation(480,        //NbofPMT
                                                         4,          //NbofPMT line in array
                                                         CalorSizeXY, //Calorimeter Size
//                                                         G4ThreeVector(0.*cm, 0.*cm, 0.*cm),
                                                         G4ThreeVector(0.*cm, (image_y_obs-sin(ang_xrot)*PMT_half_lgt)*cm, (image_z_obs+cos(ang_xrot)*PMT_half_lgt)*cm),
//                                                         G4Transform3D(Rc, Pos_PMT.transform(Rm)),
							 2.54,  //dimension x
						 	 2.54); //dimension y
 //							 G4ThreeVector(90.*cm, 0.*cm, 0.*cm), //center position      
                                                        
  physiAbsorber = new G4PVParameterised("HyCal" ,
                    	 		 logicAbsorber,
                    			 logicCalor,
                    			 kXAxis,
                    			 480,                      //NbofPMTs
                    			 CalorimeterParameter,
                    			 false);
*/
//*************************************Surfaces*************************************
  //
   const G4int nEntries = 41;
  
  G4double PhotonEnergy[nEntries] = {2.04358*eV, 2.0664*eV, 2.09046*eV, 2.14023*eV, 
                                     2.16601*eV, 2.20587*eV, 2.23327*eV, 2.26137*eV, 
                                     2.31972*eV, 2.35005*eV, 2.38116*eV, 2.41313*eV, 
                                     2.44598*eV, 2.47968*eV, 2.53081*eV, 2.58354*eV, 
                                     2.6194*eV, 2.69589*eV, 2.73515*eV, 2.79685*eV, 
                                     2.86139*eV, 2.95271*eV, 3.04884*eV, 3.12665*eV, 
                                     3.2393*eV, 3.39218*eV, 3.52508*eV, 3.66893*eV,
                                     3.82396*eV, 3.99949*eV, 4.13281*eV, 4.27679*eV, 
                                     4.48244*eV, 4.65057*eV, 4.89476*eV, 5.02774*eV, 
                                     5.16816*eV, 5.31437*eV, 5.63821*eV, 5.90401*eV, 
                                     6.19921*eV};



  // Mirror Surfaces     
  //
  G4MaterialPropertiesTable* Mirror_SPT = new G4MaterialPropertiesTable();

/*    G4double Mirror_Reflectivity[nEntries] = {1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1.};*/

  G4double Mirror_Reflectivity[nEntries] = {0.8678125, 0.8651562, 0.8639063, 0.8637500,
                                            0.8640625, 0.8645313, 0.8643750, 0.8656250,
                                            0.8653125, 0.8650000, 0.8648437, 0.8638281, 
                                            0.8635156, 0.8631250, 0.8621875, 0.8617188,
                                            0.8613281, 0.8610156, 0.8610938, 0.8616016,
                                            0.8623047, 0.8637500, 0.8655859, 0.8673828,
                                            0.8700586, 0.8741992, 0.8781055, 0.8825195,
                                            0.8876172, 0.8937207, 0.8981836, 0.9027441,
                                            0.9078369, 0.9102002, 0.9093164, 0.9061743,
                                            0.9004223, 0.8915210, 0.8599536, 0.8208313,
                                            0.7625024}; 
 

  G4double Mirror_Efficiency[nEntries] = {0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0.};

 
  Mirror_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Mirror_Reflectivity, nEntries);
  Mirror_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Mirror_Efficiency, nEntries);
  
  G4OpticalSurface* OpMirrorSurface = new G4OpticalSurface("OpMirrorSurface");
  OpMirrorSurface->SetType(dielectric_metal);
  OpMirrorSurface->SetFinish(polished);
  OpMirrorSurface->SetModel(unified);
  OpMirrorSurface->SetMaterialPropertiesTable(Mirror_SPT);

  G4LogicalSkinSurface* M1_Surface = new G4LogicalSkinSurface("M1_Surface", M1_log,
OpMirrorSurface);

//PMT Frame  

G4MaterialPropertiesTable* Frame_SPT = new G4MaterialPropertiesTable();


   G4double Frame_Transmittance[nEntries] = {1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1.};

 G4double Frame_Reflectivity[nEntries] = {0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0., 0., 0., 0., 
                                          0.};

/*  G4double Frame_Efficiency[nEntries] = {1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1.};*/

   G4double Frame_Efficiency[nEntries] = {0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0.};

//  Frame_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Frame_Reflectivity, nEntries);
  Frame_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Frame_Efficiency, nEntries);
//  Frame_SPT->AddProperty("TRANSMITTANCE", PhotonEnergy, Frame_Transmittance, nEntries);

  G4OpticalSurface* OpFrameSurface = new G4OpticalSurface("OpFrameSurface");
  OpFrameSurface->SetType(dielectric_metal);
  OpFrameSurface->SetFinish(polished);
  OpFrameSurface->SetModel(glisur);
  OpFrameSurface->SetMaterialPropertiesTable(Frame_SPT);

//for(int i = 0; i < 30; ++ i){
//  G4LogicalSkinSurface* Frame_Surface = new G4LogicalSkinSurface("Frame_Surface", logicPMTFrame[i], OpFrameSurface);
//}

  // winston_cone Surfaces     
  //
  G4MaterialPropertiesTable* winston_cone_SPT = new G4MaterialPropertiesTable();

/*    G4double winston_cone_Reflectivity[nEntries] = {1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1., 1., 1., 1., 1., 
                                                  1.};*/ 
  
 G4double winston_cone_Reflectivity[nEntries] = {0.8678125, 0.8651562, 0.8639063,
0.8637500,
                                                  0.8640625, 0.8645313, 0.8643750, 0.8656250,
                                                  0.8653125, 0.8650000, 0.8648437, 0.8638281, 
                                                  0.8635156, 0.8631250, 0.8621875, 0.8617188,
                                                  0.8613281, 0.8610156, 0.8610938, 0.8616016,
                                                  0.8623047, 0.8637500, 0.8655859, 0.8673828,
                                                  0.8700586, 0.8741992, 0.8781055, 0.8825195,
                                                  0.8876172, 0.8937207, 0.8981836, 0.9027441,
                                                  0.9078369, 0.9102002, 0.9093164, 0.9061743,
                                                  0.9004223, 0.8915210, 0.8599536, 0.8208313,
                                                  0.7625024};  
  
    G4double winston_cone_Efficiency[nEntries] = {0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0., 0., 0., 0., 0., 
                                                  0.};
    
  winston_cone_SPT->AddProperty("REFLECTIVITY", PhotonEnergy,winston_cone_Reflectivity, nEntries);
  winston_cone_SPT->AddProperty("EFFICIENCY", PhotonEnergy, winston_cone_Efficiency,nEntries); 
  
  G4OpticalSurface* wcMirrorSurface = new G4OpticalSurface("wcMirrorSurface");
  wcMirrorSurface->SetType(dielectric_metal);
  wcMirrorSurface->SetFinish(polished);
  wcMirrorSurface->SetModel(unified);
  wcMirrorSurface->SetMaterialPropertiesTable(winston_cone_SPT); 

  G4LogicalSkinSurface* wc_Surface = new G4LogicalSkinSurface("wc_Surface",winston_cone_log, wcMirrorSurface); 

// Observer Surface
//
  G4MaterialPropertiesTable* Observer_SPT = new G4MaterialPropertiesTable();
 
  G4double Observer_Reflectivity[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; 

 /*G4double Observer_Reflectivity[nEntries] = {0.8678125, 0.8651562, 0.8639063, 0.8637500,
                                            0.8640625, 0.8645313, 0.8643750, 0.8656250,
                                            0.8653125, 0.8650000, 0.8648437, 0.8638281, 
                                            0.8635156, 0.8631250, 0.8621875, 0.8617188,
                                            0.8613281, 0.8610156, 0.8610938, 0.8616016,
                                            0.8623047, 0.8637500, 0.8655859, 0.8673828,
                                            0.8700586, 0.8741992, 0.8781055, 0.8825195,
                                            0.8876172, 0.8937207, 0.8981836, 0.9027441,
                                            0.9078369, 0.9102002, 0.9093164, 0.9061743,
                                            0.9004223, 0.8915210, 0.8599536, 0.8208313,
                                            0.7625024}; */



 /*G4double Observer_Transmittance[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; */


/*   G4double Observer_Reflectivity[nEntries] = {1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1.};*/


/*  G4double Observer_Transmittance[nEntries] = {1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1., 1., 1., 1., 
                                            1.};*/


/*  G4double Observer_Efficiency[nEntries] = {1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1.}; */

    G4double Observer_Efficiency[nEntries] = {0.008, 0.0124, 0.0157, 0.02125, 
                                            0.0275, 0.034, 0.04, 0.048, 
                                            0.062, 0.0753, 0.09, 0.1071, 
                                            0.12144, 0.1428, 0.15, 0.16429, 
                                            0.17857, 0.1928, 0.2, 0.2125,
                                            0.225, 0.2375, 0.25, 0.2625, 
                                            0.275, 0.275, 0.275, 0.275, 
                                            0.275, 0.275, 0.2625, 0.25, 
                                            0.2375, 0.2125, 0.192859, 0.185716, 
                                            0.178573, 0.15714, 0.13572, 0.1143,
                                            0.09}; 

  Observer_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Observer_Reflectivity,nEntries);
//  Observer_SPT->AddProperty("TRANSMITTANCE", PhotonEnergy, Observer_Transmittance,nEntries);
  Observer_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Observer_Efficiency, nEntries);
  
  G4OpticalSurface* OpObserverSurface = new G4OpticalSurface("OpObserverSurface");
  OpObserverSurface->SetType(dielectric_metal);
  OpObserverSurface->SetFinish(polished);
  OpObserverSurface->SetModel(glisur);
 OpObserverSurface->SetMaterialPropertiesTable(Observer_SPT);

/*
for(int i = 0; i < 30; ++ i){
  G4LogicalSkinSurface* Observer_Surface = new G4LogicalSkinSurface("Observer_Surface", logicAbsorber[i], OpObserverSurface);
 }
*/

 G4LogicalSkinSurface* Observer_Surface = new G4LogicalSkinSurface("Observer_Surface", PMT_log, OpObserverSurface);
 

G4MaterialPropertiesTable* Tank_SPT = new G4MaterialPropertiesTable();
 
  G4double Tank_Reflectivity[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; 

/* G4double Tank_Efficiency[nEntries] = {1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1.}; */


 G4double Tank_Efficiency[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; 


  Tank_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Observer_Reflectivity,nEntries);
  Tank_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Observer_Efficiency, nEntries);
  
  G4OpticalSurface* OpTankSurface = new G4OpticalSurface("OpTankSurface");
  OpTankSurface->SetType(dielectric_metal);
  OpTankSurface->SetFinish(polished);
  OpTankSurface->SetModel(glisur);
  OpTankSurface->SetMaterialPropertiesTable(Tank_SPT);





 G4MaterialPropertiesTable* Shield_SPT = new G4MaterialPropertiesTable();
 
  G4double Shield_Reflectivity[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; 


G4double Shield_Efficiency[nEntries] = {0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0., 0., 0., 0., 
                                              0.}; 


 /*   G4double Shield_Efficiency[nEntries] = {1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1., 1., 1., 1., 1., 
                                            1.}; */
  Shield_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Shield_Reflectivity,nEntries);
  Shield_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Shield_Efficiency, nEntries);  
  G4OpticalSurface* OpShieldSurface = new G4OpticalSurface("OpShieldSurface");
  OpShieldSurface->SetType(dielectric_metal);
  OpShieldSurface->SetFinish(polished);
  OpShieldSurface->SetModel(glisur);
  OpShieldSurface->SetMaterialPropertiesTable(Shield_SPT);
  G4LogicalSkinSurface* Shield_Surface = new G4LogicalSkinSurface("Shield_Surface",Shield_log, OpObserverSurface);



//  G4LogicalSkinSurface* Tank_Surface = new G4LogicalSkinSurface("Tank_Surface",Tank_log, OpTankSurface);
                
  //                              
  // Visualization attributes
  //
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
//  logicCalor->SetVisAttributes(simpleBoxVisAtt);

/*
  // Below are vis attributes that permits someone to test / play 
  // with the interactive expansion / contraction geometry system of the
  // vis/OpenInventor driver :
 {G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  simpleBoxVisAtt->SetVisibility(true);
  delete logicCalor->GetVisAttributes();
  logicCalor->SetVisAttributes(simpleBoxVisAtt);}

 {G4VisAttributes* atb= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  logicLayer->SetVisAttributes(atb);}
  
 {G4VisAttributes* atb= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  atb->SetForceSolid(true);
  logicAbsorber->SetVisAttributes(atb);}
  
 {//Set opacity = 0.2 then transparency = 1 - 0.2 = 0.8
  G4VisAttributes* atb= new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.2));
  atb->SetForceSolid(true);
  logicGap->SetVisAttributes(atb);}
*/
 // PMT - Blue
  G4VisAttributes* PMTAttributes = new G4VisAttributes(G4Colour::Cyan());
// PMTAttributes->SetVisibility(false);
  PMTAttributes->SetVisibility(true);
  PMTAttributes->SetForceSolid(true);
PMT_log->SetVisAttributes(PMTAttributes);
/*
  for(int i = 0; i < 30; ++i){
  logicAbsorber[i]->SetVisAttributes(PMTAttributes);
  }
*/

 // Cone Yellow
  G4VisAttributes* coneAttributes = new G4VisAttributes(G4Colour::Yellow());
// coneAttributes->SetVisibility(false);
  coneAttributes->SetVisibility(true);
  coneAttributes->SetForceSolid(true);
  winston_cone_log->SetVisAttributes(coneAttributes);

 // Mirror Green
  G4VisAttributes* MirrorAttributes = new G4VisAttributes(G4Colour::Grey());
// coneAttributes->SetVisibility(false);
  MirrorAttributes->SetVisibility(true);
  MirrorAttributes->SetForceSolid(true);
  M1_log->SetVisAttributes(MirrorAttributes);

// Shield Green
  G4VisAttributes* ShieldAttributes = new G4VisAttributes(G4Colour::Green());
  ShieldAttributes->SetVisibility(false);
  ShieldAttributes->SetVisibility(true);
  ShieldAttributes->SetForceSolid(true);
  Shield_log->SetVisAttributes(ShieldAttributes);

// WindowM Red
  G4VisAttributes* WindowMAttributes = new G4VisAttributes(G4Colour::Red());
  WindowMAttributes->SetVisibility(false);
  WindowMAttributes->SetVisibility(true);
  WindowMAttributes->SetForceSolid(true);
  WindowM_log->SetVisAttributes(WindowMAttributes);
// WindowK Yellow
  G4VisAttributes* WindowKAttributes = new G4VisAttributes(G4Colour::Yellow());
  WindowKAttributes->SetVisibility(false);
  WindowKAttributes->SetVisibility(true);
  WindowKAttributes->SetForceSolid(true);
  WindowK_log->SetVisAttributes(WindowKAttributes);



/*for(int i = 0; i < 30; ++i) {
   DumpGeometricalTree(physiPMTFrame[i]);
  }*/

  //
  //always return the physical World
  //
  return physiWorld;
}



G4Sphere* DetectorConstruction::BuildSPMirror(G4ThreeVector P1, G4ThreeVector P2, 
                                                  G4ThreeVector V0, G4double Z_mirror, 
                                                  G4double T_mirror, G4ThreeVector& Position, 
                                                  G4double& R){
        
        // Calculate the incident vector w.r.t. the source (i.e. target)
        G4ThreeVector Vi = ((Z_mirror - P1.z())/V0.z())*V0;
        // Crossing point on mirror plane w.r.t. the origin of coordinates
        G4ThreeVector Pm = P1 + Vi;
        // Reflected vector: P2 w.r.t. the origin of coordinates; Vr doesn't matter
        G4ThreeVector Vr = P2 - Pm;
        
        // Calculate the unitory normal vector
        G4ThreeVector Vn = 1./Vr.mag()*Vr - 1./Vi.mag()*Vi;
        Vn *= 1./Vn.mag();
        
        // Calculate Angle
        G4double ang_cos = -Vi.dot(Vn)/Vi.mag();
        
        // Radius
        R = 2./ang_cos/(1./Vi.mag() + 1./Vr.mag());
        
        // Spherical Center w.r.t. the origin of coordinates
        Position = Pm + R*Vn;

        G4cout <<"Radius of Spherical Mirror: "<< R/cm << " " << "and pos mirror 1 is: " 
               << Position/cm  << " " << "vi_mag is: " << Vi.mag() << " " << "Z_mirror: " 
               << Z_mirror << " " << "P1z is: " << P1.z() << " " << "v0z is: " 
               << V0.z() << " ang_cos is: " << ang_cos << G4endl;
        
        
        // Define Mirror
        G4Sphere* SPMirror = new G4Sphere("SPMirror", R, R+T_mirror, 0., 360.*degree, 0.,
90.*degree);
        
        return SPMirror;
}

//....oooOO0OOooo........oooOO0OOooo.... Check Geometry....oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
  for(int isp=0;isp<depth;isp++)
  { G4cout << "  "; }
  //aVolume->SetCopyNo(1);
  G4cout <<"main=" <<aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
         << "mainlogic=" <<aVolume->GetLogicalVolume()->GetName() << " "
         <<"daughters="<< aVolume->GetLogicalVolume()->GetNoDaughters() << " "
         << "material="<< aVolume->GetLogicalVolume()->GetMaterial()->GetName() ;
//     << G4BestUnit(aVolume->GetLogicalVolume()->GetMass(true),"Mass");
  if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
  {
    G4cout << "   sensitive!! " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
                            ->GetFullPathName();
  }
  G4cout << G4endl;
  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
  {
DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) AbsorberMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTankMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) TankMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetConeMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) ConeMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMirrorMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) MirrorMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetShieldMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) ShieldMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetThinWindowKMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) ThinWindowKMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetThinWindowMMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) ThinWindowMMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) TargetMaterial = pttoMaterial;
}

void DetectorConstruction::SetCellMaterial(G4String materialChoice)
{
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) CellMaterial = pttoMaterial;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetNeckMaterial(G4String materialChoice)
{
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) NeckMaterial = pttoMaterial;
}


void DetectorConstruction::SetAbsorberThickness(G4double val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  AbsorberThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetCalorSizeXY(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  CalorSizeXY = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

void DetectorConstruction::SetMagField(G4double fieldValue)
{
  //apply a global uniform magnetic field along Z axis
  G4FieldManager* fieldMgr
   = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  if(magField) delete magField;		//delete the existing magn field

  if(fieldValue!=0.)			// create a new one if non nul
  { magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
  } else {
    magField = 0;
    fieldMgr->SetDetectorField(magField);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
