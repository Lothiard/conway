#pragma once
#include <vector>

class Grid {
public:
    Grid(int width, int height);

    bool get(int x, int y) const;
    void set(int x, int y, bool alive);
    void randomize(int prob = 4);
    void step();
    int width() const { return _width; }
    int height() const { return _height; }

private:
    int countNeighbours(int x, int y) const;
    int _width, _height;
    std::vector<std::vector<bool>> _current;
    std::vector<std::vector<bool>> _next;
};

