# Simple Geant4 Simulation of Time-of-Flight PID

For the class **Experimental Methods of Particle Physics** (Fall 2024).

Written by: Johannes Wüthrich

To be used on the _essos_ cluster of the Rubbia-Group.


## Simulation Description
The simulated setup is heavily simplified.
It mainly consists of two silicon based _timing_ detectors which are separated by a distance of 2m.
Particles are shot along the axis which separates the two detectors.
The output files store the true particle ID number, the true primary particle momentum, the true time recorded by each timing detector and the time recorded by each detector with some smearing (timing uncertainty) applied.

The primary particle source generates a selection of different charged particles, with a flat momentum distribution.


## Compilation
To compile the simulation, run the following commands:

    source setup.sh
    cd build/

    cmake ..
    make

This should create the _ToFPID_ binary in the _build/_ directory.


## Running the Simulation
Ensure that Geant4 is setup and change into the build directory

    source setup.sh
    cd build/

### GUI Operation
When running from a terminal with X11 forwarding (GUI) activated, simply run

    ./ToFPID

This will open the visualizer GUI, from where individual events can be simulated.

### Batch Operation
When running from a non X11 terminal, or to run multiple events in batch mode, use

    ./ToFPID run.mac

This will simulated 100'000 particles and store the resulting data in a file called `MixedParticles_N100000.root`.
The primary particles are four different charged particles, which have a lifetime long enough so that detection in the timing detectors is possible.
The particle momentum is taken randomly with a flat distribution.


### Analysis
Some basic analysis of the simulated data is implemented in the `ToFPID.ipynb` python notebook.
Run this notebook by going to <https://essos2.ethz.ch/jupyter/>.

- Ensure that the **Neutrino Lecture 2024** kernel is used!



## Notes
In order to make the overall simulation code more understandable, it does not fully follow best practices.
Especially memory management is mostly ignored leading to some memory leaks.

**Please do not take this as a copy-paste base for any future simulation! Rather take this as an inspiration to learn yourself how to implement the basic Geant4 concepts.**
