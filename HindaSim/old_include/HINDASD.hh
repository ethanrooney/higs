

#ifndef HINDASD_h
#define HINDASD_h 1

#include "G4VSensitiveDetector.hh"


class G4Step;
class G4Track;
class DataManager;

//-----------------------------------------------------------------------------

class HINDASD : public G4VSensitiveDetector
{
public:
  HINDASD(G4String name);
  virtual ~HINDASD();
  
  virtual void Initialize(G4HCofThisEvent*);
  virtual G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*);
  virtual void EndOfEvent(G4HCofThisEvent* );
  
  virtual void DrawHit(G4ThreeVector position);

private:
  G4String fClassName;
  G4String fMethodName;
  G4bool fTrackIsNew;
  G4int Nsteps_per_track;

private:
  //  std::map<TString,TString> fBranchName;//To access this fBranchName[TString LogVolName] returns Branch Name


private:
  DataManager* data;
};

//-----------------------------------------------------------------------------

#endif

