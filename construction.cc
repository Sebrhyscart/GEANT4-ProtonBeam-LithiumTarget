#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}
MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //Define Materials
    G4NistManager *nist = G4NistManager::Instance(); //get materials manager

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *Li = nist->FindOrBuildMaterial("G4_Li");

    //Define World
    G4Box *solidWorld = new G4Box("solidWorld", 0.1*m, 0.1*m, 0.1*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Define Target
    /*
    G4Box *solidTarget = new G4Box("solidTarget", 0.05*m, 0.05*m, 0.05*m);
    G4LogicalVolume *logicTarget = new G4LogicalVolume(solidTarget, Li, "logicTarget");
    G4VPhysicalVolume *physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTarget, "physTarget", logicWorld, false, 0, true);
    */
    G4Box *solidDetector = new G4Box("solidDetector", 0.05*m, 0.05*m, 0.05*m);
    logicDetector = new G4LogicalVolume(solidDetector, Li, "logicDetector");
    G4ThreeVector DetectorPos(0., 0., 0.);
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, DetectorPos, logicDetector, "physDetector", logicWorld, false, 0, true);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}


