#include "api.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <curl/curl.h>
#include <thread>
#include <condition_variable>

std::mutex mtx;  // Mutex for critical sections
std::condition_variable cv;  // Condition variable for signaling

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void DataHandler::read(int& current_id, int& total_size, std::vector<std::string>& all_lines) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/read");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::stringstream ss(readBuffer);
            ss >> current_id >> total_size;
            std::string line;
            while (getline(ss, line)) {
                all_lines.push_back(line);
            }
        }
        
        curl_easy_cleanup(curl);
    }
    cv.notify_one();  // Notify one waiting thread
}

void DataHandler::write(const OrderBook& ob) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
    CURL *curl = curl_easy_init();
    if (curl) {
        std::string postData = "current_id=" + std::to_string(ob.getCurrentID()) + "&total_size=" + std::to_string(ob.getTotalOrders());

        const std::unordered_map<int, Order*>& orderMap = ob.getOrderMap();
        for (const auto& [id, order] : orderMap) {
            postData += "&order=" + order->toString();  // Assuming Order has a method to convert it to string
        }

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/write");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    cv.notify_one();  // Notify one waiting thread
}
