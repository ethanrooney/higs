
#ifndef HINDAShield_H
#define HINDAShield_H 1


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

class HINDAShield{

public:
  HINDAShield(G4String Name);
  ~HINDAShield();
  void PlaceShieldAssembly(G4LogicalVolume* logicMother,G4Transform3D Transform);
  inline G4AssemblyVolume* GetShieldAssemblyVolume(void) {return ShieldAssembly;};

public:
  inline G4int GetNumSegments(void) {return NumSegments;};
  inline G4LogicalVolume* GetShieldNaILogicalVolume(G4int NumSegment) {return logic_NaI[NumSegment];};
  inline G4String GetShieldName(void) {return fShieldName;};

private:
  static const G4int NumSegments=8;
  //static const G4int NumSegments=8+2;
  HINDASD *HINDASDPtr;
  G4int fNumSensitiveVols;
  G4String fSensitiveLogVolName[NumSegments];
  //G4String fSensitiveLogVolName[NumSegments+2];  //To read out Pb and wax  //Added LSM 05-20-11
  G4bool IsShieldSensitive;

public:
  inline G4int GetNumSensitiveVols(void)    {return fNumSensitiveVols;};
  inline G4String* GetSensitiveLogVolNames(void)    {return fSensitiveLogVolName;};



private:

  //Logical Volumes contained in Assembly(If you add a Logical Volume you must add it to LogVolNames")
  G4LogicalVolume* logic_ShieldPMT;
  G4LogicalVolume* logic_NaI[NumSegments];
  G4LogicalVolume* logic_TeflonLiner;
  G4LogicalVolume* logic_SiliconeLiner;
  G4LogicalVolume* logic_AlLiner;
  G4LogicalVolume* logic_AlRim;
  G4LogicalVolume* logic_PbColl;
  G4LogicalVolume* logic_WaxInsert;


  //logical Volume of Assembly
  G4AssemblyVolume* ShieldAssembly;//full Shield Assembly (Center is at center of NaI crystals)
  G4AssemblyVolume* NaISegmentAssembly;//Just assembly of NaICrystals
private:
  //Methods to Build and Assemble
  void SetDimensions();
  void BuildShieldSegment();
  void BuildPMT();
  void AssembleShieldSegments();
  void BuildTeflonLiner();
  void BuildSiliconeLiner();
  void BuildAlCan();
  void BuildPbShield();
  void AssembleParts();
  void MakeSensitive();

  //Visualization methods
  void SetVisAtt();

private:
  G4String fClassName;
  G4String fMethodName;
  G4String fShieldName;

private:
  //Start and Span Angles for Revolution of Tubs of Shield
  G4double StartAngle;
  G4double SpanAngle;


  //Dimensions of NaI Crystals (From Aram's code which I think is from St. Gobain)
  G4double fNaIInnerR;
  G4double fNaIOuterR;
  G4double fNaIHalfHeight;
  G4double fNaISpanAngle;

  //Dimensions for Teflon Liner of NaI (Will be defined by G4Subtraction Solid with NaI)
  G4double fTeflonThickness;
  G4double fTeflonInnerMostR;
  G4double fTeflonOuterMostR;
  G4double fTeflonHalfHeight;

  //Dimensions for Silicone Liner of NaI (Will be defined by G4Subtraction Solid with Teflon house)
  G4double fSiliconeThickness;
  G4double fSiliconeInnerMostR;
  G4double fSiliconeOuterMostR;
  G4double fSiliconeHalfHeight;

  //Dimensions for Al Liner of NaI (Will be defined by G4Subtraction Solid with NaI Silicone house)
  G4double fAlThickness;
  G4double fAlInnerMostR;
  G4double fAlOuterMostR;
  G4double fAlHalfHeight;

  G4double fAlRimThicknessZ;
  G4double fAlRimThicknessR;
  G4double fAlRimInnerR;
  G4double fAlRimOuterR;
  G4double fAlRimHalfHeight;
  
  //Dimensions for Lead Shield
  G4double fPbShieldThickness;
  G4double fPbShieldHalfHeight;
  G4double fConeHeight;//Distance from Target to back face of Core (To Determine opening angle of collimation)
  G4double fCoreRadius;
  G4double fConeShieldOffset;//


  //Dimensions for PMT's
  static const G4int NumShieldPMTs=8;
  static const G4int ShieldPMTNPlanesZ=6;
  static const G4double ShieldPMTInnerR[];
  static const G4double ShieldPMTOuterR[];
  static const G4double ShieldPMTZPlanes[];
};
 
#endif

