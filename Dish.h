#ifndef RESTAURANTS_DISH_H
#define RESTAURANTS_DISH_H

#include <string>

class Dish {
private:
    int id;
    std::string name;
    int price;
    int restaurant_id;
public:
    Dish() = default;

    Dish(int id);

    Dish(int id, std::string name, int price, int restaurant_id);

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getPrice() const;

    void setPrice(int price);

    int getRestaurantId() const;

    void setRestaurantId(int restaurantId);

    int queryInsert();

    int queryUpdate(int id);

    int queryDelete(int id);

    int querySelect(int id);

    //int querySelectAll();
};


#endif //RESTAURANTS_DISH_H
