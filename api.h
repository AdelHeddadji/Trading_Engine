#ifndef API_H
#define API_H

#include <string>
#include <vector>
#include <unordered_map>

// Forward declaration of the Order and OrderBook classes
class Order;
class OrderBook;

class DataHandler {
public:
    DataHandler(const std::string& filename) : filename(filename) {}
    
    // Read data from the server and update the current_id, total_size, and all_lines.
    void read(int& current_id, int& total_size, std::vector<std::string>& all_lines);

    // Write the current state of the OrderBook to the server.
    void write(const OrderBook& ob);

private:
    std::string filename;
};

#endif // API_H

