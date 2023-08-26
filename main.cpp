#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "order.h"
#include "order_book.h"

using namespace std;

pair<int, int> getCurrentID;

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage: ./trading_engine add <Name> <Price> <Quantity>" << endl;
        return 1;
    }

    OrderBook myOrderBook;

    string operation = argv[1];

    // int current_id = 0, total_size = 0;
    vector<string> all_lines;

    if (operation == "add") {
        string stockName = argv[2];
        string type = argv[3];
        float price = stof(argv[4]);
        int quantity = stoi(argv[5]);
        Order new_order = Order(stockName, "buy", price, quantity);
        myOrderBook.addOrder(new_order);
    } 
    else if (operation == "remove") {
        cout << "Order has been removed." << endl;
    }
    else {
        cout << "Unknown operation." << endl;
    }

    return 0;
}

