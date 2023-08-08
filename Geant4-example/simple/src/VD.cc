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

G4VPhysicalVolume* VD::Place(const G4String      &Name,
                             const G4ThreeVector &Pos,
                             G4RotationMatrix    *Rot,
                             G4double             X,
                             G4double             Y,
                             G4double             Z,
                             G4LogicalVolume     *Mother,
                             G4Material          *Material,
			                       int                 ID)
{

  solidVD = new G4Box(Name+"S", X/2., Y/2., Z/2.);
  logicVD = new G4LogicalVolume(solidVD, Material, Name+"LV");
  physiVD = new G4PVPlacement(Rot, Pos, logicVD, Name+"PV", Mother, false, ID);

// visual //
  G4VisAttributes *vis = new G4VisAttributes();
  vis->SetColor(G4Color(0,0,0,0.1));
  vis->SetVisibility(1);
  logicVD->SetVisAttributes(vis);

  return physiVD;
}


G4VPhysicalVolume* VD::PlaceTOF(const G4String      &Name,
                                const G4ThreeVector &Pos,
                                G4RotationMatrix    *Rot,
                                G4LogicalVolume     *Mother,
                                G4Material          *Material)
{

  solidVD = new G4Box(Name+"S", 50./2.*mm, 100./2.*mm, 5./2.*mm);
  logicVD = new G4LogicalVolume(solidVD, Material, Name+"LV");
  for(int i=0;i<3;i++){
    new G4PVPlacement(Rot, G4ThreeVector(Pos.x()+i*50.*mm,Pos.y(),Pos.z()), logicVD, Name+"PV", Mother, false, i);
  }

// visual //
  G4VisAttributes *vis = new G4VisAttributes();
  vis->SetColor(G4Color(0,0,1.0,0.5));
  vis->SetVisibility(1);
  logicVD->SetVisAttributes(vis);

  return physiVD;
}

