
#ifndef HindaPhysicsList_h
#define HindaPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "HindaPhysicsListMessenger.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class HindaPhysicsMessenger;

class HindaPhysicsList: public G4VUserPhysicsList
{
public:
  HindaPhysicsList();
  virtual ~HindaPhysicsList();

  void ConstructParticle();
  void ConstructProcess();
  void SetCuts();
  void SetBuilderList0(G4bool flagHP);
  void AddList(const G4String& name);
  void Print();

private:
  HindaPhysicsListMessenger* fListMessenger;
  G4VPhysicsConstructor* emPhysicsList;
  G4VPhysicsConstructor* particleList;
  std::vector<G4VPhysicsConstructor*> hadronPhys;
 

};

#endif
