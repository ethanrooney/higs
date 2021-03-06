
#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;



class PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction* );
  ~PrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);


private:
  PrimaryGeneratorAction* HindaAction;
  G4UIdirectory* gunDir;

  G4UIcmdWithAnInteger*      SetModeCmd;
  G4UIcmdWithADoubleAndUnit* SetDiameterCmd;
  G4UIcmdWithADoubleAndUnit* SetTminCmd;
  G4UIcmdWithADoubleAndUnit* SetTmaxCmd;
  G4UIcmdWithADoubleAndUnit* SetThetaMinCmd;
  G4UIcmdWithADoubleAndUnit* SetThetaMaxCmd;
  G4UIcmdWithADoubleAndUnit* SetPhiMinCmd;
  G4UIcmdWithADoubleAndUnit* SetPhiMaxCmd;

};

#endif
