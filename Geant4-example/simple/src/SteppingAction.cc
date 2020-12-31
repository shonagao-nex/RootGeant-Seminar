#include "SteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction( const G4Step *aStep )
{
  G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
  G4Track *track = aStep->GetTrack();

  const G4VTouchable *theTouchable = aStep->GetPreStepPoint()->GetTouchable();
  G4VPhysicalVolume *Vol = theTouchable->GetVolume();
  G4String volName = Vol->GetName();
  G4double length  = track->GetTrackLength();
  G4String parName = track->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4double vkin    = track->GetVertexKineticEnergy();

  if( length>30*m
   || parName == "anti_nu_tau"
   || parName == "nu_tau"
   || parName == "anti_nu_mu"
   || parName == "nu_mu"
   || parName == "anti_nu_e"
   || parName == "nu_e"
   || vkin < 100. * keV
     ){
    track->SetTrackStatus(fKillTrackAndSecondaries);
  }

}

