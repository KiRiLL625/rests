cmake_minimum_required(VERSION 3.27.4)
project(restaurants)

set(CMAKE_CXX_STANDARD 17)

add_executable(restaurants main.cpp
        Dish.cpp
        Dish.h
        Restaurant.cpp
        Restaurant.h
        Menu.cpp
        Menu.h)

target_link_libraries(restaurants -lpqxx -lpq)