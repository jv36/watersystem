//
// Created by joaomendes on 08-03-2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Manager.h"
#include "Graph.h"

void Manager::createReservoirs(const std::string &filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name, municipality, id, code, maxDelivery;

        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDelivery, ',');

        int idConv = std::stoi(id);
        double maxConv = std::stod(maxDelivery);

        Vertex* vert = new Vertex(name, municipality, idConv, code, maxConv);
        vert->setInfo(code);
        graph.addVertex(vert);
    }


}

void Manager::createCities(const std::string &filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string city, id, code, demand, population;

        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, ',');



        int idConv = std::stoi(id);
        double demandConv = std::stod(demand);
        int popConv = std::stoi(population);

        Vertex* vert = new Vertex(city, idConv, code, demandConv, popConv);
        vert->setInfo(code);
        graph.addVertex(vert);
    }
}

void Manager::createStations(const std::string &filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, code;

        getline(iss, id, ',');
        getline(iss, code, ',');

        int idConv = std::stoi(id);

        Vertex* vert = new Vertex(idConv, code);
        vert->setInfo(code);
        graph.addVertex(vert);
    }
}

void Manager::createPipes(const std::string &filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string origin, destination, capacity, direction;

        getline(iss, origin, ',');
        getline(iss, destination, ',');
        getline(iss, capacity, ',');
        getline(iss, direction, ',');

        int intDirection = std::stoi(direction);
        double doubleCap = std::stod(capacity);

        if (intDirection == 1) {
            graph.addEdge(origin, destination, doubleCap);
        }
        if (intDirection == 0) {
            graph.addBidirectionalEdge(origin, destination, doubleCap);
        }
    }
}

void Manager::counter(Graph& graph) {


    std::cout << "Vertex set size: " << graph.getVertexSet().size() << "\n";


    for (auto v : graph.getVertexSet()) {
        if (v->getInfo().at(0) == 'R') {
            reservoirs.push_back(v);
        }

        if (v->getInfo().at(0) == 'P') {
            stations.push_back(v);
        }

        if (v->getInfo().at(0) == 'C') {
            cities.push_back(v);
        }
    }

    int number = 0;
    for (auto v : graph.getVertexSet()) {
        number += v->getAdj().size();
    }

    std::cout << "Number of reservoirs: " << reservoirs.size() << "\n";
    std::cout << "Number of stations: " << stations.size() << "\n";
    std::cout << "Number of cities: " << cities.size() << "\n";
    std::cout << "Number of pipes: " << number << "\n";
}

void Manager::maxWaterFlow(Graph &graph, std::string city) {
    // Edmonds-Karp algorithm
    // Possible approach: create a super-source and a super-sink
    // connect the super-source to the reservoirs and the super-sink to the cities
    // run the algorithm and check the flow from the super-source to the super-sink
    // the flow from the super-source to the super-sink is the maximum flow
    // then select a city (using code) and check the flow from the super-source to the city

}



