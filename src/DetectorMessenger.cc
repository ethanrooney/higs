
#include "DetectorMessenger.hh"
#include "ExperimentConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


DetectorMessenger::DetectorMessenger(ExperimentConstruction* HINDAdet)
 :fExpConstruction(HINDAdet)
{

  fInchDef = new G4UnitDefinition("inch","in","Length",2.54*cm);

  fHindaDir = new G4UIdirectory("/Hinda/");
  fHindaDir->SetGuidance("UI commands of this example");

  fDetDir = new G4UIdirectory("/Hinda/det/");
  fDetDir->SetGuidance("detector control");

  fShapeCmd = new G4UIcmdWithAString("/Hinda/det/setTargetShape",this);
  fShapeCmd->SetGuidance("Set the target shape");
  fShapeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fMatCmd = new G4UIcmdWithAString("/Hinda/det/setTargetMaterial",this);
  fMatCmd->SetGuidance("Set the target material");
  fMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fDiameterCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetDiameter",this);
  fDiameterCmd->SetGuidance("Set target diameter (Cylindrical)");
  fDiameterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLxCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetLx",this);
  fLxCmd->SetGuidance("Set target Lx (Rectangular)");
  fLxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLyCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetLy",this);
  fLyCmd->SetGuidance("Set target Ly (Rectangular)");
  fLyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLzCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetLz",this);
  fLzCmd->SetGuidance("Set target Lz (all shapes)");
  fLzCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fThetaCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetTheta",this);
  fThetaCmd->SetGuidance("Set target theta");
  fThetaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fPhiCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/det/setTargetPhi",this);
  fPhiCmd->SetGuidance("Set target phi");
  fPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}




DetectorMessenger::~DetectorMessenger()
{
  delete fShapeCmd;
  delete fMatCmd;
  delete fDiameterCmd;
  delete fLxCmd;
  delete fLyCmd;
  delete fLzCmd;
  delete fThetaCmd;
  delete fPhiCmd;

}



void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{

  if(command == fShapeCmd)
    {fExpConstruction->SetTargetShape(newValue);}

  if(command == fMatCmd)
    {fExpConstruction->SetTargetMaterial(newValue);}

  if(command == fDiameterCmd)
    {fExpConstruction->SetTargetDiameter(fDiameterCmd->GetNewDoubleValue(newValue));}

  if(command == fLxCmd)
    {fExpConstruction->SetTargetLx(fLxCmd->GetNewDoubleValue(newValue));}

  if(command == fLyCmd)
    {fExpConstruction->SetTargetLy(fLyCmd->GetNewDoubleValue(newValue));}

  if(command == fLzCmd)
    {fExpConstruction->SetTargetLz(fLzCmd->GetNewDoubleValue(newValue));}

  if(command == fThetaCmd)
    {fExpConstruction->SetTargetTheta(fThetaCmd->GetNewDoubleValue(newValue));}

  if(command == fPhiCmd)
    {fExpConstruction->SetTargetPhi(fPhiCmd->GetNewDoubleValue(newValue));}

}
