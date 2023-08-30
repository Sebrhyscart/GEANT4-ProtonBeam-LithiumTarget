# Proton Beam - Lithium Target Fixed Target Experiment with GEANT4
### Overview
This simulation models a fixed target experiment using a particle accelerator and a neutron detector. The simulation fires a beam of monoenergetic protons at a desired energy into a Lithium target and models all secondary particles produced by nuclear reactions occuring within the target. The primary reaction of interest is Li7(p,n)Be7, by which neutrons are produced in the target by incident protons. The simulation records and reports the number of neutrons present in both the target and detector over the course of the simulation.

The simulation is written in C++ with the Monte Carlo particle transport code GEANT4. The simulation uses a random number generator and experimentally-determined probability distributions to compute the trajectories and interations of sub-atomic particles.

### Geometry
The simulation geometry is shown below. Protons are fired from a source position along a vacuum beamline until they hit the target. Behind the target are multiple graphite/lead/plastic radiation sheilding and neutron moderation plugs. Surrounding the target is a graphite-resin sheilding box. Behind the box there is a small air region where the neutron detector is located. The detector is placed directly behind the target.

![sim](https://github.com/Sebrhyscart/GEANT4-ProtonBeam-LithiumTarget/assets/133667593/a24c2baa-e077-45ed-b0db-b17482cc4190)

### Running the Simumlation
Below is an example trajectory visual of the simulated fixed target experiment. In the visual, Light blue trajectories are Protons, Yellow trajectories are Neutrons, Green trajectories are Gamma rays, Red trajectories are electrons, and Grey trajectories are Neutrinos.

![image](https://github.com/Sebrhyscart/GEANT4-ProtonBeam-LithiumTarget/assets/133667593/d15c8abd-47a9-4f7d-8b3d-aa974da8433e)

