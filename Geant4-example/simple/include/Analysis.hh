#ifndef Analysis_h
#define Analysis_h 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <TH1.h>
#pragma GCC diagnostic pop

#include "globals.hh"

#include "ParamManager.hh"

class G4Run;
class G4Event;
class G4Step;

class Analysis
{
  public:
    Analysis();
    virtual ~Analysis();

    void BeginOfRun(const G4Run *aRun );
    void EndOfRun(const G4Run *aRun );
    void BeginOfEvent(const G4Event *aEvent );
    void EndOfEvent(const G4Event *aEvent );
    void Save();

  private:
    TFile *fRootFile;
    TTree *fTree;
    time_t start, end;
    void DefineRoot();
    ParamManager *paramMan;

  private:
    TH1D *h_E_gene;

    G4int evID;
    G4double Genmom3, Gentheta, Genphi;
    G4double Genpos_x, Genpos_y, Genpos_z;

    G4int VDnhit[2];
    G4double VDx[2], VDy[2], VDz[2];
    G4double VDpx[2], VDpy[2], VDpz[2];
    G4double VDtime[2];
    G4double VDedep[2];
    G4double VDpid[2], VDtrackid[2];

    G4double TOFedep[3];

};
#endif
