#include "TrackerSD.hh"
#include "G4Material.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4ios.hh"

namespace Cherenkov
{

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    TrackerSD::TrackerSD(G4String name):G4VSensitiveDetector(name)
    {
        collectionName.insert("OpticalHitsCollection");
    }

    TrackerSD::~TrackerSD()
    {;}
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    void TrackerSD::Initialize(G4HCofThisEvent* hce)
    {
        static int HCID1 = -1;

        //this will get defined in trackerhit.hh
        OpticalHitsCollection = new UltraOpticalHitsCollection(SensitiveDetectorName,collectionName[0]);

        if(HCID1<0)
        { HCID1 = GetCollectionID(0); }
        hce->AddHitsCollection(HCID1,OpticalHitsCollection);
    }

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
    {
        auto thisVolume = aStep->GetTrack()->GetVolume()->GetName() ;
        const auto particle = aStep->GetTrack()->GetDefinition();

        if (thisVolume != "Detector")
            return false;
        if (particle != G4OpticalPhoton::Definition() )
            return false;

        if(particle == G4OpticalPhoton::Definition())
            aStep->GetTrack()->SetTrackStatus(fStopAndKill);

        auto kineticEnergy = aStep->GetTrack()->GetKineticEnergy();
        auto HitPosition = aStep->GetPreStepPoint()->GetPosition();

        auto OpticalHit = new UltraOpticalHit;
        OpticalHit->SetEnergy(kineticEnergy);
        OpticalHit->SetPosition(HitPosition);

        OpticalHitsCollection->insert(OpticalHit);

        G4cout << "*******************************" << G4endl;
        G4cout << "             PMT HIT           " << G4endl;
        G4cout << "  Volume:                      " << thisVolume << G4endl;
        G4cout << "  Photon energy (eV) :         " << kineticEnergy/CLHEP::eV << G4endl;
        G4cout << "  POSITION (mm) :              "
            << HitPosition.x()/CLHEP::mm << " " << HitPosition.y()/CLHEP::mm << " " << HitPosition.z()/CLHEP::mm << G4endl;
        G4cout << "*******************************" << G4endl;

        return true;
    }

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    void TrackerSD::EndOfEvent(G4HCofThisEvent* hce)
    {
        static G4int HCID = -1;
        if(HCID<0)
            {
                HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
            }
        hce->AddHitsCollection(HCID,OpticalHitsCollection);

    }

        //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

    void TrackerSD::clear()
    {;}

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

    void TrackerSD::DrawAll()
    {;}

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

    void TrackerSD::PrintAll()
    {;}

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

} 
