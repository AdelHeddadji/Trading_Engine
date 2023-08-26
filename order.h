// order.h
#pragma once

#include <string>

class Order {
public:
    Order(const std::string& name, const std::string& type, double price, int quantity);
    int id;
    std::string name;
    std::string type;
    double price;
    int quantity;
};
