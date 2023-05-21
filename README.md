# tree_evolution
## About
Simulation of a evolution of "digital trees".

The project was created for entertainment purposes. It does not aim to simulate or investigate the evolution taking place in the real world.

Video with an example of how the program works:
https://disk.yandex.ru/i/N-yeHMxZU6CW4g

## Build

### Dependencies

* CMake 3.12 or later
* C++ compiler with C++17 support
* OpenCV (for build with **SHOW** option)

### Build options

**SHOW** — demonstrates what is going on in a generated world (OpenCV requied).

**STATS** — save some statistics about the life of digital trees.

### Build example

```
git clone git@github.com:NifFerrolab/tree_evolution.git
mkdir tree_evolution/build
cd tree_evolution/build
cmake -DSHOW=On -DSTATS=Off ..
make -j 9
```

## Run

### Command line arguments

You can pass two parameters:
1. Initial value of the pseudo-random number generator. If no arguments are passed, the current Unix timestamp is taken.
2. Generation duration in steps. If second argument is not passed, 5x60x60x30 = 540'000 is taken.

### Run example

On Linux:

```
./tree_evolution 42 $((30*60*12))
```

Pseudorandom number generator initialized with 42. The simulation will last 30x60x12=21'600 steps (12 minutes at 30 frames per second).
