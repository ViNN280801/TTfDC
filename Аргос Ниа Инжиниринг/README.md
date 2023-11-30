# Gas Discharge Simulation

## Description

- Modeling includes tracking the trajectories of a large number of individual particles, their collisions with gas atoms, as well as tracking the intersections of particle trajectories with material surfaces.
- As a result of the intersection of particles with material surfaces, they stick to the walls and their tracking ends, and the coordinate of the intersection point is recorded. New particles are created randomly uniformly from some given surface.
- The program should simulate the transport of atoms in a rarefied gas by the Monte Carlo method.

The simulation involves modeling the movement of atoms in a rarefied gas using the Monte Carlo method. The primary functionalities include:

- Tracking particle trajectories.
- Simulating collisions with gas atoms.
- Monitoring intersections of particle trajectories with material surfaces.
- Stopping particle tracking upon intersection, recording the intersection coordinates, and creating new particles randomly on a specified surface.

### Prerequisites

- Minimum C++20 standard support.

## Example

```cpp
// Code snippet demonstrating particle creation and simulation
Particle particle = Particle::createRandomParticleOnSimpleSurface(surface, minCoordinates, maxCoordinates);
particle.intersectsSurface(surface);
particle.handleIntersection(surface, filename);
```

### Running the `main.cpp` tests

#### Compiling the project

```bash
make
```

```console
<loveit@fedora Аргос Ниа Инжиниринг>$ make
[ 16%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[ 33%] Building CXX object CMakeFiles/main.dir/src/coordinates.cpp.o
[ 50%] Building CXX object CMakeFiles/main.dir/src/particle.cpp.o
[ 66%] Linking CXX executable main
[100%] Built target main
```

#### Running tests

```bash
./main && cat log.txt
```

```console
x: 0
y: 0
z: 0
Weight: 1e-10 [kg]
Velocity: 10 [m/s]
Charge: 1.084202172485504434e-19 [C]

All tests passed successfully!
-0.9685023116219289 7.5949781947307855 8.563480506352715
```

## Memory leak check

Memory leak checks provides with the [Valgtind](https://valgrind.org/) utility.

```bash
valgrind --leak-check=full -s ./main
```

```console
==1648420== Memcheck, a memory error detector
==1648420== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==1648420== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==1648420== Command: ./main
==1648420==
x: 0
y: 0
z: 0
Weight: 1e-10 [kg]
Velocity: 10 [m/s]
Charge: 1.084202172485504434e-19 [C]

All tests passed successfully!
==1648420==
==1648420== HEAP SUMMARY:
==1648420==     in use at exit: 0 bytes in 0 blocks
==1648420==   total heap usage: 17 allocs, 17 frees, 102,078 bytes allocated
==1648420==
==1648420== All heap blocks were freed -- no leaks are possible
==1648420==
==1648420== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
