#include "runaction.hh"
#include "G4Threading.hh" 

MyRunAction::MyRunAction()
{   
    /*
    std::ofstream myfile;
    myfile.open("neutronData.csv");
    myfile << "EventID,Particle,Energy1 [MeV],Energy2 [MeV],EndProcess\n";
    myfile.close();
    */
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  /*

    G4int threadID =  G4Threading::G4GetThreadId(); //get the unique thread ID to open the output file for this specific thread
    std::string strthread = std::to_string(threadID); //use normal c++ string and file IO notation since I couldn't figure out
    std::string fileName  = "output"; //the GEANT4 string and file IO methods :)
    fileName.append(strthread);
    fileName.append(".csv");

    std::ofstream myfile; //open the file to create an instance of it
    myfile.open(fileName); 
    myfile.close();



  const MyRun* theRun = static_cast<const MyRun*>aRun;
  if(IsWorker()) {
    G4String threadID = G4Threading::G4GetThreadId();

    std::ofstream myfile;
    G4Sting fileName = "Output" + threadID + ".csv";
    myfile.open(fileName);
    myfile.close();

  }
  */
  
  
  
  //OR
  //if worker thread, 
  //get thread ID
  //open a csv file with thread ID in the name 
  //then each thread can write to its own file
}

void MyRunAction::EndOfRunAction(const G4Run* aRun)
{
  /*
  const MyRun* theRun = static_cast<const MyRun*>aRun;
  if(IsMaster())
  {
    //write all results from the hits to the file
    std::ofstream myfile;
    myfile.open("neutronData.csv");
    for loop {
      if neutron BS
      add the data one line at a time :)
    }




    G4cout << "Global result with " << theRun->GetNumberOfEvent()
           << " events : " << theRun->GetTotalEDep()/GeV << " [GeV]" << G4endl;
  } else {
    
    //
    G4cout << "Local thread result with " << theRun->GetNumberOfEvent()
           << " events : " << theRun->GetTotalEDep()/GeV << " [GeV]" << G4endl;
  }
  */
}