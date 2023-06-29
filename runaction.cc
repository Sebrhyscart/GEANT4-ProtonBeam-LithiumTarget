#include "runaction.hh"
#include "G4Threading.hh" 

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    if (!G4Threading::IsWorkerThread()) { //this should only be executed by the master thread, the one thread to rule them all
        G4int numThreads = G4Threading::G4GetNumberOfCores();

        for (G4int threadID=0; threadID < numThreads; threadID++) {

            std::string strthread = std::to_string(threadID);
            std::string fileName  = "output";
            fileName.append(strthread);
            fileName.append(".csv");

            std::ofstream myfile; 
            myfile.open(fileName);

            myfile << "Event Number,Particle Name,Energy 1 (MeV),Energy 2 (MeV),Stopping Process" << std::endl; 

            myfile.close();
        }
    }
}

void MyRunAction::EndOfRunAction(const G4Run* aRun)
{}
/*
void MyRunAction::EndOfRunAction(const G4Run* aRun)
{ 
    if (!G4Threading::IsWorkerThread()) { 

        G4int nofEvents = 100000000; 
        //G4int nofEvent = aRun->GetNumberOfEvent();

        G4int numNeutron = 0;
        G4int numThreads = G4Threading::G4GetNumberOfCores(); 

        for (G4int threadID=0; threadID < numThreads; threadID++) { //for each thread:

            std::string strthread = std::to_string(threadID);
            std::string fileName  = "output"; //find the output file that this thread has produced
            fileName.append(strthread);
            fileName.append(".csv");        

            std::ifstream csvfile(fileName); //open the output file
            std::vector<bool> evtVec; //vector of bools -> whether the event at index i happened in this thread
            std::string line;

            evtVec.push_back(false);

            getline(csvfile, line); //line of column names

            //G4cout << line << G4endl;

            while (getline(csvfile, line)) { //while there is still data on the current line of the file:

                int evt = std::stoi(line.substr(0, line.find(','))); //get the event number as the first column entry

                line.erase(0,line.find(',') + 1);

                G4String particle = line.substr(0, line.find(',')); //get the particle name as the second column entry

                while (evt > evtVec.size()) {
                    evtVec.push_back(false);
                }

                if (evt == evtVec.size()) { //if the vector is filled up to but not including event evt,
                    evtVec.push_back(true); //include the event as the evt'th element
                }

            }

            G4int numNthread = 0; 
            for (int j = 0; j < evtVec.size(); j++) {

                if (evtVec.at(j)) {
                    numNthread++;
                }
            }

            numNeutron += numNthread;
        }

        G4int numProton = nofEvents;

        G4double thickness = 0.2; //get thickness //cm
        G4double targetAtomicDensity = ((0.534 / 6.94) * 6.02214076e23); //(0.534 g/cm3) * ((1/6.94) mol/g) * (6.022e23 atoms/mol) //atoms/cm3

        G4double xsMicro = (numNeutron / (numProton * thickness * targetAtomicDensity)) * 1e26 ; //b

        //G4double beamEnergy = MyPrimaryGenerator::fPrimary->GetParticleGun()->GetParticleEnergy(); //get beam energy from the particle gun //MeV
        //G4double beamEnergy = G4ParticleGun::GetParticleEnergy();
        G4double beamEnergy = 2; //MeV

        G4double stdDev = 1/sqrt(nofEvents); //the standard deviation of a monte carlo method is ~1/sqrt(# of computations)
        
        //write calculated xs to a final file
        G4String xsFileName = "finalXSfile.csv";

        std::ofstream xsfile; //open the .csv file in append mode
        xsfile.open(xsFileName, std::ios::out | std::ios::app);

        xsfile << beamEnergy << "," << xsMicro << "," << stdDev << std::endl; //write out beam Energy (MeV), xs (b), and standard deviation

        xsfile.close(); 
    }
}
*/