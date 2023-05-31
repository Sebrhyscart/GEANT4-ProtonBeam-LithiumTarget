#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *analMan = G4AnalysisManager::Instance();

    analMan->OpenFile("output.root");

    analMan->CreateNtuple("Name", "Name");
    analMan->CreateNtupleIColumn("fEvent");
    analMan->CreateNtupleDColumn("fMass");
    analMan->CreateNtupleDColumn("fCharge");
    analMan->CreateNtupleDColumn("fSpin");
    analMan->FinishNtuple(0);

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *analMan = G4AnalysisManager::Instance();

    analMan->Write();
    analMan->CloseFile();
}
