#include "engine/world.h"
#include "entities/agent.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

const int SEED = 42;

World::World(WorldConfig config) {
    _config = config;
    _predators = vector<Predator>();
    _prey = vector<Prey>();
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
        for(auto& predator : _predators) {
            predator.update(_config.tick);
            keepAgentInBounds(predator);
        }

        for(auto& prey : _prey) {
            prey.update(_config.tick);
            keepAgentInBounds(prey);
        }

        time += _config.tick;
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
    if(position.getX() < 0) {
        position.setX(0);
    } else if(position.getX() > _config.width) {
        position.setX(_config.width);
    }
    if(position.getY() < 0) {
        position.setY(0);
    } else if(position.getY() > _config.height) {
        position.setY(_config.height);
    }
    agent.setPosition(position);
}

void World::checkForCollisions() {
    vector<size_t> preyToRemove;

    for(auto& predator : _predators) {
        for(size_t i = 0; i < _prey.size(); i++) {
            if(predator.getPosition().distance(_prey[i].getPosition()) < predator.getRadius() + _prey[i].getRadius()) {
                preyToRemove.push_back(i);
                predator.eatPrey();
            }
        }
    }

    // Remove duplicates and sort in descending order
    sort(preyToRemove.begin(), preyToRemove.end(), greater<size_t>());
    preyToRemove.erase(unique(preyToRemove.begin(), preyToRemove.end()), preyToRemove.end());

    // Remove prey from back to front to preserve indices
    for(size_t idx : preyToRemove) {
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
        // Cap at 1.0 (100% chance)
        reproductionProbability = std::min(reproductionProbability, 1.0f);
        
        float chance = static_cast<float>(rand()) / RAND_MAX;
        if(chance < reproductionProbability) {
            newPredators.push_back(Predator(Vector2D(0, _config.width, 0, _config.height)));
        }
    }
    
    for(auto& prey : _prey) {
        float densityFactor = 1.0f - (float)_prey.size() / preyCarryingCapacity;
        densityFactor = std::max(0.0f, densityFactor);
        
        float adjustedRate = _config.preyReproductionRate * densityFactor;
        
        float chance = static_cast<float>(rand()) / RAND_MAX;
        if(chance < adjustedRate) {
            newPrey.push_back(Prey(Vector2D(0, _config.width, 0, _config.height)));
        }
    }
    
    _predators.insert(_predators.end(), newPredators.begin(), newPredators.end());
    _prey.insert(_prey.end(), newPrey.begin(), newPrey.end());
}