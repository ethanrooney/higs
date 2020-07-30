#include "PhysicsList.hh"
#include "AllParticles.hh"
#include "AllProcesses.hh"

#include "G4ParticleTypes.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"

PhysicsList::PhysicsList()
 :
  G4VUserPhysicsList()
{
  G4cout << "Instance of PhysicsList Constructed!" << G4endl;

}//END of constructor

PhysicsList::~PhysicsList()
{
}//END of destructor

void PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  AllParticles::ConstructAllParticles();

}//END of ConstructParticle()

void PhysicsList::ConstructProcess()
{
  // Define transportation process: this is always needed.
  AddTransportation();

  // Define pointer to AllProcesses object.
  AllProcesses *processAdder = new AllProcesses;

  // Add desired processes.

  //For good NaI response to gamma's use
  processAdder -> AddDecayProcesses();
  processAdder -> AddStandardEMProcesses();


  //To look at Neutron effects on NaI Detectors
//  processAdder -> AddProtonHadronicProcesses();
//  processAdder -> AddDeuteronHadronicProcesses();
//  processAdder -> AddTritonHadronicProcesses();
//  processAdder -> AddHelium3HadronicProcesses();
//  processAdder -> AddAlphaHadronicProcesses();
//  processAdder -> AddGenericIonHadronicProcesses();
//  processAdder -> AddPhotonuclearProcesses();//These Make much slower
//  processAdder -> AddElectronuclearProcesses();
//  processAdder -> AddNeutronHadronicProcesses();//These Make much slower

}//END of ConstructProcess()

void PhysicsList::SetCuts()
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

