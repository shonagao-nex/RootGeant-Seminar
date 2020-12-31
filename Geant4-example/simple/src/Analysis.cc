#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "VDSD.hh"
#include "VDHit.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include <time.h>

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
  
  /////////////////////
  // Virtual Detector//
  /////////////////////
  G4int vdID[2];
  VDHitsCollection* vdHC[2];

  for(int i=0;i<2;i++){
    vdID[i] = -1;
    std::ostringstream id;
    id << i;
    G4String DetName_VD = G4String("VD_") + id.str();
    vdID[i] = SDManager->GetCollectionID(DetName_VD);
    vdHC[i] = (VDHitsCollection*)(HCTE->GetHC(vdID[i]));
    if(!vdHC[i]){ std::cout<<"no VDHitsCollection"<<std::endl; return; }
    G4int vdhits = vdHC[i]->entries();
    VDnhit[i] = vdhits;

    VDtime[i] = -9999;
    VDpos[i].x = VDpos[i].y = VDpos[i].z = -9999;
    VDmom[i].x = VDmom[i].y = VDmom[i].z = -9999;
    VDpid[i] = VDtrackid[i] = -99;
    VDedep[i] = -9;

    if( vdhits > 0 ){
      VDHit *fVDhit_i = (*vdHC[i])[0];
      VDHit *fVDhit_l = (*vdHC[i])[vdhits-1];
      VDtime[i] = fVDhit_i->GetTime();
      G4ThreeVector VDgpos = fVDhit_i->GetGPos();
      G4ThreeVector VDgmom = fVDhit_i->GetGMom();
      VDpos[i].x = VDgpos.x(); VDpos[i].y = VDgpos.y(); VDpos[i].z = VDgpos.z();
      VDmom[i].x = VDgmom.x(); VDmom[i].y = VDgmom.y(); VDmom[i].z = VDgmom.z();
      VDpid[i]      = fVDhit_i->GetPID();
      VDtrackid[i]  = fVDhit_i->GetTrackID();
      VDedep[i]     = fVDhit_l->GetEdep();
    }
   
  }
  
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

  new TH1D("h_Eg_gene"      ,"h_Eg_gene"       ,200,0,2000);
  
  fTree = new TTree("tree","geant4");
  fTree->Branch("eventid" , &evID      , "eventid/I"     );
  fTree->Branch("mom_i"   , &Genmom3   , "mom_i/D"       );
  fTree->Branch("theta_i" , &Gentheta  , "theta_i/D"     );
  fTree->Branch("phi_i"   , &Genphi    , "phi_i/D"       );
  fTree->Branch("x_i"     , &Genpos_x  , "x_i/D"         );
  fTree->Branch("y_i"     , &Genpos_y  , "y_i/D"         );
  fTree->Branch("z_i"     , &Genpos_z  , "z_i/D"         );
  
  //Virtual Detector
  fTree->Branch("vdnhit"    , VDnhit     ,      "vdnhit[2]/I"      );
  fTree->Branch("vdpos0"    ,&VDpos[0]   ,      "x/D:y/D:z/D"      );
  fTree->Branch("vdmom0"    ,&VDmom[0]   ,      "x/D:y/D:z/D"      );
  fTree->Branch("vdpos1"    ,&VDpos[1]   ,      "x/D:y/D:z/D"      );
  fTree->Branch("vdmom1"    ,&VDmom[1]   ,      "x/D:y/D:z/D"      );
  fTree->Branch("vdtime"    , VDtime     ,      "vdtime[2]/D"      );
  fTree->Branch("vdpid"     , VDpid      ,      "vdpid[2]/I"       );
  fTree->Branch("vdtrackid" , VDtrackid  ,      "vdtrackid[2]/I"   );
  fTree->Branch("vdedep"    , VDedep     ,      "vdedep[2]/D"      );
}

