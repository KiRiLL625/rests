#ifndef RESTAURANTS_RESTAURANT_H
#define RESTAURANTS_RESTAURANT_H

#include <string>
#include <vector>

class Restaurant {
private:
    int id;
    std::string name;
    std::string dish_table_name;
public:
    Restaurant() = default;

    Restaurant(int id);

    Restaurant(int id, std::string name, std::string dish_table_name);

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getDishTableName() const;

    void setDishTableName(const std::string &dishTableName);

    int queryInsert();

    int queryUpdate(int id);

    int queryDelete(int id);

    int querySelect(int id);

    int changeDishTable();

    int addDish(int dish_id, std::string name, int price, int restaurant_id);

    int removeDish(int dish_id);

    //std::string[] getDishes();

    std::vector<std::tuple<int, std::string, int, int>> getDishes();
};


#endif //RESTAURANTS_RESTAURANT_H
