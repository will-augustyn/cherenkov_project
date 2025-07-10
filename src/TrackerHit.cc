#include "TrackerHit.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<UltraOpticalHit> *UltraOpticalHitAllocator=0;


UltraOpticalHit::UltraOpticalHit()
{

  fPhotEne      = 0.0;
  fPhotPos      = G4ThreeVector();

}

UltraOpticalHit::~UltraOpticalHit()
{;}

UltraOpticalHit::UltraOpticalHit(const UltraOpticalHit& right) : G4VHit()
{
  fPhotEne     =  right.fPhotEne;
  fPhotPos     =  right.fPhotPos;

}

const UltraOpticalHit& UltraOpticalHit::operator=(const UltraOpticalHit& right)
{
  fPhotEne =  right.fPhotEne;
  fPhotPos =  right.fPhotPos;

  return *this;
}

G4bool UltraOpticalHit::operator==(const UltraOpticalHit& right) const
{
  return (this==&right) ? true : false;
}

void UltraOpticalHit::Draw()
{;}

void UltraOpticalHit::Print()
{

  G4cout << fPhotEne/keV << G4endl;
  G4cout << fPhotPos/mm      << G4endl;
}
