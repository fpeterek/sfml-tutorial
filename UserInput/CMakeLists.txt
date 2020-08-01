cmake_minimum_required(VERSION 3.17)
project(UserInput)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network)

add_executable(input src/main.cpp include/line.hpp src/line.cpp)

