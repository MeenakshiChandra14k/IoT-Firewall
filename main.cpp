#include "include/BloomFilter.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

void logBlockedIP(const std::string& ip){
    std::ofstream logFile("firewall.log", std::ios_base::app);
    if(!logFile.is_open()) return;

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    logFile << "[" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << "] ";
    logFile << "BLOCKED: " << ip << "\n";

    logFile.close();

}


void loadBlacklist(const std::string& filename, BloomFilter& filter){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "[ERROR] Could not open" << filename << std::endl;
        return;
    }

    std::string ip;
    int count=0;
    while(std::getline(file, ip)){
        if(!ip.empty()){
            filter.add(ip);
            count++;
        }
    }
    std::cout << "[SUCCESS] Loaded " << count << " IPs from " << filename <<std::endl;
    file.close();
}


int main() {
    size_t filter_size = 1024 * 1024 * 8;
    int num_hashes =7;

    BloomFilter firewall(filter_size, num_hashes);

    std::cout << "--- Initializing IoT Firewall ---" << std:: endl;
    loadBlacklist("blacklist.txt",firewall);

    // std::vector<std::string> blacklist = {
    //     "192.168.1.100",
    //     "10.0.0.5",
    //     "172.16.0.22"
    // };

    // for(const auto& ip: blacklist) {
    //     firewall.add(ip);
    //     std::cout<<"Blacklisted: " << ip << std::endl;
    // }

    std::cout<< "\n--- Monitoring Incomming Traffic ---" << std::endl;
    std::vector<std::string> incoming_traffic ={
        "192.169.1.1",
        "10.0.0.5",
        "8.8.8.8",
        "8.8.4.4"
    };

    for(const auto& ip : incoming_traffic){
        if(firewall.contains(ip)){
            std::cout << "[BLOCK] Dropping packet from: " << ip <<std::endl;
            logBlockedIP(ip);
        }
        else{
            std::cout<<"[ALLOW] Passing packet from: "<< ip << std::endl;

        }
    }

    std::cout << "\nCheck 'firewall.log' for history." << std::endl;
    return 0;

}