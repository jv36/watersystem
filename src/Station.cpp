//
// Created by joaomendes on 08-03-2024.
//

#include "Station.h"

Station::Station(int id, const std::string &code) {
    this->id = id;
    this->code = code;
}

int Station::getId() const {
    return id;
}

std::string Station::getCode() const {
    return code;
}
