#include "include/BloomFilter.h"
#include <iostream>
#include <vector>

int main() {
    size_t filter_size = 1024 * 1024 * 8;
    int num_hashes =7;

    BloomFilter firewall(filter_size, num_hashes);

    std::cout << "--- Initializing IoT Firewall ---" << std:: endl;

    std::vector<std::string> blacklist = {
        "192.168.1.100",
        "10.0.0.5",
        "172.16.0.22"
    };

    for(const auto& ip: blacklist) {
        firewall.add(ip);
        std::cout<<"Blacklisted: " << ip << std::endl;
    }

    std::cout<< "\n--- Monitoring Incomming Traffic ---" << std::endl;
    std::vector<std::string> incoming_traffic ={
        "192.169.1.1",
        "10.0.0.5",
        "8.8.8.8"
    };

    for(const auto& ip : incoming_traffic){
        if(firewall.contains(ip)){
            std::cout << "[BLOCK] Dropping packet from: " << ip <<std::endl;
        }
        else{
            std::cout<<"[ALLOW] Passing packet from: "<< ip << std::endl;
        }
    }

    return 0;

}