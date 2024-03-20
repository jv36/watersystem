//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_MANAGER_H
#define WATERSYSTEM_MANAGER_H


#include <string>
#include "Graph.h"

class Manager {
public:
    void createReservoirs(const std::string &filename, Graph& graph);
    void createPipes(const std::string &filename, Graph& graph);
    void createCities(const std::string &filename, Graph& graph);
    void createStations(const std::string &filename, Graph& graph);

    void counter(Graph& graph);

    void maxWaterFlow(Graph& graph, std::string city);

private:
    Graph graph;
    std::vector<Vertex*> reservoirs;
    std::vector<Vertex*> cities;
    std::vector<Vertex*> stations;
    std::vector<Edge*> pipes;
};


#endif //WATERSYSTEM_MANAGER_H
