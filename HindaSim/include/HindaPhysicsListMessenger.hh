
#ifndef HindaPhysicsListMessenger_h
#define HindaPhysicsListMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HindaPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;


class HindaPhysicsListMessenger : public G4UImessenger
{
public:
  HindaPhysicsListMessenger(HindaPhysicsList*);
  ~HindaPhysicsListMessenger();

  void SetNewValue(G4UIcommand*,G4String);


private:
  HindaPhysicsList* HindaList;
  G4UIdirectory* physDir;

  G4UIcmdWithAString* AddListCmd;
  G4UIcmdWithoutParameter* PrintListsCmd;
 
};

#endif
