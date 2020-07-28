//Created by S. Henshaw 3/26/10
//Mostly Copied from geant4/examples/novice/NO2

class SteppingVerbose;

#ifndef SteppingVerbose_h
#define SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingVerbose : public G4SteppingVerbose 
{
 public:
   
  SteppingVerbose();
 ~SteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
