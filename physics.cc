#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    //=========================================================================================================================
    //constructor (called when a MyPhysicsList object is created)
    //this funtion adds all of the physical processes to be modeled to the physics list
    //=========================================================================================================================

    RegisterPhysics(new G4EmStandardPhysics()); //electromagnetic standard physics
    RegisterPhysics(new G4DecayPhysics()); //decay physics
    RegisterPhysics(new G4RadioactiveDecayPhysics()); //radioactive decay physics
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP()); //hadronic physics model
}

MyPhysicsList::~MyPhysicsList()
{} //destructor (no code required inside)