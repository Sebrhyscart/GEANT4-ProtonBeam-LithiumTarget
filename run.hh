#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"

class MyRun : public G4Run
{
    public:
        MyRun();
        ~MyRun();

        virtual void RecordEvent(const G4Event*);
        void Merge(const G4Run*);
        /*
        inline G4int GetEventNumber() const
        { return fevt; }

        inline G4String GetParticleName() const
        { return fParticleName; }

        inline G4double GetPreStepEnergy() const
        { return fEnergy1; }

        inline G4double GetPostStepEnergy() const
        { return fEnergy2; }

        inline G4String GetPostProcessName() const
        { return fPostProcessName}

    private:
        G4int fevt;
        G4String fParticleName;
        G4double fEnergy1;
        G4double fEnergy2;
        G4Sting fPostProcessName;
        */
};


#endif