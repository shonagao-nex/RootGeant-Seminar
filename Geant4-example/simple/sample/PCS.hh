#ifndef PCS_h
#define PCS_h 1

#include "BeamLineElement.hh"
#include "PCSFieldMan.hh"
#include "G4GDMLParser.hh"

#include <vector>

class G4Material;
class G4VPhysicalVolume;
class G4VSolid;
class G4LogicalVolume;
class G4UserLimits;

class PCS : public BeamLineElement
{
public:
  PCS( const G4String &name, 
              const G4ThreeVector &gPos,
              const G4RotationMatrix *rotMtx,
              const std::string deffilename );
  ~PCS();

  // Overloaded Functions
  bool ExistMagneticField( void ) const;
  G4ThreeVector GetlPos( const G4ThreeVector &gPos ) const;
  bool ExistElectricField( void ) const { return false; }
  bool IsInside( const G4ThreeVector &gPos ) const;

  G4ThreeVector GetMagneticField( const G4ThreeVector &gPos ) const;

  void SetMaterials( G4Material *mYoke){ mYoke_ = mYoke;}
  G4VPhysicalVolume* Place( G4VPhysicalVolume* pMother );

  void SetUserLimits( G4UserLimits *limitYoke, G4UserLimits *limitGap = 0 );

private:
  G4Material *mYoke_;
  G4VSolid *solidField;
  G4LogicalVolume *yokeLog_, *gapLog_;
  G4double Scale;

  G4ThreeVector Field( const G4ThreeVector &pos ) const;

  PCSFieldMan fMan;

  G4VSolid *MakeGap( const G4String &name );

 // For GDML
  G4String fReadFile;
  G4GDMLParser *fParser;
  G4GDMLReadStructure *fReader;

  int MapID;
};

#endif
