cmake_minimum_required(VERSION 3.15)
project(conway_sfml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(game
    src/main.cpp
    src/grid.cpp
)

target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
