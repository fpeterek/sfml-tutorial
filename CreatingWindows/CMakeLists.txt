cmake_minimum_required(VERSION 3.16)
project(CreatingWindows)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(-lsfml-audio -lsfml-system -lsfml-graphics -lsfml-network -lsfml-window)

add_executable(window src/main.cpp)
