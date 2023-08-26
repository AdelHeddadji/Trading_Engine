// order_book.h
#pragma once

#include <vector>
#include <string>
#include "order.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>

using namespace std;

struct PriceLevel {
    float price;
    vector<Order*> orders; // Use deque or list if you need to insert/remove at both ends frequently

    PriceLevel(float p, std::vector<Order*> o) : price(p), orders(o) {}
};


class OrderBook {
public:
    OrderBook(std::vector<std::string>& data);
    void addOrder(Order* order);
    // getters for private members (const because they don't modify the object)
    int getCurrentID() const { return currentID; }
    int getTotalOrders() const { return totalOrders; }
    const std::unordered_map<int, Order*>& getOrderMap() const { return orderMap; }

private:
    int currentID;
    int totalOrders;
    std::unordered_map<int, Order*> orderMap;
    std::map<float, PriceLevel*> buyLevels;
    std::map<float, PriceLevel*> sellLevels;
};
