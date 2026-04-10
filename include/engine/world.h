#pragma once

#include "entities/predator.h"
#include "entities/prey.h"
#include "entities/agent.h"
#include "entities/vision.h"
#include "engine/spatial_grid.h"
#include <vector>
#include <fstream>
#include <memory>

struct WorldConfig {

    // World
    int width = 100;
    int height = 100;

    // Timing
    float duration = 50.0f;
    float tick = 0.1f;

    // Population
    int numGenerations = 100;
    int numPredators = 50;
    int numPrey = 200;

    // Evolution/Rules
    float predatorReproductionRate = 0.2f;
    float preyReproductionRate = 0.65f;

    int predatorHungerThreshold = 1;
    int preyCarryingCapacity = 1000;

    // Spatial grid cell size (should be >= vision range for efficiency)
    float gridCellSize = 10.0f;

    // Evolution: mutation parameters for inherited brains
    float mutationRate = 0.1f;      // per-weight mutation probability
    float mutationStrength = 0.2f;  // max magnitude of weight perturbation
};


class World {
public:
    World(WorldConfig config);

    void runSimulation();

private:
    WorldConfig _config;

    std::vector<Predator> _predators;
    std::vector<Prey> _prey;

    SpatialGrid _grid;
    Vision _vision;

    void rebuildGrid();
    void keepAgentInBounds(Agent& agent);
    void checkForCollisions();
    void reproduceAgents();
    void initializeSimulation();
    void printGenerationState(float time, std::ofstream& outfile);
    void printSimulationState(int generation, std::ofstream& outfile);
    void runGeneration(int generation, std::ofstream& outfile);
};
