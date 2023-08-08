#include "DetectorConstruction.hh"
#include "ParamManager.hh"
#include "MaterialList.hh"

#include "Target.hh"
#include "VD.hh"
#include "VDSD.hh"
//#include "TOFSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "MagField.hh"
#include <fstream>

////////////////////////////////////////////////////////////////
DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(), 
 fStepLimit(NULL), fCheckOverlaps(true)
{
  G4cout<<"Constructor DetectorConstruction"<<G4endl;
}

////////////////////////////////////////////////////////////////
DetectorConstruction::~DetectorConstruction()
{
  G4cout<<"Destructor DetectorConstruction"<<G4endl;
  delete fStepLimit;
}

////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return DefineVolumes();
}

////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  MaterialList *mList = MaterialList::GetInstance();
  paramMan = ParamManager::GetParam();

  ///////////
  // World //
  ///////////
  G4double worldLength = 1.*m;
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  G4Box* worldS = new G4Box( "world", worldLength/2., worldLength/2., worldLength/2. );

  G4LogicalVolume* worldLV = new G4LogicalVolume(
                                     worldS,          // solid
                                     mList->Vacuum,   // material
                                     "World" );       // logical volume name
  
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                                     0,               // rotation
                                     G4ThreeVector(), // origin
                                     worldLV,         // logical volume
                                     "World",         // physical volume name
                                     0,               // mother volume
                                     false,           // pMany
                                     0,               // copy number
                                     fCheckOverlaps); // checking overlaps 

  G4VisAttributes* world_vis = new G4VisAttributes();
  world_vis->SetColor(G4Color(0.2, 0.2, 0.2, 0.05));
  world_vis->SetVisibility(0);
  worldLV->SetVisAttributes(world_vis);
//  worldLV->SetVisAttributes(G4VisAttributes::Invisible);   //OLD
 
  ////////////
  // target //
  ////////////
  target = new Target();
  G4ThreeVector tar_pos(0.*mm, 0.*mm, 0.*mm);
  G4RotationMatrix *tar_rot = new G4RotationMatrix();
  G4double thick = 5. * mm;
  target->target("TargetPV",tar_pos,tar_rot,thick,worldLV,mList->Graphite,0);

  //////////////////////
  // Virtual Detector //
  //////////////////////
  vd0 = new VD();
  G4ThreeVector vd_pos0(0.*mm, 0.*mm, 100.*mm);
  vd0->Place("VD0",vd_pos0,0,100.*mm, 100.*mm, 1.*mm, worldLV, mList->Vacuum, 0);

  vd1 = new VD();
  G4ThreeVector vd_pos1(30.*mm, 0.*mm, 300.*mm);
  G4RotationMatrix *vd_rot1 = new G4RotationMatrix();
  vd_rot1->rotateY(-10. * degree);
  vd1->Place("VD1",vd_pos1,vd_rot1,200.*mm, 200.*mm, 10.*mm, worldLV, mList->Scinti, 1);

//  tof = new VD();
//  tof->PlaceTOF("TOF",G4ThreeVector(50.*mm,0,450.*mm),0, worldLV, mList->Scinti);

  fStepLimit = new G4UserLimits(10.*mm);
  vd1->GetDetectorLogic()->SetUserLimits(fStepLimit);

  return worldPV;
}

////////////////////////////////////////////////////////////////
void DetectorConstruction::ConstructSDandField()
{
  // Sensitive Detectors
  G4SDManager* SDmanager= G4SDManager::GetSDMpointer();

  VDSD* vdsd = new VDSD("VDSD");
  SDmanager->AddNewDetector(vdsd);
  vd0->GetDetectorLogic()->SetSensitiveDetector(vdsd);
  vd1->GetDetectorLogic()->SetSensitiveDetector(vdsd);

//  TOFSD* tofsd = new TOFSD("TOFSD");
//  SDmanager->AddNewDetector(tofsd);
//  tof->GetDetectorLogic()->SetSensitiveDetector(tofsd);

  // Field
  G4FieldManager *fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  MagField *magfield = new MagField();
  fieldManager->SetDetectorField(magfield);
  fieldManager->CreateChordFinder(magfield);
}

////////////////////////////////////////////////////////////////
void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

////////////////////////////////////////////////////////////////
void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}  
