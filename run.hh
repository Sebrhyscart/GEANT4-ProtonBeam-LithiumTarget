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

        //void SetFastMode(G4bool clippedMode) {fastMode = fastMode};
        //G4bool GetFastMode() {return fastMode};

    private:
        //G4bool fastMode = false;
};


#endif