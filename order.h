// order.h
#pragma once

#include <string>

class Order {
public:
    Order(int id, const std::string& type, double price, int quantity);
    std::string toString() const;
    int id;
    std::string type;
    double price;
    int quantity;
};
