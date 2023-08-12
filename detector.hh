#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4SystemOfUnits.hh"

//create a Sensitive Detector class, inherting from GEANT4's generic Sensitive Detector class
//** in GEANT4, a Sensitive Detector is a volumetic region in which information about the particles that travel
//through is collected -> how we get inforation out of GEANT4!
class MySensitiveDetector : public G4VSensitiveDetector
{
    public:
        MySensitiveDetector(G4String); //constructor, takes the unique name of the Sensitive Detector being constructed
        ~MySensitiveDetector(); //destructor

    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *); //function to describe what information about passing particles
        //to record, and how to save it for later access
};

#endif