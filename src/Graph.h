#ifndef WATERSYSTEM_GRAPH_H
#define WATERSYSTEM_GRAPH_H
// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Edge;


class Vertex {
public:
    Vertex(std::string reservoir, std::string municipality, int id, std::string code, double maxdelivery); // Reservoir vertex
    Vertex(std::string city, int id, std::string code, double demand, int population); // City vertex
    Vertex(int id, std::string code); // Station vertex

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    std::string getInfo() const;
    std::vector<Edge*> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge* getPath() const;
    std::vector<Edge*> getIncoming() const;

    void setInfo(std::string info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge* addEdge(Vertex *dest, double w);
    bool removeEdge(std::string in);
    void removeOutgoingEdges();

    double getMaxDelivery() const;
    std::string getReservoir() const;
    std::string getMunicipality() const;
    int getID() const;
    std::string getCode() const;
    double getDemand() const;
    int getPopulation() const;



protected:
    std::string info;                // info node
    std::vector<Edge*> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge*> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);

    double maxdelivery; // feito
    std::string reservoir;
    std::string municipality; 
    int id;
    std::string code;
    double demand;
    int population;
};


class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double capacity);

    Vertex* getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    Edge* getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex* dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const std::string &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Vertex* v);
    bool removeVertex(const std::string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &sourc, const std::string &dest, double w);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex*> getVertexSet() const;
protected:
    std::vector<Vertex*> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index o    friend class MutablePriorityQueue<Vertex>;f the vertex with a given content.
     */
    int findVertexIdx(const std::string &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //WATERSYSTEM_GRAPH_H