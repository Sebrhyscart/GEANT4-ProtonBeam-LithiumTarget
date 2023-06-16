#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    //=================================================================================================================================
    //Register Standard Physics to use

    RegisterPhysics (new G4EmStandardPhysics()); //electromagnetic standard physics
    //RegisterPhysics (new G4OpticalPhysics()); //remove optical physics
    RegisterPhysics (new G4DecayPhysics()); //decay physics
    RegisterPhysics (new G4RadioactiveDecayPhysics()); //radioactive decay physics
    RegisterPhysics (new G4HadronPhysicsQGSP_BIC_AllHP()); //hadronic physics default model
    //QGSP - Quark Gluon String model for high energy particle collisions (shouldn't be needed but added for completeness)
    //BIC - Binary Cascade model for medium-low energy collisions (potentially needed)
    //HP - high precision low energy cross section based model (crucial)

    //=================================================================================================================================
    //Set HP cross sections
    //idk if this section is needed
    //




    /*
    //MODIFY THIS (Neutron elast and inelast) (Proton elast and inelast)
    G4HadronElasticProcess* theNeutronElasticProcess = new G4HadronElasticProcess;
    // Cross Section Data set
    G4NeutronHPElasticData* theHPElasticData = new G4NeutronHPElasticData; //This object has the xs
    theNeutronElasticProcess->AddDataSet(theHPElasticData); //add the object to the dataset //ELASTIC
    G4NeutronHPThermalScatteringData* theHPThermalScatteringData = new G4NeutronHPThermalScatteringData;
    theNeutronElasticProcess->AddDataSet(theHPThermalScatteringData); //THERMAL ELASTIC
    // Models -> set where this model (use these xs) is valid (Emin -> Emax)
    G4NeutronHPElastic* theNeutronElasticModel = new G4NeutronHPElastic;
    theNeutronElasticModel->SetMinEnergy(4.0*eV);
    theNeutronElasticProcess->RegisterMe(theNeutronElasticModel);
    G4NeutronHPThermalScattering* theNeutronThermalElasticModel = new G4NeutronHPThermalScattering;
    theNeutronThermalElasticModel->SetMaxEnergy(4.0*eV);
    theNeutronElasticProcess->RegisterMe(theNeutronThermalElasticModel);
    // Apply Processes to Process Manager of Neutron
    G4ProcessManager* pmanager = G4Neutron::Neutron()->GetProcessManager();
    pmanager->AddDiscreteProcess(theNeutronElasticProcess);
    */


    /*
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //get the GEANT4 table of default particles
    G4String particleName = "proton"; //the name of the particle needed
    const G4ParticleDefinition *particle = particleTable->FindParticle(particleName); //get the particle from the particle table
    const G4ParticleDefinition& theProton = *particle;
    G4CrossSectionDataStore::DumpPhysicsTable(theProton); //idk man
    */
}

MyPhysicsList::~MyPhysicsList()
{}
