#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>

constexpr unsigned int CELL_SIZE = 10;
constexpr int FRAME_DELAY = 150;

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <width> <height>\n";
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    if(width <= 0 || height <= 0) {
        std::cerr << "bruh\n";
        return 1;
    }

    Grid grid(width, height);
    grid.randomize();

    sf::RenderWindow window(sf::VideoMode({CELL_SIZE * width, CELL_SIZE * height}), "conway", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RectangleShape cellShape({CELL_SIZE - .1f, CELL_SIZE - .1f});
    cellShape.setFillColor(sf::Color::Green);

    bool paused = false;

    while(window.isOpen()) {
        for (sf::Event e; window.pollEvent(e);) {
            if(e.type == sf::Event::Closed) { window.close(); }
            if(e.type == sf::Event::KeyPressed) {
                if(e.key.code == sf::Keyboard::Space) { paused = !paused; }
                if(e.key.code == sf::Keyboard::R) { grid.randomize(); }
            }
        }

        if(!paused) { grid.step(); }

        window.clear(sf::Color::Black);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (grid.get(j, i)) {
                    cellShape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    window.draw(cellShape);
                }
            }
        }
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }
    return 0;
}

