#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include <CLHEP/Random/Randomize.h>
#include <cmath>

//create a new Primary Generator class, inheriting from GEANT4's existing Primary Generator class
class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
        MyPrimaryGenerator(); //constructor
        ~MyPrimaryGenerator(); //destructor

        virtual void GeneratePrimaries(G4Event*); //function to generate primary particles for each event

    private:
        G4ParticleGun *fParticleGun; //attribute to hold the pointer to the Particle Gun 
        //** the particle Gun is an object that describes how the simulation should "shoot" protons/any starting particle
};

#endif