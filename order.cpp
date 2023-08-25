// order.cpp
#include "order.h"

Order::Order(int id, const std::string& type, double price, int quantity)
    : id(id), type(type), price(price), quantity(quantity) {}

int Order::getId() const {
    return id;
}

std::string Order::getType() const {
    return type;
}

double Order::getPrice() const {
    return price;
}

int Order::getQuantity() const {
    return quantity;
}
