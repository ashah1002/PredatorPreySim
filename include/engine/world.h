#pragma once 

#include "entities/predator.h"
#include "entities/prey.h"
#include "entities/agent.h"
#include <vector>
#include <memory>

struct WorldConfig {

    // World
    float width = 10.0f;
    float height = 10.0f;

    // Timing
    float duration = 100.0f;
    float tick = 0.016f;

    // Population
    int numGenerations = 10;
    int numPredators = 5;
    int numPrey = 20;

    // Evolution/Rules
    float reproductionRate = 0.1f;
    float mutationRate = 0.05f;
    float predatorKillRateNeededForSurvival = 2.0f;
};


class World {
public:
    World(WorldConfig config);
    //~World();

    void runSimulation();

private:
    WorldConfig _config;
    std::vector<std::unique_ptr<Agent>> _agents;

    void keepAgentInBounds(Agent& agent);
    void checkForCollisions();
    void printGenerationState(float time);
    void printSimulationState(int generation);
    void runGeneration();
};