
#ifndef HINDACore_H
#define HINDACore_H 1


#include <vector>
//#include <string>
#include "globals.hh"
#include "G4PVPlacement.hh"

class G4Tubs;
class G4Polycone;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4AssemblyVolume;
class G4UserLimits;
class AllMaterials;

class HINDASD;


typedef std::vector<G4VPhysicalVolume*>::iterator VolumesIterator;

class HINDACore{

public:
  //HINDACore(G4String CoreName);
  HINDACore(G4String CoreName, G4double height, G4double gap);  //Added LSM 05-19-11
  ~HINDACore();
  void PlaceCoreAssembly(G4LogicalVolume* logicMother,G4Transform3D Transform);
  inline G4AssemblyVolume* GetCoreAssemblyVolume(void) {return CoreAssembly;};
  inline G4LogicalVolume* GetCoreNaILogicalVolume(void) {return logic_NaI;};
  inline G4String         GetCoreName(void)  {return fCoreName;};

private:
  HINDASD *HINDASDPtr;
  G4int fNumSensitiveVols;
  G4String fSensitiveLogVolName[1];
  G4bool IsCoreSensitive;

public:
  inline G4int GetNumSensitiveVols(void)    {return fNumSensitiveVols;};
  inline G4String* GetSensitiveLogVolNames(void)    {return fSensitiveLogVolName;};


private:

  //Logical Volumes contained in Assembly(If you add a Logical Volume you must add it to LogVolNames")
  G4LogicalVolume* logic_CorePMT;
  G4LogicalVolume* logic_CoreCan;
  G4LogicalVolume* logic_QuartzWindow;
  G4LogicalVolume* logic_NaI;

  G4AssemblyVolume* CoreAssembly;//Holds NaI +PMT+Al can center is at center of NaI Crystal

private:
  G4String fClassName;
  G4String fMethodName;
  G4String fCoreName;

private:
  //Methods to Build and Assemble
  //void SetDimensions();
  void SetDimensions(G4double height, G4double gap);  //Added LSM 05-19-11
  void BuildCore();
  void BuildPMT();
  void AssembleParts();
  void MakeSensitive();

  //Visualization methods
  void SetVisAtt();

private:
  //Dimensions of Al shell around Crystal
  G4double CanThickness;
  G4double CanShellOuterDiameter;
  G4double CanShellOuterRadius;
  G4double CanShellInnerRadius;
  G4double CanShellHeight;
  G4double CanShellHalfHeight;

  //Dimesions Al Front Cover of Core Detector
  G4double CanFrontThickness;
  G4double CanFrontRadius;
  G4double CanFrontHalfHeight;

  //Dimension of Al Back Plate (with Quartz window)
  G4double BackPlateThickness;
  G4double BackPlateRadius;
  G4double BackPlateQuartzRadius;
  G4double BackPlateHalfHeight;
  
  //Dimensions of NaI Crystal
  G4double NaIDiameter;
  G4double NaIRadius;
  G4double NaILength;
  G4double NaIHalfHeight;

  G4double Offset;

  //Start and Span Angles for Revolution of Tubs of Core Crystal and Can
  G4double StartAngle;
  G4double SpanAngle;

  //Dimensions for PMT's
  static const G4int NumCorePMTs=7;
  static const G4int CorePMTNPlanesZ=6;
  static const G4double CorePMTInnerR[];
  static const G4double CorePMTOuterR[];
  static const G4double CorePMTZPlanes[];

};
 
#endif

