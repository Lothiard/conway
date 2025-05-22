#include "grid.hpp"
#include <cstdlib>
#include <ctime>

Grid::Grid(int width, int height) :
    _width{width},
    _height{height},
    _current(height, std::vector<bool>(width, false)),
    _next(height, std::vector<bool>(width, false))
{
    std::srand(std::time(NULL));
}

bool Grid::get(int x, int y) const {
    return _current[x][y];
}

void Grid::set(int x, int y, bool alive) {
    _current[x][y] = alive;
}

void Grid::randomize(int prob) {
    for(int i = 0; i < _height; ++i) {
        for(int j = 0; j < _width; ++j) {
            _current[i][j] = (rand() % prob == 0) ? true : false;
        }
    }
}

int Grid::countNeighbours(int x, int y) const {
    int width = _current.size();
    int height = _current[0].size();

    int count = 0;
    for(int i = -1; i < 2; ++i) {
        for(int j = -1; j < 2; ++j) {
            if(i == 0 && j == 0) { continue; }

            int nx = (x + i + width) % width;
            int ny = (y + j + height) % height;

            if(_current[nx][ny]) { ++count; }
        }
    }

    return count;
}

void Grid::step() {
    int width = _current.size();
    int height = _current[0].size();

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            int neighbours = countNeighbours(i, j);
            if (_current[i][j]) {
                _next[i][j] = (neighbours == 2 || neighbours == 3);
            } else {
                _next[i][j] = (neighbours == 3);
            }
        }
    }

    _current.swap(_next);
}

