# Proton beam in to Lithium target Accelerator Experiment in GEANT4
This simulation models a fixed target experiment using a particle accelerator and neutron detector. This experiment is a new lab for the course ENGPHYS 4PP3: Applications of Plasma Physics offered at McMaster University. The purpose of this lab is to determine experimentally and through this simulation the Li7(p,n)Be7 cross section.

This simulation is written in C++ with the Monte Carlo particle trasport code GEANT4, developed at CERN.

The simulation uses a random number generator and experimentally-determined probabiliy distributions to compute the trajectories and interations of sub-atomic particles. Below is an example trajectory visual of the simulated particle accelerator. 

![image](https://github.com/Sebrhyscart/GEANT4-ProtonBeam-LithiumTarget/assets/133667593/d15c8abd-47a9-4f7d-8b3d-aa974da8433e)

In the visual, Light blue trajectories are Protons, Yellow trajectories are Neutrons, Green trajectories are Gamma rays, Red trajectories are electrons, and Grey trajectories are Neutrinos.
