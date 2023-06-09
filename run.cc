#include "run.hh"

MyRun::MyRun()
{}

MyRun::~MyRun()
{}

void MyRun::RecordEvent(const G4Event* event)
{
  G4Run::RecordEvent(event);
}

void MyRun::Merge(const G4Run* aRun)
{
  const MyRun* localRun = static_cast<const MyRun*>(aRun);
  G4Run::Merge(aRun);
} 
