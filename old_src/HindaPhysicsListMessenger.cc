
#include "HindaPhysicsListMessenger.hh"

#include "HindaPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"


HindaPhysicsListMessenger::HindaPhysicsListMessenger(HindaPhysicsList* HindaPhysList) :HindaList(HindaPhysList)
{
  physDir = new G4UIdirectory("/Hinda/physics/");
  physDir->SetGuidance("physics control");

  AddListCmd = new G4UIcmdWithAString("/Hinda/physics/AddPhysicsList",this);
  AddListCmd->SetGuidance("Add physics lists");
  AddListCmd->AvailableForStates(G4State_PreInit);

  PrintListsCmd = new G4UIcmdWithoutParameter("/Hinda/physics/Print",this);
  PrintListsCmd->SetGuidance("Available physics lists");
  PrintListsCmd->AvailableForStates(G4State_PreInit);
 
}


HindaPhysicsListMessenger::~HindaPhysicsListMessenger()
{
  delete physDir;
  delete AddListCmd;
  delete PrintListsCmd;

}



void HindaPhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == AddListCmd )
    HindaList->AddList(newValue);

  if( command == PrintListsCmd )
    HindaList->Print();

}
