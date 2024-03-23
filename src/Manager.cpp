#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
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
        if (v->getCode().at(0) == 'R') {
            reservoirs.push_back(v);
        }

        if (v->getCode().at(0) == 'P') {
            stations.push_back(v);
        }

        if (v->getCode().at(0) == 'C') {
            cities.push_back(v);
        }
    }

    int number = 0;

    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setSelected(false);
        }
    }

    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (!e->isSelected()) {
                number++;
                e->setSelected(true);
            }
        }
    }

    for (auto v : graph.getVertexSet()) {
        std::cout << v->getCode() << "\n";
    }
    std::cout << "Number of reservoirs: " << reservoirs.size() << "\n";
    std::cout << "Number of stations: " << stations.size() << "\n";
    std::cout << "Number of cities: " << cities.size() << "\n";
    std::cout << "Number of pipes: " << number << "\n";
}

void Manager::maxWaterFlow(Graph &graph) {
    // Edmonds-Karp algorithm
    // Possible approach: create a super-source and a super-sink
    // connect the super-source to the reservoirs and the super-sink to the cities
    // run the algorithm and check the flow from the super-source to the super-sink
    // the flow from the super-source to the super-sink is the maximum flow
    // then select a city (using code) and check the flow from the super-source to the city

    Vertex* superSource = new Vertex("supersource", "supersource", 999, "SS", INT_MAX);
    Vertex* superSink = new Vertex("supersink", "supersink", 888, "TS", INT_MAX);

    graph.addVertex(superSource);
    graph.addVertex(superSink);

    for(auto v: graph.getVertexSet()){
        if (!v->getCode().empty()) {
            if (v->getCode().at(0) == 'R') {
                graph.addEdge(superSource->getCode(), v->getCode(), v->getMaxDelivery());
            }

            if (v->getCode().at(0) == 'C') {
                graph.addEdge(v->getCode(), superSink->getCode(), v->getDemand());
            }
        }
    }

    std::cout << "Edges connected to super-source: " << superSource->getAdj().size() << "\n";
    std::cout << "Edges connected to super-sink: " << superSink->getIncoming().size()<< "\n";

    edmondsKarp(graph, superSource, superSink);

    // Para fazer por cidade é pesquisar por código e ver o getFlow()
    double maxFlow = 0;
    for (auto e : superSink->getIncoming()) {
        maxFlow += e->getFlow();
    }

    std::cout << "The maximum amount of water that can reach all cities is " << maxFlow;

}


void Manager::edmondsKarp(Graph &graph, Vertex *source, Vertex *target) {
    Vertex* s = graph.findVertex(source->getCode());
    Vertex* t = graph.findVertex(target->getCode());

    if (s == nullptr || t == nullptr || s == t) {
        std::cout << "Invalid source or sink." << "\n";
        return;
    }

    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }


    while (findAugmentingPaths(graph, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}
bool Manager::findAugmentingPaths(Graph &graph, Vertex *s, Vertex *t){
    for(auto v : graph.getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex*> q;
    q.push(s);

    while(!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }

    return t->isVisited();
}

double Manager::findMinResidualAlongPath(Vertex* s, Vertex* t) {
    double f = INT_MAX;
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }

        if (v == s) {
            break;
        }
    }
    return f;
}

void Manager::testAndVisit(std::queue<Vertex*> &q, Edge* e, Vertex* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

void Manager::augmentFlowAlongPath(Vertex* s, Vertex* t, double f) {
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

