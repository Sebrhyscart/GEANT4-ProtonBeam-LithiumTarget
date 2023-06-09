#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); //number of particle per event
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //define the type of particles
    G4String particleName = "proton"; //Particle name (G4String is a string datatype in G4 specifically)
    G4ParticleDefinition *particle = particleTable->FindParticle("proton"); //Define the particle as a proton

    G4ThreeVector pos(0., 0., -1.*m); //proton beam point source position
    G4ThreeVector mom(0., 0., 1.); //proton beam point source momentum direction (momentum magnitude is give by kinetic energy in MeV)
    //It is high energy physics convension to have the particle beam travel in the +z-direction
    //G4ThreeVector is a 3D Vector

    fParticleGun->SetParticlePosition(pos); //set the beam source position 
    fParticleGun->SetParticleMomentumDirection(mom); //set the beam direction
    //fParticleGun->SetParticleMomentum(40.*MeV); 
    fParticleGun->SetParticleEnergy(5*MeV);
    fParticleGun->SetParticleDefinition(particle); //set the particle type to above (proton)

    fParticleGun->GeneratePrimaryVertex(anEvent);
}