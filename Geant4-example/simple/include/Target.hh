#ifndef Target_h
#define Target_h 1

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4String.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "MaterialList.hh"

#include <string.h>

class G4Material;

class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class MaterialList;

class Target
{
public:
  Target();
  ~Target();

  G4VPhysicalVolume* target(const G4String      &Name,
                            const G4ThreeVector &Pos,
                            G4RotationMatrix    *Rot,
                            const G4double      &Thick,
                            G4LogicalVolume     *Mother,
                            G4Material          *Material,
                            int                 ID);
  
  G4LogicalVolume *GetTargetLV() { return TargetLV; }
  
private:
  G4Tubs*             TargetS;
  G4LogicalVolume*    TargetLV;
  G4VPhysicalVolume*  TargetPV;
  
};

#endif
