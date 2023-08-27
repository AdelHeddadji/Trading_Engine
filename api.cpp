// api.cpp
#include "api.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "order_book.h"

void DataHandler::read(int& current_id, int& total_size, std::vector<std::string>& all_lines) {
    std::ifstream readFile(filename);
    if (readFile.is_open()) {  // Check if the file is open
        if (readFile.peek() == std::ifstream::traits_type::eof()) {  // Check if the file is empty
            std::cout << "The file is empty, initializing current_id and total_size to 0." << std::endl;
        } else {
            std::string line;
            while (getline(readFile, line)) {
                all_lines.push_back(line);
            }
            if (!all_lines.empty()) {
                std::stringstream ss(all_lines[0]);
                ss >> current_id >> total_size;
            }
        }
        readFile.close();
    } else {
        std::cout << "The file could not be opened, initializing current_id and total_size to 0." << std::endl;
    }
}


void DataHandler::write(const OrderBook& ob) {
    std::ofstream writeFile(filename);
    if (writeFile.is_open()) {
        writeFile << ob.getCurrentID() << " " << ob.getTotalOrders() << std::endl;

        // Accessing orders from OrderBook
        const std::unordered_map<int, Order*>& orderMap = ob.getOrderMap();
        for (const auto& [id, order] : orderMap) {
            // Assuming Order has a method to convert it to string
            writeFile << order->toString() << std::endl;
        }
        
        writeFile.close();
        // std::cout << "Data has been written to the order book." << std::endl;
    } else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}