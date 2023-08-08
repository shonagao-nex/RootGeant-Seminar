#include "TOFHit.hh"

G4Allocator<TOFHit> TOFHitAllocator;

TOFHit::TOFHit(const G4ThreeVector &gPos,
               const G4ThreeVector &gMom,
               G4double             Time,
               G4int                Pid,
               G4int                TrackID,
               G4double             Edep)
 : gpos(gPos), gmom(gMom), time(Time), pid(Pid), trackid(TrackID), edep(Edep)
{
}

TOFHit::~TOFHit()
{
}

void TOFHit::Draw()
{
}

void TOFHit::Print()
{
}


