#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GlobalMagFieldMessenger.hh"

namespace Cherenkov
{
    G4VPhysicalVolume *DetectorConstruction::Construct()
    {
        // Get nist material manager
        G4NistManager *nist = G4NistManager::Instance();

        G4double env_sizeXY = 2 * m, env_sizeZ = 2 * m;
        G4Material *env_mat = nist->FindOrBuildMaterial("G4_AIR");
        
        G4bool checkOverlaps = true;

        //
        // World
        //
        G4double world_sizeXY = 1.2 * env_sizeXY;
        G4double world_sizeZ = 1.2 * env_sizeZ;
        G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

        auto solidWorld =
            new G4Box("World",                                                    // its name
                      0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ); // its size

        auto logicWorld = new G4LogicalVolume(solidWorld, // its solid
                                              world_mat,  // its material
                                              "World");   // its name

        auto physWorld = new G4PVPlacement(nullptr,         // no rotation
                                           G4ThreeVector(), // at (0,0,0)
                                           logicWorld,      // its logical volume
                                           "World",         // its name
                                           nullptr,         // its mother  volume
                                           false,           // no boolean operation
                                           0,               // copy number
                                           checkOverlaps);  // overlaps checking

        //
        // Envelope
        //
        auto solidEnv = new G4Box("Envelope",                                           // its name
                                  0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ); // its size

        auto logicEnv = new G4LogicalVolume(solidEnv,    // its solid
                                            env_mat,     // its material
                                            "Envelope"); // its name

        new G4PVPlacement(nullptr,         // no rotation
                          G4ThreeVector(), // at (0,0,0)
                          logicEnv,        // its logical volume
                          "Envelope",      // its name
                          logicWorld,      // its mother  volume
                          false,           // no boolean operation
                          0,               // copy number
                          checkOverlaps);  // overlaps checking

        //
        // Shell of stainless steel
        //
        G4Material *shape1_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

        G4double inner_radius = 75 * cm;
        G4double outer_radius = 80 * cm;
        G4double height = 80 * cm;

        auto solidShape1 = new G4Tubs("Shell", inner_radius, outer_radius, height, 0, CLHEP::twopi);

        auto logicShape1 = new G4LogicalVolume(solidShape1, // its solid
                                               shape1_mat,  // its material
                                               "Shell");    // its name

        new G4PVPlacement(nullptr,         // no rotation
                          G4ThreeVector(), // at position
                          logicShape1,     // its logical volume
                          "Shell",         // its name
                          logicEnv,        // its mother  volume
                          false,           // no boolean operation
                          0,               // copy number
                          checkOverlaps);  // overlaps checking

        //
        // Water inside
        //
        G4Material *shape2_mat = nist->FindOrBuildMaterial("G4_WATER");

        G4double inner_radius_h20 = 0 * cm;
        G4double outer_radius_h20 = 75 * cm;
        G4double height_h20 = 80 * cm;

        auto solidShape2 = new G4Tubs("Water", inner_radius_h20, outer_radius_h20, height_h20, 0, CLHEP::twopi);

        auto logicShape2 = new G4LogicalVolume(solidShape2, // its solid
                                               shape2_mat,  // its material
                                               "Water");    // its name

        new G4PVPlacement(nullptr,         // no rotation
                          G4ThreeVector(), // at position
                          logicShape2,     // its logical volume
                          "Water",         // its name
                          logicEnv,        // its mother  volume
                          false,           // no boolean operation
                          0,               // copy number
                          checkOverlaps);  // overlaps checking

        // Set Shape2 as scoring volume
        //
        fScoringVolume = logicShape1;
        // // Set up Detectors
        G4Material *detMat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");

        G4double inner_radius_det = 0 * cm;
        G4double outer_radius_det = 10 * cm;
        G4double height_det = 10 * cm;

        auto solidDetector = new G4Tubs("Detector", inner_radius_det, outer_radius_det, height_det, 0, CLHEP::twopi);

        logicDetector = new G4LogicalVolume(solidDetector, // its solid
                                            detMat,        // its material
                                            "Detector");   // its name

        new G4PVPlacement(nullptr,                       // no rotation
                          G4ThreeVector(0, 0, -80 * cm), // at position
                          logicDetector,                 // its logical volume
                          "Detector",                    // its name
                          logicEnv,                      // its mother  volume
                          false,                         // no boolean operation
                          0,                             // copy number
                          checkOverlaps);                // overlaps checking

        G4int fNbOfChambers = 12;

        G4VisAttributes chamberVisAtt(G4Colour::Yellow());

        fLogicChamber = new G4LogicalVolume *[fNbOfChambers];

        G4int firstPosition = 0 * cm;

        G4int chamberSpacing = 10 * cm;

        for (G4int copyNo = 0; copyNo < fNbOfChambers; copyNo++)
        {
            G4double Zposition = firstPosition + copyNo * chamberSpacing;

            auto chamberS = new G4Tubs("Chamber_solid", 0, outer_radius_det, height_det, 0. * deg, 360. * deg);

            fLogicChamber[copyNo] = new G4LogicalVolume(chamberS, detMat, "Chamber_LV", nullptr, nullptr, nullptr);

            fLogicChamber[copyNo]->SetVisAttributes(chamberVisAtt);

            new G4PVPlacement(nullptr,                        // no rotation
                              G4ThreeVector(0, 0, Zposition), // at (x,y,z)
                              fLogicChamber[copyNo],          // its logical volume
                              "Chamber_PV",                   // its name
                              logicEnv,                       // its mother  volume
                              false,                          // no boolean operations
                              copyNo,                         // copy number
                              checkOverlaps);                 // checking overlaps
        }
        //
        // always return the physical World
        //
        return physWorld;
    }

    void DetectorConstruction::ConstructSDandField()
    {
        // Sensitive detectors

        G4String trackerChamberSDname = "/TrackerChamberSD";
        auto trackerSD = new TrackerSD(trackerChamberSDname, "TrackerHitsCollection");
        G4SDManager::GetSDMpointer()->AddNewDetector(trackerSD);
        // Setting trackerSD to all logical volumes with the same name
        // of "Chamber_LV".
        SetSensitiveDetector("Chamber_LV", trackerSD, true);
    }
}
