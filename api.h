// api.h
#include <vector>
#include <string>

class OrderBook; 

class DataHandler {
    public:
        DataHandler(const std::string& filename) : filename(filename) {}
        void read(int& current_id, int& total_size, std::vector<std::string>& all_lines);
        void write(const OrderBook& ob);

    private:
        std::string filename;
};
