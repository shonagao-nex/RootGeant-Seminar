#ifndef VD_SD_h
#define VD_SD_h 1

#include "G4VSensitiveDetector.hh"
#include "VDHit.hh"
#include "ParamManager.hh"
#include "G4TouchableHandle.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class VDSD : public G4VSensitiveDetector 
{
public:
  VDSD(const G4String& Name);
  virtual ~VDSD();

private:
  VDHitsCollection* hitsCollection[2];
  G4double edep[2];

  ParamManager *paramMan;
  G4int DetectFlag;

public:
  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void Initialize(G4HCofThisEvent* HCTE);
  virtual void EndOfEvent(G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll();

};

#endif
