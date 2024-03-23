#ifndef WATERSYSTEM_MENU_H
#define WATERSYSTEM_MENU_H

#include "Manager.h"

class Menu {
public:
    int main();
    int mainMenu();

private:
    Manager manager;
    Graph graph;

    int maxFlowToCity();
};
#endif //WATERSYSTEM_MENU_H
