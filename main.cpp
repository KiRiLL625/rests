#include <iostream>
#include "Menu.h"

int main() {
    std::cout << "Enter restaurant id: ";
    int restaurant_id;
    std::cin >> restaurant_id;
    Restaurant restaurant(restaurant_id);
    Menu menu(&restaurant);
    menu.show();
    return 0;
}
