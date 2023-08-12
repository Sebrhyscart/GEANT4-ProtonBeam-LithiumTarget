#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"

//create a Physics List class, inheriting from GEANT4's generic Physics List Class
class MyPhysicsList : public G4VModularPhysicsList
{
    public:
        MyPhysicsList(); //constructor
        ~MyPhysicsList(); //destructor
};

#endif