#include "G4ios.hh"
//#include "iomanip.h"
#include "globals.hh"

#include "MyPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4OpticalPhysics.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"

UltraPhysicsList::UltraPhysicsList() :  G4VModularPhysicsList(),
           fEmPhysicsList(0),
           fOpPhysicsList(0),
           fDecayPhysicsList(0),
           fVerboseLebel(1),
           fMaxNumPhotonStep(20)
{
  G4LossTableManager::Instance();
  SetDefaultCutValue(1*mm);

  // fMessenger = new UltraPhysicsListMessenger(this);
  // fStepMaxProcess = new StepMax();

  // Initilise flags

  SetVerboseLevel(1);


  // EM physics
  fEmName = G4String("emstandard");
  fEmPhysicsList = new G4EmStandardPhysics();
  fOpPhysicsList = new G4OpticalPhysics();

  // Decay Physics is always defined
  fDecayPhysicsList = new G4DecayPhysics();
}

UltraPhysicsList::~UltraPhysicsList()
{
  delete fDecayPhysicsList;
  delete fEmPhysicsList;
  delete fOpPhysicsList;
//  delete fStepMaxProcess;
}


void UltraPhysicsList::ConstructParticle()
{
  fDecayPhysicsList->ConstructParticle();
}


void UltraPhysicsList::ConstructProcess()
{
  AddTransportation();
  if (fEmPhysicsList)
    fEmPhysicsList->ConstructProcess();

  if (fOpPhysicsList)
    fOpPhysicsList->ConstructProcess();

  if (fDecayPhysicsList)
    fDecayPhysicsList->ConstructProcess();
}


void UltraPhysicsList::SetCuts()
{
  if (verboseLevel >1){
    G4cout << "UltraPhysicsList::SetCuts:";
  }
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  SetCutsWithDefault();
}
