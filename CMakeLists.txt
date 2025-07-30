cmake_minimum_required(VERSION 3.16)
project(conway)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(conway ${SOURCES})

# Link SFML libraries
target_link_libraries(conway PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
