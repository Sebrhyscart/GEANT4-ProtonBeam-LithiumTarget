#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); //number of particle per event (THIS SHOULD STAY AS ONE PARTICLE PER EVENT!!)
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    //this method describes the paricles of the incident beam, produced by the accelerator
    //within this method, the type of particle, its energy, direction, source position, etc are defined

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //get the GEANT4 table of default particles
    G4String particleName = "proton"; //the name of the particle needed
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName); //get the particle from the particle table
    //G4ParticleDefinition is a class that describes all of the properties of a particle in it's attributes (mass, charge, energy, etc.)

    G4ThreeVector pos(0., 0., -1.*m); //proton beam point source position
    G4ThreeVector mom(0., 0., 1.); //proton beam point source momentum direction 
    //it is high energy physics convension to have the particle beam travel in the +z-direction
    //G4ThreeVector is a 3D Vector class in GEANT4

    fParticleGun->SetParticlePosition(pos); //set the beam source position 
    fParticleGun->SetParticleMomentumDirection(mom); //set the beam direction
    fParticleGun->SetParticleEnergy(2*MeV); //set the energy of each particle
    fParticleGun->SetParticleDefinition(particle); //set the particle type to the particle definition object above

    fParticleGun->GeneratePrimaryVertex(anEvent); //define a single GEANT4 event to be the transport of a single particle
}