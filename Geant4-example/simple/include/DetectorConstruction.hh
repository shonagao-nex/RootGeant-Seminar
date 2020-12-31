#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "ParamManager.hh"

#include "Target.hh"
#include "VD.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetMaxStep (G4double );
    void SetCheckOverlaps(G4bool );

  private:
    G4VPhysicalVolume* DefineVolumes();
  
    G4UserLimits* fStepLimit;

    ParamManager *paramMan;
    Target *target;
    VD *vd0, *vd1;

    G4bool  fCheckOverlaps; 
};

#endif
