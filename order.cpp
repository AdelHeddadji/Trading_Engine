// order.cpp
#include "order.h"

#include <sstream>

Order::Order(int id, const std::string& type, double price, int quantity)
    : id(id), type(type), price(price), quantity(quantity) {
    timestamp = std::chrono::system_clock::now();
}

std::string Order::toString() const {
    std::ostringstream os;
    os << id << "," << type << "," << price << "," << quantity;
    return os.str();
}