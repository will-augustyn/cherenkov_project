#ifndef CherenkovSteppingAction_h
#define CherenkovSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

namespace Cherenkov
{

    class EventAction;

    /// Stepping action class

    class SteppingAction : public G4UserSteppingAction
    {
    public:
        SteppingAction(EventAction *eventAction);
        ~SteppingAction() override = default;

        // method from the base class
        void UserSteppingAction(const G4Step *) override;

    private:
        EventAction *fEventAction = nullptr;
        G4LogicalVolume *fScoringVolume = nullptr;
    };

} // namespace B1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
