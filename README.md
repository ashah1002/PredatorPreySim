# Predator–Prey Simulator

## Overview
This project is a **C++ predator–prey simulation** where agents are controlled by **neural networks** trained through **evolutionary methods**. Predators and prey interact in a simulated environment, and behaviors emerge through selection and mutation over generations.

The project is inspired by the final project of a course I took at IMSA called Computational Science, where the entire class wrote deterministic or MLP-based policies for lynx and hare and competed in a “Hunger Games” style arena to see whose hare would survive the longest.

## How to Build & Run
```bash
cd build && cmake .. && cmake --build . && cd .. && ./build/PredatorPreySim
```
Output is saved to `logs/simulation_<timestamp>.csv`. Visualize with:
```bash
python3 scripts/visualize.py
```

## Architecture
- **Vision**: Each agent casts 8 rays (full 360° FOV, range 10 units). Each ray returns normalized distance and entity type (predator/prey/nothing).
- **Brain**: MLP (18 → 16 → 12 → 2) takes ray inputs + normalized velocity, outputs velocity delta with tanh squashing. Weights initialized with He init.
- **Spatial Grid**: Uniform 10×10 cell grid for O(1) neighbor lookups used by both raycasting and collision detection.
- **Evolution**: Agents with higher fitness (predators that eat more, prey that survive) reproduce at higher rates each generation.

## Status
Work in progress — evolution/weight inheritance not yet implemented (agents currently use random NN weights each generation).

## To-Do
- ~~Raycasting for agent "vision"~~
- ~~Spatial partitioning for collisions/rays~~
- ~~Neural Network for agent "brain"~~
- Evolutionary weight inheritance (crossover + mutation across generations)
- Visualization of agent trajectories and neural activations
