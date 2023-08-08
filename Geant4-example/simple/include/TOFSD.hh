#ifndef TOF_SD_h
#define TOF_SD_h 1

#include "G4VSensitiveDetector.hh"
#include "TOFHit.hh"
#include "ParamManager.hh"
#include "G4TouchableHandle.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class TOFSD : public G4VSensitiveDetector 
{
public:
  TOFSD(const G4String& Name);
  virtual ~TOFSD();

private:
  TOFHitsCollection* hitsCollection[3];
  G4double edep[3];

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
