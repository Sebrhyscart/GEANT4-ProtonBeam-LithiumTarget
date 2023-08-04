#ifndef PROTONLI_HH
#define PROTONLI_HH

#include <iostream>

#include "G4RunManager.hh" //import header files needed to run GEANT4
#include "G4MTRunManager.hh" 
#include "G4UImanager.hh" //#include "G4UIManager.hh" 
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Threading.hh" 

#include "construction.hh" //import the header files written for this application
#include "physics.hh"
#include "action.hh"

//simulation parameters
extern G4bool runWithVis = true; //run with the visualization window initilized
extern G4int NumThreads = 12; //the number of threads the program should use
//extern G4int NumThreads = G4Threading::G4GetNumberOfCores(); //this sets the optimum number of threads based on the number of cores in the computer

#endif