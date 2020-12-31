#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

/////////////////////////////////////////////////////
ActionInitialization::ActionInitialization(Analysis *anaman)
 : G4VUserActionInitialization(), anaMan(anaman)
{}

/////////////////////////////////////////////////////
ActionInitialization::~ActionInitialization()
{}

/////////////////////////////////////////////////////
void ActionInitialization::BuildForMaster() const
{
  SetUserAction( new RunAction(anaMan) );
}

/////////////////////////////////////////////////////
void ActionInitialization::Build() const
{
  SetUserAction(new RunAction(anaMan)   );
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new EventAction(anaMan) );
  SetUserAction(new SteppingAction);
}  
