//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_EDGEVERTEX_H
#define WATERSYSTEM_EDGEVERTEX_H
#include <string>


// Vertex class
class Vertex {
public:
    Vertex(const std::string &name, int id, const std::string &code, double maxDelivery,
           double demand, int population);

private:
    std::string name;
    int id;
    std::string code;
    double maxDelivery;
    double demand;
    int population;
};

// Edge class
class Edge {
public:

private:
};
#endif //WATERSYSTEM_EDGEVERTEX_H
