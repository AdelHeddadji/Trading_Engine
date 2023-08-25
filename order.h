// order.h
#pragma once

#include <string>

class Order {
public:
    Order(int id, const std::string& type, double price, int quantity);
    int getId() const;
    std::string getType() const;
    double getPrice() const;
    int getQuantity() const;

private:
    int id;
    std::string type;
    double price;
    int quantity;
};
