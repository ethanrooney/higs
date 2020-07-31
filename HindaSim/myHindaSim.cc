//Created by S. Henshaw 3/26/10
//Mostly Copied from geant4/examples/novice/NO2

#include "ExperimentConstruction.hh"
//#include "PhysicsList.hh"
//#include "HindaPhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
//#include "LHEP.hh"
//#include "LHEP_PRECO_HP.hh"
#include "QGSP_BIC_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  ExperimentConstruction* ExpHall = new ExperimentConstruction;
  runManager->SetUserInitialization(ExpHall);

  //This uses the Defined PhysicsList class to implement physics lists
  //runManager->SetUserInitialization(new HindaPhysicsList);
  QGSP_BIC_HP* theQGSP = new QGSP_BIC_HP;
  runManager->SetUserInitialization(theQGSP);  


  //This uses the Prebuilt list (Will Run Much Slower becuase its calc'ing all Processes
  //runManager->SetUserInitialization(new LHEP);
  //runManager->SetUserInitialization(new LHEP_PRECO_HP);
   
  // User Action classes
  G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction(ExpHall);
  runManager->SetUserAction(gen_action);
  //
  G4UserRunAction* run_action = new RunAction;
  runManager->SetUserAction(run_action);
  //
  G4UserEventAction* event_action = new EventAction;
  runManager->SetUserAction(event_action);
  //
  G4UserSteppingAction* stepping_action = new SteppingAction;
  runManager->SetUserAction(stepping_action);

  // Initialize G4 kernel
  //runManager->Initialize();
      
  // Get the pointer to the User Interface manager
  G4UImanager * UI = G4UImanager::GetUIpointer();  

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }
    
  else           // interactive mode : define visualization and UI terminal
    {
      UI->ApplyCommand("/control/execute init_vis.mac");
      ui->SessionStart();
      delete ui;
    }

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete visManager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

