#include "runaction.hh"
#include "G4Threading.hh" 

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  /*
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //get the GEANT4 table of default particles
    G4String particleName = "proton"; //the name of the particle needed
    const G4ParticleDefinition *particle = particleTable->FindParticle(particleName); //get the particle from the particle table
    const G4ParticleDefinition& theProton = *particle;
    G4CrossSectionDataStore::DumpPhysicsTable(theProton); //idk man

    //G4CrossSectionDataStore::AddDataSet(theData) //?? this aint the place to add xs

    //G4CrossSectionDataStore::BuildPhysicsTable(theProton); //No instance of G4CrossSectionDataStore object at this point :(
    //G4CrossSectionDataStore::DumpPhysicsTable(theProton); //idk man
  */

  //re-create the .csv files (so they start each run as EMPTY (since other parts of code only append))
}
void MyRunAction::EndOfRunAction(const G4Run* aRun)
{
  //move the python post processing script in here maybe

  //numProton = getNumEventsProcessed()
}