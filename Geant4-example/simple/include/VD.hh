#ifndef VD_h
#define VD_h 1

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4String.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "MaterialList.hh"

#include <string.h>

class G4Material;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class MaterialList;

class VD
{
public:
  VD();
  ~VD();

  G4VPhysicalVolume* SetVD(const G4String      &Name,
                           const G4ThreeVector &Pos,
                           G4RotationMatrix    *Rot,
                           G4double             X,
                           G4double             Y,
                           G4double             Z,
                           G4LogicalVolume     *Mother,
                           G4Material          *Material,
                           int                  ID);

  G4LogicalVolume *GetDetectorLogic() { return logicVD; }

private:
  G4Box*              solidVD;
  G4LogicalVolume*    logicVD;
  G4VPhysicalVolume*  physiVD;

  void Visualize();

};

#endif
