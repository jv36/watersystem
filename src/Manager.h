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

    void maxWaterFlow(Graph& graph);

    void maxWaterFlowTotal(Graph &graph);
    void maxWaterFlowCity(Graph& graph, const std::string &city);
    void maxWaterFlowAllCities(Graph& graph);

    void flowDeficit(Graph& graph);

    void edmondsKarp(Graph& graph, Vertex* source, Vertex* target);
    bool findAugmentingPaths(Graph &graph,Vertex *s, Vertex *t);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    void testAndVisit(std::queue<Vertex*> &q, Edge *e, Vertex *w, double residual);

private:
    Graph graph;
    std::vector<Vertex*> reservoirs;
    std::vector<Vertex*> cities;
    std::vector<Vertex*> stations;
    std::vector<Edge*> pipes;


};


#endif //WATERSYSTEM_MANAGER_H
