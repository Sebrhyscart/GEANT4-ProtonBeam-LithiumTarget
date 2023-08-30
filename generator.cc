#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    //=========================================================================================================================
    //constructor (called when an object from the MyPrimaryGenerator class is created)
    //=========================================================================================================================

    fParticleGun = new G4ParticleGun(1); //create a new Particle Gun in the Primatry Generator constructor
    //the Particle Gun constructor, G4ParticleGun(1) takes 1 argument, the number of primary particles per event
    //THIS SHOULD STAY AS ONE PARTICLE PER EVENT!!
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    //=========================================================================================================================
    //destructor (called when an object from the MyPrimaryGenerator class is deleted)
    //=========================================================================================================================

    delete fParticleGun; //put away your particle gun when you're done with it
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    //=========================================================================================================================
    //this function describes and generates primary particles. This is how the incident beam of protons is defined
    //within this function, the: type, source position, energy, and direction of the incident particle is defined
    //the particle gun is then called to "shoot" the defined particle
    //=========================================================================================================================

    //get the particle type:
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //get the GEANT4 table of default particles
    G4String particleName = "proton"; //the name of the particle we want
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName); //get the particle from the particle table
    //** G4ParticleDefinition is a class that describes all of the properties of a particle in it's attributes (mass, charge, energy, etc.)

    //define the source:
    //** here we wil define the starting position, as well as the 'Raster System' of the Tandetron Accelerator
    //** the 'Raster System' takes the thin beam of protons, and sweeps it out into a square that lands on the target
    G4double LToTarget = 1.30 * m; //distance from source position to target
    G4double LRaster = 2.5 * cm; //full side length of the square proton beam landing on target

    G4double thetaMax = std::atan(LRaster / LToTarget); //maximum deflection angle allowed in the Raster system
    G4double thetaX = thetaMax * (CLHEP::HepRandom::getTheEngine()->flat() - 0.5); //choose a random angle from Z axis in X direction
    G4double thetaY = thetaMax * (CLHEP::HepRandom::getTheEngine()->flat() - 0.5); //choose a random angle from Z axis in Y direction

    G4ThreeVector pos(0., 0., -LToTarget); //Source position of the proton beam
    G4ThreeVector mom(std::tan(thetaX), std::tan(thetaY), 1.); //Momentum direction of the proton beam
    //G4ThreeVector mom(0, 0, 1.); //proton beam point source momentum direction (use this to get a perfectly straight beam on target)

    //shoot the chosen particle, from the chosen position, in the chosen direction
    fParticleGun->SetParticlePosition(pos); //set the beam source position 
    fParticleGun->SetParticleMomentumDirection(mom); //set the beam direction
    //fParticleGun->SetParticleEnergy(1*MeV); //set the energy of each particle (to be set in the UI)
    fParticleGun->SetParticleDefinition(particle); //set the particle type to the particle definition object above

    fParticleGun->GeneratePrimaryVertex(anEvent); //Shoot the particle to start this event!
}