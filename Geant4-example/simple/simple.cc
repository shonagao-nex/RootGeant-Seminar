#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "ParamManager.hh"
#include "Analysis.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "PhysicsList.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "GetRandomSeed.hh"
#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main( int argc, char** argv )
{
  G4String runID = "0000";
  G4String InputFileName = "param/input.in";
  G4String MacroFileName = "macro/gun.mac";
  G4UIExecutive* ui = 0;

  int ch;
  extern char *optarg;
  bool display = true;

  while( (ch=getopt(argc,argv,"hbp:r:m:"))!=-1 ){
    switch(ch){
      case 'h':
        std::cout<<std::endl;
        return 0;
        break;
      case 'b':
        display = false;
        break;
      case 'p':
        InputFileName = optarg;
        std::cout<<"Input File = "<<InputFileName<<std::endl;
        break;
      case 'm':
        MacroFileName = optarg;
        std::cout<<"Macro File = "<<MacroFileName<<std::endl;
        break;
      case 'r':
        runID = optarg;
        std::cout<<"runID = "<<runID<<std::endl;
        break;
      case '?':
        std::cout<<"unknown option..."<<std::endl;
        return 0;
        break;
      default:
        std::cout<<"type -h to see help"<<std::endl;
        return 0;
    }
  }

  if ( display == true ) { ui = new G4UIExecutive(argc, argv); }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  int initSeed=GetIntFromKernelEntropyPool()&0x7FFFFFFF;
  CLHEP::HepRandom::setTheSeed(initSeed);
  int startSeed=CLHEP::HepRandom::getTheSeed();
  G4cout << "Initial Seed = " << startSeed << G4endl;
  CLHEP::HepRandom::showEngineStatus();

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Parameter Manager
  ParamManager *paramManager = new ParamManager(runID, InputFileName);

  // Set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());

  // Set Physics List
//  G4VModularPhysicsList* physicsList = new FTFP_BERT;
//  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  PhysicsList *physicsList = new PhysicsList();
  runManager->SetUserInitialization(physicsList);
    
  // Set Analyzer
  Analysis *anaManager = new Analysis();

  // Set user action classes
  runManager->SetUserInitialization(new ActionInitialization(anaManager));

  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  std::cout<<"UI Manager"<<std::endl;
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if ( ! ui ) { 
    std::cout<<"batch mode"<<std::endl;
    G4String command = "/control/execute ";
    G4String fileName = MacroFileName;
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    std::cout<<"execute macro/init_vis.mac"<<std::endl;
    UImanager->ApplyCommand("/control/execute macro/init_vis.mac");
    if (ui->IsGUI()) {
      G4cout<<"execute macro/gui.mac"<<G4endl;
      UImanager->ApplyCommand("/control/execute macro/gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete paramManager;
  delete anaManager;
  delete runManager;
}

