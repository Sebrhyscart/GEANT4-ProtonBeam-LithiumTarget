#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "runaction.hh"

//create an Action Initilization class, inheriting from GEANT4's generic Action Initilization class
class MyActionInitialization : public G4VUserActionInitialization
{
    public:
        MyActionInitialization(); //constructor
        ~MyActionInitialization(); //destructor

        virtual void Build() const; //function to initilize actions for each worker thread
        virtual void BuildForMaster() const; //function to initilize actions for the master thread
};

#endif