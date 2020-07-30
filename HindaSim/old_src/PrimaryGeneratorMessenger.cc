
#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"




PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* HindaGun) :HindaAction(HindaGun)
{

  gunDir = new G4UIdirectory("/Hinda/generator/");
  gunDir->SetGuidance("PrimaryGenerator control");

  SetModeCmd = new G4UIcmdWithAnInteger("/Hinda/generator/Mode",this);
  SetModeCmd->SetGuidance("Set the mode of the generator, -z of world, origin, or uniform target");
  SetModeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetDiameterCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setBeamDiameter",this);
  SetDiameterCmd->SetGuidance("Set the diameter of the beam for primary generation at -z of world");
  SetDiameterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetTminCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setTmin",this);
  SetTminCmd->SetGuidance("Set the minimum particle energy for the phase space generator");
  SetTminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetTmaxCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setTmax",this);
  SetTmaxCmd->SetGuidance("Set the maximum particle energy for the phase space generator");
  SetTmaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetThetaMinCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setThetaMin",this);
  SetThetaMinCmd->SetGuidance("Set the minimum particle theta for phase space generation");
  SetThetaMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetThetaMaxCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setThetaMax",this);
  SetThetaMaxCmd->SetGuidance("Set the maximum particle theta for phase space generation");
  SetThetaMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetPhiMinCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setPhiMin",this);
  SetPhiMinCmd->SetGuidance("Set the minimum particle phi for phase space generation");
  SetPhiMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetPhiMaxCmd = new G4UIcmdWithADoubleAndUnit("/Hinda/generator/setPhiMax",this);
  SetPhiMaxCmd->SetGuidance("Set the maximum particle phi for phase space generation");
  SetPhiMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}


PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{

  delete gunDir;
  delete SetModeCmd;
  delete SetDiameterCmd;
  delete SetTminCmd;
  delete SetTmaxCmd;
  delete SetThetaMinCmd;
  delete SetThetaMaxCmd;
  delete SetPhiMinCmd;
  delete SetPhiMaxCmd;

}



void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

  if( command == SetModeCmd )
    { HindaAction->SetMode(SetModeCmd->GetNewIntValue(newValue));}

  if(command == SetDiameterCmd )
    { HindaAction->SetBeamDiameter(SetDiameterCmd->GetNewDoubleValue(newValue));}

  if( command == SetTminCmd )
    { HindaAction->SetTmin(SetTminCmd->GetNewDoubleValue(newValue));}

  if( command == SetTmaxCmd )
    { HindaAction->SetTmax(SetTmaxCmd->GetNewDoubleValue(newValue));}

  if( command == SetThetaMinCmd )
    { HindaAction->SetThetaMin(SetThetaMinCmd->GetNewDoubleValue(newValue));}

  if( command == SetThetaMaxCmd )
    { HindaAction->SetThetaMax(SetThetaMaxCmd->GetNewDoubleValue(newValue));}

  if( command == SetPhiMinCmd )
    { HindaAction->SetPhiMin(SetPhiMinCmd->GetNewDoubleValue(newValue));}

  if( command == SetPhiMaxCmd )
    { HindaAction->SetPhiMax(SetPhiMaxCmd->GetNewDoubleValue(newValue));}

}
