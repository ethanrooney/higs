
#ifndef EventActionMessenger_h
#define EventActionMessenger_h 1


#include "globals.hh"
#include "G4UImessenger.hh"


class EventAction;
class G4UIdirectory;
class G4UIcmdWithAString;


class EventActionMessenger: public G4UImessenger
{

public:
  EventActionMessenger(EventAction* EvAct);
  ~EventActionMessenger();

  void SetNewValue(G4UIcommand* command, G4String newValue);

private:
  EventAction* fEventAction;
  G4UIdirectory* fEventDir;
  G4UIcmdWithAString* fOutFileCmd;


};

#endif
