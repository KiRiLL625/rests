#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pqxx/pqxx>

Menu::Menu(Restaurant *currentRestaurant) : current_restaurant(currentRestaurant) {}

void Menu::show() {
    std::cout << "===================" << "Welcome to " << current_restaurant->getName() << "!" << "===================" << std::endl;
    showDishes();

    //std::cout << "Press Ctrl+I to open the engineer menu..." << std::endl;

    while (true) {
        int ch = std::cin.get();
        if (ch == 9) {
            showEngineerMenu();
            break;
        }
    }
}

void Menu::addDish() {
    std::string name;
    int price;
    std::cout << "Enter dish name: ";
    std::cin >> name;
    std::cout << "Enter dish price: ";
    std::cin >> price;

    std::srand(std::time(nullptr));
    int dish_id = std::rand();

    current_restaurant->addDish(dish_id, name, price, current_restaurant->getId());
}

void Menu::removeDish() {
    int dish_id;
    std::cout << "Enter dish id: ";
    std::cin >> dish_id;
    current_restaurant->removeDish(dish_id);
}

void Menu::editDish() {
    int dish_id;
    std::string name;
    int price;
    std::cout << "Enter dish id: ";
    std::cin >> dish_id;
    std::cout << "Enter new dish name: ";
    std::cin >> name;
    std::cout << "Enter new dish price: ";
    std::cin >> price;
    current_restaurant->removeDish(dish_id);
    current_restaurant->addDish(dish_id, name, price, current_restaurant->getId());
}

void Menu::showDishes() {
    std::cout << "Dishes:" << std::endl;
    std::cout << "\tName\tPrice" << std::endl;
    for(auto& dish: current_restaurant->getDishes()) {
        std::cout << "\t" << std::get<1>(dish) << "\t" << std::get<2>(dish) << std::endl;
    }
}

void Menu::showDish() {
    int dish_id;
    std::cout << "Enter dish id: ";
    std::cin >> dish_id;
    for(auto& dish: current_restaurant->getDishes()) {
        if(std::get<0>(dish) == dish_id) {
            std::cout << "Dish: " << std::get<1>(dish) << std::endl;
            std::cout << "Price: " << std::get<2>(dish) << std::endl;
            return;
        }
    }
    std::cout << "Dish not found" << std::endl;
}

void Menu::showRestaurants() {
    std::cout << "Restaurants:" << std::endl;
    std::cout << "\tId\tName\tDish table name" << std::endl;
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("SELECT id, name, dish_table_name FROM restaurants");
    for(const pqxx::row &row: result) {
        std::cout << "\t" << row[0].as<int>() << "\t" << row[1].as<std::string>() << "\t" << row[2].as<std::string>() << std::endl;
    }
}

void Menu::showEngineerMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add dish" << std::endl;
    std::cout << "2. Remove dish" << std::endl;
    std::cout << "3. Edit dish" << std::endl;
    std::cout << "4. Show dishes" << std::endl;
    std::cout << "5. Show dish" << std::endl;
    std::cout << "6. Change restaurant" << std::endl;
    std::cout << "7. Show restaurants" << std::endl;
    std::cout << "8. Show restaurant" << std::endl;
    std::cout << "9. Change dish table" << std::endl;
    std::cout << "10. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    switch(choice) {
        case 1:
            addDish();
            break;
        case 2:
            removeDish();
            break;
        case 3:
            editDish();
            break;
        case 4:
            showDishes();
            break;
        case 5:
            showDish();
            break;
        case 6:
            std::cout << "Enter restaurant id: ";
            int restaurant_id;
            std::cin >> restaurant_id;
            std::cout << "Menu will be changed to " << restaurant_id << std::endl;
            current_restaurant->querySelect(restaurant_id);
            break;
        case 7:
            showRestaurants();
            break;
        case 8:
            std::cout << "Restaurant: " << current_restaurant->getName() << std::endl;
            show();
            break;
        case 9: {
            std::cout << "Enter new dish table name: ";
            std::string dish_table_name;
            std::cin >> dish_table_name;
            current_restaurant->setDishTableName(dish_table_name);
            current_restaurant->changeDishTable();
            break;
        }
        case 10:
            std::cout << "Goodbye!" << std::endl;
            show();
            return;
        default:
            std::cout << "Invalid choice" << std::endl;
    }
    showEngineerMenu();
}