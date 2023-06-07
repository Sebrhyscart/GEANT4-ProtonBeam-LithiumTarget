#include "run.hh"
#include <iostream>
#include <fstream>

MyRun::MyRun()
{}

/*
MyRun::MyRun()
:fEDep(0.)
{
    fEDepScoreID = G4SDManager::GetSDManager()->GetCollectionID("myDet/myEDepScorer");
}
*/
MyRun::~MyRun()
{}

void MyRun::RecordEvent(const G4Event* event)
{
    G4Run::RecordEvent(event);
    /*
    
    //open up the hits collection
    //for i in the all of the events (parse through each event)
    //for each neutron present
    //report E1, E2, postprocessname (in decending energy to make them in order)
    //print to csv file
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    if (HCE) {
        
    }

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(HCE) {
   // This part of the code could be replaced to any kind of access
   // to hits collections and scores
   G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(fEDepScoreID));
   std::map<G4int,G4double*>::iterator itr = evtMap->GetMap()->begin();
   for(; itr != evtMap->GetMap()->end(); itr++) { fEDep += *(itr->second); }
  }
  G4Run::RecordEvent(evt);
  */
}

void MyRun::Merge(const G4Run* aRun)
{
  const MyRun* localRun = static_cast<const MyRun*>(aRun);
  //fEDep += localRun->fEDep;
  //code on how to merge the hits
  G4Run::Merge(aRun);
} 