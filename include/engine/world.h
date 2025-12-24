#pragma once 

#include "entities/predator.h"
#include "entities/prey.h"
#include "entities/agent.h"
#include <vector>
#include <fstream>
#include <memory>

struct WorldConfig {

    // World
    int width = 50;
    int height = 50;

    // Timing
    float duration = 50.0f;
    float tick = 0.1f;

    // Population
    int numGenerations = 100;
    int numPredators = 75;
    int numPrey = 150;

    // Evolution/Rules
    float predatorReproductionRate = 0.25f;
    float preyReproductionRate = 0.55f;

    int predatorHungerThreshold = 1;
    int preyCarryingCapacity = 500;
};


class World {
public:
    World(WorldConfig config);
    //~World();

    void runSimulation();

private:
    WorldConfig _config;

    std::vector<Predator> _predators;
    std::vector<Prey> _prey;

    void keepAgentInBounds(Agent& agent);
    void checkForCollisions();
    void reproduceAgents();
    void initializeSimulation();
    void printGenerationState(float time, std::ofstream& outfile);
    void printSimulationState(int generation, std::ofstream& outfile);
    void runGeneration(int generation, std::ofstream& outfile);
};