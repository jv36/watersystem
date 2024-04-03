#include "Graph.h"

/**
 *
 * @brief Função auxiliar para remover uma aresta de saída (com um destino (d) dado) de um vértice (this).
 * @details Complexidade: O(|adj|)
 * @param in: código do vértice de destino
 * @return Retoma true se tiver sucesso e falso se o edge não existir.
 */
bool Vertex::removeEdge(std::string in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getCode() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/**
 * @brief Remove todos os outgoing edges de um vértice.t
 * @details Complexidade: O(|adj|)
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

/**
 * @brief Operador para comparar dois vértices, através do dist.
 * @param vertex: vértice
 * @return Retorna true se o dist do vértice atual for menor que o dist do vértice dado.
 */
bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

/**
 * @brief Obtém a lista de arestas adjacentes a um vértice.
 * @details Complexidade: O(1)
 * @return Retorna a lista de arestas adjacentes, sob a forma de um vetor.
 */
std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

/**
 * @brief Verifica se um vértice foi visitado.
 * @details Complexidade: O(1)
 * @return Retoma true se o vértice foi visitado, falso caso contrário.
 */
bool Vertex::isVisited() const {
    return this->visited;
}

/**
 * @brief Obtém a aresta que liga um vértice ao seu path.
 * @details Complexidade: O(1)
 * @return Retorna a aresta que liga o vértice ao seu path.
 */
Edge *Vertex::getPath() const {
    return this->path;
}

/**
 * @brief Obtém a lista de arestas que entram num vértice.
 * @details Complexidade: O(1)
 * @return Retorna a lista de arestas que entram no vértice, sob a forma de um vetor.
 */
std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

/**
 * @brief Define se um vértice foi visitado.
 * @details Complexidade: O(1)
 * @param visited: valor booleano que indica se o vértice foi visitado.
 */
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Define a aresta que liga um vértice ao seu path.
 * @details Complexidade: O(1)
 * @param path: aresta(edge)
 */
void Vertex::setPath(Edge *path) {
    this->path = path;
}


/**
 * @brief Remove uma aresta de um vértice.
 * @details Complexidade: O(|incoming|)
 * @param edge: aresta a remover
 */
void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getCode() == code) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/**
 * @brief Adiciona uma aresta a um vértice.
 * @details Complexidade: O(1)
 * @param dest: vértice de destino
 * @param w: peso da aresta
 * @return nova aresta
 */
Edge *Vertex::addEdge(Vertex *dest, double w) {
    auto newEdge = new Edge(this, dest, w);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

/**
 * @brief Construtor da classe Vertex. Utilizado para vértices do tipo reservatório.
 * @param reservoir: reservatório
 * @param municipality: município
 * @param id: id
 * @param code: código
 * @param maxdelivery: entrega máxima
 */
Vertex::Vertex(std::string reservoir, std::string municipality, int id, std::string code, double maxdelivery) {
    this->reservoir = reservoir;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxdelivery;
}

/**
 * @brief Construtor da classe Vertex. Utilizado para vértices do tipo estação.
 * @param id: id
 * @param code: código
 */
Vertex::Vertex(int id, std::string code) {
    this->id = id;
    this->code = code;
}

/**
 * @brief Construtor da classe Vertex. Utilizado para vértices do tipo cidade.
 * @param city: cidade
 * @param id: id
 * @param code: código
 * @param demand: procura
 * @param population: população
 */
Vertex::Vertex(std::string city, int id, std::string code, double demand, int population) {
    this->city = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

/**
 * @brief Obtém a entrega máxima de um vértice.
 * @details Complexidade: O(1)
 * @return Retorna a entrega máxima de um vértice.
 */
double Vertex::getMaxDelivery() const {
    return this->maxDelivery;
}

/**
 * @brief Obtém o código de um vértice.
 * @details Complexidade: O(1)
 * @return Retorna o código de um vértice.
 */
std::string Vertex::getCode() const{
    return this->code;
}

/**
 * @brief Obtém a procura de um vértice.
 * @details Complexidade: O(1)
 * @return Retorna a procura de um vértice.
 */
double Vertex::getDemand() const{
    return  this->demand;
}

/**
 * @brief Obtém a cidade de um vértice.
 * @details Complexidade: O(1)
 * @return Retorna a cidade de um vértice.
 */
std::string Vertex::getCity() const {
    return this->city;
}

/********************** Edge  ****************************/

/**
 * @brief Construtor da classe Edge.
 * @param orig: vértice de origem
 * @param dest: vértice de destino
 * @param capacity: capacidade
 */
Edge::Edge(Vertex *orig, Vertex *dest, double capacity) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = capacity;

}

/**
 * @brief Obtém o vértice de destino de uma aresta.
 * @details Complexidade: O(1)
 * @return Retorna o vértice de destino de uma aresta.
 */
Vertex * Edge::getDest() const {
    return this->dest;
}

/**
 * @brief Obtém a capacidade de uma aresta.
 * @details Complexidade: O(1)
 * @return Retorna a capacidade de uma aresta.
 */
double Edge::getCapacity() const {
    return this->capacity;
}

/**
 * @brief Verifica se uma aresta foi selecionada.
 * @details Complexidade: O(1)
 * @return Retorna true se a aresta foi selecionada, falso caso contrário.
 */
Vertex * Edge::getOrig() const {
    return this->orig;
}

/**
 * @brief Obtém o fluxo de uma aresta.
 * @details Complexidade: O(1)
 * @return Retorna o fluxo de uma aresta.
 */
bool Edge::isSelected() const {
    return this->selected;
}

/**
 * @brief Obtém a aresta reversa de uma aresta.
 * @details Complexidade: O(1)
 * @return Retorna a aresta reversa de uma aresta.
 */
double Edge::getFlow() const {
    return flow;
}

/**
 * @brief Define se uma aresta foi selecionada.
 * @details Complexidade: O(1)
 * @param selected: valor booleano que indica se a aresta foi selecionada.
 */
void Edge::setSelected(bool selected) {
    this->selected = selected;
}

/**
 * @brief Define a aresta reversa de uma aresta.
 * @details Complexidade: O(1)
 * @param reverse: aresta reversa
 */
void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

/**
 * @brief Define o fluxo de uma aresta.
 * @details Complexidade: O(1)
 * @param flow: fluxo
 */
void Edge::setFlow(double flow) {
    this->flow = flow;
}



/********************** Graph  ****************************/

/**
 * @brief Obtém o conjunto de vértices de um grafo.
 * @details Complexidade: O(1)
 * @return Retorna o conjunto de vértices de um grafo.
 */
std::vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Função auxiliar para encontrar um vértice com um dado conteúdo.
 * @details Complexidade: O(|vertexSet|)
 * @param in: conteúdo
 * @return Retorna o vértice com o conteúdo dado, ou nullptr se não existir.
 */
Vertex* Graph::findVertex(const std::string &in) const {
    for (auto v : vertexSet)
        if (v->getCode() == in)
            return v;
    return nullptr;
}

/**
 * @brief Adiciona um vértice com um dado conteúdo (v) a um grafo (this).
 * @details Complexidade: O(1)
 * @param v: vértice
 * @return Retorna true se tiver sucesso e falso se um vértice com esse conteúdo já existir.
 */
bool Graph::addVertex(Vertex* v) {
    if (findVertex(v->getCode()) != nullptr) {
        return false;
    }
    vertexSet.push_back(v);
    return true;
}

/**
 * @brief Remove um vértice com um dado conteúdo (in) de um grafo (this), e todas as arestas de saída e entrada.
 * @details Complexidade: O(|vertexSet|)
 * @param in: conteúdo
 * @return Retorna true se tiver sucesso e falso se tal vértice não existir.
 */
bool Graph::removeVertex(const std::string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getCode() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
/**
 * @brief Adiciona uma aresta a um grafo (this), dado o conteúdo dos vértices de origem e destino e o peso da aresta (w).
 * @details Complexidade: O(|vertexSet|)
 * @param sourc: conteúdo do vértice de origem
 * @param dest: conteúdo do vértice de destino
 * @param w: peso da aresta
 * @return Retorna true se tiver sucesso e falso se o vértice de origem ou destino não existir.
 */
bool Graph::addEdge(const std::string &sourc, const std::string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }
    v1->addEdge(v2, w);
    return true;
}


/**
 * @brief Remove uma aresta de um grafo (this).
 * @brief A aresta é identificada pelos conteúdos de origem (sourc) e destino (dest).
 * @details Complexidade: O(|adj|)
 * @param sourc: conteúdo do vértice de origem
 * @param dest: conteúdo do vértice de destino
 * @return
 */
bool Graph::removeEdge(const std::string &sourc, const std::string &dest) {
    Vertex* srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

/**
 * @brief Adiciona uma aresta bidirecional a um grafo (this).
 * @details Complexidade: O(|vertexSet|)
 * @param sourc: conteúdo do vértice de origem
 * @param dest: conteúdo do vértice de destino
 * @param w: peso da aresta
 * @return Retorna true se tiver sucesso e falso se o vértice de origem ou destino não existir.
 */
bool Graph::addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/**
 * @brief Parte do destrutor da classe Graph.
 * @param m: número de linhas
 * @param n: número de colunas
 */
inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

/**
 * @brief Parte do destrutor da classe Graph.
 * @param m: número de linhas
 * @param n: número de colunas
 */
inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

/**
 * @brief Destrutor da classe Graph.
 */
Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}