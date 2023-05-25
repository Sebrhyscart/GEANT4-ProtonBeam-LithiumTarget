#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
    //This function detects the cherenkov photons. It includes multiple ways of reporting photon position
    //uncomment the desired output line

    //G4Track *track = aStep->GetTrack();
    //track->SetTrackStatus(fStopAndKill);
    
    //Method 1: report exact photon position

    G4Track *track = aStep->GetTrack();
    
    G4ParticleDefinition *particle = track->GetDefinition();
    G4String particleName = particle->GetParticleName(); 




    const G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //photon enters detector
    const G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //photon leaves detector

    G4double mass = preStepPoint->GetMass();
    G4double charge = preStepPoint->GetCharge();
    G4double mag = preStepPoint->GetMagneticMoment();

    G4ThreeVector pos1 = preStepPoint->GetPosition();
    G4ThreeVector pos2 = postStepPoint->GetPosition();
    G4double energy1 = preStepPoint->GetKineticEnergy();
    G4double energy2 = postStepPoint->GetKineticEnergy();

    G4cout << "Particle: " << particleName << " Pre/Post Energy: " << energy1 << ", " << energy2 << G4endl;

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