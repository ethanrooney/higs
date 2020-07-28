//Created by S. Henshaw 3/26/10
//Mostly Copied from geant4/examples/novice/NO2


#ifndef ExperimentConstruction_h
#define ExperimentConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include <map>
#include "TString.h"

class DetectorMessenger;
class G4Box;
class G4Tubs;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class HINDACore;
class HINDAShield;
class HINDAArray;
class DataManager;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExperimentConstruction : public G4VUserDetectorConstruction
{
public:
  
  ExperimentConstruction();
  ~ExperimentConstruction();
  
public:
  
  G4VPhysicalVolume* Construct();//Called by RunManager->Initialize();
  void BuildExpHall(G4Material* mat,G4double XLength, G4double YLength, G4double ZLength);
  void BuildExpHallSquare(G4Material* mat,G4double Length);
  void BuildBeamPipe(G4Material* matInner, G4Material* matShell,G4Material* matWindow,
		     G4double InsideDiameter,G4double OutsideDiameter,
		     G4double WindowThickness,G4double Length,
		     G4double WorldPosX,G4double WorldPosY,G4double WorldPosZ);

  void BuildUTRWall(G4double thickness,G4double BeamHoleDiameter);

  //void BuildTarget(G4Material* mat, G4double diameter, G4double thickness,G4double theta,G4double phi);
  void BuildCylindricalTarget();
  void BuildRectangularTarget();

  void SetTargetShape(G4String shape){fTargetShape=shape;};
  void SetTargetMaterial(G4String material){fTargetMaterialName=material;};
  void SetTargetDiameter(G4double diameter){fTargetDiameter=diameter;};
  void SetTargetLx(G4double lx){fTargetLx=lx;};
  void SetTargetLy(G4double ly){fTargetLy=ly;};
  void SetTargetLz(G4double lz){fTargetLz=lz;};
  void SetTargetTheta(G4double theta){fTargetTheta=theta;};
  void SetTargetPhi(G4double phi){fTargetPhi=phi;};

  //inline G4Tubs* GetTargetSolid(void) {return solidTarget;};
  inline G4Tubs* GetCylindricalTargetSolid(void) {return solidCylindricalTarget;};
  inline G4Box* GetRectangularTargetSolid(void) {return solidRectangularTarget;};
  inline G4VPhysicalVolume* GetTargetPhysicalVolume(void) {return physiTarget;};



  HINDACore* CoreAssembly;
  HINDAShield* ShieldAssembly;
  HINDAArray* ArrayAssembly;

  void GetMaterials(G4int PrintOption);
  TString GetTargetShape(){return fTargetShape;};
  TString GetTargetMaterial(){return fTargetMaterialName;};  
  
  const 
  G4double GetWorldLengthX() {return fWorldLengthX;};
  G4double GetWorldLengthY() {return fWorldLengthX;};
  G4double GetWorldLengthZ() {return fWorldLengthX;};

  
private:
  G4Box*             solidWorld;    // pointer to the solid envelope 
  G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
  G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope
  
  G4Tubs*            solidCylindricalTarget;   // pointer to solid cylindrical Target
  G4Box*             solidRectangularTarget; // pointer to solid rectangular Target
  TString            fTargetShape;
  TString            fTargetMaterialName;
  G4Material*        fTargetMaterial;
  G4double           fTargetDiameter;
  G4double           fTargetLx;
  G4double           fTargetLy;
  G4double           fTargetLz;
  G4double           fTargetTheta;
  G4double           fTargetPhi;

  G4LogicalVolume*   logicTarget;   // pointer to the logical Target
  G4VPhysicalVolume* physiTarget;   // pointer to the physical Target

  G4Tubs*             solidBeamPipeShell;   // pointer to the solid Target
  G4LogicalVolume*    logicBeamPipeShell;   // pointer to the logical Target
  G4VPhysicalVolume*  physiBeamPipeShell;   // pointer to the physical Target

  G4Tubs*             solidBeamPipeInner;   // pointer to the solid Target
  G4LogicalVolume*    logicBeamPipeInner;   // pointer to the logical Target
  G4VPhysicalVolume*  physiBeamPipeInner;   // pointer to the physical Target

  G4VPhysicalVolume*  physiWindow1;
  G4VPhysicalVolume*  physiWindow2;



  G4Box*  solidUTRWall;
  G4SubtractionSolid* WallandHole;
  G4LogicalVolume* logicUTRWall;
  G4VPhysicalVolume* physiUTRWall;


  G4Material*         ExpHallMaterial;
  G4Material*         TargetMaterial;
  G4Material*         Air;
  G4Material*         Pb;
  G4Material*         Bi;
  G4Material*         Vacuum;
  G4Material*         PVC;
  G4Material*         Concrete;
  G4Material*         Kapton;
  
  G4double fWorldLengthX;            // Full length of the world volume
  G4double fWorldLengthY;            // Full length of the world volume
  G4double fWorldLengthZ;            // Full length of the world volume

  DetectorMessenger* fDetMessenger;      //pointer to the messenger

private:
  DataManager* data;
  G4int NumSensitiveVols;
  G4String* SDLogVolName;
  void SetDataPhysicalSetup();//Set the Experimental Construction Variables for the DataManager

private:
  std::map<TString,TString> fSensitiveLogVolName;//fLogVolName[TString "CoreName"] return LogVolName
  G4String* SensitiveVolName;

};


#endif
