// order_book.cpp
#include "order_book.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void OrderBook::addOrder(Order& order) {
    int current_id = 0;
    int total_size = 0;
    vector<string> all_lines;
    ifstream readFile("order_book_data.csv");
    if (readFile.is_open() && readFile.peek() != std::ifstream::traits_type::eof()) {
        string line;
        while (getline(readFile, line)) {
            all_lines.push_back(line);
        }
        if (!all_lines.empty()) {
            stringstream ss(all_lines[0]);
            ss >> current_id >> total_size;
        }
        readFile.close();
    } else {
        cout << "The file is empty or could not be opened, initializing current_id and total_size to 0." << endl;
    }

    current_id++;
    total_size++;

    ofstream writeFile("order_book_data.csv");
    if (writeFile.is_open()) {
        writeFile << current_id << " " << total_size << endl;

        for (size_t i = 1; i < all_lines.size(); ++i) {
            writeFile << all_lines[i] << endl;
        }

        writeFile << current_id << "," << order.name << "," << order.type << "," << order.price << "," << order.quantity << endl;
        
        writeFile.close();
        cout << "Order has been added to the order book." << endl;
    } else {
        cout << "Failed to open the file for writing." << endl;
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
