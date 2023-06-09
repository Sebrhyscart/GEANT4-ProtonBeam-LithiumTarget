#include "detector.hh"

#include <iostream>
#include <fstream>
#include <sstream>

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
    //everything in the SensitiveDetector is thread-local
    G4Track *track = aStep->GetTrack(); //Get particle track
    
    G4ParticleDefinition *particle = track->GetDefinition(); //Get particle definition from the track
    G4String particleName = particle->GetParticleName(); //Get name of particle

    if (particleName == "neutron") {
    
        const G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //Get point before step

        const G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //Get point after step
        const G4VProcess *postProcess = postStepPoint->GetProcessDefinedStep(); //Get the process/reaction that occured to end the step
        G4String postProcessName = postProcess->GetProcessName(); //Get the process name

        G4double energy1 = preStepPoint->GetKineticEnergy(); //kinetic energy before step
        G4double energy2 = postStepPoint->GetKineticEnergy(); //kinetic energy after step

        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
        //returns the RunManager for the the worker thread, event ID belongs to worker thread    
        
        G4int threadID =  G4Threading::G4GetThreadId(); //get the unique thread ID to open the output file for this specific thread
        std::string strthread = std::to_string(threadID); //use normal c++ string and file IO notation since I couldn't figure out
        std::string fileName  = "output"; //the GEANT4 string and file IO methods :)
        fileName.append(strthread);
        //append the name of the detector to the filename too once there are multiple detectors
        fileName.append(".csv");

        std::ofstream myfile; //open the .csv file in append mode
        myfile.open(fileName, std::ios::out | std::ios::app);


        myfile << evt << "," << particleName << "," << energy1 << "," << energy2 << "," << postProcessName << std::endl; //write out the collected data
        
        myfile.close();    
    }

    return true;
}