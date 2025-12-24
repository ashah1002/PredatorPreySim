cmake_minimum_required(VERSION 3.15)
project(PredatorPreySim VERSION 1.0)

# Set C++20 for modern features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define where headers are
include_directories(include)

# Find all .cpp files in src/ and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})