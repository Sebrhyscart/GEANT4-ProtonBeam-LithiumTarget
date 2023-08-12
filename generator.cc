#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); //number of particles per event (THIS SHOULD STAY AS ONE PARTICLE PER EVENT!!)
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun; //put away your particle gun when you're done with it
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    //this method describes the paricles of the incident beam, produced by the accelerator
    //within this method, the type of particle, its energy, direction, source position, etc are defined

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //get the GEANT4 table of default particles
    G4String particleName = "proton"; //the name of the particle needed
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName); //get the particle from the particle table
    //G4ParticleDefinition is a class that describes all of the properties of a particle in it's attributes (mass, charge, energy, etc.)

    //source distribution: start at a point, but vary momentum direction to get a square on target instead of a point
    G4double LToTarget = 1.30 * m;
    G4double LRaster = 2.5 * cm;
    G4double thetaMax = std::atan(LRaster / LToTarget);

    G4double thetaX = thetaMax * (CLHEP::HepRandom::getTheEngine()->flat() - 0.5);
    G4double thetaY = thetaMax * (CLHEP::HepRandom::getTheEngine()->flat() - 0.5);

    G4ThreeVector pos(0., 0., -LToTarget); //proton beam point source position
    G4ThreeVector mom(std::tan(thetaX), std::tan(thetaY), 1.); //proton beam point source momentum direction 
    //G4ThreeVector mom(0, 0, 1.); //proton beam point source momentum direction 

    fParticleGun->SetParticlePosition(pos); //set the beam source position 
    fParticleGun->SetParticleMomentumDirection(mom); //set the beam direction
    //fParticleGun->SetParticleEnergy(2*MeV); //set the energy of each particle (this can be done in the UI instead so its commented out here)
    fParticleGun->SetParticleDefinition(particle); //set the particle type to the particle definition object above

    fParticleGun->GeneratePrimaryVertex(anEvent); //define a single GEANT4 event to be the transport of a single particle
}