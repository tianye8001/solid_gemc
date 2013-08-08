#include "CaloSimPrimaryGeneratorAction.hh"
#include "CaloSimPrimaryGeneratorMessenger.hh"
#include "CaloSimSD.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
#include <G4FPlane.hh>

bool CaloSimPrimaryGeneratorAction::DefineBeamParticle(G4String particleName)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	if (particle)
	{
		particleGun->SetParticleDefinition(particle);
		G4cout << "Define beam particle " << particleName << G4endl;
		return true;
	}
	else
		G4cerr << "Cannot find beam particle " << particleName << G4endl;
	return false;

}

CaloSimPrimaryGeneratorAction::CaloSimPrimaryGeneratorAction(
        CaloSimDetectorConstruction* myDC) :
		myDetector(myDC)
{

	generatorMessenger = new CaloSimPrimaryGeneratorMessenger(this);

	SetEnergy(2);
	SetAngle(5);
	SetAngleRand(0);
	SetXInit(0);
	SetXInitRand(0.1);
	SetYInit(0);
	SetYInitRand(0);
	SetUseFile(0);
	//	SetInputFile("/data/npluser2/nschroed/g2electrons/wiggle1.dat");

	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);
	DefineBeamParticle();

	//  particleGun->SetParticleEnergy(1.0*GeV);
	//  particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, -0.1*m));

	//	elecfile = fopen("/data/npluser2/nschroed/g2electrons/wiggle1.dat", "r");

	elecfile = 0;
	fUseFile = 0;
	fEnergy = 0;
	fEnergySpread = 0;
	fAngle = 5;
	// particleGunMessenger = new CaloSimParticleGunMessenger(particleGun);
	//generatorMessenger = new CaloSimGeneratorMessenger(this);

	evcnt = 0;
}

CaloSimPrimaryGeneratorAction::~CaloSimPrimaryGeneratorAction()
{
	//delete generatorMessenger;
	delete particleGun;
	delete generatorMessenger;
}

void CaloSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	evcnt++;

	//this gets the electron info from the input files
	if (fUseFile)
	{
		// Get Initial position and momentum from file
//		G4float X = 0, Y = 0, Z = 0, XP = 0, YP = 0, ZP = 0;
		G4float X0 = 0, Y0 = 0, Z0 = 0, XP0 = 0, YP0 = 0, ZP0 = 0;
		G4float E = 0, theta = 0;
		E = 0;
		while (E < 0.5)
		{
			assert(elecfile);

			if (feof(elecfile))
				rewind(elecfile);

			char buffer[1000] =
			{ NULL };
			char * retchar = fgets(buffer, 1000, elecfile);
			if (!retchar)
			{
				rewind(elecfile);
				char * retchar = fgets(buffer, 1000, elecfile);
				assert(retchar);
			}

			G4int nret = sscanf(buffer, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &X0,
			        &Y0, &Z0, &XP0, &YP0, &ZP0, &E, &theta);

			assert(nret == 7 || nret == 8);

			if (nret == 8)
				CaloSimSD::SetInitTheta(theta);
		}

		// Rotating prim particle for calorimeter rotation by Rotation degrees

		const G4Vector3D CaloCSinHCS(CaloCentralR, 0 * cm, 0 * cm);
		const G4Transform3D RotHCS2CaloCS = G4RotateY3D(-Rotation);

		const G4Vector3D FrontFaceCenter_CaloCS = G4ThreeVector(0, 0, 0);
		const G4Vector3D FrontFaceNorm_CaloCS = G4ThreeVector(0, 0, 1);

		const G4Vector3D primPosition_HCS(X0 * cm, Y0 * cm, Z0 * cm);
		const G4Vector3D primMomentum_HCS(XP0 * GeV, YP0 * GeV, ZP0 * GeV);

		const G4Vector3D primPosition_CaloCS = RotHCS2CaloCS
		        * G4Vector3D(primPosition_HCS - CaloCSinHCS);
		const G4Vector3D primMomentum_CaloCS = RotHCS2CaloCS * primMomentum_HCS;
		const G4Vector3D primDir_CaloCS = primMomentum_CaloCS
		        / primMomentum_CaloCS.mag();

		// Calculate intersections  -   G4FPlane
//		00235   b = norm.x() * dirx + norm.y() * diry + norm.z() * dirz;
//		00236
//		00237   if ( std::fabs(b) < perMillion )
//		00238   {
//		00239     // G4cout << "\nLine is parallel to G4Plane.No Hit.";
//		00240   }
//		00241   else
//		00242   {
//		00243     G4double startx =  RayStart.x();
//		00244     G4double starty =  RayStart.y();
//		00245     G4double startz =  RayStart.z();
//		00246
//		00247     a = norm.x() * (srf_point.x() - startx) +
//		00248         norm.y() * (srf_point.y() - starty) +
//		00249         norm.z() * (srf_point.z() - startz)   ;
//		00250
//		00251     t = a/b;
//		00252
//		00253     // substitute t into line equation
//		00254     // to calculate final solution
//		00255     G4double solx,soly,solz;
//		00256     solx = startx + t * dirx;
//		00257     soly = starty + t * diry;
//		00258     solz = startz + t * dirz;

		const G4double b = FrontFaceNorm_CaloCS * primDir_CaloCS;
		const G4double a = FrontFaceNorm_CaloCS
		        * (FrontFaceCenter_CaloCS - primPosition_CaloCS);
		const G4Vector3D primPosition_FrontFace_CaloCS = primPosition_CaloCS
		        + a / b * primDir_CaloCS;

		G4cout << "CaloCSinHCS = " << CaloCSinHCS.x() << ", " << CaloCSinHCS.y()
		        << ", " << CaloCSinHCS.z() << G4endl;
		G4cout << "primPosition_HCS = " << primPosition_HCS.x() << ", "
		        << primPosition_HCS.y() << ", " << primPosition_HCS.z()
		        << G4endl;
		G4cout << "primMomentum_HCS = " << primMomentum_HCS.x() << ", "
		        << primMomentum_HCS.y() << ", " << primMomentum_HCS.z()
		        << G4endl;
		G4cout << "primPosition_CaloCS = " << primPosition_CaloCS.x() << ", "
		        << primPosition_CaloCS.y() << ", " << primPosition_CaloCS.z()
		        << G4endl;
		G4cout << "primMomentum_CaloCS = " << primMomentum_CaloCS.x() << ", "
		        << primMomentum_CaloCS.y() << ", " << primMomentum_CaloCS.z()
		        << G4endl;
		G4cout << "primPosition_FrontFace_CaloCS = "
		        << primPosition_FrontFace_CaloCS.x() << ", "
		        << primPosition_FrontFace_CaloCS.y() << ", "
		        << primPosition_FrontFace_CaloCS.z() << G4endl;

		// must translate again
		// Initial position of particles with offsets from old GEANT sim
		//        G4ThreeVector primPosition((X - 11.25 + 10.001) * cm, Y * cm, (Z + 7.5
		//            - 5.5 - 0.1) * cm);

		// normal definitons
//		G4ThreeVector primPosition(X * cm, Y * cm, Z * cm);
		G4ThreeVector primPosition = primPosition_FrontFace_CaloCS;

		G4cout << "Read initial track #" << evcnt << " : E = " << E
		        << " GeV, Angle = " << theta << ", x = "
		        << primPosition.x() / cm << " cm" << G4endl;

//		std::cerr << "Vertex = " << X << "\t"
//		        << Y << "\t" << Z << G4endl;

		particleGun->SetParticlePosition(primPosition);

//		G4ParticleMomentum primMomentum(XP * GeV, YP * GeV, ZP * GeV);
		G4ParticleMomentum primMomentum = primMomentum_CaloCS;
		//G4cout<<ZP<<G4endl;
		//		particleGun->SetParticleEnergy(E * GeV);
		particleGun->SetParticleMomentum(primMomentum);
		//		G4cout <<"primMomentum = "<< primMomentum.x()<<"\t"<< primMomentum.y()<<"\t"<< primMomentum.z() <<G4endl;
	}
	else
	{

		//xcenter is the center beam dist in x, xroff is x random offset
		G4double xorig = fXInit + fXInitRand * (G4UniformRand());
		G4double yorig = fYInit + fYInitRand * (G4UniformRand());
		//G4cout<<"genX = "<<xorig+7.5<<"   genY = "<<yorig+7.5<<G4endl;

		//    G4cout<<xorig<<G4endl;
		//sets initial position
		//     G4ThreeVector primPosition(xorig*cm,yorig*cm,-6.90*cm);
		G4ThreeVector primPosition(xorig * cm, yorig * cm, -1 * cm);
		particleGun->SetParticlePosition(primPosition);
		//incident angle
		G4double angle_inc = fAngle * deg + G4UniformRand() * fAngleRand * deg;

		G4ThreeVector primMomentum(std::sin(angle_inc), 0, std::cos(angle_inc));

		const G4double EnergySpread =
		        fEnergySpread <= 0 ? 0 :
		                1e-6 * GeV
		                        * exp(
		                                G4UniformRand()
		                                        * log(
		                                                fEnergySpread * GeV
		                                                        / (1e-6 * GeV)));

		particleGun->SetParticleEnergy(fEnergy * GeV + EnergySpread);
		particleGun->SetParticleMomentumDirection(primMomentum);

		G4cout << evcnt << ": primMomentum ("
		        << (fEnergy * GeV + EnergySpread) / GeV << " GeV) = "
		        << primMomentum.x() << "\t" << primMomentum.y() << "\t"
		        << primMomentum.z() << G4endl;
	}

	particleGun->GeneratePrimaryVertex(anEvent);

}

void CaloSimPrimaryGeneratorAction::SetInputFile(G4String fname)
{

	G4cout << "Use Gun Input file " << fname << G4endl;
	fFilename = fname;

	if (elecfile)
	{
		fclose(elecfile);
		elecfile = NULL;
	}

	elecfile = fopen(fname, "r");
	//fUseFile=1;
	//	G4cout << "\n\n\nFILENAME: " << fFilename << "\n\n";

	assert(elecfile);
}

