#include "VD.hh"
#include "ParamManager.hh"

#include "MaterialList.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <string.h>
#include <sstream>

VD::VD()
: solidVD(0), logicVD(0), physiVD(0)
{
}

VD::~VD()
{
}

G4VPhysicalVolume* VD::SetVD(const G4String      &Name,
                             const G4ThreeVector &Pos,
                             G4RotationMatrix    *Rot,
                             G4double             X,
                             G4double             Y,
                             G4double             Z,
                             G4LogicalVolume     *Mother,
                             G4Material          *Material,
			                       int                 ID)
{
  MaterialList *mList = MaterialList::GetInstance();

  std::ostringstream id;
  id << ID;

  solidVD = new G4Box(Name+id.str()+"S", X/2., Y/2., Z/2.);
  logicVD = new G4LogicalVolume(solidVD, Material, Name+id.str()+"LV");
  physiVD = new G4PVPlacement(Rot, Pos, logicVD, Name+id.str()+"PV", Mother, false, ID);

// visual //
  Visualize();

  return physiVD;
}

void VD::Visualize(){
  G4VisAttributes* vis = new G4VisAttributes();
  vis->SetColor(G4Color(0,0,0,0.1));
  vis->SetForceSolid(true);
  logicVD->SetVisAttributes(vis);
//  logicVD->SetVisAttributes(G4VisAttributes::Invisible);
}
