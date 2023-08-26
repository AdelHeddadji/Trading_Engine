// order_book.h
#pragma once

#include <vector>
#include "order.h"
#include <iostream>
#include <fstream>
#include <sstream>

class OrderBook {
public:
    void addOrder(Order& order);
    // void removeOrder(int id);
    // void modifyOrder(int id, int newQuantity);
    // void executeTrades();

private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
};
