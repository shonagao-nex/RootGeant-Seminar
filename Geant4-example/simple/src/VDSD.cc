#include "G4VPhysicalVolume.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4TouchableHandle.hh"
#include "G4SystemOfUnits.hh"
#include "VDSD.hh"
#include "VDHit.hh"

#include <fstream>
using namespace std;

VDSD::VDSD(const G4String& Name): G4VSensitiveDetector(Name)
{
  paramMan = ParamManager::GetParam();

  for(int i=0;i<2;i++){
    std::ostringstream id;
    id << i;
    G4String DetectorName = G4String("VD") + id.str();
	  collectionName.insert(DetectorName);
  }
}

VDSD::~VDSD()
{
}

void VDSD::Initialize(G4HCofThisEvent* HCTE)
{
  for(int i=0;i<2;i++){
    hitsCollection[i] = new VDHitsCollection(SensitiveDetectorName,collectionName[i]);
    G4int hcid = GetCollectionID(i);
	  HCTE->AddHitsCollection(hcid, hitsCollection[i]);
    edep[i] = 0;
  }
}

G4bool VDSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
// Pre Step Point
  const G4StepPoint* preStepPoint  = aStep-> GetPreStepPoint();
// Post Step Point
//  const G4StepPoint* postStepPoint = aStep-> GetPostStepPoint();
// Track
  const G4Track *aTrack            = aStep->GetTrack();
  G4TouchableHistory* touchable    = (G4TouchableHistory*)(preStepPoint-> GetTouchable());
  G4VPhysicalVolume *Vol = touchable-> GetVolume();

// Track ID
  G4int         trackID  = aTrack->GetTrackID();
// Particle Charge
  G4double      charge   = aTrack->GetDefinition()->GetPDGCharge();
// Volume ID
  G4int         volID    = Vol->GetCopyNo();
// Global Position
  G4ThreeVector gpos     = preStepPoint->GetPosition();
// Local Position
  G4ThreeVector lpos     = touchable->GetHistory()->GetTopTransform().TransformPoint(gpos);
// Momentum on the global coordinate
  G4ThreeVector gmom     = preStepPoint->GetMomentum();
// Momentum on the local coordinate
  G4double      time     = preStepPoint->GetGlobalTime();
// Particle Name
  G4String      pname    = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
// Particle ID
  G4int         pid      = aTrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
// Particle Mass
//  G4double      pmass    = aTrack->GetDynamicParticle()->GetMass();
// Energy Deposit
  edep[volID] += aStep->GetTotalEnergyDeposit();

  if( fabs(charge)>0 ){
    VDHit *ahit = new VDHit(gpos,gmom,time,pid,trackID,edep[volID]);
    hitsCollection[volID]->insert(ahit);
  }
  return true;
}

void VDSD::EndOfEvent(G4HCofThisEvent*)
{
}

void VDSD::DrawAll()
{
}

void VDSD::PrintAll()
{
  for(int i=0;i<2;i++){
    hitsCollection[i]-> PrintAllHits();
  }
}

