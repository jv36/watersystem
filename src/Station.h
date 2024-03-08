//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_STATION_H
#define WATERSYSTEM_STATION_H


#include <string>

class Station {
public:
    Station(int id, const std::string &code);
    int getId() const;
    std::string getCode() const;
private:
    int id;
    std::string code;
};


#endif //WATERSYSTEM_STATION_H
