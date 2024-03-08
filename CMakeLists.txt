cmake_minimum_required(VERSION 3.27)
project(watersystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(watersystem
        src/Menu.cpp
        src/Menu.h
        main.cpp
        src/Graph.h
        src/Manager.h
        src/Reservoir.h
        src/City.h
        src/Station.h
        src/City.cpp
        src/Graph.cpp
        src/Manager.cpp
        src/Reservoir.cpp
        src/Station.cpp
        src/EdgeVertex.h
        src/EdgeVertex.cpp)
