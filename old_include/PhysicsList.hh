#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
//#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//class PhysicsList: public G4VModularPhysicsList
class PhysicsList: public G4VUserPhysicsList
{
  public:
    PhysicsList();
    ~PhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

}; //END of class PhysicsList

#endif
