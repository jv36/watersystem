#include "Menu.h"
#include <iostream>


/**
 * @brief Apresenta o menu inicial do sistema de gestão de água - usado para escolher o tipo de dataset.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Complexidade: O(1)
 */
int Menu::main() {
    Manager manager;

    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| Before starting, you have to choose a dataset           |\n";         
    std::cout << "| to perform the operations.                              |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - Madeira Island                                      |\n";
    std::cout << "| 2 - Continental Portugal                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 2 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            manager.createReservoirs("../smalldataset/Reservoirs_Madeira.csv", graph);
            manager.createCities("../smalldataset/Cities_Madeira.csv", graph);
            manager.createStations("../smalldataset/Stations_Madeira.csv", graph);
            manager.createPipes("../smalldataset/Pipes_Madeira.csv", graph);
            break;
        case 2:
            manager.createReservoirs("../largedataset/Reservoir.csv", graph);
            manager.createCities("../largedataset/Cities.csv", graph);
            manager.createStations("../largedataset/Stations.csv", graph);
            manager.createPipes("../largedataset/Pipes.csv", graph);
            break;
    }
    mainMenu();
    return 0;
}

/**
 * @brief Apresenta o menu principal do sistema de gestão de água.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Complexidade: O(1)
 */
int Menu::mainMenu() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| Welcome to the Water System!                            |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| Our menu works based on                                 |\n";
    std::cout << "| number inputs! i.e., for                                |\n";
    std::cout << "| option 1, please input 1 in                             |\n";
    std::cout << "| the terminal.                                           |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| ==================== Main Menu ======================== |\n";
    std::cout << "| 1 - Number of elements                                  |\n";
    std::cout << "| 2 - Maximum network flow                                |\n";
    std::cout << "| 3 - Maximum amount of water that can reach a given city |\n";
    std::cout << "| 4 - List max flow for all cities                        |\n";
    std::cout << "| 5 - Cities with water flow deficit                      |\n";
    std::cout << "| 6 - Affecting reservoirs                                |\n";
    std::cout << "| 7 - Affecting pumping stations                          |\n";
    std::cout << "| 8 - Affecting pipelines                                 |\n";
    std::cout << "| 9 - Exit                                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 9 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            manager.counter(graph);
            break;
        case 2:
            manager.maxWaterFlowTotal(graph);
            break;
        case 3:
            maxFlowToCity();
            break;
        case 4:
            manager.maxWaterFlowAllCities(graph);
            break;
        case 5:
            manager.flowDeficit(graph);
            break;
        case 6:
            affectingReservoirs();
            break;
        case 7:
            affectingStations();
            break;
        case 8:
            affectingPipes();
            break;
        case 9:
            exit(0);
    }

    return 0;
}

/**
 * @brief Apresenta o menu de reservatórios.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Apresenta as cidades afetadas após a remoção de um reservatório especificado pelo utilizador.
 * @details Complexidade: O(V) - V é o número de vértices no grafo.
 */
int Menu::affectingReservoirs() {
    std::cout << "Do you wish to see a full list of reservoirs & respective codes? (y/n)\n";
    char c;
    std::cin >> c;
    if (c == 'y') {
        for (auto v : graph.getVertexSet()) {
            if (v->getCode().at(0) == 'R') {
                std::cout << v->getCode() << "\n";
            }
        }
    }

    Vertex* reservoir;
    std::string name, code;
    std::cout << "Please enter the code of the reservoir you wish to see the cities affected by:\n";
    std::cin >> code;
    reservoir = graph.findVertex(code);
    if (reservoir == nullptr) {
        std::cout << "Reservoir not found!\n";
        return 0;
    }
    std::cout << "Upon the removal of reservoir with code " << code << ", the following cities will be affected:\n";
    manager.affectingReservoirs(graph, code);

    return 0;
}

/**
 * @brief Apresenta o fluxo máximo para uma cidade específica.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Complexidade: O(V) - V é o número de vértices no grafo ou O(1) - depende do input.
 */
int Menu::maxFlowToCity() {
    std::cout << "Do you wish to see a full list of cities & respective codes? (y/n)\n";
    char c;
    std::cin >> c;
    if (c == 'y') {
        for (auto v : graph.getVertexSet()) {
            if (v->getCode().at(0) == 'C') {
                std::cout << v->getCity() << " with code " << v->getCode() << "\n";
            }
        }
    }

    std::cout << "+-------------------------------+\n";
    std::cout << "| Select type of input:         |\n";
    std::cout << "| 1 - City name                 |\n";
    std::cout << "| 2 - City code                 |\n";
    std::cout << "| 3 - Return to main menu       |\n";
    std::cout << "+-------------------------------+\n";
    int inputType;
    std::cin >> inputType;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((inputType < 1 || inputType > 3 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> inputType;
        std::cout << std::endl;
    }

    Vertex* city;
    std::string name, code;
    switch (inputType) {
        case 1:
            std::cout << "Please enter the name of the city you wish to see the maximum flow to:\n";
            std::cin >> name;
            for (auto v : graph.getVertexSet()) {
                if (v->getCity() == name) {
                    city = v;
                    break;
                }
            }
            if (city == nullptr) {
                std::cout << "City not found!\n";
                return 0;
            }
            manager.maxWaterFlowCity(graph, city->getCode());
            break;
        case 2:
            std::cout << "Please enter the code of the city you wish to see the maximum flow to:\n";
            std::cin >> code;
            city = graph.findVertex(code);
            if (city == nullptr) {
                std::cout << "City not found!\n";
                return 0;
            }
            manager.maxWaterFlowCity(graph, code);
            break;
        case 3:
            mainMenu();
            break;
    }

    return 0;
}

/**
 * @brief Apresenta as estações de bombagem afetadas após a remoção de uma estação específica.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Complexidade: O(V) - V é o número de vértices no grafo.
 */
int Menu::affectingStations() {

    Vertex* station;
    std::string code;

    std::cout << "Do you wish to see a full list of stations & respective codes? (y/n)\n";
    char c;
    std::cin >> c;
    if (c == 'y') {
        for (auto v : graph.getVertexSet()) {
            if (v->getCode().at(0) == 'P') {
                std::cout << v->getCode() << "\n";
            }
        }
    }
    std::cout << "Please enter the code of the station you wish to see the cities affected by:\n";
    std::cin >> code;
    station = graph.findVertex(code);
    if (station == nullptr) {
        std::cout << "Station not found!\n";
        return 0;
    }
    std::cout << "Upon the removal of station with code " << code << ", the following cities will be affected:\n";
    manager.affectingStations(graph, code);
    return 0;

}


/**
 * @brief Apresenta as cidades afetadas após a remoção de um pipe específico.
 * @details Manipula o input do utilizador e redireciona para a função correspondente.
 * @details Complexidade: O(V + E) - número de vértices + número de edges.
 *
 */
int Menu::affectingPipes() {
    std::cout << "Do you wish to see a full list of pipes & respective codes? (y/n)\n";
    char c;
    std::cin >> c;
    if (c == 'y') {
        for (auto v : graph.getVertexSet()) {
            for (auto e : v->getAdj()) {
                std::cout << e->getOrig()->getCode() << " to " << e->getDest()->getCode() << "\n";
            }
        }
    }

    std::string source, dest;
    std::cout << "Please enter the code of the source pipe:\n";
    std::cin >> source;
    std::cout << "Please enter the code of the destination pipe:\n";
    std::cin >> dest;

    std::cout << "Upon the removal of the pipe from " << source << " to " << dest << ", the following cities will be affected:\n";
    manager.affectingPipes(graph, source, dest);

    return 0;
}