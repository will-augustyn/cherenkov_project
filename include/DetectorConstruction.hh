// Header guards
#ifndef CHERENKOVDetectorConstruction_h
#define CHERENKOVDetectorConstruction_h 1

// Base G4 class that our program will inherit from
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "SensitiveDetector.hh"

// Declare these classes without actually defining them
class G4VPhysicalVolume;
class G4LogicalVolume;

namespace Cherenkov
{

    /// Detector construction class to define materials and geometry.

    class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction() = default;
        ~DetectorConstruction() override = default;

        G4VPhysicalVolume *Construct() override;

        G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    private:
        G4LogicalVolume *logicDetector;
        virtual void ConstructSDandField();

    protected:
        G4LogicalVolume *fScoringVolume = nullptr;
    };

}

#endif