#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "VDSD.hh"
#include "VDHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include <time.h>

/////////////////////////////////////////////////////
EventAction::EventAction(Analysis *anaman)
: G4UserEventAction(), anaMan(anaman)
{
}

/////////////////////////////////////////////////////
EventAction::~EventAction()
{
}

/////////////////////////////////////////////////////
void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
  anaMan->BeginOfEvent(anEvent);
}

/////////////////////////////////////////////////////
void EventAction::EndOfEventAction(const G4Event* anEvent)
{
  anaMan->EndOfEvent(anEvent);
}
/////////////////////////////////////////////////////
