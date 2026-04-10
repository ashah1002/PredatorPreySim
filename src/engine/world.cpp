#include "engine/world.h"
#include "entities/agent.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int SEED = 42;

World::World(WorldConfig config)
    : _config(config),
      _grid(config.gridCellSize, config.width, config.height),
      _vision(VisionConfig{NUM_RAYS, VISION_RANGE})
{
}

void World::initializeSimulation() {
    srand(static_cast<unsigned>(SEED));
    for(int i = 0; i < _config.numPredators; i++) {
        _predators.push_back(Predator(Vector2D(0, _config.width, 0, _config.height)));
    }
    for(int i = 0; i < _config.numPrey; i++) {
        _prey.push_back(Prey(Vector2D(0, _config.width, 0, _config.height)));
    }
}

void World::rebuildGrid() {
    _grid.clear();
    for (auto& predator : _predators) {
        _grid.insert(&predator);
    }
    for (auto& prey : _prey) {
        _grid.insert(&prey);
    }
}

void World::runSimulation() {
    string filename = "logs/simulation_" + to_string(time(NULL)) + ".csv";
    std::ofstream outfile(filename);

    // CSV header
    outfile << "generation,time,predators,prey" << endl;

    initializeSimulation();

    for(int gen = 1; gen <= _config.numGenerations; gen++) {
        runGeneration(gen, outfile);
    }

    outfile.close();
    cout << "Simulation complete. Results saved to " << filename << endl;
}

void World::runGeneration(int generation, std::ofstream& outfile) {
    float time = 0.0f;

    outfile << generation << "," << time << ","
            << _predators.size() << "," << _prey.size() << endl;

    for(int i = 0; i < _config.duration; i++) {
        // Rebuild spatial grid with current positions
        rebuildGrid();

        // Compute vision and update each predator
        for(auto& predator : _predators) {
            vector<float> vision = _vision.sense(predator, _grid);
            predator.update(_config.tick, vision);
            keepAgentInBounds(predator);
        }

        // Compute vision and update each prey
        for(auto& prey : _prey) {
            vector<float> vision = _vision.sense(prey, _grid);
            prey.update(_config.tick, vision);
            keepAgentInBounds(prey);
        }

        time += _config.tick;

        // Use spatial grid for collision detection
        checkForCollisions();

        outfile << generation << "," << time << ","
                << _predators.size() << "," << _prey.size() << endl;
    }

    vector<size_t> predatorsToRemove;
    for(size_t i = 0; i < _predators.size(); i++) {
        if(_predators[i].getPreyEaten() < _config.predatorHungerThreshold) {
            predatorsToRemove.push_back(i);
        }
    }

    sort(predatorsToRemove.begin(), predatorsToRemove.end(), greater<size_t>());
    predatorsToRemove.erase(unique(predatorsToRemove.begin(), predatorsToRemove.end()),
                            predatorsToRemove.end());

    for(size_t idx : predatorsToRemove) {
        _predators.erase(_predators.begin() + idx);
    }

    reproduceAgents();

    for(auto& predator : _predators) {
        predator.resetPreyEaten();
    }
}

void World::printGenerationState(float time, std::ofstream& outfile) {
    outfile << "Time: " << time << endl;
    outfile << "Number of Predators Left: " << _predators.size() << endl;
    outfile << "Number of Prey Left: " << _prey.size() << endl;
}

void World::printSimulationState(int generation, std::ofstream& outfile) {
    outfile << "End of Generation: " << generation << endl;
    outfile << "Number of Predators Left: " << _predators.size() << endl;
    outfile << "Number of Prey Left: " << _prey.size() << endl;
}

void World::keepAgentInBounds(Agent& agent) {
    Vector2D position = agent.getPosition();
    if(position.getX() - agent.getRadius() < 0) {
        position.setX(0 + agent.getRadius());
    } else if(position.getX() + agent.getRadius() > _config.width) {
        position.setX(_config.width - agent.getRadius());
    }
    if(position.getY() - agent.getRadius() < 0) {
        position.setY(0 + agent.getRadius());
    } else if(position.getY() + agent.getRadius() > _config.height) {
        position.setY(_config.height - agent.getRadius());
    }
    agent.setPosition(position);
}

void World::checkForCollisions() {
    // Track which prey have already been claimed so no double-eating
    std::set<size_t> eatenPreyIndices;

    for(auto& predator : _predators) {
        float searchRadius = predator.getRadius() + 2.0f;
        vector<Agent*> nearby = _grid.query(predator.getPosition(), searchRadius);

        for (Agent* other : nearby) {
            if (other->getType() != AgentType::PREY) continue;

            float dist = predator.getPosition().distance(other->getPosition());
            if (dist < predator.getRadius() + other->getRadius()) {
                // Find which prey index this is
                for (size_t j = 0; j < _prey.size(); j++) {
                    if (&_prey[j] == other && eatenPreyIndices.find(j) == eatenPreyIndices.end()) {
                        eatenPreyIndices.insert(j);
                        predator.eatPrey();
                        break;
                    }
                }
            }
        }
    }

    // Remove eaten prey in reverse index order
    vector<size_t> toRemove(eatenPreyIndices.begin(), eatenPreyIndices.end());
    sort(toRemove.begin(), toRemove.end(), greater<size_t>());

    for(size_t idx : toRemove) {
        _prey.erase(_prey.begin() + idx);
    }
}

void World::reproduceAgents() {
    // Store new agents separately to avoid iterator invalidation
    vector<Predator> newPredators;
    vector<Prey> newPrey;

    for(auto& predator : _predators) {
        // Probability increases with prey eaten
        float baseProbability = _config.predatorReproductionRate;
        int excessPrey = predator.getPreyEaten() - _config.predatorHungerThreshold;

        // Scale probability by excess prey (more prey = higher chance)
        float reproductionProbability = baseProbability * (1.0f + excessPrey);
        reproductionProbability = std::min(reproductionProbability, 1.0f);

        float chance = static_cast<float>(rand()) / RAND_MAX;
        if(chance < reproductionProbability) {
            // Offspring inherits parent's brain weights, then mutates
            Predator child(Vector2D(0, _config.width, 0, _config.height));
            child.getBrain().loadParameters(predator.getBrain().getParameters());
            child.getBrain().mutate(_config.mutationRate, _config.mutationStrength);
            newPredators.push_back(std::move(child));
        }
    }

    for(auto& prey : _prey) {
        float densityFactor = 1.0f - (float)_prey.size() / _config.preyCarryingCapacity;
        densityFactor = std::max(0.0f, densityFactor);

        float adjustedRate = _config.preyReproductionRate * densityFactor;

        float chance = static_cast<float>(rand()) / RAND_MAX;
        if(chance < adjustedRate) {
            // Offspring inherits parent's brain weights, then mutates
            Prey child(Vector2D(0, _config.width, 0, _config.height));
            child.getBrain().loadParameters(prey.getBrain().getParameters());
            child.getBrain().mutate(_config.mutationRate, _config.mutationStrength);
            newPrey.push_back(std::move(child));
        }
    }

    // Move new agents into population
    for (auto& p : newPredators) {
        _predators.push_back(std::move(p));
    }
    for (auto& p : newPrey) {
        _prey.push_back(std::move(p));
    }
}
