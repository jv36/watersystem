//
// Created by joaomendes on 08-03-2024.
//

#ifndef WATERSYSTEM_MANAGER_H
#define WATERSYSTEM_MANAGER_H


#include <string>

class Manager {
public:
    void createReservoirs(const std::string &filename);
    void createPipes(const std::string &filename);
    void createCities(const std::string &filename);
private:
};


#endif //WATERSYSTEM_MANAGER_H
