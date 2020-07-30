
#include "HindaPhysicsList.hh"
#include "HindaPhysicsListMessenger.hh"
#include "G4ProcessManager.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"



HindaPhysicsList::HindaPhysicsList()
{
  //messenger
  fListMessenger = new HindaPhysicsListMessenger(this);

  //particles
  particleList = new G4DecayPhysics("decays");

  //standard EM physics
  emPhysicsList = new G4EmStandardPhysics();
 
}


HindaPhysicsList::~HindaPhysicsList()
{
  delete fListMessenger;
  delete particleList;
  delete emPhysicsList;
  for(size_t i=0;i<hadronPhys.size();i++){
    delete hadronPhys[i];
  }

}


void HindaPhysicsList::ConstructParticle()
{
  particleList->ConstructParticle();
}


void HindaPhysicsList::ConstructProcess()
{
  AddTransportation();
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  for(size_t i=0;i<hadronPhys.size();i++){
    hadronPhys[i]->ConstructProcess();
  }

}



void HindaPhysicsList::SetCuts()
{
  G4cout << "----------" << G4endl;
  G4cout << "   Setting Cuts:" << G4endl;

  // suppress error messages even in case e/gamma/proton do not exist            
  G4int oldVerboseLevel = GetVerboseLevel();
  SetVerboseLevel(2);
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  defaultCutValue = 0.7*mm;
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(oldVerboseLevel);  

  G4cout << "   End Set." << G4endl;
  G4cout << "----------" << G4endl;

}//END of SetCuts()



void HindaPhysicsList::AddList(const G4String& name)
{
  if(verboseLevel>0)
    G4cout << "HindaPhysicsList::AddPhysicsList: <" << name << ">" << G4endl;

  if(name == "ExtraEM")
    hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));

  else if(name == "QGSP_BIC_HP") {
    hadronPhys.push_back( new HadronPhysicsQGSP_BIC_HP("hadrons",true));
    SetBuilderList0(true);
  }
 
}


void HindaPhysicsList::SetBuilderList0(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronElasticPhysics("elastic",verboseLevel,flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));


}


void HindaPhysicsList::Print()
{
  G4cout << "--- Available physics lists (argument):\n";
  G4cout << "EmExtraPhysics (ExtraEM)" << G4endl;
  G4cout << "QGSP_BIC_HP (QGSP_BIC_HP)" << G4endl;
}
