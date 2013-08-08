#ifndef Config_h
#define Config_h 1

#include <cmath>

//// low energy background
//enum
//{
//	nX = 1, nY = 1, nScintlayer = 200
//				, nblock = nX*nY
//}; // number of shower elements
//
//static const G4double Shower_blockHeight = 40.0 * cm;
//static const G4double Shower_blockWidth = 40.0 * cm;

static const char * PHYSICS_LIST = "QGSP_BERT";
//static const char * PHYSICS_LIST = "FTFP_BERT";
static const double prod_thre = 0.2 * mm;
//static const double prod_thre = 1.5 * mm;

// hexagon
enum
{
//	nX = 8, nY = 4, nScintlayer = 200
	nX = 20,
	nY = 8,
//	nScintlayer = 400
//	nScintlayer = 220 // 20 + .5 X0 for 0.5mm Pb
//	nScintlayer = 300
	nScintlayer = 194 // 20 X0 for 0.5mm Pbs
//		nScintlayer = 37+3 // HERA-b
//	nScintlayer = 2000
//			nX = 1, nY = 1, nScintlayer = 20

	,
	nblock = nX * nY
};
// number of shower elements


//static const G4double Shower_blockWidth = 2.0 * cm; // nX
//static const G4double Shower_blockHeight = 2.0 * cm; // nY
//static const G4double Shower_blockHeight = 10.0 * cm; // nY
//static const G4double Shower_blockWidth = 10.0 * cm; // nX

// Hexigon modules
static const G4double Shower_blockWidth = 2*5.4 * cm; // nX
static const G4double Shower_blockHeight = 2*5.4 * cm; // nY

// PVDIS
//static const G4double CaloCentralR = 1.75 * m;

////// SIDIS Forward
//static const G4double CaloCentralR = 1.58 * m;

////// SIDIS Large
//static const G4double CaloCentralR = 1.1 * m;

// Radiation background & layout
static const G4double CaloCentralR = 0 * m;

//static const G4double Rotation = (22 + 35) / 2 * degree;
static const G4double Rotation = 0 * degree;
//static const G4double Rotation = 30 * degree;

//#define CaloMaterial  LeadH
#define CaloMaterial  Lead
#define GlueMaterial  Air
#define FilberMaterial  BC404
//#define CaloMaterial  Air
//#define GlueMaterial  Air
//#define FilberMaterial  Air

//static const G4double AbsorbThick = 1* mm;
//static const G4double AbsorbThick = 0.8 * mm;
//static const G4double AbsorbThick = 0.6 * mm;
static const G4double AbsorbThick = 0.5 * mm; // Sampling ratio = 0.253017(EM) 0.285811(MIP) 0.34+-0.04(H)
//static const G4double AbsorbThick = 0.4 * mm;

static const G4double ScintThick = 1.5 * mm;
//const G4double layerSep = 2.54 * mm;

////HERA-b
//static const G4double AbsorbThick = 3* mm;
//static const G4double ScintThick = 6 * mm;

static const G4double layerSep = 0.24 * mm + AbsorbThick + ScintThick;

// scintillator before preshower as photon rejector
static const G4double phrej_Scint = 0.5  * cm;

// support structure Al.
static const G4double front_spt_plate = 2  * cm;
#define FrontPlateMaterial  Aluminum

//// Lead Absorber preshower
//static const G4double leading_Pb = 0.5137 * cm * 1.5; // 1.5 X0
static const G4double leading_Pb = 0.5137 * cm * 2; // 2 X0
static const G4double leading_Scint = 2  * cm;
static const G4double backend_Scint = 4 * cm;

////// Lead Absorber preshower
//static const G4double leading_Pb = 0.5137 * cm * 3; // 3 X0
//static const G4double leading_Scint = 2  * cm;
//static const G4double backend_Scint = 0 * mm;

//// No Lead Absorber preshower
//static const G4double leading_Pb = AbsorbThick / 2;
//static const G4double leading_Scint = 0;
//static const G4double backend_Scint = 0;
//
//// backside Scint
//static const G4double backend_Scint = 2 * cm;

//#define CaloMaterial  Copper
//static const G4double AbsorbThick = 1.27940128 * mm; // Sampling ratio = 0.148042(EM) 0.152996(MIP) 0.17+-0.02(H)

//static const G4double AbsorbThick = 0.05 * mm;
//
//static const G4double ScintThick = .15 * mm;
////const G4double layerSep = 2.54 * mm;
//static const G4double layerSep = AbsorbThick + ScintThick;

static const G4double ShashlikBlockDepth = (nScintlayer - 2) * layerSep
        + phrej_Scint+ leading_Pb + leading_Scint  + front_spt_plate + backend_Scint;
//static const G4double ShashlikBlockDepth = 5 * layerSep ;

//static const G4double OverallShiftZ = -17 *cm +  ShashlikBlockDepth/2;
static const G4double OverallShiftZ = 0 + ShashlikBlockDepth / 2;

#ifndef __CINT__
#include <G4ThreeVector.hh>
static G4double Edep2Photon(const G4double edep, const G4ThreeVector hitpos)
{
	const G4double dis2middle = OverallShiftZ - hitpos.z();
	const G4double x = fmod(hitpos.x() - (nX % 2) * Shower_blockWidth / 2,
	        Shower_blockWidth);
	const G4double y = fmod(hitpos.y() - (nY % 2) * Shower_blockHeight / 2,
	        Shower_blockHeight);

	// 60 photon / MeV for 0.275mm PB - 1.5mm Scint, Nucl.Instrum.Meth.A584:291-303,2008
	G4double scale = 60 / MeV * (0.275 * mm / AbsorbThick)
	        * (ScintThick / (1.5 * mm));

	// position dependence for one fiber per cm
	// approximately described in 	Nucl.Instrum.Meth.A584:291-303,2008
	scale *= 1 - 5e-3 / 2 * cos(x / (1 * cm) * 2 * M_PI)
	        - 5e-3 / 2 * cos(y / (1 * cm) * 2 * M_PI);

	// attenuation in the WLS fiber Y11(200)MS = 360cm, Nucl.Instrum.Meth.A584:291-303,2008
	scale *= exp(-dis2middle / (360 * cm));

//		G4cout<<"hitpos = "
//				<<hitpos.x()<<", "
//				<<hitpos.y()<<", "
//				<<hitpos.z()<<"; "
//				<<"x = "<<x<<", "
//				<<"y = "<<y<<", "
//				<<"dis2middle = "<<dis2middle<<", "
//				<<"scale = "<<scale<<"."
//				<<G4endl;

	return edep * scale;
}
#endif

#endif

