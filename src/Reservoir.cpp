//
// Created by joaomendes on 08-03-2024.
//

#include "Reservoir.h"

Reservoir::Reservoir(const std::string &name, const std::string &municipality, int id, const std::string &code,
                     double maxDelivery) {
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxDelivery;
}

std::string Reservoir::getName() const {
    return name;
}

std::string Reservoir::getMunicipality() const {
    return municipality;
}

int Reservoir::getId() const {
    return id;
}

std::string Reservoir::getCode() const {
    return code;
}

double Reservoir::getMaxDelivery() const {
    return maxDelivery;
}




