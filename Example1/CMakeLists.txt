cmake_minimum_required(VERSION 3.16)
project(Ukazka1)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/ /usr/include/)
link_directories(/usr/lib/)
link_libraries(-lsfml-window -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio)

add_executable(example src/main.cpp include/custom_rect.hpp src/custom_rect.cpp)
