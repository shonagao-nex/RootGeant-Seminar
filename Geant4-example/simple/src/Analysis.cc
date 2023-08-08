#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "VDSD.hh"
#include "VDHit.hh"
//#include "TOFSD.hh"
//#include "TOFHit.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include <time.h>
#include <iostream>
#include <sstream>

/////////////////////////////////
Analysis::Analysis()
: fRootFile(0), fTree(0)
{
  paramMan = ParamManager::GetParam();
  start=time(NULL);
  time(&start);
  DefineRoot();
}
/////////////////////////////////
Analysis::~Analysis(){
  G4cout<<"Destructor Analysis"<<G4endl;
  Save();
}
/////////////////////////////////
void Analysis::BeginOfRun(const G4Run *aRun ){
  G4cout<<"Start Run: "<<aRun->GetRunID()<<G4endl;
}
/////////////////////////////////
void Analysis::EndOfRun(const G4Run *aRun ){
  G4cout<<"End Run: "<<aRun->GetRunID()<<G4endl;
}
/////////////////////////////////
void Analysis::BeginOfEvent(const G4Event *aEvent ){
  evID = aEvent->GetEventID();
}
/////////////////////////////////
void Analysis::EndOfEvent(const G4Event *aEvent ){
  evID = aEvent->GetEventID();

  G4SDManager* SDManager = G4SDManager::GetSDMpointer();

  G4HCofThisEvent* HCTE= aEvent-> GetHCofThisEvent();
  if(!HCTE) return;

  if(evID%100000==0){
    end=time(NULL);
    time(&end);
    G4cout<<Form("eventID  %d  %.0lf sec",evID,difftime(end,start))<<G4endl;
  }
  /////////////////////
  //Initial condition//
  /////////////////////
  G4double Genmom_x = aEvent->GetPrimaryVertex()->GetPrimary()->GetPx();
  G4double Genmom_y = aEvent->GetPrimaryVertex()->GetPrimary()->GetPy();
  G4double Genmom_z = aEvent->GetPrimaryVertex()->GetPrimary()->GetPz();
  G4ThreeVector Genmom(Genmom_x, Genmom_y, Genmom_z);
  Genmom3  = Genmom.mag();
  Gentheta = Genmom.theta();
  Genphi   = Genmom.phi();
  Genpos_x = aEvent->GetPrimaryVertex()->GetX0();
  Genpos_y = aEvent->GetPrimaryVertex()->GetY0();
  Genpos_z = aEvent->GetPrimaryVertex()->GetZ0();

  h_E_gene->Fill( aEvent->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy() );
  
  /////////////////////
  // Virtual Detector//
  /////////////////////
  for(int i=0;i<2;i++){
    std::ostringstream ssid;
    ssid << i;
    G4String DetName_VD = G4String("VD" + ssid.str());
    G4int vdID = SDManager->GetCollectionID(DetName_VD);
    VDHitsCollection *vdHC = (VDHitsCollection*)(HCTE->GetHC(vdID));
    if(!vdHC){ std::cout<<"no VDHitsCollection"<<std::endl; return; }

    VDnhit[i] = 0;
    VDx[i]  = VDy[i]  = VDz[i] = -9999.;
    VDpx[i] = VDpy[i] = VDpz[i] = -9999.;
    VDtime[i] = VDedep[i] = -9999.;
    VDpid[i] = VDtrackid[i] = -9.;

    G4int vdhits = vdHC->entries();
    VDnhit[i] = vdhits;

    for(int h=0;h<vdhits;h++){
      VDHit *fVDhit = (*vdHC)[h];
      G4ThreeVector VDgpos = fVDhit->GetGPos();
      G4ThreeVector VDgmom = fVDhit->GetGMom();
      VDx[i]  = VDgpos.x();  VDy[i]  = VDgpos.y();  VDz[i]  = VDgpos.z();
      VDpx[i] = VDgmom.x();  VDpy[i] = VDgmom.y();  VDpz[i] = VDgmom.z();
      VDtime[i] = fVDhit->GetTime();
      VDedep[i] = fVDhit->GetEdep();
      VDpid[i]  = fVDhit->GetPID();
      VDtrackid[i] = fVDhit->GetTrackID();
    }
  }

  /////////////////
  // TOF Detector//
  /////////////////
//  for(int i=0;i<3;i++){
//    std::ostringstream ssid;
//    ssid << i;
//    G4String DetName_TOF = G4String("TOF" + ssid.str());
//    G4int tofID = SDManager->GetCollectionID(DetName_TOF);
//    TOFHitsCollection *tofHC = (TOFHitsCollection*)(HCTE->GetHC(tofID));
//    if(!tofHC){ std::cout<<"no TOFHitsCollection"<<std::endl; return; }
//
//    TOFedep[i] = -9999.;
//    G4int tofhits = tofHC->entries();
//
//    for(int h=0;h<tofhits;h++){
//      TOFHit *fTOFhit = (*tofHC)[h];
//      TOFedep[i] = fTOFhit->GetEdep();
//    }
//  }

  fTree->Fill();
}

/////////////////////////////////
void Analysis::Save(){
  fRootFile->Write();
  fRootFile->Close();
  if(fRootFile) delete fRootFile;
}

/////////////////////////////////
void Analysis::DefineRoot(){
  fRootFile = new TFile(paramMan->GetOutputFile(),"RECREATE","",0);
  if( !fRootFile ){
    G4cout<<"Problem creating the rootfile "<<paramMan->GetOutputFile()<<G4endl;
    return;
  }

  h_E_gene = new TH1D("h_E_gene"      ,"h_E_gene"       ,200,0,500);
  
  fTree = new TTree("tree","geant4");
  fTree->Branch("eventid" , &evID      , "eventid/I"     );
  fTree->Branch("mom_i"   , &Genmom3   , "mom_i/D"       );
  fTree->Branch("theta_i" , &Gentheta  , "theta_i/D"     );
  fTree->Branch("phi_i"   , &Genphi    , "phi_i/D"       );
  fTree->Branch("x_i"     , &Genpos_x  , "x_i/D"         );
  fTree->Branch("y_i"     , &Genpos_y  , "y_i/D"         );
  fTree->Branch("z_i"     , &Genpos_z  , "z_i/D"         );
  
//Virtual Detector
  fTree->Branch("vd0nhit"    ,&VDnhit[0]    ,      "vd0nhit/I"    );
  fTree->Branch("vd0x"       ,&VDx[0]       ,      "vd0x/D"       );
  fTree->Branch("vd0y"       ,&VDy[0]       ,      "vd0y/D"       );
  fTree->Branch("vd0z"       ,&VDz[0]       ,      "vd0z/D"       );
  fTree->Branch("vd0px"      ,&VDpx[0]      ,      "vd0px/D"      );
  fTree->Branch("vd0py"      ,&VDpy[0]      ,      "vd0py/D"      );
  fTree->Branch("vd0pz"      ,&VDpz[0]      ,      "vd0pz/D"      );
  fTree->Branch("vd0time"    ,&VDtime[0]    ,      "vd0time/D"    );
  fTree->Branch("vd0edep"    ,&VDedep[0]    ,      "vd0edep/D"    );
  fTree->Branch("vd0pid"     ,&VDpid[0]     ,      "vd0pid/I"     );
  fTree->Branch("vd0trackid" ,&VDtrackid[0] ,      "vd0trackid/I" );

  fTree->Branch("vd1nhit"    ,&VDnhit[1]    ,      "vd1nhit/I"    );
  fTree->Branch("vd1x"       ,&VDx[1]       ,      "vd1x/D"       );
  fTree->Branch("vd1y"       ,&VDy[1]       ,      "vd1y/D"       );
  fTree->Branch("vd1z"       ,&VDz[1]       ,      "vd1z/D"       );
  fTree->Branch("vd1px"      ,&VDpx[1]      ,      "vd1px/D"      );
  fTree->Branch("vd1py"      ,&VDpy[1]      ,      "vd1py/D"      );
  fTree->Branch("vd1pz"      ,&VDpz[1]      ,      "vd1pz/D"      );
  fTree->Branch("vd1time"    ,&VDtime[1]    ,      "vd1time/D"    );
  fTree->Branch("vd1edep"    ,&VDedep[1]    ,      "vd1edep/D"    );
  fTree->Branch("vd1pid"     ,&VDpid[1]     ,      "vd1pid/I"     );
  fTree->Branch("vd1trackid" ,&VDtrackid[1] ,      "vd1trackid/I" );

//  fTree->Branch("tofedep"    , TOFedep      ,      "tofedep[3]/D" );
}

