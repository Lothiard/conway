#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>

void print(std::vector<std::vector<bool>>& grid) {
    for(const auto& row : grid) {
        for(bool cell : row) {
            std::cout << (cell ? '#' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}

void init(std::vector<std::vector<bool>>& grid, int width, int height) {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            if(rand() % 4 == 0) {
                grid[i][j] = true;
            } else {
                grid[i][j] = false;
            }
        }
    }
}

int countNeighbours(std::vector<std::vector<bool>>& grid, int x, int y) {
    int width = grid.size();
    int height = grid[0].size();

    int count = 0;
    for(int i = -1; i < 2; ++i) {
        for(int j = -1; j < 2; ++j) {
            if(i == 0 && j == 0) { continue; }

            int nx = (x + i + width) % width;
            int ny = (y + j + height) % height;

            if(grid[nx][ny]) { ++count; }
        }
    }

    return count;
}

std::vector<std::vector<bool>> calculate(std::vector<std::vector<bool>>& current) {
    // < 2 neighbours = death
    // 2 || 3 neighbours = lives
    // > 3 neighbours = death

    int width = current.size();
    int height = current[0].size();

    std::vector<std::vector<bool>> next(height, std::vector<bool>(width));

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            if(current[i][j]) {
                if(countNeighbours(current, i, j) < 2 || countNeighbours(current, i, j) > 3) { next[i][j] = false; }
                else { next[i][j] = true; }
            } else {
                if(countNeighbours(current, i, j) == 3) { next[i][j] = true; }
            }
        }
    }

    return next;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <width> <height>\n";
        return 1;
    }
    std::srand(std::time(NULL));

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    std::vector<std::vector<bool>> grid(height, std::vector<bool>(width));

    init(grid, width, height);

    while(true) {
        grid = calculate(grid);
        print(grid);
        usleep(50000);
        std::cout << "\x1B[2J\x1B[H";
    }
}

