#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
    //this function is called for each step in each track in this event, and will collect information about each step
    //everything in the SensitiveDetector is thread-local

    //=========================================================================================================
    //set this to true to speed up the simulation by removing all non-strictly-necessary particles
    G4bool KillAllParticlesThatArentProtonsOrNeutrons = false;
    //=========================================================================================================

    G4Track *track = aStep->GetTrack(); //Get particle track

    G4ParticleDefinition *particle = track->GetDefinition(); //Get particle definition from the track
    G4String particleName = particle->GetParticleName(); //Get name of particle

    if (particleName == "neutron") {
        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
        //returns the RunManager for the the worker thread, event ID belongs to worker thread

        const G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //Get point before step
        const G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //Get point after step

        G4double preStepEnergy = preStepPoint->GetKineticEnergy(); //kinetic energy before step
        G4double postStepEnergy = postStepPoint->GetKineticEnergy(); //kinetic energy after step  

        G4ThreeVector posNeutron = preStepPoint->GetPosition(); //get neutron position before step

        G4String regionName = preStepPoint->GetTouchable()->GetVolume()->GetName(); //get the name of the region the neutron is detected in

        if (regionName == "physTarget") { //was the neutron detected in the target?
            //write all of the collected information to the Target file
            G4AnalysisManager *man = G4AnalysisManager::Instance();

            man->FillNtupleIColumn(0, 0, evt);
            man->FillNtupleDColumn(0, 1, preStepEnergy);
            man->FillNtupleDColumn(0, 2, postStepEnergy);
            man->FillNtupleDColumn(0, 3, posNeutron[0]);
            man->FillNtupleDColumn(0, 4, posNeutron[1]);
            man->FillNtupleDColumn(0, 5, posNeutron[2]);
            man->AddNtupleRow(0);
        }
        else if (regionName == "physDetector") {//or was the neutron detected in the BF3 detector
            //write all of the collected information to the Detector file
            G4AnalysisManager *man = G4AnalysisManager::Instance();

            man->FillNtupleIColumn(1, 0, evt);
            man->FillNtupleDColumn(1, 1, preStepEnergy);
            man->FillNtupleDColumn(1, 2, postStepEnergy);
            man->FillNtupleDColumn(1, 3, posNeutron[0]);
            man->FillNtupleDColumn(1, 4, posNeutron[1]);
            man->FillNtupleDColumn(1, 5, posNeutron[2]);
            man->AddNtupleRow(1);
        }
    }
    else if ((particleName != "proton") && (KillAllParticlesThatArentProtonsOrNeutrons)) {
        track->SetTrackStatus(fStopAndKill);
    }
    return true;
}