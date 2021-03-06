#ifndef HadronicProcesses_h
#define HadronicProcesses_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//includes for hadronic elastic scattering processes
#include "G4LElastic.hh"
#include "G4HadronElasticProcess.hh"

//#include "He3PhotodisintegrationCrossSection.hh"
//#include "He3Photodisintegration.hh"

class HadronicProcesses : public G4VPhysicsConstructor
{
  public:

    HadronicProcesses();
    ~HadronicProcesses();
    virtual void ConstructParticle() {}; //dummy method
    virtual void ConstructProcess() {};  //dummy method
  
    void AddAllHadronic();
    void AddProtonHadronicProcesses(void);
    void AddDeuteronHadronicProcesses(void);
    void AddTritonHadronicProcesses(void);
    void AddHelium3HadronicProcesses(void);
    void AddAlphaHadronicProcesses(void);
    void AddGenericIonHadronicProcesses(void);
    void AddNeutronHadronicProcesses(void);

  private:

    // The elastic model and process below are initialized in the constructor.
    G4LElastic *hadronElasticModel; // This model is used by many different particles:
                                    // hadron--nucleus elastic scattering
    G4HadronElasticProcess *hadronElasticProcess;

};//END of class HadronicProcesses

#endif

