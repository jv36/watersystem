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
    int affectingPipes();
private:
    Manager manager;
    Graph graph;
};
#endif //WATERSYSTEM_MENU_H
