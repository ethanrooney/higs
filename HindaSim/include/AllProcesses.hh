#ifndef AllProcesses_h
#define AllProcesses_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//includes for hadronic elastic scattering processes
//#include "G4LElastic.hh"
#include "G4HadronElastic.hh"
#include "G4HadronElasticProcess.hh"

//#include "He3PhotodisintegrationCrossSection.hh"
//#include "He3Photodisintegration.hh"

class AllProcesses : public G4VPhysicsConstructor
{
  public:

    AllProcesses();
    ~AllProcesses();
    virtual void ConstructParticle() {}; //dummy method
    virtual void ConstructProcess() {};  //dummy method
    void AddStandardEMProcesses(void);
    void AddProtonHadronicProcesses(void);
    void AddDeuteronHadronicProcesses(void);
    void AddTritonHadronicProcesses(void);
    void AddHelium3HadronicProcesses(void);
    void AddAlphaHadronicProcesses(void);
    void AddGenericIonHadronicProcesses(void);
    void AddPhotonuclearProcesses(void);
    void AddElectronuclearProcesses(void);
    void AddDecayProcesses(void);
    void AddNeutronHadronicProcesses(void);

  private:

    // The elastic model and process below are initialized in the constructor.
    G4HadronElastic *hadronElasticModel; // This model is used by many different particles:
                                    // hadron--nucleus elastic scattering
    G4HadronElasticProcess *hadronElasticProcess;

};//END of class AllProcesses

#endif

