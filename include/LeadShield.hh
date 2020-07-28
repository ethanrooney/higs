#ifndef LeadShield_H
#define LeadShield_H 1


#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class G4Cons;
class G4LogicalVolume;
class G4VPhysicalVolume;



class LeadShield {
public:

  LeadShield(G4double offset=0, G4double thickness=15.875*cm);
  ~LeadShield();
  
  void build(G4VPhysicalVolume* logicMother, G4ThreeVector delta, G4int copy_number);

  inline G4double GetThickness(){return shield_thickness;};
  inline void SetThickness(G4double thickness){shield_thickness=thickness;};

  inline G4double GetOffset(){return shield_offset;};
  inline void SetOffset(G4double offset=15.875*cm){shield_offset=offset;};

  G4VPhysicalVolume* GetPhysicalPlacement();

private:
    
  G4Cons*             solidLeadShield;     
  G4LogicalVolume*    logicLeadShield;    
  G4VPhysicalVolume*  physiLeadShield;     
  
  G4double            shield_offset;
  G4double            shield_thickness;
  G4ThreeVector       positionLeadShield;


};

#endif

