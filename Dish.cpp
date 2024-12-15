#include "Dish.h"
#include <pqxx/pqxx>

Dish::Dish(int id): id(id) {}

Dish::Dish(int id, std::string name, int price, int restaurant_id): id(id), name(std::move(name)), price(price), restaurant_id(restaurant_id) {}

int Dish::getId() const {
    return id;
}

void Dish::setId(int id) {
    this->id = id;
}

const std::string &Dish::getName() const {
    return name;
}

void Dish::setName(const std::string &name) {
    this->name = name;
}

int Dish::getPrice() const {
    return price;
}

void Dish::setPrice(int price) {
    this->price = price;
}

int Dish::getRestaurantId() const {
    return restaurant_id;
}

void Dish::setRestaurantId(int restaurantId) {
    restaurant_id = restaurantId;
}

int Dish::queryInsert() {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("INSERT INTO dishes (name, price, restaurant_id) VALUES ('" + name + "', " + std::to_string(price) + ", " + std::to_string(restaurant_id) + ") RETURNING id");
    if(result.empty()) {
        return -1;
    }
    id = result[0][0].as<int>();
    work.commit();
    return id;
}

int Dish::queryUpdate(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("UPDATE dishes SET name = '" + name + "', price = " + std::to_string(price) + ", restaurant_id = " + std::to_string(restaurant_id) + " WHERE id = " + std::to_string(id) + " RETURNING id");
    if(result.empty()) {
        return -1;
    }
    id = result[0][0].as<int>();
    work.commit();
    return id;
}

int Dish::queryDelete(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("DELETE FROM dishes WHERE id = " + std::to_string(id) + " RETURNING id");
    if(result.empty()) {
        return -1;
    }
    id = result[0][0].as<int>();
    work.commit();
    return id;
}

int Dish::querySelect(int id) {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("SELECT name, price, restaurant_id FROM dishes WHERE id = " + std::to_string(id));
    if(result.empty()) {
        return -1;
    }
    name = result[0][0].as<std::string>();
    price = result[0][1].as<int>();
    restaurant_id = result[0][2].as<int>();
    work.commit();
    return id;
}

/*
int Dish::querySelectAll() {
    pqxx::connection connection("dbname=restaurants user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    pqxx::work work(connection);
    pqxx::result result = work.exec("SELECT id, name, price, restaurant_id FROM dishes");
    for(const pqxx::row &row: result) {
        id = row[0].as<int>();
        name = row[1].as<std::string>();
        price = row[2].as<int>();
        restaurant_id = row[3].as<int>();
    }
    work.commit();
    if(result.empty()) {
        return -1;
    }
    return 0;
}
 */