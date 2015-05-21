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
// $Id: cherDetectorConstruction.cc,v 1.17 2008/07/17 00:32:34 gum Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


// THIS IS THE CDF SETUP

#include "cherDetectorConstruction.hh"

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

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4NistManager.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
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
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "cherField.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherDetectorConstruction::cherDetectorConstruction()
{
  expHall_x = expHall_y = expHall_z = 10*m;
  tank_x    = tank_y    = tank_z    = 5*m;
  bubble_x  = bubble_y  = bubble_z  = 0.5*m;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cherDetectorConstruction::~cherDetectorConstruction(){

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* cherDetectorConstruction::Construct()
{

//	------------- Materials -------------

  G4double a, z, density;
  G4int nelements;
  G4NistManager* Nist_man = G4NistManager::Instance();
  
  // Elements
//   G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.010*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6 , a=12.01*g/mole);
//   G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* F = new G4Element("Flourine", "F", z=9 , a=19.00*g/mole);


  // Air
  // 
  G4Material* Air = Nist_man->FindOrBuildMaterial("G4_AIR");
  
  // Vacuum
  //
  G4Material* Vacuum = new G4Material("Vacuum", density=1.e-5*g/cm3, 1, kStateGas, STP_Temperature, 2.e-2*bar);
  Vacuum->AddMaterial(Air, 1.);

  // C4F8O

  G4double density_c4f8o = 13.47255*kg/m3; // 
  G4double temp_c4f8o = 293.*kelvin; // at 20 C
  G4double pressure_c4f8o = 1.5*atmosphere;
  
  G4Material* C4F8O = new G4Material("C4F8O", density_c4f8o, 3, kStateGas, temp_c4f8o, pressure_c4f8o); 
  C4F8O->AddElement(C, 4);
  C4F8O->AddElement(F, 8);  
  C4F8O->AddElement(O, 1);

// Glass
//
  G4Material* Glass = Nist_man->FindOrBuildMaterial("G4_GLASS_PLATE");
  
//
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

  /*  G4double C4F8O_abs_length[nEntries] = {87.7642*m, 87.7642*m, 87.7642*m, 87.7642*m, 
					 87.7642*m, 87.7642*m, 87.7642*m, 87.7642*m, 
					 87.7642*m, 87.7642*m, 87.7642*m, 87.7642*m, 
					 87.7642*m, 87.7642*m, 87.616*m, 90.6032*m, 
					 93.7711*m, 102.171*m, 106.728*m, 113.497*m, 
					 119.095*m, 123.247*m, 122.872*m, 119.913*m, 
					 113.597*m, 104.84*m, 98.9037*m, 94.5673*m, 
					 91.9657*m, 90.7634*m, 90.408*m, 89.8311*m, 
					 87.4725*m, 83.3764*m, 73.8737*m, 67.4882*m, 
					 60.427*m, 53.2042*m, 39.2524*m, 30.5066*m, 
					 23.3447*m}; */
  
  
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

  // the one for error estimation: 20% lower (n-1)*10^6
  /*  G4double C4F8O_RefractiveIndex[nEntries] = {1.00164, 1.00164, 1.00164, 1.00164,
					      1.00164, 1.00165, 1.00165, 1.00165,
					      1.00165, 1.00165, 1.00165, 1.00165,
					      1.00165, 1.00165, 1.00166, 1.00166,
					      1.00166, 1.00166, 1.00166, 1.00167,
					      1.00167, 1.00167, 1.00168, 1.00168,
					      1.00168, 1.00169, 1.0017, 1.0017,
					      1.00171, 1.00172, 1.00173, 1.00174,
					      1.00175, 1.00176, 1.00178, 1.00178,
					      1.00179, 1.0018, 1.00183, 1.00185,
					      1.00187};  */

  // the one for error estimation: p0 fit to btev measurm.
  /*  G4double C4F8O_RefractiveIndex[nEntries] = {1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068, 1.00207068, 1.00207068, 1.00207068,
					      1.00207068};  */

  // the one for error estimation: 50% lower (n-1)*10^6 too much
  /*  G4double C4F8O_RefractiveIndex[nEntries] = {1.00103, 1.00103, 1.00103, 1.00103, 1.00103,
					      1.00103, 1.00103, 1.00103, 1.00103,
					      1.00103, 1.00103, 1.00103, 1.00103,
					      1.00103, 1.00104, 1.00104, 1.00104, 
					      1.00104, 1.00104, 1.00104, 1.00104,
					      1.00105, 1.00105, 1.00105, 1.00105,
					      1.00106, 1.00106, 1.00107, 1.00107,
					      1.00108, 1.00108, 1.00109, 1.00109,
					      1.0011, 1.00111, 1.00111, 1.00112,
					      1.00113, 1.00114, 1.00116, 1.00117}; */


  G4MaterialPropertiesTable* C4F8O_MPT = new G4MaterialPropertiesTable();
  C4F8O_MPT->AddProperty("RINDEX", PhotonEnergy, C4F8O_RefractiveIndex,nEntries);
  //  C4F8O_MPT->AddProperty("ABSLENGTH", PhotonEnergy, C4F8O_abs_length, nEntries);  
  C4F8O->SetMaterialPropertiesTable(C4F8O_MPT); 

// Vacuum
//
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


//	------------- Volumes --------------
//
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
  
// The experimental Hall

  G4Tubs* expHall_box = new G4Tubs("World", 0.*cm, 300.*cm, 500*cm, 0.*degree, 360.*degree);
  
  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,Vacuum,"World",0,0,0);

  Rr->rotateX(0.*degree);
  
  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,V0,expHall_log,"World",0,false,0);
  
  // The CF4 Tank
  
  // here we make the tank=sum of two polycones: the z coord. for 
  // the radius is given w.r.t. (0,0,0); numbers are taken from Xin's
  // Geant3 simulation
  
  // this is for the BaBar setup

  G4int nmbRZ = 2 ;
  
  // this is for the BaBar setup
  // polycone

  //  G4double zis[] = {306.0*cm, 376.0*cm};
  G4double zis[] = {306.0*cm, 396.0*cm}; // made it 20 cm longer
  //  G4double rmin[] = {96.0*cm, 104.0*cm}; 
  G4double rmin[] = {96.0*cm, 106.3*cm}; 
  G4double rmax[] = {265.0*cm, 265.0*cm};
  
  G4Polycone* Tank = new G4Polycone("Tank", 0.*degree, 360.*degree, nmbRZ, zis, rmin, rmax);
  
  G4LogicalVolume* Tank_log = new G4LogicalVolume(Tank, C4F8O, "Tank", 0, 0, 0);

  // therefore place the tank at (0,0,0)
  
  G4VPhysicalVolume* Tank_phys
    = new G4PVPlacement(Rr, V0, Tank_log, "Tank", expHall_log, false, 0);

  // this is rot angle of WC and PMTs around the x axis
  G4double ang_xrot = 44. * degree;

  G4double image_x = 0. * cm;
  G4double image_y = 230. * cm;
  G4double image_z = 315. * cm;

  G4double PMT_half_lgt = 2.54 * cm;

  // winston cone half length + 1 mm tolerance: this works for 6 inch
  // this is for 6"
  G4double z_w_half = (15. + 0.1)*cm;
  //  G4double z_w_half = (16.5 + 0.1)*cm;

  // this is for 6" i.e. 3 by 3 PMTs of 2" each
  // in fact H8500C-03 has 4.9 cm photocathode coverage: 
  // WC thickness from amuneal is ~ 0.57 cm; 
  G4double rmin_w_front = 7.62*cm; 
  G4double rmax_w_front = 8.19*cm; 
  G4double rmin_w_end = 19.04*cm; 
  G4double rmax_w_end = 19.61*cm; 

  G4ThreeVector Pos_Img_Observer = G4ThreeVector(image_x, image_y, image_z);

  G4Box* Observer = new G4Box("Observer", rmin_w_front, rmin_w_front, PMT_half_lgt);

  G4ThreeVector Pos_Observer = G4ThreeVector(0.*cm, (sin(ang_xrot)*PMT_half_lgt+image_y), 
					     (image_z-(cos(ang_xrot)*PMT_half_lgt)));

  G4ThreeVector Pos_winston_cone = G4ThreeVector(0.*cm, (image_y-sin(ang_xrot)*z_w_half), 
  						 (image_z+cos(ang_xrot)*z_w_half));

  G4LogicalVolume* Observer_log = new G4LogicalVolume(Observer, Glass, "Observer", 0, 0, 0);
  
  // this is for straight cone
  G4Cons* winston_cone = new G4Cons("winston_cone", rmin_w_front, rmax_w_front, rmin_w_end, rmax_w_end, z_w_half, 0.*degree, 360.*degree);

  // this is for parabolic cone, i.e. WC
  /*  G4Paraboloid* winston_cone1 = new G4Paraboloid("winston_cone1",z_w_half,rmin_w_front,rmin_w_end);
  G4Paraboloid* winston_cone2 = new G4Paraboloid("winston_cone2",z_w_half,rmax_w_front,rmax_w_end);
  G4SubtractionSolid* winston_cone = new G4SubtractionSolid("winston_cone", winston_cone2, winston_cone1); */

  G4LogicalVolume* winston_cone_log = new G4LogicalVolume(winston_cone, Glass, "winston_cone", 0, 0, 0);

  // Winston cone Assembly: place it in the tank

  G4AssemblyVolume* winston_cone_Assembly = new G4AssemblyVolume();
  Rm = R0;
  Rm.rotateZ(0.*degree); // rotate to improve eff.

  Rc = R0;  
  Rc.rotateX(44.*degree); 
  Rc.rotateZ(0.*degree); 
  
  G4ThreeVector Pos_Tmp_winston_cone;
  for(G4int i = 0; i<30; i++){
    Rm.rotateZ(12.*degree);
    Rc.rotateZ(12.*degree);
    Pos_Tmp_winston_cone = Pos_winston_cone;
    Tr = G4Transform3D(Rc, Pos_Tmp_winston_cone.transform(Rm));
    winston_cone_Assembly->AddPlacedVolume(winston_cone_log, Tr);
  } 
  winston_cone_Assembly->MakeImprint(Tank_log, T0, 0, false); 
  
  //  Observer Assembly: place it in the tank
  
  G4AssemblyVolume* Observer_Assembly = new G4AssemblyVolume();
  Rm = R0;
  Rm.rotateZ(0.*degree); // rotate Observer to improve eff.

  Rc = R0; // do not rotate 
  Rc.rotateX(44.*degree); // do not rotate 
  Rc.rotateZ(0.*degree); // do not rotate 
  
  G4ThreeVector Pos_Tmp_Observer;
  for(G4int i = 0; i<30; i++){
    Rm.rotateZ(12.*degree);
    Rc.rotateZ(12.*degree);
    Pos_Tmp_Observer = Pos_Observer;
    Tr = G4Transform3D(Rc, Pos_Tmp_Observer.transform(Rm));
    //    Tr = G4Transform3D(Rm, Pos_Tmp_Observer.transform(Rm));
    Observer_Assembly->AddPlacedVolume(Observer_log, Tr);
  }
  Observer_Assembly->MakeImprint(Tank_log, T0, 0, false);
  
  // Mirror 1
  
  // define Z_mirror w.r.t. the origin of coordinates: 
  // ~ 21 cm before the tank's back wall 
  
  // thickness of mirror: 5mm
  // central ray will give the radius of the sphere 
  // that goes into building the mirror  
  
  G4double Z_M1 = 383.*cm;
  G4double T_M1 = 3.*mm;

  // the polar angular range for the BaBar setup is (8.5, 15.5) deg --> from Xin
  G4ThreeVector central_ray = G4ThreeVector(0., sin(11.5*degree), cos(11.5*degree));

  // this will be returned by the BuildSPMirror routine
  G4ThreeVector Pos_M1;
  G4double R;
  G4Sphere* SPM1 = BuildSPMirror(V0_tg, Pos_Img_Observer, central_ray, Z_M1, T_M1, Pos_M1, R);  
  
  // max and min polar angles in SIDIS
  G4double Angle_in = 8.5*degree;
  G4double Angle_out = 15.5*degree; 

  // z dist. between the target and front/back walls of the tank: 350 + 306 & 350 + 396
  // add 15*cm to R_in because the mirror is sticking out
  G4double Z_front = 656.*cm;
  G4double Z_end = 746.*cm;
  
  G4double R_front_in = Z_front*tan(Angle_in);
  G4double R_front_out = Z_front*tan(Angle_out);
  
  G4double R_end_in = Z_end*tan(Angle_in);
  G4double R_end_out = Z_end*tan(Angle_out);

  // make a cone to intersect a sphere
  G4Cons* CM1 = new G4Cons("CM1", R_front_in, R_front_out, R_end_in, R_end_out, (Z_end-Z_front)/2., (90.-6.)*degree, 12.*degree); 

  G4cout << "rfin is: " << R_front_in/cm << " " << "rfout is: " << R_front_out/cm << " " 
	 << "rein is: " << R_end_in/cm << " " << "reout is: " << R_end_out/cm << " "
	 << "z_half is: " << (Z_end-Z_front)/2./cm << G4endl;

  // this is where the center of the cone should stay w.r.t. (0,0,0)
  // i.e. in the middle of the tank: (306+396)/2=351*cm

  G4ThreeVector Pos_CM1 = G4ThreeVector(0.,0.,351.*cm);

  G4IntersectionSolid* M1 = new G4IntersectionSolid("M1", CM1, SPM1, 0, Pos_M1-Pos_CM1);
  
  G4LogicalVolume* M1_log = new G4LogicalVolume(M1, Glass, "Mirror_1", 0, 0, 0);
  
  G4AssemblyVolume* Mirror_Assembly = new G4AssemblyVolume();
  Rm = R0;
  for(G4int i = 0; i<30; i++){
	  Rm.rotateZ(12.*degree);
	  Tr = G4Transform3D(Rm, Pos_CM1);
	  Mirror_Assembly->AddPlacedVolume(M1_log, Tr);
  }
  Mirror_Assembly->MakeImprint(Tank_log, T0, 0, false); 

  // Magnetic field
  // I put in the real thing: BaBar field from a map created by Paul Reimer
  
  static G4bool fieldIsInitialized = false;
  if(!fieldIsInitialized)
    {
      cherField* myField = new cherField;
      G4FieldManager* fieldMgr
	= G4TransportationManager::GetTransportationManager()->GetFieldManager();
      fieldMgr->SetDetectorField(myField);
      fieldMgr->CreateChordFinder(myField);
      fieldIsInitialized = true;
    } 
  
  
  //	------------- Surfaces --------------
  //
  
  // Mirror Surfaces     
  //
  G4MaterialPropertiesTable* Mirror_SPT = new G4MaterialPropertiesTable();

  /*  G4double Mirror_Reflectivity[nEntries] = {1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1., 1., 1., 1., 
					    1.}; */

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

  G4LogicalSkinSurface* M1_Surface = new G4LogicalSkinSurface("M1_Surface", M1_log, OpMirrorSurface);

  // winston_cone Surfaces     
  //
  G4MaterialPropertiesTable* winston_cone_SPT = new G4MaterialPropertiesTable();

  /*  G4double winston_cone_Reflectivity[nEntries] = {1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1., 1., 1., 1., 
						  1.}; */
  
  G4double winston_cone_Reflectivity[nEntries] = {0.8678125, 0.8651562, 0.8639063, 0.8637500,
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
    
  winston_cone_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, winston_cone_Reflectivity, nEntries);
  winston_cone_SPT->AddProperty("EFFICIENCY", PhotonEnergy, winston_cone_Efficiency, nEntries); 
  
  G4OpticalSurface* wcMirrorSurface = new G4OpticalSurface("wcMirrorSurface");
  wcMirrorSurface->SetType(dielectric_metal);
  wcMirrorSurface->SetFinish(polished);
  wcMirrorSurface->SetModel(unified);
  wcMirrorSurface->SetMaterialPropertiesTable(winston_cone_SPT); 

  G4LogicalSkinSurface* wc_Surface = new G4LogicalSkinSurface("wc_Surface", winston_cone_log, wcMirrorSurface); 

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

  /*  G4double Observer_Efficiency[nEntries] = {1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1., 1., 1., 1., 1., 
					    1.}; */ 

  /*  G4double Observer_Efficiency[nEntries] = {0.015, 0.02, 0.029, 0.045, 0.07, 
					    0.1, 0.175, 0.2, 0.245, 0.285, 
					    0.29, 0.285, 0.26, 0.215, 0.185, 
					    0.14, 0.1}; */
 
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
 
  Observer_SPT->AddProperty("REFLECTIVITY", PhotonEnergy, Observer_Reflectivity, nEntries);
  Observer_SPT->AddProperty("EFFICIENCY", PhotonEnergy, Observer_Efficiency, nEntries);
  
  G4OpticalSurface* OpObserverSurface = new G4OpticalSurface("OpObserverSurface");
  OpObserverSurface->SetType(dielectric_metal);
  OpObserverSurface->SetFinish(polished);
  OpObserverSurface->SetModel(glisur);
  OpObserverSurface->SetMaterialPropertiesTable(Observer_SPT);

  G4LogicalSkinSurface* Observer_Surface = new G4LogicalSkinSurface("Observer_Surface", Observer_log, OpObserverSurface);
  G4LogicalSkinSurface* Tank_Surface = new G4LogicalSkinSurface("Tank_Surface", Tank_log, OpObserverSurface);
  //
  // Visualisation attributes 
  // Invisible world volume.
  
  // Experimental Hall - yellow
  G4VisAttributes* expHallAttributes = new G4VisAttributes(G4Colour::Yellow());
  expHallAttributes->SetForceSolid(false);
  //  expHall_log->SetVisAttributes(expHallAttributes);
  expHall_log->SetVisAttributes(G4VisAttributes::Invisible);
  
  // Tank - magenta
  G4VisAttributes* TankAttributes = new G4VisAttributes(G4Colour::Yellow());
  //  G4VisAttributes* TankAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.2));
  TankAttributes->SetVisibility(false);
  TankAttributes->SetForceSolid(true);
  //  TankAttributes->SetForceWireframe(true);
  Tank_log->SetVisAttributes(TankAttributes);
  
  // Mirror - blue
  G4VisAttributes* MirrorAttributes = new G4VisAttributes(G4Colour::Grey());
  MirrorAttributes->SetForceLineSegmentsPerCircle(200);
  MirrorAttributes->SetVisibility(true);
  MirrorAttributes->SetForceSolid(true);
  M1_log->SetVisAttributes(MirrorAttributes); 
  
  // WC - Red
  G4VisAttributes* wcAttributes = new G4VisAttributes(G4Colour(1.0,0.0,0.0,1.));
  
  //  G4VisAttributes* wcAttributes = new G4VisAttributes(G4Colour::Red());
  wcAttributes->SetVisibility(true);
  wcAttributes->SetForceSolid(true);
  winston_cone_log->SetVisAttributes(wcAttributes); 
  
  // Observer - Blue
  G4VisAttributes* ObserverAttributes = new G4VisAttributes(G4Colour::Cyan());
  ObserverAttributes->SetVisibility(true);
  ObserverAttributes->SetForceSolid(true);
  Observer_log->SetVisAttributes(ObserverAttributes);

//always return the physical World
  return expHall_phys;
}

G4Sphere* cherDetectorConstruction::BuildSPMirror(G4ThreeVector P1, G4ThreeVector P2, 
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
	G4Sphere* SPMirror = new G4Sphere("SPMirror", R, R+T_mirror, 0., 360.*degree, 0., 90.*degree);
	return SPMirror;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
