/*********************************************************************
Created by S. Henshaw 4/1/10


*********************************************************************/

#ifndef HINDAArray_H
#define HINDAArray_H 1


#include <vector>
//#include <string>
#include "globals.hh"
#include "G4PVPlacement.hh"

#include "TString.h"
#include <map>


class G4Tubs;
class G4Polycone;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4AssemblyVolume;
class G4UserLimits;
class AllMaterials;
class HINDACore;
class HINDAShield;
class TString;

typedef std::vector<G4VPhysicalVolume*>::iterator VolumesIterator;

class HINDAArray{

protected:
  

private:
  static const G4int fMaxNDets=10;
  HINDACore* CoreAssembly[fMaxNDets];
  HINDAShield* ShieldAssembly[fMaxNDets];
  G4AssemblyVolume *HINDA[fMaxNDets];//center is at center of Core NaI crystal
  G4AssemblyVolume *ArrayAssembly;

public:
  //  HINDAArray();//Build Default Array with 8 Detectors
  //  HINDAArray(G4int NumDets);//Build Array with NumDets Detectors and use Default Name List
  HINDAArray(G4int NumDets,G4String CoreName[], G4String ShieldName[],G4double RList[], G4double ThetaList[], G4double PhiList[]);//Build array using the inputs
  ~HINDAArray();
 


private:
  //Builds the HINDA Assemblies (Builds Core and Shield Assemblies and places them in HINDA Assembly)
  void BuildHINDA(G4int DetNum);

  //Builds Array Assembly and Places HINDA Assemblies in it
  void BuildArray();



public:
  void PlaceArray(G4LogicalVolume* logicMother,G4Transform3D Transform);

  void PlaceAShield(G4int DetNum, G4LogicalVolume* logicMother,G4Transform3D Transform);
  void PlaceACore(G4int DetNum, G4LogicalVolume* logicMother,G4Transform3D Transform);

  void PlaceAShield(G4int DetNum, G4LogicalVolume* logicMother,G4RotationMatrix rot, G4ThreeVector pos);
  void PlaceACore(G4int DetNum, G4LogicalVolume* logicMother,G4RotationMatrix rot, G4ThreeVector pos);

private:
  G4String fClassName;
  G4String fMethodName;

private:
  G4int fNumDets;
  static const G4String fDefaultCoreName[];
  static const G4String fDefaultShieldName[];

  G4String* fCoreSensitiveLogVolName;
  G4String* fShieldSensitiveLogVolName;
  G4String fHINDAArraySensitiveLogVolName[fMaxNDets*9];

public:
  G4int fNumSensitiveVols;
  inline G4int GetNumHINDAs(void) {return fNumDets;};
  inline G4int GetNumSensitiveVols(void) {return fNumSensitiveVols;};
  inline G4String* GetSensitiveLogVolNames(void) {return fHINDAArraySensitiveLogVolName;}; 
private:
  G4String fCoreName[fMaxNDets];
  G4String fShieldName[fMaxNDets];
  G4double fCoreR[fMaxNDets];
  G4double fCoreTheta[fMaxNDets];
  G4double fCorePhi[fMaxNDets];
  G4ThreeVector fDetAngle[fMaxNDets];
  G4ThreeVector fDetPos[fMaxNDets];
  G4RotationMatrix *fDetRot[fMaxNDets];
  G4Transform3D transHINDA[fMaxNDets];

};
#endif
