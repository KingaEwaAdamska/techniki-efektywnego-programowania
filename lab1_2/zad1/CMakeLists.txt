cmake_minimum_required(VERSION 3.10)

project(Zad1 LANGUAGES CXX)

# C++98
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# does not let me to init and declare in diff functions
# add_compile_options(-Wall -Wextra -Werror)

include_directories(include)

add_executable(Zad1
    src/main.cpp
    src/table.cpp
)

