//
// Created by joaomendes on 28-02-2024.
//

#include "Menu.h"
#include <iostream>


int Menu::main() {
    Manager manager;
    manager.createReservoirs("../smalldataset/Reservoirs_Madeira.csv", graph);
    manager.createCities("../smalldataset/Cities_Madeira.csv", graph);
    manager.createStations("../smalldataset/Stations_Madeira.csv", graph);
    manager.createPipes("../smalldataset/Pipes_Madeira.csv", graph);
    mainMenu();
    return 0;
}

int Menu::mainMenu() {
    std::cout << "+-------------------------------+\n";
    std::cout << "| Welcome to the Water System!  |\n";
    std::cout << "|                               |\n";
    std::cout << "| Our menu works based on       |\n";
    std::cout << "| number inputs! i.e., for      |\n";
    std::cout << "| option 1, please input 1 in   |\n";
    std::cout << "| the terminal.                 |\n";
    std::cout << "|                               |\n";
    std::cout << "| ========== Main Menu =========|\n";
    std::cout << "| 1 - Number of elements        |\n";
    std::cout << "| 2 -                           |\n";
    std::cout << "| 3 -                           |\n";
    std::cout << "| 4 -                           |\n";
    std::cout << "| 5 - Exit                      |\n";
    std::cout << "| ============================= |\n";
    std::cout << "| Please enter your choice:     |\n";
    std::cout << "+-------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    switch(n) {
        case 1:
            manager.counter(graph);
            break;
    }

    return 0;
}
