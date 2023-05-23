#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh" //new
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT_HP.hh" //new

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    /*
    #ifdef G4MULTITHREADED //new
        G4MTRunManager* runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif
    */
    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction()); //Detector Geometry
    runManager->SetUserInitialization(new MyPhysicsList()); //Physics List
    runManager->SetUserInitialization(new MyActionInitialization()); //Action initialization

    G4VModularPhysicsList* physics = new QGSP_BERT_HP(); //new
    physics->RegisterPhysics(new G4DecayPhysics());
    runManager->SetUserInitialization(physics);

    //G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();

    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv); 

    G4VisManager *visManager = new G4VisExecutive(); 
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    //Run some UI commands automatically
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.2 0.2");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories rich");

    ui->SessionStart();

    return 0;
}