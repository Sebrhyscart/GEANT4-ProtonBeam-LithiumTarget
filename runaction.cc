#include "runaction.hh"
#include <fstream>
#include <vector>

MyRunAction::MyRunAction()
{
    //=========================================================================================================================
    //constructor (called when an object from the MyRunAction class is created)
    //=========================================================================================================================

    //get an instance of the G4AnalysisManager, which collects data and writes it to file for later
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    //Tally neutrons produced in Li target
    man->CreateNtuple("Target", "Target"); //create an Ntuple to hold information we want in the target
    man->CreateNtupleIColumn("fEvent"); //create an I (interger) column to hold the event number 
    man->CreateNtupleDColumn("PreStepEnergy (MeV)"); //create a D (double) column to hold the pre-step energy
    man->CreateNtupleDColumn("PostStepEnergy (MeV)"); //...
    man->CreateNtupleDColumn("fX (m)");
    man->CreateNtupleDColumn("fY (m)");
    man->CreateNtupleDColumn("fZ (m)");
    man->FinishNtuple(0); //finish the Ntuple, and give it the ID of 0

    //Tally neutrons in the detector
    man->CreateNtuple("Detector", "Detector"); //create an Ntuple to hold information we want in the BF3 detector
    man->CreateNtupleIColumn("fEvent"); //same deal as above
    man->CreateNtupleDColumn("PreStepEnergy (MeV)");
    man->CreateNtupleDColumn("PostStepEnergy (MeV)");
    man->CreateNtupleDColumn("fX (m)");
    man->CreateNtupleDColumn("fY (m)");
    man->CreateNtupleDColumn("fZ (m)");
    man->FinishNtuple(1); //finish the Ntuple, and give it the ID of 1
}

MyRunAction::~MyRunAction()
{} //destructor (no additional action is required => empty)

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    //=========================================================================================================================
    //this function is called at the beginning of each run, and lets us execute some code before the run starts
    //here, we are simply opening an output.csv file for each thread to write their collected Ntuple information into
    //=========================================================================================================================

    //create the output files for this run (each thread will run this function and create 2 files: 1 for each Ntuple it has created)
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->OpenFile("output.csv");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    //=========================================================================================================================
    //this function is called at the end of each run, so we can execute code after the run has finished
    //here, we write all of the collected Ntuple data to the output files.
    //we also count the number of neutrons detected in the target and detector by reading the files back
    //=========================================================================================================================

    //write out data collected in this run
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();

    //read the files to determine the number of neutrons
    if (G4Threading::IsMasterThread()) //this is only exectuted by the master thread, the one thread to rule them all
    {
        G4cout << "------------------- Run Complete! -------------------" << G4endl;

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
            std::vector<G4bool> targetEvtList;

            G4String targetLine;
            std::ifstream targetFile(targetFileName);

            for (G4int j=0; j<10; j++) //reads throught the first 10 lines of comments
            {
                getline(targetFile, targetLine);
                targetEvtList.push_back(false);
            }
            while (getline(targetFile, targetLine))
            {
                G4int evt = std::stoi(targetLine.substr(0, targetLine.find(',')));

                while (evt > targetEvtList.size()) {
                    targetEvtList.push_back(false);
                }
                if (evt == targetEvtList.size()) { //if the vector is filled up to but not including event evt,
                    targetEvtList.push_back(true); //include the event as the evt'th element
                }
            }
            for (G4int k = 0; k < targetEvtList.size(); k++) 
            {
                if (targetEvtList[k]) {
                    numTargetNeutronsInThread++;
                }
            }

            numDetectorNeutronsInThread = 0;
            std::vector<G4bool> detectorEvtList;

            G4String detectorLine;
            std::ifstream detectorFile(detectorFileName);

            for (G4int j=0; j<10; j++) //reads throught the first 10 lines of comments
            {
                getline(detectorFile, detectorLine);
                detectorEvtList.push_back(false);
            }
            while (getline(detectorFile, detectorLine))
            {
                G4int evt = std::stoi(detectorLine.substr(0, detectorLine.find(',')));

                while (evt > detectorEvtList.size()) {
                    detectorEvtList.push_back(false);
                }
                if (evt == detectorEvtList.size()) { //if the vector is filled up to but not including event evt,
                    detectorEvtList.push_back(true); //include the event as the evt'th element
                }
            }
            for (G4int k = 0; k < detectorEvtList.size(); k++)
            {
                if (detectorEvtList[k]) {
                    numDetectorNeutronsInThread++;
                }
            }           
            numTargetNeutrons += numTargetNeutronsInThread;
            numDetectorNeutrons += numDetectorNeutronsInThread;
        }

        G4cout << "Total number of Neutrons produced in target: " << numTargetNeutrons << G4endl;
        G4cout << "Total number of Neutrons reaching the detector: " << numDetectorNeutrons << G4endl;
        G4cout << "-----------------------------------------------------" << G4endl;
    }
}