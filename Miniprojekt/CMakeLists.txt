cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Zad4 LANGUAGES CXX)

# C++98
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(Miniprojekt
    src/main.cpp
    src/Optimizer.cpp
    src/Evaluator.cpp
    src/ProblemData.cpp
    src/Config.cpp
)
