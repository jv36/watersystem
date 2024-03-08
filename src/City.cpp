//
// Created by joaomendes on 08-03-2024.
//

#include "City.h"

City::City(const std::string &city, int id, const std::string &code, double demand, int population) {
    this->city = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

std::string City::getCity() const {
    return city;
}

int City::getId() const {
    return id;
}

std::string City::getCode() const {
    return code;
}

double City::getDemand() const {
    return demand;
}

int City::getPopulation() const {
    return population;
}
