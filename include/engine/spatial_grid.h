#pragma once

#include "utils/vector2d.h"
#include <vector>

class Agent;

class SpatialGrid {
public:
    SpatialGrid(float cellSize, int worldWidth, int worldHeight);

    void clear();
    void insert(Agent* agent);

    // Return all agents within radius of position
    std::vector<Agent*> query(Vector2D position, float radius) const;

private:
    float _cellSize;
    int _cols;
    int _rows;
    std::vector<std::vector<Agent*>> _cells;

    int cellIndex(int col, int row) const;
    std::pair<int, int> cellCoords(Vector2D position) const;
};
