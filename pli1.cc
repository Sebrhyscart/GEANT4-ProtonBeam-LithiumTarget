#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh" 
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "QGSP_BERT_HP.hh"

int main(int argc, char** argv)
{
    
    #ifdef G4MULTITHREADED 
        G4MTRunManager* runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif

    runManager->SetUserInitialization(new MyDetectorConstruction()); //Detector Geometry
    runManager->SetUserInitialization(new MyPhysicsList()); //Physics List
    runManager->SetUserInitialization(new MyActionInitialization()); //Action initialization

    G4VModularPhysicsList* physics = new QGSP_BERT_HP(); //new
    physics->RegisterPhysics(new G4DecayPhysics());
    runManager->SetUserInitialization(physics);

    //G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
    runManager->SetNumberOfThreads(8);
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
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate -1");
    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID true");

    G4cout << "                                                                  -" << G4endl;
    G4cout << "                                                               -`" << G4endl;
    G4cout << "                                                           &lt;*               ~^." << G4endl;
    G4cout << "                                                       .s^           , c- \"" << G4endl;
    G4cout << "                                                    -&gt;^         ,g^\"  .- '`" << G4endl;
    G4cout << "                                  .----------     ~'     ,.c'*\".~ ` . - \"" << G4endl;
    G4cout << "                                .`        ,' I -`  .~0P$2-^.~-^`     ,,,-wg&amp;N" << G4endl;
    G4cout << "                               [`````````} jmE;@g$BPgQ,,ww=gB$$@@bg&amp;@gg&amp;&amp;&amp;.J" <<G4endl;
    G4cout << "                               [    ,,gg@@g@@@@@@@@@@$$B$$$$$$$$@@@@@@hg$$$&amp;," << G4endl;
    G4cout << "       ,,,,,,,,,wwggmmmm4NNPPP*$*PBNBBP@$B@@@NB@@@R&amp;&amp;&amp;&amp;ZZ&amp;$$$$$$$$$$$g$$$$$," <<G4endl;
    G4cout << "       `````                   [       ` 4^~]\"*NNgwg..`'  -- .,           ``" << G4endl;
    G4cout << "                               [,,,,,,,,L|      ~  `\"M@Z ~.   `\"   ~~.." << G4endl;
    G4cout << "                                                 ~ ` .    \"^ww` - ." << G4endl;
    G4cout << "                                                    `-. `~.      \"^-." << G4endl;
    G4cout << "                                                        ` ." << G4endl;
    G4cout << "    __  __      __  __           _                                   _                _ " << G4endl;
    G4cout << "   |  \\/  |    |  \\/  |         | |                /\\               | |              | |" << G4endl;
    G4cout << "   | \\  / | ___| \\  / | __ _ ___| |_ ___ _ __     /  \\   ___ ___ ___| | ___ _ __ __ _| |_ ___  _ __" << G4endl;
    G4cout << "   | |\\/| |/ __| |\\/| |/ _` / __| __/ _ \\ '__|   / /\\ \\ / __/ __/ _ \\ |/ _ \\ '__/ _` | __/ _ \\| '__|" << G4endl;
    G4cout << "   | |  | | (__| |  | | (_| \\__ \\ ||  __/ |     / ____ \\ (_| (_|  __/ |  __/ | | (_| | || (_) | |" << G4endl;
    G4cout << "   |_|  |_|\\___|_|  |_|\\__,_|___/\\__\\___|_|    /_/    \\_\\___\\___\\___|_|\\___|_|  \\__,_|\\__\\___/|_|" << G4endl;
    G4cout << "======================================================================================================" << G4endl;
    G4cout << "======================================================================================================" << G4endl;
    G4cout << "                  Geant4 Simulation Written by Sebastian Carter and Jadyn Yaroshuk" << G4endl;

    ui->SessionStart();

    return 0;
}