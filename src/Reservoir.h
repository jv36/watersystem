//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_RESERVOIR_H
#define WATERSYSTEM_RESERVOIR_H


#include <string>

class Reservoir {
public:
    Reservoir(const std::string &name, const std::string &municipality, int id, const std::string &code, double maxDelivery);
    std::string getName() const;
    std::string getMunicipality() const;
    int getId() const;
    std::string getCode() const;
    double getMaxDelivery() const;
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    double maxDelivery;
};


#endif //WATERSYSTEM_RESERVOIR_H
