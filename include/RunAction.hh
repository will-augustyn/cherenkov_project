#ifndef CherenkovRunAction_h
#define CherenkovRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

namespace Cherenkov
{

    /// Run action class
    ///
    /// In EndOfRunAction(), it calculates the dose in the selected volume
    /// from the energy deposit accumulated via stepping and event actions.
    /// The computed dose is then printed on the screen.

    class RunAction : public G4UserRunAction
    {
    public:
        RunAction();
        ~RunAction() override = default;

        void BeginOfRunAction(const G4Run *) override;
        void EndOfRunAction(const G4Run *) override;

        void AddEdep(G4double edep);

    private:
        G4Accumulable<G4double> fEdep = 0.;
        G4Accumulable<G4double> fEdep2 = 0.;
    };

} // namespace B1

#endif