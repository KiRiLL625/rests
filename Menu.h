#ifndef RESTAURANTS_MENU_H
#define RESTAURANTS_MENU_H

#include "Restaurant.h"

class Menu {
private:
    Restaurant* current_restaurant;
public:
    Menu() = default;

    Menu(Restaurant* currentRestaurant);

    void show();

    void addDish();

    void removeDish();

    void editDish();

    void showDishes();

    void showDish();

    void showRestaurants();

    void showRestaurant();

    void showEngineerMenu();

    void showHelp();

    void showAbout();

    void showExit();

};


#endif //RESTAURANTS_MENU_H
