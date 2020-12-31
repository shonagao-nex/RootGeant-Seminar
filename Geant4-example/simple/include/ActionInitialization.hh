#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "Analysis.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(Analysis *anaman);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    Analysis *anaMan;
};

#endif

    
