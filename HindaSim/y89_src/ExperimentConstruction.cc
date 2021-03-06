//Created by S. Henshaw 3/26/10
//Mostly Copied from geant4/examples/novice/NO2
 
#include "ExperimentConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"      

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "AllMaterials.hh"
#include "HINDACore.hh"
#include "HINDAShield.hh"
#include "HINDAArray.hh"
#include "MoreUnits.hh"
#include "DataManager.hh"
#include "G4UImanager.hh"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExperimentConstruction::ExperimentConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 solidCylindricalTarget(0), solidRectangularTarget(0), logicTarget(0), physiTarget(0), 
 fWorldLengthX(0.),fWorldLengthY(0.),fWorldLengthZ(0.), fTargetDiameter(0.0), fTargetLx(0.0), fTargetLy(0.0), fTargetLz(0.0)
{
  fTargetShape = G4String("");
  fTargetMaterialName = G4String("");
  fDetMessenger = new DetectorMessenger(this);
  data=DataManager::GetInstance();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExperimentConstruction::~ExperimentConstruction()
{
   delete fDetMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* ExperimentConstruction::Construct()
{
  //This sets up pointers to all the materials used for this experiment
  GetMaterials(0);

  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  //------------------------------ 
  // World
  //------------------------------ 
  G4cout<<"Building Experimental Hall"<<G4endl;
  G4double WorldLength= 30*ft;
  //BuildExpHallSquare(Air,WorldLength);
  BuildExpHallSquare(Vacuum,WorldLength);


  //------------------------------ 
  // HINDA Array 
  //------------------------------ 
  const G4int NDets=8;
  G4String CoreNames[NDets]={"LINDA","ALAINA","SUSAN","BROOKE",
			     "CINDY","ROBERTA","KRISTA","JONI"};
  G4String ShieldNames[NDets]={"LARRY","ANDY","STEVE","BOBBY",
			       "CARL","REGGIE","KEVIN","JACK"};
  
  //Radius from center of array to center of core
  G4double RList[NDets]={87.3*cm,87.3*cm,87.3*cm,87.3*cm,
			 87.3*cm,87.3*cm,87.3*cm,87.3*cm};
  //Polar angle from z axis
  G4double ThetaList[NDets]={55.0*deg,55.0*deg,125.0*deg,125.0*deg,
			     55.0*deg,55.0*deg,125.0*deg,125.0*deg};
  //Azimuthial angle from x axis
  G4double PhiList[NDets]={0.0*deg,180.0*deg,0.0*deg,180.0*deg,
			   90.0*deg,-90.0*deg,90.0*deg,-90.0*deg};
  
  G4String* core_names = new G4String[NDets];
  for (Int_t i = 0; i < NDets; ++i) {
    core_names[i] = CoreNames[i] + "_l_NaI";
  }

  ArrayAssembly=new HINDAArray(NDets,CoreNames, ShieldNames,RList,ThetaList,
			       PhiList);
  data->SetNumCores(NDets);
  data->SetCoreNamesArray(core_names);
  

  //Place array in World at 0,0,0 with no rotation
  G4Transform3D CoreTrans=G4Transform3D(G4RotationMatrix(),G4ThreeVector());
  ArrayAssembly->PlaceArray(logicWorld,CoreTrans);


  //Echo what has been done
  G4cout<<" Placed  "<<ArrayAssembly->GetNumHINDAs()<<" HINDA's in World"<<G4endl;
  NumSensitiveVols=ArrayAssembly->GetNumSensitiveVols();
  SDLogVolName=ArrayAssembly->GetSensitiveLogVolNames();
  for(G4int i=0;i<NumSensitiveVols;i++)
    {
      G4cout<<"Sensitive Vol Name:  "<<SDLogVolName[i]<<G4endl;
    }


  //read the setup file macros/HindaSetup.mac
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4String command = "/control/execute macros/HindaSetup.mac";
  UI->ApplyCommand(command);

  //---------------------------
  // construct the target using settings in macros/HindaSetup.mac
  //--------------------------- 

  //get target material
  if(!fTargetMaterialName)
    {
      G4cerr << "ExperimentConstruction::Construct() Target material not specified. See macros/HindaSetup.mac" << G4endl; 
      exit(1);
    }
  else fTargetMaterial=(G4Material*)AllMaterials::GetMaterial((G4String)fTargetMaterialName);
  
  //construct the target
  if(!fTargetShape)
    {
      G4cerr << "ExperimentConstruction::Construce() Target shape not specified. See macros/HindaSetup.mac" << G4endl; 
      exit(1);
    }

  if(fTargetShape == "Cylinder")
    {
      BuildCylindricalTarget();
      G4cout << "Building cylindrical target" << G4endl;
    }

  else if(fTargetShape == "Rectangle")
    {
      BuildRectangularTarget();
      G4cout << "Building rectangular target" << G4endl;
    }

  else if(fTargetShape == "NoTarget")
    {
      G4cout << "*******No target constructed!*******" << G4endl;
    }

  else
    {
      G4cerr << "ExperimentConstruction::Construct() Target shape does not exist. See macros/HindaSetup.mac" << G4endl;
      exit(1);
    }

  
  
  SetDataPhysicalSetup();
  
  return physiWorld;
}
/******************************************************************************************/
/******************************************************************************************/
/***************User Defined Function to Build the Experimental Hall***********************/
/******************************************************************************************/
/******************************************************************************************/

void ExperimentConstruction::BuildExpHall(G4Material* mat,G4double XLength, G4double YLength, G4double ZLength)
{
  ExpHallMaterial=mat;
  fWorldLengthX=XLength;
  fWorldLengthY=YLength;
  fWorldLengthZ=ZLength;
  

  solidWorld= new G4Box("sWorld",XLength/2.0,YLength/2.0,ZLength/2.0);
  logicWorld= new G4LogicalVolume( solidWorld, ExpHallMaterial, "lWorld", 0, 0, 0);
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 logicWorld,      // its logical volume
				 "pWorld",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0,               //copy number
				 true);              // Check overlaps

  G4VisAttributes* ExpHallVisAtt= new G4VisAttributes(G4Colour::Grey());
  ExpHallVisAtt->SetVisibility(true);
  ExpHallVisAtt->SetForceWireframe(true);
  logicWorld  ->SetVisAttributes(ExpHallVisAtt);  

}

void ExperimentConstruction::BuildExpHallSquare(G4Material* mat,G4double Length)
{
  ExpHallMaterial=mat;
  fWorldLengthX=Length;
  fWorldLengthY=Length;
  fWorldLengthZ=Length;


  solidWorld= new G4Box("sWorld",fWorldLengthX/2.0,fWorldLengthY/2.0,fWorldLengthZ/2.0);
  logicWorld= new G4LogicalVolume( solidWorld, ExpHallMaterial, "lWorld", 0, 0, 0);
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 logicWorld,      // its logical volume
				 "pWorld",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0,               //copy number
				 true);              // Check overlaps

  G4VisAttributes* ExpHallVisAtt= new G4VisAttributes(G4Colour::Grey());
  ExpHallVisAtt->SetVisibility(true);
  ExpHallVisAtt->SetForceWireframe(true);
  logicWorld  ->SetVisAttributes(ExpHallVisAtt);  

}


void ExperimentConstruction::GetMaterials(G4int PrintOption)
{
  //--------- Material definition ---------
  //Only Put the Materials used in this particular setup. 

  new AllMaterials; //Defines all the elements and materials
  Air    = AllMaterials::GetMaterial("Air"); //Air
  Pb     = AllMaterials::GetMaterial("Lead");//Lead
  PVC    = AllMaterials::GetMaterial("G4_POLYVINYL_CHLORIDE");//PVC
  Vacuum = AllMaterials::GetMaterial("Vacuum");//Vacuum
  Bi     = AllMaterials::GetMaterial("Bismuth");//Bismuth-209
  Concrete = AllMaterials::GetMaterial("G4_CONCRETE");//From Geant Standard lib
  Kapton = AllMaterials::GetMaterial("G4_KAPTON");//From Geant Standard lib

}

void ExperimentConstruction:: BuildBeamPipe(G4Material* matInner, G4Material* matShell,G4Material* matWindow,
					    G4double InsideDiameter,G4double OutsideDiameter,
					    G4double WindowThickness,G4double Length,
					    G4double WorldPosX,G4double WorldPosY,G4double WorldPosZ)
{
  G4double pipeLength=Length;
  G4ThreeVector positionPipe = G4ThreeVector(WorldPosX,WorldPosY,WorldPosZ);//Position of Center of Pipe

  G4Tubs *sWindow=new G4Tubs("sWindow",0.0*cm,InsideDiameter/2.0,WindowThickness/2.0,0,360);
  G4LogicalVolume *lWindow=new G4LogicalVolume(sWindow,matWindow,"lWindow",0,0,0);

  

  solidBeamPipeShell = new G4Tubs("sBPShell",  //name
			     0,
			     OutsideDiameter/2.0,  //rmax
			     pipeLength/2.0,//z halfsize
			     0,
			     360); 
  
  solidBeamPipeInner = new G4Tubs("sBPInner",  //name
				  0.0 *cm,  //rmin
				  InsideDiameter/2.0,  //rmax
				  (pipeLength-2.0*WindowThickness)/2.0,//z halfsize
				  0,
				  360); 
  

  logicBeamPipeShell = new G4LogicalVolume(solidBeamPipeShell,matShell,"lBPShell",0,0,0);
  logicBeamPipeInner = new G4LogicalVolume(solidBeamPipeInner,matInner,"lBPInner",0,0,0);


  physiBeamPipeInner = new G4PVPlacement(0,               // no rotation
					 0,  // at (x,y,z)
					 logicBeamPipeInner,     // its logical volume				  
					 "pBPInner",        // its name
					 logicBeamPipeShell,      // its mother  volume
					 true,           // no boolean operations
					 0,     //copy number
					 true);       // Check Overlap 



  physiBeamPipeShell = new G4PVPlacement(0,               // no rotation
					 positionPipe,  // at (x,y,z)
					 logicBeamPipeShell,     // its logical volume				  
					 "pBPShell",        // its name
					 logicWorld,      // its mother  volume
					 true,           // no boolean operations
					 0,  //copy number
					 true);         //check overlap 
  physiWindow1=new G4PVPlacement(0,               // no rotation
				  G4ThreeVector(0.,0.,pipeLength/2.0-(WindowThickness/2.0)),  // at (x,y,z)
				  lWindow,     // its logical volume				  
				  "pWindow1",        // its name
				  logicBeamPipeShell,      // its mother  volume
				  true,           // no boolean operations
				  0,  //copy number
				  true);         //check overlap 

  physiWindow2=new G4PVPlacement(0,               // no rotation
				  G4ThreeVector(0.,0.,-pipeLength/2.0+(WindowThickness/2.0)),  // at (x,y,z)
				  lWindow,     // its logical volume				  
				  "pWindow2",        // its name
				  logicBeamPipeShell,      // its mother  volume
				  true,           // no boolean operations
				  0,  //copy number
				  true);         //check overlap 

  G4Colour transOrange=G4Colour(1.,1.0,0.0,1);
  G4VisAttributes* BeamPipeShellVisAtt= new G4VisAttributes(transOrange);
  BeamPipeShellVisAtt->SetForceWireframe(true);
  logicBeamPipeShell->SetVisAttributes(BeamPipeShellVisAtt);

  G4VisAttributes* BeamPipeInnerVisAtt= new G4VisAttributes(G4Colour::Cyan());
  BeamPipeInnerVisAtt->SetForceSolid(true);
  logicBeamPipeInner->SetVisAttributes(BeamPipeInnerVisAtt);

  G4VisAttributes* WindowVisAtt= new G4VisAttributes(G4Colour::Yellow());
  WindowVisAtt->SetForceSolid(true);
  lWindow->SetVisAttributes(WindowVisAtt);

  

}

void ExperimentConstruction::BuildUTRWall(G4double thickness,G4double BeamHoleDiameter)
{
  
  solidUTRWall=new G4Box("sUTRWall",fWorldLengthX/2.0,fWorldLengthY/2.0,thickness/2.0);

  G4Tubs* solidBeamHole=new G4Tubs("BeamHole",0,BeamHoleDiameter/2.0,thickness,0,twopi);

  WallandHole=new G4SubtractionSolid("Box-Cylinder",solidUTRWall,solidBeamHole);


  logicUTRWall=new G4LogicalVolume(WallandHole,Concrete,"lUTRWall",0,0,0);
  physiUTRWall=new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(0,0,-fWorldLengthZ/2.0+thickness/2.0+300*cm), // at (0,0,0)
                                 logicUTRWall,      // its logical volume
				 "pUTRWall",         // its name
                                 logicWorld,               // its mother  volume
                                 false,           // no boolean operations
                                 0,               //copy number
				 true);              // Check overlaps

  G4VisAttributes* UTRWallVisAtt= new G4VisAttributes(G4Colour::Grey());
  UTRWallVisAtt->SetVisibility(true);
  UTRWallVisAtt->SetForceSolid(true);
  logicUTRWall  ->SetVisAttributes(UTRWallVisAtt);  
  

}

void ExperimentConstruction::BuildCylindricalTarget()
{
  //Solid for Target
  solidCylindricalTarget=new G4Tubs("solidCylindricalTarget",0,0.5*fTargetDiameter,0.5*fTargetLz,0,twopi);

  //Logical Volume for Target
  logicTarget=new G4LogicalVolume(solidCylindricalTarget,fTargetMaterial,"CylindricalTarget",0,0,0);
  
  //Placing Target in the World
  G4ThreeVector fTargetAngle=G4ThreeVector(0,fTargetTheta,fTargetPhi);
  G4RotationMatrix *fTargetRot=new G4RotationMatrix();
  fTargetRot->rotateX(fTargetAngle.x());
  fTargetRot->rotateY(fTargetAngle.y());
  fTargetRot->rotateZ(fTargetAngle.z());

  physiTarget=new G4PVPlacement(fTargetRot,
				G4ThreeVector(0.,0.,0.),
				logicTarget,
				"physiTarget",
				logicWorld,
				false,
				0,
				true);

  G4VisAttributes* TargetVisAtt= new G4VisAttributes(G4Colour::Yellow());
  TargetVisAtt->SetVisibility(true);
  TargetVisAtt->SetForceSolid(true);
  logicTarget  ->SetVisAttributes(TargetVisAtt);  

}

void ExperimentConstruction::BuildRectangularTarget()
{
  //Solid for Target
  solidRectangularTarget=new G4Box("solidRectangularTarget",0.5*fTargetLx,0.5*fTargetLy,0.5*fTargetLz);

  //Logical Volume for Target
  logicTarget=new G4LogicalVolume(solidRectangularTarget,fTargetMaterial,"RectangularTarget",0,0,0);
  
  //Placing Target in the World
  G4ThreeVector fTargetAngle=G4ThreeVector(0,fTargetTheta,fTargetPhi);
  G4RotationMatrix *fTargetRot=new G4RotationMatrix();
  fTargetRot->rotateX(fTargetAngle.x());
  fTargetRot->rotateY(fTargetAngle.y());
  fTargetRot->rotateZ(fTargetAngle.z());

  physiTarget=new G4PVPlacement(fTargetRot,
				G4ThreeVector(0.,0.,0.),
				logicTarget,
				"physiTarget",
				logicWorld,
				false,
				0,
				true);

  G4VisAttributes* TargetVisAtt= new G4VisAttributes(G4Colour::Yellow());
  TargetVisAtt->SetVisibility(true);
  TargetVisAtt->SetForceSolid(true);
  logicTarget->SetVisAttributes(TargetVisAtt);  

}


void ExperimentConstruction::SetDataPhysicalSetup()
{//This sends experimental setup values to the Data Manager class which will write them at 
  //the end of run action
  data->SetWorldLengthX(fWorldLengthX);
  data->SetWorldLengthY(fWorldLengthY);
  data->SetWorldLengthZ(fWorldLengthZ);

  //Sending Names of Logical Volumes to DataManger to setup Branches
  data->SetNumSensitiveVols(NumSensitiveVols);
  data->SetSensitiveLogVolNames(SDLogVolName);


}


