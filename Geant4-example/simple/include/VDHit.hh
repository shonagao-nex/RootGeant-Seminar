#ifndef VD_Hit_h
#define VD_Hit_h 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class VDHit : public G4VHit 
{
public:
  VDHit(const G4ThreeVector &gPos,
        const G4ThreeVector &gMom,
        G4double Time,
        G4int    Pid,
        G4int    TrackID,
        G4double Edep);

  ~VDHit();

  VDHit(const VDHit& right);
  const VDHit& operator = (const VDHit& right);
  G4int operator == (const VDHit& right) const;

  void* operator new(size_t);
  void  operator delete(void* aHit);

private:
  G4ThreeVector gpos;
  G4ThreeVector gmom;
  G4double time;
  G4int    pid;
  G4int    trackid;
  G4double edep;

public:
  void SetGPos(const G4ThreeVector agpos) { gpos    = agpos;    }
  void SetGMom(const G4ThreeVector agmom) { gmom    = agmom;    }
  void SetTime(G4double atime)            { time    = atime;    }
  void SetPID(G4int apid)                 { pid     = apid;     }
  void SetTrackID(G4int atrackid)         { trackid = atrackid; }
  void SetEdep(G4double aedep)            { edep    = aedep;    }

  const G4ThreeVector GetGPos() const { return gpos;    }
  const G4ThreeVector GetGMom() const { return gmom;    }
  G4double GetTime()            const { return time;    }
  G4int    GetPID()             const { return pid;     }
  G4int    GetTrackID()         const { return trackid; }
  G4double GetEdep()            const { return edep;    }

  virtual void Draw();
  virtual void Print();
};

typedef G4THitsCollection<VDHit> VDHitsCollection;
extern G4Allocator<VDHit> VDHitAllocator;

inline void* VDHit::operator new(size_t)
{
  void* aHit = (void*)VDHitAllocator.MallocSingle();
  return aHit;
}

inline void VDHit::operator delete(void* aHit)
{
  VDHitAllocator.FreeSingle((VDHit*) aHit);
}

#endif
