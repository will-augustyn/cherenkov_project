#ifndef CherenkovActionInitialization_h
#define CherenkovActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace Cherenkov
{

    /// Action initialization class.

    class ActionInitialization : public G4VUserActionInitialization
    {
    public:
        ActionInitialization() = default;
        ~ActionInitialization() override = default;

        void BuildForMaster() const override;
        void Build() const override;
    };

}

#endif
