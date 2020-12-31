#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "ParamManager.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Decay.hh"
#include "G4DecayTable.hh"
#include "G4SystemOfUnits.hh"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <CLHEP/Random/RandFlat.h>
#include <CLHEP/Random/RandGauss.h>
#include <TFile.h>
#include <TROOT.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <string>
#include <vector>
#pragma GCC diagnostic pop

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* );

    G4ParticleGun* GetParticleGun() {return ParticleGun;}
  
  private:
    ParamManager *paramMan;
    
    G4ParticleGun* ParticleGun;
    G4ParticleTable* particleTable;
    G4IonTable* ionTable;
    G4ParticleDefinition *particle;
    G4DecayTable *decayTable;

    G4String BeamParticle;
    G4int    BeamType;
    G4double BeamMom, BeamMomR;
    G4double BeamX, BeamXR;
    G4double BeamY, BeamYR;
    G4double BeamZ, BeamZR;
    G4double BeamT, BeamTR;
    G4double BeamP, BeamPR;
    G4int DecayFlag;

    G4int eventID;
    G4double  x,  y,  z;
    G4double px, py, pz;

    void GenerateUniform();

    //histograms
    TH1D *h_Eg_gene_;

};

#endif
