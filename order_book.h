// order_book.h
#pragma once

#include <vector>
#include "Order.h"

class OrderBook {
public:
    void addOrder(const Order& order);
    void removeOrder(int id);
    void modifyOrder(int id, int newQuantity);
    void executeTrades();

private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
};
