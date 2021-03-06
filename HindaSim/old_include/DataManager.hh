/*********************************************************************
Created by S. Henshaw 4/6/10

This is a Singleton class which is used to parse hit,track,and step data
from the Run.  It is accessed by RunAction, EventAction, HINDASD's process hits.


*********************************************************************/

#ifndef DataManager_h
#define DataManager_h 1

#include "globals.hh"
#include "TString.h"
#include "TTree.h"
#include <map>

class TTree;
class TFile;
class TString;
class HINDAArray;

class DataManager 
{
  /*****Needed for Singleton Class Type*******/
public:
    static DataManager* GetInstance();

private:
  DataManager():fOutFile(NULL), fRunTree(NULL), fEventTree(NULL) {};
  DataManager(DataManager const& ); //not defined, not copyable
  DataManager& operator= (DataManager const& ); //not defined, not assignable
  ~DataManager();
  /*******************************************/

private:
  //Variables for File and trees
  TFile*       fOutFile; 
  TTree*       fRunTree;
  TTree*       fEventTree;

private:
  //Variables for RunTree
  G4int        fRunNumber;
  Char_t       fRunComment[100];
  Char_t       fTargetShape[100];
  Char_t       fTargetMaterialName[100];
  G4float      fWorldLengthX;
  G4float      fWorldLengthY;
  G4float      fWorldLengthZ;

  G4int        fNumSensitiveVols;
  G4String*    fSensitiveLogVolName;
private:
  //Variables for Event Tree
  static const G4int fMaxNDets=10;

  Char_t       fEventName[100];
  G4double     fEventNumber;
  G4int        fPrimaryTrackID;
  Char_t       fPrimaryParticleName[100];
  G4float      fPrimaryParticleKineticEnergy;    
  G4float      fPrimaryParticleTheta;      
  G4float      fPrimaryParticlePhi;
  G4float      fPrimaryParticleX;
  G4float      fPrimaryParticleY;
  G4float      fPrimaryParticleZ;

  std::map<TString,Double_t> fEnergyDep; 

public:
  void InitializeEvent();
  void SetOutputFile(TFile* f);
  void SetBranches();
  
public:
  void SetRunNumber(G4int Run){fRunNumber=Run;};
  void SetRunComment(TString Comment) {sprintf(fRunComment,"%s",Comment.Data());};
  void SetTargetShapeComment(TString TgtShape){sprintf(fTargetShape,"%s",TgtShape.Data());};
  void SetTargetMaterialComment(TString TgtMaterial){sprintf(fTargetMaterialName,"%s",TgtMaterial.Data());};
  void WriteTrees(){fRunTree->Write();fEventTree->Write();};
public:
  
  inline void SetWorldLengthX(G4float x) {fWorldLengthX=x;};
  inline void SetWorldLengthY(G4float y) {fWorldLengthY=y;};
  inline void SetWorldLengthZ(G4float z) {fWorldLengthZ=z;};

  inline void SetNumSensitiveVols(G4int Num) {fNumSensitiveVols=Num;};
  inline G4int GetNumSensitiveVols(void) {return fNumSensitiveVols;};
  inline void SetSensitiveLogVolNames(G4String* Name) {fSensitiveLogVolName=Name;};
  
public:
  inline void SetEventName(TString Name) {sprintf(fEventName,"%s",Name.Data());};
  inline void SetPrimaryParticleName(TString Name) {sprintf(fPrimaryParticleName,"%s",Name.Data());};
  inline void SetEventNumber(G4double Num)   {fEventNumber=Num;};
  inline void SetPrimaryTrackID(G4int ID) {fPrimaryTrackID=ID;};
  inline void SetPrimaryParticleKineticEnergy(G4float E) {fPrimaryParticleKineticEnergy=E;};
  inline void SetPrimaryParticleTheta(G4float Theta) {fPrimaryParticleTheta=Theta;};
  inline void SetPrimaryParticlePhi(G4float Phi) {fPrimaryParticlePhi=Phi;};
  inline void SetPrimaryParticleX(G4float Xpos) {fPrimaryParticleX=Xpos;};
  inline void SetPrimaryParticleY(G4float Ypos) {fPrimaryParticleY=Ypos;};
  inline void SetPrimaryParticleZ(G4float Zpos) {fPrimaryParticleZ=Zpos;};

public:
  inline void SetEnergyDeposited(TString LogVolName, Double_t val) {fEnergyDep[LogVolName]=val;};
  inline void AddEnergyDeposited(TString LogVolName, Double_t val) {fEnergyDep[LogVolName]+=val;};

public:
  inline void FillRunTree(void) {fRunTree->Fill();};
  inline void FillEventTree(void) {fEventTree->Fill();};

};

namespace
{ struct ForceSingletonInitialization
  { ForceSingletonInitialization() { DataManager::GetInstance(); } } GetInstance;
}

#endif
