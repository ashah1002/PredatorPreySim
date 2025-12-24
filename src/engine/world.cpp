#include "engine/world.h"
#include "entities/agent.h"
#include <iostream>
using namespace std;

const int SEED = 42;

World::World(WorldConfig config) {
    _config = config;
    _agents = vector<unique_ptr<Agent>>();
}



void World::runSimulation() {
    for(int i = 0; i < _config.numGenerations; i++) {
        cout << "Running generation " << i << endl;
        runGeneration();  
        printSimulationState(i);
    }
}

void World::runGeneration() {

    float time = 0.0f; 

    srand(static_cast<unsigned>(SEED));
    for(int i = 0; i < _config.numPredators; i++) {
        _agents.push_back(make_unique<Predator>(
            Vector2D(
                static_cast<float>(rand()) / RAND_MAX * _config.width,
                static_cast<float>(rand()) / RAND_MAX * _config.height
            )
        ));
    }
    for(int i = 0; i < _config.numPrey; i++) {
        _agents.push_back(make_unique<Prey>(
            Vector2D(
                static_cast<float>(rand()) / RAND_MAX * _config.width,
                static_cast<float>(rand()) / RAND_MAX * _config.height
            )
        ));
    }

    for(int i = 0; i < _config.duration; i++) {

        for(auto& agent : _agents) {
            agent->update(_config.tick);
            keepAgentInBounds(*agent);
        }

        time += _config.tick;
        checkForCollisions();
        printGenerationState(time);
    }
}

void World::printGenerationState(float time) {
    cout << "Time: " << time << endl;
    cout << "Number of Predators Left: " << _agents.size() << endl;
    cout << "Number of Prey Left: " << _agents.size() << endl;

}

void World::printSimulationState(int generation) {
    cout << "End of Generation: " << generation << endl;
    cout << "Number of Predators Left: " << _agents.size() << endl;
    cout << "Number of Prey Left: " << _agents.size() << endl;
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

    vector<unique_ptr<Agent>> agentsToRemove;

    for(auto& agent : _agents) {
        if(agent->getType() == AgentType::PREY) {
            continue;
        }

        int eatCount = 0;
        for(auto& other : _agents) {
            if(other->getType() == AgentType::PREDATOR) {
                continue;
            }

            if(agent->getPosition().distance(other->getPosition()) < agent->getRadius() + other->getRadius()) {
                agentsToRemove.push_back(move(agent));
            }
        }

        if(eatCount >= _config.predatorKillRateNeededForSurvival) {
            agentsToRemove.push_back(move(agent));
        }
    }   

    for(auto& agent : agentsToRemove) {
        _agents.erase(find(_agents.begin(), _agents.end(), agent));
    }
}