//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_CITY_H
#define WATERSYSTEM_CITY_H


#include <string>

class City {
public:
    City(const std::string &city, int id, const std::string &code, double demand, int population);
    std::string getCity() const;
    int getId() const;
    std::string getCode() const;
    double getDemand() const;
    int getPopulation() const;
private:
    std::string city;
    int id;
    std::string code;
    double demand;
    int population;
};


#endif //WATERSYSTEM_CITY_H
