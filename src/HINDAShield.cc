/*********************************************************************
Created by S. Henshaw 3/31/10

This creats a G4AssemblyVolume which is the Core of a HINDA.  I have 
Included the PMT's in this Assembly

The Core Diameter here is Assumed to be 10" and the length is 10"

*********************************************************************/
#include "HINDAShield.hh"
#include "HINDASD.hh"
#include "G4UnitsTable.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "AllMaterials.hh"
#include "MoreUnits.hh"


const G4double HINDAShield::ShieldPMTInnerR[]   = {3.5*cm, 3.5*cm, 3.5*cm, 3.5*cm, 0.*cm, 0.*cm};
const G4double HINDAShield::ShieldPMTOuterR[]   = {4.24*cm, 4.24*cm, 3.64*cm, 3.64*cm, 3.64*cm, 3.64*cm};
const G4double HINDAShield::ShieldPMTZPlanes[]  = {0.*cm, 0.8*cm, 0.8*cm, 16.25158*cm, 16.25158*cm, 16.45158*cm};


HINDAShield::HINDAShield(G4String Name)
{
  fClassName="HINDAShield";
  fMethodName="HINDAShield";
  fShieldName=Name;

  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
  G4cout<<"\tConstructing Shield with Name:  "<<fShieldName.data()<<G4endl;

  ShieldAssembly          =new G4AssemblyVolume();
  NaISegmentAssembly      =new G4AssemblyVolume();

  //Setting up Instance of Sensitive Detector Class
  HINDASDPtr = new HINDASD("/HINDA/HINDASDPtr");



  SetDimensions();
  BuildPMT();
  BuildShieldSegment();
  AssembleShieldSegments();
  BuildTeflonLiner();
  BuildSiliconeLiner();
  BuildAlCan();
  BuildPbShield();
  SetVisAtt();
  AssembleParts();
  MakeSensitive();
}

HINDAShield::~HINDAShield()
{
  //Logical Volumes
  delete logic_ShieldPMT;
    
  //Full Detector Assembly
  delete ShieldAssembly;
}

void  HINDAShield::SetDimensions()
{
  //View Slice of Detector 90 and span to 270 
  //StartAngle =  90.*deg;
  //SpanAngle  =  180.*deg;


  //For Physics Tests
  StartAngle =  0.*deg;
  SpanAngle  =  360.*deg;

  //Dimensions defined by S. Henshaw (Should be verified with St. Gobain Paperwork)
  //NaI Crystal Dimensions
  fNaIInnerR=13.843*cm;
  fNaIOuterR=20.6375*cm;
  fNaIHalfHeight=6.0*in;
  fNaISpanAngle=(360.0/NumSegments)*deg;

  //Teflon Dimensions (Thickness 0.0508*cm)
  fTeflonThickness=0.0508*cm;
  //fTeflonThickness=2*cm;//for testing purposes
  fTeflonInnerMostR=fNaIInnerR-fTeflonThickness;
  fTeflonOuterMostR=fNaIOuterR+fTeflonThickness;
  fTeflonHalfHeight=fNaIHalfHeight+(0.5*fTeflonThickness);

  //Silicone Dimensions (Thickness 0.2667*cm)
    fSiliconeThickness=0.2667*cm;
    //fSiliconeThickness=2*cm;//for Testing Purposes
  fSiliconeInnerMostR=fTeflonInnerMostR-fSiliconeThickness;
  fSiliconeOuterMostR=fTeflonOuterMostR+fSiliconeThickness;
  fSiliconeHalfHeight=fTeflonHalfHeight+(0.5*fSiliconeThickness);

  //AlCan Dimensions (Thickness 0.08128*cm)
  fAlThickness=0.08128*cm;
  //fAlThickness=2*cm;//for Testing Purposes
  fAlInnerMostR=fSiliconeInnerMostR-fAlThickness;
  fAlOuterMostR=fSiliconeOuterMostR+fAlThickness;
  fAlHalfHeight=fSiliconeHalfHeight+(0.5*fAlThickness);

  //Rim of Aluminium for Flange of Shield Dimesions
  fAlRimThicknessZ=1.0*in;
  fAlRimThicknessR=0.5*in;
  fAlRimInnerR=fAlOuterMostR;
  fAlRimOuterR=fAlOuterMostR+fAlRimThicknessR;
  fAlRimHalfHeight=0.5*fAlRimThicknessZ;
  
  //Dimesions for Lead Shield
  fPbShieldThickness=6.0*in;
  fPbShieldHalfHeight=fPbShieldThickness/2.0;
  fConeHeight=1.0*m;
  fCoreRadius=5.0*in;
  fConeShieldOffset=2.0*fAlHalfHeight+fPbShieldHalfHeight-fConeHeight/2.0;
  
  

}

void HINDAShield::BuildShieldSegment()
{
  //Creating Solid for one Shield Segment
  G4Tubs *NaI=new G4Tubs("NaI",fNaIInnerR,fNaIOuterR,fNaIHalfHeight,0.0*deg,fNaISpanAngle);

  //Creating Logical Volume for all Shield Segments
  for(G4int i=0; i<NumSegments; i++)
    {
      std::stringstream stri;
      stri<<i;
      logic_NaI[i]=new G4LogicalVolume(NaI,AllMaterials::GetMaterial("NaI"),
				       fShieldName+"_l_NaI_"+stri.str(),0,0,0);
    }
}


void HINDAShield::BuildPMT()
{
  //Solid for PMT (Values are set at Top of this file (HINDAShield.cc)
  G4Polycone *solid_ShieldPMT = new G4Polycone("s_core_PMT", 0,360*deg, 
				  ShieldPMTNPlanesZ, ShieldPMTZPlanes, 
				  ShieldPMTInnerR, ShieldPMTOuterR);

  //Defintion of Logical Volume (Origin of this logical volume is at center front face of PMT 
  logic_ShieldPMT = new G4LogicalVolume(solid_ShieldPMT, 
				       AllMaterials::GetMaterial("Air"), 
				       fShieldName+"_l_ShieldPMT", 0, 0, 0);  


}

void HINDAShield::AssembleShieldSegments()
{
  //Assembling NaISegmentArray
  G4RotationMatrix* zRot[8];
  
  //    for(G4int i=2; i<6; i++)//For Viewing only half
  for(G4int i=0; i<NumSegments; i++)
    {
      //Defines rotation of crystals about their axis
      zRot[i] = new G4RotationMatrix; 
      //      zRot[i]->rotateZ((2*i+1)*180./8.*deg);
      zRot[i]->rotateZ(i*360./8.*deg);
      
  
      
      G4Transform3D Transform_NaISegmentAssembly = 
	G4Transform3D(*zRot[i], G4ThreeVector());

      
      
      //Places the segments into the NaISegmentAssembly
      NaISegmentAssembly->AddPlacedVolume(logic_NaI[i], Transform_NaISegmentAssembly);

      //Places PMT on back of Segment
      G4ThreeVector PMTPos=G4ThreeVector(fNaIInnerR+0.5*(fNaIOuterR-fNaIInnerR),0.,fNaIHalfHeight);
      PMTPos.rotateZ(i*360./8.*deg+24*deg);//The 24 deg is so that PMT is on center of NaI segment (Purely asthetic)
      G4Transform3D PMTMove=G4Transform3D(*zRot[i], PMTPos);
      NaISegmentAssembly->AddPlacedVolume(logic_ShieldPMT, PMTMove);
      
    }


}

void HINDAShield::BuildTeflonLiner()
{//This method builds the solid and Logical volumes for the Teflon Silicone and Aluminium housings around NaI Crystals

  //Creating Solid for Teflon
  G4Transform3D TeflonNaIShift=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,0.5*fTeflonThickness));
  G4Tubs *TeflonHouse=new G4Tubs("TeflonHouse",fTeflonInnerMostR,fTeflonOuterMostR,fTeflonHalfHeight,StartAngle,SpanAngle);

  //Need this because G4SubtractionSolid will not take an Assembly
  G4Tubs *NaISegAssDummy=new G4Tubs("NaISegAssDummy",fNaIInnerR,fNaIOuterR,fNaIHalfHeight,StartAngle,SpanAngle);

  G4SubtractionSolid* TeflonLiner=new G4SubtractionSolid("TeflonLiner",TeflonHouse,NaISegAssDummy,TeflonNaIShift);

  //Creating Logical Volume for Teflon
  logic_TeflonLiner=new G4LogicalVolume(TeflonLiner,AllMaterials::GetMaterial("Teflon"),
					fShieldName+"_l_TeflonLiner",0,0,0);

}

void HINDAShield::BuildSiliconeLiner()
{//This method builds the solid and Logical volumes for the Teflon Silicone and Aluminium housings around NaI Crystals

  //Creating Solid for Silicone
  G4Transform3D SiliconeTeflonShift=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,0.5*fSiliconeThickness));
  G4Tubs *SiliconeHouse=new G4Tubs("SiliconeHouse",fSiliconeInnerMostR,fSiliconeOuterMostR,fSiliconeHalfHeight,StartAngle,SpanAngle);
  G4Tubs *TeflonHouse=new G4Tubs("TeflonHouse",fTeflonInnerMostR,fTeflonOuterMostR,fTeflonHalfHeight,StartAngle,SpanAngle);

  G4SubtractionSolid* SiliconeLiner=new G4SubtractionSolid("SiliconeLiner",SiliconeHouse,TeflonHouse,SiliconeTeflonShift);

  //Creating Logical Volume for Silicone
  logic_SiliconeLiner=new G4LogicalVolume(SiliconeLiner,AllMaterials::GetMaterial("Silicone"),
					  fShieldName+"_l_SiliconeLiner",0,0,0);

}

void HINDAShield::BuildAlCan()
{
  //Creating Aluminium Liner around crystal
  G4Transform3D AlSiliconeShift=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,0.5*fAlThickness));
  G4Tubs *AlHouse=new G4Tubs("AlHouse",fAlInnerMostR,fAlOuterMostR,fAlHalfHeight,StartAngle,SpanAngle);
  G4Tubs *SiliconeHouse=new G4Tubs("SiliconeHouse",fSiliconeInnerMostR,fSiliconeOuterMostR,fSiliconeHalfHeight,StartAngle,SpanAngle);

  G4SubtractionSolid* AlLiner=new G4SubtractionSolid("AlLiner",AlHouse,SiliconeHouse,AlSiliconeShift);

  //Creating Aluminium rim on Back of Detector
  G4Tubs *AlRim=new G4Tubs("AlRim",fAlRimInnerR,fAlRimOuterR,fAlRimHalfHeight,StartAngle,SpanAngle);
  
  //Creating Logical Volume for Al Can
  logic_AlLiner=new G4LogicalVolume(AlLiner,AllMaterials::GetMaterial("Aluminium"),
				    fShieldName+"_l_AlLiner",0,0,0);
  logic_AlRim=new G4LogicalVolume(AlRim,AllMaterials::GetMaterial("Aluminium"),
				  fShieldName+"_l_AlRim",0,0,0);
  

}

void HINDAShield::BuildPbShield()
{
  /*
  //Solids for Pb Shield
  G4Cons* CoreCone=new G4Cons("CoreCone",0.,0.0001*mm,0.,fCoreRadius,fConeHeight/2.0,StartAngle,SpanAngle);
  G4Tubs* PbShield=new G4Tubs("PbShield",0.,fAlOuterMostR,fPbShieldHalfHeight,StartAngle,SpanAngle);

  //Boolean Solids for Pb Collimator and Paraffin Insert
  G4Transform3D transCone=G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.,0.,fConeShieldOffset));
  G4SubtractionSolid *PbColl=new G4SubtractionSolid("PbColl",PbShield,CoreCone,transCone);
  G4IntersectionSolid *ParaffinInsert=new G4IntersectionSolid("ParaffinInsert",PbShield,CoreCone,transCone);
  */
  G4Cons* PbColl=new G4Cons("PbColl",2.73*in,fAlOuterMostR,3.515*in,fAlOuterMostR,fPbShieldHalfHeight,StartAngle,SpanAngle);  //Added LSM 05-19-11
  G4Cons* ParaffinInsert=new G4Cons("ParaffinInsert",0.0*in,2.72999*in,0.0*in,3.51499*in,fPbShieldHalfHeight,StartAngle,SpanAngle);  //Added LSM 05-19-11

  logic_PbColl=new G4LogicalVolume(PbColl,AllMaterials::GetMaterial("Lead"),
				   fShieldName+"_l_PbColl",0,0,0);
  
  logic_WaxInsert=new G4LogicalVolume(ParaffinInsert,AllMaterials::GetMaterial("ParaffinWax"),
				      fShieldName+"_l_WaxInsert",0,0,0);
  // logic_WaxInsert=new G4LogicalVolume(ParaffinInsert,AllMaterials::GetMaterial("Air"),
  //                                     fShieldName+"_l_WaxInsert",0,0,0);
  
}

void HINDAShield::AssembleParts()
{
   //Transforms needed for Adding Parts to ShieldAssembly (Center of Assembly will be Center of NaICrystals in x y and z
  /*
  G4Transform3D Transform_ShieldSegAss=G4Transform3D(G4RotationMatrix(), G4ThreeVector());
  G4Transform3D Transform_TeflonLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,-0.5*fTeflonThickness));
  G4Transform3D Transform_SiliconeLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0,-0.5*fTeflonThickness-0.5*fSiliconeThickness));
  G4Transform3D Transform_AlLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0,-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness));
  G4Transform3D Transform_AlRim=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness+fAlHalfHeight-fAlRimHalfHeight));
  G4Transform3D Transform_PbColl=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness-fAlHalfHeight-fPbShieldHalfHeight));
  */
  G4Transform3D Transform_ShieldSegAss=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,12*in));  //Added LSM 05-19-11
  G4Transform3D Transform_TeflonLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,12*in-0.5*fTeflonThickness));  //Added LSM 05-19-11
  G4Transform3D Transform_SiliconeLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0,12*in-0.5*fTeflonThickness-0.5*fSiliconeThickness));  //Added LSM 05-19-11
  G4Transform3D Transform_AlLiner=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0,12*in-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness));  //Added LSM 05-19-11
  G4Transform3D Transform_AlRim=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,12*in-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness+fAlHalfHeight-fAlRimHalfHeight));  //Added LSM 05-19-11
  G4Transform3D Transform_PbColl=G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.,0.,12*in-0.5*fTeflonThickness-0.5*fSiliconeThickness-0.5*fAlThickness-fAlHalfHeight-fPbShieldHalfHeight));  //Added LSM 05-19-11

  //Adding Parts to Assembly
  ShieldAssembly->AddPlacedVolume(logic_AlLiner, Transform_AlLiner);
  ShieldAssembly->AddPlacedVolume(logic_AlRim, Transform_AlRim);
  ShieldAssembly->AddPlacedVolume(logic_SiliconeLiner, Transform_SiliconeLiner);
  ShieldAssembly->AddPlacedVolume(logic_TeflonLiner, Transform_TeflonLiner);
  ShieldAssembly->AddPlacedVolume(logic_PbColl,Transform_PbColl);
  ShieldAssembly->AddPlacedVolume(logic_WaxInsert,Transform_PbColl);
  ShieldAssembly->AddPlacedAssembly(NaISegmentAssembly, Transform_ShieldSegAss);



}

void HINDAShield::SetVisAtt()
{
  //Setting Visualization Attributes for the Shield Segments
  G4VisAttributes* NaIVisAtt= new G4VisAttributes(G4Colour::Red());
  NaIVisAtt->SetForceSolid(true);
  for(G4int i=0;i<NumSegments;i++)
    logic_NaI[i] ->SetVisAttributes(NaIVisAtt);

  G4VisAttributes* TeflonVisAtt= new G4VisAttributes(G4Colour::Yellow());
  //TeflonVisAtt->SetForceWireframe(true);
  TeflonVisAtt->SetForceSolid(true);
  logic_TeflonLiner ->SetVisAttributes(TeflonVisAtt);

  G4VisAttributes* SiliconeVisAtt= new G4VisAttributes(G4Colour::Magenta());
  SiliconeVisAtt->SetForceWireframe(true);
  SiliconeVisAtt->SetForceSolid(true);
  logic_SiliconeLiner ->SetVisAttributes(SiliconeVisAtt);

  G4VisAttributes* AlVisAtt= new G4VisAttributes(G4Colour::Grey());
  AlVisAtt->SetForceWireframe(true);
  AlVisAtt->SetForceSolid(true);
  logic_AlLiner->SetVisAttributes(AlVisAtt);
  logic_AlRim->SetVisAttributes(AlVisAtt);
  logic_ShieldPMT->SetVisAttributes(AlVisAtt);

  G4VisAttributes* PbVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  PbVisAtt->SetForceSolid(true);
  logic_PbColl->SetVisAttributes(PbVisAtt);

  G4VisAttributes* WaxVisAtt= new G4VisAttributes(G4Colour(0.0,0.6,0.0));
  WaxVisAtt->SetForceSolid(true);
  logic_WaxInsert->SetVisAttributes(WaxVisAtt);

}

void HINDAShield::PlaceShieldAssembly(G4LogicalVolume* logicMother,G4Transform3D Transform)
{
  fMethodName="PlaceShieldAssembly";

  G4cout<<"-----"<<fClassName<<"::"<<fMethodName<<"-----"<<G4endl;
  G4cout<<"\t Placing: "<<fShieldName<<" with Components:"<<G4endl;

  //Places the Assembly at the postion defined by pos in the logicMother volume
  ShieldAssembly->MakeImprint(logicMother,Transform,0,false);
  
  /*//This is no longer needed because constructor has name of Shield and can label logical volumes
  //This Sets the names and copy numbers of the segments
  VolumesIterator iter=ShieldAssembly->GetVolumesIterator();
  G4int VolTypeCount[fNLogVols];
  for(G4int i=0;i<fNLogVols;i++)
    VolTypeCount[i]=0;

  for(G4int i=0; i<(G4int)ShieldAssembly->TotalImprintedVolumes(); i++,iter++)
  {
    G4VPhysicalVolume *pv= *iter;
    G4LogicalVolume *lv=pv->GetLogicalVolume();
    G4String VolName=lv->GetName();
    for(G4int j=0;j<fNLogVols;j++)
      {
	if(VolName.contains(LogVolNames[j].data()))
	  {
	    std::stringstream strCopyNo;
	    strCopyNo<<VolTypeCount[j];
	    G4String NewPVName=fShieldName + "_" +LogVolNames[j] +"_"+strCopyNo.str();
	    pv->SetName(NewPVName);
	    pv->SetCopyNo(VolTypeCount[j]);
	    G4cout<<"\t\tComponent:  "<<pv->GetName()<<" Copy #: "<<pv->GetCopyNo()<<G4endl;
	    VolTypeCount[j]++;
	  }
      }
  }//end of loop through volumes
  */
}

void HINDAShield::MakeSensitive()
{
  IsShieldSensitive=true;
  fNumSensitiveVols=NumSegments;
  for(G4int i=0;i<fNumSensitiveVols;i++)
    {
      logic_NaI[i]->SetSensitiveDetector(HINDASDPtr);
      fSensitiveLogVolName[i]=logic_NaI[i]->GetName();
    }
  /*
  //To read out pb and wax too  //Added LSM 05-20-11
  fNumSensitiveVols=NumSegments+2;  //Added LSM 05-20-11
  for(G4int i=0;i<fNumSensitiveVols;i++)
    {
      if ( i < fNumSensitiveVols - 2 ){  //shield segments  //Added LSM 05-20-11
	logic_NaI[i]->SetSensitiveDetector(HINDASDPtr);
	fSensitiveLogVolName[i]=logic_NaI[i]->GetName();
      }  //Added LSM 05-20-11
      else if ( i == fNumSensitiveVols - 2 ){  //Added LSM 05-20-11
	logic_PbColl->SetSensitiveDetector(HINDASDPtr);  //Added LSM 05-20-11
	fSensitiveLogVolName[i]=logic_PbColl->GetName();  //Added LSM 05-20-11
      }//Added LSM 05-20-11
      else if ( i == fNumSensitiveVols - 1 ){  //Added LSM 05-20-11
	logic_WaxInsert->SetSensitiveDetector(HINDASDPtr);  //Added LSM 05-20-11
	fSensitiveLogVolName[i]=logic_WaxInsert->GetName();  //Added LSM 05-20-11
      }//Added LSM 05-20-11
    }
  */
}
