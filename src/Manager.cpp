//
// Created by joaomendes on 08-03-2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Manager.h"

void Manager::createReservoirs(const std::string &filename) {
    std::ifstream file("../csv/smalldataset/Reservoirs-Maa.csv");
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
    }
}

void Manager::createCities(const std::string &filename) {
    std::ifstream file("../csv/smalldataset/Cities-Madeira.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name, id, code, demand, population;

        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, ',');
    }
}

void Manager::createPipes(const std::string &filename) {
    std::ifstream file("../csv/smalldataset/Pipes-Madeira.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name, id, code, demand, population;

        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, ',');
    }
}

