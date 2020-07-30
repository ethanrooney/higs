

#include "RunAction.hh"
#include "DataManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"



//------------------------------------------------------------------------------

RunAction::RunAction():fEventAction(NULL)
{
  G4cout<<"Constructing Run Action"<<G4endl;
  data = DataManager::GetInstance();
}

//-----------------------------------------------------------------------------

RunAction::~RunAction()
{}

//-----------------------------------------------------------------------------

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout<<"BeginOfRunAction"<<G4endl;

  //run information
  G4int runID = aRun->GetRunID();
  data->SetRunNumber(runID);
  G4String RunComment="8 core detectors";
  data->SetRunComment(RunComment);
  TString TgtShape = const_cast<ExperimentConstruction*>(static_cast<const ExperimentConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction()))->GetTargetShape();
  TString TgtMaterial = const_cast<ExperimentConstruction*>(static_cast<const ExperimentConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction()))->GetTargetMaterial();
  data->SetTargetShapeComment(TgtShape);
  data->SetTargetMaterialComment(TgtMaterial);

  //open output file
  fEventAction = const_cast<EventAction*>(static_cast<const EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));
  fEventAction->PrepareOutput();

  
}

//-----------------------------------------------------------------------------

void RunAction::EndOfRunAction(const G4Run* )
{ 
  data->FillRunTree();
  fEventAction->CloseOutput();
  fEventAction->PrintOutFileName();
  
  /*
  // G4int nEvnt = aRun->GetNumberOfEvent();
  G4cout << "End of RunAction" <<G4endl;

  //show Rndm status
  //  CLHEP::HepRandom::showEngineStatus();

  */
 
}

//-----------------------------------------------------------------------------



