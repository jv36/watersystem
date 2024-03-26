#ifndef WATERSYSTEM_MENU_H
#define WATERSYSTEM_MENU_H

#include "Manager.h"

class Menu {
public:
    int main();
    int mainMenu();
    int maxFlowToCity();
    int affectingReservoirs();
    int affectingStations();
private:
    Manager manager;
    Graph graph;

    int affectingPipes();
};
#endif //WATERSYSTEM_MENU_H
