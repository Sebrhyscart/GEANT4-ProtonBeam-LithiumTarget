#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{} //constructor (no additional action is required => empty)
//** this constructor requires the unique name of the detector as an argument!

MySensitiveDetector::~MySensitiveDetector()
{} //destructor (no additional action is required => empty)

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
    //=========================================================================================================================
    //this function collects information about all of the particles that pass through it, and records it.
    //it is called for each step in each track in each event, and collects information about each step
    //=========================================================================================================================
    
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //SET THIS TO TRUE TO SPEED UP THE SIMULATION BY KILLING ALL NON-STRICTLY-NECESSARY PARTICLES
    G4bool KillAllParticlesThatArentProtonsOrNeutrons = false;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    G4Track *track = aStep->GetTrack(); //from the current step of the particle, get the particle's entrire track

    G4ParticleDefinition *particle = track->GetDefinition(); //get particle definition from the track
    G4String particleName = particle->GetParticleName(); //get name of particle

    if (particleName == "neutron") {
        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); //get the ID number of this event

        const G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //get point before step
        const G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //get point after step

        G4double preStepEnergy = preStepPoint->GetKineticEnergy(); //kinetic energy before step
        G4double postStepEnergy = postStepPoint->GetKineticEnergy(); //kinetic energy after step  
        G4ThreeVector posNeutron = preStepPoint->GetPosition(); //get neutron position before step

        G4String regionName = preStepPoint->GetTouchable()->GetVolume()->GetName(); //get the name of the region the neutron is detected in

        if (regionName == "physTarget") { //was the neutron detected in the target?
            //write all of the collected information to the Target file
            G4AnalysisManager *man = G4AnalysisManager::Instance(); //get the analysis manager

            //write the Data to Ntuple 0 (Ntuple 0 collects information for the Target)
            man->FillNtupleIColumn(0, 0, evt);
            man->FillNtupleDColumn(0, 1, preStepEnergy/MeV);
            man->FillNtupleDColumn(0, 2, postStepEnergy/MeV);
            man->FillNtupleDColumn(0, 3, posNeutron[0]/m);
            man->FillNtupleDColumn(0, 4, posNeutron[1]/m);
            man->FillNtupleDColumn(0, 5, posNeutron[2]/m);
            man->AddNtupleRow(0); //finish this row
        }
        else if (regionName == "physDetector") {//or was the neutron detected in the BF3 detector?
            //write all of the collected information to the Detector file
            G4AnalysisManager *man = G4AnalysisManager::Instance(); //get the analysis manager

            //write the Data to Ntuple 1 (Ntuple 1 collects information for the BF3 detector
            man->FillNtupleIColumn(1, 0, evt);
            man->FillNtupleDColumn(1, 1, preStepEnergy/MeV);
            man->FillNtupleDColumn(1, 2, postStepEnergy/MeV);
            man->FillNtupleDColumn(1, 3, posNeutron[0]/m);
            man->FillNtupleDColumn(1, 4, posNeutron[1]/m);
            man->FillNtupleDColumn(1, 5, posNeutron[2]/m);
            man->AddNtupleRow(1); //finish this row
        }
    }
    else if ((particleName != "proton") && (KillAllParticlesThatArentProtonsOrNeutrons)) {
        //if the particle is not a proton or a neutron AND the user sets KillAllParticlesThatArentProtonsOrNeutrons = true,
        //the particle is not necessary for the simulation, and it is killed to save CPU time
        track->SetTrackStatus(fStopAndKill);
    }
    return true; //this funtion must return true
}