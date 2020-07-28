//Created by S. Henshaw 3/26/10
//Mostly Copied from geant4/examples/novice/NO2

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "ExperimentConstruction.hh"

#include "TMath.h"
#include "G4Event.hh"
#include "G4Tubs.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "MoreUnits.hh"
#include "geomdefs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(
                                               ExperimentConstruction* myDC)
  :myDetector(myDC), fMode(2), fBeamDiameter(0.0), fTmin(0.0), fTmax(0.0), fThetaMin(0.0), fThetaMax(180*deg), fPhiMin(-180*deg), fPhiMax(180*deg)
{
  fThreeVector = G4ThreeVector(0,0,1);

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  fGunMessenger = new PrimaryGeneratorMessenger(this);
  
}
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 

  switch(fMode){
    //generate beam at -z of world, propagate towards target
  case EPGA_ZofWorld:
    SetBeamZStartOfWorld();
    break;
    //generate beam at center of world
  case EPGA_CenterOfWorld:
    SetBeamCenterOfWorld();
    break;
    //generate beam throught target volume
  case EPGA_Target:
    SetBeamTargetVolume();
    break;
    //generate beam in beam spot at center of target
  case EPGA_BeamSpotTarget:
    SetBeamSpotTarget();
    break;
  default:
    G4cerr<<"Unknown mode given to PrimaryGeneratorAction"<<G4endl;
    exit(1);
  }

  //should only generate 1 vertex
  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetBeamZStartOfWorld()
{
  G4float T;
  if(fTmin == fTmax)T=fTmin;      //saves time, don't need G4UniformRand()
  else T=fTmin+(fTmax-fTmin)*G4UniformRand();
  G4float Mass=particleGun->GetParticleDefinition()->GetPDGMass();
  G4float E=T+Mass;
  G4float P=sqrt(E*E-Mass*Mass);
  fThreeVector.setMag(P);
  fThreeVector.setTheta(0);
  fThreeVector.setPhi(0);
  particleGun->SetParticleMomentumDirection(fThreeVector.unit());
  particleGun->SetParticleEnergy(T);
 
  if(fBeamDiameter>=0.0)
    {
      //Distributed particles over a circle
      if(fBeamDiameter<0.001*mm)
	{//Just makes a point beam 
	  G4double position = -0.5*(myDetector->GetWorldLengthZ());
	  particleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,position));
	}
      else
	{//Uniformly distributes particles in circle of diameter=BeamDiamter
	  G4bool flag=true;
	  G4double posX;
	  G4double posY;
	  G4double BeamRadius=fBeamDiameter/2.0;
	  G4double radius=0;
	  while(flag)
	    {
	      //posX=BeamDiameter/2.0;
	      //posY=BeamDiameter/2.0;
	      posX=(2.*(G4UniformRand()-0.5))*BeamRadius;
	      posY=(2.*(G4UniformRand()-0.5))*BeamRadius;
	      radius=sqrt((posX*posX)+(posY*posY));
	      if(radius<=BeamRadius)flag=false;
	    }
	  G4double posZ = -0.5*(myDetector->GetWorldLengthZ());
	  particleGun->SetParticlePosition(G4ThreeVector(posX,posY,posZ));
	}
    }
  else
    {
      G4cerr<<"**ERROR:  BeamDiameter INVALID!!!!**"<<G4endl;
      G4Exception();
    }
}

void PrimaryGeneratorAction::SetBeamCenterOfWorld(void)
{
  G4float T;
  if(fTmin == fTmax)T=fTmin;      //saves time, don't need G4UniformRand()
  else T=fTmin+(fTmax-fTmin)*G4UniformRand();
  G4float Mass=particleGun->GetParticleDefinition()->GetPDGMass();
  G4float E=T+Mass;
  G4float P=sqrt(E*E-Mass*Mass);
  G4float theta=fThetaMin+(fThetaMax-fThetaMin)*G4UniformRand();
  G4float phi=fPhiMin+(fPhiMax-fPhiMin)*G4UniformRand();
  fThreeVector.setMag(P);
  fThreeVector.setTheta(theta);
  fThreeVector.setPhi(phi);

  particleGun->SetParticleMomentumDirection(fThreeVector.unit());
  particleGun->SetParticleEnergy(T);
  particleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,0.0*mm));
  
}


void PrimaryGeneratorAction::SetBeamTargetVolume(void)
{
  //set energy and momentum based on input energy
  G4float T;
  if (fTmin == fTmax) T = fTmin;      //saves time, don't need G4UniformRand()
  else T = fTmin + (fTmax - fTmin) * G4UniformRand();
  G4float Mass=particleGun->GetParticleDefinition()->GetPDGMass();
  G4float E = T + Mass;
  G4float P = sqrt(E * E - Mass * Mass);
  G4float theta=fThetaMin+(fThetaMax-fThetaMin)*G4UniformRand();
  G4float phi=fPhiMin+(fPhiMax-fPhiMin)*G4UniformRand();
  fThreeVector.setMag(P);
  fThreeVector.setTheta(theta);
  fThreeVector.setPhi(phi);
  
  particleGun->SetParticleMomentumDirection(fThreeVector.unit());
  particleGun->SetParticleEnergy(T);


  //Returns pointer to Target Solid Defined in ExperimentConstruction
  G4VPhysicalVolume* physiTarget=myDetector->GetTargetPhysicalVolume();
  G4VSolid* target=physiTarget->GetLogicalVolume()->GetSolid();
  G4RotationMatrix TargetRot=*physiTarget->GetRotation();
  G4ThreeVector TargetPos=physiTarget->GetTranslation();

  //Makes a Box big enough to enclose the Target for Gen. Inital guess (Assumes Target is cylinder)
  G4double GenBoxVol=target->GetCubicVolume();
  G4double GenBoxLength=2*pow(GenBoxVol,0.3333333);

  G4bool flag=true;
  G4ThreeVector pos;
  while(flag)
    {
      //Generating Random Position inside Gen Box 
      G4double xGen=GenBoxLength*(2.*(G4UniformRand()-0.5));
      G4double yGen=GenBoxLength*(2.*(G4UniformRand()-0.5));
      G4double zGen=GenBoxLength*(2.*(G4UniformRand()-0.5));
      pos=G4ThreeVector(xGen,yGen,zGen);

      //Checking to see if pos is inside target volume
      if(target->Inside(pos)==kInside)
	{
	  //	  G4cout<<"The primary is inside the Target"<<G4endl;
	  flag=false;
	}
   
    }

  G4ThreeVector posTrans=pos + TargetPos;
  G4ThreeVector posFinal=posTrans.transform(TargetRot);
  
  particleGun->SetParticlePosition(posFinal);
    
}


//Generate events within a circle of diameter
//fBeamSpotDiameter within the center of the 
//target volume.
//M. Sikora
//Jan. 3, 2013
void PrimaryGeneratorAction::SetBeamSpotTarget(void)
{
  //set energy and momentum based on input energy
  G4float T;
  if (fTmin == fTmax) T = fTmin;      //saves time, don't need G4UniformRand()
  else T = fTmin + (fTmax - fTmin) * G4UniformRand();
  G4float Mass=particleGun->GetParticleDefinition()->GetPDGMass();
  G4float E = T + Mass;
  G4float P = sqrt(E * E - Mass * Mass);
  G4float theta=fThetaMin+(fThetaMax-fThetaMin)*G4UniformRand();
  G4float phi=fPhiMin+(fPhiMax-fPhiMin)*G4UniformRand();
  fThreeVector.setMag(P);
  fThreeVector.setTheta(theta);
  fThreeVector.setPhi(phi);
  
  particleGun->SetParticleMomentumDirection(fThreeVector.unit());
  particleGun->SetParticleEnergy(T);


  //Returns pointer to Target Solid Defined in ExperimentConstruction
  G4VPhysicalVolume* physiTarget=myDetector->GetTargetPhysicalVolume();
  G4VSolid* target=physiTarget->GetLogicalVolume()->GetSolid();
  G4RotationMatrix TargetRot=*physiTarget->GetRotation();
  G4ThreeVector TargetPos=physiTarget->GetTranslation();

  //Makes a Box big enough to enclose the Target for Gen. Inital guess (Assumes Target is cylinder)
  G4double GenBoxVol=target->GetCubicVolume();
  G4double GenBoxLength=2*pow(GenBoxVol,0.3333333);

  G4bool flag = true;
  G4ThreeVector pos;
  G4double BeamRadius = fBeamDiameter / 2.0;
  G4double radius=0.0;
  while (flag) {
    //Generating Random Position inside Gen Box 
    G4double xGen = BeamRadius * (2.0 * (G4UniformRand() - 0.5));
    G4double yGen = BeamRadius * (2.0 * (G4UniformRand() - 0.5));
    G4double zGen = GenBoxLength * (2.0 * (G4UniformRand() - 0.5));
    pos = G4ThreeVector(xGen,yGen,zGen);
    radius = sqrt( (xGen * xGen) + (yGen * yGen) );
    
    //Checking to see if pos is inside target volume
    //and within the beam spot diameter
    if (target->Inside(pos) == kInside && radius <= BeamRadius) flag = false;
    
  }


  G4ThreeVector posTrans=pos + TargetPos;
  G4ThreeVector posFinal=posTrans.transform(TargetRot);
  
  particleGun->SetParticlePosition(posFinal);
    
}
