

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "EventAction.hh"
#include "ExperimentConstruction.hh"
#include "globals.hh"

//------------------------------------------------------------------------------

class G4Run;
class DataManager;

class RunAction : public G4UserRunAction
{
public:
  RunAction();
  ~RunAction();
  
public:
  virtual void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  
private:
  DataManager* data;
  EventAction* fEventAction;
  ExperimentConstruction* fExperimentConstruction;

};

//------------------------------------------------------------------------------

#endif





