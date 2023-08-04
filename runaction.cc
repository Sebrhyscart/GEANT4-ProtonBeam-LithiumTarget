#include "runaction.hh"
#include <fstream>

MyRunAction::MyRunAction()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    //Tally neutrons produced in Li target
    man->CreateNtuple("Target", "Target");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("PreStepEnergy");
    man->CreateNtupleDColumn("PostStepEnergy");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    //Tally neutrons in the detector
    man->CreateNtuple("Detector", "Detector");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("PreStepEnergy");
    man->CreateNtupleDColumn("PostStepEnergy");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(1);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    //create the output files for this run
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->OpenFile("output.csv");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    //write out data collected in this run
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();

    
    //read the files to determine the number of neutrons
    if (G4Threading::IsMasterThread())
    {
        G4cout << "------------------- Run Complete -------------------" << G4endl;

        G4int numTargetNeutrons = 0;
        G4int numDetectorNeutrons = 0;

        G4int numTargetNeutronsInThread = 0;
        G4int numDetectorNeutronsInThread = 0;

        for (G4int i=0; i<G4Threading::GetNumberOfRunningWorkerThreads(); i++)
        {
            std::stringstream strThreadID;
            strThreadID << i;
            G4String targetFileName = "output_nt_Target_t" + strThreadID.str() + ".csv";
            G4String detectorFileName = "output_nt_Detector_t" + strThreadID.str() + ".csv";

            numTargetNeutronsInThread = 0;

            G4String targetLine;
            std::ifstream targetFile(targetFileName);
            for (G4int j = 0; j < 10; j++) //reads throught the first 10 lines of comments
            {
                getline(targetFile, targetLine);
            }
            while (getline(targetFile, targetLine))
            {
                numTargetNeutronsInThread += 1;
            }

            numDetectorNeutronsInThread = 0;

            G4String detectorLine;
            std::ifstream detectorFile(detectorFileName);
            for (G4int j = 0; j < 10; j++) //reads throught the first 10 lines of comments
            {
                getline(detectorFile, targetLine);
            }

            while (getline(detectorFile, targetLine))
            {
                numDetectorNeutronsInThread += 1;
            }
            
            numTargetNeutrons += numTargetNeutronsInThread;
            numDetectorNeutrons += numDetectorNeutronsInThread;
        }

        G4cout << "Total number of Neutrons produced in target: " << numTargetNeutrons << G4endl;
        G4cout << "Total number of Neutrons reaching the detector: " << numDetectorNeutrons << G4endl;
        G4cout << "----------------------------------------------------" << G4endl;
    }
}