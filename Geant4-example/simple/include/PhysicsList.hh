#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "ParamManager.hh"

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class G4PhysListFactoryMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  void SetCuts();    

private:
  ParamManager *paramMan;

  G4int verbose;
  G4int decay;
  G4String emphysics, hadphysics;
    
};

#endif
