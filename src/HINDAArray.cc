/*********************************************************************
Created by S. Henshaw 4/1/10


*********************************************************************/

#include "HINDAArray.hh"
#include "HINDACore.hh"
#include "HINDAShield.hh"
#include "AllMaterials.hh"
#include "MoreUnits.hh"

#include "TString.h"
#include "G4UnitsTable.hh"

#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"

const G4String HINDAArray::fDefaultCoreName[]={"ALAINA","BROOKE","CINDY","JONI","KRISTA","LINDA","ROBERTA","SUSAN"};
const G4String HINDAArray::fDefaultShieldName[]={"ANDY","BOBBY","CARL","JACK","KEVIN","LARRY","REGGIE","STEVE"};

//HINDAArray::HINDAArray(G4int NumDets, G4String CoreName[], G4String ShieldName[],
//		       G4double RList[], G4double ThetaList[], G4double PhiList[])
HINDAArray::HINDAArray(G4int NumDets, G4String CoreName[], G4String ShieldName[],
		       G4double RList[], G4double HList[], G4double ThetaList[], G4double PhiList[], G4double DetLength[], G4double Offset[])  //Added LSM 05-19-11
{//Builds an array of NumDets Detectors and uses input names
  fClassName="HINDAArray";
  fMethodName="HINDAArray";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;

  //Initializing Sensitive vol Number
  fNumSensitiveVols=0;


  //Checking input to make sure number of detectors is allowable
  fNumDets=NumDets;
  if(fNumDets>fMaxNDets || fNumDets<0)
    {
      G4cerr<<"**ERROR:  INVALID NUMDETS="<<fNumDets<<" IN CONSTRUCTOR(MaxNDets="<<fMaxNDets<<") !!!!!**"<<G4endl;
      G4Exception("HINDAArray::HINDAArray", "007", FatalException, "INVALID NUMDETS!!!!!***");
    }
  

  G4cout<<"Constructing a HINDA Array with "<<fNumDets<<" HINDA Detectors"<<G4endl;
  G4cout<<"Step 1.  Build Assemblies for Each HINDA"<<G4endl;

  //Looping Through fNumDets to Setup Assemblies
   for(G4int i=0;i<fNumDets;i++)
    {
      //Setting Names in Class and initial values for Det Placements
      fCoreName[i]=CoreName[i];
      fShieldName[i]=ShieldName[i];
      fCoreR[i]=RList[i];  //Maybe edit so input is the distance to the front of the lead shield!!  //LSM 05-12-11
      fCoreH[i]=HList[i];
      //fCoreR[i]=RList[i] + Half_det_length + Lead_thickness + Detector_Lead_separation; //need to input
      fCoreTheta[i]=ThetaList[i];
      fCorePhi[i]=PhiList[i];
   
      fCoreLength[i]=DetLength[i];  //Added LSM 05-19-11
      fCoreOffset[i]=Offset[i];  //Added LSM 05-19-11
      
      //Constructing Assemblies for Each HINDA Assembly
      BuildHINDA(i);
    }

   //Building an Array Assembly Volume
   G4cout<<"Step 2.  Build Assembly Volume for the Array (ArrayAssembly)"<<G4endl;
   BuildArray();
}



HINDAArray::~HINDAArray()
{
  fMethodName="~HINDAArray";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
  G4cout<<"\t Destruction of a HINDA Array"<<G4endl;
 
}

void HINDAArray::BuildHINDA(G4int DetNum)
{//Builds an assembly for the Core and shield 
  fMethodName="BuildHINDA";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;

  G4cout<<"\tBuilding HINDA Assembly Volume #: "<<DetNum<<G4endl;
  HINDA[DetNum]=new G4AssemblyVolume();

  //Building a Core for the Assembly
  G4cout<<"\n\tBuilding HINDA("<<DetNum<<") Core: "<<fCoreName[DetNum].data()<<G4endl;
  //CoreAssembly[DetNum]=new HINDACore(fCoreName[DetNum].data());
  CoreAssembly[DetNum]=new HINDACore(fCoreName[DetNum].data(),fCoreLength[DetNum],fCoreOffset[DetNum]);  //Added LSM 05-19-11


  //Building a Shield for the Assembly
  G4cout<<"\n\tBuilding HINDA("<<DetNum<<") Shield: "<<fShieldName[DetNum].data()<<G4endl;
  ShieldAssembly[DetNum]=new HINDAShield(fShieldName[DetNum].data());

  //Placing Core in the HINDA Assembly
  //cryo target setup, 2015
  //define forward/backward tilt of detectors based
  //on HINDA survey. note the change in sign relative
  //to orientation for phi=0 vs phi=180 dets.
  G4double survey_angle=0.0;// radians
  if (fCoreName[DetNum] == "ALAINA") {
    survey_angle = 4.496e-2 * 3.14 / 180.0;// tilt up
  } else if (fCoreName[DetNum] == "BROOKE") {
    survey_angle = 0.429 * 3.14 / 180.0;// tilt down
  } else if (fCoreName[DetNum] == "CINDY") {
    survey_angle = -0.111 * 3.14 / 180.0;// tilt up
  } else if (fCoreName[DetNum] == "JONI") {
    survey_angle = 8.993e-2 * 3.14 / 180.0;// tilt up
  } else if (fCoreName[DetNum] == "KRISTA") {
    survey_angle = 0.287 * 3.14 / 180.0;// tilt up
  } else if (fCoreName[DetNum] == "LINDA") {
    survey_angle = 5.88e-2 * 3.14 / 180.0;// tilt up
  } else if (fCoreName[DetNum] == "ROBERTA") {
    survey_angle = 4.15e-2 * 3.14 / 180.0;// tilt down
  } else if (fCoreName[DetNum] == "SUSAN") {
    survey_angle = -0.266 * 3.14 / 180.0;// tilt up
  } else {
    survey_angle = 0.0;
  }
  
  //survey_angle = 0.0;// no tilt

  G4RotationMatrix* tilt=new G4RotationMatrix();
  G4ThreeVector angle=G4ThreeVector(survey_angle,0,0);
  // G4ThreeVector angle=G4ThreeVector(0,45.0*3.14/180.,0);
  //G4ThreeVector angle=G4ThreeVector(0,0,45.0*3.14/180.);
  tilt->rotateX(angle.x());
  tilt->rotateY(angle.y());
  tilt->rotateZ(angle.z());
  //G4Transform3D CoreHINDAPlace=G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.,0.,0.));
  G4Transform3D CoreHINDAPlace=G4Transform3D(*tilt,G4ThreeVector(0.,0.,0.));
  HINDA[DetNum]->AddPlacedAssembly(CoreAssembly[DetNum]->GetCoreAssemblyVolume(),CoreHINDAPlace);

  //Placing Shield in the HINDA Assembly
  //the offset in z is because the center of the CoreAssembly is at the center of the crystal (5" half length)
  //and the center of the shield assembly is at the center of the NaI shield crystals which are 6"
  //half length.  We want their backfaces to line up so we offset the centers by 1 in.
  //G4Transform3D ShieldHINDAPlace=G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.,0.,-1.*in));
  G4Transform3D ShieldHINDAPlace=G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.,0.,0.));
  HINDA[DetNum]->AddPlacedAssembly(ShieldAssembly[DetNum]->GetShieldAssemblyVolume(),ShieldHINDAPlace);
  
  //Getting Names for Sensitive Logical Volumes
  G4int CoreSensNum=CoreAssembly[DetNum]->GetNumSensitiveVols(); 
  fCoreSensitiveLogVolName=CoreAssembly[DetNum]->GetSensitiveLogVolNames();


  for(G4int i=0;i<CoreSensNum;i++)
    {
      fHINDAArraySensitiveLogVolName[fNumSensitiveVols]=fCoreSensitiveLogVolName[i];
      fNumSensitiveVols++;
    }
  
  G4int ShieldSensNum=ShieldAssembly[DetNum]->GetNumSensitiveVols(); 
  fShieldSensitiveLogVolName=ShieldAssembly[DetNum]->GetSensitiveLogVolNames();

  for(G4int i=0;i<ShieldSensNum;i++)
    {
      fHINDAArraySensitiveLogVolName[fNumSensitiveVols]=fShieldSensitiveLogVolName[i];
      fNumSensitiveVols++;
    }
  

}

void HINDAArray::BuildArray(void)
{//Builds the whole array of HINDA's
  fMethodName="BuildArray";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
  

  //Building an assembly volume for the entire array
  G4cout<<"\tBuilding HINDA Array Assembly Volume"<<G4endl;
  ArrayAssembly=new G4AssemblyVolume();

  //Placing HINDA Assemblies into Array Assembly
   for(G4int i=0;i<fNumDets;i++)
     {
       fDetAngle[i]=G4ThreeVector(0,fCoreTheta[i],fCorePhi[i]);
       //****set height with respect to beam using y-coordinate****
       fDetPos[i]=G4ThreeVector(0.,fCoreH[i],fCoreR[i]);
       fDetRot[i]=new G4RotationMatrix();

       fDetPos[i].rotateX(fDetAngle[i].x());
       fDetPos[i].rotateY(fDetAngle[i].y());
       fDetPos[i].rotateZ(fDetAngle[i].z());
       
       fDetRot[i]->rotateX(fDetAngle[i].x());
       fDetRot[i]->rotateY(fDetAngle[i].y());
       fDetRot[i]->rotateZ(fDetAngle[i].z());

       transHINDA[i]=G4Transform3D(*fDetRot[i],fDetPos[i]);
       ArrayAssembly->AddPlacedAssembly(HINDA[i],transHINDA[i]);
     }
}

void HINDAArray::PlaceArray(G4LogicalVolume* logicMother,G4Transform3D Transform)
{
  ArrayAssembly->MakeImprint(logicMother,Transform,0,false);

  //This Sets the names and copy numbers of the segments
  VolumesIterator iter=ArrayAssembly->GetVolumesIterator();
  for(G4int i=0; i<(G4int)ArrayAssembly->TotalImprintedVolumes(); i++,iter++)
    {
      G4VPhysicalVolume *pv= *iter;
      G4LogicalVolume *lv=pv->GetLogicalVolume();
      G4String VolName=lv->GetName();
      G4cout<<"VolNames:  "<<VolName<<G4endl;
    }
  
}

void HINDAArray::PlaceAShield(G4int DetNum, G4LogicalVolume* logicMother,G4Transform3D Transform)
{
  fMethodName="PlaceAShield";
  ShieldAssembly[DetNum]->PlaceShieldAssembly(logicMother,Transform);

}

void HINDAArray::PlaceACore(G4int DetNum, G4LogicalVolume* logicMother,G4Transform3D Transform)
{
  fMethodName="PlaceACore";
  CoreAssembly[DetNum]->PlaceCoreAssembly(logicMother,Transform);

}

void HINDAArray::PlaceAShield(G4int DetNum, G4LogicalVolume* logicMother,G4RotationMatrix rot, G4ThreeVector pos)
{
  fMethodName="PlaceAShield";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
  G4Transform3D Transform=G4Transform3D(rot,pos);
  PlaceAShield(DetNum,logicMother,Transform);

}

void HINDAArray::PlaceACore(G4int DetNum, G4LogicalVolume* logicMother,G4RotationMatrix rot, G4ThreeVector pos)
{
  fMethodName="PlaceACore";
  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
   G4Transform3D Transform=G4Transform3D(rot,pos);
   PlaceACore(DetNum,logicMother,Transform);

}


