#include "Restaurant.h"
#include "Dish.h"
#include <pqxx/pqxx>
#include <utility>

Restaurant::Restaurant(int id): id(id) {
    querySelect(id);
}

Restaurant::Restaurant(int id, std::string name, std::string dish_table_name): id(id), name(std::move(name)), dish_table_name(std::move(dish_table_name)) {}

int Restaurant::getId() const {
    return id;
}

void Restaurant::setId(int id) {
    this->id = id;
}

const std::string &Restaurant::getName() const {
    return name;
}

void Restaurant::setName(const std::string &name) {
    this->name = name;
}

const std::string &Restaurant::getDishTableName() const {
    return dish_table_name;
}

void Restaurant::setDishTableName(const std::string &dishTableName) {
    dish_table_name = dishTableName;
}

int Restaurant::queryInsert() {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("INSERT INTO restaurants (name, dish_table_name) VALUES ('" + name + "', '" + dish_table_name + "') RETURNING id");
    if(result.empty()) {
        return -1;
    }
    id = result[0][0].as<int>();
    work.commit();
    return id;
}

int Restaurant::queryUpdate(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("UPDATE restaurants SET name = '" + name + "', dish_table_name = '" + dish_table_name + "' WHERE id = " + std::to_string(id) + " RETURNING id");
    if(result.empty()) {
        return -1;
    }
    work.commit();
    return id;
}

int Restaurant::queryDelete(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("DELETE FROM restaurants WHERE id = " + std::to_string(id) + " RETURNING id");
    if(result.empty()) {
        return -1;
    }
    work.commit();
    return id;
}

int Restaurant::querySelect(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("SELECT name, dish_table_name FROM restaurants WHERE id = " + std::to_string(id));
    if(result.empty()) {
        return -1;
    }
    this->id = id;
    name = result[0][0].as<std::string>();
    dish_table_name = result[0][1].as<std::string>();
    work.commit();
    return id;
}

int Restaurant::addDish(int dish_id, std::string name, int price, int restaurant_id) {
    Dish dish(dish_id, std::move(name), price, restaurant_id);
    return dish.queryInsert();
}

int Restaurant::changeDishTable() {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("UPDATE restaurants SET dish_table_name = '" + dish_table_name + "' WHERE id = " + std::to_string(this->id) + " RETURNING id");
    if(result.empty()) {
        return -1;
    }
    work.commit();
    return id;
}

int Restaurant::removeDish(int dish_id) {
    Dish dish(dish_id);
    return dish.queryDelete(dish_id);
}

std::vector<std::tuple<int, std::string, int, int>> Restaurant::getDishes() {
    std::vector<std::tuple<int, std::string, int, int>> dishes;
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("SELECT id, name, price, restaurant_id FROM dishes WHERE restaurant_id = " + std::to_string(id));
    for(const pqxx::row &row: result) {
        dishes.emplace_back(row[0].as<int>(), row[1].as<std::string>(), row[2].as<int>(), row[3].as<int>());
    }
    work.commit();
    return dishes;
}