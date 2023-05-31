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

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *analMan = G4AnalysisManager::Instance();
    analMan->FillNtupleIColumn(0, evt);
    analMan->FillNtupleDColumn(1, mass);
    analMan->FillNtupleDColumn(2, charge);
    analMan->FillNtupleDColumn(3, mag);
    analMan->AddNtupleRow(0);
    return true;
}