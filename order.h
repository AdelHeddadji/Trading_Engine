// order.h
#pragma once

#include <string>
#include <chrono>

class Order {
public:
    Order(int id, const std::string& type, double price, int quantity);
    std::string toString() const;
    int id;
    std::string type;
    double price;
    int quantity;
    std::chrono::system_clock::time_point timestamp;
};
