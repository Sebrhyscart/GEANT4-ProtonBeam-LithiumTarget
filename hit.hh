#ifndef HIT_HH
#define HIT_HH
/*
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "tls.hh"

class MyHit : public G4VHit
{
    public:
        MyHit();
        //MyHit(const MyHit&) = default;
        ~MyHit(); //override;

        void Print(); //override;
        //void Draw() override;

        void SetEventNumber(G4int evt) { fEvt = evt; };
        void SetParticleName(G4String particleName) { fParticleName = particleName; };
        void SetPreStepEnergy(G4double energy1) { fEnergy1 = energy1; };
        void SetPostStepEnergy(G4double energy2) { fEnergy2 = energy2; };
        void SetPostProcessName(G4String postStepProcess) { fPostStepProcess = postStepProcess; };

        void GetEventNumber() { return fEvt; };
        void GetParticleName() { return fParticleName; };
        void GetPreStepEnergy() { return fEnergy1; };
        void GetPostStepEnergy() { return fEnergy2; };
        void GetPostProcessName() { return fPostStepProcess; };

    private:
        G4int evt;
        G4String particleName;
        G4double energy1;
        G4double energy2;
        G4String postProcessName;
};

typedef G4HitsCollection<MyHit> MyHitCollection;
*/
/*
inline void* MyHit::operator new(size_t)
{
    if(!MyHitAllocator)
        MyHitAllocator = new G4Allocator<MyHit>;
    return (void *) MyHitAllocator->MallocSingle();
}

inline void MyHit::operator delete(void *hit)
{
    MyHitAllocator->FreeSingle((MyHit*) hit);
}
*/

#endif