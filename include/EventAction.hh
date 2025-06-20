#ifndef CherenkovEventAction_h
#define CherenkovEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

namespace Cherenkov
{

  class RunAction;

  /// Event action class

  class EventAction : public G4UserEventAction
  {
  public:
    EventAction(RunAction *runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *event) override;
    void EndOfEventAction(const G4Event *event) override;

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    RunAction *fRunAction = nullptr;
    G4double fEdep = 0.;
  };

}

#endif
