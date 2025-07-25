//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B2/B2a/include/TrackerSD.hh
/// \brief Definition of the B2::TrackerSD class

#ifndef CherenkovSensitiveDetector_h
#define CherenkovSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include <vector>

class G4Material;
class G4Step;
class G4HCofThisEvent;

#include "TrackerHit.hh"

namespace Cherenkov
{
    class TrackerSD : public G4VSensitiveDetector
    {
    public:
        TrackerSD(G4String name);
        ~TrackerSD();

        // methods from base class
        void Initialize(G4HCofThisEvent*);
        G4bool ProcessHits(G4Step* astep, G4TouchableHistory* history);
        void EndOfEvent(G4HCofThisEvent*);

        void clear();
        void DrawAll();
        void PrintAll();

    private:
        UltraOpticalHitsCollection*  OpticalHitsCollection;; 
    };

} // namespace B2

#endif
