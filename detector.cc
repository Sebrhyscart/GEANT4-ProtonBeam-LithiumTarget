#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
    //This function detects the cherenkov photons. It includes multiple ways of reporting photon position
    //uncomment the desired output line
    G4Track *track = aStep->GetTrack();
    
    //track->SetTrackStatus(fStopAndKill);
    
    //Method 1: report exact photon position
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //photon enters detector
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //photon leaves detector

    G4ThreeVector posPhoton = preStepPoint->GetPosition(); //position of photon when it enters the detector

    G4cout << "thingy position: " << posPhoton << G4endl; //print exact photon positions to terminal
    /*
    //Method 2: report exactly which photon detectors have detected a photon
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber(); //returns the detector that has been hit by the detector (this is what we'd see irl)

    //G4cout << "Detector Number: " << copyNo << G4endl; //print which detectors have been hit by photons

    //Method 3: report the position of the center of each detector each time it detects a photon
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    //G4cout << "Detector position: " << posDetector << G4endl;
    */

    return true;
}