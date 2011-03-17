#include "CaloSimPrimaryGeneratorAction.hh"
#include "CaloSimPrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"




CaloSimPrimaryGeneratorAction::CaloSimPrimaryGeneratorAction(CaloSimDetectorConstruction* myDC):myDetector(myDC)
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
  SetInputFile("/data/npluser2/nschroed/g2electrons/wiggle1.dat");

 G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName="e-";
  G4ParticleDefinition* particle = 
    particleTable->FindParticle(particleName);
  particleGun->SetParticleDefinition(particle);
  //  particleGun->SetParticleEnergy(1.0*GeV);
  //  particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, -0.1*m));

  elecfile=fopen("/data/npluser2/nschroed/g2electrons/wiggle1.dat", "r");

  //elecfile=0;
  //fUseFile=0;
  //fEnergy=0;
  //  fAngle=5;
  // particleGunMessenger = new CaloSimParticleGunMessenger(particleGun);
  //generatorMessenger = new CaloSimGeneratorMessenger(this);

}

CaloSimPrimaryGeneratorAction::~CaloSimPrimaryGeneratorAction()
{
  //delete generatorMessenger;
  delete particleGun;
  delete generatorMessenger;
}

void CaloSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this gets the electron info from the input files
  if(fUseFile){
    // Get Initial position and momentum from file
    G4float X, Y, Z, XP, YP, ZP, E;
    E=0;
    while(E<0.5){
      fscanf(elecfile, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n",&X,&Y,&Z,&XP,&YP,&ZP,&E);
    }
    G4cout<<"1 electron"<<G4endl;

    // must translate again
    // Initial position of particles with offsets from old GEANT sim
    G4ThreeVector primPosition((X-11.25+10.001)*cm, Y*cm, (Z+7.5-5.5-0.1)*cm);
    
    particleGun->SetParticlePosition(primPosition);
    
    G4ParticleMomentum primMomentum(XP*GeV, YP*GeV, ZP*GeV);
    //G4cout<<ZP<<G4endl;
    particleGun->SetParticleMomentum(primMomentum);
  } else {

    //xcenter is the center beam dist in x, xroff is x random offset
    G4double xorig=fXInit+fXInitRand*(G4UniformRand());
    G4double yorig=fYInit+fYInitRand*(G4UniformRand());
    //G4cout<<"genX = "<<xorig+7.5<<"   genY = "<<yorig+7.5<<G4endl;

    //    G4cout<<xorig<<G4endl;
    //sets initial position
//     G4ThreeVector primPosition(xorig*cm,yorig*cm,-6.90*cm);
    G4ThreeVector primPosition(xorig*cm,yorig*cm,-21*cm);    
    particleGun->SetParticlePosition(primPosition);
    //incident angle
    G4double angle_inc = fAngle*deg+G4UniformRand()*fAngleRand*deg;
    
    G4ThreeVector primMomentum(std::sin(angle_inc),0,std::cos(angle_inc));
    particleGun->SetParticleEnergy(fEnergy*GeV);
    particleGun->SetParticleMomentumDirection(primMomentum);
    
  }

  particleGun->GeneratePrimaryVertex(anEvent);

}


/*void CaloSimPrimaryGeneratorAction::SetInputFile(G4String fname){

  elecfile=fopen(fname, "r");
  //fUseFile=1;
  G4cout<< "\n\n\nFILENAME: " << fFilename << "\n\n";
}
*/
