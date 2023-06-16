#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <iostream>
#include <fstream>

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include "G4ParticleTable.hh"
#include "G4VCrossSectionDataSet.hh" //i dont think this works (abstract class -> cant use it here)
#include "G4CrossSectionDataStore.hh"

class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction();
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);

};

#endif