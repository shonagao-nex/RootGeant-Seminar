#ifndef TOF_Hit_h
#define TOF_Hit_h 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class TOFHit : public G4VHit 
{
public:
  TOFHit(const G4ThreeVector &gPos,
        const G4ThreeVector &gMom,
        G4double Time,
        G4int    Pid,
        G4int    TrackID,
        G4double Edep);

  ~TOFHit();

  TOFHit(const TOFHit& right);
  const TOFHit& operator = (const TOFHit& right);
  G4int operator == (const TOFHit& right) const;

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

typedef G4THitsCollection<TOFHit> TOFHitsCollection;
extern G4Allocator<TOFHit> TOFHitAllocator;

inline void* TOFHit::operator new(size_t)
{
  void* aHit = (void*)TOFHitAllocator.MallocSingle();
  return aHit;
}

inline void TOFHit::operator delete(void* aHit)
{
  TOFHitAllocator.FreeSingle((TOFHit*) aHit);
}

#endif
