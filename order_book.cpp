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
        vector<string> line = split(data[i], ",");
        int id = stoi(line[0]), quantity = stoi(line[3]);
        float price = stof(line[2]);
        string type =line[1]; 
        Order *currOrder = new Order(id, type, price, quantity);
        this->orderMap[id] = currOrder;
        addOrder(currOrder, false);
    }
}   

void OrderBook::addOrder(Order* order, bool isNew) {
    if (isNew) {
        this->currentID++;
        this->totalOrders++;
        order->id = this->currentID;
    }
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

void OrderBook::removeOrder(int id) {
    if (!this->orderMap.count(id)) {
        printf("Order id not present in Orderbook");
        return;
    }
    Order *temp = this->orderMap[id];
    map<float, PriceLevel*>& levels = (temp->type == "buy") ? this->buyLevels : this->sellLevels;

    if (levels.count(temp->price)) {
        auto& orders = levels[temp->price]->orders;
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it)->id == id) {
                orders.erase(it);
                if (orders.empty()) {
                    delete levels[temp->price];
                    levels.erase(temp->price);
                }
                
                break;
            }
        }
    }
    delete this->orderMap[id];
    this->orderMap.erase(id);
    this->totalOrders--;
}

void OrderBook::modifyOrder(int id, float newPrice, int newQuantity) {
    if (!this->orderMap.count(id)) {
        printf("Order id not present in Orderbook");
        return;
    }
    Order *oldOrder = this->orderMap[id];
    Order *newOrder = new Order(id, oldOrder->type, newPrice, newQuantity);
    this->removeOrder(id);
    this->addOrder(newOrder, false);
    this->totalOrders++;
}

void OrderBook::priceTimeMatch() {
    for (auto& sellPair : sellLevels) {
        float sellPrice = sellPair.first;
        auto& sellOrders = sellPair.second->orders;

        while (!sellOrders.empty()) {
            auto& sellOrder = sellOrders[0];

            auto it = buyLevels.lower_bound(sellPrice);
            if (it == buyLevels.end()) {
                break; 
            }

            float buyPrice = it->first;
            auto& buyOrders = it->second->orders;

            auto& buyOrder = buyOrders[0];

            int matchQuantity = min(buyOrder->quantity, sellOrder->quantity);

            buyOrder->quantity -= matchQuantity;
            sellOrder->quantity -= matchQuantity;

            if (buyOrder->quantity == 0) {
                buyOrders.erase(buyOrders.begin());
                delete buyOrder; 
                if (buyOrders.empty()) {
                    delete it->second; 
                    buyLevels.erase(it);
                }
            }
            if (sellOrder->quantity == 0) {
                sellOrders.erase(sellOrders.begin());
                delete sellOrder; 
                if (sellOrders.empty()) {
                    delete sellPair.second; 
                    sellLevels.erase(sellPrice);
                    break; 
                }
            }
        }
    }
}
