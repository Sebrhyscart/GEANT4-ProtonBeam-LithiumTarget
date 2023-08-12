#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh" //lets us specify units E.g. 1.5*m means 1.5 meters 

#include "detector.hh"

//create a new Geometry Construction class, inheriting from GEANT4's generic Geometry Construction class
//** this class is called Detector Construction, but all of the geometry is constructed within
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        MyDetectorConstruction(); //constructor
        ~MyDetectorConstruction(); //destructor

        virtual G4VPhysicalVolume *Construct(); //function to define and construct all of the geometry in the simulation
    
    private:
        G4LogicalVolume *logicTarget; //attribute to hold a pointer to the first Sensitive Detector, the Li target
        G4LogicalVolume *logicDetector; //attribute to hold a pointer to the 2nd Sensitive Detector, the BF3 detector
        virtual void ConstructSDandField(); //function to define the Sensitive Detectors
};

#endif