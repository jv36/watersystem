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
        src/Stations.h
        src/Sites.h)
