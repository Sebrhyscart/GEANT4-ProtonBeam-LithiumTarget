#include <iostream> //general c++ data IO to terminal

#include "G4RunManager.hh" //import header files needed to run GEANT4
#include "G4MTRunManager.hh" 
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Threading.hh" 

#include "construction.hh" //import the header files written for this application
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    #ifdef G4MULTITHREADED //run GEANT4 in multithreaded mode if available
        G4MTRunManager* runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif

    G4bool RunWithNoVis = false; //set this to true to run on Dr. Buijs' computer

    runManager->SetUserInitialization(new MyDetectorConstruction()); //initilize Geometry
    runManager->SetUserInitialization(new MyPhysicsList()); //initilaize physics (electromagnetic)
    runManager->SetUserInitialization(new MyActionInitialization()); //intilize user actions

    if (RunWithNoVis) {
        G4int numThreads  = 12;
    }
    else {
        G4int numThreads = G4Threading::G4GetNumberOfCores(); //get the number of available cores on this computer
    }

    runManager->SetNumberOfThreads(numThreads); //set the simulation to use the ideal number of threads
    runManager->Initialize(); //initilize the RunManager

    if (RunWithNoVis) {
        //initilize UI
        G4UIExecutive *ui = new G4UIExecutive(argc, argv); //set up UI
        G4UImanager *UImanager = G4UImanager::GetUIpointer();

        //initilize UI with some commands
        UImanager->ApplyCommand("/process/had/particle_hp/skip_missing_isotopes true");
        UImanager->ApplyCommand("/process/had/particle_hp/do_not_adjust_final_state true");

        //print ASCII art!
        G4cout << "                                                                  ~"                                             << G4endl;
        G4cout << "                                                               -`"                                               << G4endl;
        G4cout << "                                                           &lt;*               ~^."                              << G4endl;
        G4cout << "                                                       .s^           , c- \""                                    << G4endl;
        G4cout << "                                                    -&gt;^         ,g^\"  .- '`"                                 << G4endl;
        G4cout << "                                  .----------     ~'     ,.c'*\".~ ` . - \""                                     << G4endl;
        G4cout << "                                .`        ,' I -`  .~0P$2-^.~-^`     ,,,-wg&amp;N"                               << G4endl;
        G4cout << "                               [`````````} jmE;@g$BPgQ,,ww=gB$$@@bg&amp;@gg&amp;&amp;&amp;.J"                    << G4endl;
        G4cout << "                               [    ,,gg@@g@@@@@@@@@@$$B$$$$$$$$@@@@@@hg$$$&amp;,"                               << G4endl;
        G4cout << "       ,,,,,,,,,wwggmmmm4NNPPP*$*PBNBBP@$B@@@NB@@@R&amp;&amp;&amp;&amp;ZZ&amp;$$$$$$$$$$$g$$$$$,"                << G4endl;
        G4cout << "       `````                   [       ` 4^~]\"*NNgwg..`'  -- .,           ``"                                   << G4endl;
        G4cout << "                               [,,,,,,,,L|      ~  `\"M@Z ~.   `\"   ~~.."                                       << G4endl;
        G4cout << "                                                 ~ ` .    \"^ww` - ."                                            << G4endl;
        G4cout << "                                                    `-. `~.      \"^-."                                          << G4endl;
        G4cout << "                                                        ` ."                                                     << G4endl;
        G4cout << "    __  __      __  __           _                                   _                _ "                        << G4endl;
        G4cout << "   |  \\/  |    |  \\/  |         | |                /\\               | |              | |"                     << G4endl;
        G4cout << "   | \\  / | ___| \\  / | __ _ ___| |_ ___ _ __     /  \\   ___ ___ ___| | ___ _ __ __ _| |_ ___  _ __"          << G4endl;
        G4cout << "   | |\\/| |/ __| |\\/| |/ _` / __| __/ _ \\ '__|   / /\\ \\ / __/ __/ _ \\ |/ _ \\ '__/ _` | __/ _ \\| '__|"    << G4endl;
        G4cout << "   | |  | | (__| |  | | (_| \\__ \\ ||  __/ |     / ____ \\ (_| (_|  __/ |  __/ | | (_| | || (_) | |"            << G4endl;
        G4cout << "   |_|  |_|\\___|_|  |_|\\__,_|___/\\__\\___|_|    /_/    \\_\\___\\___\\___|_|\\___|_|  \\__,_|\\__\\___/|_|"   << G4endl;
        G4cout << "======================================================================================================"          << G4endl;
        G4cout << "======================================================================================================"          << G4endl;
        G4cout << "                  Geant4 Simulation Written by Sebastian Carter and Jadyn Yaroshuk"                              << G4endl;

    }
    else {
        //initilize UI
        G4UIExecutive *ui = new G4UIExecutive(argc, argv); //set up UI

        G4VisManager *visManager = new G4VisExecutive(); //initilize the geometry visualization window
        visManager->Initialize();

        G4UImanager *UImanager = G4UImanager::GetUIpointer();

        //initilize UI with commands 
        UImanager->ApplyCommand("/process/had/particle_hp/skip_missing_isotopes true");
        UImanager->ApplyCommand("/process/had/particle_hp/do_not_adjust_final_state true");

        UImanager->ApplyCommand("/vis/open OGL"); //open the geometry viewer window
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.2 0.2"); //set the perspective
        UImanager->ApplyCommand("/vis/drawVolume"); //draw the simulation geometryS
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true"); //autorefresh viewer
        UImanager->ApplyCommand("/vis/scene/add/trajectories"); //draw particle trajectories
        UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate -1"); //accumulate all events before displaying
        UImanager->ApplyCommand("/vis/multithreading/maxEventQueueSize -1"); //queue all events
        UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID true"); //draw trajectories in colour by particle type

        //print ASCII art!
        G4cout << "                                                                  ~"                                             << G4endl;
        G4cout << "                                                               -`"                                               << G4endl;
        G4cout << "                                                           &lt;*               ~^."                              << G4endl;
        G4cout << "                                                       .s^           , c- \""                                    << G4endl;
        G4cout << "                                                    -&gt;^         ,g^\"  .- '`"                                 << G4endl;
        G4cout << "                                  .----------     ~'     ,.c'*\".~ ` . - \""                                     << G4endl;
        G4cout << "                                .`        ,' I -`  .~0P$2-^.~-^`     ,,,-wg&amp;N"                               << G4endl;
        G4cout << "                               [`````````} jmE;@g$BPgQ,,ww=gB$$@@bg&amp;@gg&amp;&amp;&amp;.J"                    << G4endl;
        G4cout << "                               [    ,,gg@@g@@@@@@@@@@$$B$$$$$$$$@@@@@@hg$$$&amp;,"                               << G4endl;
        G4cout << "       ,,,,,,,,,wwggmmmm4NNPPP*$*PBNBBP@$B@@@NB@@@R&amp;&amp;&amp;&amp;ZZ&amp;$$$$$$$$$$$g$$$$$,"                << G4endl;
        G4cout << "       `````                   [       ` 4^~]\"*NNgwg..`'  -- .,           ``"                                   << G4endl;
        G4cout << "                               [,,,,,,,,L|      ~  `\"M@Z ~.   `\"   ~~.."                                       << G4endl;
        G4cout << "                                                 ~ ` .    \"^ww` - ."                                            << G4endl;
        G4cout << "                                                    `-. `~.      \"^-."                                          << G4endl;
        G4cout << "                                                        ` ."                                                     << G4endl;
        G4cout << "    __  __      __  __           _                                   _                _ "                        << G4endl;
        G4cout << "   |  \\/  |    |  \\/  |         | |                /\\               | |              | |"                     << G4endl;
        G4cout << "   | \\  / | ___| \\  / | __ _ ___| |_ ___ _ __     /  \\   ___ ___ ___| | ___ _ __ __ _| |_ ___  _ __"          << G4endl;
        G4cout << "   | |\\/| |/ __| |\\/| |/ _` / __| __/ _ \\ '__|   / /\\ \\ / __/ __/ _ \\ |/ _ \\ '__/ _` | __/ _ \\| '__|"    << G4endl;
        G4cout << "   | |  | | (__| |  | | (_| \\__ \\ ||  __/ |     / ____ \\ (_| (_|  __/ |  __/ | | (_| | || (_) | |"            << G4endl;
        G4cout << "   |_|  |_|\\___|_|  |_|\\__,_|___/\\__\\___|_|    /_/    \\_\\___\\___\\___|_|\\___|_|  \\__,_|\\__\\___/|_|"   << G4endl;
        G4cout << "======================================================================================================"          << G4endl;
        G4cout << "======================================================================================================"          << G4endl;
        G4cout << "                  Geant4 Simulation Written by Sebastian Carter and Jadyn Yaroshuk"                              << G4endl;
    }

    ui->SessionStart(); //Start the interactive UI
    return 0;
}