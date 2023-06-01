#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4NeutronCrossSectionXS.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonElasticPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4PhysListFactoryMessenger.hh"

#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4HadronPhysicsFTF_BIC.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4HadronPhysicsQGS_BIC.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"

#include "G4SystemOfUnits.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4StepLimiterPhysics.hh"

#include "G4GenericBiasingPhysics.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  paramMan = ParamManager::GetParam();

//  SetDefaultCutValue(0.7*mm);
  decay      = paramMan->GetDecayFlag();
  verbose = 0;
  SetVerboseLevel(verbose);

  RegisterPhysics( new G4EmStandardPhysics(verbose));
//  RegisterPhysics( new G4EmStandardPhysics_option1(verbose));
//  RegisterPhysics( new G4EmStandardPhysics_option2(verbose));
//  RegisterPhysics( new G4EmStandardPhysics_option3(verbose));
//  RegisterPhysics( new G4EmStandardPhysics_option4(verbose));

  RegisterPhysics( new G4HadronPhysicsFTFP_BERT(verbose));
//  RegisterPhysics( new G4HadronPhysicsQGSP_BERT(verbose));

  RegisterPhysics( new G4EmExtraPhysics(verbose) );
  RegisterPhysics( new G4HadronElasticPhysics(verbose) );
  RegisterPhysics( new G4StoppingPhysics(verbose) );
  RegisterPhysics( new G4IonPhysics(verbose));
  RegisterPhysics( new G4NeutronTrackingCut(verbose));
  RegisterPhysics( new G4StepLimiterPhysics());

  if( decay > 0 ){
    G4cout<<"DecayPhysics: ON"<<G4endl;
    RegisterPhysics( new G4DecayPhysics(verbose) );
  } else{
    G4cout<<"DecayPhysics: OFF"<<G4endl;
  }
  RegisterPhysics( new G4RadioactiveDecayPhysics(verbose) );

  G4GenericBiasingPhysics *biasingPhysics = new G4GenericBiasingPhysics();
  biasingPhysics->Bias("gamma");
  RegisterPhysics( biasingPhysics );

}

PhysicsList::~PhysicsList()
{
  G4cout<<"Destructor PhysicsList"<<G4endl;
}

void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
  if (verbose>0) DumpCutValuesTable();
}
