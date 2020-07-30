 
#include "LeadShield.hh"


#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "AllMaterials.hh"
#include "G4VisAttributes.hh"

LeadShield::LeadShield(G4double offset, G4double thickness)
:solidLeadShield(0), logicLeadShield(0), physiLeadShield(0)
{  
  shield_offset = offset;
  shield_thickness = thickness;
}

LeadShield::~LeadShield()
{
  delete physiLeadShield;
  physiLeadShield=NULL;
  delete logicLeadShield;
  logicLeadShield=NULL;
  delete solidLeadShield;
  solidLeadShield=NULL;
}

void LeadShield::build(G4VPhysicalVolume* physiMother, G4ThreeVector delta, 
		       G4int copy_number=0)
{
   //---------------------------------------------------
   // Single LeadShield; i.e., a conical slab of lead
   //---------------------------------------------------
  G4double  pRmin2                 = 8.3987*cm;
  G4double  pRmax2                 = 21.273*cm;

  G4double  con_height             = 68.09628*cm;

  G4double  tg_alpha_min           = pRmin2/con_height;
  G4double  tg_alpha_max           = pRmax2/con_height;

  G4double  pRmin1                 = tg_alpha_min*(con_height - shield_thickness);
  G4double  pRmax1                 = tg_alpha_max*(con_height - shield_thickness);
  
  G4double  pDz                    = 0.5*shield_thickness;
  G4double  start_Angl_LeadShield  = 0.*deg;
  G4double  span_Angl_LeadShield   = 360.*deg;
  G4double  lead_detector_gap      = 0.001*mm;
  G4ThreeVector positionLeadShield = G4ThreeVector(0., 0., shield_offset - 
						   pDz - lead_detector_gap);
  
  G4RotationMatrix* Rot = new G4RotationMatrix();
  Rot->rotateX(delta.x());
  Rot->rotateY(delta.y());
  Rot->rotateZ(delta.z());
  
  positionLeadShield.rotateX(delta.x());
  positionLeadShield.rotateY(delta.y());
  positionLeadShield.rotateZ(delta.z());

  G4Transform3D TransformLeadShield = G4Transform3D(*Rot, positionLeadShield);

  solidLeadShield = new G4Cons("LeadShield", pRmin1, pRmax1, pRmin2, pRmax2, pDz, 
			       start_Angl_LeadShield, span_Angl_LeadShield);

  logicLeadShield = new G4LogicalVolume(solidLeadShield, 
					//					G4Material::GetMaterial("Material_Lead"), 
					AllMaterials::GetMaterial("Lead"), 
					"LeadShield", 0, 0, 0);
  
  G4String pv_name = "LeadShield_";
  std::ostringstream tmp_str;
  tmp_str << copy_number;
  pv_name+=tmp_str.str();

  physiLeadShield = new G4PVPlacement(TransformLeadShield,
 				      pv_name,   
				      logicLeadShield,       
				      physiMother,   
				      false,              
				      copy_number);       
 

  //-----------------------
  //Set the visualization attributes
  //-----------------------

  G4VisAttributes* LeadVisAtt= new G4VisAttributes(true, G4Colour(0.5,0.5,0.7));

  logicLeadShield->SetVisAttributes(LeadVisAtt);
} 


G4VPhysicalVolume* LeadShield::GetPhysicalPlacement()
{
  if(physiLeadShield)
    return physiLeadShield;
  else
    {
      G4cerr<<__FILE__<<" : "<<__LINE__<<
	" The physical volume not defined exiting program"<<G4endl;
      exit(-1);
    }
}
