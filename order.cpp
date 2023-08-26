// order.cpp
#include "order.h"

#include <sstream>

Order::Order(int id, const std::string& type, double price, int quantity)
    : id(id), type(type), price(price), quantity(quantity) {}


// int Order::getId() const {
//     return id;
// }

// std::string Order::getType() const {
//     return type;
// }

// double Order::getPrice() const {
//     return price;
// }

// int Order::getQuantity() const {
//     return quantity;
// }

std::string Order::toString() const {
    std::ostringstream os;
    os << id << "," << type << "," << price << "," << quantity;
    return os.str();
}
