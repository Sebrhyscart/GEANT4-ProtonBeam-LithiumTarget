#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <iostream>
#include <fstream>

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction();
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);

};

#endif