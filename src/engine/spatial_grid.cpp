#include "engine/spatial_grid.h"
#include "entities/agent.h"
#include <algorithm>
#include <cmath>

SpatialGrid::SpatialGrid(float cellSize, int worldWidth, int worldHeight)
    : _cellSize(cellSize)
{
    _cols = static_cast<int>(std::ceil(static_cast<float>(worldWidth) / _cellSize));
    _rows = static_cast<int>(std::ceil(static_cast<float>(worldHeight) / _cellSize));
    _cells.resize(_cols * _rows);
}

void SpatialGrid::clear() {
    for (auto& cell : _cells) {
        cell.clear();
    }
}

int SpatialGrid::cellIndex(int col, int row) const {
    return row * _cols + col;
}

std::pair<int, int> SpatialGrid::cellCoords(Vector2D position) const {
    int col = std::clamp(static_cast<int>(position.getX() / _cellSize), 0, _cols - 1);
    int row = std::clamp(static_cast<int>(position.getY() / _cellSize), 0, _rows - 1);
    return {col, row};
}

void SpatialGrid::insert(Agent* agent) {
    auto [col, row] = cellCoords(agent->getPosition());
    _cells[cellIndex(col, row)].push_back(agent);
}

std::vector<Agent*> SpatialGrid::query(Vector2D position, float radius) const {
    std::vector<Agent*> result;

    // Determine the range of cells to check
    int minCol = std::clamp(static_cast<int>((position.getX() - radius) / _cellSize), 0, _cols - 1);
    int maxCol = std::clamp(static_cast<int>((position.getX() + radius) / _cellSize), 0, _cols - 1);
    int minRow = std::clamp(static_cast<int>((position.getY() - radius) / _cellSize), 0, _rows - 1);
    int maxRow = std::clamp(static_cast<int>((position.getY() + radius) / _cellSize), 0, _rows - 1);

    float radiusSq = radius * radius;

    for (int row = minRow; row <= maxRow; row++) {
        for (int col = minCol; col <= maxCol; col++) {
            for (Agent* agent : _cells[cellIndex(col, row)]) {
                float dx = agent->getPosition().getX() - position.getX();
                float dy = agent->getPosition().getY() - position.getY();
                if (dx * dx + dy * dy <= radiusSq) {
                    result.push_back(agent);
                }
            }
        }
    }

    return result;
}
