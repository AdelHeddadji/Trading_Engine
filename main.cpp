#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "order.h"
#include "order_book.h"
#include "api.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> all_lines;
    int current_id = 0, total_size = 0;

    DataHandler dataHandle = DataHandler("data.csv");

    dataHandle.read(current_id, total_size, all_lines);

    OrderBook myOrderBook = OrderBook(all_lines);

    string operation = argv[1];
    if (operation == "add") {
        string type = argv[2];
        float price = stof(argv[3]);
        int quantity = stoi(argv[4]);
        Order *currOrder = new Order(current_id, type, price, quantity);
        myOrderBook.addOrder(currOrder, true);
    } 
    else if (operation == "remove") {
        int id = stoi(argv[2]);
        myOrderBook.removeOrder(id);
        // cout << "Order has been removed." << endl;
    }
    else if (operation == "modify") {
        int id = stoi(argv[2]);
        float price = stof(argv[3]);
        int quantity = stoi(argv[4]);
        myOrderBook.modifyOrder(id, price, quantity);
    }
    else {
        cout << "Unknown operation." << endl;
    }

    dataHandle.write(myOrderBook);

    return 0;
}

