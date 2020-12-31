#include "VDHit.hh"

G4Allocator<VDHit> VDHitAllocator;

VDHit::VDHit(const G4ThreeVector &gPos,
             const G4ThreeVector &gMom,
             G4double             Time,
             G4int                Pid,
             G4int                TrackID,
             G4double             Edep)
 : gpos(gPos), gmom(gMom), time(Time), pid(Pid), trackid(TrackID), edep(Edep)
{
}

VDHit::~VDHit()
{
}

void VDHit::Draw()
{
}

void VDHit::Print()
{
}


