#include "HadronicProcesses.hh"

#include "G4ProcessManager.hh"



// includes for hadrons
#include "G4LElastic.hh"
#include "G4HadronElasticProcess.hh"

// includes for protons
#include "G4ProtonInelasticProcess.hh"
#include "G4ProtonInelasticCrossSection.hh"
#include "G4LEProtonInelastic.hh"
#include "G4HEProtonInelastic.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4LEpp.hh"
#include "G4LEnp.hh"

// includes for deuteron
#include "G4DeuteronInelasticProcess.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4TripathiLightCrossSection.hh"
#include "G4BinaryLightIonReaction.hh"

// includes for triton
#include "G4TritonInelasticProcess.hh"
#include "G4LETritonInelastic.hh"

// includes for triton
#include "G4AlphaInelasticProcess.hh"
#include "G4LEAlphaInelastic.hh"

// includes for gamma
#include "G4PhotoNuclearProcess.hh"
#include "G4GammaNuclearReaction.hh"
#include "G4PhotoNuclearCrossSection.hh"

// includes for electron / positron
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"
#include "G4ElectroNuclearReaction.hh"

// includes for decay
#include "G4Decay.hh"

// includes for neutron
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronInelasticCrossSection.hh"
#include "G4LENeutronInelastic.hh"
#include "G4HENeutronInelastic.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4LCapture.hh"
#include "G4HadronFissionProcess.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4NeutronHPFission.hh"
#include "G4LFission.hh"

HadronicProcesses::HadronicProcesses()
{
  // This model is used by d, He3, and other ions:  hadron-nucleus elastic scattering
  // This model is good for all energies.
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4HadronElasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4LElastic.html
  hadronElasticProcess = new G4HadronElasticProcess();
  hadronElasticModel   = new G4LElastic(); 
  hadronElasticProcess->RegisterMe( hadronElasticModel );

}//END of constructor

HadronicProcesses::~HadronicProcesses()
{
}//END of destructor


void HadronicProcesses::AddAllHadronic()
{
  AddNeutronHadronicProcesses();
  AddProtonHadronicProcesses();
  AddDeuteronHadronicProcesses();
  AddTritonHadronicProcesses();
  AddHelium3HadronicProcesses();
  AddAlphaHadronicProcesses();
  AddGenericIonHadronicProcesses();

}

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddProtonHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Proton." << G4endl;

  // Get pointer to proton process manager.
  G4ProcessManager *protonProcessManager = G4Proton::Proton()->GetProcessManager();

  // Add/Register proton-nucleus elastic scattering process and models.
  protonProcessManager -> AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei:  All Energies" << G4endl;

  ////////////////////
  // Define inelastic scattering process and models
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4ProtonInelasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/low_energy_parameterized/G4LEProtonInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/high_energy_parameterized/G4HEProtonInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4ProtonInelasticCrossSection.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/Precompound.html
  G4ProtonInelasticProcess      *protonInelasticProcess      = new G4ProtonInelasticProcess();
  G4ProtonInelasticCrossSection *protonInelasticCrossSection = new G4ProtonInelasticCrossSection();               // Ep=0-20GeV
  G4PreCompoundModel            *protonPreCompoundModel      = new G4PreCompoundModel( new G4ExcitationHandler ); // Ep=0-170MeV
  G4LEProtonInelastic           *LEprotonInelasticModel      = new G4LEProtonInelastic();                         // Ep=0-25GeV
  G4HEProtonInelastic           *HEprotonInelasticModel      = new G4HEProtonInelastic();                         // Ep=20GeV-10TeV

  // Set active energy ranges for inelastic models.
  protonPreCompoundModel -> SetMinEnergy(     0.0*MeV );
  protonPreCompoundModel -> SetMaxEnergy(   170.0*MeV );
  LEprotonInelasticModel -> SetMinEnergy(   150.0*MeV );
  LEprotonInelasticModel -> SetMaxEnergy( 55000.0*MeV );
  HEprotonInelasticModel -> SetMinEnergy( 25000.0*MeV );

  // Add/Register inelastic scattering cross sections, process and models.
  // Note: AddDataSet adds the given cross section data set to the end of the
  //       list of data sets in the data store. Data sets added later to
  //       the list will have priority over those added earlier to the list.
  protonInelasticProcess -> AddDataSet( protonInelasticCrossSection );
  protonInelasticProcess -> RegisterMe( LEprotonInelasticModel );
  protonInelasticProcess -> RegisterMe( HEprotonInelasticModel );
  protonInelasticProcess -> RegisterMe( protonPreCompoundModel );
  protonProcessManager   -> AddDiscreteProcess( protonInelasticProcess );
  G4cout << "      -> Inelastic Scattering From Nuclei: 0 - 20 GeV" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddProtonHadronicProcesses()

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddDeuteronHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Deuteron." << G4endl;

  // Get pointer to deuteron process manager.
  G4ProcessManager *deuteronProcessManager = G4Deuteron::Deuteron()->GetProcessManager();

  // Add deuteron-nucleus elastic scattering process.
  deuteronProcessManager->AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: All Energies" << G4endl;

  ////////////////////
  // Define inelastic scattering process and models
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4DeuteronInelasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/low_energy_parameterized/G4LEDeuteronInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4TripathiLightCrossSection.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4BinaryLightIonReaction.html
  G4DeuteronInelasticProcess      *deuteronInelasticProcess    = new G4DeuteronInelasticProcess();
  G4LEDeuteronInelastic           *LEdeuteronInelasticModel    = new G4LEDeuteronInelastic();       // Ed=0-100MeV
  G4TripathiLightCrossSection     *tripathiLightCrossSection   = new G4TripathiLightCrossSection(); // Ed=0-5GeV
  G4BinaryLightIonReaction        *binaryLightIonReactionModel = new G4BinaryLightIonReaction();    // Ed=80MeV-5GeV

  // Set active energy ranges for inelastic models.
  LEdeuteronInelasticModel    -> SetMinEnergy(    0.0*MeV );
  LEdeuteronInelasticModel    -> SetMaxEnergy(  100.0*MeV );
  binaryLightIonReactionModel -> SetMinEnergy(   99.0*MeV );
  binaryLightIonReactionModel -> SetMaxEnergy( 5000.0*MeV );

  // Add/Register inelastic scattering cross sections, process and models.
  deuteronInelasticProcess -> AddDataSet( tripathiLightCrossSection );
  deuteronInelasticProcess -> RegisterMe( LEdeuteronInelasticModel );
  deuteronInelasticProcess -> RegisterMe( binaryLightIonReactionModel );
  deuteronProcessManager   -> AddDiscreteProcess( deuteronInelasticProcess );
  G4cout << "      -> Inelastic Scattering From Nuclei: 0 - 5 GeV" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddDeuteronHadronicProcesses()

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddTritonHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Triton." << G4endl;

  // Get pointer to triton process manager.
  G4ProcessManager *tritonProcessManager = G4Triton::Triton()->GetProcessManager();

  // Add triton-nucleus elastic scattering process.
  tritonProcessManager->AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: All Energies" << G4endl;

  ////////////////////
  // Define inelastic scattering process and models
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4TritonInelasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/low_energy_parameterized/G4LETritonInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4TripathiLightCrossSection.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4BinaryLightIonReaction.html
  G4TritonInelasticProcess      *tritonInelasticProcess      = new G4TritonInelasticProcess();
  G4LETritonInelastic           *LEtritonInelasticModel      = new G4LETritonInelastic();       // Ed=0-100MeV
  G4TripathiLightCrossSection   *tripathiLightCrossSection   = new G4TripathiLightCrossSection(); // Ed=0-5GeV
  G4BinaryLightIonReaction      *binaryLightIonReactionModel = new G4BinaryLightIonReaction();    // Ed=80MeV-5GeV

  // Set active energy ranges for inelastic models.
  LEtritonInelasticModel      -> SetMinEnergy(    0.0*MeV );
  LEtritonInelasticModel      -> SetMaxEnergy(  100.0*MeV );
  binaryLightIonReactionModel -> SetMinEnergy(   99.0*MeV );
  binaryLightIonReactionModel -> SetMaxEnergy( 5000.0*MeV );

  // Add/Register inelastic scattering cross sections, process and models.
  tritonInelasticProcess -> AddDataSet( tripathiLightCrossSection );
  tritonInelasticProcess -> RegisterMe( LEtritonInelasticModel );
  tritonInelasticProcess -> RegisterMe( binaryLightIonReactionModel );
  tritonProcessManager   -> AddDiscreteProcess( tritonInelasticProcess );
  G4cout << "      -> Inelastic Scattering From Nuclei: 0 - 5 GeV" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddTritonHadronicProcesses()

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddHelium3HadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Helium-3." << G4endl;

  // Get pointer to helium-3 process manager.
  G4ProcessManager *helium3ProcessManager = G4He3::He3()->GetProcessManager();

  // Add helium3-nucleus elastic scattering process.
  helium3ProcessManager->AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: All Energies" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddHelium3HadronicProcesses()

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddAlphaHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Alpha." << G4endl;

  // Get pointer to alpha process manager.
  G4ProcessManager *alphaProcessManager = G4Alpha::Alpha()->GetProcessManager();

  // Add alpha-nucleus elastic scattering process.
  alphaProcessManager->AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: All Energies" << G4endl;

  ////////////////////
  // Define inelastic scattering process and models
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4AlphaInelasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/low_energy_parameterized/G4LEAlphaInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4TripathiLightCrossSection.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4BinaryLightIonReaction.html
  G4AlphaInelasticProcess      *alphaInelasticProcess        = new G4AlphaInelasticProcess();
  G4LEAlphaInelastic           *LEalphaInelasticModel        = new G4LEAlphaInelastic();          // Ed=0-100MeV
  G4TripathiLightCrossSection   *tripathiLightCrossSection   = new G4TripathiLightCrossSection(); // Ed=0-5GeV
  G4BinaryLightIonReaction      *binaryLightIonReactionModel = new G4BinaryLightIonReaction();    // Ed=80MeV-5GeV

  // Set active energy ranges for inelastic models.
  LEalphaInelasticModel       -> SetMinEnergy(    0.0*MeV );
  LEalphaInelasticModel       -> SetMaxEnergy(  100.0*MeV );
  binaryLightIonReactionModel -> SetMinEnergy(   99.0*MeV );
  binaryLightIonReactionModel -> SetMaxEnergy( 5000.0*MeV );

  // Add/Register inelastic scattering cross sections, process and models.
  alphaInelasticProcess -> AddDataSet( tripathiLightCrossSection );
  alphaInelasticProcess -> RegisterMe( LEalphaInelasticModel );
  alphaInelasticProcess -> RegisterMe( binaryLightIonReactionModel );
  alphaProcessManager   -> AddDiscreteProcess( alphaInelasticProcess );
  G4cout << "      -> Inelastic Scattering From Nuclei: 0 - 5 GeV" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddAlphaHadronicProcesses()

/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddGenericIonHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Generic Ion." << G4endl;

  // Get pointer to helium-3 process manager.
  G4ProcessManager *ionProcessManager = G4GenericIon::GenericIon()->GetProcessManager();

  // Add ion-nucleus elastic scattering process.
  ionProcessManager->AddDiscreteProcess( hadronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: All Energies" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddGenericIonHadronicProcesses()


/////////////////////////////////////////////////////////////////////////////////////
void HadronicProcesses::AddNeutronHadronicProcesses(void)
{
  G4cout << "----------" << G4endl;
  G4cout << "   Adding Processes:" << G4endl;
  G4cout << "    For Neutron." << G4endl;

  // Get pointer to neutron process manager.
  G4ProcessManager *neutronProcessManager = G4Neutron::Neutron()->GetProcessManager();

  ////////////////////
  // Define neutron-nucleus ELASTIC scattering process.
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4HadronElasticProcess.html
  G4HadronElasticProcess *neutronElasticProcess    = new G4HadronElasticProcess();
  // Define neutron-nucleus elastic scattering model.
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4NeutronHPElastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4LElastic.html
  G4NeutronHPElastic     *neutronHPElasticModel    = new G4NeutronHPElastic();     // En=0-20MeV
  G4NeutronHPElasticData *neutronHPElasticData     = new G4NeutronHPElasticData();
  G4LElastic             *neutronLElasticModel     = new G4LElastic();             // All Energies

  // Set active energy ranges for elastic models.
  neutronHPElasticModel    -> SetMinEnergy(    0.0*MeV );
  neutronHPElasticModel    -> SetMaxEnergy(   20.0*MeV );
  neutronLElasticModel     -> SetMinEnergy(   19.9*MeV );
  neutronLElasticModel     -> SetMaxEnergy( 3500.0*MeV ); // Max set to 3.5 GeV. Matches gamma max.

  // Add/Register inelastic scattering cross sections, process and models.
  neutronElasticProcess -> AddDataSet( neutronHPElasticData );
  neutronElasticProcess -> RegisterMe( neutronHPElasticModel );
  neutronElasticProcess -> RegisterMe( neutronLElasticModel );
  neutronProcessManager -> AddDiscreteProcess( neutronElasticProcess );
  G4cout << "      -> Elastic Scattering From Nuclei: 0 - 3.5 GeV" << G4endl;

  ////////////////////
  // Define neutron-nucleus INELASTIC scattering process and models.
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4NeutronInelasticProcess.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4NeutronHPInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4NeutronHPInelasticData.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/cross_sections/G4NeutronInelasticCrossSection.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/Precompound.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/low_energy_parameterized/G4LENeutronInelastic.html
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/high_energy_parameterized/G4HENeutronInelastic.html
  G4NeutronInelasticProcess      *neutronInelasticProcess      = new G4NeutronInelasticProcess();
  G4NeutronHPInelasticData       *neutronHPInelasticData       = new G4NeutronHPInelasticData();                     // En=0-20MeV
  G4NeutronHPInelastic           *neutronHPInelasticModel      = new G4NeutronHPInelastic();                         // En=0-20MeV
  G4NeutronInelasticCrossSection *neutronInelasticCrossSection = new G4NeutronInelasticCrossSection();               // En=14MeV-20GeV
  G4PreCompoundModel             *neutronPreCompoundModel      = new G4PreCompoundModel(new G4ExcitationHandler); // En=0-170MeV
  G4LENeutronInelastic           *LEneutronInelasticModel      = new G4LENeutronInelastic();                         // En=0-25GeV
  G4HENeutronInelastic           *HEneutronInelasticModel      = new G4HENeutronInelastic();                         // En=20GeV-10TeV

  // Set active energy ranges for inelastic models.
  neutronHPInelasticModel     -> SetMinEnergy(     0.0*MeV );
  neutronHPInelasticModel     -> SetMaxEnergy(    20.0*MeV );
  neutronPreCompoundModel     -> SetMinEnergy(    19.9*MeV );
  neutronPreCompoundModel     -> SetMaxEnergy(   170.0*MeV );
  LEneutronInelasticModel     -> SetMinEnergy(   150.0*MeV );
  LEneutronInelasticModel     -> SetMaxEnergy( 55000.0*MeV );
  HEneutronInelasticModel     -> SetMinEnergy( 25000.0*MeV );

  // Add/Register inelastic scattering cross sections, process and models.
  // Note: AddDataSet adds the given cross section data set to the end of the
  //       list of data sets in the data store. Data sets added later to
  //       the list will have priority over those added earlier to the list.
  neutronInelasticProcess -> AddDataSet( neutronInelasticCrossSection );
  neutronInelasticProcess -> AddDataSet( neutronHPInelasticData );
  neutronInelasticProcess -> RegisterMe( LEneutronInelasticModel );
  neutronInelasticProcess -> RegisterMe( HEneutronInelasticModel );
  neutronInelasticProcess -> RegisterMe( neutronPreCompoundModel );
  neutronInelasticProcess -> RegisterMe( neutronHPInelasticModel );
  neutronProcessManager   -> AddDiscreteProcess( neutronInelasticProcess );
  G4cout << "      -> Inelastic Scattering From Nuclei: 0 - 10 TeV" << G4endl;

  ////////////////////
  // Define neutron CAPTURE process and models.
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4HadronCaptureProcess.html
  // The link for G4NeutronHPCaptureData is broken.
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4LCapture.html
  G4HadronCaptureProcess *neutronCaptureProcess    = new G4HadronCaptureProcess();
  G4NeutronHPCaptureData *neutronHPCaptureData     = new G4NeutronHPCaptureData();
  G4NeutronHPCapture     *neutronHPCaptureModel    = new G4NeutronHPCapture();     // En=0-20MeV
  G4LCapture             *neutronLCaptureModel     = new G4LCapture();             // All Energies

  // Set active energy ranges for capture models.
  neutronHPCaptureModel    -> SetMinEnergy(     0.0*MeV );
  neutronHPCaptureModel    -> SetMaxEnergy(    20.0*MeV );
  neutronLCaptureModel     -> SetMinEnergy(    19.9*MeV );
  neutronLCaptureModel     -> SetMaxEnergy(  3500.0*MeV );

  // Add/Register capture cross sections, process, and models.
  neutronCaptureProcess -> AddDataSet( neutronHPCaptureData );
  neutronCaptureProcess -> RegisterMe( neutronLCaptureModel );
  neutronCaptureProcess -> RegisterMe( neutronHPCaptureModel );
  neutronProcessManager -> AddDiscreteProcess( neutronCaptureProcess );
  G4cout << "      -> Neutron Capture: 0 - 3.5 GeV" << G4endl;

  ////////////////////
  // Define neutron-induced FISSION process and models.
  ////////////////////
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/processes/hadronic/G4HadronFissionProcess.html
  // The link for G4NeutronHPFissionData is broken.
  // http://geant4.web.cern.ch/geant4/support/proc_mod_catalog/models/hadronic/G4LFission.html
  G4HadronFissionProcess *neutronFissionProcess    = new G4HadronFissionProcess();
  G4NeutronHPFissionData *neutronHPFissionData     = new G4NeutronHPFissionData();
  G4NeutronHPFission     *neutronHPFissionModel    = new G4NeutronHPFission();     //En=0-20MeV
  G4LFission             *neutronLFissionModel     = new G4LFission();             // All Energies

  // Set active energy ranges for fission models.
  neutronHPFissionModel    -> SetMinEnergy(     0.0*MeV );
  neutronHPFissionModel    -> SetMaxEnergy(    20.0*MeV );
  neutronLFissionModel     -> SetMinEnergy(    19.9*MeV );
  neutronLFissionModel     -> SetMaxEnergy(  3500.0*MeV );

  // Add/Register fisson cross sections, process, and models.
  neutronFissionProcess -> AddDataSet( neutronHPFissionData );
  neutronFissionProcess -> RegisterMe( neutronLFissionModel );
  neutronFissionProcess -> RegisterMe( neutronHPFissionModel );
  neutronProcessManager -> AddDiscreteProcess( neutronFissionProcess );
  G4cout << "      -> Neutron-Induced Fisson: 0 - 3.5 GeV" << G4endl;

  G4cout << "   End Add." << G4endl;
  G4cout << "----------" << G4endl;

}//END of AddNeutronHadronicProcesses()

