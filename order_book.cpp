// order_book.cpp
#include "order_book.h"
#include <algorithm>
#include <vector>
#include <string>
#include "order.h"
#include "lib.h"

using namespace std;

OrderBook::OrderBook(vector<string>& data) {
    if (data.size() == 0) {
        this->currentID = 0, this->totalOrders = 0;
        return;
    }
    vector<string> firstLine = split(data[0], " ");
    this->currentID = stoi(firstLine[0]), this->totalOrders = stoi(firstLine[1]);

    for (int i = 1; i < data.size(); i++) {
        vector<string> line = split(data[0], ",");
        int id = stoi(line[0]), quantity = stoi(line[3]);
        float price = stof(line[2]);
        string type =line[1]; 
        Order *currOrder = new Order(id, type, price, quantity);
        this->orderMap[id] = currOrder;
        addOrder(currOrder);
    }
}   

void OrderBook::addOrder(Order* order) {
    this->orderMap[order->id] = order;
    float price = order->price;
    if (order->type == "buy") {
            if (!this->buyLevels.count(price)) {
                vector<Order*> initialOrders;
                initialOrders.push_back(order);
                PriceLevel  *currPriceLevel = new PriceLevel(price, initialOrders); 
                this->buyLevels[price] = currPriceLevel;
                return;
            }
            this->buyLevels[price]->orders.push_back(order);
        }
    else if (order->type == "sell") {
        if (!this->buyLevels.count(price)) {
            vector<Order*> initialOrders;
            initialOrders.push_back(order);
            PriceLevel  *currPriceLevel = new PriceLevel(price, initialOrders); 
            this->sellLevels[price] = currPriceLevel;
            return;
        }
        this->sellLevels[price]->orders.push_back(order);
    }
}

// void OrderBook::removeOrder(int id) {
//     // Implementation to remove an order by ID from buyOrders and sellOrders
//     // ...
// }

// void OrderBook::modifyOrder(int id, int newQuantity) {
//     // Implementation to find an order by ID and modify its quantity
//     // ...
// }

// void OrderBook::executeTrades() {
//     // Implementation for matching buy and sell orders and executing trades
//     // ...
// }
