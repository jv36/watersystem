#include "Menu.h"
#include <iostream>


int Menu::main() {
    Manager manager;
    manager.createReservoirs("../largedataset/Reservoir.csv", graph);
    manager.createCities("../largedataset/Cities.csv", graph);
    manager.createStations("../largedataset/Stations.csv", graph);
    manager.createPipes("../largedataset/Pipes.csv", graph);

    /*
    manager.createReservoirs("../smalldataset/Reservoirs_Madeira.csv", graph);
    manager.createCities("../smalldataset/Cities_Madeira.csv", graph);
    manager.createStations("../smalldataset/Stations_Madeira.csv", graph);
    manager.createPipes("../smalldataset/Pipes_Madeira.csv", graph);
     */


    mainMenu();
    return 0;
}

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
    std::cout << "| 1 - Number of elements (DEBUG)                          |\n";
    std::cout << "| 2 - Maximum network flow                                |\n";
    std::cout << "| 3 - Maximum amount of water that can reach a given city |\n";
    std::cout << "| 4 - List max flow for all cities                        |\n";
    std::cout << "| 5 - Exit                                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    switch(n) {
        case 1:
            manager.counter(graph);
            break;
        case 2:
            manager.maxWaterFlow(graph);
            break;
        case 3:
            maxFlowToCity();
            break;
        case 4:
            manager.maxWaterFlowAllCities(graph);
            break;
        case 5:
            exit(0);
    }

    return 0;
}

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
