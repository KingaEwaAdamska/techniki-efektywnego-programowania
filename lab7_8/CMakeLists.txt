cmake_minimum_required(VERSION 3.10)

project(Zad4 LANGUAGES CXX)

# C++98
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

# does not let me to init and declare in diff functions
# add_compile_options(-Wall -Wextra -Werror)

include_directories(include)

add_executable(Lab7_8
    src/main.cpp
    src/Error.cpp
    src/Logger.cpp
    src/Result.cpp
    src/Node.cpp
    src/Tree.cpp
    src/CmdInterface.cpp
    src/StringHandler.cpp
)

