#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <iostream>
#include <fstream>

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"

//create a Run Action class, inheriting from GEANT4's generic Run Action class
class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction(); //constructor
        ~MyRunAction(); //destructor

        virtual void BeginOfRunAction(const G4Run*); //function to perform any action before each run
        virtual void EndOfRunAction(const G4Run*); //function to perform any action after each run
};

#endif