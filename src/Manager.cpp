#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <set>
#include <unordered_map>
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

    edmondsKarp(graph, superSource, superSink);
}


void Manager::maxWaterFlowTotal(Graph& graph) {
    maxWaterFlow(graph);
    double maxFlow = 0;
    Vertex* sink = graph.findVertex("TS");
    for (auto e : sink->getIncoming()) {
        maxFlow += e->getFlow();
    }
    std::cout << "The maximum amount of water that can reach all cities is " << maxFlow;
}
void Manager::maxWaterFlowCity(Graph &graph, const std::string &city) {
    maxWaterFlow(graph);
    Vertex* sink = graph.findVertex("TS");
    for (auto e : sink->getIncoming()) {
        if (e->getOrig()->getCode() == city) {
            std::cout << "The maximum amount of water that can reach " << e->getOrig()->getCity() << " is " << e->getFlow();
            break;
        }
    }
}

void Manager::maxWaterFlowAllCities(Graph &graph) {
    maxWaterFlow(graph);
    Vertex* sink = graph.findVertex("TS");
    for (auto e : sink->getIncoming()) {
        std::cout << e->getOrig()->getCity() << " with flow " << e->getFlow() << "\n";
    }
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

void Manager::flowDeficit(Graph &graph) {
    maxWaterFlow(graph);
    for (auto v : graph.getVertexSet()) {
        if (v->getCode().at(0) == 'C') {
            double totalFlow = 0;
            for (auto e : v->getIncoming()) {
                totalFlow += e->getFlow();
            }
            if (totalFlow < v->getDemand()) {
                std::cout << v->getCity() << " (" << v->getCode() << ")" << " has a flow deficit of " << v->getDemand() - totalFlow << "\n";
            }
        }
    }
}

void Manager::affectingReservoirs(Graph &graph, std::string code) {
    Vertex* reservoir = graph.findVertex(code);
    if (reservoir == nullptr) {
        std::cout << "Reservoir not found!\n";
        return;
    }

    for (auto e : reservoir->getAdj()) {
        graph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
    }

    for (auto e : reservoir->getIncoming()) {
        graph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
    }

    graph.removeVertex(reservoir->getCode());

    maxWaterFlow(graph);

    for (auto v : graph.getVertexSet()) {
        if (v->getCode().at(0) == 'C') {
            double totalFlow = 0;
            for (auto e : v->getIncoming()) {
                totalFlow += e->getFlow();
            }
            if (totalFlow < v->getDemand()) {
                std::cout << v->getCity() << " (" << v->getCode() << ")" << " has a flow deficit of " << v->getDemand() - totalFlow << "\n";
            }
        }
    }
}

void Manager::affectingStations(Graph graph, std::string code) {
    Vertex* station = graph.findVertex(code);
    if (station == nullptr) {
        std::cout << "Station not found!\n";
        return;
    }

        for (auto e : station->getAdj()) {
            graph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
        }

        for (auto e : station->getIncoming()) {
            graph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
        }

        graph.removeVertex(station->getCode());

        maxWaterFlow(graph);

        for (auto v : graph.getVertexSet()) {
            if (v->getCode().at(0) == 'C') {
                double totalFlow = 0;
                for (auto e : v->getIncoming()) {
                    totalFlow += e->getFlow();
                }
                if (totalFlow < v->getDemand()) {
                    std::cout << v->getCity() << " (" << v->getCode() << ")" << " has a flow deficit of " << v->getDemand() - totalFlow << "\n";
                }
            }
        }
}

void Manager::affectingPipes(Graph graph, std::string source, std::string dest) {
    graph.removeEdge(source, dest);
    maxWaterFlow(graph);

    for (auto v : graph.getVertexSet()) {
        if (v->getCode().at(0) == 'C') {
            double totalFlow = 0;
            for (auto e : v->getIncoming()) {
                totalFlow += e->getFlow();
            }
            if (totalFlow < v->getDemand()) {
                std::cout << v->getCity() << " (" << v->getCode() << ")" << " has a flow deficit of " << v->getDemand() - totalFlow << "\n";
            }
        }
    }

}

void Manager::unaffectingStations(Graph graph) {
    std::vector<std::pair<std::string, double>> stationFlows;
    std::vector<std::pair<std::string, double>> stationFlows2;
    std::vector<std::string> stations;
    maxWaterFlow(graph);
    int counter = 0;
    for (auto v : graph.getVertexSet()) {
        if (v->getCode().at(0) == 'C') {
            double totalFlow = 0;
            for (auto e : v->getIncoming()) {
                totalFlow += e->getFlow();
            }
            if (totalFlow < v->getDemand()) {
                stationFlows.push_back(std::make_pair(v->getCode(), v->getDemand() - totalFlow));
            }
        }
    }



    for (auto v : graph.getVertexSet()) {
        if (v->getCode().at(0) == 'P') {
            Graph newGraph = graphCopy(graph);
            for (auto e : v->getAdj()) {
                newGraph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
            }


            for (auto e : v->getIncoming()) {
                newGraph.removeEdge(e->getOrig()->getCode(), e->getDest()->getCode());
            }

            newGraph.removeVertex(v->getCode());
            maxWaterFlow(newGraph);
            for (auto v : newGraph.getVertexSet()) {
                if (v->getCode().at(0) == 'C') {
                    double totalFlow = 0;

                    for (auto e : v->getIncoming()) {
                        totalFlow += e->getFlow();
                    }

                    if (totalFlow < v->getDemand())
                    {
                        stationFlows2.push_back(std::make_pair(v->getCode(), v->getDemand() - totalFlow));
                    }


                    bool oi = vectorCompare(stationFlows, stationFlows2);
                    counter++;
                    std::cout << counter << std::endl;
                    if (oi) {
                        stations.push_back(v->getCode());
                        // stationFlows2.clear();
                    }
                }
            }


        }
    }


    for (auto s : stations) {
        std::cout << s << "\n";
    }
}

bool Manager::vectorCompare(const std::vector<std::pair<std::string, double>> &v1, const std::vector<std::pair<std::string, double>> &v2) {
    if (v1.size() != v2.size()) {
        return false;
    }


    // Sort the vectors
    std::vector<std::pair<std::string, double>> sorted_v1 = v1;
    std::vector<std::pair<std::string, double>> sorted_v2 = v2;
    std::sort(sorted_v1.begin(), sorted_v1.end(), [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
        return a.first < b.first;
    });
    std::sort(sorted_v2.begin(), sorted_v2.end(), [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
        return a.first < b.first;
    });

    for (auto s : sorted_v1) {
        std::cout << s.first << " " << s.second << std::endl;
    }

    std::cout << "----------------------" << std::endl;

    for (auto s : sorted_v2) {
        std::cout << s.first << " " << s.second << std::endl;
    }

    // Compare sorted vectors
    for (unsigned i = 0; i < sorted_v1.size(); i++) {

        if (sorted_v1[i].first != sorted_v2[i].first) {
            return false;
        }

        if (sorted_v1[i].second != sorted_v2[i].second) {
            return false;
        }
    }

    return true;
}



/*
 * Copia o grafo existente de modo a podermos fazer várias iterações
 * de algoritmos sem alterar o grafo original.
 */
Graph Manager::graphCopy(const Graph& graph) {
    Graph newGraph;
    std::unordered_map<Vertex*, Vertex*> vertexMap; // Map to store mapping between original and copied vertices

    // Copy vertices
    for (auto v : graph.getVertexSet()) {
        Vertex* newVertex = new Vertex(*v); // Create a new vertex with the same attributes as the original
        newGraph.addVertex(newVertex);
        vertexMap[v] = newVertex; // Store mapping between original and copied vertices
    }

    // Copy edges
    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            auto origVertex = vertexMap[e->getOrig()]; // Get the copied origin vertex
            auto destVertex = vertexMap[e->getDest()]; // Get the copied destination vertex
            double capacity = e->getCapacity();
            newGraph.addEdge(origVertex->getCode(), destVertex->getCode(), capacity);
        }
    }

    return newGraph;
}

